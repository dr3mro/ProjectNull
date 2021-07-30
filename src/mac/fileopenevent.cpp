///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
/* Because MacOs does not work like windows
 * and it pass the file as open with signals
 * we had to write this open with handler
 * DAMN MacOS
 */
#include "fileopenevent.h"

FileOpenEvent::FileOpenEvent(QObject *parent) : QObject(parent){
}

bool FileOpenEvent::eventFilter(QObject* obj, QEvent* event)
{
    QString url;
    if (event->type() == QEvent::FileOpen)
    {
        QFileOpenEvent* fileEvent = static_cast<QFileOpenEvent*>(event);
        if (!fileEvent->url().isEmpty())
            url = fileEvent->url().toString();

        // here we try to process the url
        emit urlOpened(DataHelper::processURL(url));
        return false;
    }
    return QObject::eventFilter(obj, event);
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ///////////////////////////
