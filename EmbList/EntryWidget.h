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
        TEXT = 0,
        VIDEO,
        PICTURE,
        AUDIO,
        LIVE
    };
    explicit EntryWidget(QWidget *parent = nullptr);
    EntryWidget(const QString& name, Type typeQ, QWidget *parent = nullptr);
    ~EntryWidget();

private:
    Ui::EntryWidget *ui;
};

#endif // ENTRYWIDGET_H
