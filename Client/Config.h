#ifndef CONFIG_H
#define CONFIG_H

#include <QSettings>
#include <QString>

namespace Config {

static constexpr const char* nameFile = "settings.ini";

void     WriteConfig(const QString key, const QVariant data);
QVariant ReadConfig(const QString key, QVariant data);
}

#endif // CONFIG_H
