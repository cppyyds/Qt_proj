#ifndef PICTUREMODEL_H
#define PICTUREMODEL_H

#include <memory>
#include <vector>
#include <QAbstractListModel>
#include <QUrl>
#include <QVariant>
#include "DatabaseManager.h"

using std::unique_ptr, std::vector;

class PictureModel : public QAbstractListModel
{
    Q_OBJECT;
public:
    // 自定义每个元素的数据类型
    enum Roles {
        UrlRole = Qt::UserRole + 1,
        FilePathRole
    };
    PictureModel(QObject* parent = 0);
    // 数据模型中添加单个数据
    QModelIndex addPicture(const Picture& picture);
    void addPictureFromUrl(const QUrl& fileUrl);
    // 模型的行数
    int rowCount(const QModelIndex& parent = QModelIndex()) const override;

    // 获取某个元素的数据
    QVariant data(const QModelIndex& index, int role) const;

    // 删除某几行数据
    Q_INVOKABLE bool removeRows(int row, int count, const QModelIndex& parent = QModelIndex()) override;

    // 每个元素类别的名称
    QHash<int, QByteArray> roleNames() const override;

    // 加载用户图片
    Q_INVOKABLE void loadPictures();

    // 清空模型中的数据，但不移除本地文件数据
    void clearPictures();

public slots:
    // 清空模型，删除本地文件中的数据
    void deleteAllPictures();

private:
    void resetPictures();
    bool isIndexValid(const QModelIndex& index) const;

    DatabaseManager& mDatabase_;
    unique_ptr<vector<unique_ptr<Picture>>> mPictures_;
};

#endif // PICTUREMODEL_H
