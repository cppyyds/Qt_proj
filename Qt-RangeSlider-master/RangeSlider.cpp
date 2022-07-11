
#include "RangeSlider.h"
#include <QDebug>
#include <QLabel>

namespace
{

const int scHandleSideLength = 11;
const int scSliderBarHeight = 5;
const int scLeftRightMargin = 20;
const int scDefaultMinimum = 0;
const int scDefaultMaximum = 100;
const int scTickInterval = 10;  // 将滑框分为scTickInterval块(步长)
}

RangeSlider::RangeSlider(QWidget* aParent)
    : QWidget(aParent),
      mMinimum(scDefaultMinimum),
      mMaximum(scDefaultMaximum),
      mLowerValue(mMinimum),
      mUpperValue(mMaximum),
      mSelectedValue_((mLowerValue + mUpperValue) / 2),
      mFirstHandlePressed(false),
      mSecondHandlePressed(false),
      mInterval(mMaximum - mMinimum),
      mBackgroudColorEnabled(QColor(0x1E, 0x90, 0xFF)),
      mBackgroudColorDisabled(Qt::darkGray),
      mBackgroudColor(mBackgroudColorEnabled),
      orientation(Qt::Horizontal)
{
    setMouseTracking(true);
}

RangeSlider::RangeSlider(Qt::Orientation ori, Options t, QWidget* aParent)
    : QWidget(aParent),
      mMinimum(scDefaultMinimum),
      mMaximum(scDefaultMaximum),
      mLowerValue(mMinimum),
      mUpperValue(mMaximum),
      mFirstHandlePressed(false),
      mSecondHandlePressed(false),
      mInterval(mMaximum - mMinimum),
      mBackgroudColorEnabled(QColor(0x1E, 0x90, 0xFF)),
      mBackgroudColorDisabled(Qt::darkGray),
      mBackgroudColor(mBackgroudColorEnabled),
      orientation(ori),
      type(t),
      mSelectedValue_((mLowerValue + mUpperValue) / 2)
{
    setMouseTracking(true);
}

void RangeSlider::paintEvent(QPaintEvent* aEvent)
{
    Q_UNUSED(aEvent);
    QPainter painter(this);

    // Background
    QRectF backgroundRect;
    // 水平、垂直滑框的坐标分别为(scLeftRightMargin, (height() - scSliderBarHeight) / 2),
    // ( (width() - scSliderBarHeight) / 2, scLeftRightMargin)
    if(orientation == Qt::Horizontal)
        backgroundRect = QRectF(scLeftRightMargin, (height() - scSliderBarHeight) / 2, width() - scLeftRightMargin * 2, scSliderBarHeight);
    else
        backgroundRect = QRectF((width() - scSliderBarHeight) / 2, scLeftRightMargin, scSliderBarHeight, height() - scLeftRightMargin*2);

    QPen backgrPen(Qt::gray, 0.8);
    painter.setPen(backgrPen);
    painter.setRenderHint(QPainter::Qt4CompatiblePainting);
    QBrush backgroundBrush(QColor(0xD0, 0xD0, 0xD0));
    painter.setBrush(backgroundBrush);
    painter.drawRoundedRect(backgroundRect, 1, 1);

    // 画最小值滑块
    // First value handle rect
    QPen handlePen(Qt::darkGray, 0.5);
    painter.setPen(handlePen);
    painter.setRenderHint(QPainter::Antialiasing);
    QBrush handleBrush(QColor(0xFA, 0xFA, 0xFA));
    painter.setBrush(handleBrush);

    QRectF leftHandleRect = firstHandleRect();
    if(type.testFlag(LeftHandle))
        painter.drawRoundedRect(leftHandleRect, 2, 2);

    // 画最大值滑块
    // Second value handle rect
    QRectF rightHandleRect = secondHandleRect();
    if(type.testFlag(RightHandle))
        painter.drawRoundedRect(rightHandleRect, 2, 2);



    // 画最小值文本标签
    QPen textPen(Qt::darkBlue, 0.8);
    painter.setPen(textPen);
    painter.setFont(QFont("Times", 10, QFont::Bold));
    painter.drawText(leftHandleRect.x(), leftHandleRect.y() + 2 * scHandleSideLength + 3, QString::number(mLowerValue));

    // 绘制最大值文本标签
    painter.drawText(rightHandleRect.x(), rightHandleRect.y() + 2 * scHandleSideLength + 3, QString::number(mUpperValue));

    // 绘制选择值文本标签
    painter.drawText(mSelectedHandle_.x(), mSelectedHandle_.y() - scHandleSideLength, QString::number(mSelectedValue_));

    // Handles
    painter.setRenderHint(QPainter::Antialiasing, false);
    QRectF selectedRect(backgroundRect);
    if(orientation == Qt::Horizontal) {
        selectedRect.setLeft((type.testFlag(LeftHandle) ? leftHandleRect.right() : leftHandleRect.left()) + 0.5);
        selectedRect.setRight((type.testFlag(RightHandle) ? rightHandleRect.left() : rightHandleRect.right()) - 0.5);
    } else {
        selectedRect.setTop((type.testFlag(LeftHandle) ? leftHandleRect.bottom() : leftHandleRect.top()) + 0.5);
        selectedRect.setBottom((type.testFlag(RightHandle) ? rightHandleRect.top() : rightHandleRect.bottom()) - 0.5);
    }
    QBrush selectedBrush(mBackgroudColor);
    painter.setBrush(selectedBrush);
    painter.drawRect(selectedRect);

//    画选择值的滑块
    painter.setPen(handlePen);
    handleBrush.setColor(Qt::red);
    painter.setBrush(handleBrush);

    mSelectedHandle_ = selectedHandleRect();
    painter.drawRoundedRect(mSelectedHandle_, 2, 2);
}

