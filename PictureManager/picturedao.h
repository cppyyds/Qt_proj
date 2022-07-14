#ifndef PICTUREDAO_H
#define PICTUREDAO_H

#include <vector>
#include <memory>
class Picture;
class QSqlDatabase;

using std::vector, std::unique_ptr;

class PictureDao
{
public:
    PictureDao(QSqlDatabase& database);
    void init() const;

    void addPicture(Picture& picture) const;

    void removePicture(int id) const;

    unique_ptr<vector<unique_ptr<Picture>>> loadPictures() const;

    void removeAllPictures() const;
private:
    QSqlDatabase& mDatabase_;
};

#endif // PICTUREDAO_H
