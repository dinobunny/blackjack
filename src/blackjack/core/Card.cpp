
#include <stdexcept>

#include "Card.hpp"

using namespace blackjack;

std::string Card::getRankString() const
{
    switch (rank_)
    {
    case Rank::ACE:
        return "A";
    case Rank::TWO:
        return "2";
    case Rank::THREE:
        return "3";
    case Rank::FOUR:
        return "4";
    case Rank::FIVE:
        return "5";
    case Rank::SIX:
        return "6";
    case Rank::SEVEN:
        return "7";
    case Rank::EIGHT:
        return "8";
    case Rank::NINE:
        return "9";
    case Rank::TEN:
        return "10";
    case Rank::JACK:
        return "J";
    case Rank::QUEEN:
        return "Q";
    case Rank::KING:
        return "K";
    default:
        throw std::logic_error("Invalid rank");
    }
}

std::string Card::getSuitString() const
{
    switch (suit_)
    {
    case Suit::HEARTS:
        return "cardHearts";
    case Suit::DIAMONDS:
        return "cardDiamonds";
    case Suit::CLUBS:
        return "cardClubs";
    case Suit::SPADES:
        return "cardSpades";
    default:
        throw std::logic_error("Invalid suit");
    }
}

std::string Card::toString() const
{
    return getSuitString() + getRankString() + ".png";
}
