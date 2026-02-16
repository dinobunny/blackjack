#pragma once
#include "GameRules.hpp"

class Balance
{
public:
    explicit Balance(int initialBalance = 100) noexcept;

    [[nodiscard]] int GetBalance() const noexcept;
    [[nodiscard]] int GetBet() const noexcept;


    void resetBet() noexcept;
    bool setBet(blackjack::GameRules::Bet bet) noexcept;

    void lose() noexcept;
    void win(int amount) noexcept;


private:
    int m_balance = 0;
    int m_bet = 0;
};
