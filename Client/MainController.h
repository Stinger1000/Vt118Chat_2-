#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

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
    void Registration();
    void GetStatusSocket();

signals:
    void StatusSocket(const bool status);
    void NewMes(const QByteArray& mes);

private:
    std::unique_ptr<NetworkController> m_network { nullptr };
    QTimer*                            m_timer { nullptr };
};

#endif // MAINCONTROLLER_H
