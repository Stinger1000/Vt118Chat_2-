#ifndef CLIENTDATAMODEL_H
#define CLIENTDATAMODEL_H

#include <QtGlobal>
#include <QString>

enum MsgType{
    Registration,
    Loging,
    Info,
};

struct client_data_model_t{
    quintptr discriptor{0};
    uint32_t key{0};
    bool status{0};

    QString login;
    QString password;
};

#endif // CLIENTDATAMODEL_H
