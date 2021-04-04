#include "TcpServer.h"

TcpServer::TcpServer(QObject *parent) : QTcpServer(parent)
{
}

void TcpServer::StartServer()
{
    qDebug() << "Server started...";
    if(!this->listen(QHostAddress::Any, m_default_port)){
        qDebug() << "Not Start Server";
    } else {
        qDebug() << "Server Start";
    }
}

void TcpServer::incomingConnection(qintptr socketDescriptor)
{
    MyThread *thread = new MyThread(socketDescriptor, this);

    connect(thread, &MyThread::finished, thread, &MyThread::deleteLater);

    connect(this, &TcpServer::NewDataSend, thread, &MyThread::ServerDataSend);
    connect(thread, &MyThread::ClientDataRecv, this, &TcpServer::NewDataRecv);

    thread->start();
}
