#include "Hand.hpp"
#include <sstream>
#include <stdexcept>


namespace blackjack
{

    void Hand::addCard(const Card& card)
    {
        cards_.push_back(card);
    }

    void Hand::clear()
    {
        cards_.clear();
    }

    Hand::Value Hand::getValue() const
    {
        int total = 0;
        int aces = 0;

        // First pass: count aces as 11
        for (const auto& card : cards_)
        {
            if (card.isAce())
            {
                aces++;
                total += 11;
            }
            else
            {
                total += card.getValue();
            }
        }

        // Second pass: convert aces from 11 to 1 if bust
        while (total > 21 && aces > 0)
        {
            total -= 10; // Convert one ace from 11 to 1
            aces--;
        }

        // Hand is soft if it has at least one ace still counting as 11
        bool isSoft = (aces > 0) && (total <= 21);

        return { total, isSoft };
    }

    bool Hand::isBlackjack() const
    {
        if (cards_.size() != 2)
        {
            return false;
        }

        return getTotal() == 21;
    }

} // namespace blackjack