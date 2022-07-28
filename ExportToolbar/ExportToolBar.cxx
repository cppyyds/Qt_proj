#include <QPushButton>
#include <QToolButton>
#include <QList>

#include "ExportToolBar.h"
#include "ui_ExportToolBar.h"
#include "IconHelper.h"

ExportToolBar::ExportToolBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::ExportToolBar)
{
    ui->setupUi(this);
    initToolBar();
}



ExportToolBar::~ExportToolBar()
{
    delete ui;
}

void ExportToolBar::buttonClick()
{
    QToolButton* selected = (QToolButton*)sender();
    QString name = selected->text();

    QList<QToolButton*> btns = ui->widgetLeft->findChildren<QToolButton*>();
    for (auto* btn : btns) {
        if (btn == selected) {
            btn->setChecked(true);
            btn->setIcon(IconHelper::Instance()->getPixmap(btn, false));
        }
        else {
            btn->setChecked(false);
            btn->setIcon(IconHelper::Instance()->getPixmap(btn, true));
        }
    }

    // 设置右边的页面切换
    if (name == "场景") {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (name == "视角") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "热点") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "嵌入") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "遮罩") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "通用") {
        ui->stackedWidget->setCurrentIndex(1);
    }


}




void ExportToolBar::initToolBar()
{
    this->setProperty("form", true);
    //this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinMaxButtonsHint);

    QSize icoSize(32, 32);
    // 设置导航按钮
    auto BtnList = ui->widgetLeft->findChildren<QToolButton*>();

    btns = BtnList;
    pixChars << 0xf030 << 0xf03e << 0xf247 << 0xf030 << 0xf03e << 0xf247;

    for (auto* btn : BtnList) {
        //btn->setIconSize(icoSize);
        btn->setCheckable(true);
        btn->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }
    // 默认第一个页面是最先显示的



    //ui->widgetLeft->setStyleSheet(QString("QWidget[flag=\"left\"] QToolButton{min-height:%1px;max-height:%1px;}").arg(150));
    qDebug() << ui->widgetLeft->styleSheet();
    IconHelper::Instance()->setStyle(ui->widgetLeft, btns, pixChars, 15, 35, 25, "left", 4);
    ui->widgetLeft->setProperty("flag", "left");
    ui->toolButton->click();
    qDebug() << "--------------\r\n" << ui->widgetLeft->styleSheet();
}

