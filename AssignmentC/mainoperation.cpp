#include "mainoperation.h"
#include "ui_mainoperation.h"
#include "borrower.h"
#include "datamodel.h"
#include <iostream>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QLabel>
#include "myimageitem.h"
#include <QDateTime>
#include <QSignalMapper>
#include <QInputDialog>
#include <QComboBox>
#include "chooseborr.h"
#include "dataconnect.h"
#include <algorithm>


MainOperation::MainOperation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainOperation)
{
    ui->setupUi(this);
    sence = new QGraphicsScene(this);
    ui->graphicsView->setScene(sence);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
//    ui->graphicsView->set

//    listBorrower = new vector<int>();
    listItem = new vector<int>();
//    ui->widget->hide();
//    ui->widget_return->hide();

    ui->itemBack->setEnabled(false);
//    ui->widget_status->hide();
    ui->widget_status->setStyleSheet("#widget_status {background-image: url(:/img/bg23.jpg);}");
    ui->widget_return->setStyleSheet("#widget_return {background-image: url(:/img/bg30.jpg);}");
//    ui->MainOperation.
    initTable();

//    QPixmap qp = QPixmap(QString(":/img/chibi.png"));
    int w = ui->img_label->width();
    int h = ui->img_label->height();

    // set a scaled pixmap to a w x h window keeping its aspect ratio
//    ui->img_label->setPixmap(qp.scaled(w,h,Qt::KeepAspectRatio));
//    ui->img_label->setPixmap(QPixmap(QString(":/img/chibi.png")));
    listBorrower = new vector<int>();
    listItem = new vector<int>();
}

MainOperation::~MainOperation()
{
    delete ui;
}

void MainOperation::setIDforBorrower(int id)
{
    ui->BorrowerID->setText(QString::number(id));
}

void MainOperation::setBarcodeForItem(int barcode)
{
     ui->barcode->setText(QString::number(barcode));
}

void MainOperation::setBarcodeForItemReturn(int barcode)
{
    ui->itemReturnLine->setText(QString::number(barcode));
}

void MainOperation::removeItem(int id)
{
    listItem->erase(std::remove(listItem->begin(), listItem->end(), id), listItem->end());
//    listItem->erase();
}


void MainOperation::on_idButton_clicked()
{
    int id = ui->BorrowerID->text().toInt();
    Borrower *b = DataModel::findBorrowerByID(id);
    if (b == NULL) {
        QMessageBox msgBox;
        msgBox.setText("There is no Borrower with the above ID.");
        msgBox.exec();
        return;
    }
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Confrim Borrwer"));

    QString Sid = QString("ID : ");
    QLabel *Sid2 = new QLabel();
    Sid2->setText(QString::number(b->getId()));
    form.addRow(Sid, Sid2);

    QString SidenCode = QString("Name : ");
    QLabel *SidenCode2 = new QLabel();
    SidenCode2->setText(QString::fromStdString(b->getName()));
    form.addRow(SidenCode, SidenCode2);


    QString type = QString("Type : ");
    QLabel *type2 = new QLabel();
    type2->setText(QString::fromStdString(b->getType()));
    form.addRow(type, type2);

    QString department = QString("Department : ");
    QLabel *department2 = new QLabel();
    department2->setText(QString::fromStdString(b->getDepartment()));
    form.addRow(department, department2);

    QString mobileNumber = QString("Mobile Number : ");
    QLabel *mobileNumber2 = new QLabel();
    mobileNumber2->setText(QString::fromStdString(b->getMobileNumber()));
    form.addRow(mobileNumber, mobileNumber2);

    QString itemLate = QString("Item Late : ");
    QLabel *itemLate2 = new QLabel();
    itemLate2->setText(QString::number(b->getItemLate()));
    form.addRow(itemLate, itemLate2);

    QString itemBorr = QString("Item Borrowed : ");
    QLabel *itemBorr2 = new QLabel();
    itemBorr2->setText(QString::number(b->getItemBorr()));
    form.addRow(itemBorr, itemBorr2);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        MyImageItem *item = new MyImageItem(100 , 100);
        item->setPostion(0,0);
        sence->addItem(item);
        item->setToolTip(QString("ID : ") + QString::number(b->getId())
                         +QString("\nName :") + QString::fromStdString(b->getName()));
        listBorrower->clear();
        listBorrower->push_back(b->getId());
    }

}

