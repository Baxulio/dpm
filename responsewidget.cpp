#include "responsewidget.h"
#include "ui_responsewidget.h"
#include <QtSql>

responseWidget::responseWidget(QModelIndex index, QString active_db, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::responseWidget),
    activeDb(active_db),
    ind(index)
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
    //ui->customer->setCurrentIndex(ui->customer->findText(index.,Qt::MatchExactly));

   // mod=new QSqlTableModel(this,QSqlDatabase::database(activeDb));
   // mod->setTable("dl_location");
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

responseWidget::~responseWidget()
{
    delete ui;
}

//void responseWidget::rowChanged(QModelIndex curr, QModelIndex prev)
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

//void responseWidget::on_filterEdit_textChanged(const QString &arg1)
//{
//    proxyModel->setFilterRegExp(arg1);
//}

//void responseWidget::on_dateTimeEdit_dateChanged(const QDate &date)
//{
//    proxyModel->setFilterMinimumDate(date);
//}

//void responseWidget::on_dateTimeEdit_2_dateChanged(const QDate &date)
//{
//    proxyModel->setFilterMaximumDate(date);
//}

//void responseWidget::on_recieved_2_clicked()
//{
//    relTableModel->setRecieved(ui->recieved_2->isChecked());
//}

//void responseWidget::on_picking_clicked()
//{
//    relTableModel->setPicking(ui->picking->isChecked());
//}

//void responseWidget::on_ready_to_delivery_clicked()
//{
//    relTableModel->setPicking(ui->ready_to_delivery->isChecked());
//}

//void responseWidget::on_delivered_2_clicked()
//{
//    relTableModel->setDelievered(ui->delivered_2->isChecked());
//}

//void responseWidget::on_refresh_button_clicked()
//{
//    int row=sel->currentIndex().row();
//    relTableModel->select();
//    ui->table->setCurrentIndex(sel->model()->index(row,11));
//}

//void responseWidget::on_apply_clicked()
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

//void responseWidget::on_rollback_clicked()
//{
//    QSqlDatabase::database(activeDb).rollback();
//    on_refresh_button_clicked();
//}

//void responseWidget::on_apply_2_clicked()
//{
//    QSqlDatabase::database(activeDb).commit();
//}
