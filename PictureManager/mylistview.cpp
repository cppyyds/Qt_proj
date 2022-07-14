//mylistview.cpp
#pragma execution_character_set("utf-8")

#include <QFileDialog>
#include <QInputDialog>
#include <QStandardPaths>
#include <QDebug>

#include "mylistview.h"
#include "picturedelegate.h"
#include "pictureproxymodel.h"
#include "ui_mylistview.h"
#include "picturemodel.h"
#include "picture.h"

MyListView::MyListView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyListView)
{
    ui->setupUi(this);

    //设置元素之间的间隔
    ui->pic_list_view->setSpacing(5);
    //设置尺寸变化策略
    ui->pic_list_view->setResizeMode(QListView::Adjust);
    //设置元素增减的时候的变化模式
    ui->pic_list_view->setFlow(QListView::LeftToRight);
    //设置伸缩的时候是否自动换行
    ui->pic_list_view->setWrapping(true);
    //设置每个元素的代理
    ui->pic_list_view->setItemDelegate(new PictureDelegate(this));

    //开启自定义的菜单
    ui->pic_list_view->setContextMenuPolicy(Qt::CustomContextMenu);

    //初始化功能菜单
    m_func_menu = new QMenu(this);
    m_del_current_pic = new QAction("删除当前图片",this);
    m_func_menu->addAction(m_del_current_pic);
    connect(m_del_current_pic,&QAction::triggered,this,&MyListView::delCurrentPicture);

    //对图片数据进行增删改查
    connect(ui->add_pic_btn, &QPushButton::clicked, this, &MyListView::addPictures);
    connect(ui->clear_btn, &QPushButton::clicked,this, &MyListView::clearPictures);
    connect(ui->del_pic_btn, &QPushButton::clicked, this, &MyListView::delPictures);
    connect(ui->del_all_pic_btn,&QPushButton::clicked,this,&MyListView::delAllPicture);
    connect(ui->pic_list_view,&QListView::customContextMenuRequested,this,&MyListView::showCustomMenu);
}

MyListView::~MyListView()
{
    delete ui;
}


void MyListView::setPictureModel(PictureProxyModel* pictureModel)
{
    mPictureModel = pictureModel;
    ui->pic_list_view->setModel(pictureModel);
}

void MyListView::setPictureSelectionModel(QItemSelectionModel* selectionModel)
{
    mPictureSelectionModel = selectionModel;
    ui->pic_list_view->setSelectionModel(selectionModel);
}

void MyListView::addPictures()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,
                                                          "添加图片",
                                                          QStandardPaths::writableLocation(QStandardPaths::DesktopLocation),
                                                          "Picture files (*.jpg *.png)");
    if (!filenames.isEmpty()) {
        QModelIndex lastModelIndex;
        for (auto filename : filenames) {
            qDebug() << filename;
            Picture picture(filename);
            lastModelIndex = mPictureModel->pictureModel()->addPicture(picture);
            lastModelIndex = mPictureModel->index(lastModelIndex.row(),lastModelIndex.column());
        }
        if(lastModelIndex.isValid())
        {
            ui->pic_list_view->setCurrentIndex(lastModelIndex);
        }
    }
}

void MyListView::delPictures()
{
    if (mPictureSelectionModel->selectedIndexes().isEmpty()) {
        return;
    }
    int row = mPictureSelectionModel->currentIndex().row();
    mPictureModel->sourceModel()->removeRow(row);

    //选中前一个图片
    QModelIndex previousModelIndex = mPictureModel->sourceModel()->index(row - 1, 0);
    if(previousModelIndex.isValid()) {
        previousModelIndex = mPictureModel->index(previousModelIndex.row(),previousModelIndex.column());
        mPictureSelectionModel->setCurrentIndex(previousModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }

    //选中后一个图片
    QModelIndex nextModelIndex = mPictureModel->sourceModel()->index(row, 0);
    if(nextModelIndex.isValid()) {
        nextModelIndex = mPictureModel->index(nextModelIndex.row(),nextModelIndex.column());
        mPictureSelectionModel->setCurrentIndex(nextModelIndex, QItemSelectionModel::SelectCurrent);
        return;
    }
}

void MyListView::clearPictures()
{
    PictureModel* pic_model = (PictureModel*)mPictureModel->sourceModel();
    pic_model->clearPictures();
}

void MyListView::delAllPicture()
{
    PictureModel* pic_model = (PictureModel*)mPictureModel->sourceModel();
    pic_model->deleteAllPictures();
}

void MyListView::delCurrentPicture()
{
    if(mCurrentIndex.isValid())
    {
        PictureModel* pic_model = (PictureModel*)mPictureModel->sourceModel();
        pic_model->removeRow(mCurrentIndex.row());
    }
}

void MyListView::showCustomMenu(const QPoint &pos)
{
    QPoint point = pos;
    mCurrentIndex = ui->pic_list_view->indexAt(pos);
    if(mCurrentIndex.isValid() && mCurrentIndex.row() >= 0)
    {
        m_func_menu->exec(ui->pic_list_view->mapToGlobal(point));
    }
}
