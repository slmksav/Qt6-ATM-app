#include "dllserialport.h"

QString getBaseUrl()
{
    return "http://localhost:3000";
    //tarvittaessa helppo muuttaa
    //esimerkiksi
    //return "https://azure.com/myapp"; Tämä pitäisi saada muutettua johonkin ulkoiseen palvelimeen, koska yhteys db4free:stä tähän on nyt lokaali
}

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
}

QString DLLSerialPort::getSerialData()
{
    if (m_serialPort.canReadLine())
    {
        QByteArray data = m_serialPort.readLine();
        data = data.trimmed();
        QString strData = QString::fromUtf8(data);
        return strData;
    }
    else
    {
        return QString();
    }
}


QString DLLSerialPort::putCardNumber()
{
    QString site_url = getBaseUrl() + "/card/1/pinhexcode";
}
