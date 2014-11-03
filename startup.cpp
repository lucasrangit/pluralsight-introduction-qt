#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "utils.h"
#include "Model/settings.h"
#include "Model/provider.h"
#include "Model/instsocket.h"
#include "Model/instrument.h"


namespace Ps {

Startup::Startup() :
    QObject(NULL),
    m_setupTab(*new SetupTab(NULL)),
    m_mainView(*new MainView(NULL, m_setupTab)),
    m_instrument(new Instrument(this,
                                *new InstSocket(this)))
{
    // FIXME remove when done testing
    Settings& my_settings = Provider::GetSettingsAsSingleton();
    my_settings.ParseJsonData();
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
