///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#ifndef LOGGER_H
#define LOGGER_H
#include <QGuiApplication>
#include <QFile>
#include <QTextStream>
#include <QMessageLogContext>
#include <QDateTime>
#include "src/mdebug.h"

void myMessageLogger(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QString txt;
    QString dateTime = QDateTime::currentDateTime().toString("yyyy-MM-yy hh:mm AP");
    switch (type) {

    case QtDebugMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtWarningMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtCriticalMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    case QtFatalMsg:
        txt = QString("Debug:[%1] %2 (%3:%4) %5 ").arg(dateTime).arg(msg).arg(context.file).arg(context.line).arg(context.function);
        break;
    default:
        break;

    }
    QFile outFile(LOGFILE);
    outFile.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream ts(&outFile);
    ts << txt << '\n';
    outFile.close();
}
#endif // LOGGER_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
