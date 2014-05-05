#include "chooseitem.h"
#include "ui_chooseitem.h"
#include "item.h"
#include "datamodel.h"
#include <iostream>

ChooseItem::ChooseItem(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseItem)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    QStringList m_TableHeader ;
    m_TableHeader<<"Select"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 70);
    vector<Item> itemVec = DataModel::getItemList();
    for (int i = 0; i < itemVec.size() ; i++) {
        setDataItemTable(i, itemVec[i]);
    }

}

void ChooseItem::setDataItemTable(int row ,Item a)
{
    QPushButton *q = new QPushButton("Select");

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setCellWidget(row, 0, q);
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(a.getIdenCode())));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(a.getBarcode())));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getBorrowStatus())));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(a.getBorrTime())));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(a.getDateBorr())));
    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(a.getDayBorr())));


    QSignalMapper *map = new QSignalMapper(this);
    if (DataModel::ItemLevel == 0) {
        connect (map, SIGNAL(mapped(int)), this, SLOT(handleButtonAddItem(int)));
    } else if (DataModel::ItemLevel == 1) {
        connect (map, SIGNAL(mapped(int)), this, SLOT(handleButtonAddItemForReturn(int)));
    }
    std::cout << "check : " << DataModel::ItemLevel << std::endl;
    connect(q, SIGNAL(clicked()), map, SLOT(map()));

    map->setMapping(q, a.getBarcode());
}

void ChooseItem::handleButtonAddItem(int i)
{
    DataModel::getMainopera()->setBarcodeForItem(i);
    this->hide();
}

void ChooseItem::handleButtonAddItemForReturn(int i)
{
    DataModel::getMainopera()->setBarcodeForItemReturn(i);
    this->hide();
}

ChooseItem::~ChooseItem()
{
    delete ui;
}

void ChooseItem::initTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    QStringList m_TableHeader ;
    m_TableHeader<<"Select"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 70);
    vector<Item> itemVec = DataModel::getItemList();
    for (int i = 0; i < itemVec.size() ; i++) {
        setDataItemTable(i, itemVec[i]);
    }

}

void ChooseItem::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    QStringList m_TableHeader ;
    m_TableHeader<<"Select"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 70);

    QString find = ui->lineEdit->text();
    QString cat = ui->comboBox->currentText();
//    std::cout<< cat.toStdString() << std::endl;


    vector<Item> itemVec = DataModel::getItemList();
    vector<Item>* filter = new vector<Item>();
    if (cat.compare(QString("ID")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Item)itemVec[i]).getId()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Status") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString(((Item)itemVec[i]).getBorrowStatus()).contains(find)){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("BarCode")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Item)itemVec[i]).getBarcode()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Date Borrow")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::fromStdString( ((Item)itemVec[i]).getDateBorr()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    }

    for (int i = 0; i < filter->size() ; i++) {
        setDataItemTable(i, filter->at(i));
//        Collection *c = DataModel::findCollectionByItemID( (filter->at(i).getId()));
//        setDataCollTable(i, *c);
    }

}
