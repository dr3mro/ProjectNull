#ifndef DARWINCAPTUREPREVENTER_H
#define DARWINCAPTUREPREVENTER_H

#include <QObject>
#include <QGuiApplication>
#include <QWindow>
#include <QDebug>


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
