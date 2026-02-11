#pragma once
#include <QMainWindow>
#include <QLabel>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Start;
}
QT_END_NAMESPACE

class Start : public QMainWindow
{
    Q_OBJECT

public:
    Start(QWidget* parent = nullptr);
    ~Start();

private:
    QLabel* CreateChip();
    void AnimateChip(QLabel* );
    Ui::Start* ui;
};
