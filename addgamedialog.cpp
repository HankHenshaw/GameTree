#include "addgamedialog.h"
#include "ui_addgamedialog.h"
#include <QDebug> // Потом убрать?

AddGameDialog::AddGameDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddGameDialog)
{
    ui->setupUi(this);
    ui->labelName->setText(tr("Game name:"));
    ui->labelPath->setText(tr("Path to .exe"));
    ui->lineEditName->setPlaceholderText(tr("Enter game name here"));
    ui->lineEditPath->setPlaceholderText(tr("Choose path here"));

    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);
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
    m_gameinfo.m_name = ui->lineEditName->text();
    m_gameinfo.m_path = ui->lineEditPath->text();
}

void AddGameDialog::on_lineEditName_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1); //Что за arg1??
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
    Q_UNUSED(arg1);//Что за arg1??
    if(!ui->lineEditPath->text().isEmpty())
    {
        if(!ui->lineEditName->text().isEmpty())
        {
//            if(!ui->buttonBox->button(QDialogButtonBox::Ok)->isEnabled())
            if(ui->lineEditName->text().startsWith(" "))
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
            else
                ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
        }
    }
}