#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include <QSqlRelationalTableModel>
#include <QSqlQuery>

class tableModel : public QSqlRelationalTableModel
{
    Q_OBJECT
public:

    tableModel(QObject *parent, QSqlDatabase db,QString table);

    QVariant data(const QModelIndex &item, int role) const;


    void setRecieved(bool b)
    {
        recieved=b;
    }
    void setPicking(bool b){
        picking=b;
    }
    void setReady(bool b){
        ready=b;
    }
    void setDelievered(bool b){
        delievered=b;
    }

    bool recieved,picking,ready, delievered;

    void setColumnsForMain();
    void setColumnsForResponse();


};

#endif // TABLEMODEL_H
