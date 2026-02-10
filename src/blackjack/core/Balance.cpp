#include "Balance.hpp"

int Balance::GetBalance() const
{
    return balance;
}

int Balance::GetBet() const
{
    return bet;
}

bool Balance::SetBet(int value)
{
    if (value <= 0)
        return false;
    if (value > balance)
        return false;

    bet = value;
    return true;
}

void Balance::Win()
{
    balance += bet;
    bet = 0;
}

void Balance::Lose()
{
    balance -= bet;
    if (balance < 0)
        balance = 0;

    bet = 0;
}
