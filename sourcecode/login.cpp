#include "login.h"
#include "ui_login.h"

/**
 * @brief login::login
 * @param parent
 * The standard login window ui
 */
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    addAccount("","",false);
    addAccount("admin","admin",true);
    interface.prev=this;
}

/**
 * @brief login::~login
 * Destructor
 */
login::~login()
{
    delete ui;
}

/**
 * @brief login::isAccount
 * @param nameIn
 * @param passIn
 * @return bool
 * @fn Determines if the credentials entered are traveler credentials
 */
bool login::isAccount(QString nameIn, QString passIn)
{
    /*
     * Input: STRING username guess, STRING password guess
     * Output: BOOL true if found in accounts vector, false if otherwise
     *
     */
    //this will be returned as the state of the inputted variables
    bool isValid = false;

    //cycle through the accounts and check if it's a valid account
    for(int index = 0; index < accounts.size(); index++)
    {
        if(nameIn == accounts[index].name && passIn == accounts[index].password)
        {
            isValid = true;
        }
    }
    return isValid;
}

/**
 * @brief login::isAdmin
 * @param nameIn
 * @param passIn
 * @return bool
 * @fn Determines if the credentials entered are admin credentials
 */
bool login::isAdmin(QString nameIn,QString passIn)
{

    bool isAdmin = false; //returns true if the user is infact an admin
    int accountIndex;     //index of the account searched for

    //cycle through accounts list again checking if the username is on the list
    for(int i = 0; i < accounts.size(); i++)
    {
        if(accounts[i].name == nameIn)
        {
            accountIndex = i;
        }
    }

    //checks the found index from above and compares to the admin list
    if(isAccount(nameIn,passIn))
    {
       if(accounts.at(accountIndex).okAdmin == true)
       {
           isAdmin = true;
       }
    }
    return isAdmin;
}

/**
 * @brief login::addAccount
 * @param nameIn
 * @param passIn
 * @param adminIn
 * @fn Adds an account to the 'accounts' vector, allowing the user to create new accounts.
 */
void login::addAccount(QString nameIn, QString passIn, bool adminIn)
{
    user insert;

    //assumes that the argument is valid variables
    insert.name = nameIn;
    insert.password = passIn;
    insert.okAdmin = adminIn;
    //adds the inserted variables into the struct
    accounts.push_back(insert);

}

/**
 * @brief login::on_LoginButton_clicked
 * @fn Logs the user in to the correct UI, depending on whether the user is a traveler or admin.
 */
void login::on_LoginButton_clicked()
{

    this->close();
    tiddies.show();

//    Login = new adminLogin();
//    Login->show;
//    this->close();

//    QString inName = ui->UserNameInput->text();
//    QString inPass = ui->PasswordInput->text();


//        if(isAccount(inName, inPass))
//        {
//            if(isAdmin(inName,inPass))
//            {
//                this->close();
//                adminWindow.show();
//            }
//            else
//            {
//                this->close();
//                interface.show();
//            }
//        }
//        else
//        {
//            QMessageBox::critical(this,"Error","Invalid Name and or Password!");
//            ui->UserNameInput->clear();
//            ui->PasswordInput->clear();
//        }

}

///**
// * @brief login::on_CreateCheckBox_toggled makes new account
// * @param checked
// */
//void login::on_CreateCheckBox_toggled(bool checked)
//{
//    ui->userNameLabel->setText("Desired Username: ");
//    ui->passwordLabel->setText("Desired Password: ");
//    ui->LoginButton->setText("Create");
//    if(checked == false)
//    {
//        ui->userNameLabel->setText("Username: ");
//        ui->passwordLabel->setText("Password: ");
//        ui->LoginButton->setText("Login");
//        ui->printNewUserLabel->setText("");
//    }
//}



void login::on_pushButton_viewData_clicked()
{
    this->hide();
    interface.show();
}
