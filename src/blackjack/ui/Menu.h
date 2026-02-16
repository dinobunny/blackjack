#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Menu;
}
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget* parent = nullptr);
    ~Menu();

    void goStyle();
    void goPlay();


private slots:
    void on_btnStyle_clicked();

    void on_btnPlay_clicked();

private:
    Ui::Menu* ui;
};
