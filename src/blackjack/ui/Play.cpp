#include "Play.h"
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

