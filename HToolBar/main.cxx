#include "HToolBar.h"

#include <QApplication>
#include <QDebug>
#include <QFile>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile file(":/style.qss");

    if (file.open(QFile::ReadOnly)) {
        qDebug() << "open! ";
        QString styleSheet = file.readAll();

        qApp->setPalette(QPalette(QColor(styleSheet.mid(20, 7))));
        qApp->setStyleSheet(styleSheet);
        file.close();
    }
    else {
        QMessageBox::warning(NULL, "warning", "Open failed", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
    }
    qApp->setFont(QFont("Microsoft Yahei", 9));
    HToolBar w;
    w.show();
    return a.exec();
}
