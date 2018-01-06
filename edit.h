#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include <sortfilterproxymodel.h>
#include <tablemodel.h>
#include <QDataWidgetMapper>
#include <QItemSelectionModel>

namespace Ui {
class edit;
}

class edit : public QDialog
{
    Q_OBJECT

public:
    explicit edit(QString active_db="",QWidget *parent = 0);
    ~edit();

//public slots:
//    void rowChanged(QModelIndex,QModelIndex);
//private slots:
//    void on_filterEdit_textChanged(const QString &arg1);

//    void on_dateTimeEdit_dateChanged(const QDate &date);

//    void on_dateTimeEdit_2_dateChanged(const QDate &date);

//    void on_recieved_2_clicked();

//    void on_picking_clicked();

//    void on_ready_to_delivery_clicked();

//    void on_delivered_2_clicked();

//    void on_refresh_button_clicked();

//    void on_apply_clicked();

//    void on_rollback_clicked();

//    void on_apply_2_clicked();

private:
    Ui::edit *ui;
    QString activeDb;

    SortFilterProxyModel *proxyModel;
    tableModel *relTableModel;
    QDataWidgetMapper *mapper;
    QItemSelectionModel *sel;

};

#endif // EDIT_H
