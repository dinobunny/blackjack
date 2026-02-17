
#include "Balance.hpp"

using namespace blackjack;

Balance::Balance(int initialBalance) noexcept
    : m_balance(initialBalance)
{
}

int Balance::GetBalance() const noexcept
{
    return m_balance;
}

int Balance::GetBet() const noexcept
{
    return m_bet;
}

void Balance::resetBet() noexcept
{
    m_bet = 0;
}

void Balance::lose() noexcept
{
    m_balance -= m_bet;
}

void Balance::win(int amount) noexcept
{
    m_balance += amount;
}

bool Balance::setBet(blackjack::GameRules::Bet bet) noexcept
{
    int value = static_cast<int>(bet);

    if (value > m_balance)
        return false;

    m_bet = value;
    return true;
}
