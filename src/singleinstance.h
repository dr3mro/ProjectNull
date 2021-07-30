///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include "src/datahelper.h"
/*
 * This class is responsible for keeping only one instance of the application running
 * at all time and it will pass the app args to the current instance running and also
 * will start the new video playback
 */

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = nullptr); // ctor
    ~SingleInstance();                                  // dtor
    void listen(QString name);                          // listen on local server
    bool hasPrevious(QString name, QString _url);       // check is a previous is runnining

public slots:
    void onNewConnection();                             // new connection is detected
    void onReadyRead();                                 // if message is ready to parse (URL)

private:
    QLocalSocket* mSocket;                              // Local socket
    QLocalServer mServer;                               // Local server

signals:
    void doAction(const QString & newURL);              // This is triggered if an old instance is detected

};

#endif // SINGLEINSTANCE_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
