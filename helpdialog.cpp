#include "helpdialog.h"
#include "ui_helpdialog.h"

HelpDialog::HelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::HelpDialog)
{
    ui->setupUi(this);
    ui->textBrowser->setSource(QUrl::fromLocalFile("://help/home.html"));
    this->setWindowTitle(tr("Help"));
}

HelpDialog::~HelpDialog()
{
    delete ui;
}

void HelpDialog::on_pushHomeButton_clicked()
{
    ui->textBrowser->setSource(QUrl::fromLocalFile("://help/home.html"));
}
