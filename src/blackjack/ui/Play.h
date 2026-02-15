#pragma once
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
    class Play;
}
QT_END_NAMESPACE

class Play : public QMainWindow
{
    Q_OBJECT

public:
    Play(QWidget* parent = nullptr);
    ~Play();

    void back();

private slots:
    void on_btnBackMenu_clicked();
    void on_btnDeal_clicked();

    void OnChip5();
    void OnChip10();
    void OnChip25();
    void OnChip50();

private:
    void SetBettingUi();
    void SetPlayingUi();

private:
    Ui::Play* ui;
    int m_selectedBet = 0;
};
