#include <QToolButton>
#include <QVBoxLayout>

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "CardWidget.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage *image = new QImage(":/image/main_help.png");
    vector<QImage*> left;
    left.push_back(new QImage(":/image/main_data.png"));
    left.push_back(new QImage(":/image/main_person.png"));

    vector<QImage*> right;
    right.push_back(new QImage(":/image/main_company.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    right.push_back(new QImage(":/image/main_about.png"));
    QWidget *mainWidget = new QWidget();
    setCentralWidget(mainWidget);

    QVBoxLayout * layout = new QVBoxLayout();
    mainWidget->setLayout(layout);
    CardWidget *card = new CardWidget(this, image, left, right);
    CardWidget *card1 = new CardWidget(this, image, left, right);
    CardWidget *card2 = new CardWidget(this, image, left, right);
    layout->addWidget(card);
    layout->addWidget(card1);
    layout->addWidget(card2);

}

MainWindow::~MainWindow()
{
    delete ui;
}

