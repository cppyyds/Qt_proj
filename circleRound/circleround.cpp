#include "circleround.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>

const double circleRound::PI = 3.141592653589793;

circleRound::circleRound(QWidget *parent)
    : QWidget{parent},
      radius_(100), 
      startAngle_(16 * 270),
      spanAngle_(0)
{
    setMouseTracking(true);
}

circleRound::~circleRound()
{

}

// 一次paintEvent对应一个新的QPainter对象
void circleRound::paintEvent(QPaintEvent *aEvent)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

//    // 几种错误写法，圆和矩形的坐标在每次调用paintEvent时应该重新计算，
//    // 不应该将固定值存在一个变量中，再传入translate、draw...等函数
//    painter.translate(circleCenter_);
    QRectF packRec = getPackRectF();
    painter.translate(getCircleCenter());
    painter.drawEllipse(packRec);
    painter.drawPie(packRec, startAngle_, spanAngle_);

    QString angleInfo = QString::number(userAngle_);
    angleInfo.append("°");
    painter.setFont(QFont("Times", 20, QFont::Bold));
    painter.drawText(QPointF(-1 * getRadius(), 2 * getRadius()), angleInfo);
}

void circleRound::mousePressEvent(QMouseEvent *aEvent)
{
    int pressX = aEvent->pos().x(), pressY = aEvent->pos().y();    
    transCoor(pressX, pressY);
    qDebug() << pressX << "  " << pressY;
    if (!isContained(pressX, pressY)) {
        return ;
    }
    userAngle_ = getAngle(pressX, pressY);
    double angle;
    if (userAngle_ > 270) angle = 630 - userAngle_;
    else angle = 270 - userAngle_;
    setAngle(angle);
}

void circleRound::mouseMoveEvent(QMouseEvent *aEvent)
{

}

void circleRound::mouseReleaseEvent(QMouseEvent *aEvent)
{

}

void circleRound::setAngle(int startAngle)
{
    startAngle_ = startAngle * 16;
    update();
}

double circleRound::getAngle(int x, int y) const
{
    // 要先将x,y转化为我们熟知的坐标系中的坐标
    y = -y;
    double angle = atan2(x, y) * 180 / PI;
    if (x == 0 && y <= 0)
        angle = 0;
    else if (x >= 0)
        angle += 180;
    else if (x < 0)
        angle = 180 + angle;
    return angle;
}

void circleRound::transCoor(int &x, int &y)
{
    x -= getCircleCenter().x();
    y -= getCircleCenter().y();
}

inline QPointF circleRound::getCircleCenter() const
{
    return QPointF(width() / 2, height() / 2);
}

inline QRectF circleRound::getPackRectF() const
{
    return QRectF(-1 * getRadius(), -1 * getRadius(), 2 * getRadius(), 2 * getRadius());
}

inline int circleRound::getRadius() const
{
    return radius_;
}



