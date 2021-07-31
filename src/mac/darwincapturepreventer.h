///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
/*
 * Here is the Magic code for macOS detection of
 * Screen capture signals
 * This is undocumented api
 * may break sometime
 * keep it simple
 * :)
 */
#include <QtGlobal>
#ifdef Q_OS_MACOS
#ifndef DARWINCAPTUREPREVENTER_H
#define DARWINCAPTUREPREVENTER_H

#include <QObject>
#include <QGuiApplication>
#include <QWindow>
#include <QTimer>
#include "../mdebug.h"

class DarwinCapturePreventer : public QObject
{
    Q_OBJECT
public:
    explicit DarwinCapturePreventer(QGuiApplication & app, QObject *parent = nullptr);
    Q_INVOKABLE void update();
private:
    QGuiApplication & app;
    QTimer init;
signals:

};
#endif // DARWINCAPTUREPREVENTER_H
#endif
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
