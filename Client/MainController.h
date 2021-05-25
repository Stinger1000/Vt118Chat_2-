#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include "Protocol.h"
#include <NetworkController.h>
#include <QMessageBox>
#include <QObject>
#include <QTimer>
#include <memory>

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);
    void MesFromNetwork(const QByteArray& mes);
    void Registration(const QByteArray& login, const QByteArray& pass);
    void Loging(const QByteArray& login, const QByteArray& pass);
    void SendMesNet(const QString& data);
    void GetStatusSocket();
    void SendMes(const QByteArray& data);

signals:
    void NewMesSend(const QByteArray& data);
    void StatusSocket(const bool status);
    void ResponseRegLog(const uint8_t reg_or_log, const bool status);
    void ClientsList(const QStringList& list);
    void NewMesChat(const QString& name, const QString& mes);
    void SetIP(const QString& ip);

private:
    std::unique_ptr<NetworkController> m_network { nullptr };
    QTimer*                            m_timer { nullptr };
};

#endif // MAINCONTROLLER_H
