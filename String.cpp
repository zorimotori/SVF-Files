#include <iostream>
#include <cstring>
#include <fstream>
#include "String.h"

/// CPP file, който съдържа имплементацията на вече декларирания клас String

/**
 * Метод init(): приема параметър от тип const char* и връща елемент от тип char.
 * В имплементацията му се вижда заделяне на динамична памет с размер, колкото размера на подадения параметър + 1 за \0.
 * След това параметърът с име value се копира в this->string(член-данната на класа String) посредством функцията strcpy().
*/

void String::init(const char* value)
{
    this->string = new char[strlen(value) + 1];
    strcpy(this->string, value);
}

/**
 * Метод size(): връща като отговор размера на масива, за който е извикан.
 * Първо се проверява дали масивът всъщност не е празен(nullptr), а след това неговата дължина се връща посредством функцията strlen().
*/

int String::size() const
{
    if(this->string == nullptr)
    {
        return 0;
    }
    return strlen(this->string);
}

/**
 * Конструктор по подразбиране: индексира масивът string с nullptr(т.е string "не сочи" към дадена памет).
*/

String::String()
{
    this->string = nullptr;
}

/**
 * Кондтруктор с параметър: инициализира динамично заделен масив с дадена стойност посредством метода init().
*/

String::String(const char* _string)
{
    init(_string);
}

/**
 * Конструктор за копиране: приема масив от клас String и връща масив от тип String.
 * При имплементацията първо се проверява дали масивът на "нашия" обект не е еднакъв с масива, с който се опитваме да го инициализираме.
 * След това се прави проверка дали масивът, с който ще иницилизираме, същност не е празен("сочи" към nullptr).
 * Ако е така, тогава и масивът на "нашия" обект се иницилизира с nullptr.
 * Ако първите два случая не са верни преминаваме към динамично заделяне на памет за масива string.
 * Заделената памет е с дължина колкото е дължината на подадения "друг" масив + 1 за \0.
 * След това чрез употребата на for цикъл елементите на "другия" масив се копират в масива на "нашия" обект.
 * Накрая сме длъжни собственоръчно да укажем края на масива this->string чрез поставяне на \0 на последната позиция.
*/

String::String(const String& other)
{
    if(this == &other)
    {
        return;
    }
    if(other.string == nullptr)
    {
        this->string = nullptr;
    }
    else
    {
        string = new char[strlen(other.string) + 1];
        int i;
        for(i = 0; other.string[i]; i++)
        {
            this->string[i] = other.string[i];
        }
        this->string[i] = '\0';
    }
}

/**
 * Предефиниране на оператор=: приема елемент от тип String по референция, за да не се налага да копира целия обект, 
 * а след това връща String по референция, която позволява промените да се приложат върху обекта, на когото викаме operator=.
 * Чрез if(this != &other) условието проверяваме дали двата обекта не са един и същ.
 * В случай, че не са, се извършва проверка дали в първия масив има елементи. Ако има - те се изтриват, за да се подготви масива за приемането на нови елементи. 
 * След това се прави проверка, целяща да покаже, дали вторият масив не е празен. Ако е - и първия се приравнява на nullptr, след което стойността му се връща.
 * Ако двете условия бъдат подминати се заделя динамична памет със същия размер, както при конструктора за копиране.
 * Отново чрез for цикъл елементите от other се копират в this и се връщат към потребителя посредством return *this.
 * */

String& String::operator=(const String &other)
{
    if(this != &other)
    {
        if(this->string != nullptr)
            delete[] this->string;

        if(other.string == nullptr)
        {
            this->string = nullptr;
            return *this;
        }

        this->string = new char[other.size() + 1];
        
        for(int i = 0; i < other.size() + 1; i++)
        {
            this->string[i] = other.string[i];
        }
    }
    return *this;
}

/// Деструктор на класа: освобождава динамично заделената памет.

String::~String()
{
    delete[] string;
}

/**
 * Предефиниране на оператор+=: приема константен параметър word и връща обект от тип String с референция.
 * Дължината на масива this->string бива взета посредством strlen() и бива присвоена на на променливата size.
 * Създава се нов временен масив temp. Заделя се динамична памет с размер size + 2. 
 * Чрез for цикъл елементите от масива string биват копирани в масива temp. 
 * Предпоследната клетка се иницилизира с подадената дума(word), а на последно място се поставя \0.
 * Данните от масива string се освобождават и новите данни от масива temp се поставят на тяхно място.
 * Накрая стойността на обекта се връща. 
*/

