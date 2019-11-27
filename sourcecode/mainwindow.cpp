#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "login.h"

/**
 * @brief MainWindow::MainWindow
 * @param parent
 * Spawns the main window and handles button assignment
 * and all basic UI functionalities
 */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    prev = parent;
    ui->setupUi(this);
    database = Database::getInstance();
    database->SetDBPath(QDir::currentPath() + "\\Database\\MLB.db");
    //ui->rbQualcomm->hide();
    LoadStadiumList();
    LoadStadiumGraph();

    stadiumGraph.SetMatrix();

    for (int index = 0; index < stadiumGraph.GetTotalNodes(); index++)
    {
        ui->completeTripComboBox->addItem(stadiumGraph.GetNodeName(index));
    }

    // Information Tab Radio Button Booleans

    rbTN = true;
    rbSN = true;
    rbSC = true;
    rbL = true;
    rbC = true;
    rbST = true;
    rbSRT = true;
    rbDT = true;
    rbAC = true;
    rbNC = true;
    rbO = true;
    rbF = true;
    rbR = true;

    // Custom Trip Tab Radio Button Booleans

    attPark = false;
    angelStadium = false;
    chaseField = false;
    chaseField = false;
    citiField = false;
    citizensBankPark = false;
    comericaPark = false;
    coorsField = false;
    dodgerStadium = false;
    fenwayPark = false;
    glodeLifePark = false;
    greatAmericaBallPark = false;
    guranteedRateField = false;
    kauffmanStadium = false;
    marlinsPark = false;
    millerPark = false;
    minuteMaidPark = false;
    nationalsPark = false;
    oaklandAlamedaCountyColiseum = false;
    oriolePark = false;
    pncPark = false;
    petcoPark = false;
    progressiveField = false;
    rogersCentre = false;
    safecoField = false;
    sunTrustPark = false;
    targetField = false;
    tropicanaField = false;
    wrigleyField = false;
    yankeeSadium = false;
    rbUSBank = false;
    rbUniversityPhoenix = false;

    PopulateTable();

}

/**
 * @brief MainWindow::~MainWindow
 */
MainWindow::~MainWindow()
{
    delete ui;
}

/**
 * @brief MainWindow::LoadStadiumList
 * @fn Loads the stadium list from the DB
 */
void MainWindow::LoadStadiumList()
{
    QSqlQuery* query = new QSqlQuery(database->db);
    query->prepare("SELECT * FROM MLB_Info");
    query->exec();
    qDebug() << "------- Loading Stadium List -------";
    while(query->next())
    {
        Stadium tempStadium;
        tempStadium.teamName = query->value(0).toString();
        tempStadium.stadiumName = query->value(1).toString();
        tempStadium.seatingCapacity = ((query->value(2).toString()).remove(QChar(','))).toInt();
        tempStadium.location = query->value(3).toString();
        tempStadium.surfaceType = query->value(4).toString();
        tempStadium.league = query->value(5).toString();
        tempStadium.date = query->value(6).toString();
        tempStadium.dist = query->value(7).toString();
        tempStadium.typology = query->value(8).toString();
        tempStadium.roofType = query->value(9).toString();
        //tempStadium.starPlayer = query->value(7).toString();
        stadiumList.push_back(tempStadium);
    }
    qDebug() << stadiumList.size();
    for (int i = 0; i < stadiumList.size(); i++)
    {
        qDebug() << stadiumList[i].teamName;
    }

}

/**
 * @brief MainWindow::LoadStadiumGraph
 * @fn Loads the stadium graph from the DB
 */
void MainWindow::LoadStadiumGraph()
{
    // Below Code Adds All Nodes To The Graph
    QSqlQuery* query = new QSqlQuery(database->db);
    query->prepare("SELECT * FROM MLB_Distances");
    query->exec();
    qDebug() << "------- Loading Stadium Graph -------";
    query->next();
    QString tempString = query->value(0).toString();
    stadiumGraph.AddNode(tempString);
    qDebug() << tempString;
    while(query->next())
    {
        if (tempString != query->value(0).toString())
        {
            tempString = query->value(0).toString();
            stadiumGraph.AddNode(tempString);
            qDebug() << tempString;
        }
    }

    // Below Code Adds All Edges To The Graph
    query = new QSqlQuery(database->db);
    query->prepare("SELECT * FROM MLB_Distances");
    query->exec();
    while(query->next())
    {
        stadiumGraph.AddEdge(query->value(0).toString(),query->value(1).toString(),(query->value(2).toString()).toInt());
    }
}

/**
 * @brief MainWindow::GetConferenceList
 * @return conference list
 * @fn Gets conference list from stadium vector
 * Gets the conference list by cycling through each
 * stadium in the stadium list and using the
 * conference getter method
 */
QVector<Stadium> MainWindow::GetConferenceList()
{
    QVector<Stadium> conferenceList;
    if (rbAC == true && rbNC == false)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].league == "American")
            {
                conferenceList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbAC == false && rbNC == true)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].league == "National")
            {
                conferenceList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbC == true && rbNC == true)
    {
        conferenceList = stadiumList;
    }
    return conferenceList;
}

