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
}

QString &PlayerEngine::getVideoUrl()
{
    return m_Url;
}

void PlayerEngine::setVideoUrl(const QString &_url)
{
    m_Url = _url; // sets the url
    qDebug() << "videoset: " << _url;
    emit videoUrlChanged();
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
