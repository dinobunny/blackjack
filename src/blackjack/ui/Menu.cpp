#include "Menu.h"
#include "Style.h"
#include "Play.h"

#include "ui_Menu.h"
#include "utils/Navigation.h"

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
    blackjack::NavigateTo<Style>(this);
}

void Menu::on_btnPlay_clicked()
{
    blackjack::NavigateTo<Play>(this);
}

