#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDateTime>
#include <QTextStream>
#include <QDebug>

void messageToFile(QtMsgType type, const QMessageLogContext &context, const QString& msg);

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    QApplication::setApplicationName("GameTree");
    {
//#ifndef QT_DEBUG // Для записи в файл только во время отладки
//    qInstallMessageHandler(messageToFile); // Чтобы вернуть старый хэндлер qInstallMessageHandler()
//#endif
    qInstallMessageHandler(messageToFile); // Чтобы вернуть старый хэндлер qInstallMessageHandler()
    }
    qInfo() << QApplication::applicationName();
    return a.exec();
}

void messageToFile(QtMsgType type, const QMessageLogContext &context, const QString& msg)
{
    QFile file("log.log");
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) // Убрать Append?
        return;

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
