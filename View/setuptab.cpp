#include "setuptab.h"
#include "ui_setuptab.h"
#include "utils.h"

namespace Ps {

SetupTab::SetupTab(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SetupTab)
{
    ui->setupUi(this);
}

SetupTab::~SetupTab()
{
    Utils::DestructorMsg(this);
    delete ui;
}

} // namespace