/**
 * @brief MainWindow::GetRoofTypeList
 * @return roofTypeList
 * @fn returns the rooftype of the stadium list
 */
QVector<Stadium> MainWindow::GetRoofTypeList()
{
    QVector<Stadium> roofTypeList;
    if (rbO == true && rbF == false && rbR == false)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Open")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == false && rbF == true && rbR == false)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Fixed")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == false && rbF == false && rbR == true)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Retractable")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == false && rbF == true && rbR == true)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Fixed" || stadiumList[i].roofType == "Retractable")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == true && rbF == false && rbR == true)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Open" || stadiumList[i].roofType == "Retractable")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == true && rbF == true && rbR == false)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].roofType == "Open" || stadiumList[i].roofType == "Fixed")
            {
                roofTypeList.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbO == true && rbF == true && rbR == true)
    {
        roofTypeList = stadiumList;
    }
    return roofTypeList;
}

/**
 * @brief MainWindow::GetColumns
 * @return cols
 * @fn Calculates the number of columns for output
 */
int MainWindow::GetColumns()
{
    int cols = 0;
    if (rbTN == true)
    {
        cols++;
    }
    if (rbSN == true)
    {
        cols++;
    }
    if (rbSC == true)
    {
        cols++;
    }
    if (rbL == true)
    {
        cols++;
    }
    if (rbC == true)
    {
        cols++;
    }
    if (rbST == true)
    {
        cols++;
    }
    if (rbSRT == true)
    {
        cols++;
    }
    if (rbDT == true)
    {
        cols++;
    }
    if(rbDE == true)
    {
        cols++;
    }
    if(rbTP == true)
    {
        cols++;
    }

    return cols;
}

/**
 * @brief MainWindow::PopulateTable
 * @fn Populates the stadium list table
 */
void MainWindow::PopulateTable()
{
    ui->teamSearchError->hide();

    int rows, cols;
    rows = stadiumList.size();
    cols = GetColumns();
    QStandardItemModel *customModel = new QStandardItemModel(rows,cols,this);

    // The block below checks and sets the headers
    int index = 0;
    if (rbTN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Team Name")));
        index++;
    }
    if (rbSN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Name")));
        index++;
    }
    if (rbSC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Seating Capacity")));
        index++;
    }
    if (rbL == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Location")));
        index++;
    }
    if (rbC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("League")));
        index++;
    }
    if (rbST == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Surface Type")));
        index++;
    }
    if (rbSRT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Roof Type")));
        index++;
    }
    if (rbDT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Distance")));
        index++;
    }

    if (rbTP == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Typology")));
        index++;
    }
    if (rbDE == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Date")));
        index++;
    }

    //must check each columns in stadiumList
    for (int i = 0; i < stadiumList.size(); i++)
    {
        index = 0;
        if (rbTN == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].teamName));
            index++;
        }
        if (rbSN == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].stadiumName));
            index++;
        }
        if (rbSC == true)
        {
            customModel->setItem(i, index, new QStandardItem((QString::number(stadiumList[i].seatingCapacity)).insert(2,',')));
            index++;
        }
        if (rbL == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].location));
            index++;
        }
        if (rbC == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].league));
            index++;
        }
        if (rbST == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].surfaceType));
            index++;
        }
        if (rbSRT == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].roofType));
            index++;
        }
        if (rbDT == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].dist));
            index++;
        }
        if (rbTP == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].typology));
            index++;
        }
        if (rbDE == true)
        {
            customModel->setItem(i, index, new QStandardItem(stadiumList[i].date));
            index++;
        }

    }
    ui->mainTableView->setModel(customModel);
    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->setSortingEnabled(true);
}

/**
 * @brief MainWindow::UpdateTableConferences
 * @fn Updates the Conference List table
 */
void MainWindow::UpdateTableConferences()
{
    int rows, cols;
    QVector<Stadium> conferenceList = GetConferenceList();
    rows = conferenceList.size();
    cols = GetColumns();
    QStandardItemModel *customModel = new QStandardItemModel(rows,cols,this);

    // The block below checks and sets the headers
    int index = 0;
    if (rbTN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Team Name")));
        index++;
    }
    if (rbSN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Name")));
        index++;
    }
    if (rbSC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Seating Capacity")));
        index++;
    }
    if (rbL == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Location")));
        index++;
    }
    if (rbC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("League")));
        index++;
    }
    if (rbST == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Surface Type")));
        index++;
    }
    if (rbSRT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Roof Type")));
        index++;
    }
    if (rbDT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Distance to Center Field")));
        index++;
    }
    if (rbDE == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Date")));
        index++;
    }
    if (rbTP == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Typology")));
        index++;
    }

    //simple cycle through conference list and create a new column if needed
    for (int i = 0; i < conferenceList.size(); i++)
    {
        index = 0;
        if (rbTN == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].teamName));
            index++;
        }
        if (rbSN == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].stadiumName));
            index++;
        }
        if (rbSC == true)
        {
            customModel->setItem(i, index, new QStandardItem((QString::number(conferenceList[i].seatingCapacity)).insert(2,',')));
            index++;
        }
        if (rbL == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].location));
            index++;
        }
        if (rbC == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].league));
            index++;
        }
        if (rbST == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].surfaceType));
            index++;
        }
        if (rbSRT == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].roofType));
            index++;
        }
        if (rbDT == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].dist));
            index++;
        }
        if (rbDE == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].date));
            index++;
        }
        if (rbTP == true)
        {
            customModel->setItem(i, index, new QStandardItem(conferenceList[i].typology));
            index++;
        }
    }
    ui->mainTableView->setModel(customModel);
    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->setSortingEnabled(true);
}

