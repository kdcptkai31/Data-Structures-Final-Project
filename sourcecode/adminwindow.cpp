#include "adminwindow.h"
#include "login.h"
#include "ui_adminwindow.h"

/**
 * @brief AdminWindow::AdminWindow
 * @param parent
 *
 * The admin window class allows for the use of
 * the basic (default) admin windows.
 */

AdminWindow::AdminWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AdminWindow)
{
    ui->setupUi(this);
    ui->sucSailorLabel->setVisible(false);
    ui->comboTeams->setVisible(false);
    ui->cbLabel->setVisible(false);
    ui->comboPriceSouv->setVisible(false);
    ui->priceSouvLabel->setVisible(false);
    ui->priceLabel->setVisible(false);
    ui->priceEdit->setVisible(false);
    ui->priceGoButton->setVisible(false);
    ui->souvLabel->setVisible(false);
    ui->newSouvEdit->setVisible(false);
    ui->newSouvCombo->setVisible(false);
    ui->newSouvLabel->setVisible(false);
    ui->souvPriceLabel->setVisible(false);
    ui->newSouvPriceEdit->setVisible(false);
    ui->addNewSouv->setVisible(false);
    ui->delSouvCombo->setVisible(false);
    ui->delSouvLabel->setVisible(false);
    ui->delTeamCombo->setVisible(false);
    ui->delTeamLabel->setVisible(false);
    ui->delSouv->setVisible(false);
    ui->modColCombo->setVisible(false);
    ui->modColLabel->setVisible(false);
    ui->modStadCombo->setVisible(false);
    ui->modStadLabel->setVisible(false);
    ui->modGoButton->setVisible(false);
    ui->modEdit->setVisible(false);
    ui->modEditLabel->setVisible(false);
    ui->modModButton->setVisible(false);
    priceChangeCount=0;
    addNewSouvBCount=0;
}

/**
 * @brief AdminWindow::~AdminWindow
 * @param Deconstructor
 */
AdminWindow::~AdminWindow()
{
    delete ui;
}

/**
 * @brief AdminWindow::on_sucSailorButton_clicked
 * @fn Enables creating a connection to the database
 */
void AdminWindow::on_sucSailorButton_clicked(){
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    static int num =0;

    if (!m_db->isCreated())
    {
       ui->dbLabel->setText("Error: connection with database fail");
    }
    else
    {
       ui->dbLabel->setText("Database: connection ok");
    }

    if(num==0)
    {
    QSqlQuery query;
    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Las Vegas Stadium','Oakland–Alameda County Coliseum ',325)");
    query.exec();
    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Las Vegas Stadium','Dodger Stadium',300)");
    query.exec();
    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Las Vegas Stadium','Chase Field',250)");
    query.exec();

    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Oakland–Alameda County Coliseum ','Las Vegas Stadium',325)");
    query.exec();
    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Dodger Stadium','Las Vegas Stadium',300)");
    query.exec();
    query.prepare("INSERT into MLB_Distances ('Beginning Stadium', 'Ending Stadium', 'Distance') VALUES ('Chase Field','Las Vegas Stadium',250)");
    query.exec();
    //todo
    QSqlQuery query2;
    query2.prepare("INSERT into MLB_Info ('Team Name', 'Stadium Name', 'Seating Capacity', 'Location', 'League', 'Surface Type', 'Stadium Roof Type', 'Typology', 'Distance', 'Date') VALUES ('Las Vegas Gamblers','Las Vegas Stadium',44444,'Las Vegas, Nevada ','National','Grass','Open', 'Retro Modern', '400 feet (122m)', '2018' )");
    query2.exec();

    //todo
    QSqlQuery query3;
    query3.prepare("INSERT into MLB_Stadium_Souviners ('Team', 'Item', 'Price', 'Stadium') VALUES ('Las Vegas Gamblers', 'Baseball cap', 23.99,'Las Vegas Stadium')");
    query3.exec();
    query3.prepare("INSERT into MLB_Stadium_Souviners ('Team', 'Item', 'Price', 'Stadium') VALUES ('Las Vegas Gamblers', 'Baseball bat', 79.39,'Las Vegas Stadium')");
    query3.exec();
    query3.prepare("INSERT into MLB_Stadium_Souviners ('Team', 'Item', 'Price', 'Stadium') VALUES ('Las Vegas Gamblers', 'Team pennant', 13.99,'Las Vegas Stadium')");
    query3.exec();
    query3.prepare("INSERT into MLB_Stadium_Souviners ('Team', 'Item', 'Price', 'Stadium') VALUES ('Las Vegas Gamblers', 'Autographed baseball', 29.99,'Las Vegas Stadium')");
    query3.exec();
    query3.prepare("INSERT into MLB_Stadium_Souviners ('Team', 'Item', 'Price', 'Stadium') VALUES ('Las Vegas Gamblers', 'Team jersey', 99.99,'Las Vegas Stadium')");
    query3.exec();

    ui->sucSailorLabel->setVisible(true);
    ui->sucSailorLabel->setText("Database Updated");
    ui->sucSailorButton->setVisible(false);
    num++;
    }


}

