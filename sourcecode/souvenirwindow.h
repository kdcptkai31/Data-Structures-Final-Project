/***************************************************************
 * The Souvenir Window Class
 * *************************************************************
 * This class allows for the use of the souvenir window of the
 * main program. This interfaces with the database to display,
 * modify, and change available souvenirs for a stadium location
 * *************************************************************/

#ifndef SOUVENIRWINDOW_H
#define SOUVENIRWINDOW_H

#include <QWidget>
#include "database.h"
#include <QString>
#include <QVector>
#include <QMap>
#include "checkoutwindow.h"
#include <QStandardItemModel>
#include "adminlogin.h"

namespace Ui {
class souvenirwindow;
}
struct cartNames{
    QString itemName;
    QString teamName;
};
struct souvenir {
    QString teamName;
    QString stadiumName;
    QString itemName;
    double price;
};


class souvenirwindow : public QWidget
{
    Q_OBJECT

public:
    explicit souvenirwindow(QWidget *parent = 0);
    void LoadDisplayList();
    ~souvenirwindow();

    void LoadWindow(QVector<QString> stadiums);


private slots:
    void on_nextStadium_clicked();

    void on_previousStadium_clicked();

    void on_checkOut_clicked();

    void on_teamSouvenirs_doubleClicked(const QModelIndex &index);

    void on_cart_doubleClicked(const QModelIndex &index);

private:
    Ui::souvenirwindow *ui;
    QVector<QString> displayList;
    QVector<souvenir> souvenirs;
    QVector<souvenir> cartSouvenirs;
    Database *database;
    int currentStadium;
    QMap<cartNames, double> cart;
    double cartSum;
    CheckoutWindow checkout;

    int cartRowCount;
    QString cartData[20][20];
    int cartSize;



};

#endif // SOUVENIRWINDOW_H
