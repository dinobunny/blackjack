#include "DeckStyle.h"

using namespace blackjack;

void DeckSettings::SetStyle(DeckStyle style)noexcept
{
    m_style = style;
}

QString DeckSettings::getCardsPath()
{
    if (m_style == DeckStyle::Classic)
        return R"(:/assets/cards/classic/assets/cards/classic/)";

    return R"(:/assets/cards/castom/assets/cards/castom/)";
}

QString blackjack::DeckSettings::BuildCardPath(const Card& card)
{
    return getCardsPath() + QString::fromStdString(card.toString());
}