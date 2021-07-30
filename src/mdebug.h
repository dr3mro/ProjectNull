///////////////////////////////////  ProjectNull  ////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                Coded by  Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
#ifndef MDEBUG_H
#define MDEBUG_H

#endif // MDEBUG_H
#include <QDebug>


#define LOGEDNABLED



#ifdef LOGEDNABLED

#ifdef Q_OS_WIN
#define LOGFILE "Log.txt"
#endif

#ifdef Q_OS_MACOS
#define LOGFILE "~/TheVideoPlayerLog.txt"
#endif


#define mDebug() QMessageLogger(__FILE__, __LINE__, Q_FUNC_INFO).debug()
#else
#define mDebug() QNoDebug()
#endif
////////////////////////////////////////  END  ///////////////////////////////////////
//                          Screen Capture Proof Video Player                       //
//                                 Coded by Amr Osman                               //
//                                     july 2021                                    //
////////////////////////////////  As a Freelance Project  ////////////////////////////
