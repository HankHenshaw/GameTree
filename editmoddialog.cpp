#include "editmoddialog.h"
#include "ui_editmoddialog.h"

EditModDialog::EditModDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditModDialog)
{
    ui->setupUi(this);
    ui->labelName->setText(tr("Mod Name:"));
    ui->labelPath->setText(tr("Path to .exe:"));
    ui->lineEditName->setPlaceholderText(tr("Enter mod name here"));
    ui->lineEditPath->setPlaceholderText(tr("Choose path here"));
}

EditModDialog::~EditModDialog()
{
    delete ui;
}

const ModInfos &EditModDialog::getInfo() const
{
    return m_modinfo;
}

void EditModDialog::setNamePath(const QString &gameName, const QString &pathName)
{
    ui->lineEditName->setText(gameName);
    ui->lineEditPath->setText(pathName);
}

void EditModDialog::on_buttonBox_accepted()
{
    m_modinfo.m_name = ui->lineEditName->text();
    m_modinfo.m_path = ui->lineEditPath->text();
}

void EditModDialog::on_lineEditPath_textChanged(const QString &arg1)
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

void EditModDialog::on_lineEditName_textChanged(const QString &arg1)
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
}
