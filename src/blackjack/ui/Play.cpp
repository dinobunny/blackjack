#include "Play.h"
#include "Menu.h"
#include "ui_Play.h"


Play::Play(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Play)
{
    ui->setupUi(this);

    connect(ui->btnChip5, &QPushButton::clicked, this, &Play::OnChip5);
    connect(ui->btnChip10, &QPushButton::clicked, this, &Play::OnChip10);
    connect(ui->btnChip25, &QPushButton::clicked, this, &Play::OnChip25);
    connect(ui->btnChip50, &QPushButton::clicked, this, &Play::OnChip50);

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
    balance.SetBet(5);

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip10()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipRedWhite.png)");

    balance.SetBet(10);
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip25()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipGreenWhite.png)");

    balance.SetBet(25);
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip50()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipBlueWhite.png)");

    balance.SetBet(50);

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::SetBettingUi()
{
    if (balance.GetBalance() < 5)
    {
        back();
    }

    ui->btnChip10->setEnabled(balance.GetBalance() >= 10);
    ui->btnChip25->setEnabled(balance.GetBalance() >= 25);
    ui->btnChip50->setEnabled(balance.GetBalance() >= 50);

    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));

    ui->btnDeal->show();
    ui->btnDeal->setEnabled(false);

    ui->btnHit->hide();
    ui->btnStand->hide();

    ui->labelBalance->setText("Balance: " + QString::number(balance.GetBalance()));

    balance.SetBet(0);
    ui->labelSelectedBet->setText("0");
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
    balance.ResetBet();
}

