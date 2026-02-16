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

        double blackjackPayout = 1.5;
    };
}
