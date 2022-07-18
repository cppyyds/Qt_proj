#include "dirscan.h"
#include <QDir>

bool isDrivers = true;
DirScan::DirScan(QObject *parent)
    : QObject{parent}
{

}

void DirScan::Scan(const QString& strPath) {

    if (isDrivers && !QString::compare(strPath, QString(tr("我的电脑")))) {
        QFileInfoList drivers = QDir::drives();
        int q = 0;
        while (q < drivers.size()) {
            QFileInfo file = drivers.at(q++);
            emit ItemScanned(strPath, file, isDrivers);
            
        }
        isDrivers = false;
    }
    else {
        QDir dir(strPath);
        if (!dir.exists()) return;
        QFileInfoList list = dir.entryInfoList();
        int q = 0;
        while (q < list.size()) {
            QFileInfo file = list.at(q++);
            emit ItemScanned(strPath, file, false);
        }
    }

}
