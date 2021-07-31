#ifndef VIDEORENDERER_H
#define VIDEORENDERER_H

#include <QQuickFramebufferObject>
#include <QOpenGLFramebufferObject>
#include <QTimer>
#include "mdebug.h"
#include "src/mac/libs/mdk-sdk/lib/mdk.framework/Versions/A/Headers/Player.h"

using namespace MDK_NS;

class QmlMDKPlayer : public QQuickFramebufferObject
{
    Q_OBJECT
    Q_PROPERTY(QString source READ source WRITE setSource NOTIFY sourceChanged)
public:
    explicit QmlMDKPlayer(QQuickItem *parent = nullptr);
    virtual ~QmlMDKPlayer();
    Renderer *createRenderer() const;

    Q_INVOKABLE QString source() { return m_source; }
    Q_INVOKABLE void setSource(const QString & s) {
        internal_player->setMedia(s.toUtf8().data());
        m_source = s;
        emit sourceChanged();
        play();
    }

    Q_INVOKABLE void play();
    Q_INVOKABLE void pause();
    Q_INVOKABLE void mute(const bool &m);
    Q_INVOKABLE void setPlaybackRate(float rate);
    Q_INVOKABLE void setVideoSurfaceSize(int width, int height);

    void renderVideo();
    Q_INVOKABLE void seek(unsigned long long  pos);
    Q_INVOKABLE unsigned long long duration();
    Q_INVOKABLE unsigned long long position();
    Q_INVOKABLE bool isPlaying();

signals:
    void sourceChanged();


private:
    QString m_source;
    Player *internal_player;
    QTimer seekerUpdate;
};

#endif // VIDEORENDERER_H
