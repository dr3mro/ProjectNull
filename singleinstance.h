// This is an open source non-commercial project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#ifndef SINGLEINSTANCE_H
#define SINGLEINSTANCE_H

#include <QObject>
#include <QLocalServer>
#include <QLocalSocket>
#include "datahelper.h"

class SingleInstance : public QObject
{
    Q_OBJECT
public:
    explicit SingleInstance(QObject *parent = nullptr);
    ~SingleInstance();
    void listen(QString name);
    bool hasPrevious(QString name, QString _url);

signals:

    void newInstance();
    void doAction(const QString & newURL);


public slots:

    void newConnection();
    void readyRead();

private:
    QLocalSocket* mSocket;
    QLocalServer mServer;
};

#endif // SINGLEINSTANCE_H
