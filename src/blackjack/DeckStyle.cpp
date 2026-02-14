#include "DeckStyle.h"

using namespace blackjack;

void DeckSettings::SetStyle(DeckStyle style)noexcept
{
    m_style = style;
}

QString DeckSettings::getCardsPath()
{
    if (m_style == DeckStyle::Classic)
        return ":/assets/cards/classic/";

    return ":/assets/cards/castom/";
}
