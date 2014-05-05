#include "collectiongui.h"
#include "ui_collectiongui.h"
#include "mainwindow.h"
#include "datamodel.h"
#include "item.h"
#include <QStringList>
#include <iostream>
#include <list>
#include <iterator>
#include <vector>
#include <QInputDialog>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include <QComboBox>
#include "dataconnect.h"
#include <QDate>
#include <algorithm>
#include "pdf.h"

collectionGUI::collectionGUI(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::collectionGUI)
{
    ui->setupUi(this);
    ui->tableItem->setColumnCount(7);
    QStringList m_TableHeader ;
    m_TableHeader<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableItem->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableItem->setColumnWidth(0 , 30);
    vector<Item> itemVec = DataModel::getItemList();
    for (int i = 0; i < itemVec.size() ; i++) {
        setDataItemTable(i, itemVec[i]);
    }

    ui->tableBorrow->setColumnCount(8);
    QStringList b_TableHeader ;
    b_TableHeader<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late"<<"Current Item";
    ui->tableBorrow->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableBorrow->setColumnWidth(0 , 30);
    vector<Borrower> borrVec = DataModel::getBorrList();
    for (int i = 0; i < borrVec.size() ; i++) {
        setDataBorrTable(i, borrVec[i]);
    }

    ui->tableColl->setColumnCount(12);
    QStringList c_TableHeader ;
    c_TableHeader<<"ID"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category"<<"Number of Item"<< "Borrowed Item";
    ui->tableColl->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableColl->setColumnWidth(0 , 30);
    vector<Collection> collVec = DataModel::getCollectionList();
    for (int i = 0; i < collVec.size() ; i++) {
        setDataCollTable(i, collVec[i]);
    }

    ui->widget_borrow->hide();
    ui->widget_collection->hide();
}


void collectionGUI::setDataItemTable(int row ,Item a)
{
    ui->tableItem->insertRow(ui->tableItem->rowCount());
    ui->tableItem->setItem(row, 0, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableItem->setItem(row, 1, new QTableWidgetItem(QString::number(a.getIdenCode())));
    ui->tableItem->setItem(row, 2, new QTableWidgetItem(QString::number(a.getBarcode())));
    ui->tableItem->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.getBorrowStatus())));
    ui->tableItem->setItem(row, 4, new QTableWidgetItem(QString::number(a.getBorrTime())));
    ui->tableItem->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(a.getDateBorr())));
    ui->tableItem->setItem(row, 6, new QTableWidgetItem(QString::number(a.getDayBorr())));

}

void collectionGUI::setDataBorrTable(int row, Borrower a)
{
    ui->tableBorrow->insertRow(ui->tableBorrow->rowCount());
    ui->tableBorrow->setItem(row, 0, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableBorrow->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getName())));
    ui->tableBorrow->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getType())));
    ui->tableBorrow->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.getDepartment())));
    ui->tableBorrow->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getMobileNumber())));
    ui->tableBorrow->setItem(row, 5, new QTableWidgetItem(QString::number(a.getItemBorr())));
    ui->tableBorrow->setItem(row, 6, new QTableWidgetItem(QString::number(a.getItemLate())));
    ui->tableBorrow->setItem(row, 7, new QTableWidgetItem(QString::number(a.getIdItemVector()->size())));
}

void collectionGUI::setDataCollTable(int row, Collection a)
{
    ui->tableColl->insertRow(ui->tableColl->rowCount());
    ui->tableColl->setItem(row, 0, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableColl->setItem(row, 1, new QTableWidgetItem(QString::fromStdString(a.getType())));
    ui->tableColl->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getDataType())));
    ui->tableColl->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
    ui->tableColl->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getVersion())));
    ui->tableColl->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(a.getPublisher())));
    ui->tableColl->setItem(row, 6, new QTableWidgetItem(QString::number(a.getYearRecored())));
    ui->tableColl->setItem(row, 7, new QTableWidgetItem(QString::number(a.getDuration())));
    ui->tableColl->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(a.getCategory())));
    ui->tableColl->setItem(row, 9, new QTableWidgetItem(QString::number(DataModel::findNumberItemOfColl(a.getId()))));
    ui->tableColl->setItem(row, 10, new QTableWidgetItem(QString::number(DataModel::findBorrowedNumberOfItemOfColl(a.getId()))));
    QPushButton *createButton = new QPushButton("Add Copy");
