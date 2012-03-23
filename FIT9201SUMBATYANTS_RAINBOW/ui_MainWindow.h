/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created: Thu Mar 22 15:36:28 2012
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QPushButton>
#include <QtGui/QSlider>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QWidget *controlWidget;
    QHBoxLayout *horizontalLayout_2;
    QWidget *rainbowControlWidget;
    QVBoxLayout *verticalLayout_3;
    QWidget *playingWidget;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startButton;
    QPushButton *stopButton;
    QPushButton *clearButton;
    QWidget *speedWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *speedLabel;
    QSlider *speedSlider;
    QWidget *sizeWidget;
    QHBoxLayout *horizontalLayout_3;
    QWidget *sizeLabelWidget;
    QVBoxLayout *verticalLayout_4;
    QLabel *widthLabel;
    QLabel *heightWidget;
    QWidget *sizeSpinWidget;
    QVBoxLayout *verticalLayout_5;
    QSpinBox *widthSpin;
    QSpinBox *heightSpin;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        controlWidget = new QWidget(centralwidget);
        controlWidget->setObjectName(QString::fromUtf8("controlWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(controlWidget->sizePolicy().hasHeightForWidth());
        controlWidget->setSizePolicy(sizePolicy);
        horizontalLayout_2 = new QHBoxLayout(controlWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        rainbowControlWidget = new QWidget(controlWidget);
        rainbowControlWidget->setObjectName(QString::fromUtf8("rainbowControlWidget"));
        verticalLayout_3 = new QVBoxLayout(rainbowControlWidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        playingWidget = new QWidget(rainbowControlWidget);
        playingWidget->setObjectName(QString::fromUtf8("playingWidget"));
        horizontalLayout_4 = new QHBoxLayout(playingWidget);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        startButton = new QPushButton(playingWidget);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout_4->addWidget(startButton);

        stopButton = new QPushButton(playingWidget);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout_4->addWidget(stopButton);

        clearButton = new QPushButton(playingWidget);
        clearButton->setObjectName(QString::fromUtf8("clearButton"));

        horizontalLayout_4->addWidget(clearButton);


        verticalLayout_3->addWidget(playingWidget);

        speedWidget = new QWidget(rainbowControlWidget);
        speedWidget->setObjectName(QString::fromUtf8("speedWidget"));
        horizontalLayout = new QHBoxLayout(speedWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        speedLabel = new QLabel(speedWidget);
        speedLabel->setObjectName(QString::fromUtf8("speedLabel"));

        horizontalLayout->addWidget(speedLabel);

        speedSlider = new QSlider(speedWidget);
        speedSlider->setObjectName(QString::fromUtf8("speedSlider"));
        speedSlider->setMaximum(100);
        speedSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(speedSlider);


        verticalLayout_3->addWidget(speedWidget);


        horizontalLayout_2->addWidget(rainbowControlWidget);

        sizeWidget = new QWidget(controlWidget);
        sizeWidget->setObjectName(QString::fromUtf8("sizeWidget"));
        horizontalLayout_3 = new QHBoxLayout(sizeWidget);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        sizeLabelWidget = new QWidget(sizeWidget);
        sizeLabelWidget->setObjectName(QString::fromUtf8("sizeLabelWidget"));
        verticalLayout_4 = new QVBoxLayout(sizeLabelWidget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        widthLabel = new QLabel(sizeLabelWidget);
        widthLabel->setObjectName(QString::fromUtf8("widthLabel"));

        verticalLayout_4->addWidget(widthLabel);

        heightWidget = new QLabel(sizeLabelWidget);
        heightWidget->setObjectName(QString::fromUtf8("heightWidget"));

        verticalLayout_4->addWidget(heightWidget);


        horizontalLayout_3->addWidget(sizeLabelWidget);

        sizeSpinWidget = new QWidget(sizeWidget);
        sizeSpinWidget->setObjectName(QString::fromUtf8("sizeSpinWidget"));
        verticalLayout_5 = new QVBoxLayout(sizeSpinWidget);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        widthSpin = new QSpinBox(sizeSpinWidget);
        widthSpin->setObjectName(QString::fromUtf8("widthSpin"));
        widthSpin->setMinimum(300);
        widthSpin->setMaximum(2000);

        verticalLayout_5->addWidget(widthSpin);

        heightSpin = new QSpinBox(sizeSpinWidget);
        heightSpin->setObjectName(QString::fromUtf8("heightSpin"));
        heightSpin->setMinimum(300);
        heightSpin->setMaximum(2000);

        verticalLayout_5->addWidget(heightSpin);


        horizontalLayout_3->addWidget(sizeSpinWidget);


        horizontalLayout_2->addWidget(sizeWidget);


        verticalLayout_2->addWidget(controlWidget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        startButton->setText(QApplication::translate("MainWindow", "Start", 0, QApplication::UnicodeUTF8));
        stopButton->setText(QApplication::translate("MainWindow", "Stop", 0, QApplication::UnicodeUTF8));
        clearButton->setText(QApplication::translate("MainWindow", "Clear", 0, QApplication::UnicodeUTF8));
        speedLabel->setText(QApplication::translate("MainWindow", "Speed", 0, QApplication::UnicodeUTF8));
        widthLabel->setText(QApplication::translate("MainWindow", "Width", 0, QApplication::UnicodeUTF8));
        heightWidget->setText(QApplication::translate("MainWindow", "Height", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
