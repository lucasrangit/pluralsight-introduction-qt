#include "controltabviewmanager.h"
#include "Model/instrument.h"
#include "View/controltab.h"
#include "utils.h"

namespace Ps
{

ControlTabViewManager::ControlTabViewManager(QObject *parent,
                                             ControlTab& control,
                                             Instrument& instrument) :
    QObject(parent),
    m_controlTab(control),
    m_instrument(instrument)
{
    WireControls();

    WireConnected();
}

ControlTabViewManager::~ControlTabViewManager()
{
    Utils::DestructorMsg(this);
}

void ControlTabViewManager::onConnected()
{
    m_controlTab.EnablePanel(true);
}

void ControlTabViewManager::onDisconnected()
{
    m_controlTab.EnablePanel(false);
}

void ControlTabViewManager::WireControls()
{
    connect(&m_controlTab, &ControlTab::NotifyPulseWidthChanged,
            &m_instrument, &Instrument::onPulseWidthChanged);

}

void ControlTabViewManager::WireConnected()
{
    connect(&m_instrument, &Instrument::NotifyConnected,
            this, &ControlTabViewManager::onConnected);
    connect(&m_instrument, &Instrument::NotifyDisconnected,
            this, &ControlTabViewManager::onDisconnected);
}

}
