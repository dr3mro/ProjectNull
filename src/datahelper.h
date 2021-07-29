///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////

#ifndef DATAHELPER_H
#define DATAHELPER_H

#include <QObject>
#include <QDebug>

class DataHelper : public QObject
{
    Q_OBJECT
public:
    explicit DataHelper(QObject *parent = nullptr);
    static QString processURL(const QString &rawArgs);
};
#endif // DATAHELPER_H
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
