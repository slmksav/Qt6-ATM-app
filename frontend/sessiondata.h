#ifndef SESSIONDATA_H
#define SESSIONDATA_H

#include <QObject>

class SessionData : public QObject
{
    Q_OBJECT
public:
    explicit SessionData(QObject *parent = nullptr);

signals:

};

#endif // SESSIONDATA_H
