#include "picturemodel.h"
#include <QUrl>

#include "picture.h"

PictureModel::PictureModel(QObject* parent):
    QAbstractListModel(parent),
    mPictures_(new vector<unique_ptr<Picture>>()),
    mDatabase_(DatabaseManager::instance())
{

}



QModelIndex PictureModel::addPicture(const Picture& picture)
{
    int rows = rowCount();
    beginInsertRows(QModelIndex(), rows, rows);
    unique_ptr<Picture> newPicture(new Picture(picture));
    mDatabase_.mpictureDao.addPicture(*newPicture);
    mPictures_->push_back(move(newPicture));
    endInsertRows();
    return index(rows, 0);
}

int PictureModel::rowCount(const QModelIndex &parent) const
{
    return mPictures_->size();
}

QVariant PictureModel::data(const QModelIndex& index, int role) const
{
    if (!isIndexValid(index)) {
        return QVariant();
    }

    const Picture& picture = *mPictures_->at(index.row());
    switch(role) {
        case Qt::DisplayRole:
            return picture.pictureUrl().fileName();
        break;
        case Roles::UrlRole:
            return picture.pictureUrl();
        break;
        case Roles::FilePathRole:
            return picture.pictureUrl().toLocalFile();
        break;
        default:
        return QVariant();
    }
}

bool PictureModel::removeRows(int row, int count, const QModelIndex& parent)
{
    if (row < 0
            || row >= rowCount()
            || count < 0
            || (row + count) > rowCount()
            ) {
        return false;
    }

    beginRemoveRows(parent, row, row + count - 1);
    int countLeft = count;
    while (countLeft -- ) {
        const Picture& picture = *mPictures_->at(row + countLeft);
        mDatabase_.mpictureDao.removePicture(picture.pictureId());
    }
    mPictures_->erase(mPictures_->begin() + row,
                      mPictures_->begin() + row + count);
    endRemoveRows();
    return true;
}

QHash<int, QByteArray> PictureModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[Qt::DisplayRole] = "name";
    roles[Roles::FilePathRole] = "filepath";
    roles[Roles::UrlRole] = "url";
    return roles;
}

void PictureModel::loadPictures()
{
    beginResetModel();
    mPictures_ = mDatabase_.mpictureDao.loadPictures();
    endResetModel();
}

void PictureModel::clearPictures()
{
    resetPictures();
}

void PictureModel::deleteAllPictures()
{
    mDatabase_.mpictureDao.removeAllPictures();
    resetPictures();
}

void PictureModel::resetPictures()
{
    beginResetModel();
    mPictures_.reset(new vector<unique_ptr<Picture>>());
    endResetModel();
    return;
}

bool PictureModel::isIndexValid(const QModelIndex &index) const
{
    if (index.row() < 0
            || index.row() >= rowCount()
            || !index.isValid()) {
        return false;
    }
    return true;
}




