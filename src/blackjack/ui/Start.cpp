#include "Start.h"
#include "ui_Start.h"
#include "Menu.h"

#include "utils/Navigation.h"
#include "animation/animation.h"

Start::Start(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);

    QPixmap bg(blackjack::kStartBackgroundPath);
    ui->label->setPixmap(bg);

    auto* animator = new blackjack::Animator(this);
    QLabel* chip = animator->CreateChip(this);

    connect(animator, &blackjack::Animator::Finished, this, &Start::OnAnimFinished);
    animator->AnimateMove(chip, QPoint(200, 400), QPoint(1000, 600), 4000);
}

Start::~Start()
{
    delete ui;
}

void Start::OnAnimFinished()
{
    blackjack::NavigateTo<Menu>(this);
}
