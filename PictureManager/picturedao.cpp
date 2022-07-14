#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "picture.h"
#include "picturedao.h"
#include "databasemanager.h"


PictureDao::PictureDao(QSqlDatabase& database):
    mDatabase_(database)
{

}


void PictureDao::init() const {
    if (!mDatabase_.tables().contains("pictures")) {
        QSqlQuery query(mDatabase_);
        query.prepare(QString("CREATE TABLE pictures")
                      + " (id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      + " url TEXT)"
                      );
        DatabaseManager::debugQuery(query);
    }
}

void PictureDao::addPicture(Picture &picture) const
{
    QSqlQuery query(mDatabase_);
    query.prepare(QString("INSERT INTO pictures ")
                  + " (url)"
                  + " Values("
                  + ":url"
                  + ")");
    query.bindValue(":url", picture.pictureUrl());
    query.exec();
    DatabaseManager::debugQuery(query);
    // 插入后再取出id存入picture对象中
    picture.setPictureId(query.lastInsertId().toInt());
}

void PictureDao::removePicture(int id) const
{
    QSqlQuery query(mDatabase_);
    query.prepare("delete from pictures where id = (:id)");
    query.bindValue(":id", id);
    query.exec();
    DatabaseManager::debugQuery(query);
}

unique_ptr<vector<unique_ptr<Picture> > > PictureDao::loadPictures() const
{
    QSqlQuery query(mDatabase_);
    query.prepare("select * from pictures");
    query.exec();
    //DatabaseManager::debugQuery(query);
    unique_ptr<vector<unique_ptr<Picture>>> list(new vector<unique_ptr<Picture>> ());
    while (query.next()) {
        unique_ptr<Picture> picture(new Picture());
        picture->setPictureId(query.value("id").toInt());
        picture->setPictureUrl(query.value("url").toString());
        list->push_back(std::move(picture));
    }
    return list;
}

void PictureDao::removeAllPictures() const
{
    QSqlQuery query(mDatabase_);
    query.prepare("delete from pictures where 1 = 1");
    query.exec();
    DatabaseManager::debugQuery(query);
}
