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
}

SetupViewManager::~SetupViewManager()
{
  Utils::DestructorMsg(this);
}

} // namespace
