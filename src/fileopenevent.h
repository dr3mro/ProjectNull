#ifndef FILEOPENEVENT_H
#define FILEOPENEVENT_H

#include <QObject>
#include <QFileOpenEvent>
#include <QDebug>
#include "datahelper.h"

class FileOpenEvent: public QObject
{
    Q_OBJECT
public:
    explicit FileOpenEvent(QObject *parent = nullptr);
protected:
    bool eventFilter(QObject* obj, QEvent* event);
signals:
    void urlOpened(const QString url);

};

#endif // FILEOPENEVENT_H
