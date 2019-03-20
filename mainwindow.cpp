#include "mainwindow.h"
#include "ui_mainwindow.h"

///WARNING: Опасные моменты кода, которые могут вызвать проблемы
///TEST: Тестовые эл-ты
///TODO: То что надо сделать
///OFF: Закоммент. нерабочии участки кода

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{ 
    ui->setupUi(this);
    this->setWindowTitle("Game Tree");
    qInfo() << "Audioplayer initialization";
    audioPlayerInit();

    qInfo() << "Get Data From DB";
    getDataFromDB();

    //Создаем основную папку для контента
    m_dir = MainWindow::appPath();
    m_dir.mkdir("Screenshots");
    m_dir.mkdir("Games");
    m_dir = MainWindow::appPath() + "/Games/";

    //Путь к приложению
    //m_appPath = QDir::currentPath();
    qDebug() << m_appPath;

    //Основная модель с данными
    m_model = new TreeModel(m_mapOfLetters, m_mapOfGames);

    //ui->treeView->setModel(m_model);

    //Устанавливаем политику кастомного меню
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // Разукрашивает каждую нечетную строку в серый, чеиные остаются белыми
    ui->treeView->setAlternatingRowColors(true);

    //Устанавливаем соединение, для отслеживания выбранных индексов на представлении
    connect(ui->treeView, &QTreeView::pressed, this, &MainWindow::slotButtonActivator);

    //Создаем объект класса настроек и загружаем настройки из ини файла
    QString cfgFilePath(m_appPath + "/cfg.ini");
    m_settings = new QSettings(cfgFilePath, QSettings::IniFormat, this);
    loadSettings();

    //Устанавливаем кнопки в нерабочее состояние, т.к. пока еще ничего не выбрано
    ui->buttonStart->setDisabled(true);
    ui->buttonEdit->setDisabled(true);
    ui->buttonRemove->setDisabled(true);

    //Устанавливаем соединение, для отслеживания двойного клика
    connect(ui->treeView, &QTreeView::doubleClicked, this, &MainWindow::slotDblClicked);

    //Создаем действися для меню трея*/
    QAction* aTrayQuit = new QAction(tr("Quit"), this);
    connect(aTrayQuit, &QAction::triggered, qApp, &QApplication::quit);
    QAction* aTrayShowHide = new QAction(tr("Show/Hide Application Window"), this);
    connect(aTrayShowHide, &QAction::triggered, this, &MainWindow::slotShowHide);

    //Создаем меню и заполняем его действиямм
    m_trayMenu = new QMenu(this);
    m_trayMenu->addAction(aTrayShowHide);
    m_trayMenu->addSeparator();
    m_trayMenu->addAction(aTrayQuit);

    //Создаем иконку для меню и отображаем в трее
    m_trayIcon = new QSystemTrayIcon(this);
    m_trayIcon->setContextMenu(m_trayMenu);
    m_trayIcon->setToolTip(tr("Game Tree"));
    m_trayIcon->setIcon(QPixmap(":/menu/icons/tree_24.png"));
    connect(m_trayIcon, &QSystemTrayIcon::activated, this, &MainWindow::slotIconActivated);

    m_trayIcon->show();

    /*Proxy*/
    //Соединяем строку поиска с прокси моделью
    connect(ui->searchGameLine, &QLineEdit::textChanged, this, &MainWindow::slotFilter);

    //Прокси модель для фильтрации
    m_proxy = new MyProxyModel;

    //Устанавливаем в прокси модель основную модель с данными
    m_proxy->setSourceModel(m_model);

     //а в отображение устанавливаем прокси модель
    ui->treeView->setModel(m_proxy);
    /*Proxy*/

    /*Covers & Media players*/
    m_coverScene = new QGraphicsScene(this);
    ui->coversView->setScene(m_coverScene);

    m_mediaScene = new QGraphicsScene(this);
    ui->mediaView->setScene(m_mediaScene);
    /*Covers & Media players*/

    /*Timer*/
    m_coversSlideshowTimer = new QTimer(this);
    m_mediaSlideshowTimer = new QTimer(this);
    m_slideMediaNumber = 0;
    m_slideCoverNumber = 0;
    isCoversSlideshowEnabled = true;
    isMediaSlideshowEnabled = true;
    if(isCoversSlideshowEnabled)
        m_coversSlideshowTimer->start(5000);
    if(isMediaSlideshowEnabled)
        m_mediaSlideshowTimer->start(10000);
    connect(m_coversSlideshowTimer, &QTimer::timeout, this, &MainWindow::slotCoversSlideshowStart);
    connect(m_mediaSlideshowTimer, &QTimer::timeout, this, &MainWindow::slotMediaSlideshowStart);
    /*Timer*/

    //Разварачиваем на полный экран если перед выходом приложение было на полный экран
    if(m_options.isFullscreen)
        this->setWindowState(Qt::WindowMaximized);

    //Выключаем 2 таб, т.к. пока он не используется
    ui->tabWidget->setTabEnabled(1, false);

    //Установка языка перевода
    this->changeLanguage(m_options.language);

    //Устанавливаем возможность передаскивания файлов
    setAcceptDrops(true);

    //Соединяем сигналы My Tree View, со слотами для обработки нажатия Enter и Delete
    connect(ui->treeView, &MyTreeView::signalKeyEnter, this, &MainWindow::slotKeyEnter);
    connect(ui->treeView, &MyTreeView::signalKeyDelete, this, &MainWindow::slotKeyDelete);

    /*Screenshots*/
    m_screens = QGuiApplication::screens();
    if(!RegisterHotKey(HWND(winId()), 0, MOD_SHIFT, 112))
        qWarning() << "Can't register hotkey SHIFT+F1";

    for(int hotKeyNumber = 1; hotKeyNumber < m_screens.size() + 1; ++hotKeyNumber)
    {
        size_t keyNumber = 111 + static_cast<size_t>(hotKeyNumber);
        if(!RegisterHotKey(HWND(winId()), hotKeyNumber, MOD_CONTROL, keyNumber))
        {
            QString warningStr = "Can't register hotkey CTRL+F";
            warningStr.append(QString::number(hotKeyNumber));
            qWarning() << warningStr;
        }
    }
    /*Screenshots*/
}

MainWindow::~MainWindow()
{
    saveSettings();
    UnregisterHotKey(HWND(winId()), 0);
    for(int i = 1; i < m_screens.size() + 1; ++i)
    {
            UnregisterHotKey(HWND(winId()), i);
    }
    delete ui;
}

/*Static*/
QString MainWindow::m_appPath = QDir::currentPath();


const QString MainWindow::appPath()
{
    return m_appPath;
}
/*Static*/

/*Settings*/
void MainWindow::loadSettings()
{
    qDebug() << "Load settings";

//    m_settings->beginGroup(objectName());
//    this->setGeometry(m_settings->value("Geometry", QRect(static_cast<int>(qApp->desktop()->screenGeometry().width()*0.5) - 400, static_cast<int>(qApp->desktop()->screenGeometry().height()*0.5) - 320, 800, 640)).toRect());
//    ui->splitterVertical->restoreState(m_settings->value("Vertical Splitter").toByteArray());
//    ui->splitterHorizontal->restoreState(m_settings->value("Horizontal Splitter").toByteArray());
//    ui->splitterVerticalInfo->restoreState(m_settings->value("Vertical Info Splitter").toByteArray());
//    ui->splitterHorizontalInfo->restoreState(m_settings->value("Horizontal Info Splitter").toByteArray());
//    m_settings->endGroup();

    m_settings->beginGroup("Options");
    m_options.isFullscreen = m_settings->value("Fullscreen").toBool();
    m_options.isCoverSlideshowEnabled = m_settings->value("Covers Slideshow").toBool();
    m_options.coverSlideshowRate = m_settings->value("Covers Slideshow Rate").toInt();
    m_options.isMediaSlideshowEnabled = m_settings->value("Media Slideshow").toBool();
    m_options.mediaSlideshowRate = m_settings->value("Media Slideshow Rate").toInt();
    m_options.styleNumber = m_settings->value("Style Number").toInt();
    m_options.language = m_settings->value("Language").toString();
    m_settings->endGroup();

    m_settings->beginGroup(objectName());
    this->setGeometry(m_settings->value("Geometry", QRect(static_cast<int>(qApp->desktop()->screenGeometry().width()*0.5) - 400, static_cast<int>(qApp->desktop()->screenGeometry().height()*0.5) - 320, 800, 640)).toRect());
    ui->splitterVertical->restoreState(m_settings->value("Vertical Splitter").toByteArray());
    ui->splitterHorizontal->restoreState(m_settings->value("Horizontal Splitter").toByteArray());
    ui->splitterVerticalInfo->restoreState(m_settings->value("Vertical Info Splitter").toByteArray());
    ui->splitterHorizontalInfo->restoreState(m_settings->value("Horizontal Info Splitter").toByteArray());
    m_settings->endGroup();

    OptionsDialog dialog;
    dialog.setSettings(m_options);
}

void MainWindow::saveSettings()
{
    qDebug() << "Save settings";

    m_settings->beginGroup("Options");
    m_settings->setValue("Fullscreen", m_options.isFullscreen);
    m_settings->setValue("Covers Slideshow", m_options.isCoverSlideshowEnabled);
    m_settings->setValue("Covers Slideshow Rate", m_options.coverSlideshowRate);
    m_settings->setValue("Media Slideshow", m_options.isMediaSlideshowEnabled);
    m_settings->setValue("Media Slideshow Rate", m_options.mediaSlideshowRate);
    m_settings->setValue("Style Number", m_options.styleNumber);
    m_settings->setValue("Language", m_options.language);
    m_settings->endGroup();

    m_settings->beginGroup(objectName());
    if(m_options.isFullscreen)
    {
        this->setGeometry(m_settings->value("Geometry", QRect(static_cast<int>(qApp->desktop()->screenGeometry().width()*0.5) - 400, static_cast<int>(qApp->desktop()->screenGeometry().height()*0.5) - 320, 800, 640)).toRect());
    }
    else
        m_settings->setValue("Geometry", geometry());
    m_settings->setValue("Vertical Splitter", ui->splitterVertical->saveState());
    m_settings->setValue("Horizontal Splitter", ui->splitterHorizontal->saveState());
    m_settings->setValue("Vertical Info Splitter", ui->splitterVerticalInfo->saveState());
    m_settings->setValue("Horizontal Info Splitter", ui->splitterHorizontalInfo->saveState());
    m_settings->endGroup();


}
/*Settings*/

