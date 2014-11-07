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

signals:
    void NotifyPulseWidthChanged(double value);

public slots:
    void onControlTabEnabled(bool isEnabled);

private slots:
    void on_dsbPulseWidth_valueChanged(double arg1);

private:
    Ui::ControlTab *ui;
};

} // namespace

#endif // CONTROLTAB_H
