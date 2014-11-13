#pragma once
#include <memory>

namespace Ps{

class Settings;

class Provider
{
public:
    Provider();
    static Settings& GetSettingsAsSingleton();

private:
    explicit Provider(const Provider& rhs);
    Provider& operator= (const Provider& rhs);
};

} // namespace



