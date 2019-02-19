#ifndef PLAYLISTFORM_H
#define PLAYLISTFORM_H

#include <QWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileInfo>

namespace Ui {
class PlaylistForm;
}

class PlaylistForm : public QWidget
{
    Q_OBJECT

public:
    explicit PlaylistForm(QWidget *parent = nullptr);
    ~PlaylistForm();

    QMediaPlayer *m_mp;
    void playlistClicked(QMediaPlayer *mp);
private:
    Ui::PlaylistForm *ui;  
private slots:
    void slotDoubleClicked();
};

#endif // PLAYLISTFORM_H
