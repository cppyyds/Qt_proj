#include <QToolButton>
#include <QList>
#include <QTabWidget>


#include "HToolBar.h"
#include "ui_HToolBar.h"
#define btnMain ui->toolButton
#define defaultWidth 350
#define defaultHeight 607
#define defaultBtnWidth 100
#define defaultBtnHeight 71
#define defaultPosX 0
#define defaultPosY 0
#define defaultDirection ToolBarDiretion::Horizontal
#define defaultBorderWidth 3


HToolBar::HToolBar(QWidget *parent)
    : QWidget(parent)
    ,widgetTop_(new QWidget(this))
    ,stackedWidget_(new QStackedWidget(this))
    ,width_(defaultWidth)
    ,height_(defaultHeight)
    ,tabHeight_(defaultBtnHeight)
    ,tabWidth_(defaultBtnWidth)
    ,posX_(defaultPosX)
    ,posY_(defaultPosY)
    ,direction_(defaultDirection)
    ,borderType_(direction_ == Horizontal ? BorderType::bottom : BorderType::left)
    ,borderWidth_(defaultBorderWidth)
{
    this->initToolBar();
    addTab(new QWidget(), QString::fromLocal8Bit("页面1"));
    addTab(new QWidget(), QString::fromLocal8Bit("页面2"));
    addTab(new QWidget(), QString::fromLocal8Bit("页面3"));
    addTab(new QWidget(), QString::fromLocal8Bit("页面4"));
    addTab(new QWidget(), QString::fromLocal8Bit("页面5"));
}

HToolBar::~HToolBar()
{
    //delete ui;
    delete widgetTop_;
    delete stackedWidget_;
    for (auto* btn : tabs_) {
        delete btn;
    }
}



void HToolBar::paintEvent(QPaintEvent *)
{

}

int HToolBar::addTab(QWidget *widget, const QString &name)
{
    return insertTab(tabs_.size(), widget, name);
}

int HToolBar::addTab(QWidget *widget, const QIcon &icon)
{
    return insertTab(tabs_.size(), widget, icon);
}

int HToolBar::insertTab(int index, QWidget *widget, const QString &name)
{
    QToolButton* btn = new QToolButton(widgetTop_);
    QRect btnGeometry;
    if (direction_ == Horizontal) {
        btnGeometry = QRect(posX_ + tabWidth_ * tabs_.size(), posY_, tabWidth_, tabHeight_);
    }
    else {
        btnGeometry = QRect(posX_, posY_ + tabHeight_ * tabs_.size(), tabWidth_, tabHeight_);
    }
    btn->setGeometry(btnGeometry);
    btn->setText(name);
    if (index >= tabs_.size()) {
        index = tabs_.size();
    }
    tabs_.insert(tabs_.begin() + index, btn);
    return stackedWidget_->insertWidget(index, widget);
}

int HToolBar::insertTab(int index, QWidget *widget, const QIcon &icon)
{
    QToolButton* btn = new QToolButton(widgetTop_);
    QRect btnGeometry;
    if (direction_ == Horizontal) {
        btnGeometry = QRect(posX_ + tabWidth_ * tabs_.size(), posY_, tabWidth_, tabHeight_);
    }
    else {
        btnGeometry = QRect(posX_, posY_ + tabHeight_ * tabs_.size(), tabWidth_, tabHeight_);
    }
    btn->setGeometry(btnGeometry);
    btn->setIcon(icon);btn->setToolButtonStyle(Qt::ToolButtonFollowStyle);
    if (index > tabs_.size()) index = tabs_.size();
    tabs_.insert(tabs_.begin() + index, btn);
    return stackedWidget_->insertWidget(index, widget);
}

void HToolBar::removeTab(int index)
{
    if (index >= tabs_.size()) return;
    tabs_.erase(tabs_.begin() + index);
    stackedWidget_->widgetRemoved(index);
}

void HToolBar::setTabHeight(int height)
{
    tabHeight_ = height;
}

void HToolBar::setHeight(int height)
{
    height_ = height;
}

void HToolBar::setWidth(int width)
{
    width_ = width;
}

void HToolBar::setTabStyle(TabStyle style)
{
    for (auto* btn : tabs_) {
        btn->setToolButtonStyle((Qt::ToolButtonStyle)style);
    }
    tabStyle_ = style;
}

HToolBar::ToolBarDiretion HToolBar::getToolBarDirection() const
{
    return direction_;
}

HToolBar::TabStyle HToolBar::getTabStyle() const
{
    return tabS;
}

void HToolBar::setTabWidth(int width)
{
    tabWidth_ = width;
}

