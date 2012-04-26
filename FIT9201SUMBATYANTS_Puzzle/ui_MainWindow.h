/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu Apr 26 11:17:37 2012
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDial>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *mainWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *controlWidget;
    QVBoxLayout *verticalLayout_2;
    QPushButton *initButton;
    QPushButton *startButton;
    QPushButton *stopButton;
    QDial *dial;
    QWidget *dialLabelWidget;
    QHBoxLayout *horizontalLayout_3;
    QLabel *minLabel;
    QLabel *maxLabel;
    QCheckBox *filterCheckBox;
    QCheckBox *blendCheckBox;
    QSpacerItem *verticalSpacer;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(500, 322);
        mainWidget = new QWidget(MainWindow);
        mainWidget->setObjectName(QString::fromUtf8("mainWidget"));
        mainWidget->setMinimumSize(QSize(500, 300));
        horizontalLayout_2 = new QHBoxLayout(mainWidget);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        controlWidget = new QWidget(mainWidget);
        controlWidget->setObjectName(QString::fromUtf8("controlWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlWidget->sizePolicy().hasHeightForWidth());
        controlWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(controlWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        initButton = new QPushButton(controlWidget);
        initButton->setObjectName(QString::fromUtf8("initButton"));

        verticalLayout_2->addWidget(initButton);

        startButton = new QPushButton(controlWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        verticalLayout_2->addWidget(startButton);

        stopButton = new QPushButton(controlWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        verticalLayout_2->addWidget(stopButton);

        dial = new QDial(controlWidget);
        dial->setObjectName(QString::fromUtf8("dial"));
        dial->setMaximum(360);

        verticalLayout_2->addWidget(dial);

        dialLabelWidget = new QWidget(controlWidget);
        dialLabelWidget->setObjectName(QString::fromUtf8("dialLabelWidget"));
        horizontalLayout_3 = new QHBoxLayout(dialLabelWidget);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        minLabel = new QLabel(dialLabelWidget);
        minLabel->setObjectName(QString::fromUtf8("minLabel"));
        minLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(minLabel);

        maxLabel = new QLabel(dialLabelWidget);
        maxLabel->setObjectName(QString::fromUtf8("maxLabel"));
        maxLabel->setAlignment(Qt::AlignCenter);

        horizontalLayout_3->addWidget(maxLabel);


        verticalLayout_2->addWidget(dialLabelWidget);

        filterCheckBox = new QCheckBox(controlWidget);
        filterCheckBox->setObjectName(QString::fromUtf8("filterCheckBox"));

        verticalLayout_2->addWidget(filterCheckBox);

        blendCheckBox = new QCheckBox(controlWidget);
        blendCheckBox->setObjectName(QString::fromUtf8("blendCheckBox"));

        verticalLayout_2->addWidget(blendCheckBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);


        horizontalLayout_2->addWidget(controlWidget);

        MainWindow->setCentralWidget(mainWidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        initButton->setText(QApplication::translate("MainWindow", "Init", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        minLabel->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        maxLabel->setText(QApplication::translate("MainWindow", "360", 0, QApplication::UnicodeUTF8));
        filterCheckBox->setText(QApplication::translate("MainWindow", "Filter", 0, QApplication::UnicodeUTF8));
        blendCheckBox->setText(QApplication::translate("MainWindow", "Blend", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
