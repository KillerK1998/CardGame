#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <string>

struct Card {
    std::string rank;
    std::string suit;
};

int getHandValue(const std::vector<Card>& hand);
void playBlackjack();
void playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck);
void dealerTurn(std::vector<Card>& dealerHand, std::vector<Card>& deck);

void startBlackjack()
{
    while (true) {
        std::cout << "Alright let's get started!!!" << "\n";

        // Initialize the deck
        std::vector<Card> deck;
        const std::vector<std::string> ranks = { "Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King" };
        const std::vector<std::string> suits = { "Spades", "Hearts", "Diamonds", "Clubs" };

        for (const std::string& suit : suits) {
            for (const std::string& rank : ranks) {
                Card card;
                card.rank = rank;
                card.suit = suit;
                deck.push_back(card);
            }
        }

        // Shuffle the deck
        std::random_device rd;
        std::mt19937 generator(rd());
        std::shuffle(deck.begin(), deck.end(), generator);

        // Deal initial cards
        std::vector<Card> playerHand;
        std::vector<Card> dealerHand;

        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();
        playerHand.push_back(deck.back());
        deck.pop_back();
        dealerHand.push_back(deck.back());
        deck.pop_back();

        // Display player's hand
        std::cout << "Player's Hand: ";
        for (const Card& card : playerHand)
            std::cout << card.rank << " of " << card.suit << ", ";
        std::cout << "\n";

        // Display dealer's hand (reveal only one card)
        std::cout << "Dealer's Hand: " << dealerHand[0].rank << " of " << dealerHand[0].suit << " [hidden card]\n";

        // Player's turn
        playerTurn(playerHand, deck);

        // Dealer's turn
        dealerTurn(dealerHand, deck);

        // Determine the winner and display the result
        int playerValue = getHandValue(playerHand);
        int dealerValue = getHandValue(dealerHand);

        std::cout << "Player's Hand Value: " << playerValue << "\n";
        std::cout << "Dealer's Hand Value: " << dealerValue << "\n";

        if (playerValue > 21 && dealerValue > 21) {
            std::cout << "Both player and dealer bust! It's a draw.\n";
        }
        else if (playerValue > 21) {
            std::cout << "Player busts! Dealer wins.\n";
        }
        else if (dealerValue > 21) {
            std::cout << "Dealer busts! Player wins.\n";
        }
        else if (playerValue > dealerValue) {
            std::cout << "Player wins!\n";
        }
        else if (playerValue < dealerValue) {
            std::cout << "Dealer wins!\n";
        }
        else {
            std::cout << "It's a draw!\n";
        }

        std::string userInput;
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> userInput;

        if (userInput == "n") {
            std::cout << "Returning to the main menu.\n";
            break;
        }
    }
}

void playerTurn(std::vector<Card>& playerHand, std::vector<Card>& deck)
{
    while (true) {
        std::string userInput;
        std::cout << "Do you want to hit or stand? (h/s): ";
        std::cin >> userInput;

        if (userInput == "h") {
            // Hit: Draw a card from the deck and add it to the player's hand
            playerHand.push_back(deck.back());
            deck.pop_back();

            // Display the updated player's hand
            std::cout << "Player's Hand: ";
            for (const Card& card : playerHand)
                std::cout << card.rank << " of " << card.suit << ", ";
            std::cout << "\n";

            int handValue = getHandValue(playerHand);
            std::cout << "Hand Value: " << handValue << "\n";

            if (handValue > 21) {
                std::cout << "Player busts!\n";
                break;
            }
        }
        else if (userInput == "s") {
            // Stand: Player decides to keep the current hand and end their turn
            break;
        }
        else {
            std::cout << "Invalid input. Please try again.\n";
        }
    }
}

void dealerTurn(std::vector<Card>& dealerHand, std::vector<Card>& deck)
{
    // Reveal the hidden card
    std::cout << "Dealer's Hand: ";
    for (const Card& card : dealerHand)
        std::cout << card.rank << " of " << card.suit << ", ";
    std::cout << "\n";

    int handValue = getHandValue(dealerHand);
    std::cout << "Hand Value: " << handValue << "\n";

    while (handValue < 17) {
        // Dealer draws a card from the deck
        dealerHand.push_back(deck.back());
        deck.pop_back();

        // Display the updated dealer's hand
        std::cout << "Dealer draws a card.\n";
        std::cout << "Dealer's Hand: ";
        for (const Card& card : dealerHand)
            std::cout << card.rank << " of " << card.suit << ", ";
        std::cout << "\n";

        handValue = getHandValue(dealerHand);
        std::cout << "Hand Value: " << handValue << "\n";
    }

    if (handValue > 21) {
        std::cout << "Dealer busts!\n";
    }
    else {
        std::cout << "Dealer stands.\n";
    }
}

int getHandValue(const std::vector<Card>& hand)
{
    int handValue = 0;
    int numAces = 0;

    for (const Card& card : hand) {
        if (card.rank == "Ace") {
            handValue += 11;
            numAces++;
        }
        else if (card.rank == "King" || card.rank == "Queen" || card.rank == "Jack") {
            handValue += 10;
        }
        else {
            handValue += std::stoi(card.rank);
        }
    }

    // Adjust the value of Aces if the hand value exceeds 21
    while (handValue > 21 && numAces > 0) {
        handValue -= 10;
        numAces--;
    }

    return handValue;
}

void playBlackjack()
{
    std::string userInput;
    std::cout << "You chose to play Blackjack" << "\n";
    std::cout << "Would you like to know the rules of Blackjack? (y/n): ";
    std::cin >> userInput;

    if (userInput == "y") {
        std::cout << "Blackjack is a card game where the goal is to get a hand total as close to 21 as possible without exceeding it.\n"
            "The face cards (Jack, Queen, and King) are worth 10, and the Ace can be worth either 1 or 11.\n"
            "At the beginning of each round, you and the dealer will be dealt two cards.\n"
            "You can choose to 'hit' to draw another card or 'stand' to keep your current hand.\n"
            "After your turn, the dealer will reveal their second card and draw additional cards until their hand total is 17 or higher.\n"
            "If your hand total exceeds 21, you bust and lose the round. The same applies to the dealer.\n"
            "The player with a hand total closest to 21 without going over wins the round.\n";

        std::cout << "Are you ready to play? (y/n): ";
        std::cin >> userInput;

        if (userInput == "y") {
            startBlackjack();
        }
        else {
            std::cout << "Okay, returning to the main menu.\n";
        }
    }
    else if (userInput == "n") {
        std::cout << "Okay, then let's start the game!";
        startBlackjack();
    }
    else {
        std::cout << "Invalid input. Please try again.\n";
    }
}
