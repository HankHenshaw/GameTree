#ifndef EDITMODDIALOG_H
#define EDITMODDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QMessageBox>

struct ModInfos
{
    QString m_name;
    QString m_path;
};

namespace Ui {
class EditModDialog;
}

class EditModDialog : public QDialog
{
    Q_OBJECT

public:
    explicit EditModDialog(QWidget *parent = nullptr);
    ~EditModDialog();

    const ModInfos& getInfo() const;
    void setNamePath(const QString &gameName, const QString &pathName);
private slots:
    void on_buttonBox_accepted();
    void on_lineEditPath_textChanged(const QString &arg1);
    void on_lineEditName_textChanged(const QString &arg1);

private:
    Ui::EditModDialog *ui;
    ModInfos m_modinfo;
};

#endif // EDITMODDIALOG_H