void MainOperation::on_barButton_clicked()
{
    int id = ui->barcode->text().toInt();
    Item *b = DataModel::findItemByBarCode(id);

    if (b == NULL) {
        QMessageBox msgBox;
        msgBox.setText("There is no Borrower with the above Barcode.");
        msgBox.exec();
        return;
    }

    for (int i = 0; i < listItem->size();i++) {
        if ( listItem->at(i) == b->getId()) {
            QMessageBox msgBox;
            msgBox.setText("The item is already choosen.");
            msgBox.exec();
            return;
        }
    }

    if (b->getBorrowStatus().compare("Borrowed") == 0 || b->getBorrowStatus().compare("Lost") == 0) {
        QMessageBox msgBox;
        msgBox.setText("The item is not availabe.");
        msgBox.exec();
        return;
    }
    QDialog dialog(this);
    QFormLayout form(&dialog);
    form.addRow(new QLabel("Confrim Item"));

    QString Sid = QString("ID : ");
    QLabel *Sid2 = new QLabel();
    Sid2->setText(QString::number(b->getId()));
    form.addRow(Sid, Sid2);

    QString idenCode = QString("Iden Code : ");
    QLabel *idenCode2 = new QLabel();
    idenCode2->setText(QString::number(b->getIdenCode()));
    form.addRow(idenCode, idenCode2);


    QString barcode = QString("BarCode : ");
    QLabel *barcode2 = new QLabel();
    barcode2->setText(QString::number(b->getBarcode()));
    form.addRow(barcode, barcode2);

    QString borrowStatus = QString("Borrow Status : ");
    QLabel *borrowStatus2 = new QLabel();
    borrowStatus2->setText(QString::fromStdString(b->getBorrowStatus()));
    form.addRow(borrowStatus, borrowStatus2);

    QString borrTime = QString("Borrowed Time : ");
    QLabel *borrTime2 = new QLabel();
    borrTime2->setText(QString::number(b->getBorrTime()));
    form.addRow(borrTime, borrTime2);

    QString dateBorr = QString("Date Borrowed : ");
    QLabel *dateBorr2 = new QLabel();
    dateBorr2->setText(QString::fromStdString(b->getDateBorr()));
    form.addRow(dateBorr, dateBorr2);

    QString dayBorr = QString("Number of Day Borrowed : ");
    QLabel *dayBorr2 = new QLabel();
    dayBorr2->setText(QString::number(b->getDayBorr()));
    form.addRow(dayBorr, dayBorr2);

    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    form.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        listItem->push_back(b->getId());
        MyImageItem *item = new MyImageItem(80 , 80, ":/img/blank_book.png" , b->getId());
        item->setPostion(200,0);
        sence->addItem(item);
        item->setToolTip(QString("ID : ") + QString::number(b->getId())
                         /*+QString("\nName :") + QString::fromStdString(b->getName())*/);
    }
}

