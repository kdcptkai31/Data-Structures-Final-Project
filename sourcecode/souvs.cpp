#include "souvs.h"
#include "ui_souvs.h"

souvs::souvs(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::souvs)
{
    ui->setupUi(this);
    // Default first value
    ui->comboBox->addItem("Show All");

    // Setting filepath for database
    m_db = Database::getInstance();
    m_db->SetDBPath("C:\\Users\\smitchell36\\Documents\\CS1D-Project2-master\\CS1D-Project2-master\\sourcecode\\database\\MLB.db");

    // Open the database
    if(m_db->isCreated()){
        ui->comboBox->addItem("-----------------------");
    }   // If database can not be opened
    else
    {
        ui->comboBox->addItem("XXXXXXXXXXXXXXXXXXXXXXX");
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
        ui->comboBox->addItem(places.front());
        places.pop_front();
    }
}

souvs::~souvs()
{
    delete ui;
}

void souvs::on_pushButton_view_clicked()
{
    ui->listWidget->clear();
    QSqlQuery query;
    QString name = ui->comboBox->currentText();
    qDebug() << name;
    query.prepare("SELECT * FROM MLB_Stadium_Souviners WHERE Team = :name");
    query.bindValue(":name", name);
    query.exec();
    while(query.next())
    {
        ui->listWidget->addItem(query.value(0).toString() + " " + query.value(1).toString() + " " + query.value(2).toString() + " " + query.value(3).toString());
    }
}