void HToolBar::initToolBar() {
//    if (HToolBar->objectName().isEmpty())
//        HToolBar->setObjectName(QString::fromUtf8("HToolBar"));
//    HToolBar->resize(688, 607);
//    widgetTitle = new QWidget(HToolBar);
//    widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
//    widgetTitle->setGeometry(QRect(0, 0, 681, 71));
//    widgetTop = new QWidget(widgetTitle);
//    widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
//    widgetTop->setGeometry(QRect(0, 0, 681, 71));
//    toolButton = new QToolButton(widgetTop);
//    toolButton->setObjectName(QString::fromUtf8("toolButton"));
//    toolButton->setGeometry(QRect(0, 0, 101, 71));
//    toolButton_2 = new QToolButton(widgetTop);
//    toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
//    toolButton_2->setGeometry(QRect(100, 0, 101, 71));
//    toolButton_3 = new QToolButton(widgetTop);
//    toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
//    toolButton_3->setGeometry(QRect(200, 0, 101, 71));
//    stackedWidget = new QStackedWidget(HToolBar);
//    stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
//    stackedWidget->setGeometry(QRect(0, 70, 681, 531));
//    page = new QWidget();
//    page->setObjectName(QString::fromUtf8("page"));
//    toolButton_4 = new QToolButton(page);
//    toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
//    toolButton_4->setGeometry(QRect(200, 20, 101, 71));
//    toolButton_5 = new QToolButton(page);
//    toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
//    toolButton_5->setGeometry(QRect(100, 20, 101, 71));
//    toolButton_6 = new QToolButton(page);
//    toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
//    toolButton_6->setGeometry(QRect(0, 20, 101, 71));
//    stackedWidget->addWidget(page);
//    page_2 = new QWidget();
//    page_2->setObjectName(QString::fromUtf8("page_2"));
//    stackedWidget->addWidget(page_2);

//    retranslateUi(HToolBar);

//    QMetaObject::connectSlotsByName(HToolBar);

    this->resize(2 * width_, 2 * height_);

    widgetTop_->setObjectName(QString::fromUtf8("widgetTop"));
    QRect topGeometry, stackGeometry;
    if (direction_ == ToolBarDiretion::Horizontal) {
        topGeometry = QRect(posX_, posY_, width_, tabHeight_);
        stackGeometry = QRect(posX_, posY_ + tabHeight_, width_, height_ - tabHeight_);
    }
    else {
        topGeometry = QRect(posX_, posY_, tabWidth_, height_);
        stackGeometry = QRect(posX_ + tabWidth_, posY_, width_ - tabWidth_, height_);
    }
    widgetTop_->setGeometry(topGeometry);
    stackedWidget_->setGeometry(stackGeometry);

    this->setProperty("form", "true");
    //ui->widgetTitle->setProperty("form", "title");
    widgetTop_->setProperty("nav", direction_ == Horizontal ? "top" : "left");
    setTabStyle(widgetTop_);

    auto btnList = widgetTop_->findChildren<QToolButton*>();
    for (auto* btn : btnList) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    //btnMain->click();
    QTabWidget tabWidget;
    //tabWidget.addTab();

}

void HToolBar::setTabStyle(QWidget* widget)
{


    QString strBorder;
    if (borderType_ == top) {
        strBorder = QString("border-width:%1px,0px,0px,0px; "
                            "padding:%1px,%2px,%2px,%2px;")
                .arg(borderWidth_).arg(borderWidth_ * 2);
    }
    else if (borderType_ == right) {
        strBorder = QString("border-width:0px,%1px,0px,0px; "
                            "padding:%2px,%1px,%2px,%2px;")
                .arg(borderWidth_).arg(borderWidth_ * 2);
    }
    else if (borderType_ == bottom) {
        strBorder = QString("border-width:0px,0px,%1px,0px; "
                            "padding:%2px,%2px,%1px,%2px;")
                .arg(borderWidth_).arg(borderWidth_ * 2);
    }
    else if (borderType_ == left) {
        strBorder = QString("border-width:0px,0px,0px,%1px; "
                            "padding:%2px,%2px,%2px,%1px;")
                .arg(borderWidth_).arg(borderWidth_ * 2);
    }
    QStringList qss;
    if (tabStyle_ == TabStyle::TabTextBesideIcon) {
        qss.append(QString());
    }
    else {

    }

    widget->setStyleSheet();

}


void HToolBar::buttonClick() {
    auto* b = (QToolButton*)sender();
    auto name = b->text();
    int index = 0, i = 0;
    for (QToolButton* btn : tabs_) {
        if (btn == b) {
            btn->setChecked(true);
            index = i;
        }
        else
            btn->setChecked(false);
        ++i;
    }

    stackedWidget_->setCurrentIndex(index);
}



