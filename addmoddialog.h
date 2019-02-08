#ifndef ADDMODDIALOG_H
#define ADDMODDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
//TODO?: методы для получения данных из структуры
//TODO: Подсказку в которой будет сказано, что некоторые игры(моды) запускаются через лаунчеры
//TODO: Если введено имя и потом добалвяется путь, сделать что бы кнопка ок становилась активной
//TODO: Сделать невозможным в качестве имени установить пробел

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

private:
    Ui::AddModDialog *ui;
    ModInfo m_modinfo; // ptr?
};

#endif // ADDMODDIALOG_H
