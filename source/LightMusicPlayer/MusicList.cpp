#include "MusicList.h"
#include <QCoreApplication>
#include <QProgressDialog>
#include <QDesktopServices>
#include <QtSql>
#include <algorithm>
#include "MusicListWidget.h"

MusicList::MusicList(const QList<QUrl> &urls, QString iname)
{
    //构造方法
    addMusic(urls);
    setName(iname);
}

//用文件地址来添加歌曲
void MusicList::addMusic(const QList<QUrl> &urls)
{
    /* 用 foreach 遍历 QUrl链表数组中的全部元素。
     */
    foreach (QUrl i, urls) {
        //过滤Url（添加的文件的地址）的类型
        QMimeDatabase db;
        //用QMimeDatabase.mimeTypeForFile方法来获取文件类型。QMimeType是返回的数据的数据类型.
        QMimeType mime = db.mimeTypeForFile(i.toLocalFile());
        if(mime.name()!="audio/mpeg"&&mime.name()!="audio/flac"){
            //不是音乐文件的跳过
            continue;
        }
        //剩下的符合类型,强制类型转换为Music类数据，放进music动态数组里，再把music动态数组里的内容放进数据库内
        music.push_back(Music(i));
        if(sql_flag){
            music[music.size()-1].insertSQL(name);
        }
    }
}

/* addMusic 函数重载
 * 用于已添加的歌曲从一个歌单里添加到另一个歌单
 */
void MusicList::addMusic(const Music &iMusic)
{
    //同上30行
    music.push_back(iMusic);
    if(sql_flag){
        music[music.size()-1].insertSQL(name);
    }
}

Music MusicList::getMusic(int pos)
{
    //传入歌曲的下标，再把位于该下标的歌曲传出
    return music[pos];
}

//用于 把当前播放的歌曲添加到“当前播放”歌单里
//auto 自动声明变量类型
void MusicList::addToPlayList(QMediaPlaylist *playlist)
{
    for(auto i=music.begin();i!=music.end();i++){
        playlist->addMedia(i->getUrl());
    }
}

void MusicList::addToListWidget(MusicListWidget *listWidget)
{
    //遍历歌单里的歌曲
    foreach(const Music &i,music){
        QListWidgetItem *item = new QListWidgetItem;
        //给每个歌曲加个音乐图标
        item->setIcon(listWidget->getIcon());
        //添加歌曲的信息(作者 - 歌曲名 - 歌曲时长)
        item->setText(i.getInfo());
        //把加工完的item 添加到歌单页面
        listWidget->addItem(item);
    }
}

void MusicList::removeMusic(int pos)
{
    if(sql_flag){
        //移除数据库记录
        remove_SQL_all();
        int i=0;
        for(auto it=music.begin();it!=music.end();){
            if(i==pos){
                //找到对应下标的音乐数据，用erase(it)方法删掉，删完erase(it)方法返回it下一个元素的下标，it指向下一个元素
                it= music.erase(it);
                break;
            }
            else{
                //不是目标元素
                it++;
            }
            i++;
            
        }
        //把更改完成后的歌单信息插入到数据库
        insert_SQL_all();    
    }else{
        //sql_flag=0，不用进行数据库操作
        int i=0;
        for(auto it=music.begin();it!=music.end();){
            if(i==pos){
                it= music.erase(it);
                break;
            }
            else{
                it++;
            }
            i++;
            
        }
    }
    
}

void MusicList::showInExplorer(int pos)
{
    QString str=music[pos].getUrl().toString();//获取歌曲地址，把类型转成字符串
    str.remove(str.split("/").last());//切割字符串获得所在的文件夹路径
    QDesktopServices::openUrl(str);//调用QDesktopServices类函数打开文件夹
}

void MusicList::detail(int pos)
{
    music[pos].detail();//调用Music类函数，显示指定歌曲详细信息
}

void MusicList::remove_SQL_all()
{
    QSqlQuery sql_query;
    QString delete_sql = "delete from MusicInfo where name = ?";//用SQL查询语句，在数据库中删除对应歌单中全部歌曲
    sql_query.prepare(delete_sql);
    sql_query.addBindValue(name);
    sql_query.exec();
}

//将歌单中的歌曲全部写入数据库
void MusicList::insert_SQL_all()
{
    for(auto i=music.begin();i!=music.end();i++){
        i->insertSQL(name);
    }
}

void MusicList::read_fromSQL()
{
    QSqlQuery sql_query;
    QString select_sql = "select url, author, title, duration, albumTitle, audioBitRate from MusicInfo where name = ?";
    sql_query.prepare(select_sql);
    sql_query.addBindValue(name);
    if(sql_query.exec())
    {
        while(sql_query.next())
        {
            Music tempMusic;
            tempMusic.url=QUrl(sql_query.value(0).toString());
            tempMusic.author=sql_query.value(1).toString();
            tempMusic.title=sql_query.value(2).toString();
            tempMusic.duration=sql_query.value(3).toLongLong();
            tempMusic.albumTitle=sql_query.value(4).toString();
            tempMusic.audioBitRate=sql_query.value(5).toInt();
            music.push_back(tempMusic);
        }  
    }
}

void MusicList::sort_by(COMPARE key)
{
    sort(music.begin(),music.end(),MusicCompare(key));
    if(sql_flag){
        remove_SQL_all();
        insert_SQL_all();
    }
}

void MusicList::neaten()
{
    sort(music.begin(),music.end(),MusicCompare(DEFAULT));
    music.erase(unique(music.begin(),music.end(),MusicCompare(EQUALITY)), music.end());
    if(sql_flag){
        remove_SQL_all();
        insert_SQL_all();
    }
}

void MusicList::clear()
{
    music.clear();
    if(sql_flag){
        remove_SQL_all();    
    }
}
