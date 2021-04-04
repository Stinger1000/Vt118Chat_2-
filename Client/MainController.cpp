#include "MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , m_network(
          std::make_unique<NetworkController>(this))
{
    connect(m_network.get(), &NetworkController::NewMes, this, &MainController::MesFromNetwork);
}

void MainController::MesFromNetwork(const QString& mes)
{
    emit NewMes("Test", mes);
}