/**
 * @brief MainWindow::UpdateTableRoofTypes
 * @fn Updates Roof Type column when selected
 */
void MainWindow::UpdateTableRoofTypes()
{
    int rows, cols;
    QVector<Stadium> roofTypeList = GetRoofTypeList();
    rows = roofTypeList.size();
    cols = GetColumns();
    QStandardItemModel *customModel = new QStandardItemModel(rows,cols,this);

    // The block below checks and sets the headers
    int index = 0;
    if (rbTN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Team Name")));
        index++;
    }
    if (rbSN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Name")));
        index++;
    }
    if (rbSC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Seating Capacity")));
        index++;
    }
    if (rbL == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Location")));
        index++;
    }
    if (rbC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Conference")));
        index++;
    }
    if (rbST == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Surface Type")));
        index++;
    }
    if (rbSRT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Roof Type")));
        index++;
    }
    if (rbDT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Distance")));
        index++;
    }
    if (rbTP == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Typology")));
        index++;
    }
    if (rbDE == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Date")));
        index++;
    }
    for (int i = 0; i < roofTypeList.size(); i++)
    {
        index = 0;
        if (rbTN == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].teamName));
            index++;
        }
        if (rbSN == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].stadiumName));
            index++;
        }
        if (rbSC == true)
        {
            customModel->setItem(i, index, new QStandardItem((QString::number(roofTypeList[i].seatingCapacity)).insert(2,',')));
            index++;
        }
        if (rbL == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].location));
            index++;
        }
        if (rbC == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].league));
            index++;
        }
        if (rbST == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].surfaceType));
            index++;
        }
        if (rbSRT == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].roofType));
            index++;
        }
        if (rbDT == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].dist));
            index++;
        }
        if (rbTP == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].typology));
            index++;
        }
        if (rbDE == true)
        {
            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].date));
            index++;
        }

//        if (rbSP == true)
//        {
//            customModel->setItem(i, index, new QStandardItem(roofTypeList[i].starPlayer));
//            index++;
//        }
    }
    ui->mainTableView->setModel(customModel);
    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->setSortingEnabled(true);
}

/**
 * @brief MainWindow::on_editTeamSearch_editingFinished
 * Basic function to support team searching via search option
 */
void MainWindow::on_editTeamSearch_editingFinished()
{
    bool found = false;
    int searchedIndex = 0;

    //keep checking for the teamname needed until it's found
    for (int index = 0; index < stadiumList.size(); index++)
    {
        if (stadiumList[index].teamName == ui->editTeamSearch->text())
        {
            searchedIndex = index;
            found = true;
        }
    }

    if(found) //begin displaying team information
    {
        ui->teamSearchError->hide();
        QStandardItemModel *customModel = new QStandardItemModel(1,8,this);

        customModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Team Name")));
        customModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Stadium Name")));
        customModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Seating Capacity")));
        customModel->setHorizontalHeaderItem(3, new QStandardItem(QString("Location")));
        customModel->setHorizontalHeaderItem(4, new QStandardItem(QString("Conference")));
        customModel->setHorizontalHeaderItem(5, new QStandardItem(QString("Surface Type")));
        customModel->setHorizontalHeaderItem(6, new QStandardItem(QString("Stadium Roof Type")));
        customModel->setHorizontalHeaderItem(7, new QStandardItem(QString("Distance")));
        customModel->setItem(searchedIndex, 0, new QStandardItem(stadiumList[searchedIndex].teamName));
        customModel->setItem(searchedIndex, 1, new QStandardItem(stadiumList[searchedIndex].stadiumName));
        customModel->setItem(searchedIndex, 2, new QStandardItem((QString::number(stadiumList[searchedIndex].seatingCapacity)).insert(2,',')));
        customModel->setItem(searchedIndex, 3, new QStandardItem(stadiumList[searchedIndex].location));
        customModel->setItem(searchedIndex, 4, new QStandardItem(stadiumList[searchedIndex].league));
        customModel->setItem(searchedIndex, 5, new QStandardItem(stadiumList[searchedIndex].surfaceType));
        customModel->setItem(searchedIndex, 6, new QStandardItem(stadiumList[searchedIndex].roofType));
        customModel->setItem(searchedIndex, 7, new QStandardItem(stadiumList[searchedIndex].dist));
        customModel->setItem(searchedIndex, 8, new QStandardItem(stadiumList[searchedIndex].date));
        customModel->setItem(searchedIndex, 9, new QStandardItem(stadiumList[searchedIndex].typology));
        ui->mainTableView->setModel(customModel);
        ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
        ui->mainTableView->setSortingEnabled(true);
    }
    else
    {
        ui->teamSearchError->show();
    }
}

