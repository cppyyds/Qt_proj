#include "media_temp.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    media_temp w;
    w.show();
    return a.exec();
}
