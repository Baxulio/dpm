#include "edit.h"
#include "ui_edit.h"
#include <checkboxdelegate.h>
#include <QtSql>

edit::edit(QString active_db,QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edit),
    activeDb(active_db)
{
    ui->setupUi(this);

//    relTableModel = new tableModel(ui->table, QSqlDatabase::database(activeDb),"dpm");
//    relTableModel->setColumnsForResponse();
//    relTableModel->select();

//    proxyModel=new SortFilterProxyModel(ui->table);
//    proxyModel->setSourceModel(relTableModel);
//    ui->table->setModel(proxyModel);
//    ui->table->resizeColumnsToContents();
//    ui->table->setItemDelegateForColumn(1,new CheckBoxDelegate(ui->table));
//    ui->table->setColumnWidth(relTableModel->fieldIndex("remarks"),0);

//    sel =new QItemSelectionModel(proxyModel);
//    ui->table->setSelectionModel(sel);

//    mapper = new QDataWidgetMapper(this);
//    mapper->setModel(proxyModel);
//    mapper->addMapping(ui->customer,relTableModel->fieldIndex("CUSTOMER"));
//    mapper->addMapping(ui->category,9);                                             //Critical ...
//    mapper->addMapping(ui->required_data,10);                                       //Critical ...
//    mapper->addMapping(ui->remarks,relTableModel->fieldIndex("REMARKS"));
//    connect(sel,SIGNAL(currentChanged(QModelIndex,QModelIndex)),SLOT(rowChanged(QModelIndex,QModelIndex)));

}

edit::~edit()
{
    delete ui;
}

//void edit::rowChanged(QModelIndex curr, QModelIndex prev)
//{
//    Q_UNUSED(prev);
//    mapper->setCurrentModelIndex(curr);

//    QString str=relTableModel->index(curr.row(),relTableModel->fieldIndex("RECIEVED")).data(Qt::DisplayRole).toString();
//    if(str=="")
//    {
//        ui->recieved->setChecked(false);
//        ui->recieved->setEnabled(true);
//        ui->recieved_l->setText("<font color='grey'>NOT<br>"
//                                "RECIEVED<br>"
//                                "YET");
//    }
//    else
//    {
//        ui->recieved->setChecked(true);
//        ui->recieved->setEnabled(false);
//        QStringList time=str.split("T");
//        ui->recieved_l->setText(time.at(0)+"<br>"+time.at(1)+"<br>"+"<font color='green'>RECIEVED</font>");
//    }

//    //...

//    str=relTableModel->index(curr.row(),relTableModel->fieldIndex("PICKING")).data(Qt::DisplayRole).toString();
//    if(str=="")
//    {
//        ui->picked->setChecked(false);
//        ui->picked->setEnabled(true);
//        ui->picked_l->setText("<font color='grey'>NOT<br>"
//                              "PICKED<br>"
//                              "YET");
//    }
//    else
//    {
//        ui->picked->setChecked(true);
//        ui->picked->setEnabled(false);
//        QStringList time=str.split("T");
//        ui->picked_l->setText(time.at(0)+"<br>"+time.at(1)+"<br>"+"<font color='green'>PICKED</font>");
//    }
//    //...

//    str=relTableModel->index(curr.row(),relTableModel->fieldIndex("READY")).data(Qt::DisplayRole).toString();
//    if(str=="")
//    {
//        ui->ready->setChecked(false);
//        ui->ready->setEnabled(true);
//        ui->ready_l->setText("<font color='grey'>NOT<br>"
//                             "READY TO<br>"
//                             "DELIVERY");
//    }
//    else
//    {
//        ui->ready->setChecked(true);
//        ui->ready->setEnabled(false);
//        QStringList time=str.split("T");
//        ui->ready_l->setText(time.at(0)+"<br>"+time.at(1)+"<br>"+"<font color='green'>READY</font>");
//    }
//    //...

//    str=relTableModel->index(curr.row(),relTableModel->fieldIndex("DELIVERED")).data(Qt::DisplayRole).toString();
//    if(str=="")
//    {
//        ui->delivered->setChecked(false);
//        ui->delivered->setEnabled(true);
//        ui->delivered_l->setText("<font color='grey'>NOT<br>"
//                                 "DLIVERED<br>"
//                                 "YET");
//    }
//    else
//    {
//        ui->delivered->setChecked(true);
//        ui->delivered->setEnabled(false);
//        QStringList time=str.split("T");
//        ui->delivered_l->setText(time.at(0)+"<br>"+time.at(1)+"<br>"+"<font color='green'>RECIEVED</font>");
//    }
//}

//void edit::on_filterEdit_textChanged(const QString &arg1)
//{
//    proxyModel->setFilterRegExp(arg1);
//}

//void edit::on_dateTimeEdit_dateChanged(const QDate &date)
//{
//    proxyModel->setFilterMinimumDate(date);
//}

//void edit::on_dateTimeEdit_2_dateChanged(const QDate &date)
//{
//    proxyModel->setFilterMaximumDate(date);
//}

//void edit::on_recieved_2_clicked()
//{
//    relTableModel->setRecieved(ui->recieved_2->isChecked());
//}

//void edit::on_picking_clicked()
//{
//    relTableModel->setPicking(ui->picking->isChecked());
//}

//void edit::on_ready_to_delivery_clicked()
//{
//    relTableModel->setPicking(ui->ready_to_delivery->isChecked());
//}

//void edit::on_delivered_2_clicked()
//{
//    relTableModel->setDelievered(ui->delivered_2->isChecked());
//}

//void edit::on_refresh_button_clicked()
//{
//    int row=sel->currentIndex().row();
//    relTableModel->select();
//    ui->table->setCurrentIndex(sel->model()->index(row,11));
//}

//void edit::on_apply_clicked()
//{
//    QString q="UPDATE data.dpm SET ";
//    if(ui->delivered->isEnabled() && ui->delivered->isChecked())
//        q+="delivered=SYSDATE(),";
//    if(ui->ready->isEnabled() && ui->ready->isChecked())
//        q+="ready=SYSDATE(),";
//    if(ui->picked->isEnabled() && ui->picked->isChecked())
//        q+="picking=SYSDATE(),";
//    if(ui->recieved->isEnabled() && ui->recieved->isChecked())
//        q+="recieved=SYSDATE() ";

//    if(q.endsWith(','))q.chop(1);
//    q+="WHERE Id="+relTableModel->index(sel->currentIndex().row(),0).data(Qt::EditRole).toString();

//    QSqlDatabase::database(activeDb).transaction();
//    QSqlQuery query(QSqlDatabase::database(activeDb));
//    query.exec(q);

//    on_refresh_button_clicked();
//}

//void edit::on_rollback_clicked()
//{
//    QSqlDatabase::database(activeDb).rollback();
//    on_refresh_button_clicked();
//}

//void edit::on_apply_2_clicked()
//{
//    QSqlDatabase::database(activeDb).commit();
//}
