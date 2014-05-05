#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "datamodel.h"
#include "dataconnect.h"
#include "collectiongui.h"

MainMenu::MainMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainMenu)
{
    ui->setupUi(this);
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::closeEvent(QCloseEvent *event)
{
    DataConnect data;
    data.saveData();
}

void MainMenu::on_pushButton_4_clicked()
{
    MainMenu *m = DataModel::getMainmenu();
    m->hide();

    collectionGUI *c = DataModel::getCollectiongui();
    c->show();
}


void MainMenu::on_pushButton_clicked()
{
    DataModel::getMainopera()->show();
    this->hide();
}
