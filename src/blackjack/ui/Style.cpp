#include "Style.h"
#include "ui_Style.h"
#include "Menu.h"

#include <QPixmap>

Style::Style(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Style)
{
    ui->setupUi(this);

}

Style::~Style()
{
    delete ui;
}

void Style::OnAnimFinished()
{
    auto* style = new Menu();
    style->show();
    this->close();
}
void Style::on_btnStyle_clicked()
{
    OnAnimFinished();
}

