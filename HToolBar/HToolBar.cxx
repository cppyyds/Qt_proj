#include <QToolButton>
#include <QList>

#include "HToolBar.h"
#include "ui_HToolBar.h"
#define btnMain ui->toolButton

HToolBar::HToolBar(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::HToolBar)
{
    ui->setupUi(this);
    this->initToolBar();
}

HToolBar::~HToolBar()
{
    delete ui;
}


void HToolBar::initToolBar() {
    this->setProperty("form", "true");

    ui->widgetTitle->setProperty("form", "title");
    ui->widgetTop->setProperty("nav", "top");

    auto btnList = ui->widgetTop->findChildren<QToolButton*>();
    for (auto* btn : btnList) {
        btn->setCheckable(true);
        connect(btn, SIGNAL(clicked()), this, SLOT(buttonClick()));
    }

    btnMain->click();

}


void HToolBar::buttonClick() {
    auto* b = (QToolButton*)sender();
    auto name = b->text();

    auto btns = ui->widgetTop->findChildren<QToolButton*>();
    for (QToolButton* btn : btns) {
        if (btn == b) {
            b->setChecked(true);
        }
        else
            b->setChecked(false);
    }

    if (name == "���ص�������") {
        ui->stackedWidget->setCurrentIndex(0);
    }
    else if(name == "�ƶ˵�������") {
        ui->stackedWidget->setCurrentIndex(1);
    }
    else if (name == "MP4��������") {
        ui->stackedWidget->setCurrentIndex(2);
    }
}



