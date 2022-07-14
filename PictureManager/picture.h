#ifndef PICTURE_H
#define PICTURE_H

#include <QString>
#include <QUrl>

class Picture
{
public:
    Picture(const QString &filePath = "") {
        mPictureUrl_ = QUrl::fromLocalFile(filePath);
    }

    Picture(const QUrl &fileUrl) {
        mPictureUrl_ = fileUrl;
    }

    int pictureId() const {
        return mPictureId_;
    }

    void setPictureId(int pictureId) {
        mPictureId_ = pictureId;
    }

    QUrl pictureUrl() const
    {
        return mPictureUrl_;
    }

    void setPictureUrl(const QUrl &pictureUrl)
    {
        mPictureUrl_ = pictureUrl;
    }

private:
    int mPictureId_;  // 图片ID
    QUrl mPictureUrl_;  // 图片地址
};

#endif // PICTURE_H
