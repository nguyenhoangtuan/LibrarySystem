#include "datamodel.h"
#include <iostream>
#include <QDate>

DataModel::DataModel()
{
}


vector<Item> DataModel::getItemList()
{
    return itemList;
}

void DataModel::setItemList(const vector<Item> &value)
{
    itemList = value;
}

void DataModel::addItem(Item i)
{
    itemList.push_back(i);
}

void DataModel::addBorrower(Borrower i)
{
    borrList.push_back(i);
}
vector<Borrower> DataModel::getBorrList()
{
    return borrList;
}

void DataModel::setBorrList(const vector<Borrower> &value)
{
    borrList = value;
}

void DataModel::addCollection(Collection i)
{
    collectionList.push_back(i);
}
vector<Collection> DataModel::getCollectionList()
{
    return collectionList;
}

void DataModel::setCollectionList(const vector<Collection> &value)
{
    collectionList = value;
}

Borrower *DataModel::findBorrowerByID(int id)
{
    for(int i = 0; i <borrList.size(); i++) {
        if(id == ((Borrower)borrList[i]).getId()) {
            return &(borrList[i]);
        }
    }
    return NULL;
}

Item *DataModel::findItemByBarCode(int barcode)
{
    for(int i = 0; i <itemList.size(); i++) {
        if(barcode == ((Item)itemList[i]).getBarcode()) {
            return &(itemList[i]);
        }
    }
    return NULL;
}

Item *DataModel::findItemById(int id)
{
    for(int i = 0; i <itemList.size(); i++) {
        if(id == ((Item)itemList[i]).getId()) {
            return &(itemList[i]);
        }
    }
    return NULL;
}

Borrower *DataModel::findBorrowerByItemID(int id)
{
//    Item *it = findItemById(id);
    for(int i = 0; i <borrList.size(); i++) {
        vector<int>* itemvec = ((Borrower)borrList[i]).getIdItemVector();
        for (int j = 0; j < itemvec->size() ; j++) {
            std::cout << "itemvec at " << j << std::endl;
            std::cout << itemvec->at(j)<<std::endl;
            if(itemvec->at(j) == id) {

                return &(borrList[i]);
            }
        }
    }
    return NULL;
}

Collection *DataModel::findCollectionByItemID(int id)
{
    Item *i = findItemById(id);
    int code = i->getIdenCode();
    for(int i = 0; i <collectionList.size(); i++) {
        if(code == ((Collection)collectionList[i]).getId()) {
            return &(collectionList[i]);
        }
    }
    return NULL;
}

int DataModel::findNumberItemOfColl(int idColl)
{
//    Collection *c = findCollectionByItemID(idColl);
    int count= 0;
    for(int i = 0; i <itemList.size(); i++) {
        if(idColl == ((Item)itemList[i]).getIdenCode()) {
            count++;
        }
    }
    return count;
}

int DataModel::findBorrowedNumberOfItemOfColl(int idColl)
{
    int count = 0;
    for(int i = 0; i <itemList.size(); i++) {
        if(idColl == ((Item)itemList[i]).getIdenCode()) {
            if (((Item)itemList[i]).getBorrowStatus().compare("Borrowed")== 0) {
                count++;
            }
        }
    }
    return count;

}

bool DataModel::isOverDueBorrower(Borrower b)
{
    vector<int>* ite = b.getIdItemVector();
    for (int i =0 ; i< ite->size();i++) {
        Item *item = findItemById(ite->at(i));
        if (item->getDateBorr().compare("")== 0) {

        } else {

            QString q = QString::fromStdString(item->getDateBorr());
            QDate date1 = QDate::fromString(q , "d/M/yyyy");
            QDate date2 = QDate::currentDate();

            if (date1.daysTo(date2) > 7 ) {
               return true;
            }
        }
    }
    return false;
}

void DataModel::init()
{
    mainwindow = new MainWindow();
    mainmenu = new MainMenu();
    funcgui = new FunctionGui();
    mainopera = new MainOperation();
    collectiongui= new collectionGUI();
    chooseBorr = new ChooseBorr();
    chooseItem = new ChooseItem();
}

MainWindow *DataModel::getMainwindow()
{
    return mainwindow;
}

void DataModel::setMainwindow(MainWindow *value)
{
    mainwindow = value;
}
MainMenu *DataModel::getMainmenu()
{
    return mainmenu;
}

void DataModel::setMainmenu(MainMenu *value)
{
    mainmenu = value;
}
FunctionGui *DataModel::getFuncgui()
{
    return funcgui;
}

void DataModel::setFuncgui(FunctionGui *value)
{
    funcgui = value;
}
MainOperation *DataModel::getMainopera()
{
    return mainopera;
}

void DataModel::setMainopera(MainOperation *value)
{
    mainopera = value;
}
collectionGUI *DataModel::getCollectiongui()
{
    return collectiongui;
}

void DataModel::setCollectiongui(collectionGUI *value)
{
    collectiongui = value;
}
ChooseBorr *DataModel::getChooseBorr()
{
    return chooseBorr;
}

void DataModel::setChooseBorr(ChooseBorr *value)
{
    chooseBorr = value;
}
ChooseItem *DataModel::getChooseItem()
{
    return chooseItem;
}

void DataModel::setChooseItem(ChooseItem *value)
{
    chooseItem = value;
}







int DataModel::ItemLevel;


vector<Collection> DataModel::collectionList;
vector<Item> DataModel::itemList;
vector<Borrower> DataModel::borrList;

MainWindow* DataModel::mainwindow;
MainMenu* DataModel::mainmenu;
FunctionGui* DataModel::funcgui;
MainOperation* DataModel::mainopera;
collectionGUI* DataModel::collectiongui;
ChooseBorr* DataModel::chooseBorr;
ChooseItem* DataModel::chooseItem;





