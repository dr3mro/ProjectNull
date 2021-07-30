///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#ifndef FILEOPENEVENT_H
#define FILEOPENEVENT_H

#include <QObject>
#include <QFileOpenEvent>
#include <QDebug>
#include "src/datahelper.h"

class FileOpenEvent: public QObject
{
    Q_OBJECT
public:
    explicit FileOpenEvent(QObject *parent = nullptr); //CTOR
protected:
    bool eventFilter(QObject* obj, QEvent* event);
signals:
    // This signal is emited when a new URL is sent from the OS
    void urlOpened(const QString url);

};

#endif // FILEOPENEVENT_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
