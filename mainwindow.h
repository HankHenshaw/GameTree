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
#include <QSettings>
#include <QFileInfo>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QTimer>
#include "treemodel.h"
#include "addgamedialog.h"
#include "addmoddialog.h"
#include "argsdialog.h"
#include "editmoddialog.h"
#include "myprogressbar.h"
#include "playlistform.h"
#include "myproxymodel.h"
#include "optionsdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;

    /*Settings*/
    void loadSettings();
    void saveSettings();
    /*Settings*/

    /*Static*/
    static const QString appPath();
    /*Static*/
protected:
    virtual void showEvent(QShowEvent *event) override;
    virtual void closeEvent(QCloseEvent *event) override;

private slots:
    /*Audio Player Slots*/
    void on_playButton_clicked();
    void on_previousButton_clicked();
    void on_stopButton_clicked();
    void on_nextButton_clicked();
    void on_playlistButton_clicked();
    //void on_volumeSlider_sliderMoved(int position);
    void slotSetDuration(qint64 n);
    void slotSetProgressPosotion(qint64 n);
    void slotSetMediaPosition(QPoint pos);
    void slotPlaylistFormClicked();
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
    /*Dbl Clk Start Game Slot*/

    /*Proxy*/
    void slotFilter();
    /*Proxy*/
    void on_splitterVertical_splitterMoved(int pos, int index);
    void on_splitterHorizontal_splitterMoved(int pos, int index);
    void on_splitterHorizontalInfo_splitterMoved(int pos, int index);
    void on_splitterVerticalInfo_splitterMoved(int pos, int index);

    /*Timer*/
    void slotCoversSlideshowStart();
    void slotMediaSlideshowStart();
    /*Timer*/
    void on_volumeSlider_valueChanged(int value);

    void on_actionQuit_triggered();

    void on_actionAbout_triggered();

    void on_actionSettings_triggered();

private:
    Ui::MainWindow *ui;

    /*Static*/
    static QString m_appPath;
    /*Static*/

    /*Settings*/
    QSettings *m_settings;
    /*Settings*/

    /*Model & Proxy*/
    TreeModel *m_model;
    QModelIndex m_selectedIndex;
    MyProxyModel *m_proxy;
    /*Model & Proxy*/

    /*Audio Player*/
    QMediaPlayer *m_audioPlayer;
    QMediaPlaylist *m_audioPlayerList;

    void audioPlayerInit();
    QString msecsToString(qint64 n);

    PlaylistForm *m_playlistForm;

    bool m_isPlayButtonClicked;
    /*Audio Player*/

    /*Test Covers View*/
    QMediaPlayer *m_coversPlayer;
    QGraphicsScene *m_coverScene;
    /*Test Covers View*/

    /*Test Media View*/
    QMediaPlayer *m_mediaPlayer;
    QGraphicsScene *m_mediaScene;
    /*Test Media View*/

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

    /*Dirs*/
    QDir m_dir;
    /*Dirs*/

    /*Timer*/
    QTimer *m_coversSlideshowTimer;
    QTimer *m_mediaSlideshowTimer;
    QStringList m_coversList;
    QStringList m_mediaList;
    int m_slideMediaNumber;
    int m_slideCoverNumber;
    bool isCoversSlideshowEnabled;
    bool isMediaSlideshowEnabled;
    QString m_strToMedia;
    QString m_strToCover;
    /*Timer*/
};

#endif // MAINWINDOW_H
