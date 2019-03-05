#include "optionsdialog.h"
#include "ui_optionsdialog.h"

OptionsDialog::OptionsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OptionsDialog)
{
    ui->setupUi(this);
    QStringList styles;
    styles.append(QStyleFactory::keys());

    QDirIterator it(":/styles", QDirIterator::Subdirectories);
    while (it.hasNext()) {
        it.next();
        styles.append(it.fileInfo().baseName());
        stylesPath.append(it.filePath());
    }

    this->setWindowTitle(tr("Settings"));

    ui->comboStylesBox->addItems(styles);
    ui->comboStylesBox->setCurrentIndex(2);

}

OptionsDialog::~OptionsDialog()
{
    delete ui;
}

const Setting &OptionsDialog::getSettings() const
{
    return m_setting;
}

void OptionsDialog::setSettings(const Setting &settings)
{
    m_setting = settings;
    ui->checkBoxCoverSH->setChecked(m_setting.isCoverSlideshowEnabled);
    ui->checkBoxMediaSH->setChecked(m_setting.isMediaSlideshowEnabled);
    ui->checkBoxFullscreen->setChecked(m_setting.isFullscreen);
    ui->spinBoxMediaSH->setValue(m_setting.mediaSlideshowRate);
    ui->spinBoxCoversSH->setValue(m_setting.coverSlideshowRate);
    ui->comboStylesBox->setCurrentIndex(m_setting.styleNumber);
}

void OptionsDialog::on_comboStylesBox_currentIndexChanged(int index)
{
    qApp->setStyleSheet(styleSheet());
    QApplication::setStyle(QStyleFactory::create(ui->comboStylesBox->itemText(2)));
    if(index < 4)
    {
        QApplication::setStyle(QStyleFactory::create(ui->comboStylesBox->itemText(index)));
    }
    else
    {
        QFile file(stylesPath.at(index - 4));
        file.open(QFile::ReadOnly);
        QString str = QLatin1String(file.readAll());
        qApp->setStyleSheet(str);
    }
}

void OptionsDialog::on_buttonBox_accepted()
{
    m_setting.isFullscreen = ui->checkBoxFullscreen->isChecked();
    m_setting.isCoverSlideshowEnabled = ui->checkBoxCoverSH->isChecked();
    m_setting.isMediaSlideshowEnabled = ui->checkBoxMediaSH->isChecked();
    m_setting.styleNumber = ui->comboStylesBox->currentIndex();
    m_setting.mediaSlideshowRate = ui->spinBoxMediaSH->value();
    m_setting.coverSlideshowRate = ui->spinBoxCoversSH->value();
}
