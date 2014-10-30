#include <QString>
#include "provider.h"
#include "Model/settings.h"

namespace Ps
{

static QString SETTINGS_FILE = QStringLiteral("settings.json");

std::auto_ptr<Settings> Provider::m_instanceSettings;

Settings& Provider::GetSettingsAsSingleton()
{
  if (m_instanceSettings.get() == NULL)
  {
      m_instanceSettings = std::auto_ptr<Settings>(new Settings(NULL,SETTINGS_FILE));
  }
  return *m_instanceSettings;
}

} // namespace
