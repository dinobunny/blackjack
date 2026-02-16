#pragma once

class Balance
{
public:
    int GetBalance() const;
    int GetBet() const;

    void SetBet(int value);
    void ResetBet();
    void Win();
    void Lose();

private:
    int balance = 100;
    int bet = 0;
};
