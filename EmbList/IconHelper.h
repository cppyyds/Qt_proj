#ifndef ICONHELPER_H
#define ICONHELPER_H

#include <QObject>
#include <QFont>

class QLabel;
class QAbstractButton;
class IconHelper : public QObject
{
    Q_OBJECT
public:
    explicit IconHelper(QObject *parent = nullptr);
    static IconHelper& instance();
    void setIcon(QLabel *lab, QChar c, quint32 size = 15);
    void setIcon(QAbstractButton *btn, QChar c, quint32 size = 15);
signals:

private:

    QFont iconFont;             //Í¼ÐÎ×ÖÌå
};

#endif // ICONHELPER_H
