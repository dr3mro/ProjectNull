#include "videocapturedetector.h"


VideoCaptureDetector::VideoCaptureDetector(QObject *parent) : QObject(parent)
{
    connect(&checkTimer,&QTimer::timeout,this,&VideoCaptureDetector::checkForScreenCapptureProcesses);
    checkTimer.start(2000);
    checkForScreenCapptureProcesses();
}
QStringList VideoCaptureDetector::getRunningProcessList()
{
    QStringList processList;
    HANDLE hndl = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS | TH32CS_SNAPMODULE, 0);
    if(hndl)
    {
        PROCESSENTRY32  process = { sizeof(PROCESSENTRY32) };
        Process32First(hndl, &process);
        do
        {
            processList <<  QString::fromStdWString(process.szExeFile);
        } while(Process32Next(hndl, &process));

        CloseHandle(hndl);
    }
    return processList;
}

QStringList VideoCaptureDetector::getScreenCaptureList()
{
    QStringList blocklist;

    QString val;
    QFile file;
    file.setFileName("./blacklist.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();


    QJsonDocument doc = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject jObject = doc.object();
    QJsonArray jArray = jObject.value("ScreenCaptureApps").toArray();
    for(auto app:jArray)
        blocklist.append(app.toString());
    return blocklist;
}

void VideoCaptureDetector::checkForScreenCapptureProcesses()
{
    QStringList  currentRunningProcessList = getRunningProcessList();
    //qDebug() << currentRunningProcessList;
    QStringList knownScreenCaptureSoftware = getScreenCaptureList();

    for(auto app:currentRunningProcessList){
        if (knownScreenCaptureSoftware.contains(app)){
            emit runningScreenCapture(false,app);
            return;
        }
    }
    getScreenCaptureList();
    emit runningScreenCapture(true,"");

}
