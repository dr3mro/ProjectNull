#ifndef VIDEOCAPTUREDETECTOR_H
#define VIDEOCAPTUREDETECTOR_H

#include <QObject>
#include <QTimer>
#include <QDebug>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
// windows

#include <Windows.h>
#include <stdio.h>
#include <psapi.h>
#include <tlhelp32.h>

//windows

class VideoCaptureDetector : public QObject
{
    Q_OBJECT
public:
    explicit VideoCaptureDetector(QObject *parent = nullptr);

signals:
    Q_SIGNAL void runningScreenCapture(bool playState, QString name);
private:
    QStringList getRunningProcessList();
    QTimer checkTimer;
    QStringList getScreenCaptureList();
private slots:
    void checkForScreenCapptureProcesses();


};

#endif // VIDEOCAPTUREDETECTOR_H
