/***************************************************************
 * The Login Class
 * *************************************************************
 * This class provides functionality for managing user logins,
 * user accounts, adming accounts, and user management. The
 * class interacts with the database (once it's loaded) to
 * verify the user has proper user/admin access to the program.
 * *************************************************************/

#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>

#include <QDialog>
#include <QVector>
#include <QMessageBox>
#include "mainwindow.h"
#include "adminwindow.h"
#include "adminlogin.h"

//holds the username, password, and admin access
//of each account on file.
struct user
{
    QString name;
    QString password;
    bool okAdmin;
};

namespace Ui {
class login;
}

/**
 * @brief The login class handles login information, the program
 * checks the credentials and determines if the account is an admin
 * or traveler. The class also allows the user to add an account.
 */
class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = 0);
    ~login();

    //accessor functions
    bool isAccount(QString nameIn, QString passIn); //!< isAccount checks if the user is a traveler.  */

    bool isAdmin(QString nameIn, QString passIn); //!< isAdmin checks to see if the user is an admin.  */

    //mutators
    void addAccount(QString nameIn, QString passIn, bool adminIn); //!< addAccount allows the user to add a new account.  */



private slots:
    void on_LoginButton_clicked(); //!< "Login" push button  */


    //void on_CreateCheckBox_toggled(bool checked); //!< "Login" new user creation  */



    void on_pushButton_viewData_clicked();

private:
    Ui::login *ui;
    QVector<user> accounts; /*!< QVector of struct 'user'  */
                            //vector holding user login info
                            //using struct:user
    MainWindow interface;   /*!< Traveler interface */
    AdminWindow adminWindow; /*!< Admin interface */
    adminLogin tiddies;

};

#endif // LOGIN_H
