#pragma once
#include <QObject>

namespace Ps
{

class ControlTab;
class Instrument;

class ControlTabViewManager : public QObject
{
    Q_OBJECT
public:
    explicit ControlTabViewManager(QObject *parent, ControlTab& control, Instrument &instrument);
    ~ControlTabViewManager();

public slots:
    void onConnected();
    void onDisconnected();

private:
    ControlTab& m_controlTab;
    Instrument& m_instrument;

    explicit ControlTabViewManager(const ControlTabViewManager& rhs);
    ControlTabViewManager& operator= (const ControlTabViewManager& rhs);
    void WireControls();
    void WireConnected();
};

}