QRectF RangeSlider::firstHandleRect() const
{
    float percentage = (mLowerValue - mMinimum) * 1.0 / mInterval;
    return handleRect(percentage * validLength() + scLeftRightMargin);
}

QRectF RangeSlider::secondHandleRect() const
{
    float percentage = (mUpperValue - mMinimum) * 1.0 / mInterval;
    return handleRect(percentage * validLength() + scLeftRightMargin + (type.testFlag(LeftHandle) ? scHandleSideLength : 0));
}

QRectF RangeSlider::selectedHandleRect() const
{
    float percentage = (mSelectedValue_ - mMinimum) * 1.0 / mInterval;
    return handleRect(percentage * validLength() + scLeftRightMargin + scHandleSideLength);
}

QRectF RangeSlider::handleRect(int aValue) const
{
    if(orientation == Qt::Horizontal)
        return QRect(aValue, (height()-scHandleSideLength) / 2, scHandleSideLength, scHandleSideLength);
    else
        return QRect((width()-scHandleSideLength) / 2, aValue, scHandleSideLength, scHandleSideLength);
}

void RangeSlider::mousePressEvent(QMouseEvent* aEvent)
{
    qDebug() << " mousePressEvent ";
    if(aEvent->buttons() & Qt::LeftButton)
    {
        int posCheck, posMax, posValue, firstHandleRectPosValue, secondHandleRectPosValue, selectedHandleRectPosValue;
        posCheck = (orientation == Qt::Horizontal) ? aEvent->pos().y() : aEvent->pos().x();
        posMax = (orientation == Qt::Horizontal) ? height() : width();
        posValue = (orientation == Qt::Horizontal) ? aEvent->pos().x() : aEvent->pos().y();
        firstHandleRectPosValue = (orientation == Qt::Horizontal) ? firstHandleRect().x() : firstHandleRect().y();
        secondHandleRectPosValue = (orientation == Qt::Horizontal) ? secondHandleRect().x() : secondHandleRect().y();
        selectedHandleRectPosValue = (orientation == Qt::Horizontal) ? mSelectedHandle_.x() : mSelectedHandle_.y();

        mSecondHandlePressed = secondHandleRect().contains(aEvent->pos());
        mFirstHandlePressed = !mSecondHandlePressed && firstHandleRect().contains(aEvent->pos());
        mSelectedHandlePressed = !mFirstHandlePressed && !mSecondHandlePressed && mSelectedHandle_.contains(aEvent->pos());

        if(mFirstHandlePressed)
        {
            mDelta = posValue - (firstHandleRectPosValue + scHandleSideLength / 2);
        }
        else if(mSecondHandlePressed)
        {
            mDelta = posValue - (secondHandleRectPosValue + scHandleSideLength / 2);
        }
        else if (mSelectedHandlePressed) {
            mDelta = posValue - (selectedHandleRectPosValue + scHandleSideLength / 2);
        }

        // 如果点击的坐标不在有效范围内，忽略本次点击
        if(posValue < firstHandleRectPosValue || posValue > secondHandleRectPosValue) {
            return ;
        }
        // 如果点击的范围距离滑框太远，忽略本次点击
        if (orientation == Qt::Horizontal && (posCheck < (height() - 2 * scSliderBarHeight) / 2 || posCheck > (height() + 2 * scSliderBarHeight) / 2)) {
            return ;
        }
        if (orientation == Qt::Vertical && (posCheck < (width() - 2 * scSliderBarHeight) / 2 || posCheck > (width() + 2 * scSliderBarHeight) / 2)) {
            return ;
        }

//        // 原版本
//        if(posCheck >= 2
//           && posCheck <= posMax - 2)
//        {
//            int step = mInterval / tickInterval < 1 ? 1 : mInterval / 10;
//            if(posValue < firstHandleRectPosValue)
//                setLowerValue(mLowerValue - step);
//            else if(((posValue > firstHandleRectPosValue + scHandleSideLength) || !type.testFlag(LeftHandle))
//                    && ((posValue < secondHandleRectPosValue) || !type.testFlag(RightHandle)))
//            {
//                if(type.testFlag(DoubleHandles))
//                    if(posValue - (firstHandleRectPosValue + scHandleSideLength) <
//                            (secondHandleRectPosValue - (firstHandleRectPosValue + scHandleSideLength)) / 2)
//                        setLowerValue((mLowerValue + step < mUpperValue) ? mLowerValue + step : mUpperValue);
//                    else
//                        setUpperValue((mUpperValue - step > mLowerValue) ? mUpperValue - step : mLowerValue);
//                else if(type.testFlag(LeftHandle))
//                    setLowerValue((mLowerValue + step < mUpperValue) ? mLowerValue + step : mUpperValue);
//                else if(type.testFlag(RightHandle))
//                    setUpperValue((mUpperValue - step > mLowerValue) ? mUpperValue - step : mLowerValue);
//            }
//            else if(posValue > secondHandleRectPosValue + scHandleSideLength)
//                setUpperValue(mUpperValue + step);
//        }

        mSelectedValue_ = (posValue - scLeftRightMargin) / validLength() * mInterval + mMinimum;
    }
}

