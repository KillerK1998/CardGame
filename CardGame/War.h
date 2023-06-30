#pragma once

#include <iostream>
#include <vector>
#include <algorithm>

void startWar();

void playWar()
{
    std::string userInput;
    std::cout << "You chose to play War!!!" << "\n";
    std::cout << "Would you like to know the rules of War? (y/n): ";
    std::cin >> userInput;

    if (userInput == "y") {
        std::cout << "War is a game where each player starts with half of the deck. The objective is to capture the other player's cards.\n"
            "If both players play cards of the same value, it's called a war. During a war, each player draws three cards and reveals one card face up.\n"
            "If a player's card is higher than the opponent's card, the player wins all the cards in play.\n";
    }
    else if (userInput == "n") {
        std::cout << "Okay, let's start the game!";
    }
    else {
        std::cout << "Invalid input. Please try again.\n";
        return;
    }

    std::cout << "Are you ready to begin? (y/n): ";
    std::cin >> userInput;

    if (userInput == "y") {
        startWar();
    }
    else if (userInput == "n") {
        std::cout << "Okay, maybe next time! \n";
    }
    else {
        std::cout << "Invalid input. The game will not start.\n";
    }
}

void startWar() {
    std::cout << "Let's begin the battle!!!" << "\n";

    std::vector<int> player(26);
    std::vector<int> computer(26);

    // Set up the game by assigning cards to players
    for (int count = 1; count < 26; count++) {
        player[count] = count + 1;
        computer[count] = count + 1;
    }

    // Shuffle player and computer decks
    std::random_shuffle(player.begin(), player.end());
    std::random_shuffle(computer.begin(), computer.end());

    int round = 1;
    int playerScore = 0;
    int computerScore = 0;

    while (!player.empty() && !computer.empty()) {
        std::cout << "Round " << round << "\n";

        // Each player draws a card from their deck
        int playerCard = player.back();
        player.pop_back();

        int computerCard = computer.back();
        computer.pop_back();

        std::cout << "Player's Card: " << playerCard << "\n";
        std::cout << "Computer's Card: " << computerCard << "\n";

        if (playerCard > computerCard) {
            std::cout << "Player wins the round! \n";
            playerScore++;
        }
        else if (playerCard < computerCard) {
            std::cout << "Computer wins the round! \n";
            computerScore++;
        }
        else {
            std::cout << "It's a tie! Get ready for war!!! \n";

            if (player.size() < 4 || computer.size() < 4) {
                std::cout << "Not enough cards to go to war. The game is over!\n";
                break;
            }

            // Each player draws three cards face down for war
            std::vector<int> playerWarCards;
            std::vector<int> computerWarCards;

            for (int j = 0; j < 3; j++) {
                playerWarCards.push_back(player.back());
                player.pop_back();

                computerWarCards.push_back(computer.back());
                computer.pop_back();
            }

            std::cout << "Player's War Cards:";
            for (int card : playerWarCards) {
                std::cout << " " << card;
            }
            std::cout << "\n";

            std::cout << "Computer's War Cards:";
            for (int card : computerWarCards) {
                std::cout << " " << card;
            }
            std::cout << "\n";

            // Each player reveals one face-up card
            int playerWarCard = player.back();
            player.pop_back();

            int computerWarCard = computer.back();
            computer.pop_back();

            std::cout << "Player's Face-up War Card: " << playerWarCard << "\n";
            std::cout << "Computer's Face-up War Card: " << computerWarCard << "\n";

            if (playerWarCard > computerWarCard) {
                std::cout << "Player wins the war and takes all the cards! \n";
                playerScore += playerWarCards.size() + computerWarCards.size() + 1;
            }
            else if (playerWarCard < computerWarCard) {
                std::cout << "Computer wins the war and takes all the cards! \n";
                computerScore += computerWarCards.size() + playerWarCards.size() + 1;
            }
        }

        round++;
    }

    std::cout << "Player Score: " << playerScore << "\n";
    std::cout << "Computer Score: " << computerScore << "\n";
    std::cout << "-------------------------\n";

    if (playerScore > computerScore) {
        std::cout << "Player wins the game!\n";
    }
    else if (playerScore < computerScore) {
        std::cout << "Computer wins the game!\n";
    }
    else {
        std::cout << "It's a tie!\n";
    }
}
