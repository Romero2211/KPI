#include "word.h"
#include <iostream>
#include <ctype.h>

using namespace std;

Word::Word(string w) {
    word = w;
}

string Word::getWord() {
    return word;
}

int Word::countDigits() {
    int count = 0;
    for (int i = 0; i < word.length(); i++) {
        if (isdigit(word[i])) {
            count++;
        }
    }
    return count;
}
