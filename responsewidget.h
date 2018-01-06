#ifndef RESPONSEWIDGET_H
#define RESPONSEWIDGET_H

#include <QDialog>
#include <tablemodel.h>

namespace Ui {
class responseWidget;
}

class responseWidget : public QDialog
{
    Q_OBJECT

public:
    explicit responseWidget(QModelIndex index, QString active_db="", QWidget *parent=0);
    ~responseWidget();

private:
    Ui::responseWidget *ui;
    QString activeDb;
    QModelIndex ind;
};

#endif // RESPONSEWIDGET_H
