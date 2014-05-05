#ifndef FUNCTIONGUI_H
#define FUNCTIONGUI_H

#include <QDialog>
#include <QtWidgets>

namespace Ui {
class FunctionGui;
}

class FunctionGui : public QDialog
{
    Q_OBJECT

public:
    explicit FunctionGui(QWidget *parent = 0);
    ~FunctionGui();

private slots:
    void on_pushButton_14_clicked();

    void on_pushButton_13_clicked();

private:
    Ui::FunctionGui *ui;
    int currentTab;
    void changeLayout(QWidget *wid , int a, double devine, int d ,int e);
    void mouseMoveEvent(QMouseEvent* event);
};

#endif // FUNCTIONGUI_H
