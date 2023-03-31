#ifndef DLLSERIALPORT_H
#define DLLSERIALPORT_H

#include <QObject>
#include <QSerialPort>
#include <QString>

class DLLSerialPort : public QObject
{
    Q_OBJECT
public:
    explicit DLLSerialPort(QObject *parent = nullptr);
    QString getSerialData();
    QString putCardNumber();

private:
    QSerialPort m_serialPort;
};

#endif // DLLSERIALPORT_H