//    connect(createButton, SIGNAL(pressed()),SLOT(endAnimation(1);));

    QSignalMapper *map = new QSignalMapper(this);
    connect (map, SIGNAL(mapped(int)), this, SLOT(handleButtonAddItem(int)));
    connect(createButton, SIGNAL(clicked()), map, SLOT(map()));

    map->setMapping(createButton, a.getId());


    ui->tableColl->setCellWidget(row, 11, createButton);

}

void collectionGUI::resetTableBorr()
{
    ui->tableBorrow->clear();
    ui->tableBorrow->setColumnCount(8);
    ui->tableBorrow->setRowCount(0);
    QStringList b_TableHeader ;
    b_TableHeader<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late"<<"Current Item";
    ui->tableBorrow->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableBorrow->setColumnWidth(0 , 30);
    vector<Borrower> borrVec = DataModel::getBorrList();
    for (int i = 0; i < borrVec.size() ; i++) {
        setDataBorrTable(i, borrVec[i]);
    }
}

void collectionGUI::resetTableColl()
{
    ui->tableColl->clear();
    ui->tableColl->setColumnCount(12);
    ui->tableColl->setRowCount(0);
    QStringList c_TableHeader ;
    c_TableHeader<<"ID"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category"<<"Number of Item"<< "Borrowed Item";
    ui->tableColl->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableColl->setColumnWidth(0 , 30);
    vector<Collection> collVec = DataModel::getCollectionList();
    for (int i = 0; i < collVec.size() ; i++) {
        setDataCollTable(i, collVec[i]);
    }
}

void collectionGUI::resetTableItem()
{
    ui->tableItem->clear();
    ui->tableItem->setColumnCount(7);
    ui->tableItem->setRowCount(0);
    QStringList m_TableHeader ;
    m_TableHeader<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableItem->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableItem->setColumnWidth(0 , 30);
    vector<Item> itemVec = DataModel::getItemList();
    for (int i = 0; i < itemVec.size() ; i++) {
        setDataItemTable(i, itemVec[i]);
    }

}

void collectionGUI::closeEvent(QCloseEvent *event)
{
    DataConnect data;
    data.saveData();
}

void collectionGUI::handleButtonAddItem(int id)
{
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Add Item To Collection :"));
    QLineEdit *lineBarCode = new QLineEdit(&dialog);
    QString barcode = QString("Bar Code : ");
    form.addRow(barcode, lineBarCode);
    QComboBox *combo = new QComboBox(&dialog);
    combo->addItem(QString("In Library"));
    combo->addItem(QString("In Store"));
    QString status = QString("Status : ");
    form.addRow(status , combo);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {

        vector<Item> cec = DataModel::getItemList();

        for (int i = 0; i < cec.size();i++) {
            if ( ((Item)cec.at(i)).getBarcode() == lineBarCode->text().toInt() ) {
                if (1 == 1) {
                    QMessageBox msgBox;
                    msgBox.setText("Duplicated barcode of Item.");
                    msgBox.exec();
                    return;
                }
            }
        }
        Item a(id, lineBarCode->text().toInt(),combo->currentText().toStdString(),0,"",0);
        DataModel::addItem(a);
        resetTableItem();
    }
}

collectionGUI::~collectionGUI()
{
    delete ui;
}



void collectionGUI::on_pushButton_clicked()
{
    this->hide();
    DataModel::getMainmenu()->show();
}

void collectionGUI::on_pushButton_3_clicked()
{
    QWidget* wid = ui->widget_borrow;
    ui->widget_collection->hide();
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

    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_13");
    QLineEdit* line7 = wid->findChild<QLineEdit*>("lineEdit_14");
    line6->setText("0");
    line7->setText("0");
}

void collectionGUI::endAnimationBorr()
{
        QWidget* wid = ui->widget_borrow;
        wid->hide();
        resetTableBorr();
}

