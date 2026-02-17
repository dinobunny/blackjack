
#include "Play.h"
#include "Menu.h"
#include "ui_Play.h"
#include "utils/DeckStyle.h"
#include <utils/Navigation.h>
#include <utils/Config_Constants.h>

#define NOMINMAX
#include "audio/PlaySound.h"

using namespace blackjack;

#pragma region Constructors

Play::Play(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Play)
{
    m_ui->setupUi(this);
    PlaySoundNew(kBackgroundMusicSound, true);

    InitAnimator();
    InitLabels();
    InitChipConnections();
    InitDeckBack();

    SetBettingUi();
}

Play::~Play()
{
    delete m_ui;
}

#pragma endregion

#pragma region Betting
void Play::ApplyChip(GameRules::Bet bet, const QString& chipPath)
{
    m_balance.setBet(bet);

    QPixmap chipPix(chipPath);
    m_ui->labelSelectedBet->setPixmap(chipPix);
    m_ui->btnDeal->setEnabled(true);
}

void Play::OnChip5()
{
    ApplyChip(GameRules::Bet::Five, kChipBlackWhitePath);
}

void Play::OnChip10()
{
    ApplyChip(GameRules::Bet::Ten, kChipRedWhitePath);
}

void Play::OnChip25()
{
    ApplyChip(GameRules::Bet::TwentyFive, kChipGreenWhitePath);
}

void Play::OnChip50()
{
    ApplyChip(GameRules::Bet::Fifty, kChipBlueWhitePath);
}

void Play::SetBettingUi()
{
    if (m_balance.GetBalance() < static_cast<int>(GameRules::Bet::Five))
    {
        NavigateTo<Menu>(this, true);
    }

    m_ui->btnChip5->setEnabled(m_balance.GetBalance() >= static_cast<int>(GameRules::Bet::Five));
    m_ui->btnChip10->setEnabled(m_balance.GetBalance() >= static_cast<int>(GameRules::Bet::Ten));
    m_ui->btnChip25->setEnabled(m_balance.GetBalance() >= static_cast<int>(GameRules::Bet::TwentyFive));
    m_ui->btnChip50->setEnabled(m_balance.GetBalance() >= static_cast<int>(GameRules::Bet::Fifty));

    m_ui->labelBalance->setText("Balance: " + QString::number(m_balance.GetBalance()));

    if (m_balance.GetBet() == 0)
    {
        m_ui->btnReapet->hide();
        m_ui->btnClear->setEnabled(false);
        m_ui->btnDeal->show();
        m_ui->btnDeal->setEnabled(false);
    }
    else
    {
        m_ui->btnReapet->show();
        m_ui->btnClear->show();
        m_ui->btnDeal->hide();
    }

    m_ui->btnHit->hide();
    m_ui->btnStand->hide();

    m_ui->labelBalance->setText("Balance: " + QString::number(m_balance.GetBalance()));

    m_ui->btnDeal->setEnabled(m_balance.GetBet() > 0);
    m_ui->btnClear->setEnabled(m_balance.GetBet() > 0);
}

void Play::SetPlayingUi()
{
    m_ui->btnDeal->hide();
    m_ui->btnClear->hide();
    m_ui->btnReapet->hide();

    m_ui->labelBet->setText("Bet: " + QString::number(m_balance.GetBet()));
    m_ui->labelBalance->setText("Balance: " + QString::number(m_balance.GetBalance()));

    m_ui->btnHit->show();
    m_ui->btnStand->show();

    m_ui->btnChip5->setEnabled(false);
    m_ui->btnChip10->setEnabled(false);
    m_ui->btnChip25->setEnabled(false);
    m_ui->btnChip50->setEnabled(false);
}

#pragma endregion

#pragma region Button
void Play::StartRound()
{
    SetPlayingUi();
    ClearHandsUi();
    m_game.startRound();

    PlaySoundNew(kClickSound, true);

    renderDealerHand(true);
    PlaySoundNew(kDealingSound, true);

    renderPlayerHand();
    PlaySoundNew(kDealingSound, true);

    if (m_game.isRoundComplete())
        applyOutcome(m_game.getOutcome());
}

