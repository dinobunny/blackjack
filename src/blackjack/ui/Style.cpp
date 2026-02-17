#include "Style.h"
#include "ui_Style.h"
#include "Menu.h"
#include "utils/DeckStyle.h"

#include <QStyle>

Style::Style(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::Style)
{
    ui->setupUi(this);
    installRecursive(ui->widget_Classic);
    installRecursive(ui->widget_Castom);
}

Style::~Style()
{
    delete ui;
}

void Style::back()
{
    auto* style = new Menu();
    style->show();
    this->close();
}

void Style::applySelected(QWidget* widget, const char* prop, bool on)
{
    widget->setProperty(prop, on);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

void Style::on_btnSelect_clicked()
{
    const bool classic = ui->widget_Classic->property("selected").toBool();
    const bool custom = ui->widget_Castom->property("selected").toBool();

    if (!classic && !custom)
        return;

    applySelected(ui->widget_Classic, "confirmed", classic);
    applySelected(ui->widget_Castom, "confirmed", custom);

    blackjack::DeckSettings::SetStyle(
        classic ? blackjack::DeckStyle::Classic : blackjack::DeckStyle::Castom
    );
}

void Style::on_btnBack_clicked()
{
    back();
}

void Style::installRecursive(QWidget* root)
{
    root->setAttribute(Qt::WA_StyledBackground, true);
    root->installEventFilter(this);

    const auto children = root->findChildren<QWidget*>();
    for (auto* c : children)
        c->installEventFilter(this);
}

bool Style::eventFilter(QObject* obj, QEvent* event)
{
    if (event->type() != QEvent::MouseButtonPress)
        return false;

    auto* widget = qobject_cast<QWidget*>(obj);
    if (!widget)
        return false;

    QWidget* pointer = widget;

    while (pointer &&
           pointer != ui->widget_Classic &&
           pointer != ui->widget_Castom)
    {
        pointer = pointer->parentWidget();
    }

    if (pointer == ui->widget_Classic)
    {
        applySelected(ui->widget_Classic, "selected", true);
        applySelected(ui->widget_Castom, "selected", false);
        return true;
    }

    if (pointer == ui->widget_Castom)
    {
        applySelected(ui->widget_Castom, "selected", true);
        applySelected(ui->widget_Classic, "selected", false);
        return true;
    }

    return false;
}
