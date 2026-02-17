#pragma once

#include <string>
#include <vector>

#include "Card.hpp"

namespace blackjack
{

    /** Player or dealer hand; value calculation handles soft/hard aces. */
    class Hand
    {
    public:
        struct Value
        {
            int total;
            bool isSoft; // usable ace counting as 11

            bool operator==(const Value& other) const
            {
                return total == other.total && isSoft == other.isSoft;
            }
        };

        Hand() = default;
        void addCard(const Card& card);
        void clear();

        /** Soft aces count as 11 until that would bust, then as 1. */
        Value getValue() const;

        int getTotal() const
        {
            return getValue().total;
        }
        bool isSoft() const
        {
            return getValue().isSoft;
        }
        bool isBlackjack() const;
        bool isBust() const
        {
            return getTotal() > 21;
        }
        size_t size() const
        {
            return cards_.size();
        }
        bool empty() const
        {
            return cards_.empty();
        }
        const std::vector<Card>& getCards() const
        {
            return cards_;
        }
    private:
        std::vector<Card> cards_;
    };

} // namespace blackjack
