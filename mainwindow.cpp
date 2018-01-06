#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "mysqlrelationaldelegate.h"
#include <QSqlRelationalDelegate>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setStatusState();

    resPop.setModal(false);

    connect(this, SIGNAL(roleChanged(Role)),SLOT(customizeWindowRole(Role)));
    emit addConnection();

    relTableModel = new tableModel(ui->table, QSqlDatabase::database(activeDb()),"dpm");
    relTableModel->setColumnsForMain();
    on_refresh_clicked();

    proxyModel=new SortFilterProxyModel(ui->table);
    proxyModel->setSourceModel(relTableModel);
    ui->table->setModel(proxyModel);

    ui->table->resizeColumnsToContents();
    checkDelegate=new CheckBoxDelegate(ui->table);
    ui->table->setItemDelegateForColumn(1,checkDelegate);
    //connect(checkDelegate,SIGNAL(rowChecked(QModelIndex)),SLOT(showResponseWindow(QModelIndex)));
    //ui->table->setItemDelegate(new QSqlRelationalDelegate(ui->table));

    timer=new QTimer(this);
    timer->setInterval(500);
    connect(timer, SIGNAL(timeout()) , this, SLOT(on_refresh_clicked()));

    QMenu *menu = new QMenu(ui->search);
    QAction *m_caseSensitivityAction = menu->addAction(tr("Case Sensitive"));
    m_caseSensitivityAction->setCheckable(true);
    m_caseSensitivityAction->setChecked(true);
    connect(m_caseSensitivityAction, SIGNAL(toggled(bool)),proxyModel,SLOT(setCaseSensitivity(bool)));
    ui->search->setMenu(menu);

    ui->table->addAction(ui->actionEdit);
    QAction *sep=new QAction(ui->table);
    sep->setSeparator(true);
    ui->table->addAction(sep);

    ui->table->addAction(ui->actionCheckUncheckAll);

    sep=new QAction(ui->table);
    sep->setSeparator(true);
    ui->table->addAction(sep);

    QMenu *cMenu=new QMenu(ui->table);
    cMenu->addAction(ui->deleteRowAction);
    cMenu->addAction(ui->deleteRowAction_2);
    ui->del->setMenu(cMenu);
    ui->table->addAction(ui->del);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addConnection()
{
    //    if(dialog.exec()!=QDialog::Accepted)
    //    {
    //        setRole(None);
    //        show();
    //        return;
    //    }
    //    QSqlError err = addConnection(dialog.driverName(), dialog.databaseName(), dialog.hostName(),
    //                                  dialog.userName(), dialog.password(), dialog.port());

    QSqlError err = addConnection("QMYSQL","data" ,"" ,"shakh","123");
    if (err.type() != QSqlError::NoError){
        QMessageBox::warning(this, tr("Database Error"),err.text());
        emit addConnection();
    }
    else
    {
        setRole(getRole("shakh"));
        show();
    }
}
QSqlError MainWindow::addConnection(const QString &driver, const QString &dbName, const QString &host,
                                    const QString &user, const QString &passwd, int port)
{
    static int cCount = 0;
    QSqlError err;

    QSqlDatabase db = QSqlDatabase::addDatabase(driver, QString(user+"_%1").arg(++cCount));
    setDbName((user+"_%1").arg(cCount));
    db.setDatabaseName(dbName);
    db.setHostName(host);
    db.setPort(port);
    if (!db.open(user,passwd)) {
        setDbName("");
        err=db.lastError();
        db = QSqlDatabase();
        QSqlDatabase::removeDatabase(QString(user+"_%1").arg(cCount));
    }
    return err;

}

void MainWindow::setStatusState()
{
    menuBar()->hide();
    statusBar()->layout()->setContentsMargins(10,0,2,2);
    statusBar()->addWidget(new QLabel("",statusBar()));
    statusBar()->addWidget(ui->status,1);
    statusBar()->addWidget(ui->user_button);
}

void MainWindow::customizeWindowRole(MainWindow::Role role)
{
    switch (role) {
    case Admin:{

        ui->error_frame->hide();
        ui->tabWidget->show();
        ui->body->show();

        ui->add_user->setEnabled(true);
        ui->add_item_18->setEnabled(true);
        ui->add_item->setEnabled(true);
        ui->response->setEnabled(true);

        break;
    }
    case Salesman:{
        ui->error_frame->hide();
        ui->tabWidget->show();
        ui->body->show();

        ui->add_user->setEnabled(false);
        ui->add_item_18->setEnabled(false);
        ui->add_item->setEnabled(true);
        ui->response->setEnabled(false);
        break;
    }
    case Storekeeper:{
        ui->error_frame->hide();
        ui->tabWidget->show();
        ui->body->show();

        ui->add_user->setEnabled(false);
        ui->add_item_18->setEnabled(false);
        ui->add_item->setEnabled(false);
        ui->response->setEnabled(true);
        break;
    }
    case Salesman_Storekeeper:{
        break;
    }
    default:{
        ui->body->hide();
        ui->tabWidget->hide();
        ui->error_frame->show();
        ui->animation->setMovie(new QMovie(":/ico/gif/loader.gif"));
        ui->animation->movie()->start();
        ui->user_button->setText("Log in");
        connect(ui->user_button,SIGNAL(clicked(bool)),SLOT(addConnection()));
        break;
    }
    }
}

