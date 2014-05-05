#ifndef COLLECTIONGUI_H
#define COLLECTIONGUI_H

#include <QDialog>
#include "item.h"
#include "borrower.h"
#include "collection.h"

namespace Ui {
class collectionGUI;
}

class collectionGUI : public QDialog
{
    Q_OBJECT

public:
    explicit collectionGUI(QWidget *parent = 0);
    ~collectionGUI();

    void resetTableItem();
private slots:
    void on_pushButton_clicked();
    void handleButtonAddItem(int id);
    void on_pushButton_3_clicked();
    void endAnimationBorr();
    void endAnimationColl();
    void on_AddBorrower_clicked();
    void on_pushButton_4_clicked();
    void on_Add_Collection_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_checkBox_toggled(bool checked);
    void on_comboBox_5_currentTextChanged(const QString &arg1);
    void on_comboBox_6_currentTextChanged(const QString &arg1);

    void on_print_push_clicked();

    void on_pdf_push_clicked();

private:
    Ui::collectionGUI *ui;


    void setDataItemTable(int row,Item a);
    void setDataBorrTable(int row, Borrower a);
    void setDataCollTable(int row, Collection a);

    void resetTableBorr();
    void resetTableColl();

    void closeEvent(QCloseEvent *event);

};

#endif // COLLECTIONGUI_H
