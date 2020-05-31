#include "KeyValue.h"
#include "KeyArray.h"
#include "DynArray.h"

/// Имплементацията на клас KeyArray.

/**
 * Предефиниране на оператор[]: той приема key(име на параметъра) и връща съответната му стойност(value), която е от тип String.
 * Чрез for цикъл проверяваме дали подадения като параметър key се среща вече в масива KeyArray, и ако да - връщаме съответстващата му стойност.
 * За извъртане на цикъла ползваме метода length(), който ни дава дължината на масива data.
 * В тялото на цикъла използваме get-методите getKey() & getValue() на класа KeyValue.
 * Ако излезем от цикъла без да върнем дадена стойност, тъй като не сме открили срещане на името на параметъра(key), 
 * създаваме нов обект от клас KeyValue, чиято член-данна key инициализираме посредством конструктора с параметър.
 * Вече имаме елемент KeyValue, който има подадения като параметър key, следователно операторът трябва да върне неговата стойност.
 * Това става като към масива data добавим новосъздадения обект с помощта на метода add() и едновременно с това извикаме get-метода на този обект
 * getValue(), за да видим неговата стойност.
*/

String& KeyArray::operator[](String key)
{
    for(int i = 0; i < data.length(); i++)
    {
        if(data[i].getKey() == key)
        {
            return data[i].getValue();
        }
    }
    KeyValue temp(key); // създаваме обект от тип KeyValue чрез конструктор с параметър
                        // temp прави копие на елемента key от KeyValue
                        // връщаме ключа 

    return data.add(temp).getValue();
}

String& KeyArray::operator[](const char *key)
{
    for(int i = 0; i < data.length(); i++)
    {
        if(data[i].getKey() == key)
        {
            return data[i].getValue();
        }
    }
    String skey = String(key);
    KeyValue temp(skey); // създаваме обект от тип KeyValue чрез конструктор с параметър
                        // temp прави копие на елемента key от KeyValue
                        // връщаме ключа

    return data.add(temp).getValue();
}


/// Метод length(): връща размера на масива data.

int KeyArray::length()
{
    return data.length();
}

bool KeyArray::hasKey(String key)
{
    for(int i = 0; i < data.length(); i++)
        if(data[i].getKey() == key)
            return true;
    return false;
}

/**
 * Get-метод getKeyValue(), на който подаваме параметър i(index) от целочислен тип.
 * Посредством горе предефинирания оператор[] връщаме елемента с пореден номер i, който е от клас KeyValue.
*/

KeyValue& KeyArray::getKeyValue(int i)
{
    return data[i];
}
