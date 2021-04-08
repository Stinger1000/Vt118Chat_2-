#include "Config.h"

void Config::WriteConfig(const QString key, const QVariant data)
{
    QSettings settings(nameFile, QSettings::IniFormat);
    settings.setValue(key, data);
}

QVariant Config::ReadConfig(const QString key, QVariant data)
{
    QSettings settings(nameFile, QSettings::IniFormat);
    return settings.value(key, data);
}
