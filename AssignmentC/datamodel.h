#ifndef DATAMODEL_H
#define DATAMODEL_H

#include <list>
#include <vector>
#include "collection.h"
#include "item.h"
#include "borrower.h"
#include "mainwindow.h"
#include "mainmenu.h"
#include "collectiongui.h"
#include "functiongui.h"
#include "mainoperation.h"
#include "chooseborr.h"
#include "chooseitem.h"

using namespace std;

class DataModel
{
public:
    DataModel();
    static int ItemLevel;

    static vector<Item> getItemList();
    static void setItemList(const vector<Item> &value);
    static void addItem(Item i);
    static void addBorrower(Borrower i);
    static vector<Borrower> getBorrList();
    static void setBorrList(const vector<Borrower> &value);
    static void addCollection (Collection i);
    static vector<Collection> getCollectionList();
    static void setCollectionList(const vector<Collection> &value);
    static Borrower* findBorrowerByID(int id);
    static Item* findItemByBarCode(int barcode);
    static Item* findItemById(int id);
    static Borrower* findBorrowerByItemID(int id);
    static Collection* findCollectionByItemID(int id);
    static int findNumberItemOfColl (int idColl);
    static int findBorrowedNumberOfItemOfColl(int idColl);
    static bool isOverDueBorrower (Borrower b);


    static void init();

    static MainWindow *getMainwindow();
    static void setMainwindow(MainWindow *value);

    static MainMenu *getMainmenu();
    static void setMainmenu(MainMenu *value);

    static FunctionGui *getFuncgui();
    static void setFuncgui(FunctionGui *value);

    static MainOperation *getMainopera();
    static void setMainopera(MainOperation *value);

    static collectionGUI *getCollectiongui();
    static void setCollectiongui(collectionGUI *value);

    static ChooseBorr *getChooseBorr();
    static void setChooseBorr(ChooseBorr *value);

    static ChooseItem *getChooseItem();
    static void setChooseItem(ChooseItem *value);


private:

    static vector<Collection> collectionList;
    static vector<Item> itemList;
    static vector<Borrower> borrList;
    static MainWindow* mainwindow;
    static MainMenu* mainmenu;
    static FunctionGui* funcgui;
    static MainOperation* mainopera;
    static collectionGUI* collectiongui;
    static ChooseBorr* chooseBorr;
    static ChooseItem* chooseItem;


};

#endif // DATAMODEL_H
