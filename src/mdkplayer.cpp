#include "mdkplayer.h"
#include <QDebug>

class VideoRendererInternal : public QQuickFramebufferObject::Renderer
{
public:
    VideoRendererInternal(QmlMDKPlayer *r) {
        this->r = r;
    }

    void render() override {
        r->renderVideo();
    }

    QOpenGLFramebufferObject *createFramebufferObject(const QSize &size) override {
        r->setVideoSurfaceSize(size.width(), size.height());
        return new QOpenGLFramebufferObject(size);
    }

    QmlMDKPlayer *r;
};


QmlMDKPlayer::QmlMDKPlayer(QQuickItem *parent):
    QQuickFramebufferObject(parent),
    internal_player(new Player)
{
    setMirrorVertically(true);
}

QmlMDKPlayer::~QmlMDKPlayer()
{
    delete internal_player;
}

QQuickFramebufferObject::Renderer *QmlMDKPlayer::createRenderer() const
{
    return new VideoRendererInternal(const_cast<QmlMDKPlayer*>(this));
}

void QmlMDKPlayer::play()
{
    internal_player->set(PlaybackState::Playing);
    internal_player->setRenderCallback([=](void *){
        QMetaObject::invokeMethod(this, "update");
    });
}

void QmlMDKPlayer::pause()
{
    internal_player->set(PlaybackState::Paused);
}

void QmlMDKPlayer::mute(const bool &m)
{
    internal_player->setMute(m);
}

void QmlMDKPlayer::setPlaybackRate(float rate)
{
    internal_player->setPlaybackRate(rate);
}

void QmlMDKPlayer::setVideoSurfaceSize(int width, int height)
{
    internal_player->setVideoSurfaceSize(width, height);
}

void QmlMDKPlayer::renderVideo()
{
    internal_player->renderVideo();
}

void QmlMDKPlayer::seek(unsigned long long pos)
{
    internal_player->seek(pos,SeekFlag::FromStart);
}

unsigned long long  QmlMDKPlayer::duration()
{
    return internal_player->mediaInfo().duration;
}

unsigned long long QmlMDKPlayer::position()
{
    return internal_player->position();
}

bool QmlMDKPlayer::isPlaying()
{
    return (internal_player->state() == State::Playing);
}

