#pragma once
#include <QObject>
#include "Model/instrument.h"

namespace Ps{

class MainView;
class SetupTab;
class ControlTab;
class Instrument;
class SetupViewManager;
class ControlTabViewManager;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    SetupTab& m_setupTab;
    ControlTab& m_controlTab;
    MainView& m_mainView;
    Instrument* m_instrument;
    SetupViewManager *m_setupVm;
    ControlTabViewManager *m_controlVm;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);
};
}



