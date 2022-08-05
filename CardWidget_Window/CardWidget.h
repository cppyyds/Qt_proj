#ifndef CARDWIDGET_H
#define CARDWIDGET_H

#include <QWidget>
#include <vector>

using std::vector;
#define defaultImageSize QSize(150, 90)
#define defaultLabelSize QSize(25, 25)
#define defaultCardPos QPoint(0, 0)
#define defaultCardWidth 400
#define defaultImagePos QPoint(5, 5)
#define defaultBgColor "#EDEDED"
#define defaultBorderColor "#CCCCCC"
#define defaultBorderRadius 4

class QLabel;
class CardWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CardWidget(QWidget *parent = nullptr, QImage* image = nullptr,
                        vector<QImage*> leftLabels = vector<QImage*>(),
                        vector<QImage*> rightLabels = vector<QImage*>(),
                        const QSize& imageSize = defaultImageSize, const QPoint& cardPos = defaultCardPos,
                        int cardWidth = defaultCardWidth, const QSize& labelSize = defaultLabelSize,
                        const QString& imageInfo = QString(""), int labelMarginTop = defaultLabelSize.width(),
                        const QPoint& imagePos = defaultImagePos);

    void paintEvent(QPaintEvent* event) override;
signals:

private:
    QPoint m_QPCardPos;
    QImage* m_pImage;
    QPoint m_QPImagePoint;
    QSize m_QSImageSize;
    QSize m_QSCardSize;
    QString m_SimageInfo;

    vector<QImage*> m_vLeftLabels;
    vector<QImage*> m_vRightLabels;
    QSize m_QSLabelSize;
    int m_iLabelMarginTop;

    // widgetÑùÊ½
    QString m_SBackgroundColor;
    QString m_SBorderColor;
    int m_iBorderRadius;
};

#endif // CARDWIDGET_H
