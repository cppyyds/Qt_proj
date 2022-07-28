#ifndef EXPORTTOOLBAR_H
#define EXPORTTOOLBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class ExportToolBar; }
QT_END_NAMESPACE

class QToolButton;
class ExportToolBar : public QWidget
{
    Q_OBJECT

public:
    ExportToolBar(QWidget *parent = nullptr);
    ~ExportToolBar();

    void setTabNum(int num);

public slots:
    void buttonClick();
private:
    void initToolBar();


    Ui::ExportToolBar *ui;

    int tabNum_;  // ±êÇ©µÄ
    QList<QString> tabNames_;

    QList<int> pixChars;
    QList<QToolButton*> btns;

};
#endif // EXPORTTOOLBAR_H
