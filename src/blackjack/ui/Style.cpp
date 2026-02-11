#include "Style.h"
#include "ui_Style.h"

#include <QPixmap>

Style::Style(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Style)
{
    ui->setupUi(this);

    // Background
    QPixmap bg(R"(:/assets/ui/assets/ui/Style.png)");
    ui->label->setPixmap(bg);
}

Style::~Style()
{
    delete ui;
}
