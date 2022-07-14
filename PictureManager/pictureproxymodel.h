#ifndef PICTUREPROXYMODEL_H
#define PICTUREPROXYMODEL_H

#include <QIdentityProxyModel>

class PictureModel;
class PictureProxyModel : public QIdentityProxyModel
{
public:
    PictureProxyModel(QObject* parent = 0);
    // 通过重写data接口对数据进行二次处理
    QVariant data(const QModelIndex& index, int role) const override;
    // 设置获取源数据模型
    void setSourceModel(QAbstractItemModel* sourceModel) override;
    PictureModel* pictureModel() const;
private:
    // 重新加载缩略图
    void reloadPictures();
    // 生成缩略图
    void generatePictures(const QModelIndex& startIndex, int count);

    QHash<QString, QPixmap*> mPictureHashMaps_;
};

#endif // PICTUREPROXYMODEL_H
