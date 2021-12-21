#include <iostream>
#include "Blackjack.h"

int main(int argc, char **argv)
{
    int starterBalance, currentBalance, winnings;
    std::cout << "Enter balance: ";
    std::cin >> starterBalance;
    currentBalance = starterBalance;

    while (currentBalance != 0) // While player has money
    {
        Blackjack bj;
        int exitCode = bj.getExitCode();

        switch (exitCode)
        {
        case 1:
            currentBalance -= 10;
            std::cout << "You lost 10 dollars.\n";
            break;
        case 2:
            currentBalance += 10;
            std::cout << "You won 10 dollars.\n";
            break;
        case 3:
            std::cout << "You broke even.\n";
            break;
        case 4:
            currentBalance += 20;
            std::cout << "You won 20 dollars.\n";
            break;
        case 5:
            currentBalance -= 20;
            std::cout << "You lost 20 dollars.\n";
            break;
        }

        std::cout << "Current balance: " << currentBalance << std::endl;
        _sleep(5000); // Sleep for 5 seconds
    }
    std::cout << "You're out of money.\n";
    return 0;
}