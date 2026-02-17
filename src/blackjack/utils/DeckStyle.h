#pragma once
#include <QString>
#include <core/Card.hpp>

namespace blackjack
{
    enum class DeckStyle : uint8_t
    {
        Classic,
        Castom
    };

    class DeckSettings
    {
    public:
        static void SetStyle(DeckStyle style) noexcept;

        static QString getCardsPath();
        
        static QString BuildCardPath(const Card& card);

    private:
        inline static DeckStyle m_style = DeckStyle::Classic;
    };
}// namespace blackjack
