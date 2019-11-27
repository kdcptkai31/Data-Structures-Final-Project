#include "souvenirwindow.h"
#include "ui_souvenirwindow.h"

souvenirwindow::souvenirwindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::souvenirwindow)
{
    ui->setupUi(this);
    currentStadium = 0;
    displayList.clear();
    cartSum = 0;
    cartRowCount = 0;
    cartSize = 0;

}

souvenirwindow::~souvenirwindow()
{
    delete ui;
}

void souvenirwindow::LoadDisplayList(){
    QSqlQuery* query = new QSqlQuery(database->db);
    query->prepare("SELECT Stadium FROM Visited_Stadium");
    query->exec();
    //QString tempName;

    while(query->next()){
        displayList.push_front(query->value(1).toString());
        qDebug() << displayList[0];
    }
//    //TODO delete anything in the VS db
}

void souvenirwindow::LoadWindow(QVector<QString> stadiums){
    displayList.clear();
    qDebug() << "-----Output for stadiums-----";
    for(int i = 0; i < stadiums.size(); i++){
        displayList.push_back(stadiums[i]);
        qDebug() << stadiums[i];
        //stadiums.pop_front();
    }
    souvenir tempSouvenir;
    QSqlQuery query;
    query.prepare("SELECT * FROM MLB_Stadium_Souviners");
    query.exec();
    while (query.next());
    {
        tempSouvenir.teamName = query.value(0).toString();
        tempSouvenir.stadiumName = query.value(1).toString();
        tempSouvenir.itemName = query.value(2).toString();
        tempSouvenir.price = ((query.value(3).toString()).remove(QChar(','))).toInt();
        souvenirs.push_back(tempSouvenir);
    }
    qDebug() << "Working!";

    cartSouvenirs.clear();

    for (int i = 0; i < souvenirs.size(); i++)
    {
        for (int j = 0; j < displayList.size(); j++)
        {
            if (souvenirs[i].stadiumName == displayList[j])
            {
                cartSouvenirs.push_back(souvenirs[i]);
            }
        }
    }
qDebug() << "PROBLEM HERE\n" << cartSouvenirs.size();
    QStandardItemModel* model = new QStandardItemModel(cartSouvenirs.size(),4, this);
    qDebug() << "PROBLEM UP\n";
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Team Name")));
    model->setHorizontalHeaderItem(1, new QStandardItem(QString("Stadium Name")));
    model->setHorizontalHeaderItem(2, new QStandardItem(QString("Item Name")));
    model->setHorizontalHeaderItem(3, new QStandardItem(QString("Price")));

    for (int i = 0; i < cartSouvenirs.size(); i++)
    {
        model->setItem(i,0,new QStandardItem(cartSouvenirs[i].teamName));
        model->setItem(i,1,new QStandardItem(cartSouvenirs[i].stadiumName));
        model->setItem(i,2,new QStandardItem(cartSouvenirs[i].itemName));
        model->setItem(i,3,new QStandardItem((QString::number(cartSouvenirs[i].price))));

    }


    ui->teamSouvenirs->setModel(model);
    ui->teamSouvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setVisible(false);
    ui->teamSouvenirs->show();
    currentStadium = 0;

    on_previousStadium_clicked();
    qDebug() << "HERERERE\n";
}

void souvenirwindow::on_nextStadium_clicked()
{

    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;
    if(currentStadium < displayList.size()-1){
        currentStadium++;
    }
    qDebug() << currentStadium;
    query.prepare("SELECT * FROM MLB_Stadium_Souviners WHERE Stadium = ?");
    query.addBindValue(displayList[currentStadium]);
    qDebug() << "Working!";
    query.exec();

    model->setQuery(query);

    ui->teamSouvenirs->setModel(model);
    ui->teamSouvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setVisible(false);
    ui->teamSouvenirs->show();

    //
}

void souvenirwindow::on_previousStadium_clicked()
{
    QSqlQueryModel* model = new QSqlQueryModel;
    QSqlQuery query;
    if(currentStadium > 0){
        currentStadium--;
    }
    query.prepare("SELECT * FROM MLB_Stadium_Souviners WHERE Stadium = ?");
    query.addBindValue(displayList[currentStadium]);

    query.exec();

    model->setQuery(query);

    ui->teamSouvenirs->setModel(model);
    ui->teamSouvenirs->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->teamSouvenirs->verticalHeader()->setVisible(false);
    ui->teamSouvenirs->show();
}

void souvenirwindow::on_checkOut_clicked()
{
    checkout.show();
}

void souvenirwindow::on_teamSouvenirs_doubleClicked(const QModelIndex &index)
{
    cartSize++;
    int rowId = index.row();
    int colNum = 4;
    QString value;

    for(int i = 0; i < colNum; i++){

        value = ui->teamSouvenirs->model()->data(ui->teamSouvenirs->model()->index(rowId, i)).toString();

        cartData[cartSize - 1][i] = value;
        qDebug() << value << endl;

    }

qDebug() << "MADE IT\n";
    cartRowCount++;
    int cols = 3;
    QStandardItemModel *cartModel = new QStandardItemModel(cartRowCount, cols, this);
    cartModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Team")));
    cartModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Item")));
    cartModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Price")));


    for(int i = 0; i < cartSize; i++){

        for(int j = 0; j < 3; j++){

            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));
            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));
            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));

        }

    }


    ui->cart->setModel(cartModel);
    ui->cart->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QString temp;
    QString temp1;

    temp = cartData[cartSize - 1][2];
    for(int j = 1; j < temp.size(); j++)
        temp1.push_back(temp[j]);

    cartSum += temp1.toDouble();

    ui->cartTotal->setText(QString::number(cartSum));


}

void souvenirwindow::on_cart_doubleClicked(const QModelIndex &index)
{
    cartSize--;
    int rowId = index.row();
    qDebug() << rowId;

    QString temp;
    QString temp1;

    temp = cartData[rowId][2];
    for(int j = 1; j < temp.size(); j++)
        temp1.push_back(temp[j]);

    cartSum -= temp1.toDouble();

    ui->cartTotal->setText(QString::number(cartSum));

    for(int i = rowId; i < 19; i++){

        for(int j = 0; j < 4; j++)
            cartData[i][j] = cartData[i + 1][j];

    }

    cartRowCount--;
    int cols = 3;
    QStandardItemModel *cartModel = new QStandardItemModel(cartRowCount, cols, this);
    cartModel->setHorizontalHeaderItem(0, new QStandardItem(QString("Team")));
    cartModel->setHorizontalHeaderItem(1, new QStandardItem(QString("Item")));
    cartModel->setHorizontalHeaderItem(2, new QStandardItem(QString("Price")));

    for(int i = 0; i < cartSize; i++){

        for(int j = 0; j < 3; j++){

            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));
            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));
            cartModel->setItem(i, j, new QStandardItem(cartData[i][j]));

        }

    }

    ui->cart->setModel(cartModel);
    ui->cart->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}
