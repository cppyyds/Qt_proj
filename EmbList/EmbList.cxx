#include <QListWidgetItem>
#include <QMouseEvent>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDebug>
#include <algorithm>
#include <QString>


#include "EmbList.h"
#include "ui_EmbList.h"
#include "common.h"

EmbList::EmbList(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::EmbList)
    , showType_((Type)0)
    , showTypeName_(ChQString("ȫ��"))
{
    ui->setupUi(this);
//    ui->listWidget->addItem();
//    QListWidgetItem* item = new QListWidgetItem();
//    ui->listWidget->setItemWidget(,);

    connect(ui->comboBox, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(condition_show(const QString &)));
    showType_ = (Type)100;
    addEntry(QString::fromLocal8Bit("���μ����μ����μ����μ����μ����μ����μ����μ����μ����μ�"), Type::VIDEO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    addEntry(QString::fromLocal8Bit("ҹ��"), Type::AUDIO);
    showType_ = (Type)0;
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
    unique_ptr<EntryWidget> ptr(new EntryWidget(type, name));
    entrys_.push_back(std::move(ptr));
    EntryWidget *newEntry = entrys_.back().get();
    if (showType_ == 0 || showType_ == type) {
        condition_show(showTypeName_);
    }
    //condition_show();
//    QListWidgetItem* item = new QListWidgetItem(ui->listWidget);
//    item->setSizeHint(QSize(item->sizeHint().width(), 250));

//    newEntry->setSizeIncrement(QSize(item->sizeHint().width(), 250));
//    ui->listWidget->setItemWidget(item, newEntry);
}

void EmbList::deleteEntry(EntryWidget *entry)
{
    auto ret = std::find_if(entrys_.begin(), entrys_.end(), [&entry](auto& it){
        if (entry == it.get()) {
            return true;
        }
    });
    if (ret != entrys_.end()) {
        entrys_.erase(ret);
    }
}

void EmbList::deleteEntry(QListWidgetItem *item)
{
    EntryWidget* entry = static_cast<EntryWidget*>(ui->listWidget->itemWidget(item));
    deleteEntry(entry);
    ui->listWidget->removeItemWidget(item);
}

void EmbList::condition_show(const QString &name)
{
    qDebug() << "condition_show";

    if (name == ChQString("ȫ��")) {
        showType_ = (Type)0;
        showTypeName_ = ChQString("ȫ��");
    } 
    else if (name == ChQString("��Ƶ")) {
        showType_ = Type::AUDIO;
        showTypeName_ = ChQString("��Ƶ");
    }
    else if (name == ChQString("ֱ��")) {
        showType_ = Type::LIVE;
        showTypeName_ = ChQString("ֱ��");
    }
    else if (name == ChQString("ͼƬ")) {
        showType_ = Type::PICTURE;
        showTypeName_ = ChQString("ͼƬ");
    }
    else if (name == ChQString("�ı�")) {
        showType_ = Type::TEXT;
        showTypeName_ = ChQString("�ı�");
    }
    else if (name == ChQString("��Ƶ")) {
        showType_ = Type::VIDEO;
        showTypeName_ = ChQString("��Ƶ");
    }
    int count = ui->listWidget->children().count();
    for (int i = 0; i < count; ++i) {
        delete ui->listWidget->takeItem(0);
    }  

    //ui->listWidget->disconnect();
    //ui->listWidget->clear();
    //listItems_.clear();
    for (auto& entry : entrys_) {
        if (showType_ == 0 || entry.get()->getType() == showType_) {
            auto* item = new QListWidgetItem();
            //listItems_.push_back(std::move(ptr));
            //QListWidgetItem *item = listItems_.back().get();
            ui->listWidget->addItem(item);
            ui->listWidget->setItemWidget(item, entry.get());
        }
    }
    qDebug() << ui->listWidget->children().count();
    //ui->listWidget->update();
}





