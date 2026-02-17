#include "Play.h"
#include "Menu.h"
#include "ui_Play.h"
#include "utils/DeckStyle.h"
#include <QPropertyAnimation>

#define NOMINMAX
#include "../audio/PlaySound.h"

Play::Play(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Play)
{
    ui->setupUi(this);

    PlaySoundNew(LR"(audio/background_Music.mp3)", true);

    playerLabels_ = { ui->player_1, ui->player_2, ui->player_3, ui->player_4, ui->player_5, ui->player_6 };
    dealerLabels_ = { ui->dealer_1, ui->dealer_2, ui->dealer_3, ui->dealer_4, ui->dealer_5, ui->dealer_6 };

    connect(ui->btnChip5, &QPushButton::clicked, this, &Play::OnChip5);
    connect(ui->btnChip10, &QPushButton::clicked, this, &Play::OnChip10);
    connect(ui->btnChip25, &QPushButton::clicked, this, &Play::OnChip25);
    connect(ui->btnChip50, &QPushButton::clicked, this, &Play::OnChip50);

    QString path = blackjack::DeckSettings::getCardsPath() + "cardBack_red1.png";
    ui->label_deck->setPixmap(QPixmap(path));

    SetBettingUi();
}

Play::~Play()
{
    delete ui;
}

void Play::back()
{
    auto* menu = new Menu();
    menu->show();

    setAttribute(Qt::WA_DeleteOnClose);
    this->close();
}


void Play::OnChip5()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipBlackWhite.png)");
    balance.setBet(blackjack::GameRules::Bet::Five);

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip10()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipRedWhite.png)");

    balance.setBet(blackjack::GameRules::Bet::Ten);
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip25()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipGreenWhite.png)");

    balance.setBet(blackjack::GameRules::Bet::TwentyFive);
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip50()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipBlueWhite.png)");

    balance.setBet(blackjack::GameRules::Bet::Fifty);

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::SetBettingUi()
{
    if (balance.GetBalance() < static_cast<int>(blackjack::GameRules::Bet::Five))
    {
        back();
    }

    ui->btnChip5->setEnabled(balance.GetBalance() >= static_cast<int>(blackjack::GameRules::Bet::Five));
    ui->btnChip10->setEnabled(balance.GetBalance() >= static_cast<int>(blackjack::GameRules::Bet::Ten));
    ui->btnChip25->setEnabled(balance.GetBalance() >= static_cast<int>(blackjack::GameRules::Bet::TwentyFive));
    ui->btnChip50->setEnabled(balance.GetBalance() >= static_cast<int>(blackjack::GameRules::Bet::Fifty));

    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));

    if (balance.GetBet() == 0)
    {
        ui->btnReapet->hide();
        ui->btnClear->setEnabled(false);
        ui->btnDeal->show();
        ui->btnDeal->setEnabled(false);
    }
    else
    {
        ui->btnReapet->show();
        ui->btnClear->show();
        ui->btnDeal->hide();
    }

    ui->btnHit->hide();
    ui->btnStand->hide();

    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));

    ui->btnDeal->setEnabled(balance.GetBet() > 0);
    ui->btnClear->setEnabled(balance.GetBet() > 0);
}

void Play::SetPlayingUi()
{
    ui->btnDeal->hide();
    ui->btnClear->hide();
    ui->btnReapet->hide();

    ui->labelBet->setText("Bet: " + QString::number(balance.GetBet()));
    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));

    ui->btnHit->show();
    ui->btnStand->show();

    ui->btnChip5->setEnabled(false);
    ui->btnChip10->setEnabled(false);
    ui->btnChip25->setEnabled(false);
    ui->btnChip50->setEnabled(false);
}


void Play::on_btnBackMenu_clicked()
{
    back();
}