void MainWindow::statusMessage(const QString str)
{
    ui->status->setText(str);
}

void MainWindow::showResponseWindow(QModelIndex index)
{
    if(!index.isValid()){qDebug()<<"fuck";return;}
    resPop.setParent(ui->table);
    resPop.move(ui->table->visualRect(index).topLeft()+QPoint(10,10)/*+ui->table->mapToGlobal(QPoint(0,0))*/);
    resPop.setIndex(index, relTableModel->fieldIndex("RECIEVED"));
    if(!resPop.isVisible())
        if(resPop.exec()==QDialog::Accepted)
        {
            QString q="UPDATE data.dpm SET ";
            if(resPop.delivered() && resPop.deliveredChecked())
                q+="delivered=SYSDATE(),";
            if(resPop.ready() && resPop.readyChecked())
                q+="ready=SYSDATE(),";
            if(resPop.picked() && resPop.pickedChecked())
                q+="picking=SYSDATE(),";
            if(resPop.recieved() && resPop.recievedChecked())
                q+="recieved=SYSDATE(),";

            //if(q.endsWith(','))q.chop(1);
            q+="remarks='"+resPop.remarks()+"' WHERE Id="+relTableModel->index(index.row(),0).data(Qt::EditRole).toString();

            qDebug()<<q;
            QSqlQuery query(QSqlDatabase::database(activeDb()));
            query.exec(q);

            on_refresh_clicked();
            ui->table->selectRow(index.row());
        }
}

MainWindow::Role MainWindow::getRole(QString user)
{
    QSqlQuery query(QSqlDatabase::database(activeDb()));

    if(!query.exec("select default_role FROM mysql.user WHERE User='"+user+"'"))
    {
        QMessageBox::warning(this, tr("Connection error"),query.lastError().text());
        return None;
    }

    QString roleStr;
    while (query.next())
        roleStr=query.value("default_role").toString();

    if(roleStr=="Admin")return Admin;
    else if(roleStr=="Salesman")return Salesman;
    else if(roleStr=="Salesman,Storekeeper")return Salesman_Storekeeper;
    else if(roleStr=="Storekeeper")return Storekeeper;
    else return None;
}

void MainWindow::on_add_item_clicked()
{
    addItemDialog addDialog(activeDb(),this);
    if(addDialog.exec()!=QDialog::Accepted)
    {
        return;
    }

    QSqlQuery query(relTableModel->database());

    query.prepare("INSERT INTO `data`.`dpm` (`customer_id`, `req1`, `req2`, `req3`, `req4`, `wip`, `dl_location_id`, `dl_category_id`, `req_data`, `remark`,`salesman_id`) "
                  "VALUES (:customer,:r1,:r2,:r3,:r4,:r5,:location,:category,:req_data,:remark,:salesman)");

    query.bindValue(":customer",addDialog.customer());

    if(addDialog.r1())query.bindValue(":r1",addDialog.r1());
    if(addDialog.r2())query.bindValue(":r2",addDialog.r2());
    if(addDialog.r3())query.bindValue(":r3",addDialog.r3());
    if(addDialog.r4())query.bindValue(":r4",addDialog.r4());
    if(addDialog.r5())query.bindValue(":r5",addDialog.r5());

    query.bindValue(":location",addDialog.location());
    query.bindValue(":category",addDialog.category());
    query.bindValue(":req_data",addDialog.requiredData());
    query.bindValue(":remark",addDialog.remark());
    query.bindValue(":salesman",addDialog.salesman());

    query.exec();
    if(query.lastError().type()!=QSqlError::NoError)
        statusMessage(query.lastError().text());
    else
    {
        on_refresh_clicked();

        for(int i(0); i<ui->table->model()->rowCount();i++)
            if(query.lastInsertId().toInt()==ui->table->model()->data(ui->table->model()->index(i,0),Qt::EditRole))
            {
                ui->table->selectRow(i);
                break;
            }
    }
}

void MainWindow::on_recieved_clicked()
{
    relTableModel->setRecieved(ui->recieved->isChecked());
}

void MainWindow::on_filterEdit_textChanged(const QString &arg1)
{
    proxyModel->setFilterRegExp(arg1);
}

void MainWindow::on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime)
{
    proxyModel->setFilterMinimumDate(dateTime.date());
}

void MainWindow::on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime)
{
    proxyModel->setFilterMaximumDate(dateTime.date());
}

