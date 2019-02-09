#include "mainwindow.h"
#include "ui_mainwindow.h"

///WARNING: Опасные моменты кода, которые могут вызвать проблемы
///TEST: Тестовые эл-ты
///TODO: То что надо сделать

//TODO: Add Author of Icons from www.flaticon.com
//TODO: RMB Progressbar
//TODO: Playerlist widget
//TODO: Mouse Wheel at volumeSlider
//TODO: Settings
//TODO: Fix all warnings
//TODO: Replace menu icons to ~16x16 size
//TODO: Minimize to tray
//TODO: Проверить почему у позиций не должно быть указано родителя(т.е. корня)
//TODO: Обнулять лог при каждом запуске??
//TODO: Экранирование всех апострофов в запросах к БД
//TODO: Запуск мода и запуск мода с параметрами
//TODO: Абсолютный путь до лога!!!!
//TODO: Добавить горизонтальный слайдер в ТриВью если название не влезает в отведенную область

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qInfo() << "Audioplayer initialization";
    audioPlayerInit();

    qInfo() << "Get Data From DB";
    getDataFromDB();

    //Основная модель с данными
    m_model = new TreeModel(m_mapOfLetters, m_mapOfGames);

    ui->treeView->setModel(m_model);

    //Устанавливаем политику кастомного меню
    ui->treeView->setContextMenuPolicy(Qt::CustomContextMenu);

    // Разукрашивает каждую нечетную строку в серый, чеиные остаются белыми
    ui->treeView->setAlternatingRowColors(true);
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

void MainWindow::on_actionRussian_triggered()
{
    changeLanguage("ru");
}

void MainWindow::on_actionEnglish_triggered()
{
    changeLanguage("en");
}
/*Translator*/

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
    QAction *addGame = new QAction(tr("Add game"));

    //Создаем действие для добавления мода
    QAction *addMod = new QAction(tr("Add mod"));

    //Создаем действие для запуска игры
    QAction *startGame = new QAction(tr("Start game"));

    //Создаем действие для запуска игры с параметрами
    QAction *startGameWithParameters = new QAction(tr("Start game with parameters..."));

    //Создаем действие для запуска игры с параметрами
    QAction *startMod = new QAction(tr("Start game"));

    //Создаем действие для запуска игры с параметрами
    QAction *startModWithParameters = new QAction(tr("Start game with parameters..."));

    //Создаем действие для удаления игры
    QAction *deleteGame = new QAction(tr("Delete game/mod"));

    //Создаем действие для редактирования информации об игре
    QAction *editGame = new QAction(tr("Edit information about game"));

    //Создаем действие для редактирования информации о моде
    QAction *editMod = new QAction(tr("Edit information about mod"));

    //Заполняем оба меню действиями
    invalidIndexMenu.addAction(addGame);

    modMenu.addAction(startMod);
    modMenu.addAction(startModWithParameters);
    modMenu.addSeparator();
    modMenu.addAction(addGame);
    modMenu.addAction(addMod);
    modMenu.addAction(editGame);
    modMenu.addAction(editMod);
    modMenu.addAction(deleteGame);

    gameMenu.addAction(startGame);
    gameMenu.addAction(startGameWithParameters);
    gameMenu.addSeparator();
    gameMenu.addAction(addGame);
    gameMenu.addAction(addMod);
    gameMenu.addAction(editGame);
    gameMenu.addAction(deleteGame);

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

    //Исп. перемн. класса, а не локальную, для того что бы запоминать послд. выделен. позицию и исп. эту перемен. в слотах QAction
    m_selectedIndex = ui->treeView->indexAt(pos);

    if(!m_selectedIndex.isValid())
    {
        invalidIndexMenu.exec(globalPos);
    }
    else
    {
        //if(m_selectedIndex.data().toString().size() == 1)
        if(!m_selectedIndex.parent().isValid())
        {
            //Меню для букв
            letterMenu.exec(globalPos);
        }
        //else if(m_selectedIndex.parent().data().toString().size() == 1)
        else if(!m_selectedIndex.parent().parent().isValid())
        {
            //Меню для игр
            gameMenu.exec(globalPos);
        }
        //else if(m_selectedIndex.parent().parent().data().toString().size() == 1)
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
    qDebug() << "Delete item" << m_selectedIndex.data().toString();
}