void Play::on_btnStand_clicked()
{
    if (game_.isRoundComplete())
        return;

    PlaySoundNew(LR"(assets\music\click.mp3)", true);
    game_.stand();

    renderDealerHand(false);
    renderPlayerHand();

    const auto outcome = game_.getOutcome();
    applyOutcome(outcome);
}
void Play::on_btnReapet_clicked()
{
    if (balance.GetBet() <= 0)
        return;

    SetPlayingUi();
    ClearHandsUi();
    game_.startRound();
    PlaySoundNew(LR"(audio\click.mp3)", true);

    renderDealerHand(true);
    PlaySoundNew(LR"(audio\dealing.mp3)", true);
    renderPlayerHand();
    PlaySoundNew(LR"(audio\dealing.mp3)", true);

    if (game_.isRoundComplete())
        applyOutcome(game_.getOutcome());
}
void Play::on_btnClear_clicked()
{
    PlaySoundNew(LR"(audio\click.mp3)", true);
    balance.resetBet();
    ui->btnReapet->hide();
    ui->btnDeal->show();
}
void Play::on_btnHit_clicked()
{
    if (!game_.hit())
        return;
    PlaySoundNew(LR"(audio\click.mp3)", true);

    renderPlayerHand();
    PlaySoundNew(LR"(audio\dealing.mp3)", true);

    if (game_.isRoundComplete())
    {
        renderDealerHand(false);
        const auto outcome = game_.getOutcome();
        applyOutcome(outcome);
    }
}
void Play::on_btnDeal_clicked()
{
    if (balance.GetBet() <= 0)
        return;

    SetPlayingUi();
    ClearHandsUi();
    game_.startRound();

    PlaySoundNew(LR"(audio\click.mp3)", true);

    renderDealerHand(true);
    PlaySoundNew(LR"(audio\dealing.mp3)", true);
    renderPlayerHand();
    PlaySoundNew(LR"(audio\dealing.mp3)", true);

    if (game_.isRoundComplete())
        applyOutcome(game_.getOutcome());
}

QLabel* Play::CreateFlyingCard(const QPixmap& px)
{
    auto* card = new QLabel(this);
    card->setPixmap(px);
    card->resize(px.size());

    const QPoint start = ui->label_deck->mapTo(this, QPoint(0, 0));
    const int offsetX = (ui->label_deck->width() - card->width()) / 2;
    const int offsetY = (ui->label_deck->height() - card->height()) / 2;
    const QPoint centered = start + QPoint(offsetX, offsetY);

    card->move(centered);
    card->show();
    card->raise();

    return card;
}

void Play::AnimateCardTo(QLabel* flying, QLabel* target)
{
    const QPoint end = target->mapTo(this, QPoint(0, 0));

    auto* anim = new QPropertyAnimation(flying, "pos", this);
    anim->setDuration(250);
    anim->setStartValue(flying->pos());
    anim->setEndValue(end);
    anim->setEasingCurve(QEasingCurve::OutCubic);

    connect(anim, &QPropertyAnimation::finished, this, [=] ()
            {
                target->setPixmap(flying->pixmap());
                flying->deleteLater();
            });

    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void Play::ClearHandsUi()
{
    for (auto* l : playerLabels_)
        l->clear();

    for (auto* l : dealerLabels_)
        l->clear();
}
void Play::renderHand(const blackjack::Hand& hand,
                      const std::vector<QLabel*>& labels)
{
    constexpr size_t LAST = 1;

    const auto& cards = hand.getCards();
    const size_t count = std::min(cards.size(), labels.size());

    for (size_t i = count; i < labels.size(); ++i)
        labels [i]->clear();

    for (size_t i = 0; i < count; ++i)
    {
        QPixmap px(blackjack::DeckSettings::BuildCardPath(cards [i]));
        if (px.isNull())
            continue;

        const bool isLast = (i == count - LAST);

        if (isLast && labels [i]->pixmap().isNull())
        {
            AnimateCardTo(CreateFlyingCard(px), labels [i]);
        }
        else
        {
            labels [i]->setPixmap(px);
        }
    }
}
void Play::renderDealerHand(bool hideHoleCard)
{
    const auto dealer = game_.getDealerHand(hideHoleCard);
    renderHand(dealer, dealerLabels_);

    ui->label_15->setText(
        "Dealer: " + QString::number(dealer.getTotal()));
}
void Play::renderPlayerHand()
{
    const auto& player = game_.getPlayerHand();
    renderHand(player, playerLabels_);

    ui->label_14->setText(
        "Player: " + QString::number(player.getTotal()));
}

void Play::applyOutcome(blackjack::Outcome outcome)
{
    const int bet = balance.GetBet();
    const int payout = static_cast<int>(bet * rules.blackjackPayout);

    switch (outcome)
    {
    case blackjack::Outcome::PUSH:
        break;

    case blackjack::Outcome::PLAYER_BLACKJACK:
        balance.win(bet + payout);
        break;

    case blackjack::Outcome::PLAYER_WIN:
    case blackjack::Outcome::DEALER_BUST:
        balance.win(bet);
        break;

    default:
        balance.lose();
        break;
    }

    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));
    SetBettingUi();
}
