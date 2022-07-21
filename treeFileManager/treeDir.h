#ifndef TREEDIR_H
#define TREEDIR_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QFileInfo>
#include <QWidget>


namespace Ui {
class treeDir;
}

class DirScan;
class treeDir : public QWidget
{
    Q_OBJECT

public:
    explicit treeDir(QWidget *parent = nullptr);
    ~treeDir();
signals:
    void ScanByPath(const QString&);
public slots:
    void ItemSelected(QTreeWidgetItem* item, int col);
    void addItem(const QString& fullPath,const QFileInfo& file, bool);
    void popMenu(const QPoint& point);
    void deleteItem();
    void RenameItem();
    void RenameEntry(QTreeWidgetItem*);
private:
    QString getAbsolutePath(QTreeWidgetItem* item, int col);
    void init();
    bool deleteDir(const QString& path);
    bool isDir(const QString&) const;
    void RecurChangePath(const QString& oldPath, const QString& newPath);

    Ui::treeDir *ui;
    DirScan *dirScan_;

    QHash<QString, QTreeWidgetItem*> dirToItem_;

    QString before_;

};

#endif // TREEDIR_H
