#include "Menu.h"
#include "Style.h"
#include "Play.h"

#include "ui_Menu.h"
#include "utils/Navigation.h"


#define NOMINMAX
#include "../audio/PlaySound.h"

Menu::Menu(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::on_btnStyle_clicked()
{
    PlaySoundNew(LR"(audio\click.mp3)", true);
    blackjack::NavigateTo<Style>(this);
}

void Menu::on_btnPlay_clicked()
{
    PlaySoundNew(LR"(audio\click.mp3)", true);
    blackjack::NavigateTo<Play>(this);
}

