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

    QString fortune;
    m_data_stream >> fortune;

    if (!m_data_stream.commitTransaction())
        return;

    emit NewMes(fortune);
}
