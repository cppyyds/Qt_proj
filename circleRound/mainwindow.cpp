#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    widget_ = new QWidget(this);
    layout_ = new QHBoxLayout();

    circleRound_ = new circleRound();
    layout_->addWidget(circleRound_);

    widget_->setLayout(layout_);
    setCentralWidget(widget_);
    resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

}

MainWindow::~MainWindow()
{
    delete widget_;
    delete circleRound_;
    delete layout_;
    delete ui;
}

