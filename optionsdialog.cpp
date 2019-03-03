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

    ui->comboStylesBox->addItems(styles);
    ui->comboStylesBox->setCurrentIndex(2);

}

OptionsDialog::~OptionsDialog()
{
    delete ui;
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