void RangeSlider::mouseMoveEvent(QMouseEvent* aEvent)
{
    qDebug() << " mouseMoveEvent ";
    if(aEvent->buttons() & Qt::LeftButton)
    {
        int posValue, firstHandleRectPosValue, secondHandleRectPosValue;
        posValue = (orientation == Qt::Horizontal) ? aEvent->pos().x() : aEvent->pos().y();
        firstHandleRectPosValue = (orientation == Qt::Horizontal) ? firstHandleRect().x() : firstHandleRect().y();
        secondHandleRectPosValue = (orientation == Qt::Horizontal) ? secondHandleRect().x() : secondHandleRect().y();
        qDebug() << mDelta;
        if (mFirstHandlePressed && type.testFlag(LeftHandle))
        {
            // 如果左滑块的最右边坐标小于等于右滑块的左坐标时
            if(posValue - mDelta + scHandleSideLength / 2 <= secondHandleRectPosValue)
            {
                setLowerValue((posValue - mDelta - scLeftRightMargin - scHandleSideLength / 2) * 1.0 / validLength() * mInterval + mMinimum);
            }
            else
            {
                setLowerValue(mUpperValue);
            }
        }
        else if(mSecondHandlePressed && type.testFlag(RightHandle))
        {
            if(firstHandleRectPosValue + scHandleSideLength * (type.testFlag(DoubleHandles) ? 1.5 : 0.5) <= posValue - mDelta)
            {
                setUpperValue((posValue - mDelta - scLeftRightMargin - scHandleSideLength / 2 - (type.testFlag(DoubleHandles) ? scHandleSideLength : 0)) * 1.0 / validLength() * mInterval + mMinimum);
            }
            else
            {
                setUpperValue(mLowerValue);
            }
        }
        else if (mSelectedHandlePressed)
        {


        }
    }
}

