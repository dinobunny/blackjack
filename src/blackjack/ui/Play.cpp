#include "Play.h"
#include "Menu.h"
#include "ui_Play.h"


Play::Play(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Play)
{
    ui->setupUi(this);
}

Play::~Play()
{
    delete ui;
}


void Play::back()
{
    auto* style = new Menu();
    style->show();
    this->close();
}

void Play::on_pushButton_clicked()
{
    back();
}

