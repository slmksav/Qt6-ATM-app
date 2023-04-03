#include "dllserialport.h"
#include <QSerialPortInfo>
#include <QDebug>

DLLSerialPort::DLLSerialPort(QObject *parent) : QObject(parent)
{
    m_serialPort.setPortName("COM3");
    if(!m_serialPort.setBaudRate(QSerialPort::Baud9600))
        qDebug() << m_serialPort.errorString();
    if(!m_serialPort.setDataBits(QSerialPort::Data7))
        qDebug() << m_serialPort.errorString();
    if(!m_serialPort.setParity(QSerialPort::EvenParity))
        qDebug() << m_serialPort.errorString();
    if(!m_serialPort.setFlowControl(QSerialPort::HardwareControl))
        qDebug() << m_serialPort.errorString();
    if(!m_serialPort.setStopBits(QSerialPort::OneStop))
        qDebug() << m_serialPort.errorString();
    if(!m_serialPort.open(QIODevice::ReadOnly))
        qDebug() << m_serialPort.errorString();
    qDebug() << m_serialPort.bytesAvailable();

    connect(&m_serialPort, &QSerialPort::readyRead, this, &DLLSerialPort::handleReadyRead);
}

void DLLSerialPort::sendData(const QString& dataToSend)
{
    QByteArray data = dataToSend.toUtf8();
    m_serialPort.write(data);
}

void DLLSerialPort::handleReadyRead()
{
    QByteArray data = m_serialPort.readAll();
    QString hexData = QString(data.toHex()).trimmed();
    qDebug() << "Received data:" << hexData;
    emit dataReceived(hexData);
}

