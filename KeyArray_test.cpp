#include <iostream>
#include "KeyArray.h"
using namespace std;

int main()
{
    KeyArray k1;
    k1["test"] = "drundrun";
    std::cout << k1["test"];
    k1["test"] = "proba";
    std::cout << k1["test"];

    return 0;
}