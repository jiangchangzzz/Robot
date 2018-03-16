/********************************************************************************
** Form generated from reading UI file 'OccQt.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OCCQT_H
#define UI_OCCQT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_OccQt
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *OccQt)
    {
        if (OccQt->objectName().isEmpty())
            OccQt->setObjectName(QStringLiteral("OccQt"));
        OccQt->resize(400, 300);
        menuBar = new QMenuBar(OccQt);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        OccQt->setMenuBar(menuBar);
        mainToolBar = new QToolBar(OccQt);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        OccQt->addToolBar(mainToolBar);
        centralWidget = new QWidget(OccQt);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        OccQt->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(OccQt);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        OccQt->setStatusBar(statusBar);

        retranslateUi(OccQt);

        QMetaObject::connectSlotsByName(OccQt);
    } // setupUi

    void retranslateUi(QMainWindow *OccQt)
    {
        OccQt->setWindowTitle(QApplication::translate("OccQt", "OccQt", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OccQt: public Ui_OccQt {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OCCQT_H
