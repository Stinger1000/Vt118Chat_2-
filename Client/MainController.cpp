#include "MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , m_network(std::make_unique<NetworkController>(this))
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(2000);
    m_timer->start();

    connect(m_timer, &QTimer::timeout, this, &MainController::GetStatusSocket);
    connect(m_network.get(), &NetworkController::NewMes, this, &MainController::MesFromNetwork);
    connect(this, &MainController::NewMes, m_network.get(), &NetworkController::SendMes);
}

void MainController::MesFromNetwork(const QByteArray& mes)
{
    //emit NewMes("Test", mes);
}

void MainController::Registration()
{
    QByteArray data;
    uint8_t    null = 0;
    data.push_back(null);
    data.push_back(0x04);
    data.push_back(0x01);
    data.push_back(0x01);
    data.push_back(0x01);
    data.push_back(0x01);
    data.push_back(0x04);
    data.push_back(0x01);
    data.push_back(0x01);
    data.push_back(0x01);
    data.push_back(0x01);
    emit NewMes(data);
}

void MainController::GetStatusSocket()
{
    auto status = m_network->GetStatusConnect();
    if (!status)
        m_network->ConnectToHost();
    emit StatusSocket(status);
}
