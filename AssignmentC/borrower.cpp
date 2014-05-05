#include "borrower.h"
#include <iostream>
#include <QString>
#include <QStringList>
#include "datamodel.h"

Borrower::Borrower()
{
}

Borrower::Borrower(string name,
                   string type,
                   string department,
                   string mobileNumber,
                   int itemBorr,
                   int itemLate): name(name), type(type),
    department(department), mobileNumber(mobileNumber), itemBorr(itemBorr), itemLate(itemLate)
{
    idItemVector = new vector<int>();
    currentID = currentID + 1;
    id = currentID;
}

Borrower::Borrower(int id, string name, string type, string department, string mobileNumber, int itemBorr, int itemLate): id(id), name(name), type(type),
    department(department), mobileNumber(mobileNumber), itemBorr(itemBorr), itemLate(itemLate)
{
    idItemVector = new vector<int>();
}

Borrower::Borrower(int id, string name, string type, string department, string mobileNumber, int itemBorr, int itemLate, string itemString): id(id), name(name), type(type),
    department(department), mobileNumber(mobileNumber), itemBorr(itemBorr), itemLate(itemLate), itemString(itemString)
{
    idItemVector = new vector<int>();
    QString list = QString::fromStdString(itemString);
    if (list.compare(QString("")) != 0) {
        QStringList listItem = list.split("-");
        for (int i = 0; i < listItem.size(); i++) {
            std::cout << "chuan men : "<<listItem.at(i).toInt() << std::endl;
            idItemVector->push_back(listItem.at(i).toInt());
        }
    }

    showItemList();
    int max = 0;
    vector<Borrower> itemv = DataModel::getBorrList();
    for(int i = 0; i < itemv.size(); i++) {
        if (max <= ((Borrower)itemv[i]).getId() ) {
            max = ((Borrower)itemv[i]).getId();
        }
    }
    if (max <= id) {
        max = id;
    }
    currentID = max;

}



int Borrower::getId() const
{
    return id;
}

void Borrower::setId(int value)
{
    id = value;
}
string Borrower::getName() const
{
    return name;
}

void Borrower::setName(const string &value)
{
    name = value;
}
string Borrower::getType() const
{
    return type;
}

void Borrower::setType(const string &value)
{
    type = value;
}
string Borrower::getDepartment() const
{
    return department;
}

void Borrower::setDepartment(const string &value)
{
    department = value;
}
string Borrower::getMobileNumber() const
{
    return mobileNumber;
}

void Borrower::setMobileNumber(const string &value)
{
    mobileNumber = value;
}
int Borrower::getItemBorr() const
{
    return itemBorr;
}

void Borrower::setItemBorr(int value)
{
    itemBorr = value;
}
int Borrower::getItemLate() const
{
    return itemLate;
}

void Borrower::setItemLate(int value)
{
    itemLate = value;
}
vector<int> *Borrower::getIdItemVector() const
{
    return idItemVector;
}

void Borrower::setIdItemVector(vector<int> *value)
{
    idItemVector = value;
}
string Borrower::getItemString() const
{
//    idItemVector = new vector<int>();
//    QString list = QString::fromStdString(itemString);
//    QStringList listItem = list.split("-");
//    for (int i = 0; i < listItem.size(); i++) {
//        std::cout << "chuan men : "<<listItem.at(i).toInt() << std::endl;
//        idItemVector->push_back(listItem.at(i).toInt());
//    }
    QString all("");
    for (int i = 0; i < idItemVector->size();i++) {
        if (i == 0) {
            all = QString::number(idItemVector->at(i));
        } else {
            all = all + QString("-") +QString::number(idItemVector->at(i));
        }
    }
//    itemString = all.toStdString();
    std::cout << "check item String : "<< all.toStdString()<< std::endl;
    return all.toStdString();
}

void Borrower::setItemString(const string &value)
{
    itemString = value;
}

void Borrower::addItem(int id)
{
    idItemVector->push_back(id);
}

void Borrower::deleteItem(int id)
{
    for (int i = 0; i< idItemVector->size();i++) {
        if(idItemVector->at(i) == id) {
            idItemVector->erase(idItemVector->begin() + i);
        }
    }
}

void Borrower::showItemList()
{
    for (int i = 0; i< idItemVector->size();i++) {
       std::cout << "item : "<<idItemVector->at(i) << std::endl;
    }
}

bool Borrower::before(const Borrower &c1, const Borrower &c2)
{
    int o = c1.getName().compare(c2.getName());
    if (o <0) {
        return false;

    } else {
        return true;
    }
}

bool Borrower::after(const Borrower &c1, const Borrower &c2)
{
    return c1.getItemBorr() <c2.getItemBorr();
}

int Borrower::currentID;








