#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

namespace Ps {

class SetupTab;
class ControlTab;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent, SetupTab& setup, ControlTab& control);
    ~MainView();

private:
    SetupTab& m_setupTab;
    ControlTab& m_controlTab;
    Ui::MainView *ui;
};

}

#endif // MAINVIEW_H
