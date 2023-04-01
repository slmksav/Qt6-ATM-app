#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>
#include <QString>

class DLLPinCode : public QObject
{
    Q_OBJECT
public:
    explicit DLLPinCode(QObject *parent = nullptr);
};

#endif // DLLSERIALPORT_H
