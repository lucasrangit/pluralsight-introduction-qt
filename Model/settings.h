#pragma once
#include <QObject>

class QString;
class QStringListModel;
class QJsonParseError;
class QJasonObject;
class QFile;
class QDir;

namespace Ps{

class Settings : public QObject
{
    Q_OBJECT
public:
    explicit Settings(QObject *parent, QString filename);


private:
    QString m_filename;

    QString ReadJsonFile();
    QString ReadJsonFileFromInternalResource();

    explicit Settings(const Settings& rhs) = delete;
    Settings& operator= (const Settings& rhs) = delete;
};

} // namespace
