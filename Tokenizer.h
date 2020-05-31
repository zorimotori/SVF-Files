#ifndef TOKENIZER_H_
#define TOKENIZER_H_

/**
 * Header file, който съдържа декларация на клас Tokenizer.
 * Tokenizer се използва за разпознаването на команда, подадена от потребителя, и последвалите параметри.
 * Класът има две член-данни - масив от символи str и цяло число pos(position).
 * В публичната си част класът има конструктор с параметър char* и метод next(), който връща масив от символи.
*/
class Tokenizer
{
private:
    char* str;
    int pos;

public:
    Tokenizer(char*);
    
    char* next();
};

#endif