#ifndef PLAYERENGINE_H
#define PLAYERENGINE_H

#include <QObject>
#include <QTimer>

class PlayerEngine : public QObject
{
    Q_OBJECT
public:
    explicit PlayerEngine(const QString & _url = QString(), QObject *parent = nullptr);
    void startPlayingMovie();
public slots:
    void setVideoUrl(const QString &_url);

private:
    QString m_Url;
    QTimer timer;

signals:
    void playNow(const QString& _url);
    void hidePlayPauseButton();

};

#endif // PLAYERENGINE_H
