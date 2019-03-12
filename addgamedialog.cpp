#include "addgamedialog.h"
#include "ui_addgamedialog.h"

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);
    ui->labelName->setText(tr("Game name:"));
    ui->labelPath->setText(tr("Path to .exe:"));
    ui->lineEditName->setPlaceholderText(tr("Enter game name here"));
    ui->lineEditPath->setPlaceholderText(tr("Choose path here"));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

    this->setWindowTitle(tr("Editing Game"));
}

AddGameDialog::~AddGameDialog()
{
    delete ui;
}

const GameInfo &AddGameDialog::getInfo() const
{
    return m_gameinfo;
}

void AddGameDialog::setNamePath(const QString &gameName, const QString &pathName) const
{
    ui->lineEditName->setText(gameName);
    ui->lineEditPath->setText(pathName);
}

void AddGameDialog::on_buttonBox_accepted()
{
    QString name = ui->lineEditName->text();
    name.replace(0, 1, name.at(0).toUpper());
//    m_gameinfo.m_name = ui->lineEditName->text();
    m_gameinfo.m_name = name;
    m_gameinfo.m_path = ui->lineEditPath->text();
}

void AddGameDialog::on_lineEditName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(ui->lineEditName->text().isEmpty())
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    else
    {
        if(ui->lineEditPath->text().isEmpty())
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
        else if(ui->lineEditName->text().startsWith(" "))
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
        else
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(false);
    }
}

void AddGameDialog::on_lineEditPath_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1);
    if(!ui->lineEditPath->text().isEmpty())
    {
        if(!ui->lineEditName->text().isEmpty())
        {
            if(ui->lineEditName->text().startsWith(" "))
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            else
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
        else
        {
            ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
        }
    }
    else
    {
        ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
    }
}
