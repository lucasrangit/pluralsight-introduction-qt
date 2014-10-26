#include "startup.h"
#include "View/mainview.h"
#include "View/setuptab.h"
#include "utils.h"
#include "Model/settings.h"

namespace Ps {

Startup::Startup() :
    QObject(nullptr),
    m_setupTab(*new SetupTab(nullptr)),
    m_mainView(*new MainView(nullptr, m_setupTab))
{
    Settings my_settings(this, "settings.json");
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
