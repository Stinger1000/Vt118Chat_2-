#ifndef MAINCONTROLLER_H
#define MAINCONTROLLER_H

#include <QObject>
#include <QFile>
#include <QDataStream>

#include "TcpServer.h"
#include "ClientDataModel.h"

class MainController : public QObject
{
    Q_OBJECT
public:
    explicit MainController(QObject *parent = nullptr);
    ~MainController();

    bool ChechLoginDublicate(const QString login);

public slots:
    void DataRecv(const QByteArray& data, const quintptr socketDescriptor);

signals:
    void DataSend(const QByteArray& data, const quintptr socketDescriptor);

    void DublicateLogin(const QByteArray& data, const quintptr socketDescriptor);

private:
    TcpServer* m_server{nullptr};
    QList<client_data_model_t> m_clients;
};

#endif // MAINCONTROLLER_H
