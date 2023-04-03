#include <QObject>
#include <QSerialPort>
#include "DLLSerialPort_global.h"

class DLLSERIALPORT_EXPORT DLLSerialPort : public QObject
{
    Q_OBJECT

public:
    explicit DLLSerialPort(QObject *parent = nullptr);
    QString getSerialData();
    QSerialPort m_serialPort;

signals:
    void dataReceived(const QString& data);

private slots:
    void handleReadyRead();

private:
    //QSerialPort m_serialPort;
};
