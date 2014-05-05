#include <string>
#include "item.h"
#include <string>
#include "datamodel.h"
#include <iostream>

Item::Item()
{
}

Item::Item(int idenCode,int barcode,string borrowStatus,int borrTime,string dateBorr,int dayBorr):
    idenCode(idenCode), barcode(barcode), borrowStatus(borrowStatus), borrTime(borrTime),
    dateBorr(dateBorr), dayBorr(dayBorr)
{
    currentID = currentID + 1;
    id = currentID;
}

Item::Item(int id , int idenCode,int barcode,string borrowStatus,int borrTime,string dateBorr,int dayBorr):
    id(id), idenCode(idenCode), barcode(barcode), borrowStatus(borrowStatus), borrTime(borrTime),
    dateBorr(dateBorr), dayBorr(dayBorr)
{
    int max = 0;
    vector<Item> itemv = DataModel::getItemList();
    for(int i = 0; i < itemv.size(); i++) {
        if (max <= ((Item)itemv[i]).getId() ) {
            max = ((Item)itemv[i]).getId();
        }
    }
    if (max <= id) {
        max = id;
    }
    currentID = max;
    std::cout << "max = " << currentID << endl;
}


int Item::getBarcode() const
{
    return barcode;
}

void Item::setBarcode(int value)
{
    barcode = value;
}
string Item::getBorrowStatus() const
{
    return borrowStatus;
}

void Item::setBorrowStatus(const string &value)
{
    borrowStatus = value;
}
int Item::getBorrTime() const
{
    return borrTime;
}

void Item::setBorrTime(int value)
{
    borrTime = value;
}
string Item::getDateBorr() const
{
    return dateBorr;
}

void Item::setDateBorr(const string &value)
{
    dateBorr = value;
}
int Item::getDayBorr() const
{
    return dayBorr;
}

void Item::setDayBorr(int value)
{
    dayBorr = value;
}

int Item::getIdenCode() const
{
    return idenCode;
}

void Item::setIdenCode(int value)
{
    idenCode = value;
}
int Item::getId() const
{
    return id;
}

void Item::setId(int value)
{
    id = value;
}

int Item::currentID;


