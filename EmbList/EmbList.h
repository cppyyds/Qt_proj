#ifndef EMBLIST_H
#define EMBLIST_H

#include <QWidget>
#include <vector>
#include <memory>
#include <list>
#include <unordered_map>

#include "EntryWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui { class EmbList; }
QT_END_NAMESPACE

using Type = EntryWidget::Type;
using std::vector, std::unique_ptr, std::list;

class QListWidgetItem;
class EmbList : public QWidget
{
    Q_OBJECT

public:

    EmbList(QWidget *parent = nullptr);
    ~EmbList();

    void addEntry(const QString& name, Type type);

    void deleteEntry(QListWidgetItem*);

public slots:
    void condition_show(const QString &);
private:
    void initComboBox();
    void deleteEntry(EntryWidget*);

    Type showType_;
    QString showTypeName_;
    vector<unique_ptr<EntryWidget>> entrys_;
    vector<QListWidgetItem*> listItems_;
    Ui::EmbList *ui;

};
#endif // EMBLIST_H
