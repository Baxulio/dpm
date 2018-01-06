#include "adduser.h"
#include "ui_adduser.h"

AddUser::AddUser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddUser)
{
    ui->setupUi(this);

    ui->role->addItems(QStringList()<<"Admin"<<"Salesman"<<"Storekeeper");
    ui->host->addItems(QStringList()<<"Access only from server"<<"Local network: 192.168.%"<<"Local network: 10.122.%"<<"Access from any place");
}

AddUser::~AddUser()
{
    delete ui;
}

QString AddUser::name() const
{
    return ui->name->text();
}

QString AddUser::role() const
{
    return ui->role->currentText();
}

QString AddUser::host() const
{
    int curInd=ui->host->currentIndex();

    if(curInd==0)return "localhost";
    if(curInd==1)return "192.168.%";
    if(curInd==2)return "10.122.%";
    if(curInd==3)return "%";

    return ui->host->currentText();
}

QString AddUser::password() const
{
    return ui->password->text();
}
