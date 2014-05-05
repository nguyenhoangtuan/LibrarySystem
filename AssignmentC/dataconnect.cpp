#include <QtSql>
#include <QtDebug>
#include <QFileInfo>
#include "item.h"
#include "borrower.h"
#include "collection.h"
#include <iostream>
#include "datamodel.h"
#include "dataconnect.h"




DataConnect::DataConnect()
{
        QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
        mydb.setDatabaseName("data.db");
        if  (mydb.open()) {
            std::cout<<"Database is open\n";
        } else {
            std::cout<<"Database is not open\n";
        }
        QSqlQuery comman;
        QString exc = "create table if not exists collection ( id INTEGER NOT NULL , type VARCHAR(100), dataType VARCHAR(100),title VARCHAR(100),version VARCHAR(100),publisher VARCHAR(100), yearRecored int, duration int, category VARCHAR(100) );";
        if (comman.exec(exc)) {
            std::cout << "collection data run\n";
        } else {
            std::cout << "collection data not run\n";
        }
        exc = "create table if not exists items ( id INTEGER NOT NULL, idenCode int,barcode int,borrowStatus VARCHAR(100),borrTime int,dateBorr VARCHAR(100), dayBorr int );";

        if (comman.exec(exc)) {
            std::cout << "items data run\n";
        } else {
            std::cout << "item data not run\n";
        }

        exc = "create table if not exists borrowers ( id INTEGER NOT NULL,name VARCHAR(100),type VARCHAR(100),department VARCHAR(100),mobileNumber VARCHAR(100), itemBorr int, itemLate int , itemString VARCHAR(100));";

        if (comman.exec(exc)) {
            std::cout << "borrowers data run\n";
        } else {
            std::cout << "borrowers data not run\n";
        }
        mydb.close();
}

void DataConnect::getDataFromDatabase()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QSqlQuery comman;
    QString exc = "SELECT * FROM items;";
    comman.exec(exc);
    while (comman.next()) {
        int id = comman.record().value("id").toInt();
        int idenCode = comman.record().value("idenCode").toInt();
        int barcode = comman.record().value("barcode").toInt();
        string borrowStatus = comman.record().value("borrowStatus").toString().toStdString();
        int borrTime = comman.record().value("borrTime").toInt();
        string dateBorr = comman.record().value("dateBorr").toString().toStdString();
        int dayBorr = comman.record().value("dayBorr").toInt();

        Item i(id, idenCode, barcode, borrowStatus, borrTime, dateBorr, dayBorr);
        DataModel::addItem(i);
    }

    mydb.close();
}

void DataConnect::getBorrDataFromDatabase()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QSqlQuery comman;
    QString exc = "SELECT * FROM borrowers;";
    comman.exec(exc);
    while (comman.next()) {
        int id = comman.record().value("id").toInt();
        string name = comman.record().value("name").toString().toStdString();
        string type = comman.record().value("type").toString().toStdString();
        string department = comman.record().value("department").toString().toStdString();
        string mobileNumber = comman.record().value("mobileNumber").toString().toStdString();

        int itemBorr = comman.record().value("itemBorr").toInt();

        int itemLate = comman.record().value("itemLate").toInt();

        Borrower i( id, name,
                    type,
                    department,
                    mobileNumber,
                    itemBorr,
                    itemLate);
        DataModel::addBorrower(i);
    }

    mydb.close();
}

void DataConnect::getCollDataFromDatabase()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QSqlQuery comman;
    QString exc = "SELECT * FROM collection;";
    comman.exec(exc);
    while (comman.next()) {

        int id = comman.record().value("id").toInt();
        string type = comman.record().value("type").toString().toStdString();
        string dataType = comman.record().value("dataType").toString().toStdString();
        string title = comman.record().value("title").toString().toStdString();
        string version = comman.record().value("version").toString().toStdString();
        string publisher = comman.record().value("publisher").toString().toStdString();
        int yearRecored = comman.record().value("yearRecored").toInt();
        int duration = comman.record().value("duration").toInt();
        string category = comman.record().value("category").toString().toStdString();


        Collection i(id,
                    type,
                        dataType,
                        title,
                        version,
                        publisher,
                        yearRecored,
                        duration,
                        category);
        DataModel::addCollection(i);
    }

    mydb.close();
}



