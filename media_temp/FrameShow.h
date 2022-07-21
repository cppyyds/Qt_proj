#pragma once

#include <QWidget>
#include "ui_FrameShow.h"

class QVideoFrame;
class VideoSurface;
class QMediaPlayer;
class QLabel;
class FrameShow : public QWidget
{
	Q_OBJECT

public:
	FrameShow(QWidget *parent = nullptr);
	~FrameShow();
protected:
    void paintEvent(QPaintEvent* event) override;
public slots:
    void ProcessFrame(QVideoFrame& frame);
private:
    void init();

    Ui::FrameShowClass ui;

    QMediaPlayer* mediaPlayer_;
    VideoSurface* videoSurface_;
    QLabel* showWidget_;
    QPixmap* pixmap_;
};
