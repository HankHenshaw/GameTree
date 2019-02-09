#include "argsdialog.h"
#include "ui_argsdialog.h"
//TODO: Подсказку, что в случае если аргументов нет, то игра запустится в обычном режиме
//WARNING: Могут быть проблемы с аргументами в которых есть пробел
ArgsDialog::ArgsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ArgsDialog)
{
    ui->setupUi(this);
    ui->labelArgs->setText(tr("Arguments"));
    ui->lineEditArgs->setPlaceholderText(tr("Enter arguments here"));
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
