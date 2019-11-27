#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStandardItemModel>
#include <QDir>
#include "database.h"
#include "graph.h"
#include "souvenirwindow.h"
#include "form.h"
#include "adminlogin.h"
#include "souvs.h"


namespace Ui {
class MainWindow;
}

/**
 * @brief The Stadium struct
 * The stadium structs holds all the needed data for an individual stadium.
 * This data is consistent to a stadium that is up to valid NFL stats
 */
struct Stadium {
    QString teamName;    //name of the nfl teal
    QString stadiumName; //name of the stadium
    int seatingCapacity; //the total seating capacity
    QString location;    //the location (city usually) of the stadium
    QString surfaceType; //the field surface type (grass, turf, etc)
    QString league;  //the conference division
    QString date;
    QString dist;
    QString typology;
    QString roofType;    //the roof type (solid, sliding)
};

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void LoadStadiumList();
    void LoadStadiumGraph();
    void PopulateTable();
    void UpdateTableConferences();
    void UpdateTableRoofTypes();
    void UpdateDistanceConferences();

    void UpdateCustomTripTable(QString nodeName, bool valid);
    void UpdateCompleteTripTable(QString nodeName);

    QVector<Stadium> GetConferenceList();
    QVector<Stadium> GetRoofTypeList();
    QVector<Stadium> DistancesToCenterField();
    int GetColumns();
    QWidget *prev;


private slots:

    void on_rbTN_clicked();

    void on_rbSN_clicked();

    void on_rbSC_clicked();

    void on_rbL_clicked();

    void on_rbC_clicked();

    void on_rbST_clicked();

    void on_rbSRT_clicked();

    void on_rbSP_clicked();

    void on_rbAC_clicked();

    void on_rbNC_clicked();

    void on_editTeamSearch_editingFinished();

    void on_rbO_clicked();

    void on_rbF_clicked();

    void on_rbR_clicked();

    void on_attPark_clicked();

    void on_angelStadium_clicked();

    void on_buschStadium_clicked();

    void on_chaseField_clicked();

    void on_citiField_clicked();

    void on_citizensBankPark_clicked();

    void on_comericaPark_clicked();

    void on_coorsField_clicked();

    void on_dodgerStadium_clicked();

    void on_fenwayPark_clicked();

    void on_glodeLifePark_clicked();

    void on_greatAmericaBallPark_clicked();

    void on_guranteedRateField_clicked();

    void on_kauffmanStadium_clicked();

    void on_marlinsPark_clicked();

    void on_millerPark_clicked();

    void on_minuteMaidPark_clicked();

    void on_nationalsPark_clicked();

    void on_oaklandAlamedaCountyColiseum_clicked();

    void on_oriolePark_clicked();

    void on_pncPark_clicked();

    void on_petcoPark_clicked();

    void on_progressiveField_clicked();

    void on_rogersCentre_clicked();

    void on_safecoField_clicked();

    void on_sunTrustPark_clicked();

    void on_targetField_clicked();

    void on_tropicanaField_clicked();

    void on_wrigleyField_clicked();

    void on_yankeeSadium_clicked();

    void on_customTripStartButton_clicked();

    void on_dfsButton_clicked();

    void on_bfsButton_clicked();

    void on_mstButton_clicked();

    void on_dijkstraButton_clicked();

    void on_completeTripButton_clicked();

    void on_totalCapacityButton_clicked();

    void on_pushButton_clicked();

    void on_rbTP_clicked();

    void on_rbDE_clicked();

    void on_pushButton_back_clicked();

    void on_pushButton_back_2_clicked();

    void on_pushButton_back_3_clicked();

    void on_lasVegasStadium_clicked();

    void on_pushButton_viewitems_clicked();

    void on_pushButton_viewitems_2_clicked();

    void on_pushButton_viewitems_3_clicked();

    void on_pushButton_2_clicked();

    void on_rbMax_clicked();

    void on_rbMin_clicked();

private:
    Ui::MainWindow *ui;

    /**
     * @brief database
     * @var database pointer
     */
    Database *database;

    QVector<Stadium> stadiumList;
    QVector<QString> customTripNameList;
    QVector<QString> completeTripNameList;
    Graph stadiumGraph;
    Form test;
    souvenirwindow shop;
    adminLogin *Login;
    int numStadiums;

    // Helper Functions

/*
 * ********** Radio Button Booleans For UI **********
 */

    // Bools For Information Tab

    bool rbTN;  // Radio Button Team Name
    bool rbSN;  // Radio Button Stadium Name
    bool rbSC;  // Radio Button Seating Capacity
    bool rbL;   // Radio Button Location
    bool rbC;   // Radio Button Conference
    bool rbST;  // Radio Button Surface Type
    bool rbSRT; // Radio Button Stadium Roof Type
    bool rbDT;  // Radio Button Distance
    bool rbDE=true;  // Radio Button Date
    bool rbTP=true;  // Radio Button Typology
    bool rbAC;  // Radio Button American Conference
    bool rbNC;  // Radio Button National Conference
    bool rbO;   // Radio Button Open Roof Type
    bool rbF;   // Radio Button Fixed Roof Type
    bool rbR;   // Radio Button Retractable Roof Type
    bool rbMax;
    bool rbMin;


    // Bools For Custom Trip Tab

    bool attPark;           // Radio Button
    bool angelStadium;                 // Radio Button
    bool buschStadium;
    bool chaseField;         // Radio Button
    bool citiField;            // Radio Button
    bool citizensBankPark;               // Radio Button
    bool comericaPark;         // Radio Button
    bool coorsField;                // Radio Button
    bool dodgerStadium;             // Radio Button
    bool fenwayPark;            // Radio Button
    bool glodeLifePark;            // Radio Button
    bool greatAmericaBallPark;               // Radio Button
    bool guranteedRateField;         // Radio Button
    bool kauffmanStadium;             // Radio Button
    bool lasVegasStadium;
    bool marlinsPark;              // Radio Button
    bool millerPark;             // Radio Button
    bool minuteMaidPark;               // Radio Button
    bool nationalsPark;    // Radio Button
    bool oaklandAlamedaCountyColiseum;          // Radio Button
    bool oriolePark;            // Radio Button
    bool pncPark;        // Radio Button
    bool petcoPark;              // Radio Button
    bool progressiveField;                 // Radio Button
    bool rogersCentre;      // Radio Button
    bool safecoField;           // Radio Button
    bool sunTrustPark;            // Radio Button
    bool targetField;             // Radio Button
    bool tropicanaField;             // Radio Button
    bool wrigleyField;     // Radio Button
    bool yankeeSadium;             // Radio Button
    bool rbUSBank;              // Radio Button
    bool rbUniversityPhoenix;   // Radio Button
};

#endif // MAINWINDOW_H
