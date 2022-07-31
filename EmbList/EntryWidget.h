#ifndef ENTRYWIDGET_H
#define ENTRYWIDGET_H

#include <QWidget>

namespace Ui {
class EntryWidget;
}

class EntryWidget : public QWidget
{
    Q_OBJECT

public:
    enum Type{
        TEXT = 1,
        VIDEO,
        PICTURE,
        AUDIO,
        LIVE
    };
    explicit EntryWidget(QWidget *parent = nullptr);
    EntryWidget(Type type, const QString& name = QString::fromLocal8Bit("标题名称"), QWidget *parent = nullptr);
    ~EntryWidget();

    Type getType() const;

private:
    Ui::EntryWidget *ui;

    Type type_;
    QString name_;
};

#endif // ENTRYWIDGET_H
