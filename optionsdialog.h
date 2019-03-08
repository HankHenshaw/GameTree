#ifndef OPTIONSDIALOG_H
#define OPTIONSDIALOG_H

#include <QDialog>
#include <QStyleFactory>
#include <QDirIterator>
#include <QDebug>
#include <QFileInfo>
#include <QStyle>

namespace Ui {
class OptionsDialog;
}

struct Setting
{
    bool isCoverSlideshowEnabled;
    bool isMediaSlideshowEnabled;
    bool isFullscreen;
    int coverSlideshowRate;
    int mediaSlideshowRate;
    int styleNumber;
    QString language;
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

private:
    Ui::OptionsDialog *ui;
    QStringList stylesPath;
    Setting m_setting;
};

#endif // OPTIONSDIALOG_H
