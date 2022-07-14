#include "pictureproxymodel.h"
#include "picturemodel.h"
#include <QPixmap>

const unsigned int PICTURE_SIZE = 350;

PictureProxyModel::PictureProxyModel(QObject* parent):
    QIdentityProxyModel(parent),
    mPictureHashMaps_()
{

}

QVariant PictureProxyModel::data(const QModelIndex &index, int role) const
{
    // 对原始数据模型中的数据进行二次加工处理
    // 供前端调用
    if (role != Qt::DecorationRole) {
        return QIdentityProxyModel::data(index, role);
    }
    QString filePath = sourceModel()->data(index,
                                           PictureModel::Roles::FilePathRole).toString();
    return *(mPictureHashMaps_[filePath]);
}

void PictureProxyModel::setSourceModel(QAbstractItemModel *sourceModel)
{
    QIdentityProxyModel::setSourceModel(sourceModel);
    if (!sourceModel) return;

    connect(sourceModel, &QAbstractItemModel::modelReset, [this] {reloadPictures(); });
    connect(sourceModel, &QAbstractItemModel::rowsInserted, [this] (const QModelIndex& , int first, int last) {
        generatePictures(index(first, 0), last - first + 1);
    });
}

PictureModel *PictureProxyModel::pictureModel() const
{
    return static_cast<PictureModel*> (sourceModel());
}

void PictureProxyModel::reloadPictures()
{
    qDeleteAll(mPictureHashMaps_);
    mPictureHashMaps_.clear();
    generatePictures(index(0, 0), rowCount());
}

void PictureProxyModel::generatePictures(const QModelIndex &startIndex, int count)
{
    if (!startIndex.isValid()) {
        return ;
    }
    const QAbstractItemModel* model = startIndex.model();
    int lastIndex = startIndex.row() + count;
    for (int row = startIndex.row(); row < lastIndex; row++){
        QString filepath = model->data(model->index(row, 0), PictureModel::Roles::FilePathRole).toString();
        QPixmap pixmap(filepath);
        auto thumbnail = new QPixmap(pixmap.scaled(PICTURE_SIZE, PICTURE_SIZE,Qt::KeepAspectRatio,
                                            Qt::SmoothTransformation));
        mPictureHashMaps_.insert(filepath, thumbnail);
    }
}
