#include "dllserialport.h"

DLLSerialPort::DLLSerialPort(QObject *parent) : QObject(parent)
{
    m_serialPort.setPortName("/dev/ttyACM0");
    m_serialPort.setBaudRate(QSerialPort::Baud9600);
    m_serialPort.setDataBits(QSerialPort::Data8);
    m_serialPort.setParity(QSerialPort::NoParity);
    m_serialPort.setStopBits(QSerialPort::OneStop);
    m_serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if (!m_serialPort.open(QIODevice::ReadOnly))
    {
        qWarning("Failed to open serial port");
    }

    connect(&m_serialPort, &QSerialPort::readyRead, this, &DLLSerialPort::handleReadyRead);
}

void DLLSerialPort::handleReadyRead()
{
    if (m_serialPort.canReadLine())
    {
        QByteArray data = m_serialPort.readLine();
        data = data.trimmed();
        QString strData = QString::fromUtf8(data);
        emit dataReceived(strData);
    }
}