void MainWindow::slotEdit()
{
    qDebug() << "Edit game" << m_selectedIndex.data().toString();
}

void MainWindow::slotEditMod()
{
    qDebug() << "Edit mod" << m_selectedIndex.data().toString() << "of" << m_selectedIndex.parent().data().toString();
}

void MainWindow::slotStart()
{
    //WARNING: Проблема такого запуска игр, в том, что будет если ехе находится на большей вложенности

    //Получаем имя игры
    QString gameName = m_selectedIndex.data().toString();

    //Получаем путь до .ехе из БД
    QString strPath = ("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
    QSqlQuery queryPath;
    queryPath.exec(strPath);
    queryPath.next();
    QString path = queryPath.value(0).toString();

    qDebug() << "Start Game:" << gameName << "From:" << path;

    //Устанавливаем путь до папки где расположен ехе
    QDir dir(path);
    dir.cdUp();
    QDir::setCurrent(dir.path());

    //Получаем из пути имя ехе файла
    QString exeNameReverse;
    QString::reverse_iterator beginIterator = path.rbegin();
    QString::reverse_iterator endIterator = path.rend();

    while(beginIterator != endIterator)
    {
        if(*beginIterator == '\\')
            break;
        exeNameReverse.append(*beginIterator);
        ++beginIterator;
    }

    //Экранируем имя
    QString exeName('\"');

    beginIterator = exeNameReverse.rbegin();
    endIterator = exeNameReverse.rend();

    while(beginIterator != endIterator)
    {
        exeName.append(*beginIterator);
        ++beginIterator;
    }

    //Экранируем имя
    exeName.append('\"');

    QProcess::startDetached(exeName);
}

void MainWindow::slotStartWithParameters()
{
    qDebug() << "Start with paremeters" << m_selectedIndex.data().toString();

    ArgsDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        /*Для печати в дебаг*/
        //        QStringList tmp = dialog.getList();
        //        auto itb = tmp.begin();
        //        auto ite = tmp.end();
        //        while(itb != ite)
        //        {
        //            qDebug() << *itb;
        //            ++itb;
        //        }
        /*Для печати в дебаг*/

        //Получаем имя игры
        QString gameName = m_selectedIndex.data().toString();

        //Получаем путь до ехе из БД
        QString strPath = ("SELECT Path FROM Games WHERE Title = '" + gameName + "'");
        QSqlQuery queryPath;
        queryPath.exec(strPath);
        queryPath.next();
        QString path = queryPath.value(0).toString();

        //Устанавливаем путь до папки где расположен ехе
        QDir dir(path);
        dir.cdUp();

        QDir::setCurrent(dir.path());

        //Получаем из пути имя ехе файла
        QString exeNameReverse;
        QString::reverse_iterator beginIterator = path.rbegin();
        QString::reverse_iterator endIterator = path.rend();

        while(beginIterator != endIterator)
        {
            if(*beginIterator == '\\')
                break;
            exeNameReverse.append(*beginIterator);
            ++beginIterator;
        }

        //Экранируем имя
        QString exeName('\"');

        beginIterator = exeNameReverse.rbegin();
        endIterator = exeNameReverse.rend();

        while(beginIterator != endIterator)
        {
            exeName.append(*beginIterator);
            ++beginIterator;
        }

        //Экранируем имя
        exeName.append('\"');

        QProcess::startDetached(exeName, dialog.getList());
    }
}

void MainWindow::slotStartMod()
{
    //WARNING: Проблема такого запуска мода, в том, что будет если ехе находится на большей вложенности

    //Получаем имя мода
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

    //Получаем из пути имя ехе файла
    QString exeNameReverse;
    QString::reverse_iterator beginIterator = path.rbegin();
    QString::reverse_iterator endIterator = path.rend();

    while(beginIterator != endIterator)
    {
        if(*beginIterator == '\\')
            break;
        exeNameReverse.append(*beginIterator);
        ++beginIterator;
    }

    //Экранируем имя
    QString exeName('\"');

    beginIterator = exeNameReverse.rbegin();
    endIterator = exeNameReverse.rend();

    while(beginIterator != endIterator)
    {
        exeName.append(*beginIterator);
        ++beginIterator;
    }

    //Экранируем имя
    exeName.append('\"');

    QProcess::startDetached(exeName);
}

