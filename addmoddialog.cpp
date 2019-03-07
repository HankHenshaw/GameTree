#include "addmoddialog.h"
#include "ui_addmoddialog.h"

AddModDialog::AddModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddModDialog)
{
    ui->setupUi(this);
    ui->labelName->setText(tr("Mod Name:"));
    ui->labelPath->setText(tr("Path to .exe:"));
    ui->lineEditName->setPlaceholderText(tr("Enter mod name here"));
    ui->lineEditPath->setPlaceholderText(tr("Choose path here"));
    ui->labelGameName->setText(tr("Game Name:"));
    ui->labelGamePath->setText(tr("Path to game .exe:"));
    ui->buttonBox->button(QDialogButtonBox::Ok)->setDisabled(true);

    this->setWindowTitle(tr("Adding Mod"));
}

AddModDialog::~AddModDialog()
{
    delete ui;
}

const ModInfo &AddModDialog::getInfo() const
{
    return m_modinfo;
}

void AddModDialog::setNamePath(const QString &gameName, const QString &pathName)
{
    ui->lineEditGameName->setText(gameName);
    ui->lineEditGamePath->setText(pathName);

    ui->lineEditGameName->setDisabled(true);
    ui->lineEditGamePath->setDisabled(true);
}

void AddModDialog::on_buttonBox_accepted()
{
    m_modinfo.m_name = ui->lineEditName->text();
    m_modinfo.m_path = ui->lineEditPath->text();
}

void AddModDialog::on_lineEditName_textChanged(const QString &arg1)
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

void AddModDialog::on_lineEditPath_textChanged(const QString &arg1)
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
