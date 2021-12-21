/*
    Date: 12/20/2021
    Description: Blackjack game
    Usage: Call constructor to execute game
*/

#include <iostream>
#include <vector>
#include <time.h> //Generates time seed for rand num
#include <string>

class Blackjack
{
    std::vector<std::string> playerCards, dealerCards;
    int totalPlayer = 0, totalDealer = 0,
        cardsDrawn = 0, exitCode;
    std::string endScreen, choice;
    std::vector<int> deck = {};
    bool gameEnded = false;

protected:
    void shuffleCards();
    void initializeHands();
    void hitOrStay();

public:
    Blackjack();
    std::vector<std::string> getPlayerCards() const;
    std::vector<std::string> getDealerCards() const;
    int getTotalPlayer() const;
    int getTotalDealer() const;
    int getExitCode() const;
    int getCardsDrawn() const;
    void print();
    int checkWin();
};

// Constructor
Blackjack::Blackjack()
{
    srand(time(NULL));
    shuffleCards();
    initializeHands();
    print();
    hitOrStay();
}

// Checks if the game has found a winner
int Blackjack::checkWin()
{
    std::string white = "\033[0m",
                red = "\033[31m",
                green = "\033[32m",
                yellow = "\033[33m";
    // Player bust
    if (totalPlayer > 21)
    {
        endScreen = red + "\n\nPlayer Busts! DEALER WINS!!!" + white;
        exitCode = 1;
    }

    // Dealer bust
    if (totalDealer > 21)
    {
        endScreen = green + "\n\nDealer Busts! PLAYER WINS!!!" + white;
        exitCode = 2;
    }

    // Stalemate
    if (totalDealer == totalPlayer && choice == "s" || choice == "stand")
    {
        endScreen = yellow + "\n\nSTALEMATE!!!" + white;
        exitCode = 3;
    }

    // Player wins
    if (totalPlayer <= 21 && totalDealer != totalPlayer && totalDealer <= totalPlayer && choice == "s" || choice == "stand")
    {
        endScreen = green + "\n\nPLAYER WINS!!!" + white;
        exitCode = 4;
    }

    // Dealer wins
    if (totalDealer <= 21 && totalDealer != totalPlayer && totalPlayer <= totalDealer && choice == "s" || choice == "stand")
    {
        endScreen = red + "\n\nDEALER WINS!!!" + white;
        exitCode = 5;
    }

    // Exit game with a winner
    if (!endScreen.empty())
    {
        std::cout << endScreen << std::endl;
        gameEnded = true;
        return exitCode;
    }
    return 0;
}

// Player hits or stays
// If player hits, draw a card
// If player stays, dealer draws cards
void Blackjack::hitOrStay()
{
    do
    {
        checkWin();            // Check if game has ended
        if (gameEnded == true) // If game has ended, exit loop
            break;

        std::cout << "\n\nHit or Stand? (Use 'h' or 's')\n";
        std::cin >> choice;

        // Player hits
        if (choice == "h" || choice == "hit")
        {
            totalPlayer += deck[cardsDrawn];                           // Add card to player's total
            playerCards.push_back(std::to_string(deck[cardsDrawn++])); // Add card to player's hand
        }
        else
            while (totalDealer <= 17) // Dealer draws cards until total is 17 or higher
            {
                totalDealer += deck[cardsDrawn];                           // Add card to dealer's total
                dealerCards.push_back(std::to_string(deck[cardsDrawn++])); // Add card to dealer's hand
            }

        print(); // Print updated hands
    } while (gameEnded == false);
}

// Shuffles the deck of cards
void Blackjack::shuffleCards()
{
    std::vector<int> cardVals = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10,
                                 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10};
    int size = cardVals.size();

    for (int i = 0; i < size; i++)
    {
        int randNum = rand() % cardVals.size();     // Generate random number
        deck.push_back(cardVals[randNum]);          // Add card to deck
        cardVals.erase(cardVals.begin() + randNum); // Remove card from cardVals
    }
}

// Player and dealer's hands are initialized
void Blackjack::initializeHands()
{
    // Player's hand gets two cards
    totalPlayer += deck[cardsDrawn];
    playerCards.push_back(std::to_string(deck[cardsDrawn++]));
    totalPlayer += deck[cardsDrawn];
    playerCards.push_back(std::to_string(deck[cardsDrawn++]));

    // Dealer's hand gets one card
    totalDealer += deck[cardsDrawn];
    dealerCards.push_back(std::to_string(deck[cardsDrawn++]));
}

// Prints the player's hand and dealer's hand
void Blackjack::print()
{
    std::cout << "-----------------------------";
    std::cout << "\n🃏 Blackjack 🃏\n\n";
    std::cout << "Player: \n     ";
    for (std::string i : getPlayerCards())
        std::cout << i << " | ";
    std::cout << "\n= " << getTotalPlayer() << "\n\nDealer: \n     ";
    for (std::string i : getDealerCards())
        std::cout << i << " | ";
    std::cout << "\n= " << getTotalDealer();
}

// Returns the player's hand
std::vector<std::string> Blackjack::getPlayerCards() const
{
    return playerCards;
}

// Returns the dealer's hand
std::vector<std::string> Blackjack::getDealerCards() const
{
    return dealerCards;
}

// Returns the player's total
int Blackjack::getTotalPlayer() const
{
    return totalPlayer;
}

// Returns the dealer's total
int Blackjack::getTotalDealer() const
{
    return totalDealer;
}

// Returns the number of cards drawn
int Blackjack::getCardsDrawn() const
{
    return cardsDrawn;
}

// Returns the exit code
int Blackjack::getExitCode() const
{
    return exitCode;
}