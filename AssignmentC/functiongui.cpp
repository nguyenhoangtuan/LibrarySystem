#include "functiongui.h"
#include "ui_functiongui.h"
#include <QPropertyAnimation>

FunctionGui::FunctionGui(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FunctionGui)
{
    ui->setupUi(this);
    currentTab = 2;
}

FunctionGui::~FunctionGui()
{
    delete ui;
}

void FunctionGui::changeLayout(QWidget *wid , int a, double devine, int d ,int e)
{

    int x = wid->pos().rx();
    int y = wid->pos().ry();
    QRect rec(x,y,wid->width() ,wid->height());
    QRect recend(x - a , y , d , e);
    QPropertyAnimation *anim2 = new QPropertyAnimation(wid, "geometry");
    anim2->setDuration(1500);
    anim2->setStartValue(rec);
    anim2->setEndValue(recend);
    anim2->setEasingCurve(QEasingCurve::OutQuad);
    anim2->start(QAbstractAnimation::DeleteWhenStopped);

}

void FunctionGui::on_pushButton_14_clicked() // >>
{
    if (currentTab == 2) {
        QWidget *wid1 = ui->widget_3;
        changeLayout(wid1, 81, 1,81 , 61);
        QWidget *wid = ui->widget;
        changeLayout(wid , +81, 2 ,81 , 61);
        QWidget *wid2 = ui->widget_4;
        changeLayout(wid2, 271, 1,271 , 181);
        currentTab =3;
    } else if (currentTab == 1) {
        QWidget *wid1 = ui->widget_3;
        changeLayout(wid1, 81, 1,81 , 61);
        QWidget *wid = ui->widget;
        changeLayout(wid , +271, 2 ,271 , 181);
        QWidget *wid2 = ui->widget_4;
        changeLayout(wid2, 81, 1,81 , 61);
        currentTab =2;
    } else if (currentTab == 3) {

    }


}

void FunctionGui::on_pushButton_13_clicked() // <<
{
    if (currentTab == 2) {
        QWidget *wid1 = ui->widget_3;
        changeLayout(wid1, -81, 1,271 , 181);
        QWidget *wid = ui->widget;
        changeLayout(wid , -271, 0.8,81 , 61);
        QWidget *wid2 = ui->widget_4;
        changeLayout(wid2 , -81, 1,81 , 61);
        currentTab =1;
    } else if (currentTab == 1) {
//        QWidget *wid1 = ui->widget_3;
//        changeLayout(wid1, -271, 1,81 , 61);
//        QWidget *wid = ui->widget;
//        changeLayout(wid , -271, 0.8,81 , 61);
//        QWidget *wid2 = ui->widget_4;
//        changeLayout(wid2 , -271, 1,271 , 181);
    } else if (currentTab == 3) {
        QWidget *wid1 = ui->widget_3;
        changeLayout(wid1, -81, 1,81 , 61);
        QWidget *wid = ui->widget;
        changeLayout(wid , -81, 0.8,271 , 181);
        QWidget *wid2 = ui->widget_4;
        changeLayout(wid2 , -271, 1,81 , 61);
        currentTab =2;
    }

}

void FunctionGui::mouseMoveEvent(QMouseEvent* event) {
//    qDebug() << QString::number(event->pos().x());
//    qDebug() << QString::number(event->pos().y());
}
// 271 , 181
// 81 , 61
