
#include <stdexcept>

#include "BlackjackGame.hpp"

using namespace blackjack;

std::string outcomeToString(Outcome outcome)
{
    switch (outcome)
    {
    case Outcome::PLAYER_WIN:
        return "Player Win";
    case Outcome::PLAYER_BLACKJACK:
        return "Player Blackjack";
    case Outcome::DEALER_WIN:
        return "Dealer Win";
    case Outcome::PUSH:
        return "Push";
    case Outcome::PLAYER_BUST:
        return "Player Bust";
    case Outcome::DEALER_BUST:
        return "Dealer Bust";
    default:
        return "Unknown";
    }
}

BlackjackGame::BlackjackGame(const GameRules& m_rules)
    : m_rules(m_rules), m_deck(std::make_unique<Deck>(m_rules.numDecks)),
    m_roundComplete(false)
{
}

void BlackjackGame::startRound()
{
    // Check if we need to reshuffle
    checkAndReshuffle();

    // Clear previous hands
    m_playerHand.clear();
    m_dealerHand.clear();
    m_roundComplete = false;
    m_outcome.reset();

    // Deal initial cards (player, dealer, player, dealer)
    m_playerHand.addCard(m_deck->deal());
    m_dealerHand.addCard(m_deck->deal());
    m_playerHand.addCard(m_deck->deal());
    m_dealerHand.addCard(m_deck->deal());


    // Check for immediate blackjack
    if (m_playerHand.isBlackjack() || m_dealerHand.isBlackjack())
    {
        m_roundComplete = true;
        m_outcome = determineOutcome();
    }
}

bool BlackjackGame::hit()
{
    if (m_roundComplete)
    {
        return false;
    }

    m_playerHand.addCard(m_deck->deal());

    // Check if player busts
    if (m_playerHand.isBust())
    {
        m_roundComplete = true;
        m_outcome = Outcome::PLAYER_BUST;
        return true;
    }

    return true;
}

void BlackjackGame::stand()
{
    if (m_roundComplete)
    {
        return;
    }

    // Player is done, dealer plays
    playDealerHand();

    m_roundComplete = true;
    m_outcome = determineOutcome();
}

Outcome BlackjackGame::getOutcome() const
{
    if (!m_roundComplete)
    {
        throw std::logic_error("Round is not complete");
    }

    return m_outcome.value();
}

Hand BlackjackGame::getDealerHand(bool hideHoleCard) const
{
    if (hideHoleCard && m_dealerHand.size() >= 2)
    {
        Hand visibleHand;
        visibleHand.addCard(m_dealerHand.getCards() [0]);
        return visibleHand;
    }

    return m_dealerHand;
}

void BlackjackGame::reset()
{
    m_deck->reset();
    m_playerHand.clear();
    m_dealerHand.clear();
    m_roundComplete = false;
    m_outcome.reset();
}

void BlackjackGame::playDealerHand()
{
    // Dealer must hit until 17 or higher
    while (true)
    {
        int total = m_dealerHand.getTotal();
        bool soft = m_dealerHand.isSoft();

        // Check if dealer should hit
        bool shouldHit = false;

        if (total < m_rules.dealerStandValue)
        {
            shouldHit = true;
        }
        else if (total == m_rules.dealerStandValue && soft && m_rules.dealerHitsSoft17)
        {
            shouldHit = true;
        }

        if (!shouldHit)
        {
            break;
        }

        m_dealerHand.addCard(m_deck->deal());

        // Check for bust
        if (m_dealerHand.isBust())
        {
            break;
        }
    }
}

Outcome BlackjackGame::determineOutcome() const
{
    bool playerBlackjack = m_playerHand.isBlackjack();
    bool dealerBlackjack = m_dealerHand.isBlackjack();

    // Check for blackjacks first
    if (playerBlackjack && dealerBlackjack)
    {
        return Outcome::PUSH;
    }

    if (playerBlackjack)
    {
        return Outcome::PLAYER_BLACKJACK;
    }

    if (dealerBlackjack)
    {
        return Outcome::DEALER_WIN;
    }

    // Check for busts
    int playerTotal = m_playerHand.getTotal();
    int dealerTotal = m_dealerHand.getTotal();

    if (playerTotal > m_rules.blackjackValue)
    {
        return Outcome::PLAYER_BUST;
    }

    if (dealerTotal > m_rules.blackjackValue)
    {
        return Outcome::DEALER_BUST;
    }

    // Compare totals
    if (playerTotal > dealerTotal)
    {
        return Outcome::PLAYER_WIN;
    }
    else if (dealerTotal > playerTotal)
    {
        return Outcome::DEALER_WIN;
    }
    else
    {
        return Outcome::PUSH;
    }
}

void BlackjackGame::checkAndReshuffle()
{
    if (m_deck->needsReshuffle(m_rules.penetration))
    {
        m_deck->reset();
    }
}

int BlackjackGame::calcPayout(int bet) const
{
    if (!m_outcome.has_value())
        throw std::logic_error("Round is not complete");

    const Outcome o = *m_outcome;

    switch (o)
    {
    case Outcome::PUSH:
        return 0;

    case Outcome::PLAYER_BLACKJACK:
        return static_cast<int>(bet * m_rules.blackjackPayout);

    case Outcome::PLAYER_WIN:
    case Outcome::DEALER_BUST:
        return bet;

    default:
        return -bet;
    }
}

