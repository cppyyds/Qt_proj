#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <QString>
#include <memory>

#include "picturedao.h"

class QSqlQuery;
class QSqlDatabase;

const QString DATABASE_FILENAME = "picture.db";

class DatabaseManager
{
public:
    static void debugQuery(const QSqlQuery& query);
    static DatabaseManager& instance();
    ~DatabaseManager();
protected:
    DatabaseManager(const QString& path = DATABASE_FILENAME);
    DatabaseManager& operator= (const DatabaseManager& rhs);

private:
    std::unique_ptr<QSqlDatabase> mDatabase_;

public:
    // 图片数据操作类
    const PictureDao mpictureDao;
};

#endif // DATABASEMANAGER_H
