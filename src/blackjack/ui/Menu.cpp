#include "Menu.h"
#include "Style.h"
#include "Play.h"

#include "ui_Menu.h"

#include <QPixmap>

Menu::Menu(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);

    // Background
    QPixmap bg(R"(:/assets/ui/assets/ui/menu.png)");
    ui->label->setPixmap(bg);
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

