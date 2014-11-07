#include <QDebug>
#include "controltab.h"
#include "ui_controltab.h"
#include "utils.h"

namespace Ps {

ControlTab::ControlTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ControlTab)
{
    ui->setupUi(this);
}

ControlTab::~ControlTab()
{
    Utils::DestructorMsg(this);
    delete ui;
}

void ControlTab::onControlTabEnabled(bool isEnabled)
{
    // TODO
    qDebug() << "control tab enabled slot called with" << isEnabled;
}

void ControlTab::on_dsbPulseWidth_valueChanged(double arg1)
{
   emit NotifyPulseWidthChanged(arg1);
}

} // namespace

