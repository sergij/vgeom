/********************************************************************************
** Form generated from reading UI file 'generator.ui'
**
** Created: Sun Jul 22 11:02:19 2012
**      by: Qt User Interface Compiler version 4.7.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GENERATOR_H
#define UI_GENERATOR_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollBar>

QT_BEGIN_NAMESPACE

class Ui_Generator
{
public:
    QScrollBar *numberScroll;
    QLabel *label;
    QLabel *numberLabel;
    QPushButton *ok;
    QPushButton *cancel;
    QRadioButton *vert;
    QRadioButton *multi;
    QRadioButton *full;

    void setupUi(QDialog *Generator)
    {
        if (Generator->objectName().isEmpty())
            Generator->setObjectName(QString::fromUtf8("Generator"));
        Generator->resize(463, 333);
        numberScroll = new QScrollBar(Generator);
        numberScroll->setObjectName(QString::fromUtf8("numberScroll"));
        numberScroll->setGeometry(QRect(200, 40, 160, 16));
        numberScroll->setOrientation(Qt::Horizontal);
        label = new QLabel(Generator);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 40, 161, 20));
        numberLabel = new QLabel(Generator);
        numberLabel->setObjectName(QString::fromUtf8("numberLabel"));
        numberLabel->setGeometry(QRect(250, 70, 67, 17));
        ok = new QPushButton(Generator);
        ok->setObjectName(QString::fromUtf8("ok"));
        ok->setGeometry(QRect(210, 269, 97, 27));
        cancel = new QPushButton(Generator);
        cancel->setObjectName(QString::fromUtf8("cancel"));
        cancel->setGeometry(QRect(330, 270, 97, 27));
        vert = new QRadioButton(Generator);
        vert->setObjectName(QString::fromUtf8("vert"));
        vert->setGeometry(QRect(50, 110, 201, 22));
        multi = new QRadioButton(Generator);
        multi->setObjectName(QString::fromUtf8("multi"));
        multi->setGeometry(QRect(50, 150, 381, 22));
        full = new QRadioButton(Generator);
        full->setObjectName(QString::fromUtf8("full"));
        full->setGeometry(QRect(50, 190, 311, 22));

        retranslateUi(Generator);

        QMetaObject::connectSlotsByName(Generator);
    } // setupUi

    void retranslateUi(QDialog *Generator)
    {
        Generator->setWindowTitle(QApplication::translate("Generator", "Dialog", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Generator", "\320\232\320\276\320\273\320\270\321\207\320\265\321\201\321\202\320\262\320\276 \320\276\321\202\321\200\320\265\320\267\320\272\320\276\320\262", 0, QApplication::UnicodeUTF8));
        numberLabel->setText(QApplication::translate("Generator", "0", 0, QApplication::UnicodeUTF8));
        ok->setText(QApplication::translate("Generator", "Ok", 0, QApplication::UnicodeUTF8));
        cancel->setText(QApplication::translate("Generator", "Cancel", 0, QApplication::UnicodeUTF8));
        vert->setText(QApplication::translate("Generator", "\320\222\320\265\321\200\321\202\320\270\320\272\320\260\320\273\321\214\320\275\321\213\320\265 \320\276\321\202\321\200\320\265\320\267\320\272\320\270", 0, QApplication::UnicodeUTF8));
        multi->setText(QApplication::translate("Generator", "\320\237\320\265\321\200\320\265\321\201\320\265\321\207\320\265\320\275\320\270\320\265 \320\261\320\276\320\273\320\265\320\265 \320\264\320\262\321\203\321\205 \320\276\321\202\321\200\320\265\320\267\320\272\320\276\320\262 \320\262 \320\276\320\264\320\275\320\276\320\271 \321\202\320\276\321\207\320\272\320\265", 0, QApplication::UnicodeUTF8));
        full->setText(QApplication::translate("Generator", "\320\222\321\201\320\265 \320\276\321\202\321\200\320\265\320\267\320\272\320\270 \320\277\320\265\321\200\320\265\321\201\320\265\320\272\320\260\321\216\321\202\321\201\321\217 \320\274\320\265\320\266\320\264\321\203 \321\201\320\276\320\261\320\276\320\271", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Generator: public Ui_Generator {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GENERATOR_H
