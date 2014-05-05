#ifndef MAINOPERATION_H
#define MAINOPERATION_H

#include <QDialog>
#include <QGraphicsScene>
#include <vector>
#include "item.h"
#include "collection.h"
#include <QFormLayout>


namespace Ui {
class MainOperation;
}

class MainOperation : public QDialog
{
    Q_OBJECT

public:
    explicit MainOperation(QWidget *parent = 0);
    ~MainOperation();
    void setIDforBorrower(int id);
    void setBarcodeForItem(int barcode);
    void setBarcodeForItemReturn(int barcode);
    void removeItem(int id);

private slots:
    void on_idButton_clicked();
    void on_barButton_clicked();
    void on_submitButton_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_itemBack_clicked();
    void on_pushButton_3_clicked();
    void handleButtonAddItem(int id);
    void on_findButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainOperation *ui;
    QGraphicsScene *sence;
    QTimer *timer;
    QFormLayout* form;
    std::vector<int> *listBorrower;
    std::vector<int> *listItem;

    void initTable();
    void setDataItemTable(int id, Item i);
    void setDataCollTable(int row, Collection i);
    void updateTable();
    void closeEvent(QCloseEvent *event);
    void clearAllLabel();

};

#endif // MAINOPERATION_H
