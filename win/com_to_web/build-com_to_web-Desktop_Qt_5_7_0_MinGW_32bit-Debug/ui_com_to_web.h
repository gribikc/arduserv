/********************************************************************************
** Form generated from reading UI file 'com_to_web.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_COM_TO_WEB_H
#define UI_COM_TO_WEB_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_com_to_web
{
public:
    QWidget *centralWidget;
    QTextEdit *textEdit;
    QPushButton *pushButton;

    void setupUi(QMainWindow *com_to_web)
    {
        if (com_to_web->objectName().isEmpty())
            com_to_web->setObjectName(QStringLiteral("com_to_web"));
        com_to_web->resize(471, 472);
        centralWidget = new QWidget(com_to_web);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setGeometry(QRect(10, 10, 451, 401));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(10, 420, 75, 23));
        com_to_web->setCentralWidget(centralWidget);

        retranslateUi(com_to_web);

        QMetaObject::connectSlotsByName(com_to_web);
    } // setupUi

    void retranslateUi(QMainWindow *com_to_web)
    {
        com_to_web->setWindowTitle(QApplication::translate("com_to_web", "com_to_web", 0));
        pushButton->setText(QApplication::translate("com_to_web", "Clear", 0));
    } // retranslateUi

};

namespace Ui {
    class com_to_web: public Ui_com_to_web {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_COM_TO_WEB_H