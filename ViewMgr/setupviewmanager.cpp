#include "setupviewmanager.h"
#include "View/setuptab.h"
#include "Model/instrument.h"
#include "Model/settings.h"
#include "utils.h"

namespace Ps
{
SetupViewManager::SetupViewManager(QObject *parent,
                                   SetupTab &tab,
                                   Instrument &inst,
                                   Settings &config) :
    QObject(parent),
    m_setupTab(tab),
    m_instrument(inst)
{
    WireSettings(config);
    config.ParseJsonData();

    WireHostAndPort();
    m_setupTab.SetHostName(config.getHostName());
    m_setupTab.SetPort(config.getPortNumber());

    WireButtons();
}

SetupViewManager::~SetupViewManager()
{
  Utils::DestructorMsg(this);
}

void SetupViewManager::WireSettings(Settings& config)
{
    connect(&config, &Settings::NotifyStatusMessage,
            &m_setupTab, &SetupTab::onStatusUpdated);
}

void SetupViewManager::WireHostAndPort()
{
    connect(&m_setupTab, &SetupTab::NotifyHostNameChanged,
            &m_instrument, &Instrument::onHostNameChanged);
    connect(&m_setupTab, &SetupTab::NotifyPortChanged,
            &m_instrument, &Instrument::onPortChanged);
}

void SetupViewManager::WireMessages()
{
    connect(&m_instrument, &Instrument::NotifyErrorDetected,
            &m_setupTab, &SetupTab::onStatusUpdated);
    connect(&m_instrument, &Instrument::NotifyStatusUpdated,
            &m_setupTab, &SetupTab::onStatusUpdated);
//    connect(this, &SetupViewManager::NotifyStatusUpdated,
//            &m_setupTab, &SetupTab::onStatusUpdated);
}

void SetupViewManager::WireButtons()
{
    connect(&m_setupTab, &SetupTab::NotifyConnectClicked,
            &m_instrument, &Instrument::Connect);
    connect(&m_instrument, &Instrument::NotifyConnected,
            &m_setupTab, &SetupTab::onConnected);

    connect(&m_setupTab, &SetupTab::NotifyDisconnectClicked,
            &m_instrument, &Instrument::Disconnect);
    connect(&m_instrument, &Instrument::NotifyDisconnected,
            &m_setupTab, &SetupTab::onDisconnected);

    connect(&m_setupTab, &SetupTab::NotifySendClicked,
            &m_instrument, &Instrument::onSendRequest);
    connect(&m_setupTab, &SetupTab::NotifyReceiveClicked,
            &m_instrument, &Instrument::onReceiveRequest);

    connect(&m_instrument, &Instrument::NotifyDataReceived,
            &m_setupTab, &SetupTab::onDataReceived);
}

} // namespace
