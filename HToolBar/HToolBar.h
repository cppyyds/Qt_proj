#ifndef HTOOLBAR_H
#define HTOOLBAR_H

#include <QWidget>
#include <vector>
#include <unordered_map>


QT_BEGIN_NAMESPACE
namespace Ui { class HToolBar; }
QT_END_NAMESPACE

using std::vector;

class QToolButton;
class QStackedWidget;
class HToolBar : public QWidget
{
    Q_OBJECT

public:
    enum TabStyle {
        TabIconOnly,
        TabTextOnly,
        TabTextBesideIcon,
        TabUnderIcon,
        TabFollowStyle
    };
    enum ToolBarDiretion{
        Horizontal,
        Vertical
    };

    enum BorderType{
        top,
        right,
        bottom,
        left
    };

    HToolBar(QWidget *parent = nullptr);
    ~HToolBar();

    void paintEvent(QPaintEvent*) override;

    // 外部接口
    int addTab(QWidget *widget, const QString &);
    int addTab(QWidget *widget, const QIcon& icon);

    int insertTab(int index, QWidget *widget, const QString &);
    int insertTab(int index, QWidget *widget, const QIcon& icon);

    void removeTab(int index);

    void setTabWidth(int width);
    void setTabHeight(int height);
    void setHeight(int height);
    void setWidth(int width);

    void setTabStyle(TabStyle style);

    void setToolBarDirection(const ToolBarDiretion& direction);
    ToolBarDiretion getToolBarDirection() const;
    TabStyle getTabStyle() const;

public slots:
    void buttonClick();
private:
    void initToolBar();
    void setTabStyle(QWidget*);

    QWidget *widgetTop_;
    vector<QToolButton*> tabs_;
    QStackedWidget *stackedWidget_;

    int width_;
    int height_;
    int tabHeight_;
    int tabWidth_;
    int posX_;
    int posY_;

    ToolBarDiretion direction_;

    // 样式数据
    BorderType borderType_;
    int borderWidth_;
    TabStyle tabStyle_;
};
#endif // HTOOLBAR_H
