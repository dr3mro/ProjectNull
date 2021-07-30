///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#include "playerengine.h"

PlayerEngine::PlayerEngine(const QString &_url, QObject *parent) : QObject(parent),
    m_Url(_url){
}

void PlayerEngine::startPlayingMovie()
{
    emit playNow(m_Url); // play the current URL
    timer.singleShot(2000,this,&PlayerEngine::hidePlayPauseButton); // call the hidePlayPauseButton after 2 sec
}

QString &PlayerEngine::getVideoUrl()
{
    return m_Url;
}

void PlayerEngine::setVideoUrl(const QString &_url)
{
    qDebug() << "videoset: " << _url;
    m_Url = _url; // sets the url
    emit playNow(m_Url);
    timer.singleShot(2000,this,&PlayerEngine::hidePlayPauseButton); // call the hidePlayPauseButton after 2 sec
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
