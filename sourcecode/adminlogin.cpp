#include "adminlogin.h"
#include "ui_adminlogin.h"
#include "qmessagebox.h"
#include "login.h"

adminLogin::adminLogin(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::adminLogin)
{
    ui->setupUi(this);
}

adminLogin::~adminLogin()
{
    delete ui;
}

void adminLogin::on_pushButton_clicked()
{
    QString username = ui->lineEdit_User->text();
    QString password = ui->lineEdit_Pass->text();

    if(username == "admin" && password == "admin")
    {
        this->close();
        adminwindow.show();
    }
    else
    {

        ui->label_3->setText("WRONG Password or Username!");
//        //setStyleSheet("QMessageBox{background: rgb(0,0,0);  border: none;font-family: Arial; font-style: normal;  font-size: 15pt; color: #ffffff ; }");
//        setStyleSheet("QMessageBox{color: rgb(255, 255, 255);}");
//        QMessageBox::warning(this, "Login", "Username or passsword are incorrect.");
    }
}

void adminLogin::on_pushButton_back_clicked()
{
    login *back = new login();
    back->show();
    this->close();
}
