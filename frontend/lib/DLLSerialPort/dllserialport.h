#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include "DLLSerialPort_global.h"

class DLLSERIALPORT_EXPORT DLLSerialPort : public QObject
{
Q_OBJECT

public:
    explicit DLLSerialPort(QObject *parent = nullptr);
    void sendData(const QString& dataToSend);

signals:
    void dataReceived(const QString& hexData);

private slots:
    void handleReadyRead();

private:
    QSerialPort m_serialPort;
    int SerialBytes;
    QString SerialInfo;
};

#endif // DLLSERIALPORT_H
