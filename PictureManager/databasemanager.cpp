#include <QSqlDatabase>
#include <QDebug>
#include <QSqlError>
#include <QSqlQuery>

#include "databasemanager.h"

void DatabaseManager::debugQuery(const QSqlQuery &query)
{
    if (query.lastError().type() == QSqlError::ErrorType::NoError) {
        qDebug() << "Query OK: " << query.lastQuery();
    }
    else {
        qWarning() << "Query KO: " << query.lastError().text();
        qWarning() << "Query text: " << query.lastQuery();
    }
}

DatabaseManager &DatabaseManager::instance()
{
    static DatabaseManager singleton;
    return singleton;
}

DatabaseManager::DatabaseManager(const QString &path):
    mDatabase_(new QSqlDatabase(QSqlDatabase::addDatabase("QSQLITE"))),
    mpictureDao(*mDatabase_)
{
    mDatabase_->setDatabaseName(path);
    bool openStatus = mDatabase_->open();
    qDebug() << "Database connection: " << (openStatus ? "OK" : "Error");
    mpictureDao.init();
}

DatabaseManager::~DatabaseManager()
{
    mDatabase_->close();
}



DatabaseManager &DatabaseManager::operator=(const DatabaseManager &rhs)
{
    return *this;
}


