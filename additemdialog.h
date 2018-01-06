#ifndef ADDITEMDIALOG_H
#define ADDITEMDIALOG_H

#include <QDialog>
#include <QtSql>

namespace Ui {
class addItemDialog;
}

class addItemDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addItemDialog(QString, QWidget *parent=0);
    ~addItemDialog();

    int salesman() const;
    int customer() const;
    int location() const;
    int category() const;
    QString remark() const;
    QDate requiredData() const;
    int r1() const;
    int r2() const;
    int r3() const;
    int r4() const;
    int r5() const;

private slots:

    void on_pushButton_clicked();

private:
    Ui::addItemDialog *ui;
};

#endif // ADDITEMDIALOG_H
