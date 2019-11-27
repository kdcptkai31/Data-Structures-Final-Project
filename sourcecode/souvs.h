#ifndef SOUVS_H
#define SOUVS_H

#include <QDialog>
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
class souvs;
}

class souvs : public QDialog
{
    Q_OBJECT

public:
    explicit souvs(QWidget *parent = 0);
    ~souvs();

private slots:
    void on_pushButton_view_clicked();

private:
    Database* m_db;
    Ui::souvs *ui;
};

#endif // SOUVS_H
