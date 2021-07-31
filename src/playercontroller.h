///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include <QObject>
#include "mdebug.h"

class PlayerController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString m_Url READ getVideoUrl WRITE setVideoUrl NOTIFY videoUrlChanged)
public:
    explicit PlayerController(const QString & _url = QString(), QObject *parent = nullptr);
    // public method to start playback ASAP and squedule the fadeout of playpausebutton
    void startPlayingMovie();
    QString &getVideoUrl();
public slots:
    // public slot (method) to set URL
    void setVideoUrl(const QString &_url);

private:
    QString m_Url; // current videoURL

signals:
    void videoUrlChanged();
   /*
    * Those signals above are connected in the QML file (MIAN.QML)
    *    PlayerContrller.onHidePlayPauseButton.connect(onHidePlayPauseButton)
    */
};

#endif // PLAYERCONTROLLER_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
