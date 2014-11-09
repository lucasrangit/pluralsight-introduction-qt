#include "mainview.h"
#include "ui_mainview.h"
#include "View/setuptab.h"
#include "View/controltab.h"
#include "utils.h"

namespace Ps {

MainView::MainView(QWidget *parent,
                   SetupTab &setup,
                   ControlTab &control) :
    QMainWindow(parent),
    m_setupTab(setup),
    m_controlTab(control),
    ui(new Ui::MainView)
{
    ui->setupUi(this);

    m_setupTab.setParent(this);
    ui->loSetupTab->addWidget(&m_setupTab);

    m_controlTab.setParent(this);
    ui->loControlTab->addWidget(&m_controlTab);
}

MainView::~MainView()
{
    Utils::DestructorMsg(this);
    delete ui;
}

void MainView::on_action_Exit_triggered()
{
   QApplication::quit();
}

void MainView::on_action_About_triggered()
{
    // TODO show about dialog
}

} // namespace