void DataConnect::itemInsert(Item a)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    int idenCode = a.getIdenCode();
    int barCode = a.getBarcode();
    QString borrowStatus = QString::fromStdString(a.getBorrowStatus());
    int borrTime = a.getBorrTime();
    QString dateBorr = QString::fromStdString(a.getDateBorr());
    int dayBorr = a.getDayBorr();

    QSqlQuery comman;
    QString exc = QString("INSERT INTO items (idenCode , barcode, borrowStatus,")
            +QString("borrTime, dateBorr, dayBorr) VALUES ")
            +QString("(")+ QString::number(idenCode) +QString(",")+ QString::number(barCode)+QString(",'")+borrowStatus
            +QString("',")+ QString::number(borrTime)+QString(",'")+dateBorr+QString("',")+ QString::number(dayBorr) +QString(");");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success!\n";
    } else {
        std::cout << "insert failure!\n";
    }

    mydb.close();
}

void DataConnect::itemDelete(Item a)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    int id = a.getId();
    id = 1;
    QSqlQuery comman;
    QString exc = QString("DELETE FROM items WHERE id= ")+ QString::number(id) +QString(";");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"delete success!\n";
    } else {
        std::cout << "delete failure!\n";
    }

    mydb.close();
}

void DataConnect::itemUpdate(Item a)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    int id = a.getId();
    int idenCode = a.getIdenCode();
    int barCode = a.getBarcode();
    QString borrowStatus = QString::fromStdString(a.getBorrowStatus());
    int borrTime = a.getBorrTime();
    QString dateBorr = QString::fromStdString(a.getDateBorr());
    int dayBorr = a.getDayBorr();
//    UPDATE table_name
//    SET column1=value1,column2=value2,...
//    WHERE some_column=some_value;
    QSqlQuery comman;
    QString exc = QString("UPDATE items SET idenCode = ") + QString::number(idenCode)+
            QString(", barcode = ") + QString::number(barCode) +
            QString(", borrowStatus = '") + borrowStatus +
            QString("', borrTime = ") + QString::number(borrTime) +
            QString(",dateBorr = '")+dateBorr +
            QString("', dayBorr = ") + QString::number(dayBorr) +
            QString(" WHERE id =") + QString::number(id) +QString(";");


    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"update success!\n";
    } else {
        std::cout << "update failure!\n";
    }

    mydb.close();
}

void DataConnect::borrowInsert(Borrower b)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QString name = QString::fromStdString(b.getName());
    QString type = QString::fromStdString(b.getType());
    QString department = QString::fromStdString(b.getDepartment());
    QString mobile = QString::fromStdString(b.getMobileNumber());
    int itemBorr = b.getItemBorr();
    int itemLate = b.getItemLate();

    QSqlQuery comman;
    QString exc = QString("INSERT INTO borrowers (name , type, department,")
            +QString("mobileNumber, itemBorr, itemLate) VALUES ")
            +QString("('")+ name +QString("','")+type+QString("','")+department
            +QString("','")+ mobile +QString("',")+ QString::number(itemBorr) +QString(",")+  QString::number(itemLate) +QString(");");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success!\n";
    } else {
        std::cout << "insert failure!\n";
    }

    mydb.close();
}

void DataConnect::collectionInsert(Collection c)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QString type = QString::fromStdString(c.getType());
    QString dataType = QString::fromStdString(c.getDataType());
    QString title = QString::fromStdString(c.getTitle());
    QString version = QString::fromStdString(c.getVersion());
//    int idenCode = c.getIdenCode();
    QString publisher = QString::fromStdString(c.getPublisher());
    std::cout << c.getPublisher()<< endl;
    int yearRecored = c.getYearRecored();
    int duration = c.getDuration();
    QString category = QString::fromStdString(c.getCategory());

    QSqlQuery comman;
    QString exc = QString("INSERT INTO collection (type , dataType, title,")
            +QString("version, publisher,yearRecored,duration,category ) VALUES ")
            +QString("('")+ type +QString("','")+dataType+QString("','")+title
            +QString("','")+ version +QString("'")/*+ QString::number(idenCode)*/ +QString(",'")
            +publisher +QString("',")+QString::number(yearRecored)+QString(",")+QString::number(duration)
            +QString(",'") +category+ QString("');");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success!\n";
    } else {
        std::cout << "insert failure!\n";
    }
    mydb.close();
}

void DataConnect::getItemFromDatabaseNew()
{

}

void DataConnect::getBorrDataFromDatabaseNew()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QSqlQuery comman;
    QString exc = "SELECT * FROM borrowers;";
    comman.exec(exc);
    while (comman.next()) {
        int id = comman.record().value("id").toInt();
        string name = comman.record().value("name").toString().toStdString();
        string type = comman.record().value("type").toString().toStdString();
        string department = comman.record().value("department").toString().toStdString();
        string mobileNumber = comman.record().value("mobileNumber").toString().toStdString();

        int itemBorr = comman.record().value("itemBorr").toInt();

        int itemLate = comman.record().value("itemLate").toInt();
        string itemString = comman.record().value("itemString").toString().toStdString();

        Borrower i( id, name,
                    type,
                    department,
                    mobileNumber,
                    itemBorr,
                    itemLate,
                    itemString);
        DataModel::addBorrower(i);
    }

    mydb.close();
}

