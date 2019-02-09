#ifndef ADDGAMEDIALOG_H
#define ADDGAMEDIALOG_H

#include <QDialog>
#include <QMessageBox>
#include <QPushButton>
//TODO?: методы для получения данных из структуры
//TODO: Подсказку в которой будет сказано, что некоторые игры(моды) запускаются через лаунчеры
//TODO: Если введено имя и потом добалвяется путь, сделать что бы кнопка ок становилась активной
//TODO: Сделать невозможным в качестве имени установить пробел

struct GameInfo
{
    QString m_name;
    QString m_path;
};

namespace Ui {
class AddGameDialog;
}

class AddGameDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddGameDialog(QWidget *parent = nullptr);
    ~AddGameDialog();

    const GameInfo& getInfo() const;
    void setNamePath(const QString &gameName, const QString &pathName) const;
private slots:
    void on_buttonBox_accepted();

    void on_lineEditName_textChanged(const QString &arg1);
    void on_lineEditPath_textChanged(const QString &arg1);

private:
    Ui::AddGameDialog *ui;
    GameInfo m_gameinfo; // ptr?
};

#endif // ADDGAMEDIALOG_H
