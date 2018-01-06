#include "additemdialog.h"
#include "ui_additemdialog.h"
#include <QMessageBox>

addItemDialog::addItemDialog(QString activeDb,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItemDialog)
{
    ui->setupUi(this);
    ui->dateEdit->setDate(QDate::currentDate());

    QSqlTableModel *mod=new QSqlTableModel(this,QSqlDatabase::database(activeDb));
    mod->setTable("salesman_staffcode");
    mod->select();
    ui->salesman->setModel(mod);
    ui->salesman->setModelColumn(1);
    ui->salesman->setCurrentIndex(-1);

    mod=new QSqlTableModel(this,QSqlDatabase::database(activeDb));
    mod->setTable("customer");
    mod->select();
    ui->customer->setModel(mod);
    ui->customer->setModelColumn(1);
    ui->customer->setCurrentIndex(-1);

    mod=new QSqlTableModel(this,QSqlDatabase::database(activeDb));
    mod->setTable("dl_location");
    mod->select();
    ui->location->setModel(mod);
    ui->location->setModelColumn(1);
    ui->location->setCurrentIndex(-1);

    mod=new QSqlTableModel(this,QSqlDatabase::database(activeDb));
    mod->setTable("dl_category");
    mod->select();
    ui->category->setModel(mod);
    ui->category->setModelColumn(1);
    ui->category->setCurrentIndex(-1);


}

addItemDialog::~addItemDialog()
{
    delete ui;
}

int addItemDialog::salesman() const
{
    return ui->salesman->currentText().toInt();
}

int addItemDialog::customer() const
{
    return ui->customer->currentText().toInt();
}

int addItemDialog::location() const
{
    return ui->location->currentText().toInt();
}

int addItemDialog::category() const
{
    return ui->category->currentText().toInt();
}

QString addItemDialog::remark() const
{
    return ui->plainTextEdit->toPlainText();
}

QDate addItemDialog::requiredData() const
{
    return ui->dateEdit->date();
}

int addItemDialog::r1() const
{
    return ui->r1->text().toInt();
}

int addItemDialog::r2() const
{
    return ui->r2->text().toInt();
}

int addItemDialog::r3() const
{
    return ui->r3->text().toInt();
}

int addItemDialog::r4() const
{
    return ui->r4->text().toInt();
}

int addItemDialog::r5() const
{
    return ui->r5->text().toInt();
}

void addItemDialog::on_pushButton_clicked()
{
    if(ui->salesman->currentIndex()==-1)
    {
        ui->salesman->setFocus();
        QMessageBox::critical(this, "Incorrect input", "Not all boxes are filled, please take attentin!");
    }
    else if(ui->customer->currentIndex()==-1)
    {
        ui->customer->setFocus();
        QMessageBox::critical(this, "Incorrect input", "Not all boxes are filled, please take attentin!");
    }
    else if(ui->location->currentIndex()==-1)
    {
        ui->location->setFocus();
        QMessageBox::critical(this, "Incorrect input", "Not all boxes are filled, please take attentin!");
    }
    else if(ui->category->currentIndex()==-1)
    {
        ui->category->setFocus();
        QMessageBox::critical(this, "Incorrect input", "Not all boxes are filled, please take attentin!");
    }
    else if(ui->dateEdit->date()<QDate::currentDate())
    {
        ui->dateEdit->setFocus();
        QMessageBox::critical(this, "Required data", "Required data is already expired, please change it!");
    }
    else if(!ui->r1->value() && !ui->r2->value() && !ui->r3->value() && !ui->r4->value() && !ui->r5->value())
    {
        ui->r1->setFocus();
        QMessageBox::critical(this, "Incorrect input", "Not all boxes are filled, please take attentin!");
    }
    else
    {
        ui->salesman->setModelColumn(0);
        ui->customer->setModelColumn(0);
        ui->location->setModelColumn(0);
        ui->category->setModelColumn(0);

        accept();
    }
}
