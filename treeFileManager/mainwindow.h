#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class DirScan;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void ScanByPath(const QString&);
public slots:
    void ItemSelected(QTreeWidgetItem* item, int col);
    void addItem(const QString& fullPath,const QFileInfo& file, bool);
    void popMenu(const QPoint& point);
    void deleteItem();
    void reNameItem();
private:
    QString getAbsolutePath(QTreeWidgetItem* item, int col);
    void init();
    bool deleteDir(const QString& path);
    bool isDir(const QString&) const;

    Ui::MainWindow *ui;
    DirScan *dirScan_;

    QHash<QString, QTreeWidgetItem*> dirToItem_;
};
#endif // MAINWINDOW_H
