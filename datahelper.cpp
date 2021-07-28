#include "datahelper.h"

DataHelper::DataHelper(QObject *parent) : QObject(parent)
{

}

QString DataHelper::processURL(const QString &rawArgs)
{
    qDebug() << "raw_args : " << rawArgs;
    QStringList list_args = rawArgs.split(',');
    QString newURL = list_args.at(1);
    qDebug() << "newURL : " << newURL;
    newURL.remove("projectNull::[",Qt::CaseInsensitive);
    qDebug() << "newURL : " << newURL;
    newURL.remove("]");
    qDebug() << "newURL : " << newURL;
    return newURL;
}
