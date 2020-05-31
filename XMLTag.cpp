#include "String.h"
#include "XMLTag.h"
#include "KeyArray.h"
#include "DynArray.h"

/// Имплементация на класа XMLTag.

/// Конструктор по подразбиране: задава стойност на булевата променлива textTag -> false, т.е по подразбиране четем таг с параметри.

XMLTag::XMLTag() : textTag(false) {}

/**
 * Конструктор с параметри: параметрите са от тип String и тип bool.
 * textTag се иницилизира със стойността на _textTag, която по подразбиране е false, но може да бъде променяна, като промяната се указва допълнително.
 * Ако член-данната textTag е зададена да бъде true, инициализираме член-данната text с подадедия параметър str.
 * Ако член-данната textTag остане false, инициализираме член-данната tagName с попадения параметър str.
*/

XMLTag::XMLTag(String str, bool _textTag) : textTag(_textTag) 
{
    if(textTag)
    {
        this->text = str;
    }
    else
    {
        this->tagName = str;
    }
}

/**
 * Get-метод getName(): осигурява достъп до частната член-данна tagName.
*/

String& XMLTag::getName()
{
    return this->tagName;
}

/// Get-метод getPar(): осигурява достъп до масива с параметри от тип KeyArray.

KeyArray& XMLTag::getPar()
{
    return this->parameters;
}

/// Get-метод getChildren(): осигурява достъп до динамичния масива от подтагове.

DynArray<XMLTag*>& XMLTag::getChildren()
{
    return this->children;
}

/**
 * Метод getCode(): възстановява кода на xml-таговете по зададени параметри.
 * Параметърът indent по подразбиране е зададен = 0; Той показва отстъпа от началото на реда. 
 * При главните тагове отстъп няма, но при подтаговете такъв се задава, за да се подравнят правилно.
 * В началото на тялото на метода създаваме обект от клас String с името result; в него ще съхраним възстановения по параметрите код.
 * Нужно е да се направи проверка дали таг-ът, който ще се чете, всъщност не е текстов. Ако е така текстът директно се връща, без да се очакват думи и параметри.
 * След това чрез for цикъл се осигурява нужния отстъп от началото на реда под формата на интервали.
 * Ако тагът е главен и следователно indent = 0, for цикълът не върши никаква работа.
 * Преминава се на следващата стъпка - прибавят се < и tagName, които присъстват при таговете в SVG файловете.
 * С помощта на for цикъл към тага се добавят и параметрите със съответния им синтаксис. Броят на параметрите се разбира при извикването на метода length() от класа KeyArray.
 * Ако length() = 0, тогава считаме, че параметрите са 0 на брой. Съответно преминаваме към затваряне на тага.
 * Нужно е да се добавят и подтаговете, ако такива съществуват.
 * Това става чрез for цикъл, който ще се изпълнява само ако размера на масива, в който се съхраняват подтаговете, е > 0.
 * Чрез рекурсия извикваме метода getCode(), който възстановява кода на подтага за всеки един подтаг children. 
 * След това подтаговете children се добавят към обекта result.
 * Тъй като SVG файловете започват и завършват съотетно с отварящ и затварящ тагове, които имат различен синтаксис, показан в клас Parser, 
 * след добавянето на подтаговете е нужно да се прибави към result и затварящ таг. 
*/

String XMLTag::getCode(int indent) 
{
    String result = "";
    if(textTag)
    {
        return this->text;
    }

    for(int i = 0; i < indent; i++)
    {
        result = result.concat(" ");
    }

    result = result.concat("<");
    result = result.concat(tagName);
    for(int i = 0; i < parameters.length(); i++)
    {
        result = result.concat(" ");
        result = result.concat(parameters.getKeyValue(i).getKey());
        result = result.concat("=\"");
        result = result.concat(parameters.getKeyValue(i).getValue());
        result = result.concat("\"");
    }

    if(children.length() == 0)
    {
        result = result.concat(" />\n");
        return result;
    }

    result = result.concat(">\n");
    for(int i = 0; i < children.length(); i++)
    {
        result = result.concat(children[i]->getCode(indent + 2));
    }
    
    for(int i = 0; i < indent; i++)
    {
        result = result.concat(" ");
    }
    result = result.concat("</");
    result = result.concat(tagName);
    result = result.concat(">\n");

    return result;
}