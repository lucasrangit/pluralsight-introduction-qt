#pragma once
#include <QObject>

namespace Ps
{

class InstSocket;
class Settings;

class Instrument : public QObject
{
    Q_OBJECT
public:
    explicit Instrument(QObject *parent, InstSocket& sock, Settings &config);
    ~Instrument();

    void Connect();
    void Disconnect() const;
    bool IsConnected() const;
    QString GetHostName() const;
    quint16 GetPort() const;
    void SetLongWaitMs(int value);
    void SetShortWaitMs(int value);

signals:
    void NotifyConnected() const;
    void NotifyDisconnected() const;
    void NotifyDataSent(const QString& dataSent) const;
    void NotifyDataReceived(const QString& dataRead) const;
    void NotifyErrorDetected(const QString& errorMsg) const;
    void NotifyStatusUpdated(const QString& statusMsg) const;

public slots:
    void onHostNameChanged(const QString& hostName);
    void onPortChanged(quint16 port);
    void onConnected();
    void onDisconnected();
    void onSendRequest(const QString& dataToSend);
    void onReceiveRequest();
    void onPulseWidthChanged(double value);

private:
    InstSocket& m_instSocket;
    QString m_lastCommandSent;
    Settings& m_settings;

    void WireConnections();

    explicit Instrument(const Instrument& rhs);
    Instrument& operator= (const Instrument& rhs);
};

} // namespace


