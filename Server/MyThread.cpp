#include "MyThread.h"

MyThread::MyThread(qintptr ID, QObject *parent) : QThread(parent)
{
    this->m_sockDescriptor = ID;
}

void MyThread::run()
{
    m_socket = new QTcpSocket();

     if(!m_socket->setSocketDescriptor(this->m_sockDescriptor)){
         emit error(m_socket->error());
         return;
     }

     connect(m_socket, &QTcpSocket::readyRead, this, &MyThread::readyRead, Qt::DirectConnection);
     connect(m_socket, &QTcpSocket::disconnected, this, &MyThread::disconnected);

     exec();
}

void MyThread::ServerDataSend(const QByteArray &data, const quintptr sockDescriptor)
{
    if(m_sockDescriptor != sockDescriptor)
        return;

    QByteArray send_data = data;
    uint16_t mes_size = send_data.size();
    send_data.push_front(mes_size & 0xFF);
    send_data.push_front((mes_size >> 8) & 0xFF);
    m_socket->write(data);
}

void MyThread::readyRead()
{
    QByteArray data = m_socket->readAll();
    uint16_t len_mes = ((data[0] << 8) & 0xFF00) | (data[1] & 0xFF);
    if(data.size() == len_mes){
        data.remove(0, 2);
        emit ClientDataRecv(data, m_sockDescriptor);
    }
}

void MyThread::disconnected()
{
    m_socket->deleteLater();
    exit(0);
}
