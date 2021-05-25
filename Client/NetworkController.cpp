#include "NetworkController.h"

NetworkController::NetworkController(QObject* parent)
    : QObject(parent)
    , m_tcp_socket(new QTcpSocket(this))
{
    ConnectToHost();

    connect(m_tcp_socket, &QTcpSocket::channelReadyRead, this, &NetworkController::GetMesFromHost);
}

NetworkController::~NetworkController()
{
    delete m_tcp_socket;
}

/**
 * @brief Connect socket to host
 */
void NetworkController::ConnectToHost()
{
    m_tcp_socket->abort();
    m_tcp_socket->connectToHost(QHostAddress(m_ip_server), m_port_server);
}

/**
 * @brief Get message from host
 */
void NetworkController::GetMesFromHost(int /*channel*/)
{
    emit NewMes(m_tcp_socket->readAll());
}

/**
 * @brief Set ip to socket
 * @param ip - ipv4
 */
void NetworkController::SetIP(const QString& ip)
{
    m_ip_server = ip;
    ConnectToHost();
}

/**
 * @brief Get status connect
 * @return - status(true - work)
 */
bool NetworkController::GetStatusConnect()
{
    if (m_tcp_socket->state() == 3) {
        return true;
    }
    return false;
}

/**
 * @brief Send mes to server
 * @param mes - message
 */
void NetworkController::SendMes(const QByteArray& mes)
{
    QByteArray out  = mes;
    uint16_t   size = mes.size() + 2;
    out.push_front(size & 0xFF);
    out.push_front((size >> 8) & 0xFF);
    m_tcp_socket->write(out);
}
