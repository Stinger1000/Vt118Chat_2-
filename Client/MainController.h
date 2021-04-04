#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <NetworkController.h>
#include <QObject>
#include <memory>

class MainController : public QObject {
    Q_OBJECT
public:
    explicit MainController(QObject* parent = nullptr);
    void MesFromNetwork(const QString& mes);

signals:
    void NewMes(const QString& name, const QString& mes);

private:
    std::unique_ptr<NetworkController> m_network { nullptr };
};

#endif // MAINCONTROLLER_H
