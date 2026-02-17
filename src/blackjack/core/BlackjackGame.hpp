#pragma once

#include <memory>
#include <optional>

#include "GameRules.hpp"
#include "Deck.hpp"
#include "Hand.hpp"

namespace blackjack
{

    enum class Outcome
    {
        PLAYER_WIN,
        PLAYER_BLACKJACK,
        DEALER_WIN,
        PUSH,
        PLAYER_BUST,
        DEALER_BUST
    };

    std::string outcomeToString(Outcome outcome);

    /** Single-player vs dealer; manages state, rules, and dealer play. */
    class BlackjackGame
    {
    public:
        explicit BlackjackGame(const GameRules& m_rules = GameRules {});
        void startRound();

        /** @return true if action was applied. */
        bool hit();
        void stand();

        int calcPayout(int bet) const;

        bool isRoundComplete() const
        {
            return m_roundComplete;
        }

        /** @throws std::logic_error if round not complete. */
        Outcome getOutcome() const;

        const Hand& getPlayerHand() const
        {
            return m_playerHand;
        }

        /** hideHoleCard: true to show only upcard (e.g. during player turn). */
        Hand getDealerHand(bool hideHoleCard = false) const;

        const GameRules& getRules() const
        {
            return m_rules;
        }
        void reset();

    private:
        void playDealerHand();
        Outcome determineOutcome() const;
        void checkAndReshuffle();


    private:
        GameRules m_rules;
        std::unique_ptr<Deck> m_deck;
        Hand m_playerHand;
        Hand m_dealerHand;
        bool m_roundComplete;
        std::optional<Outcome> m_outcome;

    };

} // namespace blackjack
