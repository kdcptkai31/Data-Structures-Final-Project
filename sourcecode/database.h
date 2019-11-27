/***************************************************************
 * The Database Class
 * *************************************************************
 * This class is used to interface with the databse object.
 * To reach full support of this class, the database should be
 * in the SQLite databse format. It was considered that other
 * databse formats such as MySQL and MariaDB should be supported
 * but ultimately it was out of the scope of the project.
 * *************************************************************/

#ifndef DATABASE_H
#define DATABASE_H

#include <QString>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlDatabase>
#include <QFileInfo>
#include <QDebug>
#include <QSqlQueryModel>

/**
 * @brief The Database class
 *
 * This database class aquires a singleton connection
 * and will be used to communicate with the SQL file
 */
class Database: public QSqlDatabase
{
private:

    /**
     * @brief created
     * @var Variable to show we created an instance of the database
     *
     */
    static bool created;

    /**
     * @brief globalBCInstance
     * @var Pointer to the instance of the Database class
     */
    static Database * globalBCInstance;

    /**
     * @brief Database
     */
    Database()
    {
    }


public:
    /**
     * @brief db
     * @var db object for QT interactions
     */
    QSqlDatabase db;
    /**
     * @brief getInstance
     * @fn gets the instance of the created object
     * @return instance of db
     */
    static Database* getInstance();
    /**
     * @brief SetDBPath
     * @fn sets the path to the connection
     * @param path
     */
    void SetDBPath(const QString &path);
    /**
     * @brief Autoload
     * @fn loads db
     */
    void Autoload();

    ~Database()
    {
        created = false;
    }

    /*!
     * \brief Autoload
     * \fn returns wether the database exists
     */
    bool isCreated(){
        return created;
    }

};

#endif // DATABASE_H