void MainOperation::on_submitButton_clicked()
{
    if (listItem->size() == 0 || listBorrower->size() == 0) {
        if (1 == 1) {
            QMessageBox msgBox;
            msgBox.setText("THe list item is empty or the list borrower is empty.");
            msgBox.exec();
            return;
        }
        return;
    }

    for(int i = 0; i <listItem->size(); i++) {

       Item *itm =DataModel::findItemById(listItem->at(i));
       itm->setBorrowStatus("Borrowed");
       QString date = QString::number(QDateTime::currentDateTime().date().day())
               + QString("/")
               + QString::number(QDateTime::currentDateTime().date().month())
               + QString("/")
               + QString::number(QDateTime::currentDateTime().date().year());
       itm->setDateBorr(date.toStdString());
    }

    for(int i = 0; i <listBorrower->size(); i++) {
       Borrower *itm =DataModel::findBorrowerByID(listBorrower->at(i));
       itm->setItemBorr(itm->getItemBorr() + 1);
//       vector<int> *idItemVec = itm->getIdItemVector();
       std::cout << itm->getName() << std::endl;
       for(int j = 0; j<listItem->size(); j++) {
            itm->addItem(listItem->at(j));
       }
    }


    listItem->clear();
    listBorrower->clear();
    sence->clear();
    updateTable();
    DataModel::getCollectiongui()->resetTableItem();
    if (1 == 1) {
        QMessageBox msgBox;
        msgBox.setText("Item is borrowed successfully!!.");
        msgBox.exec();
        return;
    }


}

void MainOperation::on_pushButton_clicked()
{
//    ui->widget_status->hide();
//    ui->widget->show();
//    ui->widget_return->hide();
}


void MainOperation::on_pushButton_2_clicked()
{
//    ui->widget->hide();
//    ui->widget_return->show();
//    ui->widget_status->hide();
}

void MainOperation::on_pushButton_3_clicked()
{/*
    ui->widget_status->show();
    ui->widget->hide();
    ui->widget_return->hide();*/
}

void MainOperation::handleButtonAddItem(int id)
{
//    std::cout << "check id " << id<<std::endl;

    QStringList items;
    items << tr("In Library") << tr("In Store") << tr("Borrowed") << tr("Lost");

    bool ok;
    QString item = QInputDialog::getItem(this, tr("QInputDialog::getItem()"),
                                         tr("Status:"), items, 0, false, &ok);
    if (ok && !item.isEmpty()) {
        DataModel::findItemById(id)->setBorrowStatus(item.toStdString());
        updateTable();
    }
}

void MainOperation::initTable()
{
//    ui->tableWidget->setColumnCount(7);
//    ui->tableWidget->setRowCount(0);
//    QStringList m_TableHeader ;
//    m_TableHeader<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow";
//    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
//    ui->tableWidget->setColumnWidth(0 , 30);
    vector<Item> itemVec = DataModel::getItemList();
//    for (int i = 0; i < itemVec.size() ; i++) {
//        setDataItemTable(i, itemVec[i]);
//    }

    ui->tableWidget->setColumnCount(16);
    ui->tableWidget->setRowCount(0);
    QStringList c_TableHeader ;
    c_TableHeader<<"Command"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category";
    ui->tableWidget->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
//    vector<Collection> collVec = DataModel::getCollectionList();
    for (int i = 0; i < itemVec.size() ; i++) {
        setDataItemTable(i, itemVec[i]);
        Collection *c = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId());
        setDataCollTable(i, *c);
    }
}

void MainOperation::setDataItemTable(int row, Item a)
{
    QPushButton *createButton = new QPushButton("Update Status");

    QSignalMapper *map = new QSignalMapper(this);
    connect (map, SIGNAL(mapped(int)), this, SLOT(handleButtonAddItem(int)));
    connect(createButton, SIGNAL(clicked()), map, SLOT(map()));

    map->setMapping(createButton, a.getId());

    ui->tableWidget->insertRow(ui->tableWidget->rowCount());


    ui->tableWidget->setCellWidget(row, 0, createButton);
    ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(QString::number(a.getIdenCode())));
    ui->tableWidget->setItem(row, 3, new QTableWidgetItem(QString::number(a.getBarcode())));
    ui->tableWidget->setItem(row, 4, new QTableWidgetItem(QString::fromStdString(a.getBorrowStatus())));
    ui->tableWidget->setItem(row, 5, new QTableWidgetItem(QString::number(a.getBorrTime())));
    ui->tableWidget->setItem(row, 6, new QTableWidgetItem(QString::fromStdString(a.getDateBorr())));
    ui->tableWidget->setItem(row, 7, new QTableWidgetItem(QString::number(a.getDayBorr())));
}

