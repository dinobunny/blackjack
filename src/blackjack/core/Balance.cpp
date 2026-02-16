#include "Balance.hpp"

int Balance::GetBalance() const
{
    return balance;
}

int Balance::GetBet() const
{
    return bet;
}

void Balance::SetBet(int value)
{
    bet = value;
}

void Balance::ResetBet()
{
    bet = 0;
}

void Balance::Win()
{
    balance += bet;
}

void Balance::Lose()
{
    balance -= bet;
}

void Balance::BlackJack()
{
    balance += (bet * 2);
}
