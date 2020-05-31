#include "String.h"
#include "Parser.h"
#include "XMLTag.h"

/// Имплементация на клас Parser.

/// Конструктор с параметър, на който му се подава параметър от тип String. Чрез този параметър конструкторът иницилизира член-данната xmlText.

Parser::Parser(String _xmlText) : xmlText(_xmlText) {}

/**
 * Метод parse().
 * В него се създават две променливи от целочислен тип - start & end и се инициализиррат с 0.
 * Тези променливи по-късно ще се подават като параметри на метода, който ще бъде извикан.
 * Създава се обект tag от тип указател към XMLTag, на който се присвоява стойността, която методът readTag() връща.
 * Прави се проверка която проверява дали обектът tag всъщност "сочи" някъде.
 * Ако не сочи никъде - излизаме от метода parse.
 * Ако сочи някъде, задаваме го да сочи към метода getCode(), така че прочетения таг да се появи като синтактично правилен код.
*/

XMLTag* Parser::parse()
{
    int start = 0; 
    int end = 0;
    XMLTag* tag = readTag(start, end);
    return tag;
}

/**
 * Метод readTag(): разпознава какъв вид е дадения таг, така че да може да се обработи правилно от метода parse().
*/

XMLTag* Parser::readTag(int start, int& end)
{
    XMLTag* newTag = new XMLTag();
    String temp;

    if(readOpenCloseTag(start, end, *newTag))
    {
        consume(start, end);
        return newTag;
    }
    delete newTag;
    newTag = new XMLTag();

    if(readOpenTag(start, end, *newTag))
    {
        consume(start, end);
        while(!readCloseTag(start, end, temp))
        {
            XMLTag* childTag = readTag(start, end);
            if(childTag == nullptr)
            {
                delete newTag;
                return nullptr;
            }
            consume(start, end);
            newTag->getChildren().add(childTag);
        }
        consume(start, end);
        if(newTag->getName() == temp)
        {
            return newTag;
        }
    }

    delete newTag;
    return nullptr;
}

bool Parser::readOpenTag(int start, int& end, XMLTag& tag)
{
    skipSpaces(start);
    if(!readSymbol(start, end, '<'))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readWord(start, end))
    {
        return false;
    }
    tag.getName() = consume(start, end);
    KeyValue kv; 
    while(readParam(start, end, kv))
    {
        consume(start, end);
        tag.getPar()[kv.getKey()] = kv.getValue();
    }
    skipSpaces(start);
    if(!readSymbol(start, end, '>'))
    {
        return false;
    }
    consume(start, end);

    return true;
}

bool Parser::readOpenCloseTag(int start, int& end, XMLTag& tag)
{
    skipSpaces(start);
    if(!readSymbol(start, end, '<'))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readWord(start, end))
    {
        return false;
    }
    tag.getName() = consume(start, end);
    KeyValue kv; 
    while(readParam(start, end, kv))
    {
        consume(start, end);
        tag.getPar()[kv.getKey()] = kv.getValue();
    }
    skipSpaces(start);
    if(!readSymbol(start, end, '/'))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readSymbol(start, end, '>'))
    {
        return false;
    }
    consume(start, end);

    return true;
}

bool Parser::readCloseTag(int start, int& end, String& tagName)
{
    skipSpaces(start);
    if(!readSymbol(start, end, '<'))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readSymbol(start, end, '/'))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readWord(start, end))
    {
        return false;
    }
    tagName = consume(start, end);
    skipSpaces(start);
    if(!readSymbol(start, end, '>'))
    {
        return false;
    }
    consume(start, end);

    return true;
}

bool Parser::readParam(int start, int& end, KeyValue& kv)
{
    skipSpaces(start);
    if(!readWord(start, end))
    {
        return false;
    }
    KeyValue _kv(consume(start, end));
    skipSpaces(start);
    if(!readSymbol(start, end, '='))
    {
        return false;
    }
    consume(start, end);
    skipSpaces(start);
    if(!readSymbol(start, end, '"'))
    {
        return false;
    }
    consume(start, end);
    if(!readTo(start, end, '"'))
    {
        return false;
    }
    _kv.getValue() = consume(start, end);
    if(!readSymbol(start, end, '"'))
    {
        return false;
    }
    consume(start, end);
    
    kv = _kv;
    return true;
}

void Parser::skipSpaces(int& start)
{
    while(xmlText[start] == ' ' || xmlText[start] == '\t' || xmlText[start] == '\n' || xmlText[start] == '\r')
    {
        start++;
    }
}

bool Parser::readWord(int start, int& end)
{
    end = start;
    while((xmlText[end] >= 'a' && xmlText[end] <= 'z') || (xmlText[end] >= 'A' && xmlText[end] <= 'Z') ||
            xmlText[end] == '-' || xmlText[end] == '_' || (xmlText[end] >= '0' && xmlText[end] <= '9'))
    {
        end++;
    }
    if(start != end)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Метод readSymbol(): приема параметри start, end & symbol и връща булева стойност, която е true, ако дадения символ може да бъде прочетен, 
 * и съответно false, ако такъв символ няма и не може да се прочете.
 * Със start и end се задават начална и крайна позиция на четене, като началната е фиксирана -> в началото на дадения символ/дума.
 * Крайната позиция първоначално е равна на началната, но с всеки успешно прочетен символ тя се мести надясно.
 * Съответно ако в масива от тип String срещнем търсения символ, подаден като параметър, той се прочита и позицията end се измества с 1 надясно.
 * За да сме убедени обаче, че нещо наистина е прочетено, трябва да сравним позициите на start и end: 
 * ако те са различни - символът е успешно прочетен и методът връща положителна стойност true;
 * В противен случай като разултат се връща false.
*/

bool Parser::readSymbol(int start, int& end, char symbol)
{
    end = start;
    if(xmlText[end] == symbol)
    {
        end++;
    }
    if(start != end)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Метод consume(): "консумира" даден 
*/

String Parser::consume(int& start, int end)
{
    String word = "";
    for(int i = start; i < end; i++)
    {  
        word += xmlText[i];
    }
    start = end;
    return word;
}

/**
 * Метод readTo(): приема параметри start, end & symbol и връща булева стойност.
 * Параметърът start приема позицията, до която е стигнало "четенето".
 * 
*/

bool Parser::readTo(int start, int& end, char symbol = '"')
{
    while(xmlText[end] != symbol)
    {
        if(xmlText[end] == '\0')
        {
            return false;
        }
        end++;
    }
    return true;
}

/*void debug(int start, int end)
{
    String word = "";
    for(int i = start; i < end; i++)
    {  
        word += xmlText[i];
    }
    std::cout << word << std::endl;
}*/




