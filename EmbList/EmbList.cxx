#include <QListWidgetItem>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>


#include "EmbList.h"
#include "ui_EmbList.h"

EmbList::EmbList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmbList)
{
    ui->setupUi(this);
//    ui->listWidget->addItem();
//    QListWidgetItem* item = new QListWidgetItem();
//    ui->listWidget->setItemWidget(,);
    addEntry(QString::fromLocal8Bit("西游记西游记西游记西游记西游记西游记西游记西游记西游记西游记"), Type::VIDEO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("夜曲"), Type::AUDIO);
    initComboBox();
}


void EmbList::initComboBox()
{
    auto* comb = ui->comboBox;
    //comb->setEditable(true);
    int count = comb->count();

    connect(comb, QOverload<int>::of(&QComboBox::highlighted),
            [=](int index) {
        qDebug() << comb->itemData(index, Qt::ForegroundRole).value<QColor>().name();
        comb->setStyleSheet(QString("selection-color:#00BB9E;"));
    });

//    QObject::connect(comb, QOverload<int>::of(&QComboBox::activated),
//            [=](int index){
//            comb->lineEdit()->setStyleSheet(QString("background-color:%1;").arg(
//                                    comb->itemData(index,Qt::BackgroundRole).value<QColor>().name()));

}

EmbList::~EmbList()
{
    delete ui;
}

void EmbList::addEntry(const QString &name, Type type)
{
    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
    item->setSizeHint(QSize(item->sizeHint().width(), 250));
    EntryWidget *newEntry = new EntryWidget(name, type);
    newEntry->setSizeIncrement(QSize(item->sizeHint().width(), 250));
    ui->listWidget->setItemWidget(item, newEntry);
}



