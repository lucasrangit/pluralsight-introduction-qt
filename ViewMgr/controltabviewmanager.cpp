#include "controltabviewmanager.h"
#include "View/controltab.h"


namespace Ps
{
ControlTabViewManager::ControlTabViewManager(QObject *parent,
                                             ControlTab& control) :
    QObject(parent),
    m_controlTab(control)
{
}
}
