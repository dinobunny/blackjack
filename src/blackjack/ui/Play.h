#pragma once
#include <QMainWindow>
#include "core\Balance.hpp"
#include <QLabel>
#include <core\GameRules.hpp>
#include <core\BlackjackGame.hpp>

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

    void on_btnStand_clicked();

    void on_btnReapet_clicked();

    void OnChip5();
    void OnChip10();
    void OnChip25();
    void OnChip50();

    void on_btnClear_clicked();

    void on_btnHit_clicked();

    void ClearHandsUi();

    QLabel* CreateFlyingCard(const QPixmap& px);

    void AnimateCardTo(QLabel* flying, QLabel* target);

    void renderHand(const blackjack::Hand& hand, const std::vector<QLabel*>& labels);

    void renderDealerHand(bool hideHoleCard);

    void renderPlayerHand();

    void applyOutcome(blackjack::Outcome outcome);

private:
    void SetBettingUi();
    void SetPlayingUi();

private:
    Ui::Play* ui;
    Balance balance;

    blackjack::BlackjackGame game_;
    blackjack::GameRules rules;
    std::vector<QLabel*> playerLabels_;
    std::vector<QLabel*> dealerLabels_;

};