String& String::operator+=(const char word)
{
    unsigned int size = strlen(this->string);
    char* temp = new char[size + 2];
    for (int i = 0; i < (size + 2); i++)
    {
        temp[i] = string[i];
    }
    temp[size] = word;
    temp[size + 1] = '\0';
    delete[] string;
    string = temp;
    return *this;
}

/**
 * Предефиниране на оператор+: получава дума от тип const char и връща елемент от тип String
 * При имплементацията се създава нов, резултатен масив, който приема всички елементи на масива string, както и новоподадената дума word.
 * Резултатният масив се връща като отговор при събирането.
*/

String String::operator+(const char word)
{
    String result;
    result += *this;
    result += word;
    return result;
}

/**
 * Предефиниране на оператор+: приема масив от тип String и връща масив от тип String.
 * Посредством дефинирания метод concat() оператор+ "събира" this->string и other.string и връща техния "сбор" като резултат. 
*/

String String::operator+(const String& other)
{
    return this->concat(other);
}

/**
 * Предефиниране на оператор==: приема даден обект от тип String и проверява дали той е равен, или различен от първия.
 * Посредством функцията strcmp() определяме дали this->string = other.string. Ако да - резултатът е true, ако двата стринга са различни - false.
*/

bool String::operator==(String &other)
{
    return strcmp(this->string, other.string) == 0;
}

bool String::operator==(const char *other)
{
    return strcmp(this->string, other) == 0;
}

/**
 * Предефиниране на оператор[]: приема променлива от тип цяло число и връща променлива от тип char&.
 * При подаден индекс i операторът връща символа, който се намира на посочената от индекса позиция в масива string.
*/

char& String::operator[](unsigned int i)
{
    return string[i];
}

/**
 * Предефиниране на оператор+=: приема два обекта от тип String и ги "събира", като резултатът се запаметява в първия string.
 * Операторът работи с *this, тъй като сам по себе си this e указател, а чрез *this ние успяваме да достъпим и стойността, към която указателят сочи.
*/

String& String::operator+=(const String& other)
{
    *this = *this + other;
    return *this;
}

/**
 * Метод concat(): събира/конкатенира два масива от тип String.
 * В тялото на метода се създава нови променливи result & concatSize. concatSize приема размера на двата масива, които предстои да бъдат конкатенирани.
 * При масива на result се заделя динамично памет с размера на concatSize + 1 за \0. 
 * След това посредством for цикъл елементите на this->string се копират в масива result.string. 
 * С помощта на втори for цикъл и елементите на other.string се "залепят" до тези на this->string в result.string.
 * На последната позиция, която се достъпва чрез индекс = concatSize, се поставя и \0.
 * Резултатът, който се съдържа в String result, се връща.
*/

String String::concat(const String& other)
{
    String result;
    unsigned int concatSize;

    concatSize = this->size() + other.size();
    result.string = new char[concatSize + 1];
    
    for(int i = 0; i < this->size(); i++)
    {
        result.string[i] = this->string[i];
    }

    for(int i = 0; i < other.size(); i++)
    {
        result.string[this->size() + i] = other.string[i]; 
    }

    result.string[concatSize] = '\0';
    return result;
}

/**
 * Метод getter - getString(): позволява достъп до частната член-данна string.
*/

char* String::getString()
{
    return this->string;
}

/**
 * Предефиниране на оператор<<: оператор за изходен поток. Подава му се изходен поток out и обект от типа, който искаме да извеждаме.
 * С помощтта на get метода getString() извикан за обекта str, операторът "отпечатва" на екрана String.
*/

std::ostream& operator<< (std::ostream& out, String str)
{
    out << str.getString();
    return out;
}

/**
 * Предефиниране на оператор>>: оператор за входен поток. Подава му се входен поток и обект от типа, който искаме да въвеждаме в паметта.
 * Чрез while цикъл и помощтта на функцията get() докато можем да "четем" символ от входния поток, той се добавя към обекта от клас String.
 * Така успяваме да изчетем целия масив от String, който влиза в паметта.
*/

std::istream& operator>> (std::istream& in, String& str)
{
    str = "";
    char c;
    while(in.get(c))
    {
        str += c;
    }
    return in;
}


