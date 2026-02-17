#include "Menu.h"
#include "Style.h"
#include "Play.h"

#include "ui_Menu.h"
#include "utils/Navigation.h"

#define NOMINMAX
#include "../audio/PlaySound.h"

Menu::Menu(QWidget* parent)
    : QMainWindow(parent)
    , m_ui(new Ui::Menu)
{
    m_ui->setupUi(this);
}

Menu::~Menu()
{
    delete m_ui;
}

void Menu::on_btnStyle_clicked()
{
    blackjack::PlaySoundNew(LR"(audio\click.mp3)", true);
    blackjack::NavigateTo<Style>(this);
}

void Menu::on_btnPlay_clicked()
{
    blackjack::PlaySoundNew(LR"(audio\click.mp3)", true);
    blackjack::NavigateTo<Play>(this);
}