void MainOperation::setDataCollTable(int row, Collection a)
{
//    ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QString::number(a.getId())));
    ui->tableWidget->setItem(row, 8, new QTableWidgetItem(QString::fromStdString(a.getType())));
    ui->tableWidget->setItem(row, 9, new QTableWidgetItem(QString::fromStdString(a.getDataType())));
    ui->tableWidget->setItem(row, 10, new QTableWidgetItem(QString::fromStdString(a.getTitle())));
    ui->tableWidget->setItem(row, 11, new QTableWidgetItem(QString::fromStdString(a.getVersion())));
    ui->tableWidget->setItem(row, 12, new QTableWidgetItem(QString::fromStdString(a.getPublisher())));
    ui->tableWidget->setItem(row, 13, new QTableWidgetItem(QString::number(a.getYearRecored())));
    ui->tableWidget->setItem(row, 14, new QTableWidgetItem(QString::number(a.getDuration())));
    ui->tableWidget->setItem(row, 15, new QTableWidgetItem(QString::fromStdString(a.getCategory())));
}

void MainOperation::updateTable()
{
    ui->tableWidget->clear();
    QStringList c_TableHeader;
    c_TableHeader<<"Command"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category";
    ui->tableWidget->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setRowCount(0);
    QString find = ui->fineLine->text();
    QString cat = ui->FindComboBox->currentText();


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
    } else if (cat.compare(QString("Barcode")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Item)itemVec[i]).getBarcode()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Type") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getType()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Data Type") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getDataType()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }

    } else if (cat.compare(QString("Title") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getTitle()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Version") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getVersion()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Category") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getCategory()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Publisher") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getPublisher()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    }

    for (int i = 0; i < filter->size() ; i++) {
        setDataItemTable(i, filter->at(i));
        Collection *c = DataModel::findCollectionByItemID( (filter->at(i).getId()));
        setDataCollTable(i, *c);
    }
}




