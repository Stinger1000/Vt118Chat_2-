#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>

#include "MyThread.h"

class TcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    void StartServer();
    void TestServer();

public slots:

signals:
    void NewDataSend(const QByteArray& data, const quintptr socketDescriptor);
    void NewDataRecv(const QByteArray& data, const quintptr socketDescriptor);

protected:
    void incomingConnection(qintptr socketDescriptor);

private:
    const int m_default_port {9999};
};

#endif // TCPSERVER_H