/**
 * @brief MainWindow::UpdateCustomTripTable
 * @param nodeName
 * @param valid
 * @fn Updates the custom trip table
 */
void MainWindow::UpdateCustomTripTable(QString nodeName, bool valid)
{
    QStandardItemModel *customModel = new QStandardItemModel(0,1,this);
    customModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Stadium Name")));

    if(valid)
    {
        customTripNameList.push_back(nodeName);
        for (int index = 0; index < customTripNameList.length(); index++)
        {
            customModel->setItem(index, 0, new QStandardItem(customTripNameList[index]));
        }
    }
    else
    {
        int index = 0;
        bool found;

        while (index < customTripNameList.length() && !found)
        {
            if (customTripNameList[index] == nodeName)
            {
                customTripNameList.remove(index);
                found = true;
            }
            index++;
        }
        for (int index = 0; index < customTripNameList.length(); index++)
        {
            customModel->setItem(index, 0, new QStandardItem(customTripNameList[index]));
        }
    }
    ui->customTripTableView->setModel(customModel);
    ui->customTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

/**
 * @brief MainWindow::UpdateCompleteTripTable
 * @param nodeName
 * @fn Update the WHOLE trip table
 */
void MainWindow::UpdateCompleteTripTable(QString nodeName)
{
    QStandardItemModel *customModel = new QStandardItemModel(0,1,this);
    customModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Stadium Name")));

    completeTripNameList.push_back(nodeName);
    for (int index = 0; index < completeTripNameList.length(); index++)
    {
        customModel->setItem(index, 0, new QStandardItem(completeTripNameList[index]));
    }
    ui->completeTripTableView->setModel(customModel);
    ui->completeTripTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

/*
 * ********** Radio Buttons Slots For Sort Types Information Tab **********
 */

/**
 * @brief MainWindow::on_rbTN_clicked
 */
void MainWindow::on_rbTN_clicked()
{
    rbTN = !rbTN;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbSN_clicked
 */
void MainWindow::on_rbSN_clicked()
{
    rbSN = !rbSN;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbSC_clicked
 */
void MainWindow::on_rbSC_clicked()
{
    rbSC = !rbSC;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbL_clicked
 */
void MainWindow::on_rbL_clicked()
{
    rbL = !rbL;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbC_clicked
 */
void MainWindow::on_rbC_clicked()
{
    rbC = !rbC;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbST_clicked
 */
void MainWindow::on_rbST_clicked()
{
    rbST = !rbST;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbSRT_clicked
 */
void MainWindow::on_rbSRT_clicked()
{
    rbSRT = !rbSRT;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbSP_clicked
 */
void MainWindow::on_rbSP_clicked()
{
    rbDT = !rbDT;
    PopulateTable();
}

/**
 * @brief MainWindow::on_rbAC_clicked
 */
void MainWindow::on_rbAC_clicked()
{
    rbAC = !rbAC;
    UpdateTableConferences();
}

/**
 * @brief MainWindow::on_rbNC_clicked
 */
void MainWindow::on_rbNC_clicked()
{
    rbNC = !rbNC;
    UpdateTableConferences();
}

/**
 * @brief MainWindow::on_rbO_clicked
 */
void MainWindow::on_rbO_clicked()
{
    rbO = !rbO;
    UpdateTableRoofTypes();
}

/**
 * @brief MainWindow::on_rbF_clicked
 */
void MainWindow::on_rbF_clicked()
{
    rbF = !rbF;
    UpdateTableRoofTypes();
}

/**
 * @brief MainWindow::on_rbR_clicked
 */
void MainWindow::on_rbR_clicked()
{
    rbR = !rbR;
    UpdateTableRoofTypes();
}

/*
 * ********** Radio Buttons Slots For Custom Trip **********
 */

/**
 * @brief MainWindow::on_rbArrowhead_clicked
 */
void MainWindow::on_attPark_clicked()
{
    if (ui->attPark->isChecked())
    {
        attPark = true;
    }
    else
    {
        attPark = false;
    }
    UpdateCustomTripTable(ui->attPark->text(), attPark);
}

/**
 * @brief MainWindow::on_rbATT_clicked
 */
void MainWindow::on_angelStadium_clicked()
{
    if (ui->angelStadium->isChecked())
    {
        angelStadium = true;
    }
    else
    {
        angelStadium = false;
    }
    UpdateCustomTripTable(ui->angelStadium->text(), angelStadium);
}

/**
 * @brief MainWindow::on_rbBankAmerica_clicked
 */
void MainWindow::on_buschStadium_clicked()
{
    if (ui->buschStadium->isChecked())
    {
        buschStadium = true;
    }
    else
    {
        buschStadium = false;
    }
    UpdateCustomTripTable(ui->buschStadium->text(), buschStadium);
}

/**
 * @brief MainWindow::on_rbCenturyLink_clicked
 */
void MainWindow::on_chaseField_clicked()
{
    if (ui->chaseField->isChecked())
    {
        chaseField = true;
    }
    else
    {
        chaseField = false;
    }
    UpdateCustomTripTable(ui->chaseField->text(), chaseField);
}

/**
 * @brief MainWindow::on_rbEverBank_clicked
 */
void MainWindow::on_citiField_clicked()
{
    if (ui->citiField->isChecked())
    {
        citiField = true;
    }
    else
    {
        citiField = false;
    }
    UpdateCustomTripTable(ui->citiField->text(), citiField);
}

/**
 * @brief MainWindow::on_rbFedEx_clicked
 */
void MainWindow::on_citizensBankPark_clicked()
{
    if (ui->citizensBankPark->isChecked())
    {
        citizensBankPark = true;
    }
    else
    {
        citizensBankPark = false;
    }
    UpdateCustomTripTable(ui->citizensBankPark->text(), citizensBankPark);
}

/**
 * @brief MainWindow::on_rbFirstEnergy_clicked
 */
void MainWindow::on_comericaPark_clicked()
{
    if (ui->comericaPark->isChecked())
    {
        comericaPark = true;
    }
    else
    {
        comericaPark = false;
    }
    UpdateCustomTripTable(ui->comericaPark->text(), comericaPark);
}

/**
 * @brief MainWindow::on_rbFord_clicked
 */
void MainWindow::on_coorsField_clicked()
{
    if (ui->coorsField->isChecked())
    {
        coorsField = true;
    }
    else
    {
        coorsField = false;
    }
    UpdateCustomTripTable(ui->coorsField->text(), coorsField);
}

/**
 * @brief MainWindow::on_rbGeorgia_clicked
 */
void MainWindow::on_dodgerStadium_clicked()
{
    if (ui->dodgerStadium->isChecked())
    {
        dodgerStadium = true;
    }
    else
    {
        dodgerStadium = false;
    }
    UpdateCustomTripTable(ui->dodgerStadium->text(), dodgerStadium);
}

/**
 * @brief MainWindow::on_rbGillette_clicked
 */
void MainWindow::on_fenwayPark_clicked()
{
    if (ui->fenwayPark->isChecked())
    {
        fenwayPark = true;
    }
    else
    {
        fenwayPark = false;
    }
    UpdateCustomTripTable(ui->fenwayPark->text(), fenwayPark);
}

/**
 * @brief MainWindow::on_rbHardRock_clicked
 */
void MainWindow::on_glodeLifePark_clicked()
{
    if (ui->glodeLifePark->isChecked())
    {
        glodeLifePark = true;
    }
    else
    {
        glodeLifePark = false;
    }
    UpdateCustomTripTable(ui->glodeLifePark->text(), glodeLifePark);
}

/**
 * @brief MainWindow::on_rbHeinz_clicked
 */
void MainWindow::on_greatAmericaBallPark_clicked()
{
    if (ui->greatAmericaBallPark->isChecked())
    {
        greatAmericaBallPark = true;
    }
    else
    {
        greatAmericaBallPark = false;
    }
    UpdateCustomTripTable(ui->greatAmericaBallPark->text(), greatAmericaBallPark);
}

/**
 * @brief MainWindow::on_rbRalphWilson_clicked
 */
void MainWindow::on_guranteedRateField_clicked()
{
    if (ui->guranteedRateField->isChecked())
    {
        guranteedRateField = true;
    }
    else
    {
        guranteedRateField = false;
    }
    UpdateCustomTripTable("Guaranteed Rate Field", guranteedRateField);
}

/**
 * @brief MainWindow::on_rbMetlife_clicked
 */
void MainWindow::on_kauffmanStadium_clicked()
{
    if (ui->kauffmanStadium->isChecked())
    {
        kauffmanStadium = true;
    }
    else
    {
        kauffmanStadium = false;
    }
    UpdateCustomTripTable(ui->kauffmanStadium->text(), kauffmanStadium);
}
/**
 * @brief MainWindow::on_lasVegasStadium_clicked
 */
void MainWindow::on_lasVegasStadium_clicked()
{
    if (ui->lasVegasStadium->isChecked())
        lasVegasStadium = true;
    else
        lasVegasStadium = false;

    UpdateCustomTripTable(ui->lasVegasStadium->text(), lasVegasStadium);
}


/**
 * @brief MainWindow::on_rbMTBank_clicked
 */
void MainWindow::on_marlinsPark_clicked()
{
    if (ui->marlinsPark->isChecked())
    {
        marlinsPark = true;
    }
    else
    {
        marlinsPark = false;
    }
    UpdateCustomTripTable(ui->marlinsPark->text(), marlinsPark);
}

/**
 * @brief MainWindow::on_rbLambeau_clicked
 */
void MainWindow::on_millerPark_clicked()
{
    if (ui->millerPark->isChecked())
    {
        millerPark = true;
    }
    else
    {
        millerPark = false;
    }
    UpdateCustomTripTable(ui->millerPark->text(), millerPark);
}

/**
 * @brief MainWindow::on_rbLevis_clicked
 */
void MainWindow::on_minuteMaidPark_clicked()
{
    if (ui->minuteMaidPark->isChecked())
    {
        minuteMaidPark = true;
    }
    else
    {
        minuteMaidPark = false;
    }
    UpdateCustomTripTable(ui->minuteMaidPark->text(), minuteMaidPark);
}

/**
 * @brief MainWindow::on_rbLincolnFinancial_clicked
 */
void MainWindow::on_nationalsPark_clicked()
{
    if (ui->nationalsPark->isChecked())
    {
        nationalsPark = true;
    }
    else
    {
        nationalsPark = false;
    }
    UpdateCustomTripTable(ui->nationalsPark->text(), nationalsPark);
}

/**
 * @brief MainWindow::on_rbLosAngeles_clicked
 */
void MainWindow::on_oaklandAlamedaCountyColiseum_clicked()
{
    if (ui->oaklandAlamedaCountyColiseum->isChecked())
    {
        oaklandAlamedaCountyColiseum = true;
    }
    else
    {
        oaklandAlamedaCountyColiseum = false;
    }
    UpdateCustomTripTable("Oakland–Alameda County Coliseum ", oaklandAlamedaCountyColiseum);
}

/**
 * @brief MainWindow::on_rbLucasOil_clicked
 */
void MainWindow::on_oriolePark_clicked()
{
    if (ui->oriolePark->isChecked())
    {
        oriolePark = true;
    }
    else
    {
        oriolePark = false;
    }
    UpdateCustomTripTable(ui->oriolePark->text(), oriolePark);
}

/**
 * @brief MainWindow::on_rbMercedesBenz_clicked
 */
void MainWindow::on_pncPark_clicked()
{
    if (ui->pncPark->isChecked())
    {
        pncPark = true;
    }
    else
    {
        pncPark = false;
    }
    UpdateCustomTripTable(ui->pncPark->text(), pncPark);
}

/**
 * @brief MainWindow::on_rbNissan_clicked
 */
void MainWindow::on_petcoPark_clicked()
{
    if (ui->petcoPark->isChecked())
    {
        petcoPark = true;
    }
    else
    {
        petcoPark = false;
    }
    UpdateCustomTripTable(ui->petcoPark->text(), petcoPark);
}

/**
 * @brief MainWindow::on_rbNRG_clicked
 */
void MainWindow::on_progressiveField_clicked()
{
    if (ui->progressiveField->isChecked())
    {
        progressiveField = true;
    }
    else
    {
        progressiveField = false;
    }
    UpdateCustomTripTable(ui->progressiveField->text(), progressiveField);
}

/**
 * @brief MainWindow::on_rbOaklandAlameda_clicked
 */
void MainWindow::on_rogersCentre_clicked()
{
    if (ui->rogersCentre->isChecked())
    {
        rogersCentre = true;
    }
    else
    {
        rogersCentre = false;
    }
    UpdateCustomTripTable(ui->rogersCentre->text(), rogersCentre);
}

/**
 * @brief MainWindow::on_rbPaulBrown_clicked
 */
void MainWindow::on_safecoField_clicked()
{
    if (ui->safecoField->isChecked())
    {
        safecoField = true;
    }
    else
    {
        safecoField = false;
    }
    UpdateCustomTripTable("SafeCo Field", safecoField);
}

/**
 * @brief MainWindow::on_rbQualcomm_clicked
 */
void MainWindow::on_sunTrustPark_clicked()
{
    if (ui->sunTrustPark->isChecked())
    {
        sunTrustPark = true;
    }
    else
    {
        sunTrustPark = false;
    }
    UpdateCustomTripTable("Sun Trust Park", sunTrustPark);
}

/**
 * @brief MainWindow::on_rbRaymond_clicked
 */
void MainWindow::on_targetField_clicked()
{
    if (ui->targetField->isChecked())
    {
        targetField = true;
    }
    else
    {
        targetField = false;
    }
    UpdateCustomTripTable(ui->targetField->text(), targetField);
}

/**
 * @brief MainWindow::on_rbSoldier_clicked
 */
void MainWindow::on_tropicanaField_clicked()
{
    if (ui->tropicanaField->isChecked())
    {
        tropicanaField = true;
    }
    else
    {
        tropicanaField = false;
    }
    UpdateCustomTripTable(ui->tropicanaField->text(), tropicanaField);
}

/**
 * @brief MainWindow::on_rbSportsAuthority_clicked
 */
void MainWindow::on_wrigleyField_clicked()
{
    if (ui->wrigleyField->isChecked())
    {
        wrigleyField = true;
    }
    else
    {
        wrigleyField = false;
    }
    UpdateCustomTripTable(ui->wrigleyField->text(), wrigleyField);
}

/**
 * @brief MainWindow::on_rbStubHub_clicked
 */
void MainWindow::on_yankeeSadium_clicked()
{
    if (ui->yankeeSadium->isChecked())
    {
        yankeeSadium = true;
    }
    else
    {
        yankeeSadium = false;
    }
    UpdateCustomTripTable(ui->yankeeSadium->text(), yankeeSadium);
}


/**
 * @brief MainWindow::on_customTripStartButton_clicked
 */
void MainWindow::on_customTripStartButton_clicked()
{
    int distance = 0;
    for (int index = 0; index < customTripNameList.size()-1; index++)
    {
        distance += stadiumGraph.PerformFromToDijkstra(stadiumGraph.GetVertex(customTripNameList[index]),stadiumGraph.GetVertex(customTripNameList[index+1]));
        qDebug() << customTripNameList[index] << customTripNameList[index+1] << stadiumGraph.PerformFromToDijkstra(stadiumGraph.GetVertex(customTripNameList[index]),stadiumGraph.GetVertex(customTripNameList[index+1]));
    }

qDebug() << "WORKING!!\n";
    ui->customTripDistance->setText("Total Trip Distance: " + (QString::number(distance)));
    //customTripNameList;
    //shop.LoadWindow(customTripNameList);
}

/**
 * @brief MainWindow::on_dfsButton_clicked
 */
void MainWindow::on_dfsButton_clicked()
{
    ui->listWidget_trips->clear();
    QVector<QString> stadiums;
    qDebug() << "------------ Starting DFS ------------";
    stadiumGraph.DFS("Target Field", stadiums);
    qDebug() << "dfs size is: " << stadiums.size();
    for(int i=0;i<stadiums.size();i++)
    {
        ui->listWidget_trips->addItem(stadiums[i]);
    }
    ui->dfsLabel->setText("DFS at Target Field: " + (QString::number(stadiumGraph.GetDistance())));
    ui->label_dist->setText("Total Distance Traveled: " + (QString::number(stadiumGraph.GetDistance())));
}

/**
 * @brief MainWindow::on_bfsButton_clicked
 */
void MainWindow::on_bfsButton_clicked()
{
    ui->listWidget_trips->clear();
    QVector<QString> stadiums;
    qDebug() << "------------ Starting BFS ------------";
    stadiumGraph.BFS("Citi Field", stadiums);
    for(int i=0;i<stadiums.size();i++)
        ui->listWidget_trips->addItem(stadiums[i]);
    ui->bfsLabel->setText("BFS at Citi Field: " + (QString::number(stadiumGraph.GetDistance())));
    ui->label_dist->setText("Total Distance Traveled: " + (QString::number(stadiumGraph.GetDistance())));
}

/**
 * @brief MainWindow::on_mstButton_clicked
 */
void MainWindow::on_mstButton_clicked()
{
    qDebug() << "------------ Starting MST ------------";
    ui->mstLabel->setText("MST: " + (QString::number(stadiumGraph.PrimMST())));
    ui->label_dist->setText("MST: " + (QString::number(stadiumGraph.PrimMST())));
}

void MainWindow::on_dijkstraButton_clicked()
{
    ui->listWidget_trips->clear();
    QVector<QString> stadiums;
    qDebug() << "------------ Starting Dijkstra ------------";
    ui->dijkstraLabel->setText("Dijkstra at Dodger Stadium : " + (QString::number(stadiumGraph.PerformCompleteDijkstra(stadiumGraph.GetVertex("Dodger Stadium"), 0, stadiums))));
    for(int i=0; i<stadiums.size();i++)
        ui->listWidget_trips->addItem(stadiums[i]);
    ui->label_dist->setText("Total Distance Traveled: " + (QString::number(stadiumGraph.PerformCompleteDijkstra(stadiumGraph.GetVertex("Dodger Stadium"), 0, stadiums))));

}

/**
 * @brief MainWindow::on_completeTripButton_clicked
 */
void MainWindow::on_completeTripButton_clicked()
{
    QVector<QString> stadiums;
    ui->completeTripDistance->setText("Total Trip Distance: " + (QString::number(stadiumGraph.PerformCompleteDijkstra(stadiumGraph.GetVertex(ui->completeTripComboBox->currentText()), 0, stadiums))));
    completeTripNameList.clear();
    qDebug() << "Total - " << stadiumGraph.GetTotalNodes();
    auto x = stadiumGraph.GetVisitedNodes();
    for (int index = 0; index < stadiumGraph.GetVisitedNodes().size(); index++)
    {
        qDebug() << x[index];
        UpdateCompleteTripTable(stadiumGraph.GetVisitedNodes()[index]);
    }

}

/**
 * @brief MainWindow::on_totalCapacityButton_clicked
 * @fn Calculates total capacity when button selected
 */
void MainWindow::on_totalCapacityButton_clicked()
{
    int totalCapacity = 0;
    bool singular = true;
    bool accountedFor = false;

    //run through each stadium
    for (int i = 0; i < stadiumList.size(); i++)
    {
        singular = true;
        int j = 0;

        while (j < stadiumList.size() && singular)
        {
            if (stadiumList[i].teamName != stadiumList[j].teamName && stadiumList[i].stadiumName == stadiumList[j].stadiumName)
            {
                singular = false;
            }
            j++;
        }

        if (singular)
        {
            totalCapacity += stadiumList[i].seatingCapacity;
        }
        else if(!accountedFor)
        {
                totalCapacity += stadiumList[i].seatingCapacity;
                accountedFor = true;
        }
    }
    ui->totalCapacityLabel->setText("Total Cap: " + (QString::number(totalCapacity)));
}

void MainWindow::on_pushButton_clicked()
{
    //Custom
    if(customTripNameList.size() == 0){

        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please select the stadium(s) to purchase souvenirs from!");
        messageBox.setFixedSize(500,200);

    }else{

        shop.LoadWindow(customTripNameList);
        shop.show();

    }

}

void MainWindow::on_pushButton_2_clicked()
{
    //Complete
    if(completeTripNameList.size() == 0){

        QMessageBox messageBox;
        messageBox.critical(0,"Error","Please start a complete trip first!");
        messageBox.setFixedSize(500,200);

    }else{

        shop.LoadWindow(completeTripNameList);
        shop.show();

    }

}


void MainWindow::on_rbTP_clicked()
{
    rbTP = !rbTP;
    PopulateTable();
}

void MainWindow::on_rbDE_clicked()
{
    rbDE = !rbDE;
    PopulateTable();
}

void MainWindow::on_pushButton_back_clicked()
{
    login *back = new login();
    back->show();
    this->close();
}

void MainWindow::on_pushButton_back_2_clicked()
{
    login *back = new login();
        back->show();
        this->close();

}

void MainWindow::on_pushButton_back_3_clicked()
{
    login *back = new login();
        back->show();
        this->close();
}

void MainWindow::on_pushButton_viewitems_clicked()
{
    souvs *items = new souvs();
    items->show();
}

void MainWindow::on_pushButton_viewitems_2_clicked()
{
    souvs *items = new souvs();
    items->show();
}

void MainWindow::on_pushButton_viewitems_3_clicked()
{
    souvs *items = new souvs();
    items->show();
}


void MainWindow::on_rbMax_clicked()
{
    rbMax = !rbMax;
    UpdateDistanceConferences();
}

void MainWindow::on_rbMin_clicked()
{
    rbMin = !rbMin;
    UpdateDistanceConferences();
}



QVector<Stadium> MainWindow::DistancesToCenterField()
{
    QVector<Stadium> distances;
    if (rbMax == true && rbMin == false)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].dist == "420 feet (128m)")
            {
                distances.push_back(stadiumList[i]);
            }
        }
    }
    else if (rbMax == false && rbMin == true)
    {
        for (int i = 0; i < stadiumList.size(); i++)
        {
            if (stadiumList[i].dist == "396 feet (121m)")
            {
                distances.push_back(stadiumList[i]);
            }
        }
    }
    return distances;
}
void MainWindow::UpdateDistanceConferences()
{
    int rows, cols;
    QVector<Stadium> distances = DistancesToCenterField();
    rows = distances.size();
    cols = GetColumns();
    QStandardItemModel *customModel = new QStandardItemModel(rows,cols,this);

    // The block below checks and sets the headers
    int index = 0;
    if (rbTN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Team Name")));
        index++;
    }
    if (rbSN == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Name")));
        index++;
    }
    if (rbSC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Seating Capacity")));
        index++;
    }
    if (rbL == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Location")));
        index++;
    }
    if (rbC == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("League")));
        index++;
    }
    if (rbST == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Surface Type")));
        index++;
    }
    if (rbSRT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Stadium Roof Type")));
        index++;
    }
    if (rbDT == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Distance to Center Field")));
        index++;
    }
    if (rbDE == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Date")));
        index++;
    }
    if (rbTP == true)
    {
        customModel->setHorizontalHeaderItem(index, new QStandardItem(QString("Typology")));
        index++;
    }

    //simple cycle through conference list and create a new column if needed
    for (int i = 0; i < distances.size(); i++)
    {
        index = 0;
        if (rbTN == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].teamName));
            index++;
        }
        if (rbSN == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].stadiumName));
            index++;
        }
        if (rbSC == true)
        {
            customModel->setItem(i, index, new QStandardItem((QString::number(distances[i].seatingCapacity)).insert(2,',')));
            index++;
        }
        if (rbL == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].location));
            index++;
        }
        if (rbC == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].league));
            index++;
        }
        if (rbST == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].surfaceType));
            index++;
        }
        if (rbSRT == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].roofType));
            index++;
        }
        if (rbDT == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].dist));
            index++;
        }
        if (rbDE == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].date));
            index++;
        }
        if (rbTP == true)
        {
            customModel->setItem(i, index, new QStandardItem(distances[i].typology));
            index++;
        }
    }
    ui->mainTableView->setModel(customModel);
    ui->mainTableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->mainTableView->setSortingEnabled(true);
}
