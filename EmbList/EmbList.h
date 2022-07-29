#ifndef EMBLIST_H
#define EMBLIST_H

#include <QWidget>

#include "EntryWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EmbList; }
QT_END_NAMESPACE

using Type = EntryWidget::Type;
class EmbList : public QWidget
{
    Q_OBJECT

public:

    EmbList(QWidget *parent = nullptr);
    ~EmbList();

    void addEntry(const QString& name, Type type);

private:
    void initComboBox();
    Ui::EmbList *ui;
};
#endif // EMBLIST_H
