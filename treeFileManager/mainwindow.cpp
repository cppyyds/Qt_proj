#include <qtextcodec.h>
#include <QDir>
#include <qDebug>
#include <QHBoxLayout>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "treeDir.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow start";
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    ui->setupUi(this);
    mainWidget_ = new QWidget(this);
    treeDir_ = new treeDir();

    QHBox
}

MainWindow::~MainWindow()
{
    delete ui;
}







