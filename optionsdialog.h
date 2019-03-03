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
};

class OptionsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OptionsDialog(QWidget *parent = nullptr);
    ~OptionsDialog();

private slots:
    void on_comboStylesBox_currentIndexChanged(int index);

private:
    Ui::OptionsDialog *ui;
    QStringList stylesPath;
};

#endif // OPTIONSDIALOG_H
