#include <QString>
#include <QDir>
#include <QFile>
#include "settings.h"


namespace Ps
{

static auto RESOURCE_PREFIX = QStringLiteral(":/json");

Settings::Settings(QObject *parent, QString filename) :
    QObject(parent),
    m_filename(filename)
{
    ReadJsonFile();
}

QString Settings::ReadJsonFile()
{
    auto default_settings = ReadJsonFileFromInternalResource();
    return default_settings;
}

QString Settings::ReadJsonFileFromInternalResource()
{
  QDir res_dir (RESOURCE_PREFIX);
  if (!res_dir.exists())
  {
      // TODO send error message
      return "";
  }

  auto path = res_dir.filePath(m_filename);

  QFile res_file(path);
  if (!res_file.open(QFile::ReadOnly | QFile::Text))
  {
      // TODO send error message
      return "";
  }
  QString settings = res_file.readAll();

  return settings;
}

}
