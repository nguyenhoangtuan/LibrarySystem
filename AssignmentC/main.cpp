#include "mainwindow.h"
#include "collectiongui.h"
#include "dataconnect.h"
#include "functiongui.h"
#include "item.h"
#include <QApplication>
#include "model.h"
#include "mainoperation.h"
#include "datamodel.h"
#include "mainmenu.h"
#include <algorithm>

#include <list>
#include <iostream>

int main(int argc, char *argv[])
{
    DataConnect data;
    data.getDataFromDatabase();
    data.getBorrDataFromDatabaseNew();
    data.getCollDataFromDatabase();

    QApplication a(argc, argv);
    DataModel::init();

  MainMenu *m = DataModel::getMainmenu();
  m->show();

  //  MainWindow *m = DataModel::getMainwindow();
  //  m->show();

    return a.exec();
}
