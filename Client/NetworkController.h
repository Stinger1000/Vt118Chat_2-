#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <QDataStream>
#include <QHostAddress>
#include <QObject>
#include <QString>
#include <QTcpSocket>

class NetworkController : public QObject {
    Q_OBJECT
public:
    explicit NetworkController(QObject* parent = nullptr);
    ~NetworkController();
    void ConnectToHost();
    bool GetStatusConnect();

public slots:
    void SendMes(const QByteArray& mes);
    void GetMesFromHost(int channel);
    void SetIP(const QString& ip);

signals:
    void NewMes(const QByteArray& mes);

private:
    QTcpSocket* m_tcp_socket { nullptr };

    quint16 m_port_server { 9999 };
    QString m_ip_server { "192.168.0.15" };
};

#endif // NETWORKCONTROLLER_H
