#include "mainwindow.h"
#include "ui_mainwindow.h"

//TODO: Add Author of Icons from www.flaticon.com
//TODO: RMB Progressbar
//TODO: Playerlist widget
//TODO: Mouse Wheel at volumeSlider
//TODO: Settings
//TODO: Fix all warnings
//TODO: Replace menu icons to ~16x16 size
//TODO: Minimize to tray

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    qInfo() << "Audioplayer initialization";
    audioPlayerInit();
}

MainWindow::~MainWindow()
{
    delete ui;
}

/*Audio Player*/
void MainWindow::on_playButton_clicked()
{
    // Play/Pause Button
    static bool isClicked = true; // можно вынести в реал. класса или лучше переписать
    if(isClicked)
    {
        isClicked = false;
        ui->playButton->setIcon(QIcon(":/audioplayer/icons/pause-button.png"));
        m_audioPlayer->play();
    }
    else
    {
        isClicked = true;
        ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
        m_audioPlayer->pause();
    }
}

void MainWindow::on_previousButton_clicked()
{
    // Prev song
    m_audioPlayerList->previous();
}

void MainWindow::on_stopButton_clicked()
{
    m_audioPlayer->stop();
}

void MainWindow::on_nextButton_clicked()
{
    // Next song
    m_audioPlayerList->next();
}

void MainWindow::on_playlistButton_clicked()
{

}

void MainWindow::on_volumeSlider_sliderMoved(int position)
{
    m_audioPlayer->setVolume(position);
}

void MainWindow::audioPlayerInit()
{
    // Set icons
    ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
    ui->previousButton->setIcon(QIcon(":/audioplayer/icons/previous-step-circular-button.png"));
    ui->nextButton->setIcon(QIcon(":/audioplayer/icons/next-step-circular-button.png"));
    ui->stopButton->setIcon(QIcon(":/audioplayer/icons/stop-button.png"));
    ui->playlistButton->setIcon(QIcon(":/audioplayer/icons/song-playlist.png"));

    // Initialization
    m_audioPlayer = new QMediaPlayer(this);
    m_audioPlayerList = new QMediaPlaylist(this);

    // Add songs to playerlist
    m_audioPlayerList->addMedia(QUrl::fromLocalFile("C:/Users/Максим/Downloads/Trivium/Albums/2011 - In Waves (Special Edition)/06 - Black.mp3"));
    m_audioPlayerList->addMedia(QUrl::fromLocalFile("C:/Users/Максим/Downloads/Trivium/Albums/2011 - In Waves (Special Edition)/09 - Built To Fall.mp3"));

    // Set Playback Mode
    m_audioPlayerList->setPlaybackMode(QMediaPlaylist::Loop);

    // Set volume and list to audioplayer
    m_audioPlayer->setPlaylist(m_audioPlayerList);
    m_audioPlayer->setVolume(1);

    // Set connection
    connect(m_audioPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_audioPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetProgressPosotion(qint64)));

    // Set text in the middle of the progress bar
    ui->durationProgressBar->setAlignment(Qt::AlignCenter);
    ui->durationProgressBar->setTextVisible(true);

    //TEST: testing label
    ui->coverLabel->setText("<img src = \"Front.jpg\" height = \"60\" width = \"60\" />");
}

void MainWindow::slotSetDuration(qint64 n)
{
    ui->durationProgressBar->setRange(0, n);
    ui->durationProgressBar->setFormat(msecsToString(n));
}

void MainWindow::slotSetProgressPosotion(qint64 n)
{
    ui->durationProgressBar->setValue(n);

    int nDuration = ui->durationProgressBar->maximum();
    ui->durationProgressBar->setFormat(msecsToString(nDuration - n));
}

QString MainWindow::msecsToString(qint64 n)
{
    int nHours   = (n / (60 * 60 * 1000));
    int nMinutes = ((n  % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}
/*Audio Player*/
/*Translator*/
void MainWindow::changeLanguage(QString postfix)
{
    QApplication::removeTranslator(translator); // Удаляем старый
    translator = new QTranslator(this);
    translator->load(QApplication::applicationName() + "_" + postfix);
    QApplication::installTranslator(translator); // Устанавливаем новый
}

void MainWindow::changeEvent(QEvent *event)
{
    qDebug() << "Language Change";
    if(event->type() == QEvent::LanguageChange)
    {
        setWindowTitle(tr("GameTree"));
        ui->menuLanguage->setTitle(tr("Language"));
        ui->menuHelp->setTitle(tr("Help"));
        ui->menuMenu->setTitle(tr("Menu"));
        ui->menuOption->setTitle(tr("Options"));
        ui->actionAbout->setText(tr("About"));
        ui->actionHelp->setText(tr("Help"));
        ui->actionQuit->setText(tr("Quit"));
        ui->actionEnglish->setText(tr("English"));
        ui->actionRussian->setText(tr("Russian"));
        ui->actionStart_Game->setText(tr("Start Game"));
        ui->buttonEdit->setText(tr("Edit"));
        ui->buttonStart->setText(tr("Start"));
        ui->buttonRemove->setText(tr("Remove"));
        ui->searchGameLine->setPlaceholderText(tr("Search..."));
    }
    else
    {
        QMainWindow::changeEvent(event);
    }
}

void MainWindow::on_actionRussian_triggered()
{
    changeLanguage("ru");
}

void MainWindow::on_actionEnglish_triggered()
{
    changeLanguage("en");
}
/*Translator*/
