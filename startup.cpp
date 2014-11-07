#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "utils.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instsocket.h"
#include "Model/instrument.h"
#include "ViewMgr/setupviewmanager.h"
#include "ViewMgr/controltabviewmanager.h"

namespace Ps {

Startup::Startup() :
    QObject(NULL),
    m_setupTab(*new SetupTab(NULL)),
    m_controlTab(*new ControlTab(NULL)),
    m_mainView(*new MainView(NULL,
                             m_setupTab,
                             m_controlTab)),
    m_instrument(new Instrument(this,
                                *new InstSocket(this),
                                Provider::GetSettingsAsSingleton())),
    m_setupVm(new SetupViewManager(this,
                                   m_setupTab,
                                   m_controlTab,
                                   *m_instrument,
                                   Provider::GetSettingsAsSingleton())),
    m_controlVm(new ControlTabViewManager(this,
                                          m_controlTab))
{
}

Startup::~Startup()
{
    Utils::DestructorMsg(this);
    delete &m_mainView;
}

void Startup::show() const
{
    m_mainView.show();
}

} // namespace
