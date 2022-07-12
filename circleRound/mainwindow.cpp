#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopWidget>
#include <QDebug>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    widget_ = new QWidget(this);
    circleRound_ = new circleRound();

    layout_ = new QVBoxLayout();
    layout_->addWidget(circleRound_);

    widget_->setLayout(layout_);
    setCentralWidget(widget_);
    // resize(QDesktopWidget().availableGeometry(this).size() * 0.9);

}

MainWindow::~MainWindow()
{
    if (widget_) delete widget_;
    if (circleRound_) delete circleRound_;
    if(layout_) delete layout_;
    if(ui) delete ui;
    widget_ = nullptr;
    circleRound_ = nullptr;
    layout_ = nullptr;
    ui = nullptr;
}

