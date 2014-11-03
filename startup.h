#pragma once
#include <QObject>
#include "Model/instrument.h"

namespace Ps{

class MainView;
class SetupTab;
class Instrument;

class Startup : public QObject
{
    Q_OBJECT
public:
    explicit Startup();
    void show() const;
    ~Startup();

private:
    SetupTab& m_setupTab;
    MainView& m_mainView;
    Instrument* m_instrument;

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);
};
}



