#include "Menu.h"
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
