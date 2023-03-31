#pragma once
#ifndef WORD_H
#define WORD_H

#include <string>

class Word {
private:
    std::string word;

public:
    Word(std::string w);

    std::string getWord();

    int countDigits();
};

#endif
