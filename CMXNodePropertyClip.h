#ifndef CMXNODEPROPERTYCLIP_H
#define CMXNODEPROPERTYCLIP_H

#include <QWidget>

namespace Ui {
class CMXNodePropertyClip;
}
class QScrollArea;
class QPushButton;
class CMXNodePropertyClip : public QWidget
{
    Q_OBJECT

public:
    explicit CMXNodePropertyClip(QWidget *parent = nullptr);
    ~CMXNodePropertyClip();

protected:
    QScrollArea *m_pScroll;
    QWidget* m_pMainWidget;

    QPushButton* m_pAddMask;
    QPushButton* m_pAddClip;
    QPushButton* m_pAddLive;
    QPushButton* m_pAdd3DMode;
private:
    Ui::CMXNodePropertyClip *ui;
};

#endif // CMXNODEPROPERTYCLIP_H
