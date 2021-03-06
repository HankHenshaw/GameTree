#include "argsdialog.h"
#include "ui_argsdialog.h"
//WARNING: Могут быть проблемы с аргументами в которых есть пробел

ArgsDialog::ArgsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArgsDialog)
{
    ui->setupUi(this);
    ui->labelArgs->setText(tr("Arguments:"));
    ui->lineEditArgs->setPlaceholderText(tr("Enter arguments here"));

    this->setWindowTitle(tr("Start With Arguments"));
}

ArgsDialog::~ArgsDialog()
{
    delete ui;
}

const QStringList &ArgsDialog::getList() const
{
    return m_argList;
}

void ArgsDialog::on_buttonBox_accepted()
{
    QString strArgs = ui->lineEditArgs->text();
    QString tmpStr;

    for(int i = 0; i < strArgs.size(); ++i)
    {
        if(strArgs.at(i) == ' ')
        {
            m_argList << tmpStr;
            tmpStr.clear();
            continue;
        }

        tmpStr.append(strArgs.at(i));
    }

    m_argList << tmpStr;
}
