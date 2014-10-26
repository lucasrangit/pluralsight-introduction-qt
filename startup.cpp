#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "utils.h"
#include "Model/settings.h"

namespace Ps {

Startup::Startup() :
    QObject(NULL),
    m_setupTab(*new SetupTab(NULL)),
    m_mainView(*new MainView(NULL, m_setupTab))
{
    // FIXME remove when done testing
    Settings my_settings(this, "settings.json");
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
