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

void SetupTab::SetCommands(QStringListModel &commands)
{
    ui->cmbCommands->setModel(&commands);
}

void SetupTab::onStatusUpdated(const QString &statusMsg)
{
    ui->editInstMsgs->append(statusMsg);
}

void SetupTab::onConnected()
{
    ui->editInstMsgs->append(tr("Connected"));
}

void SetupTab::onDisconnected()
{
    ui->editInstMsgs->append(tr("Disconnected"));
}

void SetupTab::onDataSent(const QString &dataSent)
{
    ui->editInstMsgs->append("Data sent: " + dataSent);
}

void SetupTab::onDataReceived(const QString &dataReceived)
{
    ui->editInstMsgs->append("Data received: " + dataReceived);
}

void SetupTab::onConnectEnabled(bool isEnabled)
{
   ui->btnConnect->setEnabled(isEnabled);
}

void SetupTab::onDisconnectEnabled(bool isEnabled)
{
    ui->btnDisconnect->setEnabled(isEnabled);
}

void SetupTab::onDirectCommandsEnabled(bool isEnabled)
{
    ui->cmbCommands->setEnabled(isEnabled);
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

void SetupTab::on_btnConnect_clicked()
{
    emit NotifyConnectClicked();
}

void SetupTab::on_btnDisconnect_clicked()
{
    emit NotifyDisconnectClicked();
}

void SetupTab::on_pbSend_clicked()
{
    emit NotifySendClicked(ui->cmbCommands->currentText());
}

void SetupTab::on_pbReceive_clicked()
{
    emit NotifyReceiveClicked();
}

void SetupTab::on_pbClear_clicked()
{
   ui->editInstMsgs->clear();
}


} // namespace
