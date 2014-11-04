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

void SetupTab::SetHostName(const QString& value)
{
    ui->editIpAddress->setText(value);
    emit NotifyHostNameChanged(value);
}

void SetupTab::SetPort(quint16 value)
{
    ui->editPort->setText(QString::number(value));
    emit NotifyPortChanged(value);
}

void SetupTab::onStatusUpdated(const QString &statusMsg)
{
    ui->editInstMsgs->append(statusMsg);
}

void SetupTab::on_editIpAddress_editingFinished()
{
  emit NotifyHostNameChanged(ui->editIpAddress->text());
}

void SetupTab::on_editPort_editingFinished()
{
    bool ok;
    int result = ui->editPort->text().toInt(&ok);
    if (!ok || (result > USHRT_MAX))
    {
        ui->editInstMsgs->append(tr("Invalid port number: " + result));
    }
    else
    {
        emit NotifyPortChanged(result);
    }
}


} // namespace
