#include <QObject>
#include <QSerialPort>

#if defined(DLLSERIALPORT_LIBRARY)
#  define DLLSERIALPORTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLLSERIALPORTSHARED_EXPORT Q_DECL_IMPORT
#endif

class DLLSERIALPORTSHARED_EXPORT DLLSerialPort : public QObject
{
    Q_OBJECT

public:
    explicit DLLSerialPort(QObject *parent = nullptr);
    QString getSerialData();

signals:
    void dataReceived(const QString& data);

private slots:
    void handleReadyRead();

private:
    QSerialPort m_serialPort;
};
