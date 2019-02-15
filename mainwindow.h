#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <QProgressBar>
#include <QTranslator>
#include <QEvent>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMap>
#include <QSet>
#include <QDir>
#include <QProcess>
#include <QSystemTrayIcon>
#include <QCloseEvent>
#include "treemodel.h"
#include "addgamedialog.h"
#include "addmoddialog.h"
#include "argsdialog.h"
#include "editmoddialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

protected:
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    /*Audio Player Slots*/
    void on_playButton_clicked();
    void on_previousButton_clicked();
    void on_stopButton_clicked();
    void on_nextButton_clicked();
    void on_playlistButton_clicked();
    void on_volumeSlider_sliderMoved(int position);
    void slotSetDuration(qint64 n);
    void slotSetProgressPosotion(qint64 n);
    /*Audio Player Slots*/

    /*Translator Slots*/
    void on_actionRussian_triggered();
    void on_actionEnglish_triggered();
    /*Translator Slots*/

    /*Context Menu Slots*/
    void on_treeView_customContextMenuRequested(const QPoint &pos);

    void slotDelete();
    void slotEdit();
    void slotEditMod();
    void slotStart();
    void slotStartWithParameters();
    void slotStartMod();
    void slotStartModWithParameters();
    void slotAdd();
    void slotAddMod();
    /*Context Menu Slots*/

    /*Button slots*/
    void on_buttonStart_clicked();
    void on_buttonEdit_clicked();
    void on_buttonRemove_clicked();

    void slotButtonActivator(QModelIndex selectedIndex);
    /*Button slots*/

    /*System Tray*/
    void slotShowHide();
    void slotIconActivated(QSystemTrayIcon::ActivationReason reason);
    /*System Tray*/

    /*Dbl Clk Start Game Slot*/
    void slotDblClicked();
private:
    Ui::MainWindow *ui;

    /*Model & Proxy*/
    TreeModel *m_model;

    QModelIndex m_selectedIndex;
    /*Model & Proxy*/

    /*Audio Player*/
    QMediaPlayer *m_audioPlayer;
    QMediaPlaylist *m_audioPlayerList;

    void audioPlayerInit();
    QString msecsToString(qint64 n);
    /*Audio Player*/

    /*Translator*/
    QTranslator* translator;

    void changeLanguage(QString postfix);
    void changeEvent(QEvent* event) override;
    /*Translator*/

    /*Sql*/
    QSqlDatabase m_db;

    QMap<QChar, int> m_mapOfLetters;
    QMap<QString, QSet<QString>> m_mapOfGames;

    void getDataFromDB();
    /*Sql*/

    /*System Tray*/
    QMenu *m_trayMenu;
    QSystemTrayIcon *m_trayIcon;
    /*System Tray*/
};

#endif // MAINWINDOW_H
