#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include "word.h"

using namespace std;

int main() {
    vector<Word> words;
    string input;

    cout << "Enter the words (press Enter for a new line, or ESC to exit):" << endl;
    char ch = _getch();
    while (ch != 27) {
        if (ch == '\r') { // Enter key
            words.push_back(Word(input));
            input.clear();
            cout << endl;
        }
        else if (ch == '\b' && input.length() > 0) {
            input.pop_back();
            cout << "\b \b";
        }
        else if (isprint(ch)) {
            input.push_back(ch);
            cout << ch;
        }
        ch = _getch();
    }

    cout << "\nA list of words:" << endl;
    for (int i = 0; i < words.size(); i++) {
        cout << words[i].getWord() << endl;
    }

    int maxDigits = -1;
    string maxDigitsWord;
    for (int i = 0; i < words.size(); i++) {
        int digitsCount = words[i].countDigits();
        if (digitsCount > maxDigits) {
            maxDigits = digitsCount;
            maxDigitsWord = words[i].getWord();
        }
    }

    cout << "\nThe word with the most digits: " << maxDigitsWord << endl;
    cout << "\nThe number of digits in the word: " << maxDigits << endl;

    return 0;
}
