#ifndef CHECKOUTWINDOW_H
#define CHECKOUTWINDOW_H

#include <QWidget>
namespace Ui {
class CheckoutWindow;
}

class CheckoutWindow : public QWidget
{
    Q_OBJECT

public:
    /*!
     * \fn CheckoutWindow
     * \param parent
     */
    explicit CheckoutWindow(QWidget *parent = 0);

    /*!
     * \fn invalidCVV
     * \param cvv
     * \return
     */
    bool invalidCVV(QString cvv);

    /*!
     * \fn invalidCardNumber
     * \param cardNum
     * \return
     */
    bool invalidCardNumber(QString cardNum);

    /*!
     * \fn checkNum
     * \param postion
     * \return
     */
    bool checkNum(QChar postion);

    /*!
     * \fn setUserameLabel
     */
    void setUserameLabel();


    ~CheckoutWindow();

private slots:
    /*!
     * \fn on_pushButton_clicked
     */
    void on_pushButton_clicked();

    /*!
     * \fn on_pushButton_2_clicked
     */
    void on_pushButton_2_clicked();


private:
    Ui::CheckoutWindow *ui;         /*! \var ui*/
};

#endif // CHECKOUTWINDOW_H
