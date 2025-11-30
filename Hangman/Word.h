#ifndef WORD_H
#define WORD_H

#include <string>
#include <vector>
using namespace std;

class Word {
private:
    string _word;
    string _wordSoFar;
    vector<string> _possibleWords;
    vector<char> _incorrectLetters;
    void loadPossibleWords();
    void generateBlank();
    void saveToFile();
public:
    Word();
    Word(string word);
    string getWord();
    bool containsLetter(char letter);
    string getWordSoFar();
    vector<char> getIncorrectLetters();
    bool isComplete();
};

#endif
