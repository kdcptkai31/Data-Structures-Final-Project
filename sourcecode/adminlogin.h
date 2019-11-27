#ifndef ADMINLOGIN_H
#define ADMINLOGIN_H

#include <QDialog>
#include <adminwindow.h>
namespace Ui {
class adminLogin;
}

class adminLogin : public QDialog
{
    Q_OBJECT

public:
    explicit adminLogin(QWidget *parent = 0);
    ~adminLogin();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_back_clicked();

private:
    Ui::adminLogin *ui;
    AdminWindow adminwindow;
};

#endif // ADMINLOGIN_H
