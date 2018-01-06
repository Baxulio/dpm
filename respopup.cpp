#include "respopup.h"
#include "ui_respopup.h"
#include <QGraphicsDropShadowEffect>

resPopUp::resPopUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::resPopUp)
{
    ui->setupUi(this);

    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

    int radius=15;
    int offset=0;

    QGraphicsDropShadowEffect *shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(offset);
    shadow->setBlurRadius(radius);
    shadow->setColor(QColor(Qt::lightGray));
    ui->frame->setGraphicsEffect(shadow);

    shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(offset);
    shadow->setBlurRadius(radius);
    shadow->setColor(QColor(Qt::lightGray));
    ui->accept->setGraphicsEffect(shadow);

    shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(offset);
    shadow->setBlurRadius(radius);
    shadow->setColor(QColor(Qt::lightGray));
    ui->revert->setGraphicsEffect(shadow);

    shadow=new QGraphicsDropShadowEffect(this);
    shadow->setOffset(offset);
    shadow->setBlurRadius(radius);
    shadow->setColor(QColor(Qt::lightGray));
    ui->plainTextEdit->setGraphicsEffect(shadow);
}

resPopUp::~resPopUp()
{
    delete ui;
}

void resPopUp::on_accept_clicked()
{
    accept();
}

void resPopUp::setIndex(QModelIndex index, int column)
{

    QString str=index.model()->index(index.row(),column).data().toString();
    if(str=="")
    {
        ui->recieved->setChecked(false);
        ui->recieved->setEnabled(true);
        ui->recieved->setText("SET\nRECIEVED");
    }
    else
    {
        ui->recieved->setChecked(true);
        ui->recieved->setEnabled(false);
        QStringList time=str.split("T");
        ui->recieved->setText(time.at(0)+"\n"+time.at(1));
    }

    //...

    str=index.model()->index(index.row(),column+1).data().toString();
    if(str=="")
    {
        ui->picked->setChecked(false);
        ui->picked->setEnabled(true);
        ui->picked->setText("SET\nPICKED");
    }
    else
    {
        ui->picked->setChecked(true);
        ui->picked->setEnabled(false);
        QStringList time=str.split("T");
        ui->picked->setText(time.at(0)+"\n"+time.at(1));
    }
    //...

    str=str=index.model()->index(index.row(),column+2).data().toString();
    if(str=="")
    {
        ui->ready->setChecked(false);
        ui->ready->setEnabled(true);
        ui->ready->setText("SET\nREADY");
    }
    else
    {
        ui->ready->setChecked(true);
        ui->ready->setEnabled(false);
        QStringList time=str.split("T");
        ui->ready->setText(time.at(0)+"\n"+time.at(1));
    }
    //...

    str=index.model()->index(index.row(),column+3).data().toString();
    if(str=="")
    {
        ui->delivered->setChecked(false);
        ui->delivered->setEnabled(true);
        ui->delivered->setText("SET\nDELIVERED");
    }
    else
    {
        ui->delivered->setChecked(true);
        ui->delivered->setEnabled(false);
        QStringList time=str.split("T");
        ui->delivered->setText(time.at(0)+"\n"+time.at(1));
    }

    ui->plainTextEdit->clear();
    ui->plainTextEdit->insertPlainText(index.model()->index(index.row(),column+4).data().toString());
}

bool resPopUp::recieved() const
{
    return ui->recieved->isEnabled();
}

bool resPopUp::picked() const
{
    return ui->picked->isEnabled();
}

bool resPopUp::ready() const
{
    return ui->ready->isEnabled();
}

bool resPopUp::delivered() const
{
    return ui->delivered->isEnabled();
}

bool resPopUp::recievedChecked() const
{
    return ui->recieved->isChecked();
}

bool resPopUp::pickedChecked() const
{
    return ui->picked->isChecked();
}

bool resPopUp::readyChecked() const
{
    return ui->ready->isChecked();
}

bool resPopUp::deliveredChecked() const
{
    return ui->delivered->isChecked();
}

QString resPopUp::remarks() const
{
    return ui->plainTextEdit->toPlainText();
}

void resPopUp::on_revert_clicked()
{
    reject();
}

void resPopUp::on_toolButton_clicked()
{
    if(!ui->plainTextEdit->maximumHeight())ui->plainTextEdit->setMaximumHeight(100);
    else ui->plainTextEdit->setMaximumHeight(0);
}