void DataConnect::itemInsertNew(Item a)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    int idenCode = a.getIdenCode();
    int barCode = a.getBarcode();
    QString borrowStatus = QString::fromStdString(a.getBorrowStatus());
    int borrTime = a.getBorrTime();
    QString dateBorr = QString::fromStdString(a.getDateBorr());
    int dayBorr = a.getDayBorr();
    int id = a.getId();

    QSqlQuery comman;
    QString exc = QString("INSERT INTO items (idenCode , barcode, borrowStatus,")
            +QString("borrTime, dateBorr, dayBorr, id) VALUES ")
            +QString("(")+ QString::number(idenCode) +QString(",")+ QString::number(barCode)+QString(",'")+borrowStatus
            +QString("',")+ QString::number(borrTime)+QString(",'")+dateBorr+QString("',")+ QString::number(dayBorr) +QString(",")+QString::number(id) +QString(");");
//    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success item!\n";
    } else {
        std::cout << "insert failure item!\n";
    }

    mydb.close();
}

void DataConnect::collectionInsertNew(Collection c)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QString type = QString::fromStdString(c.getType());
    QString dataType = QString::fromStdString(c.getDataType());
    QString title = QString::fromStdString(c.getTitle());
    QString version = QString::fromStdString(c.getVersion());
//    int idenCode = c.getIdenCode();
    QString publisher = QString::fromStdString(c.getPublisher());
    std::cout << c.getPublisher()<< endl;
    int yearRecored = c.getYearRecored();
    int duration = c.getDuration();
    QString category = QString::fromStdString(c.getCategory());
    int id = c.getId();

    QSqlQuery comman;
    QString exc = QString("INSERT INTO collection (type , dataType, title,")
            +QString("version, publisher,yearRecored,duration,category ,id ) VALUES ")
            +QString("('")+ type +QString("','")+dataType+QString("','")+title
            +QString("','")+ version +QString("'")/*+ QString::number(idenCode)*/ +QString(",'")
            +publisher +QString("',")+QString::number(yearRecored)+QString(",")+QString::number(duration)
            +QString(",'") +category+ QString("',") +QString::number(id)+QString(");");
//    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success coll!\n";
    } else {
        std::cout << "insert failure coll!\n";
    }
    mydb.close();


}

void DataConnect::borrowInsertNew(Borrower b)
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }
    QString name = QString::fromStdString(b.getName());
    QString type = QString::fromStdString(b.getType());
    QString department = QString::fromStdString(b.getDepartment());
    QString mobile = QString::fromStdString(b.getMobileNumber());
    int itemBorr = b.getItemBorr();
    int itemLate = b.getItemLate();
    QString itemString = QString::fromStdString(b.getItemString());
    int id = b.getId();

    QSqlQuery comman;
    QString exc = QString("INSERT INTO borrowers (name , type, department,")
            +QString("mobileNumber, itemBorr, itemLate ,itemString, id) VALUES ")
            +QString("('")+ name +QString("','")+type+QString("','")+department
            +QString("','")+ mobile +QString("',")+ QString::number(itemBorr) +QString(",")
            +QString::number(itemLate)+QString(",'") +itemString+ QString("',")+ QString::number(id) +QString(");");
    std::cout << exc.toStdString()<< std::endl;
    if(comman.exec(exc)) {
        std::cout <<"insert success borr!\n";
    } else {
        std::cout << "insert failure borr!\n";
    }

    mydb.close();
}

void DataConnect::saveData()
{
    QSqlDatabase mydb = QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("data.db");
    if  (mydb.open()) {
        std::cout<<"Database is open\n";
    } else {
        std::cout<<"Database is not open\n";
    }

    QSqlQuery comman;
    QString exc = QString("DELETE FROM items;");
    if(comman.exec(exc)) {
        std::cout<< "delete success" << std::endl;
    } else {
        std::cout<< "delete failure" << std::endl;
    }
    exc = QString("DELETE FROM borrowers;");
    comman.exec(exc);
    exc = QString("DELETE FROM collection;");
    comman.exec(exc);

    mydb.close();

    vector<Item> itemli =  DataModel::getItemList();
    for (int i = 0; i < itemli.size();i++) {
        itemInsertNew(itemli[i]);
    }
    vector<Borrower> borrli =  DataModel::getBorrList();
    for (int i = 0; i < borrli.size();i++) {
        borrowInsertNew(borrli[i]);
    }
    vector<Collection> collli =  DataModel::getCollectionList();
    for (int i = 0; i < collli.size();i++) {
        collectionInsertNew(collli[i]);
    }
}





