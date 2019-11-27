#include "checkoutwindow.h"
#include "ui_checkoutwindow.h"
#include <QMessageBox>
#include <QDebug>

/*!
 * \fn CheckoutWindow::CheckoutWindow
 * \param parent
 */
CheckoutWindow::CheckoutWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CheckoutWindow)
{
    ui->setupUi(this);

}

/*!
 * \fn CheckoutWindow::~CheckoutWindow
 */
CheckoutWindow::~CheckoutWindow()
{
    delete ui;
}

/*!
 * \fn CheckoutWindow::on_pushButton_clicked
 */
void CheckoutWindow::on_pushButton_clicked()
{
    QString cardNum;
    QString month;
    QString year;
    QString CVV;

    cardNum = ui->cardNum->text();
    month = ui->month->currentText();
    year = ui->year->currentText();
    CVV = ui->CVV->text();

    if(invalidCardNumber(cardNum)){
        QMessageBox::critical(this, "ERROR", "Invalid Card Number!");
    }
    else if(month == "Month"){
        QMessageBox::critical(this, "ERROR", "Invalid Month!");
    }
    else if(year == "Year"){
        QMessageBox::critical(this, "ERROR", "Invalid Year!");
    }
    else if(invalidCVV(CVV)){
        QMessageBox::critical(this, "ERROR", "CVV!");
    }
    else{
        qDebug() << "Card has been checked!\n";
        QMessageBox::information(this, "Thank You!", "Your order has been proccessed, sending purchased information to your email.");
        ui->cardNum->clear();
        ui->CVV->clear();
        ui->month->setCurrentIndex(0);
        ui->year->setCurrentIndex(0);
//        windowHolder* wh = windowHolder::getInstance();
//        wh->clearShoppingCart();
//        wh->checkoutWindowHide();
        this->hide();
    }

}

/*!
 * \fn CheckoutWindow::on_pushButton_2_clicked
 */
void CheckoutWindow::on_pushButton_2_clicked()
{
    ui->cardNum->clear();
    ui->CVV->clear();
    ui->month->setCurrentIndex(0);
    ui->year->setCurrentIndex(0);
//    windowHolder* wh = windowHolder::getInstance();
//    wh->checkoutWindowHide();
    this->hide();
}

/*!
 * \fn CheckoutWindow::checkNum
 * \param postion
 * \return
 */
bool CheckoutWindow::checkNum(QChar postion){
    return (postion == '0' ||
            postion == '1' ||
            postion == '2' ||
            postion == '3' ||
            postion == '4' ||
            postion == '5' ||
            postion == '6' ||
            postion == '7' ||
            postion == '8' ||
            postion == '9');
}

/*!
 * \fn CheckoutWindow::setUserameLabel
 */
void CheckoutWindow::setUserameLabel()
{
    //windowHolder *WH = windowHolder::getInstance();
    ui->infoLabel->setText("Please enter your credit/debit card information ");
}

/*!
 * \fn CheckoutWindow::invalidCardNumber
 * \param cardNum
 * \return
 */
bool CheckoutWindow::invalidCardNumber(QString cardNum){
    bool invalid = false;
    if(cardNum.size() != 16){
        return true;
    }
    else{
        for(int i = 0; i < 16 && invalid; i++){
            if(!checkNum(cardNum[i])){
                invalid = true;
            }
        }
        return invalid;
    }
}

/*!
 * \fn CheckoutWindow::invalidCVV
 * \param cvv
 * \return
 */
bool CheckoutWindow::invalidCVV(QString cvv){
    bool invalid = false;
    if(cvv.size() != 3){
        return true;
    }
    else{
        for(int i = 0; i < 3 && invalid; i++){
            if(!checkNum(cvv[i])){
                invalid = true;
            }
        }
        return invalid;
    }
}


