    #include "Card.hpp"
    #include <stdexcept>

    namespace blackjack
    {

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
            case Rank::BACK:
                return "1";
            default:
                throw std::logic_error("Invalid rank");
            }
        }

        std::string Card::getSuitString() const
        {
            switch (suit_)
            {
            case Suit::HEARTS:
                return "cardsHearts";
            case Suit::DIAMONDS:
                return "cardsDiamonds";
            case Suit::CLUBS:
                return "cardsClubs";
            case Suit::SPADES:
                return "cardsSpades";
            case Suit::RED:
                return "cardsBack_red";
            default:
                throw std::logic_error("Invalid suit");
            }
        }

        std::string Card::toString() const
        {
            return getSuitString() + getRankString() + ".png";
        }

        std::string Card::toShortString() const//fantom
        {
            return std::string();
        }

        std::ostream& operator<<(std::ostream& os, const Card& card)//fantom
        {
            return os << card.toString();
        }

    } // namespace blackjack