#ifndef ITEM_H
#define ITEM_H

#include <string>

using namespace std;


class Item
{
public:
    Item();
    Item(int idenCode,int barcode,string borrowStatus,int borrTime,string dateBorr,int dayBorr);

    Item(int id ,int idenCode,int barcode,string borrowStatus,int borrTime,string dateBorr,int dayBorr);

    int getBarcode() const;
    void setBarcode(int value);

    string getBorrowStatus() const;
    void setBorrowStatus(const string &value);

    int getBorrTime() const;
    void setBorrTime(int value);

    string getDateBorr() const;
    void setDateBorr(const string &value);

    int getDayBorr() const;
    void setDayBorr(int value);

    int getIdenCode() const;
    void setIdenCode(int value);

    int getId() const;
    void setId(int value);

private:
    int id;
    int idenCode;
    int barcode;
    string borrowStatus;
    int borrTime;
    string dateBorr;
    int dayBorr;

    static int currentID;

};

#endif // ITEM_H


// Barcode (must be unique)
// Borrowing status (in storeroom, in library, borrowed, lost, etc.)
// Number of times borrowed
// The date it was borrowed
// The number of days it is borrowed this time
