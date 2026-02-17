#pragma once

namespace blackjack
{
    // UI
    inline constexpr const char* kStartBackgroundPath = R"(:/assets/ui/assets/ui/start.png)";

    // Chips
    inline constexpr const char* kChipBlackWhitePath =R"(:/assets/chips/assets/chips/chipBlackWhite.png)";
    inline constexpr const char* kChipRedWhitePath = R"(:/assets/chips/assets/chips/chipRedWhite.png)";
    inline constexpr const char* kChipGreenWhitePath = R"(:/assets/chips/assets/chips/chipGreenWhite.png)";
    inline constexpr const char* kChipBlueWhitePath = R"(:/assets/chips/assets/chips/chipBlueWhite.png)";

    // Audio
    inline constexpr const wchar_t* kBackgroundMusicSound = LR"(audio/background_Music.mp3)";
    inline constexpr const wchar_t* kClickSound = LR"(audio/click.mp3)";
    inline constexpr const wchar_t* kDealingSound = LR"(audio/dealing.mp3)";

    // Card decks
    inline constexpr const char* kClassicCardsPath = ":/assets/cards/classic/assets/cards/classic/";
    inline constexpr const char* kCastomCardsPath = ":/assets/cards/castom/assets/cards/castom/";

}// namespace blackjack
