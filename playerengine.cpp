#include "playerengine.h"

PlayerEngine::PlayerEngine(const QString &_url, QObject *parent) : QObject(parent),
    m_Url(_url){
}

void PlayerEngine::startPlayingMovie()
{
    emit playNow(m_Url);
    timer.singleShot(2000,this,&PlayerEngine::hidePlayPauseButton);
}

void PlayerEngine::setVideoUrl(const QString &_url)
{
    m_Url = _url;
    timer.singleShot(2000,this,&PlayerEngine::hidePlayPauseButton);
}
