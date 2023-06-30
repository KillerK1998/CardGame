#include "War.h"
#include "Blackjack.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <random>
#include <algorithm>

void playBlackjack();
void startBlackjack();

int main() {
    std::string userInput;

    while (true) {
        std::cout << "Welcome Player! Please select an option on the screen\n";
        std::cout << "1. War\n";
        std::cout << "2. Blackjack\n";
        std::cout << "3. Exit\n";

        std::cin >> userInput;

        if (userInput == "1") {
            playWar();
        }
        else if (userInput == "2") {
            playBlackjack();
        }
        else if (userInput == "3") {
            std::cout << "Exiting the game. Goodbye!\n";
            break;
        }
        else {
            std::cout << "Invalid input. Please try again.\n";
        }
    }

    return 0;
}
