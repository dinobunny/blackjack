#include "Start.h"
#include "ui_Start.h"
#include "Menu.h"

#include "utils/Navigation.h"
#include "animation/animation.h"

Start::Start(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Start)
{
    m_ui->setupUi(this);

    QPixmap bg(blackjack::kStartBackgroundPath);
    m_ui->label->setPixmap(bg);

    auto* animator = new blackjack::Animator(this);
    QLabel* chip = animator->CreateChip(this);

    connect(animator, &blackjack::Animator::Finished, this, &Start::OnAnimFinished);
    animator->AnimateMove(chip, QPoint(200, 400), QPoint(1000, 600), 4000);
}

Start::~Start()
{
    delete m_ui;
}

void Start::OnAnimFinished()
{
    blackjack::NavigateTo<Menu>(this);
}
