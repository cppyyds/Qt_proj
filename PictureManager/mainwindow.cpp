//MainWindow.cpp
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "picturemodel.h"
#include "pictureproxymodel.h"

#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent)
{
    mListView = new MyListView(this);

    PictureModel* pic_model = new PictureModel(this);
    PictureProxyModel* pic_proxy_model = new PictureProxyModel(this);
    pic_proxy_model->setSourceModel(pic_model);

    QItemSelectionModel* pictureSelectionModel = new QItemSelectionModel(pic_proxy_model, this);

    mListView->setPictureModel(pic_proxy_model);
    mListView->setPictureSelectionModel(pictureSelectionModel);

    pic_model->loadPictures();

    QHBoxLayout* main_layout = new QHBoxLayout(this);
    main_layout->addWidget(mListView);
    this->setLayout(main_layout);
    this->setFixedSize(910,600);
}

MainWindow::~MainWindow()
{
}
