#ifndef HTOOLBAR_H
#define HTOOLBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class HToolBar; }
QT_END_NAMESPACE

class HToolBar : public QWidget
{
    Q_OBJECT

public:
    HToolBar(QWidget *parent = nullptr);
    ~HToolBar();
public slots:
    void buttonClick();
private:

    void initToolBar();
    Ui::HToolBar *ui;
};
#endif // HTOOLBAR_H
