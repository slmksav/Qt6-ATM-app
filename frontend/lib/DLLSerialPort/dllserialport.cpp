#include "dllserialport.h"
#include <QSerialPortInfo>
#include <QDebug>

DLLSerialPort::DLLSerialPort(QObject *parent) : QObject(parent)
{
    const auto serialPortInfos = QSerialPortInfo::availablePorts();

    // etsii portin joka on käytössä. todellisuudessa ei kovin hyvä ratkaisu koska voi olla monta sarjaporttia käyttävää laitetta kiinni

    QString serialPortName;
    for (const QSerialPortInfo &portInfo : serialPortInfos) {
        QSerialPort serialPort;
        serialPort.setPort(portInfo);
        qDebug() << "\n"
                 << "Port:" << portInfo.portName() << "\n"
                 << "Location:" << portInfo.systemLocation() << "\n"
                 << "Description:" << portInfo.description() << "\n"
                 << "Manufacturer:" << portInfo.manufacturer() << "\n"
                 << "Serial number:" << portInfo.serialNumber() << "\n"
                 << "Vendor Identifier:"
                 << (portInfo.hasVendorIdentifier()
                     ? QByteArray::number(portInfo.vendorIdentifier(), 16)
                     : QByteArray()) << "\n"
                 << "Product Identifier:"
                 << (portInfo.hasProductIdentifier()
                     ? QByteArray::number(portInfo.productIdentifier(), 16)
                     : QByteArray());

        if (serialPort.open(QIODevice::ReadOnly)) {
            if (serialPort.baudRate() == QSerialPort::Baud9600) {
                serialPortName = portInfo.portName();
                serialPort.close();
                break;
            } else {
                serialPort.close();
            }
        } else {
            qDebug() << "failed to open port" << portInfo.portName() << ": " << serialPort.errorString();
        }
    }
    if (serialPortName.isEmpty()) {
        qDebug() << "No serial port found";
    } else {
        qDebug() << "Using serial port:" << serialPortName;
        m_serialPort.setPortName(serialPortName);
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
}


void DLLSerialPort::sendData(const QString& dataToSend)
{
    QByteArray data = dataToSend.toUtf8();
    m_serialPort.write(data);
}

void DLLSerialPort::handleReadyRead()
{
    QByteArray data = m_serialPort.readAll();
    QString hexData = QString::fromLatin1(data.toHex().constData(), data.size()*2);
    qDebug() << "Received data:" << hexData;
    emit dataReceived(hexData);
}


