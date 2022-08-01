/********************************************************************************
** Form generated from reading UI file 'HToolBar.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HTOOLBAR_H
#define UI_HTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_HToolBar
{
public:
    QWidget *widgetTitle;
    QWidget *widgetTop;
    QToolButton *toolButton;
    QToolButton *toolButton_2;
    QToolButton *toolButton_3;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QToolButton *toolButton_4;
    QToolButton *toolButton_5;
    QToolButton *toolButton_6;
    QWidget *page_2;

    void setupUi(QWidget *HToolBar)
    {
        if (HToolBar->objectName().isEmpty())
            HToolBar->setObjectName(QString::fromUtf8("HToolBar"));
        HToolBar->resize(688, 607);
        widgetTitle = new QWidget(HToolBar);
        widgetTitle->setObjectName(QString::fromUtf8("widgetTitle"));
        widgetTitle->setGeometry(QRect(0, 0, 681, 71));
        widgetTop = new QWidget(widgetTitle);
        widgetTop->setObjectName(QString::fromUtf8("widgetTop"));
        widgetTop->setGeometry(QRect(0, 0, 681, 71));
        toolButton = new QToolButton(widgetTop);
        toolButton->setObjectName(QString::fromUtf8("toolButton"));
        toolButton->setGeometry(QRect(0, 0, 101, 71));
        toolButton_2 = new QToolButton(widgetTop);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));
        toolButton_2->setGeometry(QRect(100, 0, 101, 71));
        toolButton_3 = new QToolButton(widgetTop);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));
        toolButton_3->setGeometry(QRect(200, 0, 101, 71));
        stackedWidget = new QStackedWidget(HToolBar);
        stackedWidget->setObjectName(QString::fromUtf8("stackedWidget"));
        stackedWidget->setGeometry(QRect(0, 70, 681, 531));
        page = new QWidget();
        page->setObjectName(QString::fromUtf8("page"));
        toolButton_4 = new QToolButton(page);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));
        toolButton_4->setGeometry(QRect(200, 20, 101, 71));
        toolButton_5 = new QToolButton(page);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));
        toolButton_5->setGeometry(QRect(100, 20, 101, 71));
        toolButton_6 = new QToolButton(page);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));
        toolButton_6->setGeometry(QRect(0, 20, 101, 71));
        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QString::fromUtf8("page_2"));
        stackedWidget->addWidget(page_2);

        retranslateUi(HToolBar);

        QMetaObject::connectSlotsByName(HToolBar);
    } // setupUi

    void retranslateUi(QWidget *HToolBar)
    {
        HToolBar->setWindowTitle(QCoreApplication::translate("HToolBar", "HToolBar", nullptr));
        toolButton->setText(QCoreApplication::translate("HToolBar", "\346\234\254\345\234\260\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        toolButton_2->setText(QCoreApplication::translate("HToolBar", "\344\272\221\347\253\257\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        toolButton_3->setText(QCoreApplication::translate("HToolBar", "MP4\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        toolButton_4->setText(QCoreApplication::translate("HToolBar", "MP4\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        toolButton_5->setText(QCoreApplication::translate("HToolBar", "\344\272\221\347\253\257\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
        toolButton_6->setText(QCoreApplication::translate("HToolBar", "\346\234\254\345\234\260\345\257\274\345\207\272\350\256\276\347\275\256", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HToolBar: public Ui_HToolBar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HTOOLBAR_H