void MainWindow::slotStartModWithParameters()
{
    qDebug() << "Start Mod with parameters:";

    ArgsDialog dialog;

    if(dialog.exec() == QDialog::Accepted)
    {
        /*Для печати в дебаг*/
        //        QStringList tmp = dialog.getList();
        //        auto itb = tmp.begin();
        //        auto ite = tmp.end();
        //        while(itb != ite)
        //        {
        //            qDebug() << *itb;
        //            ++itb;
        //        }
        /*Для печати в дебаг*/

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

        //Получаем из пути имя ехе файла
        QString exeNameReverse;
        QString::reverse_iterator beginIterator = path.rbegin();
        QString::reverse_iterator endIterator = path.rend();

        while(beginIterator != endIterator)
        {
            if(*beginIterator == '\\')
                break;
            exeNameReverse.append(*beginIterator);
            ++beginIterator;
        }

        //Экранируем имя
        QString exeName('\"');

        beginIterator = exeNameReverse.rbegin();
        endIterator = exeNameReverse.rend();

        while(beginIterator != endIterator)
        {
            exeName.append(*beginIterator);
            ++beginIterator;
        }

        //Экранируем имя
        exeName.append('\"');

        QProcess::startDetached(exeName, dialog.getList());
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
            m_model->insertRow(newRowNumber, parent);

            //Получаем индекс новой строки
            QModelIndex newIdx = m_model->index(newRowNumber, 0, parent);

            //Устанавливаем данные в новой строке
            m_model->setData(newIdx, gameName);

            //TODO: Добавляем в БД
        }
        else //Если нет
        {
            qDebug() << "Letter not found";

            //Добавляем строку
            int newRowNumber = m_model->getRoot()->childCount();
            m_model->insertRow(newRowNumber);

            //Получаем индекс добавленной строки
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0);

            //Переименовываем пустую строку
            m_model->setData(newRowIdx, gameName.at(0));

            /*Добавляем игру*/
            //Добавляем строку
            m_model->insertRow(0, newRowIdx);

            //Получаем индекс на вставленную строку
            QModelIndex newGameIdx = m_model->index(0, 0, newRowIdx);

            //Устанавливаем данные в этой строке
            m_model->setData(newGameIdx, gameName);

            //TODO: Добавляем запись в БД
        }
    }
}

void MainWindow::slotAddMod()
{
    qDebug() << "Add mod";

    //Создаем диалог
    AddModDialog dialog;

    //Если выбранный эл-т игра
    if(!m_selectedIndex.parent().parent().isValid()) //WARNING: Тут могут быть проблемы
    {
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = m_selectedIndex.data().toString();
        QString strGamePath("SELECT Path FROM Games WHERE Title = '" + gameName + "'"); //TODO: Экранировать апостроф
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
            int newRowNumber = m_model->getItem(m_selectedIndex)->childCount();

            //Добавляем строку
            m_model->insertRow(newRowNumber, m_selectedIndex);

            //Получаем индекс на новую строку
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0, m_selectedIndex);

            //Устанавливаем данные в этой строке
            m_model->setData(newRowIdx, modName);

            //Добавляем запись в БД
        }
    }
    else //WARNING: Тут могут быть проблемы
    {
        //Добавляем в диалог имя игры и путь до .ехе
        QString gameName = m_selectedIndex.parent().data().toString();
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
            int newRowNumber = m_model->getItem(m_selectedIndex.parent())->childCount();

            //Добавляем строку
            m_model->insertRow(newRowNumber, m_selectedIndex.parent());

            //Получаем индекс на новую строку
            QModelIndex newRowIdx = m_model->index(newRowNumber, 0, m_selectedIndex.parent());

            //Устанавливаем название
            m_model->setData(newRowIdx, modName);

            //Добавляем мод в БД
        }
    }
}
