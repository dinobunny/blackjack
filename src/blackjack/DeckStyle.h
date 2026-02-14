#pragma once
#include <QString>

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
        

    private:
        inline static DeckStyle m_style = DeckStyle::Classic;
    };
}