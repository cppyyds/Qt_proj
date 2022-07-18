#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->treeWidget->setColumnCount(1);
    ui->treeWidget->setHeaderLabel("LocalFileSystem");
    dirScan = new DirScan();
    init();
    //! 绑定扫DirScan扫描完的信号，发送过来添加进树
    if(!connect(dirScan , SIGNAL(ItemScaned(QString,QFileInfo,int)) , this , SLOT(AddItem(QString,QFileInfo,int)))){
        qDebug("--error:1--\n");
    }

    //! 绑定本地树控件的单击事件，经过处理后发送出去，参数为点击的path
    if(!connect(ui->treeWidget , SIGNAL(itemClicked(QTreeWidgetItem*,int)) , this , SLOT(selectItem(QTreeWidgetItem* , int)))){
        qDebug("--error:2--\n");
    }

    //! 绑定发送出去的事件，即发送给DirScan的事件
    if(!connect(this , SIGNAL(sendToDirScan(QString)) , dirScan , SLOT(Scan(QString)))){
        qDebug("--error:3--\n");
    }

    qDebug("--structre function--\n");
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::init()
{
    QTreeWidgetItem *top = new QTreeWidgetItem(ui->treeWidget , QStringList(QString(tr("我的电脑"))));
    root.append(top);
    ui->treeWidget->insertTopLevelItems(0 , root);
}

void MainWindow::AddItem(const QString &strRootPath, const QFileInfo &ItemInfo , const int k)
{

    if(ItemInfo.isDir()){

        if(ItemInfo.fileName() == QLatin1String(".") || ItemInfo.fileName() == QLatin1String("..")){
            return ;
        }

        QString fullPath = ItemInfo.absolutePath().replace("/" , "\\") ;

//        if(!QString::compare(strRootPath , rootPath)){
//           return ;
//        }

        qDebug("(fullPath: %s)\n" , fullPath.toLatin1().data());

        // 这个只是第一次走，剩下的肯定都是包含的，因为盘符是在最外面的
        if(!m_StoreDirItem.contains(fullPath)){

            QString showname = ( k ? ItemInfo.fileName() : ItemInfo.filePath() );
            // qDebug("---not----contains----k = %d ---------showname = %s.\n" , k , showname.toLatin1().data());
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget->findItems(QString(tr("我的电脑")) , 0 , 0).at(0) , QStringList(showname));

            m_StoreDirItem.insert(fullPath , item);

        }else{

            qDebug("---------contains---------\n");
            QTreeWidgetItem *item = m_StoreDirItem.value(fullPath);
            QTreeWidgetItem *item_1 = new QTreeWidgetItem(QStringList(ItemInfo.fileName()));

            int j ;
            for(j=0 ; j < item->childCount() ; j++){
                // 如果此目录的下属数据已经加载到treeView中，就跳循环
                if(!QString::compare(ItemInfo.fileName() , item->child(j)->text(0))){
                    break ;
                }
            }

            if(j == item->childCount()){
                item->addChild(item_1);
                m_StoreDirItem.insert(ItemInfo.absoluteFilePath().replace("/","\\") , item_1);
            }
        }

    }else if(ItemInfo.isFile()){
        qDebug(":::::::I am a file.\n");

        QString fileFullPath = ItemInfo.filePath();
        QString filename = ItemInfo.fileName();

        QString file_path ;

        file_path = ItemInfo.absolutePath().replace("/","\\");

        qDebug("::::::file_path = %s\n" , file_path.toLatin1().data());

        if(!m_StoreDirItem.contains(file_path)){

            qDebug("----not contains----\n");
            QTreeWidgetItem *item = new QTreeWidgetItem(ui->treeWidget , QStringList(file_path));
            QTreeWidgetItem *item_1 = new QTreeWidgetItem(item , QStringList(filename));
            item->addChild(item_1);

            m_StoreDirItem.insert(file_path , item);
        }else{

            qDebug("---contains---\n");
            QTreeWidgetItem *item = m_StoreDirItem.value(file_path);
            QTreeWidgetItem *item_1 = new QTreeWidgetItem(QStringList(filename));
            int j ;
            for( j = 0 ; j < item->childCount() ; j++){
                if(!QString::compare(filename , item->child(j)->text(0))){
                    break ;
                }
            }

            qDebug("---j = %d and childCount = %d \n" , j , item->childCount());
            if(j == item->childCount()){
                item->addChild(item_1);
            }
        }
    }

    return ;

}

// 根据点击的节点获取它的绝对路径，然后发送信号给文件系统扫描类对该目录进行扫描
void MainWindow::selectItem(QTreeWidgetItem *item, int index)
{
     QString itemFullPath = getItemFullPath(item);

     qDebug("send signal and itemFullPath = %s ... \n" , itemFullPath.toLatin1().data());
     emit sendToDirScan(itemFullPath);

     return ;
}

//! 通过查找父节点，定位某节点的绝对路径
QString MainWindow::getItemFullPath(QTreeWidgetItem *item)
{
    QString itemFullPath = item->text(0);

    while(item->parent() != NULL && QString::compare(item->parent()->text(0) , QString(tr("我的电脑")))) {
        qDebug("------parentPath = %s\n" , item->parent()->text(0).toLatin1().data());
        itemFullPath = item->parent()->text(0).replace("/","") + "\\" + itemFullPath ;
        qDebug("------itemFullPath = %s\n" , itemFullPath.data());
        item = item->parent();
    }

    if(!QString::compare(item->text(0) , QString(tr("我的电脑")))){
        return QString(tr("我的电脑"));
    }

    return itemFullPath ;
}