void MainWindow::on_picking_clicked()
{
    relTableModel->setPicking(ui->picking->isChecked());
}

void MainWindow::on_ready_to_delivery_clicked()
{
    relTableModel->setReady(ui->ready_to_delivery->isChecked());
}

void MainWindow::on_delivered_clicked()
{
    relTableModel->setDelievered(ui->delivered->isChecked());
}

void MainWindow::on_response_clicked()
{
    if(!ui->table->currentIndex().isValid())
    {
        QMessageBox::information(this,"No current element","You should select at least one element from the table!");
        return;
    }
    if(role()==Role::Storekeeper)
    {
        //if(!relTableModel->index(ui->table->currentIndex().row(),relTableModel->fieldIndex("IN CHARGE")).data().isNull())
        {
        showResponseWindow(ui->table->currentIndex());
        return;
        }

    }

//    responseWidget response(activeDb(),this);
//    if(response.exec()!=QDialog::Accepted)
//    {
//        return;
//    }
//    response.

}

void MainWindow::on_table_doubleClicked(const QModelIndex &index)
{
    showResponseWindow(index);
}

void MainWindow::on_refresh_clicked()
{
    relTableModel->select();

    if (relTableModel->lastError().type() != QSqlError::NoError)
    {
        emit statusMessage("<font color='red'>"+relTableModel->lastError().text());
        timer->stop();
        setRole(None);
        return;
    }
    emit statusMessage("<font color='green'>Success : </font>"+QString::number(relTableModel->rowCount())+" rows affected");
}

void MainWindow::on_deleteRowAction_triggered()
{
    if(QMessageBox::warning(this, "Deleting items", "Are you sure you want to delete checked items?", QMessageBox::Ok|QMessageBox::Cancel)!=QMessageBox::Ok)return;

    for(int i=0; i<proxyModel->rowCount();i++)
        if(relTableModel->index(i,1).data(Qt::EditRole).toBool())
            relTableModel->removeRow(i);
    relTableModel->submitAll();
}

void MainWindow::on_deleteRowAction_2_triggered()
{
    if(QMessageBox::warning(this, "Deleting items", "Are you sure you want to delete selected items?", QMessageBox::Ok|QMessageBox::Cancel)!=QMessageBox::Ok)return;


    foreach (QModelIndex index, ui->table->selectionModel()->selectedIndexes())
    {
        relTableModel->removeRow(index.row());
    }

relTableModel->submitAll();
}

void MainWindow::on_add_user_clicked()
{
    AddUser addUser(this);
    if(addUser.exec()!=QDialog::Accepted)
    {
        return;
    }

    QSqlQuery query(relTableModel->database());

    if(addUser.role()=="Admin")
    {
        query.prepare("CREATE USER :name@:host IDENTIFIED BY :password;"
                      "GRANT EXECUTE, SELECT, ALTER, DELETE, DROP, UPDATE, SHOW VIEW, INSERT  ON `data`.* TO :name@:host WITH GRANT OPTION;"
                      "UPDATE `mysql`.`user` SET `default_role`='Admin' WHERE  `Host`=:host AND `User`=:name");
    }
    else if(addUser.role()=="Salesman")
    {
        query.prepare("CREATE USER :name@:host IDENTIFIED BY :password;"
                      "GRANT SELECT, UPDATE, INSERT  ON `data`.* TO :name@:host WITH GRANT OPTION;"
                      "UPDATE `mysql`.`user` SET `default_role`='Salesman' WHERE  `Host`=:host AND `User`=:name");
    }
    else
    {
        query.prepare("CREATE USER :name@:host IDENTIFIED BY :password;"
                      "GRANT SELECT, UPDATE ON `data`.* TO :name@:host WITH GRANT OPTION;"
                      "UPDATE `mysql`.`user` SET `default_role`='Storekeeper' WHERE  `Host`=:host AND `User`=:name");
    }

    query.bindValue(":name",addUser.name());
    query.bindValue(":host",addUser.host());
    query.bindValue(":password",addUser.password());

    query.exec();
    if(query.lastError().type()!=QSqlError::NoError)
        statusMessage(query.lastError().text());
    else
        statusMessage("<font color='green'>Successfully added new user!");

}

void MainWindow::on_autorefresh_clicked(bool checked)
{
    if(checked)
    {
        timer->start();
        ui->autorefresh->setText("ON");
        return;
    }

    timer->stop();
    ui->autorefresh->setText("OFF");
}

void MainWindow::on_actionCheckUncheckAll_triggered(bool checked)
{
    for(int i=0; i<proxyModel->rowCount();i++)
        relTableModel->setData(relTableModel->index(i,1),checked,Qt::EditRole);
}

void MainWindow::on_actionEdit_triggered()
{
    //    responseWidget resDialog(this);
    //    //resDialog.setIndex(ui->table->currentIndex());

    //    if(resDialog.exec()!=QDialog::Accepted)
    //    {
    //        return;
    //    }
}
