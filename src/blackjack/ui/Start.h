#pragma once

#include <QMainWindow>

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

private slots:
    void OnAnimFinished();

private:
    Ui::Start* m_ui;
};
