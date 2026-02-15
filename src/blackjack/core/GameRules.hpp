#pragma once

#include <cstddef>

namespace blackjack
{

    /** House rules and table config. */
    struct GameRules
    {
        size_t numDecks = 6;
        bool dealerHitsSoft17 = true;
        double blackjackPayout = 1.5;  // 3:2 = 1.5, 6:5 = 1.2
        double penetration = 0.75;  // fraction of shoe dealt before reshuffle

    };

} // namespace blackjack