/*Audio Player*/
void MainWindow::on_playButton_clicked()
{
    // Play/Pause Button
    if(!m_isPlayButtonClicked)
    {
        m_isPlayButtonClicked = true;
        ui->playButton->setIcon(QIcon(":/audioplayer/icons/pause-button.png"));
        m_audioPlayer->play();
    }
    else
    {
        m_isPlayButtonClicked = false;
        ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
        m_audioPlayer->pause();
    }
}

void MainWindow::on_previousButton_clicked()
{
    // Прелылущая песня
    m_audioPlayerList->previous();
}

void MainWindow::on_stopButton_clicked()
{
    m_audioPlayer->stop();
}

void MainWindow::on_nextButton_clicked()
{
    // Следующая песня
    m_audioPlayerList->next();
}

void MainWindow::on_playlistButton_clicked()
{
    // Кнопка списка воспроизведения
    m_playlistForm.setWindowTitle(tr("Playlist"));
    m_playlistForm.setWindowModality(Qt::ApplicationModal);
    m_playlistForm.show();
    m_playlistForm.playlistClicked(m_audioPlayer);
}

void MainWindow::on_volumeSlider_valueChanged(int value)
{
    m_audioPlayer->setVolume(value);
}

void MainWindow::audioPlayerInit()
{
    m_isPlayButtonClicked = false;

    // Set icons
    ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
    ui->previousButton->setIcon(QIcon(":/audioplayer/icons/previous-step-circular-button.png"));
    ui->nextButton->setIcon(QIcon(":/audioplayer/icons/next-step-circular-button.png"));
    ui->stopButton->setIcon(QIcon(":/audioplayer/icons/stop-button.png"));
    ui->playlistButton->setIcon(QIcon(":/audioplayer/icons/song-playlist.png"));

    // Initialization
    m_audioPlayer = new QMediaPlayer(this);
    m_audioPlayerList = new QMediaPlaylist(this);

    // Set Playback Mode
    m_audioPlayerList->setPlaybackMode(QMediaPlaylist::Loop);

    // Set volume and list to audioplayer
    m_audioPlayer->setPlaylist(m_audioPlayerList);
    m_audioPlayer->setVolume(1);

    // Set connection
    connect(m_audioPlayer, SIGNAL(durationChanged(qint64)), SLOT(slotSetDuration(qint64)));
    connect(m_audioPlayer, SIGNAL(positionChanged(qint64)), SLOT(slotSetProgressPosotion(qint64)));
    connect(ui->durationProgressBar, &MyProgressBar::signalMousePressedPos, this, &MainWindow::slotSetMediaPosition);
    connect(&m_playlistForm, &PlaylistForm::signalPlay, this, &MainWindow::slotPlaylistFormClicked);

    // Set text in the middle of the progress bar
    ui->durationProgressBar->setAlignment(Qt::AlignCenter);
    ui->durationProgressBar->setTextVisible(true);

    // Set start value and format
    ui->durationProgressBar->setValue(0);
    ui->durationProgressBar->setFormat(msecsToString(0));
}

void MainWindow::slotSetDuration(qint64 n)
{
    // Слот установки длительности песни
    ui->durationProgressBar->setRange(0, static_cast<int>(n));
    ui->durationProgressBar->setFormat(msecsToString(n));
}

void MainWindow::slotSetProgressPosotion(qint64 n)
{
    // Слот обновления прогресс бара в зависимости от длительности
    ui->durationProgressBar->setValue(static_cast<int>(n));

    int nDuration = ui->durationProgressBar->maximum();
    ui->durationProgressBar->setFormat(msecsToString(nDuration - n));
}

QString MainWindow::msecsToString(qint64 n)
{
    int nHours   = (static_cast<int>(n) / (60 * 60 * 1000));
    int nMinutes = ((n  % (60 * 60 * 1000)) / (60 * 1000));
    int nSeconds = ((n % (60 * 1000)) / 1000);

    return QTime(nHours, nMinutes, nSeconds).toString("hh:mm:ss");
}

void MainWindow::slotSetMediaPosition(QPoint pos)
{
    //Слот установки позиции воспроизведения
    int widthOfProgressBar = size().width() - 86; // 24 = 9x2 (Margins) - 6(Space between progressbar and label) - 60 (Lable size) - 2(idk, mb Border)

    double nScale = static_cast<double>(pos.x())/widthOfProgressBar;
    qint64 position = static_cast<qint64>((ui->durationProgressBar->maximum())*nScale);
    m_audioPlayer->setPosition(position);
}

void MainWindow::slotPlaylistFormClicked()
{
    m_isPlayButtonClicked = true;
    ui->playButton->setIcon(QIcon(":/audioplayer/icons/pause-button.png"));
    m_audioPlayer->play();
}
/*Audio Player*/
/*Translator*/
void MainWindow::changeLanguage(QString postfix)
{
    QApplication::removeTranslator(translator); // Удаляем старый
    translator = new QTranslator(this);
    translator->load(QApplication::applicationName() + "_" + postfix);
    QApplication::installTranslator(translator); // Устанавливаем новый
    m_options.language = postfix;
}

