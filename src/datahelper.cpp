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
    // First we convert the application argument from a String to a List of Strings
    QStringList list_args = rawArgs.split(',');

    // Now we have the URL as ARG[1] but still contains the protocol
    // like this
    // projectNull::[file:///C:/Users/Amr/Downloads/video1.mp4]
    // or that
    // projectNull::[http://commondatastorage.googleapis.com/gtv-videos-bucket/sample/ElephantsDream.mp4]
    QString newURL = list_args.at(1);

    // now we remove the preceeding "projectNull::["
    newURL.remove("projectNull::[",Qt::CaseInsensitive);

    // now we remove the trailing "]"
    newURL.remove("]");

    // reurning a clean URL
    return newURL;
}
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
