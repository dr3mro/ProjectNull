#include "fileopenevent.h"

FileOpenEvent::FileOpenEvent(QObject *parent) : QObject(parent)
{

}


bool FileOpenEvent::eventFilter(QObject* obj, QEvent* event)
{
    QString url;
    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent* fileEvent = static_cast<QFileOpenEvent*>(event);
        if (!fileEvent->url().isEmpty())
            url = fileEvent->url().toString();
            emit urlOpened(DataHelper::processURL(url));
        return false;
    }
   return QObject::eventFilter(obj, event);

}
