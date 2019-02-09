#ifndef ARGSDIALOG_H
#define ARGSDIALOG_H

#include <QDialog>

namespace Ui {
class ArgsDialog;
}

class ArgsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ArgsDialog(QWidget *parent = nullptr);
    ~ArgsDialog();

    const QStringList& getList() const; // const QStringList& ???
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ArgsDialog *ui;
    QStringList m_argList;
};

#endif // ARGSDIALOG_H
