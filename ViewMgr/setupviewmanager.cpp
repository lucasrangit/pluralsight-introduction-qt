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

} // namespace
