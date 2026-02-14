#include "Style.h"
#include "ui_Style.h"
#include "Menu.h"

#include <QPixmap>
#include <QMouseEvent>
#include <QStyle>

Style::Style(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Style)
{
    ui->setupUi(this);
    ui->widget_Classic->installEventFilter(this);
    ui->widget_Castom->installEventFilter(this);

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

// Checking if the map style selection widgets are clicked and setting the "selected" property for the corresponding widget to change its appearance
void Style::applySelected(QWidget* widget, bool on)
{
    widget->setProperty("selected", on);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}


void Style::mousePressEvent(QMouseEvent* event)
{
    const QPoint pClassic = ui->widget_Classic->mapFrom(this, event->pos());
    const QPoint pCustom = ui->widget_Castom->mapFrom(this, event->pos());

    if (ui->widget_Classic->rect().contains(pClassic))
    {
        applySelected(ui->widget_Classic, true);
        applySelected(ui->widget_Castom, false);
    }
    else if (ui->widget_Castom->rect().contains(pCustom))
    {
        applySelected(ui->widget_Castom, true);
        applySelected(ui->widget_Classic, false);
    }

    QMainWindow::mousePressEvent(event);
}
