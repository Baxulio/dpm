#include "tablemodel.h"
#include <QFont>
#include <QBrush>
#include <QCheckBox>
tableModel::tableModel(QObject *parent, QSqlDatabase db, QString table):
    QSqlRelationalTableModel(parent,db)

{
    setRecieved(false);
    setPicking(false);
    setReady(false);
    setDelievered(false);

    setTable(table);
}


QVariant tableModel::data(const QModelIndex &item, int role) const
{
    int row = item.row();
    int col = item.column();

    switch(role){
    case Qt::DisplayRole:
    {
        if(!col){
            if(delievered)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("delivered"))).isNull())
                    return "●";
            if(ready)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("ready"))).isNull())
                    return "●";
            if(picking)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("picking"))).isNull())
                    return "●";
            if(recieved)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("recieved"))).isNull())
                    return "●";
            return QVariant();
        }
        break;
    }
    case Qt::BackgroundColorRole:
    {
        if(QSqlRelationalTableModel::data(this->index(row,0)).toString()=="!")return QColor(Qt::yellow);

        if(delievered)
            if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("delivered"))).isNull())
                return QColor(qRgb(241,250,229));
        if(ready)
            if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("ready"))).isNull())
                return QColor(qRgb(242,251,254));
        if(picking)
            if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("picking"))).isNull())
                return QColor(qRgb(255,250,231));
        if(recieved)
            if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("recieved"))).isNull())
                return QColor(qRgb(255,232,228));
        if(item.column()>fieldIndex("SALESMAN"))
                return QColor(qRgb(250,250,250));

        break;
    }
    case Qt::TextAlignmentRole:
    {
        if(col!=fieldIndex("CUSTOMER"))return Qt::AlignCenter;
        break;
    }
    case Qt::TextColorRole:
    {
        if(!col){
            if(delievered)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("delivered"))).isNull())
                    return QColor(qRgb(154,223,54));
            if(ready)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("ready"))).isNull())
                    return QColor(qRgb(0,176,217));
            if(picking)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("picking"))).isNull())
                    return QColor(qRgb(255,222,0));
            if(recieved)
                if(!QSqlRelationalTableModel::data(this->index(row, fieldIndex("recieved"))).isNull())
                    return QColor(qRgb(255,74,34));
            return QVariant();
        }
        break;
    }
    }
    return QSqlRelationalTableModel::data(item,role);
}


void tableModel::setColumnsForMain()
{
    QStringList headers;
    headers<<""<<"ID"<<"CUSTOMER"<<"R1"<<"R2"<<"R3"<<"R4"<<"WIP"<<"DELIVERY LOCATION"<<"DELIVERY CATEGORY"<<"REQUIRED DATA"<<"REMARK"<<"RAISED TIME"<<"SALESMAN"<<"RECIEVED"<<"PICKING"<<"READY"<<"DELIVERED"<<"REMARKS"<<"IN CHARGE";

    setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    for(int i=0; i<headers.length(); i++)
        setHeaderData(i, Qt::Horizontal, headers.at(i));

    setRelation(fieldIndex("customer_id"),QSqlRelation("customer","Id", "Customer"));
    setRelation(fieldIndex("dl_location_id"),QSqlRelation("dl_location","Id", "dl_location"));
    setRelation(fieldIndex("dl_category_id"),QSqlRelation("dl_category","Id", "dl_category"));
    setRelation(fieldIndex("salesman_id"),QSqlRelation("salesman_staffcode","Id", "Salesman"));
    setRelation(fieldIndex("charge_id"),QSqlRelation("storekeeper","Id", "storekeeper_name"));

    setJoinMode(QSqlRelationalTableModel::LeftJoin);
}

void tableModel::setColumnsForResponse()
{
    QStringList headers;
    headers<<""<<"ID"<<"CUSTOMER"<<"R1"<<"R2"<<"R3"<<"R4"<<"WIP"<<"DELIVERY LOCATION"<<"DELIVERY CATEGORY"<<"REQUIRED DATA"<<"RECIEVED"<<"PICKING"<<"READY"<<"DELIVERED"<<"REMARKS"<<"IN CHARGE";

    setEditStrategy(QSqlRelationalTableModel::OnManualSubmit);

    for(int i=0; i<headers.length(); i++)
        setHeaderData(i, Qt::Horizontal, headers.at(i));

    removeColumns(fieldIndex("remark"),3);

    setRelation(fieldIndex("customer_id"),QSqlRelation("customer","Id", "Customer"));
    setRelation(fieldIndex("dl_location_id"),QSqlRelation("dl_location","Id", "dl_location"));
    setRelation(fieldIndex("dl_category_id"),QSqlRelation("dl_category","Id", "dl_category"));
    setRelation(fieldIndex("charge_id"),QSqlRelation("storekeeper","Id", "storekeeper_name"));

    setJoinMode(QSqlRelationalTableModel::LeftJoin);

}
