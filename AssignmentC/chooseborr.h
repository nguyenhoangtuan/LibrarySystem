#ifndef CHOOSEBORR_H
#define CHOOSEBORR_H

#include <QDialog>
#include "borrower.h"

namespace Ui {
class ChooseBorr;
}

class ChooseBorr : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseBorr(QWidget *parent = 0);
    ~ChooseBorr();
    void initTable();

private slots:
    void handleButtonAddItem(int i);
    void on_pushButton_clicked();

private:
    Ui::ChooseBorr *ui;
    void setDataBorrTable(int i, Borrower b);

};

#endif // CHOOSEBORR_H
