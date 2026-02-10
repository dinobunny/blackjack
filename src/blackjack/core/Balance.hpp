#pragma once

class Balance
{
public:
    int GetBalance() const;
    int GetBet() const;

    bool SetBet(int value);

    void Win();
    void Lose();

private:
    int balance = 100;
    int bet = 0;
};
