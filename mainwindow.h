#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

//windows
#include <qsqlconnectiondialog.h>
#include <additemdialog.h>
#include <responsewidget.h>
#include <respopup.h>
#include <adduser.h>
#include <edit.h>
//...

//Models
#include <sortfilterproxymodel.h>
#include <tablemodel.h>
#include <checkboxdelegate.h>
//...

#include <QtSql>
#include <QtWidgets>
#include <QMessageBox>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

    Q_PROPERTY(Role role READ role WRITE setRole NOTIFY roleChanged)

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    enum Role{
        None=0,
        Admin,
        Salesman_Storekeeper,
        Salesman,
        Storekeeper
    };
    Q_ENUM(Role)

    Role role() const
    {   return m_role;  }
    void setRole(Role role)
    {
        m_role=role;
        emit roleChanged(role);
    }
    Role getRole(QString);

    QString activeDb() const
    { return dbName; }
    void setDbName(QString name)
    {
        dbName=name;
    }

    QSqlError addConnection(const QString &driver, const QString &dbName, const QString &host,
                                 const QString &user, const QString &passwd, int port = -1);

    void setStatusState();

public slots:
    void customizeWindowRole(Role);
    void addConnection();
    void statusMessage(const QString str);

signals:
    void roleChanged(Role);

private slots:

    void showResponseWindow(QModelIndex);

    void on_add_item_clicked();

    void on_recieved_clicked();

    void on_filterEdit_textChanged(const QString &arg1);

    void on_dateTimeEdit_dateTimeChanged(const QDateTime &dateTime);

    void on_dateTimeEdit_2_dateTimeChanged(const QDateTime &dateTime);

    void on_picking_clicked();

    void on_ready_to_delivery_clicked();

    void on_delivered_clicked();

    void on_response_clicked();

    void on_table_doubleClicked(const QModelIndex &index);

    void on_refresh_clicked();

    void on_deleteRowAction_triggered();

    void on_deleteRowAction_2_triggered();

    void on_add_user_clicked();

    void on_autorefresh_clicked(bool checked);

    void on_actionCheckUncheckAll_triggered(bool checked);

    void on_actionEdit_triggered();

private:
    Ui::MainWindow *ui;
    QString dbName;

    //Models
    SortFilterProxyModel *proxyModel;
    tableModel *relTableModel;
    CheckBoxDelegate *checkDelegate;
    //...

    //Dialogs
    qsqlconnectiondialog dialog;
    resPopUp resPop;
    //...

    //Roles
    Role m_role;
    //...

    QTimer *timer;

};

#endif // MAINWINDOW_H
