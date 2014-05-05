#include "myimageitem.h"
#include <QAction>
#include <QMenu>
#include <QGraphicsSceneContextMenuEvent>
#include <iostream>
#include "datamodel.h"
MyImageItem::MyImageItem(int width, int height) : width(width), height(height)
{
//    setFlag(ItemIsMovable);
    //random start rotation
//    angle = (qrand() %360);
//    setRotation(angle);

    //st the speed
    speed = 1;
    //random start postion
//    int StartX = -100;
//    int StartY = -100;

//    if((qrand()%1)) {
//        StartX = (qrand()%200);
//        StartY = (qrand()%200);
//    } else {
//        StartX = (qrand()%-100);
//        StartY = (qrand()%-100);
//    }

//    setPos(mapToParent(StartX, StartY));
    opa = 1;
    img = ":/img/default-avatar.jpg";
}

MyImageItem::MyImageItem(int width, int height, std::string img ,int id ) : width(width), height(height) ,img(img), id(id)
{
//    setFlag(ItemIsMovable);
    //random start rotation
//    angle = (qrand() %360);
//    setRotation(angle);

    //st the speed
    speed = 1;
    //random start postion
    int StartX = 0;
    int StartY = 0;

    if((qrand()%1)) {
        StartX = (qrand()%200);
        StartY = (qrand()%200);
    } else {
        StartX = (qrand()%-100);
        StartY = (qrand()%-100);
    }

    setPos(mapToParent(StartX, StartY));
    opa = 1;
}

QRectF MyImageItem::boundingRect() const
{

    return QRect(0,0,width, height);
}

void MyImageItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
    QImage myImage;
    myImage.load(QString::fromStdString(img));
    painter->setOpacity(opa);
    painter->drawImage(rec,myImage);
}

void MyImageItem::setPostion(int x, int y)
{
    setPos(mapToParent(x, y));
}

void MyImageItem::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();
    angle += 2;
    if (angle >= 360) {
        angle = 0;
    }
    setRotation(angle);
    setPos(mapToParent(0,  (speed)));

}

void MyImageItem::DoCollision()
{
    if((qrand() %1)) {
        setRotation(rotation() + (180 + (qrand()% 10)));
    } else {
        setRotation(rotation() + (180 + (qrand()% -10)));
    }
}

void MyImageItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
//    QMenu *menu = new QMenu();
//    menu->addAction("Remove");
//    menu->addAction("Check Info");
////    menu->popup(event->screenPos());

//    QAction *a = menu->exec(event->screenPos());
////    qDebug("User clicked %s", qPrintable(a->text()));

//    std::cout <<"check button : "<< a->text().toStdString() << std::endl;

////    connect(menu, SIGNAL(triggered(QAction *)),
////                 this, SLOT(triggered(QAction *)));

 /*      std::auto_ptr<QMenu> menu(new QMenu());
       QAction *removeAction = menu->addAction("Remove");
//       QAction *markAction = menu->addAction("Mark");
       QAction *selectedAction = menu->exec(event->screenPos());
       if ( selectedAction != 0 ) {
//            std::cout <<"check button : " << id << std::endl;
            DataModel::getMainopera()->removeItem(id);
            delete this;
       }
       */
}
