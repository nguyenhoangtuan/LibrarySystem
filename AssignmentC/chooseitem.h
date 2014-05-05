#ifndef CHOOSEITEM_H
#define CHOOSEITEM_H

#include <QDialog>
#include "item.h"

namespace Ui {
class ChooseItem;
}

class ChooseItem : public QDialog
{
    Q_OBJECT

public:
    explicit ChooseItem(QWidget *parent = 0);
    ~ChooseItem();
    void initTable();

private slots:
    void handleButtonAddItem(int i);
    void handleButtonAddItemForReturn(int i);
    void on_pushButton_clicked();

private:
    Ui::ChooseItem *ui;
    void setDataItemTable(int i, Item a);
};

#endif // CHOOSEITEM_H
