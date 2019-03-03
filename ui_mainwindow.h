/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "myprogressbar.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionHelp;
    QAction *actionEnglish;
    QAction *actionRussian;
    QAction *actionStart_Game;
    QAction *actionQuit;
    QAction *actionSettings;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_4;
    QSplitter *splitterHorizontal;
    QSplitter *splitterVertical;
    QWidget *layoutWidget;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *searchGameLine;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *buttonStart;
    QPushButton *buttonEdit;
    QPushButton *buttonRemove;
    QSpacerItem *horizontalSpacer_7;
    QSplitter *splitterHorizontalInfo;
    QSplitter *splitterVerticalInfo;
    QGraphicsView *mediaView;
    QGraphicsView *coversView;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QWidget *layoutWidget1;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    MyProgressBar *durationProgressBar;
    QHBoxLayout *horizontalLayout_2;
    QToolButton *playButton;
    QHBoxLayout *horizontalLayout;
    QToolButton *previousButton;
    QToolButton *stopButton;
    QToolButton *nextButton;
    QToolButton *playlistButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSlider *volumeSlider;
    QLabel *coverLabel;
    QMenuBar *menuBar;
    QMenu *menuMenu;
    QMenu *menuOption;
    QMenu *menuLanguage;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 640);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        QIcon icon;
        icon.addFile(QStringLiteral(":/menu/icons/About.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon);
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/menu/icons/Help.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon1);
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/menu/icons/English128x86.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionEnglish->setIcon(icon2);
        actionRussian = new QAction(MainWindow);
        actionRussian->setObjectName(QStringLiteral("actionRussian"));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/menu/icons/Russia128x86.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRussian->setIcon(icon3);
        actionStart_Game = new QAction(MainWindow);
        actionStart_Game->setObjectName(QStringLiteral("actionStart_Game"));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/menu/icons/Start.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionStart_Game->setIcon(icon4);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/menu/icons/Exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon5);
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QStringLiteral("actionSettings"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout_4 = new QVBoxLayout(centralWidget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        splitterHorizontal = new QSplitter(centralWidget);
        splitterHorizontal->setObjectName(QStringLiteral("splitterHorizontal"));
        splitterHorizontal->setOrientation(Qt::Vertical);
        splitterVertical = new QSplitter(splitterHorizontal);
        splitterVertical->setObjectName(QStringLiteral("splitterVertical"));
        splitterVertical->setOrientation(Qt::Horizontal);
        layoutWidget = new QWidget(splitterVertical);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        verticalLayout_2 = new QVBoxLayout(layoutWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 1);
        searchGameLine = new QLineEdit(layoutWidget);
        searchGameLine->setObjectName(QStringLiteral("searchGameLine"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchGameLine->sizePolicy().hasHeightForWidth());
        searchGameLine->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(searchGameLine);

        treeView = new QTreeView(layoutWidget);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(treeView);

        splitterVertical->addWidget(layoutWidget);
        tabWidget = new QTabWidget(splitterVertical);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_3 = new QVBoxLayout(tab);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        buttonStart = new QPushButton(tab);
        buttonStart->setObjectName(QStringLiteral("buttonStart"));

        horizontalLayout_4->addWidget(buttonStart);

        buttonEdit = new QPushButton(tab);
        buttonEdit->setObjectName(QStringLiteral("buttonEdit"));

        horizontalLayout_4->addWidget(buttonEdit);

        buttonRemove = new QPushButton(tab);
        buttonRemove->setObjectName(QStringLiteral("buttonRemove"));

        horizontalLayout_4->addWidget(buttonRemove);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_4);

        splitterHorizontalInfo = new QSplitter(tab);
        splitterHorizontalInfo->setObjectName(QStringLiteral("splitterHorizontalInfo"));
        splitterHorizontalInfo->setOrientation(Qt::Vertical);
        splitterVerticalInfo = new QSplitter(splitterHorizontalInfo);
        splitterVerticalInfo->setObjectName(QStringLiteral("splitterVerticalInfo"));
        splitterVerticalInfo->setOrientation(Qt::Horizontal);
        mediaView = new QGraphicsView(splitterVerticalInfo);
        mediaView->setObjectName(QStringLiteral("mediaView"));
        splitterVerticalInfo->addWidget(mediaView);
        coversView = new QGraphicsView(splitterVerticalInfo);
        coversView->setObjectName(QStringLiteral("coversView"));
        splitterVerticalInfo->addWidget(coversView);
        splitterHorizontalInfo->addWidget(splitterVerticalInfo);
        textBrowser = new QTextBrowser(splitterHorizontalInfo);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        splitterHorizontalInfo->addWidget(textBrowser);

        verticalLayout_3->addWidget(splitterHorizontalInfo);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());
        splitterVertical->addWidget(tabWidget);
        splitterHorizontal->addWidget(splitterVertical);
        layoutWidget1 = new QWidget(splitterHorizontal);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        horizontalLayout_5 = new QHBoxLayout(layoutWidget1);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        horizontalLayout_5->setContentsMargins(0, 0, 0, 0);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        durationProgressBar = new MyProgressBar(layoutWidget1);
        durationProgressBar->setObjectName(QStringLiteral("durationProgressBar"));
        durationProgressBar->setValue(24);
        durationProgressBar->setFormat(QStringLiteral("%v%"));

        verticalLayout->addWidget(durationProgressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        playButton = new QToolButton(layoutWidget1);
        playButton->setObjectName(QStringLiteral("playButton"));

        horizontalLayout_2->addWidget(playButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        previousButton = new QToolButton(layoutWidget1);
        previousButton->setObjectName(QStringLiteral("previousButton"));

        horizontalLayout->addWidget(previousButton);

        stopButton = new QToolButton(layoutWidget1);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);

        nextButton = new QToolButton(layoutWidget1);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        horizontalLayout->addWidget(nextButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        playlistButton = new QToolButton(layoutWidget1);
        playlistButton->setObjectName(QStringLiteral("playlistButton"));

        horizontalLayout_2->addWidget(playlistButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_5);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_6);

        volumeSlider = new QSlider(layoutWidget1);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setMaximum(100);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(volumeSlider);


        verticalLayout->addLayout(horizontalLayout_2);


        horizontalLayout_5->addLayout(verticalLayout);

        coverLabel = new QLabel(layoutWidget1);
        coverLabel->setObjectName(QStringLiteral("coverLabel"));

        horizontalLayout_5->addWidget(coverLabel);

        splitterHorizontal->addWidget(layoutWidget1);

        verticalLayout_4->addWidget(splitterHorizontal);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 21));
        menuMenu = new QMenu(menuBar);
        menuMenu->setObjectName(QStringLiteral("menuMenu"));
        menuOption = new QMenu(menuBar);
        menuOption->setObjectName(QStringLiteral("menuOption"));
        menuLanguage = new QMenu(menuOption);
        menuLanguage->setObjectName(QStringLiteral("menuLanguage"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menuMenu->menuAction());
        menuBar->addAction(menuOption->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuMenu->addAction(actionStart_Game);
        menuMenu->addSeparator();
        menuMenu->addAction(actionQuit);
        menuOption->addAction(menuLanguage->menuAction());
        menuOption->addAction(actionSettings);
        menuLanguage->addAction(actionEnglish);
        menuLanguage->addAction(actionRussian);
        menuHelp->addAction(actionAbout);
        menuHelp->addAction(actionHelp);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", Q_NULLPTR));
        actionAbout->setText(QApplication::translate("MainWindow", "About...", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help...", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        actionRussian->setText(QApplication::translate("MainWindow", "Russian", Q_NULLPTR));
        actionStart_Game->setText(QApplication::translate("MainWindow", "Add Game", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        actionSettings->setText(QApplication::translate("MainWindow", "Settings...", Q_NULLPTR));
        searchGameLine->setPlaceholderText(QApplication::translate("MainWindow", "Search...", Q_NULLPTR));
        buttonStart->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        buttonEdit->setText(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        buttonRemove->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Info", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        playButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        previousButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        nextButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        playlistButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        coverLabel->setText(QString());
        menuMenu->setTitle(QApplication::translate("MainWindow", "Menu", Q_NULLPTR));
        menuOption->setTitle(QApplication::translate("MainWindow", "Option", Q_NULLPTR));
        menuLanguage->setTitle(QApplication::translate("MainWindow", "Language", Q_NULLPTR));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