void MainWindow::changeEvent(QEvent *event)
{
    if(event->type() == QEvent::LanguageChange)
    {
        qDebug() << "Language Change";
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
        ui->actionStart_Game->setText(tr("Add Game..."));
        ui->buttonEdit->setText(tr("Edit"));
        ui->buttonStart->setText(tr("Start"));
        ui->buttonRemove->setText(tr("Remove"));
        ui->searchGameLine->setPlaceholderText(tr("Search..."));
        ui->tabWidget->setTabText(0, tr("Info"));
    }
    else if(event->type() == QEvent::WindowStateChange)
    {
        if(this->isMinimized())
        {
            m_coversSlideshowTimer->stop();
            m_mediaSlideshowTimer->stop();
        }
        else
        {
            if(!m_coversSlideshowTimer->isActive())
            {
                if(m_options.isCoverSlideshowEnabled)
                    m_coversSlideshowTimer->start();
            }
            if(!m_mediaSlideshowTimer->isActive())
            {
                if(m_options.isMediaSlideshowEnabled)
                    m_mediaSlideshowTimer->start();
            }
        }

        if(this->isMaximized())
        {
            m_options.isFullscreen = true;
            ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
            ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
        else
        {
            m_options.isFullscreen = false;
            ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
            ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
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

void MainWindow::getDataFromDB()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("GameTree.sqlite");

    if(!m_db.open())
        qWarning() << "Can't connection to DB";
    else
    {
        qDebug() << "DB Connected";

        //Сет для дефолтного значения если у позиции нет подпозиции
        QSet<QString> defaultValue;
        defaultValue.insert("");

        QSqlQuery *query = new QSqlQuery(m_db);
        QString strQuery("SELECT Title FROM Games");
        query->exec(strQuery);
        while(query->next())
        {
            //Записываем результат запроса в строку для проверки потом 1-ого символа
            QString tempQueryString = query->value(0).toString();

            //Добавляем в список(мар) букв новое значение
            m_mapOfLetters[tempQueryString[0]] += 1;

            //Подзапрос
            QSqlQuery *subQuery = new QSqlQuery(m_db);
            QString strSubQuery = "SELECT Title FROM '" + tempQueryString + "'";

            subQuery->exec(strSubQuery);
            bool isSubQuerySuccess = false;
            while(subQuery->next())
            {
                isSubQuerySuccess = true;
                //Записываем в строку результат подзапроса
                QString tempSubQueryString = subQuery->value(0).toString();

                //Получаем результат поиска позиции
                QMap<QString, QSet<QString>>::iterator findIterator = m_mapOfGames.find(tempQueryString);

                //Создаем итератор на конец для проверки
                QMap<QString, QSet<QString>>::iterator endIterator = m_mapOfGames.end();

                //Если поиск удачный, просто добавляем еще 1 значение в сет
                if(findIterator != endIterator)
                {
                    findIterator.value().insert(tempSubQueryString);
                }
                //Иначе создаем сет, добаляем туда первое значение и создаем новую запись в мар
                else
                {
                    QSet<QString> tempSetOfSubGames;
                    tempSetOfSubGames.insert(tempSubQueryString);
                    m_mapOfGames[tempQueryString] = tempSetOfSubGames;
                }
            }
            if(!isSubQuerySuccess)
            {
                m_mapOfGames[tempQueryString] = defaultValue;
            }
        }
    }
}
/*Context Menu*/
void MainWindow::on_treeView_customContextMenuRequested(const QPoint &pos)
{
    //Получаем глобальные координаты виджета
    QPoint globalPos = ui->treeView->mapToGlobal(pos);

    //Меню для букв
    QMenu letterMenu;

    //Меню для игр
    QMenu gameMenu;

    //Меню для модов
    QMenu modMenu;

    //Меню для невалидных индексов
    QMenu invalidIndexMenu;

    //Создаем действие для добавления игры
    QAction *addGame = new QAction(tr("Add game..."));

    //Создаем действие для добавления мода
    QAction *addMod = new QAction(tr("Add mod..."));

    //Создаем действие для запуска игры
    QAction *startGame = new QAction(tr("Start game"));

    //Создаем действие для запуска игры с параметрами
    QAction *startGameWithParameters = new QAction(tr("Start game with parameters..."));

    //Создаем действие для запуска игры с параметрами
    QAction *startMod = new QAction(tr("Start mod"));

    //Создаем действие для запуска игры с параметрами
    QAction *startModWithParameters = new QAction(tr("Start mod with parameters..."));

    //Создаем действие для удаления игры
    QAction *deleteGame = new QAction(tr("Delete game(s)/mod(s)"));

    //Создаем действие для редактирования информации об игре
    QAction *editGame = new QAction(tr("Edit information about game..."));

    //Создаем действие для редактирования информации о моде
    QAction *editMod = new QAction(tr("Edit information about mod..."));

    //Создаем действие для открытия папки игры в окне обозревателя
    QAction *openGameDir = new QAction(tr("Open game dir..."));

    //Создаем действие для открытия папки мода в окне обозревателя
    QAction *openModDir = new QAction(tr("Open mod dir..."));

    //Создаем действие для открытия папки игры в окне обозревателя
    QAction *openProgramGameDir = new QAction(tr("Open game info dir..."));

    //Создаем действие для открытия папки мода в окне обозревателя
    QAction *openProgramModDir = new QAction(tr("Open mod info dir..."));

    //Заполняем оба меню действиями
    invalidIndexMenu.addAction(addGame);

    modMenu.addAction(startMod);
    modMenu.addAction(startModWithParameters);
    modMenu.addSeparator();
    modMenu.addAction(addGame);
    modMenu.addAction(addMod);
//    modMenu.addAction(editGame); //Вырублено
    modMenu.addAction(editMod);
    modMenu.addAction(deleteGame);
    modMenu.addAction(openModDir);
    modMenu.addAction(openProgramModDir);

    gameMenu.addAction(startGame);
    gameMenu.addAction(startGameWithParameters);
    gameMenu.addSeparator();
    gameMenu.addAction(addGame);
    gameMenu.addAction(addMod);
    gameMenu.addAction(editGame);
    gameMenu.addAction(deleteGame);
    gameMenu.addAction(openGameDir);
    gameMenu.addAction(openProgramGameDir);

    letterMenu.addAction(addGame);
    letterMenu.addAction(deleteGame);

    //Соединяем сигнал-слоты QAction
    connect(addGame, &QAction::triggered, this, &MainWindow::slotAdd);
    connect(addMod, &QAction::triggered, this, &MainWindow::slotAddMod);
    connect(editGame, &QAction::triggered, this, &MainWindow::slotEdit);
    connect(editMod, &QAction::triggered, this, &MainWindow::slotEditMod);
    connect(deleteGame, &QAction::triggered, this, &MainWindow::slotDelete);
    connect(startGame, &QAction::triggered, this, &MainWindow::slotStart);
    connect(startGameWithParameters, &QAction::triggered, this, &MainWindow::slotStartWithParameters);
    connect(startMod, &QAction::triggered, this, &MainWindow::slotStartMod);
    connect(startModWithParameters, &QAction::triggered, this, &MainWindow::slotStartModWithParameters);
    connect(openGameDir, &QAction::triggered, this, &MainWindow::slotOpenGameDir);
    connect(openModDir, &QAction::triggered, this, &MainWindow::slotOpenModDir);
    connect(openProgramGameDir, &QAction::triggered, this, &MainWindow::slotOpenProgramGameDir);
    connect(openProgramModDir, &QAction::triggered, this, &MainWindow::slotOpenProgramModDir);

    //Исп. перемн. класса, а не локальную, для того что бы запоминать послд. выделен. позицию и исп. эту перемен. в слотах QAction
    m_selectedIndex = ui->treeView->indexAt(pos);

    if(!m_selectedIndex.isValid())
    {
        invalidIndexMenu.exec(globalPos);
    }
    else
    {
        if(!m_selectedIndex.parent().isValid())
        {
            //Меню для букв
            letterMenu.exec(globalPos);
        }
        else if(!m_selectedIndex.parent().parent().isValid())
        {
            //Меню для игр
            gameMenu.exec(globalPos);
        }
        else if(!m_selectedIndex.parent().parent().parent().isValid())
        {
            //Меню для модов
            modMenu.exec(globalPos);
        }
        else
        {
            //Если вдруг ничего не подходит
            invalidIndexMenu.exec(globalPos);
        }
    }

}

void MainWindow::slotDelete()
{
    //Останавливаем плеер и очищаем плейлист
    m_audioPlayer->stop();
    m_audioPlayerList->clear();

    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex();
    QModelIndex selectedOriginalIndex = m_proxy->mapToSource(selectedIndex);

    qDebug() << "Delete item" << selectedOriginalIndex.data().toString();
    //TODO: Удалять букву если игр на эту букву не осталось

    if(!selectedOriginalIndex.parent().isValid())
    {
        qDebug() << "Letter";
        //Удаление игр и модов из под каждой игры

        int childAmount = m_model->getItem(selectedOriginalIndex)->childCount();

        for(int childCount = 0; childCount < childAmount; ++childCount)
        {
            QString childName = m_model->getItem(selectedOriginalIndex)->child(childCount)->data();
            QString strRemoveChild("DELETE FROM Games WHERE Title = '" + childName + "'");
            QString strRemoveGrandchild("DROP TABLE '" + childName + "'");
            QSqlQuery queryRemoveChild;
            QSqlQuery queryRemoveGrandchild;
            queryRemoveChild.exec(strRemoveChild);
            queryRemoveGrandchild.exec(strRemoveGrandchild);
        }

        //Удаление папки буквы и всего содержимого
        QString path = m_dir.path() + '/' + selectedOriginalIndex.data().toString().at(0);
        QDir dir(path);
        dir.removeRecursively();
        //Добавить qDebug?
    }
    else if(!selectedOriginalIndex.parent().parent().isValid())
    {
        qDebug() << "Game";
        //Удаление игры и модов из под этой игры из БД
        QString childName = selectedOriginalIndex.data().toString();
        QString strRemoveChild("DELETE FROM Games WHERE Title = '" + childName + "'");
        QSqlQuery queryRemoveChild;
        queryRemoveChild.exec(strRemoveChild);
        if(m_model->getItem(selectedOriginalIndex)->childCount() > 0)
        {
            qDebug() << "Child";
            QString strRemoveGrandchild("DROP TABLE '" + childName + "'");
            QSqlQuery queryRemoveGrandchild;
            queryRemoveGrandchild.exec(strRemoveGrandchild);
        }

        //Удаление папки игры со всеми модами
        QString path = m_dir.path() + '/' + selectedOriginalIndex.data().toString().at(0) + '/' + selectedIndex.data().toString();
        QDir dir(path);
        dir.removeRecursively();
        //Добавить qDebug?
    }
    else if(!selectedOriginalIndex.parent().parent().parent().isValid())
    {
        qDebug() << "Mod";
        //Удаление мода из БД
        QString gameName = selectedOriginalIndex.parent().data().toString();
        QString grandChildName = selectedOriginalIndex.data().toString();
        QString strRemoveMod("DELETE FROM '" + gameName + "' WHERE Title = '" + grandChildName + "'");
        QSqlQuery queryRemove;
        queryRemove.exec(strRemoveMod);

        if(m_model->getItem(selectedOriginalIndex.parent())->childCount() == 1) // 1, т.к. удаление из модели происходит после редактирования БД
        {
            QString strDropTable("DROP TABLE '" + gameName + "'");
            QSqlQuery queryDrop;
            queryDrop.exec(strDropTable);
        }

        //Удаление папки мода
        QString path = m_dir.path() + '/' + selectedOriginalIndex.parent().data().toString().at(0) + '/' + selectedIndex.parent().data().toString() + "/mods/" + selectedIndex.data().toString();
        QDir dir(path);
        dir.removeRecursively();
    }

    //Удаление из модели
    m_proxy->removeRow(selectedIndex.row(), selectedIndex);
}

void MainWindow::slotEdit()
{
    qDebug() << "Slot Edit";

    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex();
    qDebug() << selectedIndex.data();
    QModelIndex selectedOriginalIndex = m_proxy->mapToSource(selectedIndex);

    //Создаем диалог
    AddGameDialog dialog;

    //Если выбрана игра
    if(!selectedOriginalIndex.parent().parent().isValid())
    {
        qDebug() << selectedIndex.data();
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = selectedOriginalIndex.data().toString();
        QString strPath("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next();
        QString path = queryPath.value(0).toString();

        //Устанавливаем поля в диалоге в соответствии с данными в БД
        dialog.setNamePath(gameName, path);

        //Отображаем диалог и если нажата Ок
        if(dialog.exec() == QDialog::Accepted)
        {
            qDebug() << selectedIndex.data();
            //Останавливаем плеер и очищаем список
            m_audioPlayer->stop();
            m_audioPlayerList->clear();

            //Если имя не поменялось, то можно не лезть в модель
            if(dialog.getInfo().m_name == gameName)
            {
                if(dialog.getInfo().m_path != path)
                {
                    //Обновляем путь в БД
                    QString strUpdPath("UPDATE Games SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + gameName + "'");
                    QSqlQuery queryUpd;
                    queryUpd.exec(strUpdPath);
                }
            }
            else //Если имя поменялось
            {
                qDebug() << selectedIndex.data();
                //Тут придется лезть в модель
                //А также менять имя игры не только в таблице игр, но и название таблицы к этой игре
                if(dialog.getInfo().m_path != path)
                {
                    //Меняем путь в таблицы игр в БД
                    QString strUpdPath("UPDATE Games SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + gameName + "'");
                    QSqlQuery queryUpd;
                    queryUpd.exec(strUpdPath);
                }
                //Обновляем таблицу игр
                QString strUpdName("UPDATE Games SET Title = '" + dialog.getInfo().m_name + "' WHERE Title = '" + gameName + "'");
                QSqlQuery queryUpdName;
                queryUpdName.exec(strUpdName);

                //Обновляем имя таблицы модов к этой игре
                QString strUpdModTableName("ALTER TABLE '" + gameName + "' RENAME TO '" + dialog.getInfo().m_name + "'");
                QSqlQuery queryUpdModTable;
                queryUpdModTable.exec(strUpdModTableName);

                //Если первая буква совпадает
                if(dialog.getInfo().m_name.at(0) == gameName.at(0))
                {
                    //Меняем данные в модели
                    m_model->setData(selectedOriginalIndex, dialog.getInfo().m_name);

                    //Переимен. папку
                    QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                    QString newPath = m_dir.path() + '/' + gameName.at(0) + '/' + dialog.getInfo().m_name;
                    QDir dir;
                    dir.rename(oldPath, newPath);
                }
                else //Если буква не совпадает
                {
                    //Ищем есть ли такая буква
                    int i = 0;
                    bool isFound = false;
                    for(; i < m_model->getRoot()->childCount(); ++i)
                    {
                        if(m_model->getRoot()->child(i)->data().at(0) == dialog.getInfo().m_name.at(0))
                        {
                            isFound = true;
                            break;
                        }
                    }

                    //Если буква нашлась
                    if(isFound)
                    {
                        qDebug() << "Game";
                        qDebug() << "Letter Found!";
                        //Получаем индекс буквы
                        QModelIndex parent = m_model->index(i, 0);

                        //Получаем номер новой строки
                        int newRowNumber = m_model->getRoot()->child(i)->childCount();

                        //Добавляем строку
                        m_proxy->insertRow(newRowNumber, m_proxy->mapFromSource(parent));

                        //Получаем индекс новой строки
                        QModelIndex newIdx = m_model->index(newRowNumber, 0, parent);

                        //Устанавливаем данные в новой строке
                        m_proxy->setData(newIdx, dialog.getInfo().m_name);

                        /*Добавляем моды*/
                        //Если моды есть
                        if(m_model->getItem(selectedOriginalIndex)->childCount() > 0)
                        {
                            qDebug() << "Has children";

                            //Получаем список всех детей, что бы узнать их имена
                            QList<TreeItem*> modItem = m_model->getItem(selectedOriginalIndex)->getList();

                            int childCount = m_model->getItem(selectedOriginalIndex)->childCount();
                            for(int i = 0; i < childCount; ++i)
                            {
                                //Добавляем строку
                                m_proxy->insertRow(i, m_proxy->mapFromSource(newIdx));

                                //Получаем индекс на эту строку
                                QModelIndex modIdx = m_model->index(i, 0, newIdx);

                                //Устанавливаем данные в этой строке
                                m_model->setData(modIdx, modItem.at(i)->data());
                            }
                        }
                        /*Добавляем моды*/

                        //Перемещаем папку
                        QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                        QString newPath = m_dir.path() + '/' + dialog.getInfo().m_name.at(0) + '/' + dialog.getInfo().m_name;
                        QDir dir;
                        dir.rename(oldPath, newPath);

                        //Удаляем старую запись
                        //Только так т.к. selectedIndex меняет свое значение после добавления строки
                        m_proxy->removeRow(m_proxy->mapFromSource(selectedOriginalIndex).row(), m_proxy->mapFromSource(selectedOriginalIndex));
                    }
                    else //Если буквы нету
                    {
                        qDebug() << "Not Found!";
                        //Возможно надо добавить перевода буквы в Верхний регистр

                        /*Добавляем букву*/
                        //Получаем номер новой строки
                        int newRowNumber = m_model->getRoot()->childCount();

                        //Добавляем строку
                        m_proxy->insertRow(newRowNumber);

                        //Получаем индекс на эту строку
                        QModelIndex letterIdx = m_model->index(newRowNumber, 0);

                        //Устанавливаем данные в этой строке
                        m_proxy->setData(letterIdx, dialog.getInfo().m_name.at(0));
                        /*Добавляем букву*/

                        /*Добавляем игру*/
                        //Добавляем строку(0-ая, т.к. там ничего до этого не было)
                        m_proxy->insertRow(0, m_proxy->mapFromSource(letterIdx));

                        //Получаем индекс на эту строку
                        QModelIndex gameIdx = m_model->index(0, 0, letterIdx);

                        //Устанавливаем данные в этой строке
                        m_proxy->setData(gameIdx, dialog.getInfo().m_name);
                        /*Добавляем игру*/

                        /*Добавляем моды*/
                        //Если моды есть
                        if(m_model->getItem(selectedOriginalIndex)->childCount() > 0)
                        {
                            qDebug() << "Has children";

                            //Получаем список всех детей, что бы узнать их имена
                            QList<TreeItem*> modItem = m_model->getItem(selectedOriginalIndex)->getList();

                            int childAmount = m_model->getItem(selectedOriginalIndex)->childCount();
                            for(int childCount = 0; childCount < childAmount; ++childCount)
                            {
                                //Добавляем строку
                                m_proxy->insertRow(childCount, m_proxy->mapFromSource(gameIdx));

                                //Получаем индекс на эту строку
                                QModelIndex modIdx = m_model->index(childCount, 0, gameIdx);

                                //Устанавливаем данные в этой строке
                                m_model->setData(modIdx, modItem.at(childCount)->data());
                            }
                        }
                        //Перемещаем папку
                        m_dir.mkdir(dialog.getInfo().m_name.at(0));
                        QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                        QString newPath = m_dir.path() + '/' + dialog.getInfo().m_name.at(0) + '/' + dialog.getInfo().m_name;
                        QDir dir;
                        dir.rename(oldPath, newPath);

                        //Удаляем игру
                        m_proxy->removeRow(m_proxy->mapFromSource(selectedOriginalIndex).row(), m_proxy->mapFromSource(selectedOriginalIndex));
                    }
                }
            }
        }
    }
    else if(!selectedOriginalIndex.parent().parent().parent().isValid())//Если выбран мод
    {
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = selectedOriginalIndex.parent().data().toString();
        QString strPath("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next();
        QString path = queryPath.value(0).toString();

        //Устанавливаем поля в диалоге в соответствии с данными в БД
        dialog.setNamePath(gameName, path);

        //Отображаем диалог и если нажата Ок
        if(dialog.exec() == QDialog::Accepted)
        {
            //Останавливаем плеер и очищаем список
            m_audioPlayer->stop();
            m_audioPlayerList->clear();

            //Если имя не поменялось
            if(dialog.getInfo().m_name == gameName)
            {
                //Если одинокавы, то можно не лезть в модель
                //Только в случае, если путь изменился, тогда лезем в БД
                if(dialog.getInfo().m_path != path)
                {
                    //Обновляем путь в БД
                    QString strUpdPath("UPDATE Games SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + gameName + "'");
                    QSqlQuery queryUpd;
                    queryUpd.exec(strUpdPath);
                }
            }
            else //Если имя поменялось
            {
                //Тут придется лезть в модель
                //А также менять имя игры не только в таблице игр, но и в таблице модов к этой игре
                if(dialog.getInfo().m_path != path)
                {
                    //Меняем путь в таблицы игр в БД
                    QString strUpdPath("UPDATE Games SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + gameName + "'");
                    QSqlQuery queryUpd;
                    queryUpd.exec(strUpdPath);
                }

                //Обновляем таблицу игр
                QString strUpdName("UPDATE Games SET Title = '" + dialog.getInfo().m_name + "' WHERE Title = '" + gameName + "'");
                QSqlQuery queryUpdName;
                queryUpdName.exec(strUpdName);

                //Обновляем имя таблицы модов к этой игре
                QString strUpdModTableName("ALTER TABLE '" + gameName + "' RENAME TO '" + dialog.getInfo().m_name + "'");
                QSqlQuery queryUpdModTable;
                queryUpdModTable.exec(strUpdModTableName);

                //Если первая буква совпадает
                if(dialog.getInfo().m_name.at(0) == gameName.at(0))
                {
                    //Меняем данные в модели
                    m_model->setData(selectedOriginalIndex.parent(), dialog.getInfo().m_name);

                    //Переимен. папку
                    QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                    QString newPath = m_dir.path() + '/' + gameName.at(0) + '/' + dialog.getInfo().m_name;
                    QDir dir;
                    dir.rename(oldPath, newPath);
                }
                else //Если буква не совпадает
                {
                    //Ищем есть ли такая буква
                    int i = 0;
                    bool isFound = false;
                    for(; i < m_model->getRoot()->childCount(); ++i)
                    {
                        if(m_model->getRoot()->child(i)->data().at(0) == dialog.getInfo().m_name.at(0))
                        {
                            isFound = true;
                            break;
                        }
                    }

                    //Если буква нашлась
                    if(isFound)
                    {
                        qDebug() << "Found!";
                        //Получаем индекс буквы
                        QModelIndex parent = m_model->index(i, 0);

                        //Получаем номер новой строки
                        int newRowNumber = m_model->getRoot()->child(i)->childCount();

                        //Добавляем строку
                        m_proxy->insertRow(newRowNumber, m_proxy->mapFromSource(parent));

                        //Получаем индекс новой строки
                        QModelIndex newIdx = m_model->index(newRowNumber, 0, parent);

                        //Устанавливаем данные в новой строке
                        m_proxy->setData(newIdx, dialog.getInfo().m_name);

                        /*Добавляем моды*/
                        //Если моды есть
                        if(m_model->getItem(selectedOriginalIndex.parent())->childCount() > 0)
                        {
                            qDebug() << "Has children";

                            //Получаем список всех детей, что бы узнать их имена
                            QList<TreeItem*> modItem = m_model->getItem(selectedOriginalIndex.parent())->getList();

                            int childCount = m_model->getItem(selectedOriginalIndex.parent())->childCount();
                            for(int i = 0; i < childCount; ++i)
                            {
                                //Добавляем строку
                                m_proxy->insertRow(i, m_proxy->mapFromSource(newIdx));

                                //Получаем индекс на эту строку
                                QModelIndex modIdx = m_model->index(i, 0, newIdx);

                                //Устанавливаем данные в этой строке
                                m_model->setData(modIdx, modItem.at(i)->data());
                            }
                        }
                        /*Добавляем моды*/

                        //Перемещаем папку
                        QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                        QString newPath = m_dir.path() + '/' + dialog.getInfo().m_name.at(0) + '/' + dialog.getInfo().m_name;
                        QDir dir;
                        dir.rename(oldPath, newPath);

                        //Удаляем старую запись
                        qDebug() << "Start remove";
                        m_proxy->removeRow(m_proxy->mapFromSource(selectedOriginalIndex).parent().row(), m_proxy->mapFromSource(selectedOriginalIndex).parent());
                        qDebug() << "End remove";
                    }
                    else //Если буквы нет
                    {
                        qDebug() << "Not Found!";
                        //Возможно надо добавить перевода буквы в Верхний регистр

                        /*Добавляем букву*/
                        //Получаем номер новой строки
                        int newRowNumber = m_model->getRoot()->childCount();

                        //Добавляем строку
                        //m_model->insertRow(newRowNumber);
                        m_proxy->insertRow(newRowNumber);

                        //Получаем индекс на эту строку
                        QModelIndex letterIdx = m_model->index(newRowNumber, 0);

                        //Устанавливаем данные в этой строке
                        m_proxy->setData(letterIdx, dialog.getInfo().m_name.at(0));
                        /*Добавляем букву*/

                        /*Добавляем игру*/
                        //Добавляем строку(0-ая, т.к. там ничего еще нету)
                        m_proxy->insertRow(0, m_proxy->mapFromSource(letterIdx));

                        //Получаем индекс на эту строку
                        QModelIndex gameIdx = m_model->index(0, 0, letterIdx);

                        //Устанавливаем данные в этой строке
                        m_proxy->setData(gameIdx, dialog.getInfo().m_name);
                        /*Добавляем игру*/

                        /*Добавляем моды*/
                        //Если моды есть
                        if(m_model->getItem(selectedOriginalIndex.parent())->childCount() > 0)
                        {
                            qDebug() << "Has choldren";

                            //Получаем список всех детей, что бы узнать их имена
                            QList<TreeItem*> modItem = m_model->getItem(selectedOriginalIndex.parent())->getList();

                            int childAmount = m_model->getItem(selectedOriginalIndex.parent())->childCount();
                            for(int childCount = 0; childCount < childAmount; ++childCount)
                            {
                                //Добавляем строку
                                m_proxy->insertRow(childCount, m_proxy->mapFromSource(gameIdx));

                                //Получаем индекс на эту строку
                                QModelIndex modIdx = m_model->index(childCount, 0, gameIdx);

                                //Устанавливаем данные в этой строке
                                m_model->setData(modIdx, modItem.at(childCount)->data());
                            }
                        }
                        /*Добавляем моды*/

                        //Перемещаем папку
                        m_dir.mkdir(dialog.getInfo().m_name.at(0));
                        QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName;
                        QString newPath = m_dir.path() + '/' + dialog.getInfo().m_name.at(0) + '/' + dialog.getInfo().m_name;
                        QDir dir;
                        dir.rename(oldPath, newPath);

                        //Удаляем игру
                        m_proxy->removeRow(m_proxy->mapFromSource(selectedOriginalIndex).parent().row(), m_proxy->mapFromSource(selectedOriginalIndex).parent());
                    }
                }
            }
        }
    }
}

void MainWindow::slotEditMod()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex();
    //TODO: При стирании имени мода, если строка остается пустой, то можно нажать "Ок". Пофиксить.
    qDebug() << "Edit mod" << selectedIndex.data().toString() << "of" << selectedIndex.parent().data().toString();

    //Создаем диалог
    EditModDialog dialog;

    //Устанавливаем имя окна
    dialog.setWindowTitle(tr("Editing Mod"));

    //Получаем имя мода
    QString modName = selectedIndex.data().toString();

    //Получаем имя игры
    QString gameName = selectedIndex.parent().data().toString();

    //Получаем путь до ехе мода из БД
    QString strPath("SELECT Path FROM '" + gameName + "' WHERE Title = '" + modName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next();
    QString path = queryPath.value(0).toString();

    //Добавляем в диалог имя мода и путь до .ехе
    dialog.setNamePath(modName, path);

    //Отображаем диалог и если нажата кнопка Ок
    if(dialog.exec() == QDialog::Accepted)
    {
        //Останавливаем плеер и очищаем список
        m_audioPlayer->stop();
        m_audioPlayerList->clear();

        //Если имя не совпадает, то надо лезть в модель
        if(dialog.getInfo().m_name != modName)
        {
            if(dialog.getInfo().m_path != path)
            {
                //Обновляем путь в БД
                QString strUpdPath("UPDATE '" + gameName + "' SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + modName + "'");
                QSqlQuery queryUpd;
                queryUpd.exec(strUpdPath);
                qDebug() << strUpdPath;
            }

            //Обновляем имя в БД
            QString strUpdName("UPDATE '" + gameName + "' SET Title = '" + dialog.getInfo().m_name + "' WHERE Title = '" + modName + "'");
            QSqlQuery queryUpdName;
            queryUpdName.exec(strUpdName);

            //Переимен. папку мода
            QString oldPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName;
            QString newPath = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + "/mods/" + dialog.getInfo().m_name;
            QDir dir;
            dir.rename(oldPath, newPath);

            //Обновляем модель
            m_proxy->setData(m_proxy->mapToSource(selectedIndex), dialog.getInfo().m_name);

        }
        else //Если имя одинаково, то лезем только в БД
        {
            //Только если путь изменился, лезем БД
            if(dialog.getInfo().m_path != path)
            {
                //Обновляем путь в БД
                QString strUpdPath("UPDATE '" + gameName + "' SET Path = '" + dialog.getInfo().m_path + "' WHERE Title = '" + modName + "'");
                QSqlQuery queryUpd;
                queryUpd.exec(strUpdPath);
            }
        }
    }
}

void MainWindow::slotStart()
{
    qDebug() << "Slot Start!";
    //WARNING: Проблема такого запуска игр, в том, что будет если ехе находится на большей вложенности

    //Получаем имя игры
    QString gameName = ui->treeView->selectionModel()->currentIndex().data().toString();

    //Получаем путь до .ехе из БД
    QString strPath = ("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next();
    QString path = queryPath.value(0).toString();

    qDebug() << "Path: " << path;

    qDebug() << "Start Game:" << gameName << "From:" << path;

    //Устанавливаем путь до папки где расположен ехе
    QDir dir(path);
    dir.cdUp();
    QDir::setCurrent(dir.path());

    qDebug() << "Current Path:" << QDir::currentPath();

    //Запускаем .ехе
    QFileInfo pathToExe(path);
    qDebug() << "Path To .exe: " << pathToExe.fileName();

//    QProcess::startDetached(pathToExe.fileName()); // Старый запуск

    QString execute = "start \"\" \"" + pathToExe.fileName() + '\"';
    qDebug() << "Execute string: " << execute;
    system(execute.toStdString().c_str());
}

void MainWindow::slotStartWithParameters()
{
    qDebug() << "Start with paremeters" << m_selectedIndex.data().toString();

    ArgsDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        //Получаем имя игры
        QString gameName = m_selectedIndex.data().toString();

        //Получаем путь до ехе из БД
        QString strPath = ("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next();
        QString path = queryPath.value(0).toString();

        qDebug() << "Path: " << path;

        //Устанавливаем путь до папки где расположен ехе
        QDir dir(path);
        dir.cdUp();

        QDir::setCurrent(dir.path());

        qDebug() << "Current Path:" << QDir::currentPath();

        //Запускаем .ехе
        QFileInfo pathToExe(path);
        qDebug() << "Path To .exe: " << pathToExe.fileName();
//        QProcess::startDetached(pathToExe.fileName()); // Старый запуск

        QString execute = "start \"\" \"" + pathToExe.fileName() + "\" ";
        QStringList argsList = dialog.getList();
        foreach(QString arg, argsList)
        {
            execute.append(" ");
            execute.append(arg);
        }
        qDebug() << "Execute string: " << execute;
        system(execute.toStdString().c_str());
    }
}

void MainWindow::slotStartMod()
{
    //WARNING: Проблема такого запуска мода, в том, что будет если ехе находится на большей вложенности

    //Получаем имя мода
    QString modName = ui->treeView->selectionModel()->currentIndex().data().toString();

    //Получаем имя игры
    QString gameName = ui->treeView->selectionModel()->currentIndex().parent().data().toString();

    qDebug() << "------------";
    qDebug() << modName;
    qDebug() << gameName;

    //Получаем путь до .ехе из БД
    QString strPath = ("SELECT Path FROM '" + gameName + "' WHERE Title = '" + modName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next();
    QString path = queryPath.value(0).toString();

    qDebug() << "Start Mod:" << modName << "From:" << path;

    //Устанавливаем путь до папки где расположен ехе
    QDir dir(path);
    dir.cdUp();
    QDir::setCurrent(dir.path());

    qDebug() << "Current Path:" << QDir::currentPath();

    QFileInfo pathToExe(path);
//    QProcess::startDetached(pathToExe.fileName()); Старый запуск

    QString execute = "start \"\" \"" + pathToExe.fileName() + '\"';
    qDebug() << "Execute string: " << execute;
    system(execute.toStdString().c_str());
}

void MainWindow::slotStartModWithParameters()
{
    qDebug() << "Start Mod with parameters:";

    ArgsDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        //Получаем имя игры
        QString modName = m_selectedIndex.data().toString();

        //Получаем имя игры
        QString gameName = m_selectedIndex.parent().data().toString();

        //Получаем путь до .ехе из БД
        QString strPath = ("SELECT Path FROM '" + gameName + "' WHERE Title = '" + modName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next();
        QString path = queryPath.value(0).toString();

        qDebug() << "Start Mod:" << modName << "From:" << path;

        //Устанавливаем путь до папки где расположен ехе
        QDir dir(path);
        dir.cdUp();
        QDir::setCurrent(dir.path());

        qDebug() << "Current Path:" << QDir::currentPath();

        //Запускаем .ехе
        QFileInfo pathToExe(path);
//        QProcess::startDetached(pathToExe.fileName()); // Старый запуск

        QString execute = "start \"\" \"" + pathToExe.fileName() + "\" ";
        QStringList argsList = dialog.getList();
        foreach(QString arg, argsList)
        {
            execute.append(" ");
            execute.append(arg);
        }
        qDebug() << "Execute string: " << execute;
        system(execute.toStdString().c_str());
    }
}

void MainWindow::slotAdd()
{
    qDebug() << "Add game";

    //Создаем диалог
    AddGameDialog dialog;

    //Отображаем диалог и если нажата кнопка Ок
    if(dialog.exec() == QDialog::Accepted)
    {
        //Получаем имя игры и путь до exe
        QString gameName = dialog.getInfo().m_name;
        QString path = dialog.getInfo().m_path;

        qDebug() << gameName << path;

        //Ищем букву
        int i = 0;
        bool isFound = false;
        for(; i < m_model->getRoot()->childCount(); ++i)
        {
            if(m_model->getRoot()->child(i)->data() == gameName.at(0))
            {
                isFound = true;
                break;
            }
        }

        //Если буква найдена
        if(isFound)
        {
            qDebug() << "Letter found";

            //Получаем индекс родителя(буквы)
            QModelIndex parent = m_model->index(i, 0);

            //Получаем номер новой строки
            int newRowNumber = m_model->getRoot()->child(i)->childCount();

            //Добавляем строку
            m_proxy->insertRow(newRowNumber, m_proxy->mapFromSource(parent));

            //Получаем индекс новой строки
            QModelIndex newIdx = m_model->index(newRowNumber, 0, parent);

            //Устанавливаем данные в новой строке
            m_proxy->setData(newIdx, gameName);

            //Создаем папки игры и т.д
            QString pathToLetter = m_dir.path() + '/' + gameName.at(0);
            QDir dir(pathToLetter);
            QString pathToGame = pathToLetter + '/' + gameName + '/';
            dir.mkdir(gameName);
            dir.setPath(pathToGame);
            dir.mkpath("music/covers");
            dir.mkpath("image/covers");
            dir.mkpath("image/screenshots");
            dir.mkdir("video");
            dir.mkdir("mods");

            //Добавляем в БД
            QString strInsert("INSERT INTO Games(Title, Path) VALUES ('" + gameName + "', '" + path + "');");
            QSqlQuery queryInsert;
            queryInsert.exec(strInsert);
        }
        else //Если нет
        {
            qDebug() << "Letter not found";

            //Добавляем строку
            int newRowNumber = m_model->getRoot()->childCount();
            m_proxy->insertRow(newRowNumber);

            //Получаем индекс добавленной строки
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0);

            //Переименовываем пустую строку
            m_proxy->setData(newRowIdx, gameName.at(0));

            /*Добавляем игру*/
            //Добавляем строку
            m_proxy->insertRow(0, m_proxy->mapFromSource(newRowIdx));

            //Получаем индекс на вставленную строку
            QModelIndex newGameIdx = m_model->index(0, 0, newRowIdx);

            //Устанавливаем данные в этой строке
            m_proxy->setData(newGameIdx, gameName);

            //Создаем папки буквы/игры и т.д
            QString pathToGame = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + '/';
            m_dir.mkpath(pathToGame);
            QDir dir(pathToGame);
            dir.mkpath("music/covers");
            dir.mkpath("image/covers");
            dir.mkpath("image/screenshots");
            dir.mkdir("video");
            dir.mkdir("mods");

            //Добавляем запись в БД
            QString strInsert("INSERT INTO Games(Title, Path) VALUES ('" + gameName + "', '" + path + "');");
            QSqlQuery queryInsert;
            queryInsert.exec(strInsert);
        }
    }
}

void MainWindow::slotAddMod()
{
    QModelIndex selectedIndex = m_proxy->mapToSource(m_selectedIndex);

    qDebug() << "Add mod";

    //Создаем диалог
    AddModDialog dialog;

    //Если выбранный эл-т игра
    if(!selectedIndex.parent().parent().isValid()) //WARNING: Тут могут быть проблемы
    {
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = selectedIndex.data().toString();
        QString strGamePath("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strGamePath);
        queryPath.next(); //Проверка на валидность?
        QString path = queryPath.value(0).toString();

        //Устанавливаем поля в диалоге в соответствии с данными в БД
        dialog.setNamePath(gameName, path);

        //Отображаем диалог и если нажата кнопка Ок
        if(dialog.exec() == QDialog::Accepted)
        {
            //Получаем имя мода
            QString modName = dialog.getInfo().m_name;

            //Получаем номер строки
            int newRowNumber = m_model->getItem(selectedIndex)->childCount();

            //Добавляем строку
            m_proxy->insertRow(newRowNumber, m_selectedIndex);

            //Получаем индекс на новую строку
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0, selectedIndex);

            //Устанавливаем данные в этой строке
            m_proxy->setData(newRowIdx, modName);

            //Добавляем таблицу с модами если ее ещё нету
            QString strCreate("CREATE TABLE IF NOT EXISTS '" + gameName + "' (ID INTEGER PRIMARY KEY AUTOINCREMENT, Title STRING, Path STRING);");
            QSqlQuery queryCreate;
            queryCreate.exec(strCreate);

            //Создаем папки для мода
            QString pathToModsFolder = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + "/mods";
            QDir dir(pathToModsFolder);
            dir.mkdir(modName);
            QString pathToMod = pathToModsFolder + '/' + modName;
            dir.setPath(pathToMod);
            dir.mkpath("music/covers");
            dir.mkpath("image/covers");
            dir.mkpath("image/screenshots");
            dir.mkdir("video");

            //Добавляем запись в БД
            QString strInsert("INSERT INTO '" + gameName + "'(Title, Path) VALUES('" + modName + "', '" + dialog.getInfo().m_path + "');");
            QSqlQuery queryInsert;
            queryInsert.exec(strInsert);
        }
    }
    else //WARNING: Тут могут быть проблемы
    {
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = selectedIndex.parent().data().toString();
        QString strPath("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next(); //Проверка на валидность??
        QString path = queryPath.value(0).toString();

        //Устанавливаем поля в диалоге в соответствии с данными в БД
        dialog.setNamePath(gameName, path);

        //Отображаем диалог и если нажата кнопка Ок
        if(dialog.exec() == QDialog::Accepted)
        {
            QString modName = dialog.getInfo().m_name;

            //Получаем номер строки
            int newRowNumber = m_model->getItem(selectedIndex.parent())->childCount();

            //Добавляем строку
            m_proxy->insertRow(newRowNumber, m_selectedIndex.parent());

            //Получаем индекс на новую строку
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0, selectedIndex.parent());

            //Устанавливаем название
            m_proxy->setData(newRowIdx, modName);

            //Добавляем таблицу с модами если ее ещё нету
            QString strCreate("CREATE TABLE IF NOT EXISTS '" + gameName + "' (ID INTEGER PRIMARY KEY AUTOINCREMENT, Title STRING, Path STRING);");
            QSqlQuery queryCreate;
            queryCreate.exec(strCreate);

            //Создаем папки для мода
            QString pathToModsFolder = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + "/mods";
            QDir dir(pathToModsFolder);
            dir.mkdir(modName);
            QString pathToMod = pathToModsFolder + '/' + modName;
            dir.setPath(pathToMod);
            dir.mkpath("music/covers");
            dir.mkpath("image/covers");
            dir.mkpath("image/screenshots");
            dir.mkdir("video");

            //Добавляем мод в БД
            QString strInsert("INSERT INTO '" + gameName + "'(Title, Path) VALUES('" + modName + "', '" + dialog.getInfo().m_path + "');");
            QSqlQuery queryInsert;
            queryInsert.exec(strInsert);
        }
    }
}

void MainWindow::slotOpenGameDir()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex(); //mapToSource?
    QString gameName = selectedIndex.data().toString();
    QString strPath("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next(); //Проверка на валидность??
    QString path = queryPath.value(0).toString();

    QFileInfo info(path);

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(info.path())))
    {
        QMessageBox::information(this, tr("Message"), tr("Directory: ") + path + tr(" doesn't exist"));
    }
}

void MainWindow::slotOpenModDir()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex(); //mapToSource?
    QString gameName = selectedIndex.parent().data().toString();
    QString modName = selectedIndex.data().toString();
    QString strPath("SELECT Path FROM '" + gameName + "' WHERE Title = '" + modName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next(); //Проверка на валидность??
    QString path = queryPath.value(0).toString();

    QFileInfo info(path);

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(info.path())))
    {
        QMessageBox::information(this, tr("Message"), tr("Directory: ") + path + tr(" doesn't exist"));
    }
}

void MainWindow::slotOpenProgramGameDir()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex(); //mapToSource?
    QString dirPath = m_appPath + "/Games/" + selectedIndex.data().toString().at(0) + '/' + selectedIndex.data().toString();

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(dirPath)))
    {
        QMessageBox::information(this, tr("Message"), tr("Directory: ") + dirPath + tr(" doesn't exist"));
    }
}

void MainWindow::slotOpenProgramModDir()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex(); //mapToSource?
    QString dirPath = m_appPath + "/Games/" + selectedIndex.parent().data().toString().at(0) + '/' + selectedIndex.parent().data().toString() + "/mods/" + selectedIndex.data().toString();

    if(!QDesktopServices::openUrl(QUrl::fromLocalFile(dirPath)))
    {
        QMessageBox::information(this, tr("Message"), tr("Directory: ") + dirPath + tr(" doesn't exist"));
    }
}
/*Context Menu*/

/*Buttons*/
void MainWindow::on_buttonStart_clicked()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex();
    if(!selectedIndex.parent().parent().isValid())
    {
        slotStart();
    }
    else if(!selectedIndex.parent().parent().parent().isValid())
    {
        slotStartMod();
    }
}

void MainWindow::on_buttonEdit_clicked()
{
    QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex();
    if(!selectedIndex.parent().parent().isValid())
    {
        slotEdit();
    }
    else if(!selectedIndex.parent().parent().parent().isValid())
    {
        slotEditMod();
    }
}

void MainWindow::on_buttonRemove_clicked()
{
    if(ui->treeView->selectionModel()->currentIndex().isValid())
        slotDelete();
}
/*Buttons*/

void MainWindow::slotButtonActivator(QModelIndex selectedIndex)
{
    bool isLMBCliked = false;
    if(QApplication::mouseButtons() == Qt::LeftButton)
    {
        qDebug() << "LEFT";
        isLMBCliked = true;
    }
    else if(QApplication::mouseButtons() == Qt::RightButton)
    {
        qDebug() << "RIGHT";
    }
    if(!selectedIndex.parent().isValid())
    {
        ui->buttonStart->setDisabled(true);
        ui->buttonEdit->setDisabled(true);
        ui->buttonRemove->setDisabled(true);
    }
    else
    {
        ui->buttonStart->setEnabled(true);
        ui->buttonEdit->setEnabled(true);
        ui->buttonRemove->setEnabled(true);
    }

    //Путь до основной папки с медиафайлами
    QString pathToItem = m_appPath + "/Games";

    /*Получаем медиафайламы*/
    if(!selectedIndex.parent().isValid()) // Если выбрана буква
    {
        qDebug() << "It's Letter";
    }
    else if(!selectedIndex.parent().parent().isValid()) //Если выбрана игра
    {
        //Очищаем список и сцены, а также обновляем отображения
        ui->textBrowser->clear();
        m_coverScene->clear();
        m_mediaScene->clear();
        ui->coversView->viewport()->update();
        ui->mediaView->viewport()->update();

        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = selectedIndex.data().toString();

        /*Audio Player*/
        //Работаем с аудио только в с случае нажатия ЛКМ на итеме
        if(isLMBCliked)
        {
            QString strToMusic = '/' + gameName.at(0) + '/' + gameName + "/music";
            QString strToMusicCovers = '/' + gameName.at(0) + '/' + gameName + "/music/covers";

            QString pathToMusic = pathToItem + strToMusic;
            QString pathToMusicCovers = pathToItem + strToMusicCovers;

            QDir musDir(pathToMusic);
            QDir musCoverDir(pathToMusicCovers);

            QStringList musList = musDir.entryList(QStringList() << "*.mp3", QDir::Files);
            QStringList musCoverList = musCoverDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

            bool isListEmpty = false;

            //Очищаем список, только если в выбраном итеме есть мп3 файлы
            if(!musList.isEmpty())
            {
                isListEmpty = true;
                m_audioPlayerList->clear();
                if(musCoverList.isEmpty())
                    ui->coverLabel->setText("");
                else
                {
                    ui->coverLabel->setText("<img src = \"" + pathToMusicCovers + '/' + musCoverList.at(0) + "\" height = \"60\" width = \"60\" />");
                    qDebug() << "<img src = " + pathToMusicCovers + '/' + musCoverList.at(0) + " height = \"60\" width = \"60\" />";
                }

                if(m_isPlayButtonClicked)
                {
                    m_isPlayButtonClicked = false;
                    ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
                    m_audioPlayer->pause();
                }
            }

            foreach (QString audio, musList)
            {
                m_audioPlayerList->addMedia(QUrl::fromLocalFile(pathToMusic + '/' + audio));
            }

            if(isListEmpty)
            {
                m_audioPlayer->playlist()->setCurrentIndex(0);
    //            m_audioPlayer->play(); //Начинает воспроизводить композицию при нажатии на итем
            }
        }
        /*Audio Player*/

        //Covers & Media Views
        m_strToMedia = pathToItem + '/' + gameName.at(0) + '/' + gameName + "/image/screenshots";
        m_strToCover = pathToItem + '/' + gameName.at(0) + '/' + gameName + "/image/covers";

        QDir coversDir(m_strToCover);
        QDir mediaDir(m_strToMedia);

        m_coversList = coversDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
        m_mediaList = mediaDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

        if(!m_coversList.isEmpty())
        {
            QPixmap cover(m_strToCover + '/' + m_coversList.at(0));
            ui->coversView->setSceneRect(0, 0, cover.width(), cover.height());
            QGraphicsPixmapItem *coverItem = new QGraphicsPixmapItem(cover);
            m_coverScene->addItem(coverItem);
            ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
        if(!m_mediaList.isEmpty())
        {
            QPixmap media(m_strToMedia + '/' + m_mediaList.at(0));
            ui->mediaView->setSceneRect(0, 0, media.width(), media.height());
            QGraphicsPixmapItem *mediaItem = new QGraphicsPixmapItem(media);
            m_mediaScene->addItem(mediaItem);
            ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);

        }

        //Text Browser
        QString strToHtml = pathToItem + '/' + gameName.at(0) + '/' + gameName;

        QDir htmlDir(strToHtml);
        QStringList htmlList = htmlDir.entryList(QStringList() << "*.html", QDir::Files);

        if(!htmlList.isEmpty())
        {
            QFile htmlFile(strToHtml + '/' + htmlList.at(0));
            htmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream stream(&htmlFile);
            ui->textBrowser->setHtml(htmlFile.readAll());
            htmlFile.close();
        }
    }
    else if(!selectedIndex.parent().parent().parent().isValid()) //Если выбран мод
    {
        //Очищаем список и сцены, а также обновляем отображения
        ui->textBrowser->clear();
        m_coverScene->clear();
        m_mediaScene->clear();
        ui->coversView->viewport()->update();
        ui->mediaView->viewport()->update();

        //Получаем имя мода
        QString modName = selectedIndex.data().toString();

        //Получаем имя игры
        QString gameName = selectedIndex.parent().data().toString();

        /*Audio Player*/
        //Работаем с аудио только в с случае нажатия ЛКМ на итеме
        if(isLMBCliked)
        {
            QString strToMusic = '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName + "/music";
            QString strToMusicCovers = '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName + "/music/covers";

            QString pathToMusic = pathToItem + strToMusic;
            QString pathToMusicCovers = pathToItem + strToMusicCovers;

            QDir musDir(pathToMusic);
            QDir musCoverDir(pathToMusicCovers);

            QStringList musList = musDir.entryList(QStringList() << "*.mp3", QDir::Files);
            QStringList musCoverList = musCoverDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

            bool isListEmpty = false;

            //Очищаем список, только если в выбраном итеме есть мп3 файлы
            if(!musList.isEmpty())
            {
                isListEmpty = true;
                m_audioPlayerList->clear();
                if(musCoverList.isEmpty())
                    ui->coverLabel->setText("");
                else
                {
                    ui->coverLabel->setText("<img src = \"" + pathToMusicCovers + '/' + musCoverList.at(0) + "\" height = \"60\" width = \"60\" />");
                    qDebug() << "<img src = " + pathToMusicCovers + '/' + musCoverList.at(0) + " height = \"60\" width = \"60\" />";
                }

                if(m_isPlayButtonClicked)
                {
                    m_isPlayButtonClicked = false;
                    ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
                    m_audioPlayer->pause();
                }
            }

            foreach (QString audio, musList)
            {
                m_audioPlayerList->addMedia(QUrl::fromLocalFile(pathToMusic + '/' + audio));
            }

            if(isListEmpty)
            {
                m_audioPlayer->playlist()->setCurrentIndex(0);
    //            m_audioPlayer->play(); //Начинает воспроизводить композицию при нажатии на итем
            }
        }
        /*Audio Player*/

        //Covers & Media Views
        m_strToMedia = pathToItem + '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName + "/image/screenshots";
        m_strToCover = pathToItem + '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName + "/image/covers";

        QDir coversDir(m_strToCover);
        QDir mediaDir(m_strToMedia);

        m_coversList = coversDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);
        m_mediaList = mediaDir.entryList(QStringList() << "*.jpg" << "*.png", QDir::Files);

        if(!m_coversList.isEmpty())
        {
            QPixmap cover(m_strToCover + '/' + m_coversList.at(0));
            ui->coversView->setSceneRect(0, 0, cover.width(), cover.height());
            QGraphicsPixmapItem *coverItem = new QGraphicsPixmapItem(cover);
            m_coverScene->addItem(coverItem);
            ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }
        if(!m_mediaList.isEmpty())
        {
            QPixmap media(m_strToMedia + '/' + m_mediaList.at(0));
            ui->mediaView->setSceneRect(0, 0, media.width(), media.height());
            QGraphicsPixmapItem *mediaItem = new QGraphicsPixmapItem(media);
            m_mediaScene->addItem(mediaItem);
            ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
        }

        //Text Browser
        QString strToHtml = pathToItem + '/' + gameName.at(0) + '/' + gameName + "/mods/" + modName;

        QDir htmlDir(strToHtml);
        QStringList htmlList = htmlDir.entryList(QStringList() << "*.html", QDir::Files);

        if(!htmlList.isEmpty())
        {
            QFile htmlFile(strToHtml + '/' + htmlList.at(0));
            htmlFile.open(QIODevice::ReadOnly | QIODevice::Text);
            QTextStream stream(&htmlFile);
            ui->textBrowser->setHtml(htmlFile.readAll());
            htmlFile.close();
        }
    }
    /*Получаем медиафайламы*/

}

/*Dbl Click*/
void MainWindow::slotDblClicked()
{
    on_buttonStart_clicked();
}

void MainWindow::slotFilter()
{
    //Поисковое выражение, без привязки к регистру, с базовым паттерном поиска
    QRegExp filterExpr(ui->searchGameLine->text(), Qt::CaseInsensitive, QRegExp::RegExp);
    m_proxy->setFilterRegExp(filterExpr);
}
/*Dbl Click*/

/*System Tray*/
void MainWindow::slotShowHide()
{
    setVisible(!isVisible());
    if(!isVisible())
    {
        m_coversSlideshowTimer->stop();
        m_mediaSlideshowTimer->stop();
    }
    else
    {
        if(!m_coversSlideshowTimer->isActive())
            m_coversSlideshowTimer->start();
        if(!m_mediaSlideshowTimer->isActive())
            m_mediaSlideshowTimer->start();
    }
}

void MainWindow::slotIconActivated(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
    //case QSystemTrayIcon::Trigger:
    case QSystemTrayIcon::DoubleClick:
        setVisible(true);
        if(!m_coversSlideshowTimer->isActive())
            m_coversSlideshowTimer->start();
        if(!m_mediaSlideshowTimer->isActive())
            m_mediaSlideshowTimer->start();
        break;
    //case QSystemTrayIcon::MiddleClick:
    //    break;
    default:
        ;
    }
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_trayIcon->isVisible())
    {
        m_coversSlideshowTimer->stop();
        m_mediaSlideshowTimer->stop();
        hide();
        event->ignore();
    }
}
/*System Tray*/

