#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>

#include "CMXNodePropertyClip.h"
#include "ui_CMXNodePropertyClip.h"

CMXNodePropertyClip::CMXNodePropertyClip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CMXNodePropertyClip)
{
    ui->setupUi(this);
    m_pScroll = new QScrollArea(this);
    m_pMainWidget = new QWidget();
    m_pScroll->setWidget(m_pMainWidget);
    QVBoxLayout* mainLayout = new QVBoxLayout();
    m_pMainWidget->setLayout(mainLayout);

    QHBoxLayout* btnLayout = new QHBoxLayout();
    mainLayout->addLayout(btnLayout);
    m_pAddMask = new QPushButton(QString::fromLocal8Bit("+ 遮罩"), m_pMainWidget);
    m_pAddClip = new QPushButton(QString::fromLocal8Bit("+ 素材"), m_pMainWidget);
    m_pAddLive = new QPushButton(QString::fromLocal8Bit("+ 直播"), m_pMainWidget);
    m_pAdd3DMode = new QPushButton(QString::fromLocal8Bit("+ 3D模型"), m_pMainWidget);
    btnLayout->addWidget(m_pAddMask);
    btnLayout->addWidget(m_pAddClip);
    btnLayout->addWidget(m_pAddLive);
    btnLayout->addWidget(m_pAdd3DMode);


    mainLayout->();
}

CMXNodePropertyClip::~CMXNodePropertyClip()
{
    delete ui;
}
