#include "MainController.h"

MainController::MainController(QObject* parent)
    : QObject(parent)
    , m_network(std::make_unique<NetworkController>(this))
    , m_timer(new QTimer(this))
{
    m_timer->setInterval(1000);
    m_timer->start();

    connect(m_timer, &QTimer::timeout, this, &MainController::GetStatusSocket);
    connect(m_network.get(), &NetworkController::NewMes, this, &MainController::MesFromNetwork);
    connect(this, &MainController::NewMesSend, m_network.get(), &NetworkController::SendMes);
    connect(this, &MainController::SetIP, m_network.get(), &NetworkController::SetIP);
}

/**
 * @brief Handler message from server
 * @param mes - message
 */
void MainController::MesFromNetwork(const QByteArray& mes)
{
    QByteArray data = mes;
    uint16_t   len  = data.at(0) << 8 | data.at(1);

    if (len != mes.size()) {
        if (len > mes.size())
            return;

        QByteArray save_data = data;
        save_data.remove(0, len);

        MesFromNetwork(save_data);
    }

    data.resize(len);

    data.remove(0, 2);

    switch (data.at(0)) {
    case ResponseRegistration_id: {
        auto status = data.at(1);
        emit ResponseRegLog(ResponseRegistration_id, bool(status));
        break;
    }
    case ResponseLoging_id: {
        auto status = data.at(1);
        emit ResponseRegLog(ResponseLoging_id, bool(status));
        break;
    }
    case ClientsInfo_id: {
        data.remove(0, 1); //type mes

        uint16_t    num = (data.at(0) << 8) | data.at(1);
        uint8_t     size_name { 0 };
        QStringList list_name;
        QByteArray  name;
        data.remove(0, 2);
        for (auto i = 0; i < num; i++) {
            size_name = data.at(0);
            data.remove(0, 1);
            name = data.left(size_name);
            list_name.push_back(QByteArrayToQString(name));
            data.remove(0, size_name);
        }
        emit ClientsList(list_name);
        break;
    }
    case ChatMes_id: {
        data.remove(0, 1); //type mes

        uint8_t size_user_name = data.at(0);
        data.remove(0, 1);
        QByteArray name = data.left(size_user_name);
        data.remove(0, size_user_name);
        emit NewMesChat(QByteArrayToQString(name), QByteArrayToQString(data));
        break;
    }
    }
}

/**
 * @brief Send registration to server
 * @param login - login user
 * @param pass - password user
 */
void MainController::Registration(const QByteArray& login, const QByteArray& pass)
{
    QByteArray data;
    data.push_back(login.size());
    data += login;
    data.push_back(pass.size());
    data += pass;

    data.push_front(Registration_id); //type mes

    emit NewMesSend(data);
}

/**
 * @brief Send loging to server
 * @param login - login user
 * @param pass - password user
 */
void MainController::Loging(const QByteArray& login, const QByteArray& pass)
{
    QByteArray data;
    data.push_back(login.size());
    data += login;
    data.push_back(pass.size());
    data += pass;

    data.push_front(Loging_id); //type mes

    emit NewMesSend(data);
}

/**
 * @brief Send message to server
 * @param data - message
 */
void MainController::SendMes(const QByteArray& data)
{
    QByteArray data_send = data;

    data_send.push_front(SendMes_id); //type mes

    emit NewMesSend(data_send);
}

/**
 * @brief Get status socket
 */
void MainController::GetStatusSocket()
{
    auto status = m_network->GetStatusConnect();
    if (!status)
        m_network->ConnectToHost();
    emit StatusSocket(status);
}
