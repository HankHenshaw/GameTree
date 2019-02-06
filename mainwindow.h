#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QTime>
#include <QProgressBar>
#include <QTranslator>
#include <QEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

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

private:
    Ui::MainWindow *ui;

    /*Audio Player*/
    QMediaPlayer *m_audioPlayer;
    QMediaPlaylist *m_audioPlayerList;

    void audioPlayerInit();
    QString msecsToString(qint64 n);
    /*Audio Player*/

    /*Translator*/
    QTranslator* translator;

    void changeLanguage(QString postfix);
    void changeEvent(QEvent* event);
    /*Translator*/
};

#endif // MAINWINDOW_H
