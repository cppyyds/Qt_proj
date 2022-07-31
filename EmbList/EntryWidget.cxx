#include "EntryWidget.h"
#include "ui_EntryWidget.h"
#include "IconHelper.h"

EntryWidget::EntryWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::EntryWidget)
{
    ui->setupUi(this);
}

EntryWidget::EntryWidget(Type type, const QString &name, QWidget *parent):
    QWidget(parent),
    ui(new Ui::EntryWidget),
    type_(type),
    name_(name)
{
    ui->setupUi(this);
    ui->name->setText(name);
    IconHelper::instance().setIcon(ui->visiable, QChar(0xf06e), 12);
    switch(type) {
        case Type::AUDIO:
            IconHelper::instance().setIcon(ui->icon, QChar(0xf001));
        break;
        case Type::VIDEO:
            IconHelper::instance().setIcon(ui->icon, QChar(0xf008));
        break;
        case Type::LIVE:
            IconHelper::instance().setIcon(ui->icon, QChar(0xf03d));
        break;
        case Type::PICTURE:
            IconHelper::instance().setIcon(ui->icon, QChar(0xf03e));
        break;
        case Type::TEXT:
            IconHelper::instance().setIcon(ui->icon, QChar(0xf893));
        break;
        default:
        break;
    }

}

EntryWidget::~EntryWidget()
{
    delete ui;
}

EntryWidget::Type EntryWidget::getType() const
{
    return type_;
}
