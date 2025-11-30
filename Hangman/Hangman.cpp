// Hangman.cpp : This file contains the 'main' function. Program execution begins and ends there.

#include <iostream>
#include <string>
#include "Word.h"

using namespace std;

void printHangman(int lives) {
    string stages[7] = {
        // 0 lives – full hangman
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|  /|\\\n"
        "|  / \\\n",

        // 1 life – missing right leg
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|  /|\\\n"
        "|  /  \n",

        // 2 lives – missing legs
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|  /|\\\n"
        "|      \n",

        // 3 lives – one arm
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|  /| \n"
        "|      \n",

        // 4 lives – no arms
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|   | \n"
        "|      \n",

        // 5 lives – just the head
        "_____ \n"
        "|   | \n"
        "|   O \n"
        "|      \n"
        "|      \n",

        // 6 lives – empty
        "_____ \n"
        "|   | \n"
        "|      \n"
        "|      \n"
        "|      \n"
    };

    cout << stages[lives] << endl;
}

int main() {
    srand(time(0));

    while (true) {  // Outer loop: keeps the game running
        cout << "Welcome to Hangman!\n";
        cout << "Type 'exit' at any prompt to quit.\n";

        // --- Mode Selection ---
        string mode;
        while (true) {
            cout << "Do you want to play by yourself or with a friend? (solo/friend): ";
            cin >> mode;
            if (mode == "exit") return 0;
            if (mode == "solo" || mode == "friend") break;
            cout << "Invalid option. Please type 'solo' or 'friend'.\n";
        }

        Word word;
        if (mode == "friend") {
            string friendWord;
            cout << "Friend, please enter the word for the other player: ";
            cin >> friendWord;
            word = Word(friendWord);
        }
        else {
            word = Word();  // Random word from file
        }

        // --- Game Loop ---
        int lives = 6;
        bool isComplete = false;

        while (lives > 0 && !isComplete) {
            system("cls"); // Clear console
            printHangman(lives);
            cout << "Word: " << word.getWordSoFar() << "\n";

            vector<char> incorrectLetters = word.getIncorrectLetters();
            if (!incorrectLetters.empty()) {
                cout << "Incorrect letters: ";
                for (char c : incorrectLetters) cout << c << " ";
                cout << "\n";
            }

            string input;
            char guess;

            while (true) {  // Input validation loop
                cout << "Enter your next guess: ";
                cin >> input;
                if (input == "exit") return 0;

                if (input.length() != 1) {
                    cout << "Please enter exactly one letter.\n";
                    continue;
                }

                guess = tolower(input[0]);

                if (!isalpha(guess)) {
                    cout << "That's not a valid letter.\n";
                    continue;
                }

                string soFar = word.getWordSoFar();
                if (soFar.find(guess) != string::npos ||
                    find(incorrectLetters.begin(), incorrectLetters.end(), guess) != incorrectLetters.end()) {
                    cout << "You already guessed that letter.\n";
                    continue;
                }
                break;  // Valid guess
            }

            if (!word.containsLetter(guess)) lives--;
            isComplete = word.isComplete();
        }

        system("cls");
        printHangman(lives);
        if (isComplete)
            cout << "Congratulations! You guessed the word: " << word.getWord() << "\n";
        else
            cout << "Better luck next time! The word was: " << word.getWord() << "\n";

        cout << "Press RETURN to play again or type 'exit' to quit: ";
        string playAgain;
        cin.ignore(); // ignore leftover newline
        getline(cin, playAgain);
        if (playAgain == "exit") break;

        system("cls"); // Clear screen before new game
    }

    cout << "Thanks for playing Hangman!\n";
    return 0;
}