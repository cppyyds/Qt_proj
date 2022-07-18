#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileInfo>
#include <QTreeWidgetItem>
#include <QHash>
#include "dirscan.h"

namespace Ui {
class MainWindow;
}
/*
具体描述为：界面显示类在初始化Init()阶段设置树控件的基本外观以及建立信号与槽的绑定。这里要绑定三个信号与槽：

      1> 本地树控件中的节点点击响应信号与SelectItem槽的绑定，树节点的点击信号是系统行为无需我们手动声明，
        而SelectItem槽的作用是，根据点击的节点获取它的绝对路径，然后发送信号给文件系统扫描类对该目录进行扫描。
        在该connect中，发送者是QTreeWidge树控件，接收者是界面显示本身，信号是系统树控件点击信号itemClicked，
        槽是界面显示类中的selectItem（）；

      2> 绑定发送出去的信号（界面类中定义的信号：sendToDirScan()）与 文件系统扫描类中的处理槽Scan() ，
        即：对点击树节点后，获取它的绝对路径后，触发sendToDirScan信号，将绝对路径发送出去；
        而文件系统扫描类中的Scan槽，收到该绝对路径，就开始扫描该绝对路径下的文件或文件夹，并将符合条件的item再发送给界面显示类。
        在该connect中，发送者是界面显示类，接收者是文件系统扫描类，信号是界面显示类中定义的sendToDirScan，
        槽是文件系统扫描类中的实现Scan；

      3> 绑定文件系统扫描类中扫描到满足条件item的信号ItemScaned() 与 界面显示类中处理添加树节点的槽AddItem()，
        即：文件系统扫描类扫描到目录下满足条件的文件或文件夹后，将扫描结果发送给界面显示类进行处理显示。
        在该connect中，发送者是文件系统扫描类，接收者是界面显示类，信号是文件系统扫描类中定义的ItemScaned()，
        槽是界面显示类中定义的AddItem()；

      从上面的关系我们可以得出这样的一个结论：信号的发送有两种：一种是系统自带的信号；一种是用户自定义的信号。
        对于前者，我们无需声明，只需要绑定特定的处理槽就好，对于后者我们需要自己定义好对应的信号与槽。
        而在很多情况下，槽的处理过程中会包含着信号，比如：在响应树节点点击后的槽中，我们获取到绝对路径后就要发送信号；
        又比如在文件扫描类的扫描槽Scan中，当我们扫描到满足条件的item后，也会发送信号。
*/

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void init();
    QString getItemFullPath(QTreeWidgetItem* item);

protected slots:
    void AddItem(const QString &strRootPath, const QFileInfo &ItemInfo , const int k );
    void selectItem(QTreeWidgetItem * , int);

signals:
    void sendToDirScan(const QString &selectedItem );

private:
    Ui::MainWindow *ui;

private:
    DirScan *dirScan ;
    QList<QTreeWidgetItem *> root ;
    QString rootPath ;

private:
    QHash<QString/*path*/, QTreeWidgetItem *> m_StoreDirItem;
};

#endif // MAINWINDOW_H