void MainOperation::on_pushButton_4_clicked()
{

    int id = ui->itemReturnLine->text().toInt();
    Item *b = DataModel::findItemByBarCode(id);
//    std::cout << b->getName() << std::endl;
    if (b == NULL) {
        QMessageBox msgBox;
        msgBox.setText("There is no Item with the above Barcode.");
        msgBox.exec();
        return;
    }

    QDialog dialog(this);
//    QFormLayout *form = new
//    form =new QFormLayout(ui->widget_item);
//    form->findChildren<QWidget*>().clear();
//    QFormLayout form(ui->widget_item);
//    form.re
//    delete form;
    QString Sid = QString("ID : ");
//    QLabel *Sid2 = new QLabel();
//    Sid2->setText(QString::number(b->getId()));
//    form->addRow(Sid, Sid2);

    ui->labelID->setText(Sid + QString::number(b->getId()));


//    delete form;
    QString idenCode = QString("Iden Code : ");
//    QLabel *idenCode2 = new QLabel();
//    idenCode2->setText(QString::number(b->getIdenCode()));
//    form.addRow(idenCode, idenCode2);
    ui->label_2->setText(idenCode + QString::number(b->getIdenCode()));

    QString barcode = QString("BarCode : ");

//    QLabel *barcode2 = new QLabel();
//    barcode2->setText(QString::number(b->getBarcode()));
//    form.addRow(barcode, barcode2);
    ui->label_3->setText(barcode + QString::number(b->getBarcode()));

    QString borrowStatus = QString("Borrow Status : ");
//    QLabel *borrowStatus2 = new QLabel();
//    borrowStatus2->setText(QString::fromStdString(b->getBorrowStatus()));
//    form.addRow(borrowStatus, borrowStatus2);
    ui->label_4->setText(borrowStatus + QString::fromStdString(b->getBorrowStatus()));

    QString borrTime = QString("Borrowed Time : ");
//    QLabel *borrTime2 = new QLabel();
//    borrTime2->setText(QString::number(b->getBorrTime()));
//    form.addRow(borrTime, borrTime2);
    ui->label_5->setText(borrTime + QString::number(b->getBorrTime()));

    QString dateBorr = QString("Date Borrowed : ");
//    QLabel *dateBorr2 = new QLabel();
//    dateBorr2->setText(QString::fromStdString(b->getDateBorr()));
//    form.addRow(dateBorr, dateBorr2);
    ui->label_6->setText(dateBorr + QString::fromStdString(b->getDateBorr()));

    QString dayBorr = QString("Number of Day Borrowed : ");
//    QLabel *dayBorr2 = new QLabel();
//    dayBorr2->setText(QString::number(b->getDayBorr()));
//    form.addRow(dayBorr, dayBorr2);
    ui->label_7->setText(dayBorr + QString::number(b->getDayBorr()));


    Borrower *c = DataModel::findBorrowerByItemID(b->getId());

    if (c == NULL) {
        QMessageBox msgBox;
        msgBox.setText("There is no Borrower who borrowe the above Item.");
        msgBox.exec();
        return;
    }

//    QFormLayout form2(ui->widget_borr);

    QString sSid = QString("ID : ");
//    QLabel *sSid2 = new QLabel();
//    sSid2->setText(QString::number(c->getId()));
//    form2.addRow(sSid, sSid2);
    ui->label->setText(sSid + QString::number(c->getId()));

    QString SidenCode = QString("Name : ");
//    QLabel *SidenCode2 = new QLabel();
//    SidenCode2->setText(QString::fromStdString(c->getName()));
//    form2.addRow(SidenCode, SidenCode2);
ui->label_8->setText(SidenCode + QString::fromStdString(c->getName()));

    QString type = QString("Type : ");
//    QLabel *type2 = new QLabel();
//    type2->setText(QString::fromStdString(c->getType()));
//    form2.addRow(type, type2);
ui->label_9->setText(type + QString::fromStdString(c->getType()));
    QString department = QString("Department : ");
//    QLabel *department2 = new QLabel();
//    department2->setText(QString::fromStdString(c->getDepartment()));
//    form2.addRow(department, department2);
ui->label_10->setText(department + QString::fromStdString(c->getDepartment()));
    QString mobileNumber = QString("Mobile Number : ");
//    QLabel *mobileNumber2 = new QLabel();
//    mobileNumber2->setText(QString::fromStdString(c->getMobileNumber()));
//    form2.addRow(mobileNumber, mobileNumber2);
ui->label_11->setText(mobileNumber + QString::fromStdString(c->getMobileNumber()));
    QString itemLate = QString("Item Late : ");
//    QLabel *itemLate2 = new QLabel();
//    itemLate2->setText(QString::number(c->getItemLate()));
//    form2.addRow(itemLate, itemLate2);
ui->label_12->setText(itemLate + QString::number(c->getItemLate()));
    QString itemBorr = QString("Item Borrowed : ");
//    QLabel *itemBorr2 = new QLabel();
//    itemBorr2->setText(QString::number(c->getItemBorr()));
//    form2.addRow(itemBorr, itemBorr2);
ui->label_13->setText(itemBorr + QString::number(c->getItemBorr()));

    QFormLayout formtest(&dialog);
    QDialogButtonBox buttonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel,
                               Qt::Horizontal, &dialog);
    formtest.addRow(new QLabel("Item Found\nBorrower Found"));
    formtest.addRow(&buttonBox);
    QObject::connect(&buttonBox, SIGNAL(accepted()), &dialog, SLOT(accept()));
    QObject::connect(&buttonBox, SIGNAL(rejected()), &dialog, SLOT(reject()));

    if (dialog.exec() == QDialog::Accepted) {
        ui->itemBack->setEnabled(true);
    }

}

