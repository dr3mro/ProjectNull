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

signals:

};

#endif // DATAHELPER_H
