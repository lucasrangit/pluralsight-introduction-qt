#ifndef CONTROLTAB_H
#define CONTROLTAB_H

#include <QWidget>

namespace Ui {
class ControlTab;
}

namespace Ps {

class ControlTab : public QWidget
{
    Q_OBJECT

public:
    explicit ControlTab(QWidget *parent = 0);
    ~ControlTab();

public slots:
    void onControlTabEnabled(bool isEnabled);

private:
    Ui::ControlTab *ui;
};

} // namespace

#endif // CONTROLTAB_H
