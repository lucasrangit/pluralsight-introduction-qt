#include <QString>
#include <QDir>
#include <QFile>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QStringListModel>
#include "settings.h"


namespace Ps
{

static QString RESOURCE_PREFIX = QStringLiteral(":/json");

Settings::Settings(QObject *parent, QString filename) :
    QObject(parent),
    m_filename(filename),
    m_modelCommands(*new QStringListModel(this))
{

}

void Settings::ParseJsonData()
{
    QString raw_json = ReadJsonFile();
    if (raw_json.size() == 0) return;

    JsonObjErrPair json_result = GetJsonObject(raw_json);
    QJsonParseError json_error = json_result.second;
    if (json_error.error != QJsonParseError::NoError)
    {
      ShowJsonParseError(json_error);
    }

    QJsonObject json_obj = json_result.first;
    m_applicationName = json_obj["applicationName"].toString();
    m_appShortName = json_obj["appShortName"].toString();
    m_hostName = json_obj["hostName"].toString();
    m_portNumber = json_obj["port"].toInt();
    m_waitMs = json_obj["tcpLongWaitMs"].toInt();
    m_readWaitMs = json_obj["tcpShortWaitMs"].toInt();
    SetupCommands(json_obj);
}

JsonObjErrPair Settings::GetJsonObject(const QString& raw_jason)
{
  QJsonParseError json_parse_error;
  QJsonDocument json_doc = QJsonDocument::fromJson(raw_jason.toUtf8(),
                                                   &json_parse_error);
  QJsonObject json_obj = json_doc.object();
  return std::make_pair(json_obj, json_parse_error);
}

void Settings::SetupCommands(QJsonObject json_obj)
{
    QJsonArray cmd_array = json_obj["commands"].toArray();
    QStringList cmd_list;
    foreach (const QJsonValue &item, cmd_array)
    {
        cmd_list.append(item.toString());
    }
    m_modelCommands.setStringList(cmd_list);
}

void Settings::ShowJsonParseError(QJsonParseError json_error)
{
   QString msg = tr("Error parsing JSON settings file.\n");
   msg.append(json_error.errorString());
   QMessageBox::critical(0,tr("VFP"),msg);
}

QString Settings::ReadJsonFile()
{
    QString default_settings = ReadJsonFileFromInternalResource();
    return default_settings;
}

QString Settings::ReadJsonFileFromInternalResource()
{
  QDir res_dir (RESOURCE_PREFIX);
  if (!res_dir.exists())
  {
      SendErrorMessage("Internal resource path missing " +
                       res_dir.canonicalPath());
      return "";
  }

  QString path = res_dir.filePath(m_filename);

  QFile res_file(path);
  if (!res_file.open(QFile::ReadOnly | QFile::Text))
  {
      SendErrorMessage("Cound not open internal resource " +
                       path);
      return "";
  }
  QString settings = res_file.readAll();

  return settings;
}

void Settings::SendErrorMessage(const QString& msg)
{
  emit NotifyStatusMessage(msg);
}

}
