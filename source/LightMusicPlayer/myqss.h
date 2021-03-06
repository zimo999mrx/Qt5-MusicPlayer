#ifndef MYQSS_H
#define MYQSS_H
#include<QString>

/* QSS样式代码:
 * QSS代码作用类似于HTML里面的CSS。（stylesheet 样式表）
 * 使用QSS代码方便 播放/暂停键，播放模式键 的图标的切换。
 * 参考：https://blog.csdn.net/hht0506/article/details/104580407
 */

//播放按钮样式
inline QString PlayStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/play.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"
    
"    }"
    
    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/play-hover.png);"
    
   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/play.png);"
    
     "}";
}
//暂停按钮样式
inline QString PaseStyle()
{
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/pase.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/pase-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/pase.png);"

     "}";
}
inline QString RandomStyle()
{
    
    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/play-random.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/play-random-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/play-random.png);"

     "}";
    
}
inline QString LoopStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/loop.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/loop-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/loop.png);"

     "}";

}
inline QString LoopOneStyle()
{


    return "QPushButton"
   " {"
   "background-image:url(:/image/image/image/loop-one.png);"
 "   background-repeat:no-repeat;"
  "  background-position:center center;"
 "   border:none;"

"    }"

    "QPushButton:hover{"
  "  background-repeat:no-repeat;"
 "   background-position:center center;"
 "background-image:url(:/image/image/image-hover/loop-one-hover.png);"

   " }"
   " QPushButton:pressed{"
    "background-repeat:no-repeat;"
   " background-position:center center;"
   " background-image:url(:/image/image/image/loop-one.png);"

     "}";

}

inline QString ListWidgetStyle(){
    return "QScrollBar:vertical"
 "{"
         "width:8px;"
         "background-color:transparent;"
         "margin:0px,0px,0px,0px;"
        " padding-top:12px;   /*上预留位置*/"
        " padding-bottom:12px;    /*下预留位置*/"
     "}"
 
 
   "  QScrollBar::handle:vertical"
    " {"
         "width:8px;"
        " background-color:rgba(255,255,255,0.2);"
        " border-radius:4px;"
        " min-height:20px;"
    " }"
 
 
 "    QScrollBar::handle:vertical:hover"
  "   {"
   "      width:9px;"
        " background-color:rgba(255,255,255,0.5);"
      "   border-radius:4px;"
    "     min-height:20;"
   "  }"
 
   "  QScrollBar::add-line:vertical"
   "  {"
        " height:12px;"
    "     width:10px;"
 "        border-image:url(:/selectfile/scroll/3.png);"
        " subcontrol-position:bottom;"
 "    }"
 
 "    QScrollBar::sub-line:vertical"
 "    {"
 "        height:12px;"
         "width:10px;"
      "   border-image:url(:/selectfile/scroll/1.png);"
         "subcontrol-position:top;"
  "   }"
 "    QScrollBar::add-line:vertical:hover"
  "   {"
        " height:12px;"
         "width:10px;"
        " border-image:url(:/selectfile/scroll/4.png);"
         "subcontrol-position:bottom;"
    " }"
 
 
    " QScrollBar::sub-line:vertical:hover"
    " {"
    "     height:12px;"
       "  width:10px;"
       "  border-image:url(:/selectfile/scroll/2.png);"
        " subcontrol-position:top;"
    " }"
 
    " QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical"
    " {"
        " background-color:transparent;"
      "   border-radius:4px;"
     "}";
 
}

#endif // MYQSS_H
