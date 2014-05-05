#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "collectiongui.h"
#include "collection.h"
#include "borrower.h"
#include "myitem.h"
#include <iostream>
#include <QPushButton>
#include <QColorDialog>
#include <QApplication>
#include <QLabel>
#include <QGraphicsEffect>
#include <QLineEdit>
#include "dataconnect.h"
#include <QComboBox>
#include <QDateEdit>
#include "mofunction.h"
#include "datamodel.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    sence = new QGraphicsScene(this);
    ui->graphicsView->setScene(sence);
    sence->setSceneRect(-200,-200,300,300);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);

    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget");
    wid->hide();
    QWidget* wid1 = ui->centralWidget->findChild<QWidget*>("widget_borrow");
    wid1->hide();
    QWidget* wid2 = ui->centralWidget->findChild<QWidget*>("widget_collection");
    wid2->hide();
//    int a = 1;
//    MoFunction::graphicsEffect(a);


//    this->setWindowFlags( Qt::CustomizeWindowHint );
//    QPen mypen = QPen(Qt::red);

//    QLineF TopLine(sence->sceneRect().topLeft(),sence->sceneRect().topRight());
//    QLineF LeftLine(sence->sceneRect().topLeft(),sence->sceneRect().bottomLeft());
//    QLineF RightLine(sence->sceneRect().topRight(),sence->sceneRect().bottomRight());
//    QLineF BottomLine(sence->sceneRect().bottomLeft(),sence->sceneRect().bottomRight());


//    sence->addLine(TopLine,mypen);
//    sence->addLine(LeftLine,mypen);
//    sence->addLine(RightLine,mypen);
//    sence->addLine(BottomLine,mypen);

    int ItemCount = 6;
    for(int i = 0;i <ItemCount;i++) {
        MyItem *item = new MyItem();
        sence->addItem(item);
    }


    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), sence,SLOT(advance()));
    timer->start(20);


//    QMovie *movie = new QMovie(":/img/fallingSakura.gif");
//    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
//    ui->label->setGraphicsEffect(opacityEffect);
//    ui->label_2->setGraphicsEffect(opacityEffect);
//    opacityEffect->setOpacity(0.6);
//    ui->label->setMovie(movie);
////    movie->start();
////    opacityEffect->setOpacity(0.3);
//    ui->label_2->setMovie(movie);
//    movie->start();


//    opacityEffect->setOpacity(0.7);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_collectionButton_clicked()
{

    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_collection");
    wid->show();
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;

    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);


    int x = wid->pos().rx();
    int y = wid->pos().ry();
    QRect rec(x,y,wid->width() ,wid->height());
    QRect recend(x,y + 100,wid->width() ,wid->height());

    QPropertyAnimation *anim2 = new QPropertyAnimation(wid, "geometry");
    anim2->setDuration(2500);
    anim2->setStartValue(recend);
    anim2->setEndValue(rec);
    anim2->setEasingCurve(QEasingCurve::OutQuad);
    anim2->start(QAbstractAnimation::DeleteWhenStopped);

}

void MainWindow::on_itemButton_clicked()
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget");
    wid->show();
    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);

    int x = wid->pos().rx();
    int y = wid->pos().ry();
    QRect rec(x,y,wid->width() ,wid->height());
    QRect recend(x + 100,y,wid->width() ,wid->height());

    QPropertyAnimation *anim2 = new QPropertyAnimation(wid, "geometry");
    anim2->setDuration(2500);
    anim2->setStartValue(recend);
    anim2->setEndValue(rec);
    anim2->setEasingCurve(QEasingCurve::OutQuad);
    anim2->start(QAbstractAnimation::DeleteWhenStopped);

//    QLineEdit* line1 = wid->findChild<QLineEdit*>("lineEdit");
//    QLineEdit* line2 = wid->findChild<QLineEdit*>("lineEdit_2");
//    QComboBox* combo3 = wid->findChild<QComboBox*>("comboBox3");
//    QLineEdit* line4 = wid->findChild<QLineEdit*>("lineEdit_4");
//    QDateEdit* dateEdit = wid->findChild<QDateEdit*>("dateEdit");
//    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_6");

//    QPropertyAnimation *anim3 = new QPropertyAnimation(line1, "geometry");
//    x = line1->pos().rx();
//    y = line1->pos().ry();
//    QRect rec1(x,y,line1->width() ,line1->height());
//    QRect recend1(x + 300,y,line1->width() ,line1->height());
//    anim3->setDuration(3000);
//    anim3->setStartValue(recend1);
//    anim3->setEndValue(rec1);
//    anim3->setEasingCurve(QEasingCurve::OutQuad);
//    anim3->start(QAbstractAnimation::DeleteWhenStopped);

//    anim3 = new QPropertyAnimation(line2, "geometry");
//    x = line2->pos().rx();
//    y = line2->pos().ry();
//    QRect rec2(x,y,line2->width() ,line2->height());
//    QRect recend2(x + 300,y,line2->width() ,line2->height());
//    anim3->setDuration(3000);
//    anim3->setStartValue(recend2);
//    anim3->setEndValue(rec2);
//    anim3->setEasingCurve(QEasingCurve::OutQuad);
//    anim3->start(QAbstractAnimation::DeleteWhenStopped);

}


