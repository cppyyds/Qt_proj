#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dirscan.h"

#include <qtextcodec.h>



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("目录索引");
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    dirScan_ = new DirScan();
    //setCentralWidget(ui->treeWidget);
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(ItemSelected(QTreeWidgetItem*, int)));

    connect(this, SIGNAL(ScanByPath(const QString &)), dirScan_, SLOT(Scan(const QString&)));

    connect(dirScan_, SIGNAL(ItemScanned(const QString&, const  QFileInfo&, bool)), this, SLOT(addItem(const QString&, const  QFileInfo&, bool)));

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(onCustomContextMenuRequested(const QPoint&)));
    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init()
{
    QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget,  QStringList(QString(tr("我的电脑"))));
    QList<QTreeWidgetItem*> root;
    root.append(top);
    ui->treeWidget->insertTopLevelItems(0, root);
}

void MainWindow::ItemSelected(QTreeWidgetItem *item, int col)
{
    QString fullPath = getAbsolutePath(item, col);
    emit ScanByPath(fullPath);
}

void MainWindow::addItem(const QString& parentPath, const QFileInfo& itemInfo, bool isDrivers)
{
    if (itemInfo.isDir()) {
        if (itemInfo.fileName() == QLatin1String(".") || itemInfo.fileName() == QLatin1String("..")) {
            return ;
        }

        QString fullPath = itemInfo.absolutePath().replace("/", "\\");
        if (isDrivers && !dirToItem_.contains(fullPath)) {
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget->findItems(QString(tr("我的电脑")), 0, 0).at(0), QStringList(itemInfo.filePath()));

            dirToItem_.insert(fullPath, item);
        }
        else {
            QTreeWidgetItem *item = dirToItem_.value(fullPath);
            QTreeWidgetItem *subItem = new QTreeWidgetItem(QStringList(itemInfo.fileName()));
            int i = 0;
            for (; i < item->childCount(); ++i) {
                if (!QString::compare(itemInfo.fileName(), item->child(i)->text(0))) {
                    break;
                }
            }
            // 如果还未加载subItem结点
            if (i == item->childCount()) {
                item->addChild(subItem);
                dirToItem_.insert(itemInfo.absoluteFilePath().replace("/", "\\"), subItem);
            }

        }
    }
    else if (itemInfo.isFile()) {
        QString fullPath = itemInfo.absolutePath().replace("/", "\\");
        QTreeWidgetItem* item = dirToItem_.value(fullPath);
        QTreeWidgetItem* subItem = new QTreeWidgetItem(QStringList(itemInfo.fileName()));

        int i = 0;
        for (; i < item->childCount(); ++i) {
            if (!QString::compare(itemInfo.fileName(), item->child(i)->text(0))) {
                break;
            }
        }
        // 如果还未加载subItem结点
        if (i == item->childCount()) {
            item->addChild(subItem);
        }
        
    }

}

void MainWindow::onCustomContextMenuRequested(const QPoint& point)
{
    auto* item = ui->treeWidget->itemAt(point);
    QRegExp reg("([A-D]):/");
    int pos = 0;
    if (item != nullptr)
        pos = reg.indexIn(item->text(0));
    // 当结点不为"我的电脑"或磁盘名时
    if (item != nullptr && item->text(0) != tr("我的电脑") && pos <= -1) {
    QAction* pDelAction = new QAction("删除", this);
        QMenu* popMenu = new QMenu(this);  // 定义⼀个右键弹出菜单
        popMenu->addAction(pDelAction);  // 往菜单内添加QAction 该action在前⾯⽤设计器定义了
        popMenu->exec(QCursor::pos());
     }
    
     //popMenu->exec(QCursor::pos());  // 弹出右键菜单，菜单位置为光标位
}

QString MainWindow::getAbsolutePath(QTreeWidgetItem *item, int col)
{
    QString path = item->text(col);
    while (item->parent() && QString::compare(QString(tr("我的电脑")), item->parent()->text(col))) {
        path = item->parent()->text(col).replace("/","") + "\\" + path;
        item = item->parent();
    }

    if (!QString::compare(item->text(col), QString(tr("我的电脑")))) {
        return QString(tr("我的电脑"));
    }

    return path;
}













