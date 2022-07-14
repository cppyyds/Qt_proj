//mylistview.h
#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QWidget>
#include <QItemSelectionModel>
#include <QMouseEvent>
#include <QMenu>

namespace Ui {
class MyListView;
}
class PictureProxyModel;
class MyListView : public QWidget
{
    Q_OBJECT

public:
    explicit MyListView(QWidget *parent = 0);
    ~MyListView();

    //设置数据模型
    void setPictureModel(PictureProxyModel *pictureModel);
    //设置选中的数据模型
    void setPictureSelectionModel(QItemSelectionModel *selectionModel);

private slots:
    void addPictures();
    void delPictures();
    void clearPictures();
    void delAllPicture();
    void delCurrentPicture();
    void showCustomMenu(const QPoint& pos);

private:
    Ui::MyListView *ui;

    //图片数据模型
    PictureProxyModel* mPictureModel;
    //选中元素的数据模型
    QItemSelectionModel* mPictureSelectionModel;
    QModelIndex mCurrentIndex;
    QMenu* m_func_menu = nullptr;
    QAction* m_del_current_pic = nullptr;
};

#endif // MYLISTVIEW_H
