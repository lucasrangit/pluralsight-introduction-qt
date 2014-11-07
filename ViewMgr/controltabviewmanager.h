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
    explicit ControlTabViewManager(QObject *parent, ControlTab& control);

private:
    ControlTab& m_controlTab;

    explicit ControlTabViewManager(const ControlTabViewManager& rhs);
    ControlTabViewManager& operator= (const ControlTabViewManager& rhs);
};
}



