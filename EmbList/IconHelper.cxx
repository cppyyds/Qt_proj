#include <QLabel>
#include <QFontDatabase>
#include <QDebug>

#include "IconHelper.h"

IconHelper::IconHelper(QObject *parent)
    : QObject{parent}
{
    int id = QFontDatabase::addApplicationFont(":/image/fontawesome-webfont.ttf");
    auto fontList = QFontDatabase::applicationFontFamilies(id);

    if (fontList.size() > 0) {
        iconFont = QFont(fontList.at(0));
    }
    else {
        qDebug() << "load fontawesome-webfont.ttf error";
    }
}

IconHelper &IconHelper::instance()
{
    static IconHelper iconHelper;
    return iconHelper;
}

void IconHelper::setIcon(QLabel *lab, QChar c, quint32 size) {
    iconFont.setPixelSize(size);
    lab->setFont(iconFont);
    lab->setText(c);
}


