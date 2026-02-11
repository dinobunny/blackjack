#include <QPixmap>
#include <QPropertyAnimation>

#include "Start.h"
#include "ui_Start.h"
#include "Menu.h"


Start::Start(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Start)
{
    ui->setupUi(this);

    // Background
    QPixmap bg(R"(:/assets/ui/assets/ui/start.png)");
    ui->label->setPixmap(bg);

    // Chip
    QLabel* chip = CreateChip();
    AnimateChip(chip);

}

Start::~Start()
{
    delete ui;
}

void Start::OnAnimFinished()
{
    auto* menu = new Menu();
    menu->show();
    this->close();
}

QLabel* Start::CreateChip()
{
    auto* chip = new QLabel(this);
    QPixmap chipPix(R"(:/assets/chips/assets/chips/chipRedWhite.png)");

    chip->setPixmap(chipPix);
    chip->resize(chipPix.size());
    chip->show();

    return chip;
}


void Start::AnimateChip(QLabel* chip)
{
    auto* anim = new QPropertyAnimation(chip, "pos");

    anim->setDuration(4000);
    anim->setStartValue(QPoint(200, 400));
    anim->setEndValue(QPoint(1000, 600));
    
    connect(anim, &QPropertyAnimation::finished, this, &Start::OnAnimFinished);
    
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}
