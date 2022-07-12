#ifndef CIRCLEROUND_H
#define CIRCLEROUND_H

#include <QWidget>
#include <QtMath>

class circleRound : public QWidget
{
    Q_OBJECT
public:
    explicit circleRound(QWidget *parent = nullptr);
    ~circleRound();
    const static double PI;
protected:
    void paintEvent(QPaintEvent* aEvent) override;
    void mousePressEvent(QMouseEvent* aEvent) override;
    void mouseMoveEvent(QMouseEvent* aEvent) override;
    void mouseReleaseEvent(QMouseEvent* aEvent) override;

signals:

private:
    bool isContained(int x, int y) const{
        double distance = sqrt(qPow(x, 2) + qPow(y, 2));
        return distance <= radius_;
    }
    void setAngle(int startAngle);
    double getAngle(int x, int y) const;
    void transCoor(int& x, int& y);  // 将原来窗口的坐标转化自定义的画图坐标
    QPointF getCircleCenter() const;
    QRectF getPackRectF() const;
    int getRadius() const;

    qreal radius_;
    int startAngle_;  // 圆饼开始的角度
    int spanAngle_;   // 援兵覆盖的角度
    double userAngle_;  // 用户设置的角度
};

#endif // CIRCLEROUND_H
