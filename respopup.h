#ifndef RESPOPUP_H
#define RESPOPUP_H

#include <QDialog>

namespace Ui {
class resPopUp;
}

class resPopUp : public QDialog
{
    Q_OBJECT

public:
    explicit resPopUp(QWidget *parent = 0);
    ~resPopUp();
    void setIndex(QModelIndex index, int column);

    bool recieved() const;
    bool picked() const;
    bool ready() const;
    bool delivered() const;

    bool recievedChecked() const;
    bool pickedChecked() const;
    bool readyChecked() const;
    bool deliveredChecked() const;

    QString remarks() const;

private slots:

    void on_accept_clicked();
    void on_revert_clicked();


    void on_toolButton_clicked();

private:
    Ui::resPopUp *ui;
};

#endif // RESPOPUP_H
