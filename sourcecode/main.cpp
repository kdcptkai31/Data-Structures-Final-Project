/*************************************************************************
 * AUTHORS		 : Daniel, Chase, Sean, and Wesley
 * GROUP PROJECT : 2
 * GROUP NAME    : White Male Enterprises
 * CLASS		 : CS1D
 * SECTION		 : MW: 15:00-18:20
 ************************************************************************/

#include "mainwindow.h"
#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login program;
    program.show();

    return a.exec();
}
