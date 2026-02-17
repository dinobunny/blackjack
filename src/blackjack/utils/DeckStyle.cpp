
#include "DeckStyle.h"
#include "utils/Config_Constants.h"

using namespace blackjack;

void DeckSettings::SetStyle(DeckStyle style)noexcept
{
    m_style = style;
}

QString DeckSettings::getCardsPath()
{
    if (m_style == DeckStyle::Classic)
        return kClassicCardsPath;

    return kCastomCardsPath;
}

QString blackjack::DeckSettings::BuildCardPath(const Card& card)
{
    return getCardsPath() + QString::fromStdString(card.toString());
}
