#include "NetworkController.h"

NetworkController::NetworkController(QObject* parent)
    : QObject(parent)
    , m_tcp_socket(new QTcpSocket(this))
{
    m_data_stream.setDevice(m_tcp_socket);
    m_data_stream.setVersion(QDataStream::Qt_4_0);
    ConnectToHost();
}

NetworkController::~NetworkController()
{
    delete m_tcp_socket;
}

void NetworkController::ConnectToHost()
{
    m_tcp_socket->abort();
    m_tcp_socket->connectToHost(QHostAddress(m_ip_server), m_port_server);
}

void NetworkController::GetMesFromHost()
{
    m_data_stream.startTransaction();

    QByteArray fortune;
    m_data_stream >> fortune;

    if (!m_data_stream.commitTransaction())
        return;

    emit NewMes(fortune);
}

bool NetworkController::GetStatusConnect()
{
    if (m_tcp_socket->state() == 3) {
        return true;
    }
    return false;
}

void NetworkController::SendMes(const QByteArray& mes)
{
    QByteArray out  = mes;
    uint16_t   size = mes.size() + 2;
    out.push_front(size & 0xFF);
    out.push_front((size >> 8) & 0xFF);
    m_data_stream.writeRawData(out, out.size());
    m_data_stream.startTransaction();
}
