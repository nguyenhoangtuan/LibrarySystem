#ifndef MYIMAGEITEM_H
#define MYIMAGEITEM_H

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <string>
#include <QGraphicsSceneContextMenuEvent>


class MyImageItem : public QGraphicsItem
{
public:
    MyImageItem(int width, int height);
    MyImageItem(int width, int height, std::string img, int id);
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void setPostion(int x, int y);

protected:
    void advance(int phase);
private:
    int id;
    std::string img;
    int width;
    int height;
    qreal angle;
    qreal speed;
    qreal opa;
    bool checkFade;
    void DoCollision();
    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);
};

#endif // MYIMAGEITEM_H
