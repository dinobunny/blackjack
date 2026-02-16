#include "Play.h"
#include "Menu.h"
#include "ui_Play.h"
#include "DeckStyle.h"
#include <format>

Play::Play(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Play)
{
    ui->setupUi(this);

    connect(ui->btnChip5, &QPushButton::clicked, this, &Play::OnChip5);
    connect(ui->btnChip10, &QPushButton::clicked, this, &Play::OnChip10);
    connect(ui->btnChip25, &QPushButton::clicked, this, &Play::OnChip25);
    connect(ui->btnChip50, &QPushButton::clicked, this, &Play::OnChip50);
    
    QString path = QString("%1%2")
        .arg((blackjack::DeckSettings::getCardsPath()))
        .arg("cardBack_red1.png");

    QPixmap bg(path);
    ui->label_deck->setPixmap(bg);


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

void Play::on_btnBackMenu_clicked()
{
    back();
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

    ui->labelBet->setText("Bet: " + QString::number(balance.GetBet()));
    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance() - balance.GetBet()));

    ui->btnHit->show();
    ui->btnStand->show();

    ui->btnChip5->setEnabled(false);
    ui->btnChip10->setEnabled(false);
    ui->btnChip25->setEnabled(false);
    ui->btnChip50->setEnabled(false);
}

void Play::on_btnDeal_clicked()
{
    SetPlayingUi();
}

void Play::on_btnClear_clicked()
{
    balance.resetBet();
    ui->btnReapet->hide();
    ui->btnDeal->show();
}

