#include <QString>
#include "provider.h"
#include "Model/settings.h"

namespace Ps
{

static QString SETTINGS_FILE = QStringLiteral("settings.json");

Settings& Provider::GetSettingsAsSingleton()
{
  static Settings instance(NULL,SETTINGS_FILE);
  return instance;
}

} // namespace
