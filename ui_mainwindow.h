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
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

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
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLineEdit *searchGameLine;
    QTreeView *treeView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startPushButton;
    QPushButton *editPushButton;
    QPushButton *removePushButton;
    QSpacerItem *horizontalSpacer_7;
    QTextBrowser *textBrowser;
    QWidget *tab_2;
    QWidget *page_2;
    QProgressBar *durationProgressBar;
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
        actionHelp = new QAction(MainWindow);
        actionHelp->setObjectName(QStringLiteral("actionHelp"));
        actionEnglish = new QAction(MainWindow);
        actionEnglish->setObjectName(QStringLiteral("actionEnglish"));
        actionRussian = new QAction(MainWindow);
        actionRussian->setObjectName(QStringLiteral("actionRussian"));
        actionStart_Game = new QAction(MainWindow);
        actionStart_Game->setObjectName(QStringLiteral("actionStart_Game"));
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QStringLiteral("actionQuit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalSpacer = new QSpacerItem(779, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer);

        horizontalSpacer_2 = new QSpacerItem(779, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        verticalLayout->addItem(horizontalSpacer_2);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        horizontalLayout_3 = new QHBoxLayout(page);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(5);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        searchGameLine = new QLineEdit(page);
        searchGameLine->setObjectName(QStringLiteral("searchGameLine"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(searchGameLine->sizePolicy().hasHeightForWidth());
        searchGameLine->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(searchGameLine);

        treeView = new QTreeView(page);
        treeView->setObjectName(QStringLiteral("treeView"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(treeView->sizePolicy().hasHeightForWidth());
        treeView->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(treeView);


        horizontalLayout_3->addLayout(verticalLayout_2);

        tabWidget = new QTabWidget(page);
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
        startPushButton = new QPushButton(tab);
        startPushButton->setObjectName(QStringLiteral("startPushButton"));

        horizontalLayout_4->addWidget(startPushButton);

        editPushButton = new QPushButton(tab);
        editPushButton->setObjectName(QStringLiteral("editPushButton"));

        horizontalLayout_4->addWidget(editPushButton);

        removePushButton = new QPushButton(tab);
        removePushButton->setObjectName(QStringLiteral("removePushButton"));

        horizontalLayout_4->addWidget(removePushButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);


        verticalLayout_3->addLayout(horizontalLayout_4);

        textBrowser = new QTextBrowser(tab);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout_3->addWidget(textBrowser);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        tabWidget->addTab(tab_2, QString());

        horizontalLayout_3->addWidget(tabWidget);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        stackedWidget->addWidget(page_2);

        verticalLayout->addWidget(stackedWidget);

        durationProgressBar = new QProgressBar(centralWidget);
        durationProgressBar->setObjectName(QStringLiteral("durationProgressBar"));
        durationProgressBar->setValue(24);
        durationProgressBar->setFormat(QStringLiteral("%v%"));

        verticalLayout->addWidget(durationProgressBar);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(5);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        playButton = new QToolButton(centralWidget);
        playButton->setObjectName(QStringLiteral("playButton"));

        horizontalLayout_2->addWidget(playButton);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        previousButton = new QToolButton(centralWidget);
        previousButton->setObjectName(QStringLiteral("previousButton"));

        horizontalLayout->addWidget(previousButton);

        stopButton = new QToolButton(centralWidget);
        stopButton->setObjectName(QStringLiteral("stopButton"));

        horizontalLayout->addWidget(stopButton);

        nextButton = new QToolButton(centralWidget);
        nextButton->setObjectName(QStringLiteral("nextButton"));

        horizontalLayout->addWidget(nextButton);


        horizontalLayout_2->addLayout(horizontalLayout);

        playlistButton = new QToolButton(centralWidget);
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

        volumeSlider = new QSlider(centralWidget);
        volumeSlider->setObjectName(QStringLiteral("volumeSlider"));
        volumeSlider->setMaximum(100);
        volumeSlider->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(volumeSlider);


        verticalLayout->addLayout(horizontalLayout_2);

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
        actionAbout->setText(QApplication::translate("MainWindow", "About", Q_NULLPTR));
        actionHelp->setText(QApplication::translate("MainWindow", "Help", Q_NULLPTR));
        actionEnglish->setText(QApplication::translate("MainWindow", "English", Q_NULLPTR));
        actionRussian->setText(QApplication::translate("MainWindow", "Russian", Q_NULLPTR));
        actionStart_Game->setText(QApplication::translate("MainWindow", "Start Game", Q_NULLPTR));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", Q_NULLPTR));
        searchGameLine->setPlaceholderText(QApplication::translate("MainWindow", "Search...", Q_NULLPTR));
        startPushButton->setText(QApplication::translate("MainWindow", "Start", Q_NULLPTR));
        editPushButton->setText(QApplication::translate("MainWindow", "Edit", Q_NULLPTR));
        removePushButton->setText(QApplication::translate("MainWindow", "Remove", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Info", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Tab 2", Q_NULLPTR));
        playButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        previousButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        stopButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        nextButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
        playlistButton->setText(QApplication::translate("MainWindow", "...", Q_NULLPTR));
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