void MainWindow::resizeEvent(QResizeEvent *event)
{
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    QMainWindow::resizeEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //TODO: Срабатывает только если не активировано виджет поиска, трифью или текст браузер
    if(event->key() == Qt::Key_Space)
    {
        if(!m_isPlayButtonClicked)
        {
            m_isPlayButtonClicked = true;
            ui->playButton->setIcon(QIcon(":/audioplayer/icons/pause-button.png"));
            m_audioPlayer->play();
        }
        else
        {
            m_isPlayButtonClicked = false;
            ui->playButton->setIcon(QIcon(":/audioplayer/icons/play-button.png"));
            m_audioPlayer->pause();
        }
    }
    else
        QMainWindow::keyPressEvent(event);
}

/*Drag & Drop*/
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    if(event->mimeData()->hasFormat("text/uri-list"))
    {
        event->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *event)
{
    QList<QUrl> urlList = event->mimeData()->urls();
    foreach(QUrl url, urlList)
    {
        if(url.toString().endsWith(".exe") || url.toString().endsWith(".lnk"))
        {
            qDebug() << "Link:" << url;
            QFileInfo info(url.toString());
            QString gameName = info.baseName();
            QFile file(url.toLocalFile());
            qDebug() << "File:" << file.readLink();
            qDebug() << info.suffix();
            QString path;
            if(info.suffix() == "lnk") //Если ссылка, то получаем путь куда ссылается
                 path = file.readLink();
            else if(info.suffix() == "exe") //Если .ехе, просто получаем путь
                 path = url.toLocalFile();
            else
                return;

            //Переводим первую букву в верхний регистр
            gameName.replace(0, 1, gameName.at(0).toUpper());

            //Ищем букву
            int i = 0;
            bool isFound = false;
            for(; i < m_model->getRoot()->childCount(); ++i)
            {
                if(m_model->getRoot()->child(i)->data() == gameName.at(0))
                {
                    isFound = true;
                    break;
                }
            }

            //Если буква найдена
            if(isFound)
            {
                qDebug() << "Letter found";

                //Получаем индекс родителя(буквы)
                QModelIndex parent = m_model->index(i, 0);

                //Получаем номер новой строки
                int newRowNumber = m_model->getRoot()->child(i)->childCount();

                //Добавляем строку
                m_proxy->insertRow(newRowNumber, m_proxy->mapFromSource(parent));

                //Получаем индекс новой строки
                QModelIndex newIdx = m_model->index(newRowNumber, 0, parent);

                //Устанавливаем данные в новой строке
                m_proxy->setData(newIdx, gameName);

                //Создаем папки игры и т.д
                QString pathToLetter = m_dir.path() + '/' + gameName.at(0);
                QDir dir(pathToLetter);
                QString pathToGame = pathToLetter + '/' + gameName + '/';
                dir.mkdir(gameName);
                dir.setPath(pathToGame);
                dir.mkpath("music/covers");
                dir.mkpath("image/covers");
                dir.mkpath("image/screenshots");
                dir.mkdir("video");
                dir.mkdir("mods");

                //Добавляем в БД
                QString strInsert("INSERT INTO Games(Title, Path) VALUES ('" + gameName + "', '" + path + "');");
                QSqlQuery queryInsert;
                queryInsert.exec(strInsert);
            }
            else //Если нет
            {
                qDebug() << "Letter not found";

                //Добавляем строку
                int newRowNumber = m_model->getRoot()->childCount();
                m_proxy->insertRow(newRowNumber);

                //Получаем индекс добавленной строки
                QModelIndex newRowIdx = m_model->index(newRowNumber, 0);

                //Переименовываем пустую строку
                m_proxy->setData(newRowIdx, gameName.at(0));

                /*Добавляем игру*/
                //Добавляем строку
                m_proxy->insertRow(0, m_proxy->mapFromSource(newRowIdx));

                //Получаем индекс на вставленную строку
                QModelIndex newGameIdx = m_model->index(0, 0, newRowIdx);

                //Устанавливаем данные в этой строке
                m_proxy->setData(newGameIdx, gameName);

                //Создаем папки буквы/игры и т.д
                QString pathToGame = m_dir.path() + '/' + gameName.at(0) + '/' + gameName + '/';
                m_dir.mkpath(pathToGame);
                QDir dir(pathToGame);
                dir.mkpath("music/covers");
                dir.mkpath("image/covers");
                dir.mkpath("image/screenshots");
                dir.mkdir("video");
                dir.mkdir("mods");

                //Добавляем запись в БД
                QString strInsert("INSERT INTO Games(Title, Path) VALUES ('" + gameName + "', '" + path + "');");
                QSqlQuery queryInsert;
                queryInsert.exec(strInsert);
            }
        }
    }
}
/*Drag & Drop*/

