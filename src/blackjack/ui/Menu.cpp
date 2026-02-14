#include "Menu.h"
#include "Style.h"
#include "Play.h"

#include "ui_Menu.h"

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

void Menu::goStyle()
{
    auto* menu = new Style();
    menu->show();
    this->close();
}

void Menu::goPlay()
{
    auto* menu = new Play();
    menu->show();
    this->close();
}

void Menu::on_btnStyle_clicked()
{
    goStyle();
}

    
void Menu::on_btnPlay_clicked()
{
    goPlay();
}