/**
 * @brief AdminWindow::on_priceChangeButton_clicked
 * @fn Used to change the price of an item
 */
void AdminWindow::on_priceChangeButton_clicked(){

    ui->comboTeams->setVisible(true);
    ui->cbLabel->setVisible(true);
    ui->comboPriceSouv->setVisible(true);
    ui->priceSouvLabel->setVisible(true);
    ui->priceLabel->setVisible(true);
    ui->priceEdit->setVisible(true);
    ui->priceGoButton->setVisible(true);

    ui->sucSailorLabel->setVisible(false);
    ui->dbLabel->setText(" ");
    ui->souvLabel->setVisible(false);
    ui->newSouvEdit->setVisible(false);
    ui->newSouvCombo->setVisible(false);
    ui->newSouvLabel->setVisible(false);
    ui->souvPriceLabel->setVisible(false);
    ui->newSouvPriceEdit->setVisible(false);
    ui->addNewSouv->setVisible(false);
    ui->delSouvCombo->setVisible(false);
    ui->delSouvLabel->setVisible(false);
    ui->delTeamCombo->setVisible(false);
    ui->delTeamLabel->setVisible(false);
    ui->delSouv->setVisible(false);
    ui->modColCombo->setVisible(false);
    ui->modColLabel->setVisible(false);
    ui->modStadCombo->setVisible(false);
    ui->modStadLabel->setVisible(false);
    ui->modGoButton->setVisible(false);
    ui->modEdit->setVisible(false);
    ui->modEditLabel->setVisible(false);
    ui->modModButton->setVisible(false);

    if(priceChangeCount <= 0){
    // Default first value
    ui->comboTeams->addItem("Show All");

    // Setting filepath for database
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");

    // Open the database
    if(m_db->isCreated()){
        ui->comboTeams->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->comboTeams->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query;            // SQL command to be executed (query.exec)
    QList<QString> places;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query.prepare("select \"Team Name\" from MLB_Info");

    // Execute and populate QList<string> with database info
    if(query.exec()){
        while(query.next()){    // Get next line
            places.push_back(query.value(0).toString());
        }
    }

    // Set menu labels
    while(!places.empty()) {
        ui->comboTeams->addItem(places.front());
        places.pop_front();
    }
    // separate spin boxes
    // Default first value
    ui->comboPriceSouv->addItem("Show All");

    // Open the database
    if(m_db->isCreated()){
        ui->comboPriceSouv->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->comboPriceSouv->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query2;            // SQL command to be executed (query.exec)
    QList<QString> souv;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query2.prepare("select item from MLB_Stadium_Souviners group by item");

    // Execute and populate QList<string> with database info
    if(query2.exec()){
        while(query2.next()){    // Get next line
            souv.push_back(query2.value(0).toString());
        }
    }
    // Set menu labels
    while(!souv.empty()) {
        ui->comboPriceSouv->addItem(souv.front());
        souv.pop_front();
    }
    }
    priceChangeCount++;
}

/**
 * @brief AdminWindow::on_priceGoButton_clicked
 * @fn Price Get price of item, provides db errors
 */
void AdminWindow::on_priceGoButton_clicked(){
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    double price = 0;
    if(m_db->isCreated()){
        ui->dbLabel->setText("Database opened");
    }   // If database can not be opened
    else{
        ui->dbLabel->setText("No Database");
    }

    if(ui->priceEdit->text().toDouble() > 0){
        price = ui->priceEdit->text().toDouble();
        QString souv = ui->comboPriceSouv->currentText();
        QString team = ui->comboTeams->currentText();
        QSqlQuery query;
        query.prepare("UPDATE MLB_Stadium_Souviners SET price = :price where item = :item AND team= :team");
        query.bindValue(":price", price);
        query.bindValue(":item", souv);
        query.bindValue(":team", team);
        query.exec();
        ui->priceEdit->setText(NULL);
        ui->dbLabel->setText("Price changed");
    }else{
        ui->dbLabel->setText("Price Not Changed");
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please Enter an Inter");
        messageBox.setFixedSize(500,200);
    }
}

/**
 * @brief AdminWindow::on_addNewSouvButton_clicked
 * @fn Used to add a new souvenir
 */
void AdminWindow::on_addNewSouvButton_clicked(){
    ui->souvLabel->setVisible(true);
    ui->newSouvEdit->setVisible(true);
    ui->newSouvCombo->setVisible(true);
    ui->newSouvLabel->setVisible(true);
    ui->souvPriceLabel->setVisible(true);
    ui->newSouvPriceEdit->setVisible(true);
    ui->addNewSouv->setVisible(true);

    ui->priceGoButton->setVisible(false);
    ui->sucSailorLabel->setVisible(false);
    ui->dbLabel->setText(" ");
    ui->comboTeams->setVisible(false);
    ui->cbLabel->setVisible(false);
    ui->comboPriceSouv->setVisible(false);
    ui->priceSouvLabel->setVisible(false);
    ui->priceLabel->setVisible(false);
    ui->priceEdit->setVisible(false);
    ui->delSouvCombo->setVisible(false);
    ui->delSouvLabel->setVisible(false);
    ui->delTeamCombo->setVisible(false);
    ui->delTeamLabel->setVisible(false);
    ui->delSouv->setVisible(false);
    ui->modColCombo->setVisible(false);
    ui->modColLabel->setVisible(false);
    ui->modStadCombo->setVisible(false);
    ui->modStadLabel->setVisible(false);
    ui->modGoButton->setVisible(false);
    ui->modEdit->setVisible(false);
    ui->modEditLabel->setVisible(false);
    ui->modModButton->setVisible(false);

    if(addNewSouvBCount<=0){

    // Default first value
    ui->newSouvCombo->addItem("Show All");

    // Setting filepath for database
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");

    // Open the database
    if(m_db->isCreated()){
        ui->newSouvCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->newSouvCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query;            // SQL command to be executed (query.exec)
    QList<QString> places;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query.prepare("select \"Team Name\" from MLB_Info");

    // Execute and populate QList<string> with database info
    if(query.exec()){
        while(query.next()){    // Get next line
            places.push_back(query.value(0).toString());
        }
    }

    // Set menu labels
    while(!places.empty()) {
        ui->newSouvCombo->addItem(places.front());
        places.pop_front();
    }
    }
    addNewSouvBCount++;
}

/**
 * @brief AdminWindow::on_addNewSouv_clicked
 * @fn When the button has been clicked, allows to add new souvenirs to db
 */
void AdminWindow::on_addNewSouv_clicked(){
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    double newPrice = 0;
    if(m_db->isCreated()){
        ui->dbLabel->setText("Database opened");
    }   // If database can not be opened
    else{
        ui->dbLabel->setText("No Database");
    }

    if(ui->newSouvPriceEdit->text().toDouble() > 0){
        newPrice = ui->newSouvPriceEdit->text().toDouble();
        QString stad;
        QString team = ui->newSouvCombo->currentText();
        QString newSouv = ui->newSouvEdit->text();

        QSqlQuery query;
        query.prepare("select Stadium from MLB_Stadium_Souviners where Team = :team");
        query.bindValue(":team", team);
        query.exec();
        if(query.next()){
                stad = query.value(0).toString();
        }

        QSqlQuery query2;
        query2.prepare("INSERT INTO MLB_Stadium_Souviners (Team, Item, Price, Stadium) VALUES (:team, :newSouv, :newPrice, :stad)");
        query2.bindValue(":newPrice", newPrice);
        query2.bindValue(":newSouv", newSouv);
        query2.bindValue(":team", team);
        query2.bindValue(":stad", stad);
        query2.exec();
        ui->priceEdit->setText(NULL);
        ui->dbLabel->setText("New Souviner Added");
    }else{
        ui->dbLabel->setText("New Souviner not added");
        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please Enter an Inter");
        messageBox.setFixedSize(500,200);
    }

    ui->delSouvCombo->clear();
    ui->comboPriceSouv->clear();

    // Load Distance database
    QSqlQuery queryA;            // SQL command to be executed (query.exec)
    QList<QString> souv;      // Database info as a Qlist<string

    // SQL Command to be executed
    queryA.prepare("select item from MLB_Stadium_Souviners group by item");

    // Execute and populate QList<string> with database info
    if(queryA.exec()){
        while(queryA.next()){    // Get next line
            souv.push_back(queryA.value(0).toString());
        }
    }
    // Set menu labels
    while(!souv.empty()) {
        ui->delSouvCombo->addItem(souv.front());
        ui->comboPriceSouv->addItem(souv.front());
        souv.pop_front();
    }
}

/**
 * @brief AdminWindow::on_delSouvButton_clicked
 * @fn Provides souvenir deletion function
 */
void AdminWindow::on_delSouvButton_clicked(){
    ui->delSouvCombo->setVisible(true);
    ui->delSouvLabel->setVisible(true);
    ui->delTeamCombo->setVisible(true);
    ui->delTeamLabel->setVisible(true);
    ui->delSouv->setVisible(true);

    ui->priceGoButton->setVisible(false);
    ui->sucSailorLabel->setVisible(false);
    ui->dbLabel->setText(" ");
    ui->comboTeams->setVisible(false);
    ui->cbLabel->setVisible(false);
    ui->comboPriceSouv->setVisible(false);
    ui->priceSouvLabel->setVisible(false);
    ui->priceLabel->setVisible(false);
    ui->priceEdit->setVisible(false);
    ui->souvLabel->setVisible(false);
    ui->newSouvEdit->setVisible(false);
    ui->newSouvCombo->setVisible(false);
    ui->newSouvLabel->setVisible(false);
    ui->souvPriceLabel->setVisible(false);
    ui->newSouvPriceEdit->setVisible(false);
    ui->addNewSouv->setVisible(false);
    ui->modColCombo->setVisible(false);
    ui->modColLabel->setVisible(false);
    ui->modStadCombo->setVisible(false);
    ui->modStadLabel->setVisible(false);
    ui->modGoButton->setVisible(false);
    ui->modEdit->setVisible(false);
    ui->modEditLabel->setVisible(false);
    ui->modModButton->setVisible(false);

    if(delSouvCount <= 0){
    // Default first value
    ui->delTeamCombo->addItem("Show All");

    // Setting filepath for database
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");

    // Open the database
    if(m_db->isCreated()){
        ui->delTeamCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->delTeamCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query;            // SQL command to be executed (query.exec)
    QList<QString> places;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query.prepare("select \"Team Name\" from MLB_Info");

    // Execute and populate QList<string> with database info
    if(query.exec()){
        while(query.next()){    // Get next line
            places.push_back(query.value(0).toString());
        }
    }

    // Set menu labels
    while(!places.empty()) {
        ui->delTeamCombo->addItem(places.front());
        places.pop_front();
    }
// separate spin boxes
    // Default first value
    ui->delSouvCombo->addItem("Show All");

    // Open the database
    if(m_db->isCreated()){
        ui->delSouvCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->delSouvCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query2;            // SQL command to be executed (query.exec)
    QList<QString> souv;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query2.prepare("select item from MLB_Stadium_Souviners group by item");

    // Execute and populate QList<string> with database info
    if(query2.exec()){
        while(query2.next()){    // Get next line
            souv.push_back(query2.value(0).toString());
        }
    }
    // Set menu labels
    while(!souv.empty()) {
        ui->delSouvCombo->addItem(souv.front());
        souv.pop_front();
    }
    }
   delSouvCount++;
}

/**
 * @brief AdminWindow::on_delSouv_clicked
 * @fn Secondary function for deleting souvenir items
 */
void AdminWindow::on_delSouv_clicked(){
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");

    if(m_db->isCreated()){
        ui->dbLabel->setText("Database opened");
    }   // If database can not be opened
    else{
        ui->dbLabel->setText("No Database");
    }
    QString souv = ui->delSouvCombo->currentText();
    QString team = ui->delTeamCombo->currentText();
    QSqlQuery query;
    query.prepare("DELETE FROM MLB_Stadium_Souviners WHERE Team=:team AND Item=:item");
    query.bindValue(":item", souv);
    query.bindValue(":team", team);
    query.exec();
    ui->dbLabel->setText(ui->delTeamCombo->currentText()+"'s "+ui->delSouvCombo->currentText()+" deleted");
}

/**
 * @brief AdminWindow::on_modifyInfoButton_clicked
 * @fn Used to change the info of a souvenir
 */
void AdminWindow::on_modifyInfoButton_clicked(){
    ui->modColCombo->setVisible(true);
    ui->modColLabel->setVisible(true);
    ui->modStadCombo->setVisible(true);
    ui->modStadLabel->setVisible(true);
    ui->modGoButton->setVisible(true);

    ui->priceGoButton->setVisible(false);
    ui->sucSailorLabel->setVisible(false);
    ui->dbLabel->setText(" ");
    ui->comboTeams->setVisible(false);
    ui->cbLabel->setVisible(false);
    ui->comboPriceSouv->setVisible(false);
    ui->priceSouvLabel->setVisible(false);
    ui->priceLabel->setVisible(false);
    ui->priceEdit->setVisible(false);
    ui->souvLabel->setVisible(false);
    ui->newSouvEdit->setVisible(false);
    ui->newSouvCombo->setVisible(false);
    ui->newSouvLabel->setVisible(false);
    ui->souvPriceLabel->setVisible(false);
    ui->newSouvPriceEdit->setVisible(false);
    ui->addNewSouv->setVisible(false);
    ui->delSouvCombo->setVisible(false);
    ui->delSouvLabel->setVisible(false);
    ui->delTeamCombo->setVisible(false);
    ui->delTeamLabel->setVisible(false);
    ui->delSouv->setVisible(false);
    ui->modEdit->setVisible(false);
    ui->modEditLabel->setVisible(false);
    ui->modModButton->setVisible(false);

    if(modCount <= 0){
    // Default first value
    ui->modStadCombo->addItem("Show All");

    // Setting filepath for database
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    // Open the database
    if(m_db->isCreated()){
        ui->modStadCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->modStadCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query;            // SQL command to be executed (query.exec)
    QList<QString> places;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query.prepare("select \"Stadium Name\"from MLB_Info");

    // Execute and populate QList<string> with database info
    if(query.exec()){
        while(query.next()){    // Get next line
            places.push_back(query.value(0).toString());
        }
    }

    // Set menu labels
    while(!places.empty()) {
        ui->modStadCombo->addItem(places.front());
        places.pop_front();
    }
    // separate spin boxes
    // Default first value
    ui->modColCombo->addItem("Show All");

    // Open the database
    if(m_db->isCreated()){
        ui->modColCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->modColCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query2;            // SQL command to be executed (query.exec)
    QList<QString> souv;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query2.prepare("PRAGMA table_info(MLB_Info)");

    // Execute and populate QList<string> with database info
    if(query2.exec()){
        while(query2.next()){    // Get next line
            souv.push_back(query2.value(1).toString());
        }
    }
    // Set menu labels
    while(!souv.empty()) {
        ui->modColCombo->addItem(souv.front());
        souv.pop_front();
    }
    }
    modCount++;
}

/**
 * @brief AdminWindow::on_modGoButton_clicked
 * @fn Modify the items souvenir data help function
 */
void AdminWindow::on_modGoButton_clicked(){
    ui->modColCombo->setVisible(false);
    ui->modColLabel->setVisible(false);
    ui->modStadCombo->setVisible(false);
    ui->modStadLabel->setVisible(false);
    ui->modGoButton->setVisible(false);
    ui->modEdit->setVisible(true);
    ui->modEditLabel->setVisible(true);
    ui->modModButton->setVisible(true);
    stadiumName=ui->modStadCombo->currentText();
    columnName=ui->modColCombo->currentText();
    ui->modEditLabel->setText("Modify "+stadiumName+"'s \n"+columnName+" to :");
}

/**
 * @brief AdminWindow::on_modModButton_clicked
 * @fn Modification helper function
 */
void AdminWindow::on_modModButton_clicked(){
    m_db = Database::getInstance();
    m_db->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    if(m_db->isCreated()){
        ui->dbLabel->setText("success");
    }   // If database can not be opened
    else{
        ui->dbLabel->setText("not1");
    }

    if(ui->modColCombo->currentText() == "Seating Capacity"){
        int cap = ui->modEdit->text().toInt();
        if(cap>0){
        QSqlQuery query;
        query.prepare("UPDATE MLB_Info SET \"Seating Capacity\" =:cap WHERE \"Stadium Name\"=:stad");
        query.bindValue(":cap", cap);
        query.bindValue(":stad", stadiumName);
        if(query.exec()){
            ui->dbLabel->setText("Seating Capacity modified");
        }else{
            ui->dbLabel->setText("not2");
        }
        }else{
            ui->dbLabel->setText("Seating Capacity not modified");
            QMessageBox messageBox;
            messageBox.critical(0,"Error","Please Enter an Integer");
            messageBox.setFixedSize(500,200);
        }

    }

    else{
        QString modData = ui->modEdit->text();
        if(ui->modColCombo->currentText() == "Team Name"){
            QSqlQuery query4;
            query4.prepare("UPDATE MLB_Stadium_Souviners SET \"Team\"=:modData WHERE \"Stadium Name\"=:stadium");
            query4.bindValue(":modData", modData);
            query4.bindValue(":stadium",stadiumName);
            if(query4.exec()){
                ui->dbLabel->setText(columnName+" modified");
            }else{
                ui->dbLabel->setText("not5");
            }
        }
        if(ui->modColCombo->currentText() == "Stadium Name"){
            QSqlQuery query4;
            query4.prepare("UPDATE MLB_Stadium_Souviners SET \"Stadium\"=:modData WHERE \"Stadium Name\"=:stadium");
            query4.bindValue(":modData", modData);
            query4.bindValue(":stadium",stadiumName);
            if(query4.exec()){
                ui->dbLabel->setText(columnName+" modified");
            }else{
                ui->dbLabel->setText("not5");
            }
            QSqlQuery query5;
            query5.prepare("UPDATE MLB_Distances SET \"Beginning Stadium\"=:modData WHERE \"Stadium Name\"=:stadium");
            query5.bindValue(":modData", modData);
            query5.bindValue(":stadium",stadiumName);
            if(query5.exec()){
                ui->dbLabel->setText(columnName+" modified");
            }else{
                ui->dbLabel->setText("not6");
            }
            QSqlQuery query6;
            query6.prepare("UPDATE MLB_Distances SET \"Ending Stadium\"=:modData WHERE \"Stadium Name\"=:stadium");
            query6.bindValue(":modData", modData);
            query6.bindValue(":stadium",stadiumName);
            if(query6.exec()){
                ui->dbLabel->setText(columnName+" modified");
            }else{
                ui->dbLabel->setText("not6");
            }
        }
        QSqlQuery query2;
        query2.prepare("UPDATE MLB_Info SET \""+columnName+"\"=:modData WHERE \"Stadium Name\"=:stadium");
        query2.bindValue(":modData", modData);
        query2.bindValue(":stadium",stadiumName);
        if(query2.exec()){
            ui->dbLabel->setText(columnName+" modified");
        }else{
            ui->dbLabel->setText("Error - Please select a Team/Option");
        }
    }

    //re configure 3 team and 1 stadium combo boxes
    ui->modStadCombo->clear();
    ui->comboTeams->clear();
    ui->delTeamCombo->clear();
    ui->newSouvCombo->clear();
    // Default first value
    ui->modStadCombo->addItem("Show All");

    // Open the database
    if(m_db->isCreated()){
        ui->modStadCombo->addItem("-----------------------");
    }   // If database can not be opened
    else{
        ui->modStadCombo->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
    }

    // Load Distance database
    QSqlQuery query;            // SQL command to be executed (query.exec)
    QList<QString> places;      // Database info as a Qlist<string>
    QSqlQuery query3;            // SQL command to be executed (query.exec)
    QList<QString> tea;      // Database info as a Qlist<string>

    // SQL Command to be executed
    query.prepare("select \"Stadium Name\"from MLB_Info");
    query3.prepare("select \"Team Name\"from MLB_Info");

    // Execute and populate QList<string> with database info
    if(query.exec()){
        while(query.next()){    // Get next line
            places.push_back(query.value(0).toString());
        }
    }
    if(query3.exec()){
        while(query3.next()){    // Get next line
            tea.push_back(query3.value(0).toString());
        }
    }

    // Set menu labels
//    while(!places.empty()) {
//        ui->modStadCombo->addItem(places.front());
//        places.pop_front();
//    }
    while(!places.empty()) {
        ui->comboTeams->addItem(places.front());
        ui->delTeamCombo->addItem(places.front());
        ui->newSouvCombo->addItem(places.front());
        ui->modStadCombo->addItem(places.front());
        places.pop_front();
    }
}

/**
 * @brief AdminWindow::on_done_clicked
 * @fn FOr ending the editing process
 */
void AdminWindow::on_done_clicked(){
        ui->priceGoButton->setVisible(false);
        ui->sucSailorLabel->setVisible(false);
        ui->dbLabel->setText(" ");
        ui->comboTeams->setVisible(false);
        ui->cbLabel->setVisible(false);
        ui->comboPriceSouv->setVisible(false);
        ui->priceSouvLabel->setVisible(false);
        ui->priceLabel->setVisible(false);
        ui->priceEdit->setVisible(false);
        ui->souvLabel->setVisible(false);
        ui->newSouvEdit->setVisible(false);
        ui->newSouvCombo->setVisible(false);
        ui->newSouvLabel->setVisible(false);
        ui->souvPriceLabel->setVisible(false);
        ui->newSouvPriceEdit->setVisible(false);
        ui->addNewSouv->setVisible(false);
        ui->delSouvCombo->setVisible(false);
        ui->delSouvLabel->setVisible(false);
        ui->delTeamCombo->setVisible(false);
        ui->delTeamLabel->setVisible(false);
        ui->delSouv->setVisible(false);
        ui->modColCombo->setVisible(false);
        ui->modColLabel->setVisible(false);
        ui->modStadCombo->setVisible(false);
        ui->modStadLabel->setVisible(false);
        ui->modGoButton->setVisible(false);
        ui->modEdit->setVisible(false);
        ui->modEditLabel->setVisible(false);
        ui->modModButton->setVisible(false);
}

/**
 * @brief AdminWindow::on_backLogin_clicked
 * @fn return to login window (from exiting Admin)
 */
void AdminWindow::on_backLogin_clicked(){
    login *l= new login;
    l->show();
    this->close();

}
