#include <qtextcodec.h>
#include <QDir>
#include <qDebug>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dirscan.h"





MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    qDebug() << "MainWindow start";
    //QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));
    ui->setupUi(this);

    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("目录索引");
    ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    dirScan_ = new DirScan();
    //setCentralWidget(ui->treeWidget);
    connect(ui->treeWidget, SIGNAL(itemClicked(QTreeWidgetItem *, int)), this, SLOT(ItemSelected(QTreeWidgetItem*, int)));

    connect(this, SIGNAL(ScanByPath(const QString &)), dirScan_, SLOT(Scan(const QString&)));

    connect(dirScan_, SIGNAL(ItemScanned(const QString&, const  QFileInfo&, bool)), this, SLOT(addItem(const QString&, const  QFileInfo&, bool)));

    connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), this, SLOT(popMenu(const QPoint&)));

    init();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::init()
{
    QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget,  QStringList(QString(tr("我的电脑"))));
    //top->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
    QList<QTreeWidgetItem*> root;
    root.append(top);
    ui->treeWidget->insertTopLevelItems(0, root);
}

void MainWindow::deleteItem()
{
    qDebug() << "deleteItem";
    auto* item = ui->treeWidget->currentItem();

    QString path = getAbsolutePath(item, 0);
    if (isDir(path)) deleteDir(path);
    else {  // 如果是文件，直接删除
        QFileInfo file(path);
        file.dir().remove(file.fileName());
    }

    // item的父节点释放item
    item->parent()->removeChild(item);
    delete item;
}

void MainWindow::RenameItem()
{
    qDebug() << "RenameItem";
    auto* item = ui->treeWidget->currentItem();
    before_ = item->text(0);
    ui->treeWidget->editItem(item);

    connect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(RenameEntry(QTreeWidgetItem*)));
}

void MainWindow::RenameEntry(QTreeWidgetItem* item)
{
    Q_ASSERT(item == ui->treeWidget->currentItem());
    QString after = item->text(0);
    if (before_ == after) return;

    QString newPath = getAbsolutePath(item, 0);
    QString dirPath = newPath.mid(0, newPath.lastIndexOf('\\') + 1);
    QString oldPath = dirPath + before_;

    if (!isDir(oldPath)) { // 如果是文件的话，直接重命名然后返回
        QFile file(oldPath);
        Q_ASSERT(file.rename(after));
        return;
    }

    QDir dir(dirPath);
    dir.rename(before_, after);
 
    Q_ASSERT(dirToItem_.contains(oldPath));
    Q_ASSERT(item == dirToItem_.find(oldPath).value());

    RecurChangePath(oldPath ,newPath);

    // 避免第二次之后重命名出现问题，这句语句不能少
    disconnect(ui->treeWidget, SIGNAL(itemChanged(QTreeWidgetItem*, int)), this, SLOT(RenameEntry(QTreeWidgetItem*)));

}

bool MainWindow::deleteDir(const QString& path)
{
    if (path.isEmpty()) return false;
    QDir dir(path);
    if (!dir.exists()) return true;

    // 有两种情况，1.路径path的目录已经加载为TreeItem 
    // 2.还未加载为TreeItem，两种情况都要向下继续删除文件和目录
    QTreeWidgetItem* item = nullptr;
    if (dirToItem_.contains(path)) 
        item = dirToItem_.find(path).value();

    dir.setFilter(QDir::AllEntries | QDir::NoDotAndDotDot);
    QFileInfoList fileList = dir.entryInfoList();
    bool isDeletedOk = true;
    for (auto& file: fileList) {
        if (file.isFile()) {
            isDeletedOk &= file.dir().remove(file.fileName());

        }
        else {
            isDeletedOk &= deleteDir(file.absoluteFilePath().replace('/','\\'));
        }
    }

    // 释放孩子结点的工作由父节点完成
    if (item != nullptr) {
        for (int i = 0; i < item->childCount(); ++i) {
            auto* childItem = item->child(i);
            item->removeChild(childItem);
            delete childItem;
        }
        dirToItem_.erase(dirToItem_.find(path));
    }

    isDeletedOk &= dir.rmdir(dir.absolutePath());
    return isDeletedOk;
}

inline bool MainWindow::isDir(const QString& path) const
{
    return dirToItem_.contains(path);
}

void MainWindow::RecurChangePath(const QString& oldPath, const QString& newPath)
{
    if (!dirToItem_.contains(oldPath)) return;
    auto it = dirToItem_.find(oldPath);
    auto* item = it.value();
    dirToItem_.erase(it);
    dirToItem_.insert(newPath, item);

    QDir dir(newPath);
    QFileInfoList fileList = dir.entryInfoList();
    for (auto& file : fileList) {
        if (file.isDir()) {
            QString subOldPath = oldPath + '\\' + file.fileName();
            QString subNewPath = newPath + '\\' + file.fileName();
            RecurChangePath(subOldPath, subNewPath);
        }
    }
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
            //item->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);
            dirToItem_.insert(fullPath, item);
        }
        else {
            QTreeWidgetItem *item = dirToItem_.value(fullPath);
            QTreeWidgetItem *subItem = new QTreeWidgetItem(QStringList(itemInfo.fileName()));
            subItem->setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable);

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

void MainWindow::popMenu(const QPoint& point)
{
    auto* item = ui->treeWidget->itemAt(point);
    QRegExp reg("([A-D]):/");
    int pos = 0;
    if (item != nullptr)
        pos = reg.indexIn(item->text(0));
    // 当结点不为"我的电脑"或磁盘名时
    if (item != nullptr && item->text(0) != tr("我的电脑") && pos <= -1) {
        QAction *pDelAction = new QAction("Delete", this);
        QAction *pReNameAction = new QAction("Rename", this);

        connect(pDelAction, SIGNAL(triggered()), this, SLOT(deleteItem()));
        connect(pReNameAction, SIGNAL(triggered()), this, SLOT(RenameItem()));

        QMenu *popMenu = new QMenu(this);  // 定义⼀个右键弹出菜单
        popMenu->addAction(pDelAction);  // 往菜单内添加QAction 该action在前⾯⽤设计器定义了
        popMenu->addAction(pReNameAction);
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













