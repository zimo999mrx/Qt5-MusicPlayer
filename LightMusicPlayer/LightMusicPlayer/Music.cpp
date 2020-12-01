#include "Music.h"
/* 先在.pro文件中加入QT += multimediawidgets,否则#include <QMediaPlayer>报错.
 * 参考：http://bbs.csdn.net/topics/390884883
 */
#include <QMediaPlayer>
#include <QCoreApplication> //QT控制台程序
#include <QMessageBox>
#include <QtSql>

Music::Music(QUrl iurl)
{
    //构造方法
    url=iurl;
    refreshInfo();
}

//调用外部函数，格式化时间，原函数在MainWidget.cpp中.
extern QString formatTime(qint64 timeMilliSeconds);

void Music::refreshInfo()
{
    QMediaPlayer tempPlayer;//QMediaPlayer 是音乐播放器类
    tempPlayer.setMedia(url);
    /* 音乐数据的解析需要时间，当读到不是音乐的文件的时候而没有任何处理方法会把页面卡住，
     * 加QCoreApplication::processEvents()可以防止处理数据时界面卡顿。
     * 参考: https://www.qter.org/forum.php?mod=viewthread&tid=1838
     */
    while(!tempPlayer.isMetaDataAvailable()){
        QCoreApplication::processEvents();
    }
    //文件是音乐文件，歌曲信息读取
    if(tempPlayer.isMetaDataAvailable()){
        //作者信息
        author = tempPlayer.metaData(QStringLiteral("Author")).toStringList().join(",");
        //歌曲名
        title = tempPlayer.metaData(QStringLiteral("Title")).toString();
        //唱片集
        albumTitle = tempPlayer.metaData(QStringLiteral("AlbumTitle")).toString();
        //歌曲比特率（音质）
        audioBitRate = tempPlayer.metaData(QStringLiteral("AudioBitRate")).toInt();
        //歌曲时长
        duration=tempPlayer.duration();
    }
}

QString Music::getInfo() const
{
    //返回歌曲的信息(作者 - 歌曲名 - 歌曲时长)
    return author+" - "+title+" ["+formatTime(duration)+"]";
}

void Music::detail()
{
    //把歌曲信息放入 info 中
    QString info("歌曲名：%1\n艺术家：%2\n时长：%3\n唱片集：%4\n比特率：%5\n文件路径：%6");
    info=info.arg(title,author,formatTime(duration),albumTitle,QString::number(audioBitRate)+"bps",url.toString());
    //弹窗显示信息
    QMessageBox::about(Q_NULLPTR,"歌曲信息",info);
}

//把新增歌曲的歌曲信息存入数据库
void Music::insertSQL(const QString &name)
{
    QSqlQuery sql_query;
    QString insert_sql = "insert into MusicInfo values (?, ?, ?, ?, ?, ?, ?)";
    sql_query.prepare(insert_sql);
    sql_query.addBindValue(name);
    sql_query.addBindValue(url.toString());
    sql_query.addBindValue(author);
    sql_query.addBindValue(title);
    sql_query.addBindValue(duration);
    sql_query.addBindValue(albumTitle);
    sql_query.addBindValue(audioBitRate);
    sql_query.exec();
}

//排序
bool MusicCompare::operator()(const Music &A, const Music &B)
{
    switch (key) {
    case TITLE:
        return A.title<B.title;
    case AUTHOR:
        return A.author<B.author;
    case DURATION:
        return A.duration<B.duration;
    case EQUALITY:
        return A.getUrl()==B.getUrl();
    default:
        return A.getInfo()<B.getInfo();
    }
}
