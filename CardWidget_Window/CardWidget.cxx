#include <QLabel>
#include <QPicture>
#include <QPainter>

#include "CardWidget.h"



CardWidget::CardWidget(QWidget *parent,
                       QImage *image,
                       std::vector<QImage *> leftLabels,
                       std::vector<QImage *> rightLabels,
                       const QSize &imageSize,
                       const QPoint &cardPos,
                       int cardWidth,
                       const QSize &labelSize,
                       const QString &imageInfo,
                       int labelMarginTop,
                       const QPoint& imagePos):
    m_QPCardPos(cardPos),
    m_pImage(image),
    m_QPImagePoint(imagePos),
    m_QSImageSize(imageSize),
    m_QSCardSize(cardWidth, imageSize.height() + 6),
    m_SimageInfo(imageInfo),
    m_vLeftLabels(leftLabels),
    m_vRightLabels(rightLabels),
    m_QSLabelSize(labelSize),
    m_iLabelMarginTop(labelMarginTop)
{
    this->setObjectName(QString("CardWidget"));
    this->setGeometry(QRect(m_QPCardPos, m_QSCardSize));
}

void CardWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QColor(defaultBgColor));
    painter.setPen(QColor(defaultBorderColor));
    painter.drawRoundedRect(QRect(m_QPCardPos, m_QSCardSize), defaultBorderRadius, defaultBorderRadius);
    painter.drawImage(QRect(m_QPImagePoint, m_QSImageSize), *m_pImage);

    // »æÖÆ×ó±ßµÄlabel
    QPoint point;
    for (int i = 0; i < m_vLeftLabels.size(); ++i) {
        point = QPoint(m_QPImagePoint.x() + m_QSImageSize.width() + m_QSLabelSize.width() * (i + 1), m_iLabelMarginTop);
        painter.drawImage(QRect(point, m_QSLabelSize), *m_vLeftLabels[i]);
    }

    for (int i = 0; i < m_vRightLabels.size(); ++i) {
        point = QPoint(m_QSCardSize.width() - (i + 2) * m_QSLabelSize.width(), m_iLabelMarginTop);
        painter.drawImage(QRect(point, m_QSLabelSize), *m_vRightLabels[i]);
    }


//    this->setStyleSheet(QString("QWidget #%1{ background-color:%2;border-style:solid;border-color:%3}")
//                        .arg(this->objectName()).arg(defaultBgColor).arg(defaultBorderColor));

}


