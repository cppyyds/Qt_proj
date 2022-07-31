/********************************************************************************
** Form generated from reading UI file 'EmbList.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMBLIST_H
#define UI_EMBLIST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_EmbList
{
public:
    QListWidget *listWidget;
    QComboBox *comboBox;
    QLabel *label;

    void setupUi(QWidget *EmbList)
    {
        if (EmbList->objectName().isEmpty())
            EmbList->setObjectName(QString::fromUtf8("EmbList"));
        EmbList->resize(420, 413);
        listWidget = new QListWidget(EmbList);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(0, 70, 381, 291));
        comboBox = new QComboBox(EmbList);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(320, 30, 69, 22));
        label = new QLabel(EmbList);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 30, 61, 21));

        retranslateUi(EmbList);

        QMetaObject::connectSlotsByName(EmbList);
    } // setupUi

    void retranslateUi(QWidget *EmbList)
    {
        EmbList->setWindowTitle(QCoreApplication::translate("EmbList", "EmbList", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("EmbList", "\345\205\250\351\203\250", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("EmbList", "\346\226\207\346\234\254", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("EmbList", "\350\247\206\351\242\221", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("EmbList", "\345\233\276\347\211\207", nullptr));
        comboBox->setItemText(4, QCoreApplication::translate("EmbList", "\347\233\264\346\222\255", nullptr));
        comboBox->setItemText(5, QCoreApplication::translate("EmbList", "\351\237\263\351\242\221", nullptr));

        label->setText(QCoreApplication::translate("EmbList", "\345\265\214\345\205\245\345\210\227\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class EmbList: public Ui_EmbList {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMBLIST_H
