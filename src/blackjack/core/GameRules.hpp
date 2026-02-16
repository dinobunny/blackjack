#pragma once

namespace blackjack
{
    struct GameRules
    {
        enum class Bet
        {
            Five = 5,
            Ten = 10,
            TwentyFive = 25,
            Fifty = 50,
            Hundred = 100
        };

        double blackjackPayout = 1.5;
    };
}
