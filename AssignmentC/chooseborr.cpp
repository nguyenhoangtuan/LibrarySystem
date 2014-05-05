#include "chooseborr.h"
#include "ui_chooseborr.h"
#include "borrower.h"
#include <vector>
#include "datamodel.h"
#include <iostream>
#include "mainoperation.h"


ChooseBorr::ChooseBorr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChooseBorr)
{
    ui->setupUi(this);
    ui->tableWidget->setColumnCount(8);
    QStringList b_TableHeader ;
    b_TableHeader<<"Select"<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late";
    ui->tableWidget->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 60);
    vector<Borrower> borrVec = DataModel::getBorrList();
    for (int i = 0; i < borrVec.size() ; i++) {
        setDataBorrTable(i, borrVec[i]);
    }
}

ChooseBorr::~ChooseBorr()
{
    delete ui;
}

void ChooseBorr::handleButtonAddItem(int i)
{
    DataModel::getMainopera()->setIDforBorrower(i);
    this->hide();
}

void ChooseBorr::setDataBorrTable(int row, Borrower a)
{
    QPushButton *q = new QPushButton("Select");

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());
    ui->tableWidget->setCellWidget(row, 0, q);
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::fromStdString(a.getName())));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::fromStdString(a.getType())));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getDepartment())));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::fromStdString(a.getMobileNumber())));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::number(a.getItemBorr())));
    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(a.getItemLate())));

    QSignalMapper *map = new QSignalMapper(this);
    connect (map, SIGNAL(mapped(int)), this, SLOT(handleButtonAddItem(int)));
    connect(q, SIGNAL(clicked()), map, SLOT(map()));

    map->setMapping(q, a.getId());

}

void ChooseBorr::initTable()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    QStringList b_TableHeader ;
    b_TableHeader<<"Select"<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late";
    ui->tableWidget->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 60);
    vector<Borrower> borrVec = DataModel::getBorrList();
    for (int i = 0; i < borrVec.size() ; i++) {
        setDataBorrTable(i, borrVec[i]);
    }

}

void ChooseBorr::on_pushButton_clicked()
{
    ui->tableWidget->clear();
    ui->tableWidget->setColumnCount(8);
    ui->tableWidget->setRowCount(0);
    QStringList b_TableHeader ;
    b_TableHeader<<"Select"<<"ID"<<"Name"<<"Type"<<"Department"<< "Mobile Number" << "Item Borr" << "Item Late";
    ui->tableWidget->setHorizontalHeaderLabels(b_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setColumnWidth(0 , 60);

    QString find = ui->lineEdit->text();
    QString cat = ui->comboBox->currentText();
//    std::cout<< cat.toStdString() << std::endl;


    vector<Borrower> itemVec = DataModel::getBorrList();
    vector<Borrower>* filter = new vector<Borrower>();
    if (cat.compare(QString("ID")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Borrower)itemVec[i]).getId()).contains(find)  ){
                filter->push_back( (Borrower)itemVec[i] );
            }
        }
    } /*else if (cat.compare(QString("Status") , Qt::CaseInsensitive) == 0) {
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
    }*/

    for (int i = 0; i < filter->size() ; i++) {
        setDataBorrTable(i, filter->at(i));
//        Collection *c = DataModel::findCollectionByItemID( (filter->at(i).getId()));
//        setDataCollTable(i, *c);
    }

}

