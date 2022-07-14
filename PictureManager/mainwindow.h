//mainwwindow.h
#ifndef MAINWWINDOW_H
#define MAINWWINDOW_H

#include <QWidget>
#include "mylistview.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    MyListView* mListView=nullptr;
};

#endif // MAINWWINDOW_H
