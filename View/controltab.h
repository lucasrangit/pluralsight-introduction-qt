#pragma once
#include <QWidget>

namespace Ps{
class ControlTab : public QWidget
{
    Q_OBJECT
public:
    explicit ControlTab(QWidget *parent=0);

private:


    explicit ControlTab(const ControlTab& rhs);
    ControlTab& operator= (const ControlTab& rhs);
};
}



