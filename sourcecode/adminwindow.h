/***************************************************************
 * The Admin Window Class
 * *************************************************************
 * This class provides the login interface and admin functions
 * for the use of logging in as an Administrator. Using this
 * interface it grants access to the applications maintenance
 * functions allowing Admins to modify stadium, team, and
 * souvenir data.
 * *************************************************************/

#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QDialog>
#include <QObject>
#include<QApplication>
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "database.h"

namespace Ui {
class AdminWindow;
}

/**
 * @brief The AdminWindow class
 * @variable UI
 * @fn Defines the basics for the Admin Window ui interface
 */
class AdminWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AdminWindow(QWidget *parent = 0);
    ~AdminWindow();

private slots:
    void on_sucSailorButton_clicked();
    void on_priceChangeButton_clicked();
    void on_done_clicked();
    void on_priceGoButton_clicked();
    void on_addNewSouvButton_clicked();
    void on_addNewSouv_clicked();
    void on_delSouvButton_clicked();
    void on_delSouv_clicked();
    void on_modifyInfoButton_clicked();
    void on_modGoButton_clicked();
    void on_modModButton_clicked();
    void on_backLogin_clicked();

private:
    Ui::AdminWindow *ui;
    Database* m_db;
    int priceChangeCount;
    int addNewSouvBCount;
    int delSouvCount;
    int modCount;
    QString stadiumName;
    QString columnName;

};

#endif // ADMINWINDOW_H
