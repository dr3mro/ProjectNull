///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#include "datahelper.h"

DataHelper::DataHelper(QObject *parent) : QObject(parent){
}

// argument processing
QString DataHelper::processURL(const QString &rawArgs)
{
    mDebug() << "pre processing" << rawArgs;

    // First we convert the application argument from a String to a List of Strings
    QStringList list_args = rawArgs.split(',');

    // Now we have the URL as ARG[1] but still contains the protocol
    // like this
    // projectNull::[file:///C:/Users/Amr/Downloads/video1.mp4]
    // or that
    // projectNull::[http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ElephantsDream.mp4]
    // in MacOs it will never be as an ARG but as open with signal

    QString newURL;       

    // now we remove the preceeding "projectNull::[" &  the trailing "]"
#ifdef Q_OS_MACOS
    newURL = list_args.at(0);
    newURL.remove("projectnull::%5B",Qt::CaseInsensitive);
    newURL.remove("%5D");
#endif

#ifdef Q_OS_WIN
    newURL = list_args.at(1);
    newURL.remove("projectnull::[",Qt::CaseInsensitive);
    newURL.remove("]");
#endif

    mDebug() << "post processing" << newURL;
    // reurning a clean URL
    return newURL;
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
