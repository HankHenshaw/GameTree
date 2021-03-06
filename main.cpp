#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>
#include <QStyleFactory>

void messageToFile(QtMsgType type, const QMessageLogContext &context, const QString& msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setWindowIcon(QIcon(":/menu/icons/tree_64.png"));
    qInstallMessageHandler(messageToFile);
    qInfo() << QApplication::applicationName();
    MainWindow w;
    w.show();

    return a.exec();
}

void messageToFile(QtMsgType type, const QMessageLogContext &context, const QString& msg)
{
    QString path = MainWindow::appPath() + '\\';
    QFile file(path + "log.log");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
        return;

    static int count = 0;
    if(count == 0)
    {
        file.resize(0);
    }
    ++count;

    QString strDate = QDateTime::currentDateTime().toString("dd.MM.yy-hh:mm");

    QTextStream stream(&file);
    switch (type)
    {
    case QtInfoMsg: // qInfo()
        stream << strDate << " Info: " << msg << ", " << context.file << endl;
        break;
    case QtDebugMsg: // qDebug()
        stream << strDate << " Debug: " << msg << ", " << context.file << endl;
        break;
    case QtWarningMsg: // qWarning()
        stream << strDate << " Warning: " << msg << ", " << context.file << endl;
        break;
    case QtCriticalMsg: // qCritical()
        stream << strDate << " Critical: " << msg << ", " << context.file << endl;
        break;
    case QtFatalMsg: // qFatal()
        stream << strDate << " Fatal: " << msg << ", " << context.file << endl;
        abort();
    }
}
