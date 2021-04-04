#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>

class MyThread : public QThread
{
    Q_OBJECT
public:
    explicit MyThread(qintptr ID, QObject *parent = nullptr);

    void run();

signals:
    void error(QTcpSocket::SocketError error);
    void ClientDataRecv(const QByteArray& data, const quintptr sockDescriptor);

public slots:
    void ServerDataSend(const QByteArray& data, const quintptr sockDescriptor);
    void readyRead();
    void disconnected();

private:
    QTcpSocket* m_socket{nullptr};
    quintptr m_sockDescriptor;

};

#endif // MYTHREAD_H
