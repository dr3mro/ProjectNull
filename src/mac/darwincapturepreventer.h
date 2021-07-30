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
#ifdef Q_OS_MACOS
#ifndef DARWINCAPTUREPREVENTER_H
#define DARWINCAPTUREPREVENTER_H

#include <QObject>
#include <QGuiApplication>
#include <QWindow>
#include <QDebug>
#include <QtGlobal>

class DarwinCapturePreventer : public QObject
{
    Q_OBJECT
public:
    explicit DarwinCapturePreventer(QGuiApplication & app, QObject *parent = nullptr);
    void update();
private:
    QGuiApplication & app;
signals:

};
#endif // DARWINCAPTUREPREVENTER_H
#endif
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////