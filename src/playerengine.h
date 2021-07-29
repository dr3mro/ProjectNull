///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////

#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H

#include <QObject>
#include <QTimer>

class PlayerEngine : public QObject
{
    Q_OBJECT
public:
    explicit PlayerEngine(const QString & _url = QString(), QObject *parent = nullptr);
    // public method to start playback ASAP and squedule the fadeout of playpausebutton
    void startPlayingMovie();
public slots:
    // public slot (method) to set URL
    void setVideoUrl(const QString &_url);

private:
    QString m_Url; // current videoURL
    QTimer timer; // timer to hide the playpausebutton after timeout

signals:
    void playNow(const QString& _url); // this signal will start playnow
    void hidePlayPauseButton(); //this signal will hide the playPauseButton
   /*
    * Those signals above are connected in the QML file (MIAN.QML)
    *    PlayerEngine.onPlayNow.connect(playNow)
    *    PlayerEngine.onHidePlayPauseButton.connect(onHidePlayPauseButton)
    */
};

#endif // PLAYERENGINE_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
