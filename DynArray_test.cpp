#include <iostream>
#include "DynArray.h"
using namespace std;

int main()
{
    DynArray<int> d1;

    d1.add(1);
    d1.add(2);
    d1.add(3);
    d1.add(4);
    d1.add(5);
    d1.add(6);

    d1[3] = 8;

    for (int i = 0; i < d1.length(); i++)
    {
        cout << d1[i] << " ";
    }
    cout << endl;

    cout << d1.length() << endl;

    d1.remove(2);

    for (int i = 0; i < d1.length(); i++)
    {
        cout << d1[i] << " ";
    }
    cout << endl;

    cout << d1.length() << endl;


    return 0;
}