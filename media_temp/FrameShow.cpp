#include <QLabel>
#include <QPainter>
#include <QMediaPlayer>

#include "FrameShow.h"
#include "VideoSurface.h"

FrameShow::FrameShow(QWidget *parent)
	: QWidget(parent)
{
    ui.setupUi(this);

    mediaPlayer_ = new QMediaPlayer;
    videoSurface_ = new VideoSurface;
    showWidget_ = new QLabel();
    pixmap_ = nullptr;

    mediaPlayer_->setVideoOutput(videoSurface_);
    mediaPlayer_->setMedia(QUrl::fromLocalFile("D:\\video\\League of Legends (TM) Client 2022-05-11 15-01-59.mp4"));
    mediaPlayer_->play();

    qDebug() << mediaPlayer_->error();
    connect(videoSurface_, SIGNAL(frameAvailable(QVideoFrame&)), this, SLOT(ProcessFrame(QVideoFrame&)));
}

FrameShow::~FrameShow()
{
    delete mediaPlayer_;
    delete videoSurface_;
    delete showWidget_;
    delete pixmap_;
}

void FrameShow::paintEvent(QPaintEvent * event)
{
    QPainter painter(this);
    QPointF point(55, 55);
//    QPen pen;
//    pen.setWidth(5);                    //线宽
//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::SolidLine);        //实线
//    pen.setCapStyle(Qt::FlatCap);       //线端点样式
//    pen.setJoinStyle(Qt::BevelJoin);    //线连接点样式
//    painter.setPen(pen);
//    painter.setFont(QFont("Times", 150, QFont::Bold));
    if (pixmap_) painter.drawPixmap(QPointF(5, 5), *pixmap_);
}

void FrameShow::init()
{
    showWidget_->setWindowTitle("Image Show");
    showWidget_->setAlignment(Qt::AlignCenter);


}




void FrameShow::ProcessFrame(QVideoFrame & frame) {
    qDebug() << "=============ProcessFrame===============";
    qDebug() << "width : " << frame.width() << " height : " << frame.height();
    qDebug() << "start time : " << frame.startTime() / 1000 << "ms";
    qDebug() << "end time : " << frame.endTime() / 1000 << "ms";
    qDebug() << "pixelFormat :" << frame.pixelFormat();

    frame.map(QAbstractVideoBuffer::ReadOnly);
    QImage recvImage(frame.bits(), frame.width(), frame.height(), QVideoFrame::imageFormatFromPixelFormat(frame.pixelFormat()));

    qDebug() << "frame data size :" << frame.mappedBytes();
    frame.unmap();
    if (pixmap_) {
        delete pixmap_;
        pixmap_ = nullptr;
    }
    pixmap_ = new  QPixmap(QPixmap::fromImage(recvImage)); ;
    update();
    mediaPlayer_->stop();
    //showWidget_->setPixmap();
    //showWidget_->showMaximized();
    //mediaPlayer_->play();
}
