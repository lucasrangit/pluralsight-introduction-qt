#include <QString>
#include <QDir>
#include <QFile>
#include <QStandardPaths>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QMessageBox>
#include <QStringListModel>
#include <QDebug>
#include "settings.h"


namespace Ps
{

static QString RESOURCE_PREFIX = QStringLiteral(":/json");
static const int PW_COMMAND_INDEX = 5;

Settings::Settings(QObject *parent, QString filename) :
    QObject(parent),
    m_filename(filename),
    m_applicationName(""),
    m_appShortName(""),
    m_hostName("127.0.0.1"),
    m_portNumber(555102),
    m_tcpLongWaitMs(10*1000),
    m_tcpShortWaitMs(1*1000),
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
    m_tcpLongWaitMs = json_obj["tcpLongWaitMs"].toInt();
    m_tcpShortWaitMs = json_obj["tcpShortWaitMs"].toInt();
    SetupCommands(json_obj);
}

QString Settings::ReadJsonFile()
{
    QString default_settings = ReadJsonFileFromInternalResource();

    QDir config_dir = OpenConfigDirectory();
    QString path = config_dir.filePath(m_filename);
    QFile std_file(path);
    if (std_file.exists())
    {
        if (!std_file.open(QFile::ReadOnly|QFile::Text))
        {
            SendErrorMessage("Cound not open " + path);
            return default_settings;
        }
        QString settings = std_file.readAll();
        std_file.close();
        return settings;
    }
    else
    {
        WriteDefaultsToStdConfigFile(std_file,default_settings);
        return default_settings;
    }
}

void Settings::WriteDefaultsToStdConfigFile(QFile& stdConfigFile,
                                            const QString& settings)
{
    int length = settings.length();
    if (!stdConfigFile.open(QFile::WriteOnly|QFile::Text))
    {
        SendErrorMessage("Could not open file to write " + stdConfigFile.fileName());
    }
    else
    {
        qint64 bytes_written = stdConfigFile.write(qPrintable(settings),length);
        if (bytes_written != length)
        {
          SendErrorMessage("Could not write default settings to " + stdConfigFile.fileName());
          if (!stdConfigFile.remove())
          {
              SendErrorMessage("Count not remove configuration file. Please delete " +
                               stdConfigFile.fileName());
          }
        }
        stdConfigFile.close();
    }
}

QDir Settings::OpenConfigDirectory()
{
    QDir config_dir(QStandardPaths::writableLocation(
                        QStandardPaths::ConfigLocation));
    if (!config_dir.exists())
    {
        QDir dir;
        if (!dir.mkdir(config_dir.path()))
        {
            SendErrorMessage("Could not create configuration directory");
            abort();
        }
    }
    return config_dir;
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

    QModelIndex index = m_modelCommands.index(PW_COMMAND_INDEX);
    QVariant test_cmd = m_modelCommands.data(index, Qt::DisplayRole);
    qDebug() << "Test command" << test_cmd.toString();

    if (PW_COMMAND_INDEX < cmd_list.size())
    {
        m_pwCommand = cmd_list[PW_COMMAND_INDEX];
    }
    else
    {
        emit NotifyStatusMessage("Unable to get pulse width command.");
    }
}

void Settings::ShowJsonParseError(QJsonParseError json_error)
{
   QString msg = tr("Error parsing JSON settings file.\n");
   msg.append(json_error.errorString());
   QMessageBox::critical(0,tr("VFP"),msg);
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