void MainOperation::on_itemBack_clicked()
{
    int id = ui->itemReturnLine->text().toInt();
    Item *b = DataModel::findItemByBarCode(id);
    Borrower *c = DataModel::findBorrowerByItemID(b->getId());
    c->deleteItem(b->getId());
    b->setBorrowStatus("In Library");

    QDate date1 = QDate::fromString(QString::fromStdString(b->getDateBorr()) , "d/M/yyyy");
    QDate date2 = QDate::currentDate();

    if (date1.daysTo(date2) > 7 ) {
        QMessageBox msgBox;
        msgBox.setText(QString("The item is returned late for ")
                       + QString::number(date1.daysTo(date2) - 7) + QString(" days"));
        msgBox.exec();

        c->setItemLate(c->getItemLate() + 1);
    }
    b->setDateBorr("");


    // calculate the item late
    // check day Borrwed this time
    if (1 == 1) {
        QMessageBox msgBox;
        msgBox.setText("Successful recieve the Item.");
        msgBox.exec();
        clearAllLabel();
        updateTable();
        return;
    }

//    c->showItemList();
}



void MainOperation::on_findButton_clicked()
{
    ui->tableWidget->clear();
    QStringList c_TableHeader;
    c_TableHeader<<"Command"<<"ID"<<"Iden Code"<<"Bar Code"<<"Borrow Status"<< "Borr Time" << "Date" << "Day Borrow"<<"Type"<<"Data Type"<<"Title"<< "Version" << "Publisher" << "Year Recorded"<<"Duration"<<"Category";
    ui->tableWidget->setHorizontalHeaderLabels(c_TableHeader);
    ui->tableWidget->setColumnWidth(1 , 30);
    ui->tableWidget->setRowCount(0);
    QString find = ui->fineLine->text();
    QString cat = ui->FindComboBox->currentText();
    std::cout<< cat.toStdString() << std::endl;


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
    } else if (cat.compare(QString("Barcode")) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            if( QString::number( ((Item)itemVec[i]).getBarcode()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Type") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getType()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Data Type") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getDataType()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }

    } else if (cat.compare(QString("Title") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getTitle()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Version") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getVersion()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Category") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getCategory()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    } else if (cat.compare(QString("Publisher") , Qt::CaseInsensitive) == 0) {
        for (int i = 0; i < itemVec.size() ; i++) {
            Collection *co = DataModel::findCollectionByItemID( ((Item)itemVec[i]).getId() );

            if( QString::fromStdString(co->getPublisher()).contains(find)  ){
                filter->push_back( (Item)itemVec[i] );
            }
        }
    }

    for (int i = 0; i < filter->size() ; i++) {
        setDataItemTable(i, filter->at(i));
        Collection *c = DataModel::findCollectionByItemID( (filter->at(i).getId()));
        setDataCollTable(i, *c);
    }

}

void MainOperation::closeEvent(QCloseEvent *event)
 {
//    std::cout << "exit" <<endl;
    DataConnect data;
    data.saveData();
}

void MainOperation::clearAllLabel()
{
    ui->label->clear();
    ui->labelID->clear();
    ui->label_2->clear();
    ui->label_3->clear();
    ui->label_4->clear();
    ui->label_5->clear();
    ui->label_6->clear();
    ui->label_7->clear();
    ui->label_8->clear();
    ui->label_9->clear();
    ui->label_10->clear();
    ui->label_11->clear();
    ui->label_12->clear();
    ui->label_13->clear();

}

void MainOperation::on_pushButton_5_clicked()
{
    DataModel::getChooseBorr()->show();
    DataModel::getChooseBorr()->initTable();

}

void MainOperation::on_pushButton_6_clicked()
{
    DataModel::getChooseItem()->show();
    DataModel::ItemLevel = 0;
    DataModel::getChooseItem()->initTable();
}

void MainOperation::on_pushButton_7_clicked()
{

    DataModel::getChooseItem()->show();
    DataModel::ItemLevel = 1;
    DataModel::getChooseItem()->initTable();

}

void MainOperation::on_pushButton_8_clicked()
{
    DataModel::getMainmenu()->show();
    this->hide();
}