void Play::on_btnStand_clicked()
{
    if (m_game.isRoundComplete())
        return;

    PlaySoundNew(kClickSound, true);
    m_game.stand();

    renderDealerHand(false);
    renderPlayerHand();

    const auto outcome = m_game.getOutcome();
    applyOutcome(outcome);
}
void Play::on_btnBackMenu_clicked()
{
    NavigateTo<Menu>(this);
}
void Play::on_btnReapet_clicked()
{
    if (m_balance.GetBet() <= 0)
        return;

    StartRound();
}
void Play::on_btnClear_clicked()
{
    PlaySoundNew(kClickSound, true);
    m_balance.resetBet();
    m_ui->btnReapet->hide();
    m_ui->btnDeal->show();
}
void Play::on_btnHit_clicked()
{
    if (!m_game.hit())
        return;
    PlaySoundNew(kClickSound, true);

    renderPlayerHand();
    PlaySoundNew(kDealingSound, true);

    if (m_game.isRoundComplete())
    {
        renderDealerHand(false);
        const auto outcome = m_game.getOutcome();
        applyOutcome(outcome);
    }
}
void Play::on_btnDeal_clicked()
{
    if (m_balance.GetBet() <= 0)
        return;

    StartRound();
}
#pragma endregion

#pragma region Rendering

void Play::ClearHandsUi()
{
    for (auto* l : m_playerLabels)
        l->clear();

    for (auto* l : m_dealerLabels)
        l->clear();
}

void Play::renderHand(const Hand& hand, const std::vector<QLabel*>& labels)
{
    constexpr size_t LAST = 1;

    const auto& cards = hand.getCards();
    const size_t count = std::min(cards.size(), labels.size());

    for (size_t i = count; i < labels.size(); ++i)
        labels [i]->clear();

    for (size_t i = 0; i < count; ++i)
    {
        QPixmap px(DeckSettings::BuildCardPath(cards [i]));
        if (px.isNull())
            continue;

        const bool isLast = (i == count - LAST);

        if (isLast && labels [i]->pixmap().isNull())
        {
            QLabel* flying = m_animator->CreateCenteredCard(this, m_ui->label_deck, px);
            m_animator->AnimateCardTo(flying, labels [i]);
        }
        else
        {
            labels [i]->setPixmap(px);
        }
    }
}

void Play::renderDealerHand(bool hideHoleCard)
{
    const auto dealer = m_game.getDealerHand(hideHoleCard);
    renderHand(dealer, m_dealerLabels);

    m_ui->label_15->setText(
        "Dealer: " + QString::number(dealer.getTotal()));
}

void Play::renderPlayerHand()
{
    const auto& player = m_game.getPlayerHand();
    renderHand(player, m_playerLabels);

    m_ui->label_14->setText(
        "Player: " + QString::number(player.getTotal()));
}

void Play::applyOutcome(Outcome outcome)
{
    const int bet = m_balance.GetBet();
    const int payout = static_cast<int>(bet * m_rules.blackjackPayout);

    switch (outcome)
    {
    case Outcome::PUSH:
        break;

    case Outcome::PLAYER_BLACKJACK:
        m_balance.win(bet + payout);
        break;

    case Outcome::PLAYER_WIN:
    case Outcome::DEALER_BUST:
        m_balance.win(bet);
        break;

    default:
        m_balance.lose();
        break;
    }

    m_ui->labelBalance->setText("Balance: " + QString::number(m_balance.GetBalance()));
    SetBettingUi();
}

#pragma endregion

#pragma region Play Init

void Play::InitLabels()
{
    m_playerLabels = {
        m_ui->player_1,
        m_ui->player_2,
        m_ui->player_3,
        m_ui->player_4,
        m_ui->player_5,
        m_ui->player_6
    };

    m_dealerLabels = {
        m_ui->dealer_1,
        m_ui->dealer_2,
        m_ui->dealer_3,
        m_ui->dealer_4,
        m_ui->dealer_5,
        m_ui->dealer_6
    };
}

void Play::InitChipConnections()
{
    connect(m_ui->btnChip5, &QPushButton::clicked, this, &Play::OnChip5);
    connect(m_ui->btnChip10, &QPushButton::clicked, this, &Play::OnChip10);
    connect(m_ui->btnChip25, &QPushButton::clicked, this, &Play::OnChip25);
    connect(m_ui->btnChip50, &QPushButton::clicked, this, &Play::OnChip50);
}

void Play::InitDeckBack()
{
    QString path = DeckSettings::getCardsPath() + "cardBack_red1.png";
    m_ui->label_deck->setPixmap(QPixmap(path));
}

void Play::InitAnimator()
{
    m_animator = new Animator(this);
}

#pragma endregion
