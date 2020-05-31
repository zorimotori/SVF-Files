#include <iostream>
#include "Tokenizer.h"
using namespace std;

char test[] = "open \"C:\\Temp\\another file.txt\"";;

int main()
{
    Tokenizer t1(test);
    char* token;
    while((token = t1.next()) != nullptr)
    {
        cout << token << " ";
    }

    return 0;
}