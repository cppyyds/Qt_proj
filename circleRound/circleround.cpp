#include "circleround.h"
#include <QPainter>
#include <QMouseEvent>

circleRound::circleRound(QWidget *parent)
    : QWidget{parent},
      radius_(100),
      circleCenter_(QPointF(width() / 2, height() / 2)),
      srcPoint_(circleCenter_),
      destPoint_(circleCenter_.x(),  circleCenter_.y() +  radius_)
{

}

void circleRound::paintEvent(QPaintEvent *aEvent)
{
    painter_->setRenderHint(QPainter::Antialiasing);
    int centerX = circleCenter_.x(), centerY = circleCenter_.y();
    painter_ = new QPainter(this);
    painter_->drawEllipse(circleCenter_.x() - radius_, circleCenter_.y() -radius_, 2 * radius_, 2 * radius_);
    painter_->drawRect(circleCenter_.x() - radius_, circleCenter_.y() - radius_, 2 * radius_, 2 * radius_);
    painter_->drawLine(srcPoint_, destPoint_);
}

void circleRound::mousePressEvent(QMouseEvent *aEvent)
{
    int pressX = aEvent->pos().x(), pressY = aEvent->pos().y();
    if (!isContained(pressX, pressY)) {
        return ;
    }
    setDestPoint(pressX, pressY);
}

void circleRound::mouseMoveEvent(QMouseEvent *aEvent)
{

}

void circleRound::mouseReleaseEvent(QMouseEvent *aEvent)
{

}

void circleRound::setDestPoint(int x, int y)
{
    destPoint_.setX(x);
    destPoint_.setY(y);

    update();
}

void circleRound::getAngle(int x, int y) const
{

}
