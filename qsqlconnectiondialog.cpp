#include "qsqlconnectiondialog.h"
#include "ui_qsqlconnectiondialog.h"

qsqlconnectiondialog::qsqlconnectiondialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::qsqlconnectiondialog)
{
    ui->setupUi(this);

}

qsqlconnectiondialog::~qsqlconnectiondialog()
{
    delete ui;
}

QString qsqlconnectiondialog::driverName() const
{
    return "QMYSQL";
}

QString qsqlconnectiondialog::databaseName() const
{
    return "data";
}

QString qsqlconnectiondialog::userName() const
{
    return ui->user->text();
}

QString qsqlconnectiondialog::password() const
{
    return ui->password->text();
}

QString qsqlconnectiondialog::hostName() const
{
 return ui->host->text();
}

int qsqlconnectiondialog::port() const
{
    return ui->spinBox->value();
}

void qsqlconnectiondialog::on_pushButton_clicked()
{
//    if (ui->user->text().isEmpty()) {
//        QMessageBox::information(this, "Incorrect user field","The User field must be filled");
//        ui->user->setFocus();
//    }
//    else {
        accept();
//    }
}
