#ifndef DATACONNECT_H
#define DATACONNECT_H

#include "borrower.h"
#include "item.h"
#include "collection.h"

class DataConnect
{
public:
    DataConnect();
    void itemInsert(Item a);
    void itemDelete(Item a);
    void itemUpdate(Item a);
    void borrowInsert(Borrower b);
    void collectionInsert(Collection c);
    void getDataFromDatabase();
    void getBorrDataFromDatabase();
    void getCollDataFromDatabase();

    void getItemFromDatabaseNew();
    void getBorrDataFromDatabaseNew();
    void itemInsertNew(Item a);
    void collectionInsertNew(Collection c);
    void borrowInsertNew(Borrower b);

    void saveData();
};

#endif // DATACONNECT_H
