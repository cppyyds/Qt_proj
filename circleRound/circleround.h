#ifndef CIRCLEROUND_H
#define CIRCLEROUND_H

#include <QWidget>
#include <QtMath>

class circleRound : public QWidget
{
    Q_OBJECT
public:
    explicit circleRound(QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent* aEvent) override;
    void mousePressEvent(QMouseEvent* aEvent) override;
    void mouseMoveEvent(QMouseEvent* aEvent) override;
    void mouseReleaseEvent(QMouseEvent* aEvent) override;

signals:

private:
    bool isContained(int x, int y) const{
        double distance = sqrt(qPow(x - circleCenter_.x(), 2) + qPow(y - circleCenter_.y(), 2));
        return distance <= radius_;
    }
    void setDestPoint(int x, int y);

    void getAngle(int x, int y) const;

    qreal radius_;
    QPointF circleCenter_;
    // 画出的半径，起点和终点的坐标
    QPointF srcPoint_;
    QPointF destPoint_;


    QPainter *painter_;
};

#endif // CIRCLEROUND_H
