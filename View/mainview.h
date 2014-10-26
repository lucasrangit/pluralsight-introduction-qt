#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>

namespace Ui {
class MainView;
}

namespace Ps {

class SetupTab;

class MainView : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainView(QWidget *parent, SetupTab& setup);
    ~MainView();

private:
    SetupTab& m_setupTab;
    Ui::MainView *ui;
};

}

#endif // MAINVIEW_H
