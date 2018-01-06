#ifndef QSQLCONNECTIONDIALOG_H
#define QSQLCONNECTIONDIALOG_H

#include <QDialog>

namespace Ui {
class qsqlconnectiondialog;
}

class qsqlconnectiondialog : public QDialog
{
    Q_OBJECT

public:
    explicit qsqlconnectiondialog(QWidget *parent = 0);
    ~qsqlconnectiondialog();

    QString driverName() const;
    QString databaseName() const;
    QString userName() const;
    QString password() const;
    QString hostName() const;
    int port() const;

private slots:

    void on_pushButton_clicked();

private:
    Ui::qsqlconnectiondialog *ui;
};

#endif // QSQLCONNECTIONDIALOG_H