void MainWindow::on_submitItem_clicked()
{
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget");

    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), SLOT(endAnimation(1);));

    QLineEdit* line1 = wid->findChild<QLineEdit*>("lineEdit");
    QLineEdit* line2 = wid->findChild<QLineEdit*>("lineEdit_2");
    QComboBox* combo3 = wid->findChild<QComboBox*>("comboBox3");
    QLineEdit* line4 = wid->findChild<QLineEdit*>("lineEdit_4");
    QDateEdit* dateEdit = wid->findChild<QDateEdit*>("dateEdit");
    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_6");


    int idenCode = (line1->text()).toInt();
    int barCode = (line2->text()).toInt();
    std::string borrowStatus = (combo3->currentText()).toStdString();
    int borrTime = (line4->text()).toInt();
    std::string dateBorr = (dateEdit->text()).toStdString();
    int dayBorr = (line6->text()).toInt();
    Item *a = new Item(idenCode, barCode, borrowStatus, borrTime, dateBorr, dayBorr);

//    DataConnect data;

//    data.itemInsert(*a);
    DataModel::addItem(*a);
}

void MainWindow::endAnimation(int i)
{
    if (i == 1) {
        QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget");
        wid->hide();
    } else if (i == 2) {
        QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_borrow");
        wid->hide();
    } else if (i == 3) {
        QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_collection");
        wid->hide();
    }

}

void MainWindow::on_BorrowerButton_clicked()
{
    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_borrow");
    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;
    wid->show();
    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(0.0);
    anim->setEndValue(1.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);


    int x = wid->pos().rx();
    int y = wid->pos().ry();
    QRect rec(x,y,wid->width() ,wid->height());
    QRect recend(x - 100,y,wid->width() ,wid->height());

    QPropertyAnimation *anim2 = new QPropertyAnimation(wid, "geometry");
    anim2->setDuration(2500);
    anim2->setStartValue(recend);
    anim2->setEndValue(rec);
    anim2->setEasingCurve(QEasingCurve::OutQuad);
    anim2->start(QAbstractAnimation::DeleteWhenStopped);


}

void MainWindow::on_AddBorrower_clicked()
{

    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_borrow");

    QLineEdit* line1 = wid->findChild<QLineEdit*>("lineEdit_10");
    QLineEdit* line2 = wid->findChild<QLineEdit*>("lineEdit_11");
    QComboBox* combo3 = wid->findChild<QComboBox*>("comboBox");
    QLineEdit* line4 = wid->findChild<QLineEdit*>("lineEdit_12");
    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_13");
    QLineEdit* line7 = wid->findChild<QLineEdit*>("lineEdit_14");


    string name = line1->text().toStdString();
    string type = line2->text().toStdString();
    string department = combo3->currentText().toStdString();
    string mobileNumber = line4->text().toStdString();
    int itemBorr = (line6->text()).toInt();;
    int itemLate = (line7->text()).toInt();;

    Borrower *b = new Borrower(name, type, department, mobileNumber,itemBorr,itemLate);


//    DataConnect data;
//    data.borrowInsert(*b);

    DataModel::addBorrower(*b);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;


    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), SLOT(endAnimation(2);));

}

void MainWindow::on_Add_Collection_clicked()
{
    QWidget* wid = ui->centralWidget->findChild<QWidget*>("widget_collection");
    QComboBox* combo1 = wid->findChild<QComboBox*>("comboBox_2");
    QComboBox* combo2 = wid->findChild<QComboBox*>("comboBox_3");
    QLineEdit* line1 = wid->findChild<QLineEdit*>("lineEdit_20");
    QLineEdit* line2 = wid->findChild<QLineEdit*>("lineEdit_21");

    QLineEdit* line4 = wid->findChild<QLineEdit*>("lineEdit_22");
    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_23");
    QLineEdit* line7 = wid->findChild<QLineEdit*>("lineEdit_24");
    QLineEdit* line8 = wid->findChild<QLineEdit*>("lineEdit_25");
    QComboBox* combo3 = wid->findChild<QComboBox*>("comboBox_4");


    string type = combo1->currentText().toStdString();
    string dataType = combo2->currentText().toStdString();
    string title = line1->text().toStdString();
    string version = line2->text().toStdString();
    int idenCode = (line4->text()).toInt();
    string publisher = line6->text().toStdString();
    int yearRecored = (line7->text()).toInt();
    int duration = (line8->text()).toInt();
    string category = combo3->currentText().toStdString();

    Collection *c = new Collection(type, dataType, title, version,/*idenCode,*/publisher ,
                                  yearRecored,duration,category );


//    DataConnect data;
//    data.collectionInsert(*c);

    DataModel::addCollection(*c);


    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;


    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), SLOT(endAnimation(3);));

}




void MainWindow::on_pushButton_22_clicked()
{
        this->hide();
        collectionGUI *c = new collectionGUI();
        c->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    DataConnect data;
    data.saveData();
}
