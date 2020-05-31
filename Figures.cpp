#include <iostream>
#include "String.h"
#include "Figures.h"
#include "KeyArray.h"
#include "XMLTag.h"
using namespace std;

Figures::Figures(KeyArray& _parameters)
{
    for(int i = 0; i < _parameters.length(); i++)
    {
        KeyValue kv = _parameters.getKeyValue(i);
        parameters[kv.getKey()] = kv.getValue();
    }
}

void Figures::initXMLTag(XMLTag& tag)
{
    for(int i = 0; i < parameters.length(); i++)
    {
        KeyValue kv = parameters.getKeyValue(i);
        tag.getPar()[kv.getKey()] = kv.getValue();
    }
}

int Figures::getPar(String key)
{
    if(!parameters.hasKey(key))
        return 0;
    return atoi(parameters[key].getString());
}

String Figures::getParStr(String key)
{
    if(!parameters.hasKey(key))
        return "";
    return parameters[key].getString();
}

void Figures::setPar(String key, int value)
{
    char conv[32] = "";
    sprintf(conv, "%d", value);
    parameters[key] = String(conv);
}

void Figures::setParStr(String key, String value)
{
    parameters[key] = value;
}

void help()
{
    cout << "The following commands are supported:\n";
    cout << "open <file>       opens <file>\n";
    cout << "close             closes currently opened file\n";
    cout << "save              saves the currently opened file\n";
    cout << "saveas <file>     saves the currently opened file in <file>\n";
    cout << "help              shows this information\n";
    cout << "exit              exits the program\n";
    cout << "print             prints all figures from the opened file\n";
    cout << "create            creates new figure\n";
    cout << "erase <n>         erases the figure with serial number <n>\n";
    cout << "translate <n>     translates the figure with serial number <n>\n";
    cout << "                  or all existing figures\n";
    cout << "within <option>   displays all figures in certain region\n";
    cout << "                  the region is set through <option>\n";
}