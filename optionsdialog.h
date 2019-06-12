#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QStyleFactory>
#include <QDirIterator>
#include <QDebug>
#include <QFileInfo>
#include <QFileDialog>
#include <QStyle>
#include <QThread>

namespace Ui {
class OptionsDialog;
}

struct Setting
{
    bool isCoverSlideshowEnabled;
    bool isMediaSlideshowEnabled;
    bool isFullscreen;
    bool isFpsSetEnabled;
    bool isFpsLockEnabled;
    bool isCustomQualityEnabled;
    int coverSlideshowRate;
    int mediaSlideshowRate;
    int styleNumber;
    int threadCount;
    int codecIndex;
    int fpsSet;
    int fpsLock;
    int frameQuality;
    QString language;
    QString codec;
};

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();
    const Setting &getSettings() const;
    void setSettings(const Setting &settings);

private slots:
    void on_comboStylesBox_currentIndexChanged(int index);
    void on_buttonBox_accepted();
    void on_checkBoxQuality_stateChanged(int arg1);
    void on_checkBoxSetFps_stateChanged(int arg1);
    void on_checkBoxLockFps_stateChanged(int arg1);

private:
    Ui::OptionsDialog *ui;
    QStringList stylesPath;
    Setting m_setting;

    QStringList m_codecList;
};

#endif // OPTIONSDIALOG_H
