#pragma once
#include <QWidget>

namespace Ps{

class Utils
{
public:
    Utils();

  static void DestructorMsg(const QString& value);
  static void DestructorMsg(const QObject * const object);

private:
  // singleton
  explicit Utils(const Utils& rhs);
  Utils& operator= (const Utils& rhs);
};

} // namespace
