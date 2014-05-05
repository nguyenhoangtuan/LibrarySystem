#include "myitem.h"

MyItem::MyItem()
{

    setFlag(ItemIsMovable);
    //random start rotation
    angle = (qrand() %360);
    setRotation(angle);


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
    opa = 0.7;
}

QRectF MyItem::boundingRect() const
{

    return QRect(0,0,20, 20);
}

void MyItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QRectF rec = boundingRect();
//    QBrush Brush(Qt::green);
////    QPixmap pixmap(":/new/prefix1/lyn.png");

//    // basic Collion dectecion

//    if(scene()->collidingItems(this).isEmpty()) {
//        // no collision
//        Brush.setColor(Qt::green);
//    } else {
//        //  collision
//        Brush.setColor(Qt::red);

//        //set the positon
//        DoCollision();

//    }

//    painter->fillRect(rec,Brush);

//    painter->drawRect(rec);
    QImage myImage;
    myImage.load(":/img/sakura.png");
    opa += 0.02;
    if (opa >= 1) {
       checkFade = true;
    }
    if (opa <= 0.3) {
        checkFade = false;
    }
    if (checkFade == true) {
        opa -= 0.03;
    } else if (checkFade == false) {
        opa -= 0.01;
    }

    painter->setOpacity(opa);
    painter->drawImage(rec,myImage);


}

void MyItem::advance(int phase)
{
    if(!phase) return;

    QPointF location = this->pos();
    angle += 2;
    if (angle >= 360) {
        angle = 0;
    }
    setRotation(angle);
//    qreal opa += 0.05;
//    setOpacity(1);

    setPos(mapToParent(0,  (speed)));


}

void MyItem::DoCollision()
{

    if((qrand() %1)) {
        setRotation(rotation() + (180 + (qrand()% 10)));

    } else {
        setRotation(rotation() + (180 + (qrand()% -10)));

    }
}
