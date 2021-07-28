// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "singleinstance.h"

SingleInstance::SingleInstance(QObject *parent):QObject(parent)
{
    Q_UNUSED(parent)
    connect(&mServer, SIGNAL(newConnection()),this,SLOT(newConnection()));
}

SingleInstance::~SingleInstance()
{
    mServer.close();
}

void SingleInstance::listen(QString name)
{
    mServer.removeServer(name);
    if (!mServer.isListening())
        mServer.listen(name);
    if ( !mServer.isListening())
        qDebug() << mServer.errorString();
}

bool SingleInstance::hasPrevious(QString name, QString arg)
{
    QLocalSocket socket;
    socket.connectToServer(name, QLocalSocket::ReadWrite);
    if(socket.waitForConnected())
    {
        QByteArray buffer = arg.toUtf8();
        socket.write(buffer);
        socket.waitForBytesWritten();
        return true;
    }
    return false;
}

void SingleInstance::newConnection()
{
   emit newInstance();
   mSocket = mServer.nextPendingConnection();
   connect(mSocket,SIGNAL(readyRead()),this,SLOT(readyRead()));
}

void SingleInstance::readyRead()
{
    QString url = mSocket->readAll();
    emit doAction(url);
    mSocket->deleteLater();
}