/*Show Image*/
void MainWindow::showEvent(QShowEvent *event)
{
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    QMainWindow::showEvent(event);
}
/*Show Image*/

void MainWindow::on_splitterVertical_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_splitterHorizontal_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_splitterHorizontalInfo_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

void MainWindow::on_splitterVerticalInfo_splitterMoved(int pos, int index)
{
    Q_UNUSED(pos);
    Q_UNUSED(index);
    ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
}

/*Slideshow Slots*/
void MainWindow::slotMediaSlideshowStart()
{
    if(m_mediaList.size() > 1)
    {
        ++m_slideMediaNumber;
        m_mediaScene->clear();
        ui->mediaView->viewport()->update();
        QPixmap media(m_strToMedia + '/' + m_mediaList.at(m_slideMediaNumber%m_mediaList.size()));
        ui->mediaView->setSceneRect(0, 0, media.width(), media.height());
        QGraphicsPixmapItem *mediaItem = new QGraphicsPixmapItem(media);
        m_mediaScene->addItem(mediaItem);
        ui->mediaView->fitInView(m_mediaScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}

void MainWindow::slotCoversSlideshowStart()
{
    if(m_coversList.size() > 1)
    {
        ++m_slideCoverNumber;
        m_coverScene->clear();
        ui->coversView->viewport()->update();
        QPixmap media(m_strToCover + '/' + m_coversList.at(m_slideCoverNumber%m_coversList.size()));
        ui->coversView->setSceneRect(0, 0, media.width(), media.height());
        QGraphicsPixmapItem *mediaItem = new QGraphicsPixmapItem(media);
        m_coverScene->addItem(mediaItem);
        ui->coversView->fitInView(m_coverScene->itemsBoundingRect(), Qt::KeepAspectRatio);
    }
}
/*Slideshow Slots*/

/*Menu Actions*/
void MainWindow::on_actionQuit_triggered()
{
    qApp->quit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, tr("About"), tr("GameTree v0.1.0.1 \u00A9 2018-2019 Maxim Zherebkov\n\n\n"
                                                   "Used Resources:\n"
                                                   "Icons:\n"
                                                   "From https://flaticon.com:\n"
                                                   "\tTree, Setting by Freepik\n"
                                                   "\tPlay, Pause, Playlist by Appzgear\n"
                                                   "\tStop by Elegant Themes\n"
                                                   "\tCheck by Maxim Basinski\n"
                                                   "\tPrevious, Next by Alessio Atzeni\n"
                                                   "From https://thenounproject.com:\n"
                                                   "\tExit by JS\n"
                                                   "\tAbout by Deemak Daksina\n"
                                                   "\tHelp by i cons\n"
                                                   "\tGamepad by mikicon\n"
                                                   "\tHome by Smashicons\n"
                                                   "Styles:\n"
                                                   "From https://gitlab.com:\n"
                                                   "\tCoffee by Sergei Galin\n"
                                                   "From https://github.com:\n"
                                                   "\tFlat by chenwen1126"));

}

void MainWindow::on_actionSettings_triggered()
{
    OptionsDialog dialog;

    dialog.setSettings(m_options);

    if(dialog.exec() == QDialog::Accepted)
    {
        m_options = dialog.getSettings();

        //Если включен слайд шоу обложек
        if(m_options.isCoverSlideshowEnabled)
        {
            m_coversSlideshowTimer->start(m_options.coverSlideshowRate * 1000);
        }
        else //Иначе
        {
            m_coversSlideshowTimer->stop();
        }

        //Если включен слайд шоу скринов
        if(m_options.isMediaSlideshowEnabled)
        {
            m_mediaSlideshowTimer->start(m_options.mediaSlideshowRate * 1000);
        }
        else
        {
            m_mediaSlideshowTimer->stop();
        }

        if(m_options.isFullscreen)
        {
            this->setWindowState(Qt::WindowMaximized);

        }
        else
        {
            this->setWindowState(Qt::WindowNoState);
        }
    }
}
void MainWindow::on_actionHelp_triggered()
{
    HelpDialog dialog;
    dialog.exec();
}
void MainWindow::on_actionStart_Game_triggered()
{
    slotAdd();
}
/*Menu Actions*/

/*Tree View Key Event*/
void MainWindow::slotKeyDelete()
{
    if(ui->treeView->currentIndex().isValid())
        slotDelete();
}

void MainWindow::slotKeyEnter()
{
    if(ui->treeView->currentIndex().isValid())
        slotStart();
}
/*Tree View Key Event*/

/*Screenshots*/
bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *msg = static_cast<MSG*>(message);
    if(msg->message == WM_HOTKEY)
    {
        QModelIndex selectedIndex = ui->treeView->selectionModel()->currentIndex(); //mapToSource?
        if(msg->wParam == 0)
        {
            QRect screenGeometry = qApp->primaryScreen()->virtualGeometry();
            QPixmap screenPixmap = qApp->primaryScreen()->grabWindow(qApp->desktop()->winId(), screenGeometry.x(), screenGeometry.y(), screenGeometry.width(), screenGeometry.height());
            QString fileName("screenshot_full_" + QDateTime::currentDateTime().toString("ddMMyy_HHmmss") + ".png");
            if(!selectedIndex.isValid() || !selectedIndex.parent().isValid())
            {
                qDebug() << screenPixmap.save(m_appPath + "/screenshots/" + fileName);
                qDebug() << m_appPath + "/Screenshots/" + fileName;
            }
            else if(!selectedIndex.parent().parent().isValid())
            {
                QString dirPath = m_appPath + "/Games/" + selectedIndex.data().toString().at(0) + '/' + selectedIndex.data().toString() + "/image/screenshots/";
                qDebug() << screenPixmap.save(dirPath + fileName);
            }
            else
            {
                QString dirPath = m_appPath + "/Games/" + selectedIndex.parent().data().toString().at(0) + '/' + selectedIndex.parent().data().toString() + "/mods/" + selectedIndex.data().toString() + "/image/screenshots/";
                qDebug() << screenPixmap.save(dirPath + fileName);
            }
            return true;
        }
        for(int hotKeyNumber = 1; hotKeyNumber < m_screens.size() + 1; ++hotKeyNumber)
        {
            QString str("screen_");
            str.append(QString::number(hotKeyNumber));
            str.append(".png");
            if(msg->wParam == static_cast<uint>(hotKeyNumber))
            {
                QPixmap screen = m_screens.at(hotKeyNumber-1)->grabWindow(0);
                QString fileName("screenshot_" + QString::number(hotKeyNumber) + QDateTime::currentDateTime().toString("ddMMyy_HHmmss") + ".png");
                if(!selectedIndex.isValid() || !selectedIndex.parent().isValid())
                {
                    qDebug() << screen.save(m_appPath + "/Screenshots/" + fileName); //Добавить формат файла
                }
                else if(!selectedIndex.parent().parent().isValid())
                {
                    QString dirPath = m_appPath + "/Games/" + selectedIndex.data().toString().at(0) + '/' + selectedIndex.data().toString() + "/image/screenshots/";
                    qDebug() << screen.save(dirPath + fileName);
                }
                else
                {
                    QString dirPath = m_appPath + "/Games/" + selectedIndex.parent().data().toString().at(0) + '/' + selectedIndex.parent().data().toString() + "/mods/" + selectedIndex.data().toString() + "/image/screenshots/";
                    qDebug() << screen.save(dirPath + fileName);
                }
                return true;
            }
        }
        return true; // или false
    }
    else
    {
        return QMainWindow::nativeEvent(eventType, message, result);
    }
}
/*Screenshots*/
