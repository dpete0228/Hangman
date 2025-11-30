#include "Word.h"
#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

// Constructor with a specific word
Word::Word(std::string word) {
    _word = word;
    transform(_word.begin(), _word.end(), _word.begin(), ::tolower);

    loadPossibleWords();

    // Add word if it doesn't exist
    if (find(_possibleWords.begin(), _possibleWords.end(), _word) == _possibleWords.end()) {
        _possibleWords.push_back(_word);
        saveToFile();
    }

    generateBlank();
}

// Default constructor: pick random word
Word::Word() {
    loadPossibleWords();
    if (!_possibleWords.empty()) {
        int randomIndex = rand() % _possibleWords.size();
        _word = _possibleWords[randomIndex];
        generateBlank();
    }
}

// Return the full word
string Word::getWord() {
    return _word;
}

// Return the word progress (underscores + correct letters)
string Word::getWordSoFar() {
    return _wordSoFar;
}

// Return incorrect letters guessed so far
vector<char> Word::getIncorrectLetters() {
    return _incorrectLetters;
}

// Check if the word contains the letter
bool Word::containsLetter(char letter) {
    letter = tolower(letter);
    bool contains = false;

    for (size_t i = 0; i < _word.length(); i++) {
        if (_word[i] == letter) {
            contains = true;
            _wordSoFar[i] = _word[i];
        }
    }

    if (!contains) {
        // Avoid duplicates
        if (find(_incorrectLetters.begin(), _incorrectLetters.end(), letter) == _incorrectLetters.end()) {
            _incorrectLetters.push_back(letter);
        }
    }

    return contains;
}

// Load words from file and ensure minimum of 30 diverse words
void Word::loadPossibleWords() {
    ifstream MyFile("words.txt");
    _possibleWords.clear();

    if (MyFile.is_open()) {
        string text;
        while (getline(MyFile, text, ',')) {
            if (!text.empty()) {
                _possibleWords.push_back(text);
            }
        }
        MyFile.close();
    }
    else {
        cerr << "Warning: Could not open words.txt, will create new file." << endl;
    }

    // Diverse fallback words
    vector<string> fallbackWords = {
        "apple", "banana", "cat", "dog", "sun",                  // very easy
        "guitar", "puzzle", "jungle", "mountain", "window",     // medium
        "algorithm", "astronomy", "quarantine", "xylophone", "labyrinth", // hard
        "elephant", "library", "ocean", "volcano", "butterfly", // medium
        "microscope", "telescope", "cactus", "pyramid", "diamond", // medium-hard
        "symphony", "chameleon", "hologram", "rhapsody", "conundrum" // harder
    };

    // Fill up to 30 words
    for (const auto& word : fallbackWords) {
        if (_possibleWords.size() >= 30) break;
        if (find(_possibleWords.begin(), _possibleWords.end(), word) == _possibleWords.end()) {
            _possibleWords.push_back(word);
        }
    }

    saveToFile();
}

// Generate underscores for the word
void Word::generateBlank() {
    _wordSoFar = string(_word.length(), '_');
}

// Check if word is fully guessed
bool Word::isComplete() {
    return _word == _wordSoFar;
}

// Save current list of words back to file
void Word::saveToFile() {
    ofstream myFile("words.txt");
    if (!myFile.is_open()) {
        cerr << "Error: Could not open words.txt for writing" << endl;
        return;
    }

    for (size_t i = 0; i < _possibleWords.size(); i++) {
        myFile << _possibleWords[i];
        if (i < _possibleWords.size() - 1) {
            myFile << ",";  // Add comma between words
        }
    }

    myFile.close();
}
