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
    m_selectedBet = 5;

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip10()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipRedWhite.png)");
    
    m_selectedBet = 10;
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip25()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipGreenWhite.png)");

    m_selectedBet = 25;
    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::OnChip50()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipBlueWhite.png)");

    m_selectedBet = 50;

    ui->labelSelectedBet->setPixmap(chipPix);
    ui->btnDeal->setEnabled(true);
}

void Play::SetBettingUi()
{
    ui->btnDeal->show();
    ui->btnDeal->setEnabled(false);

    ui->btnHit->hide();
    ui->btnStand->hide();

    ui->btnChip5->setEnabled(true);
    ui->btnChip10->setEnabled(true);
    ui->btnChip25->setEnabled(true);
    ui->btnChip50->setEnabled(true);

    m_selectedBet = 0;
    ui->labelSelectedBet->setText("0");
}

void Play::SetPlayingUi()
{
    ui->btnDeal->hide();
    ui->labelBet->setText("Bet: " + QString::number(m_selectedBet));
    ui->labelBalance->setText("Balance: " + QString::number(100 - m_selectedBet));

    ui->btnHit->show();
    ui->btnStand->show();

    ui->btnChip5->setEnabled(false);
    ui->btnChip10->setEnabled(false);
    ui->btnChip25->setEnabled(false);
    ui->btnChip50->setEnabled(false);
}

void Play::on_btnDeal_clicked()
{
    if (m_selectedBet <= 0)
        return;

    SetPlayingUi();
}
