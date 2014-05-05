#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDialog>
#include <QtGui>
#include <QtCore>
#include <QGraphicsScene>
#include <QPen>


#include <QtDebug>
#include <QFileInfo>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_collectionButton_clicked();

    void on_itemButton_clicked();

    void on_submitItem_clicked();
    void endAnimation(int i);
    void on_BorrowerButton_clicked();

    void on_AddBorrower_clicked();

    void on_Add_Collection_clicked();

    void on_pushButton_22_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *sence;
    QTimer *timer;
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H
