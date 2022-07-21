#include <QMediaPlayer>
#include <QLabel>
#include <QPainter>
#include <QHBoxLayout>
#include <QDesktopWidget>

#include "media_temp.h"
#include "VideoSurface.h"
#include "FrameShow.h"

media_temp::media_temp(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    QWidget* widget = new QWidget(this);
    FrameShow* frameShow = new FrameShow();
    QHBoxLayout* layout = new QHBoxLayout();

    layout->addWidget(frameShow);

    widget->setLayout(layout);
    setCentralWidget(widget);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.7);
}


media_temp::~media_temp()
{
}
