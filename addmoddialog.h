#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>

struct ModInfo
{
    QString m_name;
    QString m_path;
};

namespace Ui {
class AddModDialog;
}

class AddModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddModDialog(QWidget *parent = nullptr);
    ~AddModDialog();

    const ModInfo& getInfo() const;
    void setNamePath(const QString &gameName, const QString &pathName);
private slots:
    void on_buttonBox_accepted();

    void on_lineEditPath_textChanged(const QString &arg1);

    void on_lineEditName_textChanged(const QString &arg1);

private:
    Ui::AddModDialog *ui;
    ModInfo m_modinfo;
};

#endif // ADDMODDIALOG_H
