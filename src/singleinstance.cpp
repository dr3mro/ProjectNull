///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#include "singleinstance.h"

SingleInstance::SingleInstance(QObject *parent):QObject(parent)
{
    // connect to onNewConnection if a new instance is trying to access local server
    connect(&mServer,&QLocalServer::newConnection,this,&SingleInstance::onNewConnection);
}

SingleInstance::~SingleInstance()
{
    // close the local server
    mServer.close();
}

void SingleInstance::listen(QString name)
{
    // first we remove server if exists ( acutually it will never found any ) but just in case
    mServer.removeServer(name);

    if (!mServer.isListening())                                             // if not listening
        mServer.listen(name);                                               // just listen

    if (!mServer.isListening())                                             // if still not listening
        qDebug() << mServer.errorString();                                  // bam error message
}

// This function is to be called from main.cpp and it true the we exit the app
bool SingleInstance::hasPrevious(QString name, QString arg)
{
    // create a socket
    QLocalSocket socket;

    // connect socket to server
    socket.connectToServer(name, QLocalSocket::ReadWrite);

    // if connected ?
    if(socket.waitForConnected())
    {
        // crate a byte array of args and write them to the socket
        QByteArray buffer = arg.toUtf8();
        socket.write(buffer);
        socket.waitForBytesWritten();
        return true;
    }

    // if reach here that means no previous servers is running so return false
    return false;
}

void SingleInstance::onNewConnection()
{
    // store the current socket to access later
    mSocket = mServer.nextPendingConnection();
    // connect the socket readReady signal to onReadReady
    connect(mSocket,&QLocalSocket::readyRead,this,&SingleInstance::onReadyRead);
}

void SingleInstance::onReadyRead()
{
    // Read the message as a URL
    QString url = mSocket->readAll();
    // send the message inside the doAction Signal to the QML slot
    emit doAction(url);
    // delete the socket so prevent memory leaks
    mSocket->deleteLater();
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
