#pragma once
#include <QObject>

namespace Ps
{

class SetupTab;
class Instrument;
class Settings;

class SetupViewManager : public QObject
{
    Q_OBJECT
public:
    explicit SetupViewManager(QObject *parent,
                              SetupTab& tab,
                              Instrument& inst,
                              Settings& config);

    ~SetupViewManager();

private:
    SetupTab& m_setupTab;
    Instrument& m_instrument;

    void WireSettings(Settings &config);
    void WireHostAndPort();
    void WireMessages();
    void WireButtons();

    explicit SetupViewManager(const SetupViewManager& rhs);
    SetupViewManager& operator= (const SetupViewManager& rhs);
};

} // namespace

