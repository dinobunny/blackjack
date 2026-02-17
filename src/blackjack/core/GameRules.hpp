#pragma once

namespace blackjack
{
    struct GameRules
    {
        enum class Bet : int
        {
            Five = 5,
            Ten = 10,
            TwentyFive = 25,
            Fifty = 50
        };
        size_t numDecks = 6;
        bool dealerHitsSoft17 = true;
        double blackjackPayout = 1.5;  // 3:2 = 1.5, 6:5 = 1.2
        double penetration = 0.75;  // fraction of shoe dealt before reshuffle
    };
}// namespace blackjack
