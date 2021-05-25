#ifndef PROTOCOL_H
#define PROTOCOL_H

#include <QByteArray>
#include <QString>

enum {
    Registration_id,
    Loging_id,
    SendMes_id,
};

enum {
    ResponseRegistration_id,
    ResponseLoging_id,
    ClientsInfo_id,
    ChatMes_id,
};

static QByteArray QStingToQByteArray(const QString& data)
{
    QByteArray out((const char*)(data.utf16()), data.size() * 2);
    return out;
}

static QString QByteArrayToQString(const QByteArray& data)
{
    auto str = QString::fromUtf16(
        reinterpret_cast<const ushort*>(data.data()), data.size() / 2);

    return str;
}

#endif // PROTOCOL_H