void RangeSlider::mouseReleaseEvent(QMouseEvent* aEvent)
{
    Q_UNUSED(aEvent);

    mFirstHandlePressed = false;
    mSecondHandlePressed = false;
    mSelectedHandlePressed = false;
}

void RangeSlider::changeEvent(QEvent* aEvent)
{
    qDebug() << "changeEvent";
    if(aEvent->type() == QEvent::EnabledChange)
    {
        if(isEnabled())
        {
            mBackgroudColor = mBackgroudColorEnabled;
        }
        else
        {
            mBackgroudColor = mBackgroudColorDisabled;
        }
        update();
    }
}

QSize RangeSlider::minimumSizeHint() const
{
    return QSize(scHandleSideLength * 2 + scLeftRightMargin * 2, scHandleSideLength);
}

int RangeSlider::GetMinimun() const
{
    return mMinimum;
}

void RangeSlider::SetMinimum(int aMinimum)
{
    setMinimum(aMinimum);
}

int RangeSlider::GetMaximun() const
{
    return mMaximum;
}

void RangeSlider::SetMaximum(int aMaximum)
{
    setMaximum(aMaximum);
}

int RangeSlider::GetLowerValue() const
{
    return mLowerValue;
}

void RangeSlider::SetLowerValue(int aLowerValue)
{
    setLowerValue(aLowerValue);
}

int RangeSlider::GetUpperValue() const
{
    return mUpperValue;
}

void RangeSlider::SetUpperValue(int aUpperValue)
{
    setUpperValue(aUpperValue);
}

void RangeSlider::setLowerValue(int aLowerValue)
{
    if(aLowerValue > mMaximum)
    {
        aLowerValue = mMaximum;
    }

    if(aLowerValue < mMinimum)
    {
        aLowerValue = mMinimum;
    }

    mLowerValue = aLowerValue;
    emit lowerValueChanged(mLowerValue);

    update();
}

void RangeSlider::setUpperValue(int aUpperValue)
{
    if(aUpperValue > mMaximum)
    {
        aUpperValue = mMaximum;
    }

    if(aUpperValue < mMinimum)
    {
        aUpperValue = mMinimum;
    }

    mUpperValue = aUpperValue;
    emit upperValueChanged(mUpperValue);

    update();
}

void RangeSlider::setSelectedValue(int aSelectedValue)
{
    if (aSelectedValue > mUpperValue)
        aSelectedValue = mUpperValue;
    if (aSelectedValue < mLowerValue)
        aSelectedValue = mLowerValue;

    mSelectedValue_ = aSelectedValue;
//    emit upperValueChanged(mSelectedValue_);

    update();
}


void RangeSlider::setMinimum(int aMinimum)
{
    if(aMinimum <= mMaximum)
    {
        mMinimum = aMinimum;
    }
    else
    {
        int oldMax = mMaximum;
        mMinimum = oldMax;
        mMaximum = aMinimum;
    }
    mInterval = mMaximum - mMinimum;
    update();

    setLowerValue(mMinimum);
    setUpperValue(mMaximum);

    emit rangeChanged(mMinimum, mMaximum);
}

void RangeSlider::setMaximum(int aMaximum)
{
    if(aMaximum >= mMinimum)
    {
        mMaximum = aMaximum;
    }
    else
    {
        int oldMin = mMinimum;
        mMaximum = oldMin;
        mMinimum = aMaximum;
    }
    mInterval = mMaximum - mMinimum;
    update();

    setLowerValue(mMinimum);
    setUpperValue(mMaximum);

    emit rangeChanged(mMinimum, mMaximum);
}


// 除去滑块的滑框长度
int RangeSlider::validLength() const
{
    int len = (orientation == Qt::Horizontal) ? width() : height();
    return len - scLeftRightMargin * 2 - scHandleSideLength * (type.testFlag(DoubleHandles) ? 2 : 1);
}

void RangeSlider::SetRange(int aMinimum, int mMaximum)
{
    setMinimum(aMinimum);
    setMaximum(mMaximum);
}
