#include <iostream>
#include <fstream>
#include "String.h"
#include "Parser.h"
using namespace std;

int main()
{

    String s1("This is a test");

    String s2("This is another test");

    String s3(s2);
    
    cout << s3 << endl;

    cout << (s1 == s2) << endl;
    
    s1[5] = 'z';
    cout << s1 << endl;

    cout << s2 << endl;

    cout << s1.size() << endl << s2.size() << endl;

    cout << s1.concat(s2) << endl;

    String s4("Try this!");
    String s5("and this");

    s4 += s5;
    cout << s4 << endl;

    s4 += 'k';
    cout << s4 << endl;

    String s6;
    s6 = s4 + 'b'; 
    cout << s6 << endl;

    String str;

    ifstream in("circle01.svg");
    if(in.is_open())
    {   
        in >> str;
    }
    in.close();
    cout << str << endl << endl;

    Parser p1(str);
    p1.parse();


    return 0;
}
