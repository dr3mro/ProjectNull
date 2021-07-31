///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#include "playercontroller.h"

PlayerController::PlayerController(const QString &_url, QObject *parent) : QObject(parent),
    m_Url(_url){
}

void PlayerController::startPlayingMovie()
{
}

QString &PlayerController::getVideoUrl()
{
    return m_Url;
}

void PlayerController::setVideoUrl(const QString &_url)
{
    m_Url = _url; // sets the url
    mDebug() << "videoset: " << _url;
    emit videoUrlChanged();
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
