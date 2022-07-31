/********************************************************************************
** Form generated from reading UI file 'EntryWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ENTRYWIDGET_H
#define UI_ENTRYWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EntryWidget
{
public:
    QLabel *visiable;
    QWidget *widget;
    QLabel *name;
    QLabel *icon;

    void setupUi(QWidget *EntryWidget)
    {
        if (EntryWidget->objectName().isEmpty())
            EntryWidget->setObjectName(QString::fromUtf8("EntryWidget"));
        EntryWidget->resize(402, 62);
        visiable = new QLabel(EntryWidget);
        visiable->setObjectName(QString::fromUtf8("visiable"));
        visiable->setGeometry(QRect(10, 0, 21, 21));
        widget = new QWidget(EntryWidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(40, 0, 361, 61));
        name = new QLabel(widget);
        name->setObjectName(QString::fromUtf8("name"));
        name->setGeometry(QRect(0, 0, 281, 21));
        icon = new QLabel(widget);
        icon->setObjectName(QString::fromUtf8("icon"));
        icon->setGeometry(QRect(290, 0, 41, 21));

        retranslateUi(EntryWidget);

        QMetaObject::connectSlotsByName(EntryWidget);
    } // setupUi

    void retranslateUi(QWidget *EntryWidget)
    {
        EntryWidget->setWindowTitle(QCoreApplication::translate("EntryWidget", "Form", nullptr));
        visiable->setText(QCoreApplication::translate("EntryWidget", "\347\234\274\347\235\233", nullptr));
        name->setText(QCoreApplication::translate("EntryWidget", "\345\220\215\347\247\260", nullptr));
        icon->setText(QCoreApplication::translate("EntryWidget", "\345\233\276\346\240\207", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EntryWidget: public Ui_EntryWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ENTRYWIDGET_H
