#include "database.h"

/**
 * @brief Database::created
 * @var accesses created variable and sets to fall
 */
bool Database::created = false;

/**
 * @brief Database::globalBCInstance
 * @var sets the global instance to nothing
 */
Database* Database::globalBCInstance = NULL;

/**
 * @brief Database::getInstance
 * @fn Gets instance
 * @return Database pointer
 */
Database* Database::getInstance()
{
    if (!created)
    {
        globalBCInstance = new Database();
        created = true;
        return globalBCInstance;
    }
    else
    {
        return globalBCInstance;
    }
}

/**
 * @brief Database::SetDBPath
 * @param path
 * @fn Sets path to the database based on the string provided
 */
void Database::SetDBPath(const QString &path)
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(path);

    if(!db.open())
    {
        qDebug() << "Error: connection with database failed";
    }
    else
    {
        qDebug() << "Database: connection made!";
    }
}
