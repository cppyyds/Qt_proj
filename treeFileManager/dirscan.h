#ifndef DIRSCAN_H
#define DIRSCAN_H

#include <QObject>
#include <QFileInfo>

class DirScan : public QObject
{
    Q_OBJECT
public:
    explicit DirScan(QObject *parent = nullptr);

signals:
    void ItemScanned(const QString&,const QFileInfo&, bool);
public slots:
    void Scan(const QString& path);
};

#endif // DIRSCAN_H
