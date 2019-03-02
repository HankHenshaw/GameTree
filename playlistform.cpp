#include "playlistform.h"
#include "ui_playlistform.h"
//TODO: Delete Item
//TODO: DropItem
//TODO: Get MetaData
//TODO: TableWidget/View

PlaylistForm::PlaylistForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PlaylistForm)
{
    ui->setupUi(this);
    connect(ui->listWidget, &QListWidget::doubleClicked, this, &PlaylistForm::slotDoubleClicked);
}

PlaylistForm::~PlaylistForm()
{
    delete ui;
}

void PlaylistForm::playlistClicked(QMediaPlayer *mp)
{
    QMediaPlaylist *list = mp->playlist();
    int listCount = list->mediaCount();

    if(ui->listWidget->count() < listCount) //TODO: Костыль, надо подумать как переделать
    {
        ui->listWidget->clear();
        for(int i = 0; i < listCount; ++i)
        {
            QFileInfo info(list->media(i).resources().first().url().path());
            ui->listWidget->addItem(info.fileName());
        }
    }

    m_mp = mp;
}

void PlaylistForm::slotDoubleClicked()
{
    int itemRow = ui->listWidget->currentRow();
    m_mp->playlist()->setCurrentIndex(itemRow);
    emit signalPlay();
}
