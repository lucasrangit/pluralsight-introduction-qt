#pragma once
#include <QObject>

namespace Ps{

class MainView;
class SetupTab;

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

    // singleton
    explicit Startup(const Startup& rhs);
    Startup& operator= (const Startup& rhs);
};
}