void collectionGUI::endAnimationColl()
{
    QWidget* wid = ui->widget_collection;
    wid->hide();
    resetTableColl();
}

void collectionGUI::on_AddBorrower_clicked()
{
    QWidget* wid = ui->widget_borrow;
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

    DataModel::addBorrower(*b);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;

    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), SLOT(endAnimationBorr()));

}

void collectionGUI::on_pushButton_4_clicked()
{
    QWidget* wid = ui->widget_collection;
    wid->show();
    ui->widget_borrow->hide();
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

void collectionGUI::on_Add_Collection_clicked()
{
    QWidget* wid = ui->widget_collection;
    QComboBox* combo1 = wid->findChild<QComboBox*>("comboBox_2");
    QComboBox* combo2 = wid->findChild<QComboBox*>("comboBox_3");
    QLineEdit* line1 = wid->findChild<QLineEdit*>("lineEdit_20");
    QLineEdit* line2 = wid->findChild<QLineEdit*>("lineEdit_21");
    QLineEdit* line6 = wid->findChild<QLineEdit*>("lineEdit_23");
    QLineEdit* line7 = wid->findChild<QLineEdit*>("lineEdit_24");
    QLineEdit* line8 = wid->findChild<QLineEdit*>("lineEdit_25");
    QComboBox* combo3 = wid->findChild<QComboBox*>("comboBox_4");

    string type = combo1->currentText().toStdString();
    string dataType = combo2->currentText().toStdString();
    string title = line1->text().toStdString();
    string version = line2->text().toStdString();
    string publisher = line6->text().toStdString();
    int yearRecored = (line7->text()).toInt();
    int duration = (line8->text()).toInt();
    string category = combo3->currentText().toStdString();

    Collection *c = new Collection(type, dataType, title, version,/*idenCode,*/publisher ,
                                  yearRecored,duration,category );

    DataModel::addCollection(*c);

    QGraphicsOpacityEffect *opacityEffect = new QGraphicsOpacityEffect;

    wid->setGraphicsEffect(opacityEffect);
    QPropertyAnimation *anim = new QPropertyAnimation(opacityEffect, "opacity");
    anim->setDuration(2000);
    anim->setStartValue(1.0);
    anim->setEndValue(0.0);
    anim->setEasingCurve(QEasingCurve::OutQuad);
    anim->start(QAbstractAnimation::DeleteWhenStopped);
    connect(anim, SIGNAL(finished()), SLOT(endAnimationColl()));

}

void collectionGUI::on_pushButton_5_clicked()
{

    ui->tableColl->clear();
    ui->tableColl->setColumnCount(12);
    ui->tableColl->setRowCount(0);
    QStringList c_TableHeader ;
    c_TableHeader<<"ID"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category"<<"Number of Item"<< "Borrowed Item";
    ui->tableColl->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableColl->setColumnWidth(0 , 30);

    QString find = ui->lineCollFind->text();
    QString cat = ui->comboBoxColl->currentText();
    vector<Collection> itemVec = DataModel::getCollectionList();
    vector<Collection>* filter = new vector<Collection>();
    if (cat.compare(QString("Type")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString( ((Collection)itemVec[i]).getType()).contains(find)  ){
                filter->push_back( (Collection)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Data Type") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString(((Collection)itemVec[i]).getDataType()).contains(find)){
                filter->push_back( (Collection)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Category")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString( ((Collection)itemVec[i]).getCategory()).contains(find)  ){
                filter->push_back( (Collection)itemVec[i] );
            }
        }
    }

    for (int i = 0; i < filter->size() ; i++) {
        setDataCollTable(i ,filter->at(i));
    }
}

void collectionGUI::on_pushButton_6_clicked()
{
    ui->tableItem->clear();
    ui->tableItem->setColumnCount(7);
    ui->tableItem->setRowCount(0);
    QStringList m_TableHeader ;
    m_TableHeader<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableItem->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableItem->setColumnWidth(0 , 30);
//    vector<Item> itemVec = DataModel::getItemList();
//    for (int i = 0; i < itemVec.size() ; i++) {
//        setDataItemTable(i, itemVec[i]);
//    }
    QString find = ui->line_itemfind->text();
    QString cat = ui->comboBox_item->currentText();
    vector<Item> itemVec = DataModel::getItemList();
    vector<Item>* filter = new vector<Item>();
    if (cat.compare(QString("Status")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString( ((Item)itemVec[i]).getBorrowStatus()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("OverDue") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if ( ((Item)itemVec[i]).getDateBorr().compare("") == 0  ) {

            } else {
                QDate date1 = QDate::fromString(QString::fromStdString( ((Item)itemVec[i]).getDateBorr()) , "d/M/yyyy");
                QDate date2 = QDate::currentDate();

                if (date1.daysTo(date2) > 7 ) {
                   filter->push_back( (Item)itemVec[i] );
                }
            }
        }
    } else if (cat.compare(QString("Iden Code")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Item)itemVec[i]).getIdenCode()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    }

    for (int i = 0; i < filter->size() ; i++) {
        setDataItemTable(i ,filter->at(i));
    }
}

void collectionGUI::on_checkBox_toggled(bool checked)
{
        ui->tableBorrow->clear();
        ui->tableBorrow->setColumnCount(8);
        ui->tableBorrow->setRowCount(0);
        QStringList b_TableHeader ;
        b_TableHeader<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late"<<"Current Item";
        ui->tableBorrow->setHorizontalHeaderLabels(b_TableHeader);
        ui->tableBorrow->setColumnWidth(0 , 30);

        vector<Borrower> itemVec = DataModel::getBorrList();
        vector<Borrower>* filter = new vector<Borrower>();
        if (checked == true) {
            for (int i = 0; i < itemVec.size() ; i++) {
                if (DataModel::isOverDueBorrower(itemVec.at(i))) {
                    filter->push_back( (Borrower)itemVec[i] );
                }

            }
        } else {
            for (int i = 0; i < itemVec.size() ; i++) {

                    filter->push_back( (Borrower)itemVec[i] );


            }
        }

        for (int i = 0; i < filter->size() ; i++) {
            setDataBorrTable(i ,filter->at(i));
        }

}


void collectionGUI::on_comboBox_5_currentTextChanged(const QString &arg1)
{
    ui->tableColl->clear();
    ui->tableColl->setColumnCount(12);
    ui->tableColl->setRowCount(0);
    QStringList c_TableHeader ;
    c_TableHeader<<"ID"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category"<<"Number of Item"<< "Borrowed Item";
    ui->tableColl->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableColl->setColumnWidth(0 , 30);


    vector<Collection> itemVec = DataModel::getCollectionList();
//    vector<Collection>* filter = new vector<Collection>();

    if (arg1.compare(QString("Title"))== 0) {

        std::sort(itemVec.begin(), itemVec.end(), Collection::before);
    } else if (arg1.compare(QString("Number Of Item"))== 0) {
        std::sort(itemVec.begin(), itemVec.end(), Collection::after);
    }


    for (int i = 0; i < itemVec.size() ; i++) {
        setDataCollTable(i ,itemVec.at(i));
    }
}

void collectionGUI::on_comboBox_6_currentTextChanged(const QString &arg1)
{
    ui->tableBorrow->clear();
    ui->tableBorrow->setColumnCount(8);
    ui->tableBorrow->setRowCount(0);
    QStringList b_TableHeader ;
    b_TableHeader<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late"<<"Current Item";
    ui->tableBorrow->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableBorrow->setColumnWidth(0 , 30);

    vector<Borrower> itemVec = DataModel::getBorrList();
    if (arg1.compare(QString("Name"))== 0) {

        std::sort(itemVec.begin(), itemVec.end(), Borrower::before);
    } else if (arg1.compare(QString("Borrowed Item"))== 0) {
        std::sort(itemVec.begin(), itemVec.end(), Borrower::after);
    }




    for (int i = 0; i < itemVec.size() ; i++) {
        setDataBorrTable(i ,itemVec.at(i));
    }
}

void collectionGUI::on_print_push_clicked()
{

}

void collectionGUI::on_pdf_push_clicked()
{
    PDF *a;
    a->pdf_file();
}
