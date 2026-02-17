#include "Style.h"
#include "ui_Style.h"
#include "Menu.h"
#include "utils/DeckStyle.h"

#include <QStyle>
#include <utils/Navigation.h>
#include <audio/PlaySound.h>
#include "utils/Config_Constants.h"

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

void Style::applySelected(QWidget* widget, const char* prop, bool on)
{
    PlaySoundNew(blackjack::kClickSound, true);

    widget->setProperty(prop, on);
    widget->style()->unpolish(widget);
    widget->style()->polish(widget);
    widget->update();
}

void Style::on_btnSelect_clicked()
{
    PlaySoundNew(blackjack::kClickSound, true);

    const bool classic = ui->widget_Classic->property("selected").toBool();
    const bool custom = ui->widget_Castom->property("selected").toBool();

    if (!classic && !custom)
        return;

    applySelected(ui->widget_Classic, "confirmed", classic);
    applySelected(ui->widget_Castom, "confirmed", custom);

    if (classic)
        blackjack::DeckSettings::SetStyle(blackjack::DeckStyle::Classic);
    else
        blackjack::DeckSettings::SetStyle(blackjack::DeckStyle::Castom);

}

void Style::on_btnBack_clicked()
{
    PlaySoundNew(blackjack::kClickSound, true);
    blackjack::NavigateTo<Menu>(this);
}

void Style::installRecursive(QWidget* root)
{
    root->setAttribute(Qt::WA_StyledBackground, true);
    root->installEventFilter(this);

    const auto children = root->findChildren<QWidget*>();
    for (auto* c : children)
    {
        c->installEventFilter(this);
    }
}

void Style::setSelectedPair(QWidget* on, QWidget* off)
{
    applySelected(on, "selected", true);
    applySelected(off, "selected", false);
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
        setSelectedPair(ui->widget_Classic, ui->widget_Castom);
        return true;
    }

    if (pointer == ui->widget_Castom)
    {
        setSelectedPair(ui->widget_Castom, ui->widget_Classic);
        return true;
    }

    return false;
}
