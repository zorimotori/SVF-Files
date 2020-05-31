#ifndef PARSER_H_
#define PARSER_H_

#include "String.h"
#include "XMLTag.h"
#include "KeyValue.h"

/**
 * Декларация на клас Parser.
 * Задачата на този клас е да дефинира различните видове обекти, които се срещат в един SVG файл, така че при отваряне на SVG файл, 
 * програмата да може да го разпознае, прочете и работи с него.
 * Класът съдържа член-данна от тип String, с помощта на която ще се обработва текст от SVG файл.
 * Дефинирани са конструктор с параметър, както и списък от методи.
*/

class Parser
{
private:
    String xmlText;

public:
    Parser(String _xmlText);

    XMLTag* parse(); ///< Метод, който свързва прочетения SVG файл с клас XMLTag, който да разпознае съдържанието във файла.

    XMLTag* readTag(int start, int& end); ///< Метод, който прочита таг в зависимост от това какъв е видът на тага.
    bool readOpenTag(int start, int& end, XMLTag& tag); ///< Метод, който съдържа алгоритъм за разчитането на отварящ таг.
    bool readOpenCloseTag(int start, int& end, XMLTag& tag); ///< Метод, който съдържа алгоритъм за разчитането на комбиниран таг(таг, който е отварящ и затварящ едновременно).
    bool readCloseTag(int start, int& end, String& tagName); ///< Метод, който съдържа алгоритъм за разчитането на затварящ таг.
    bool readParam(int start, int& end, KeyValue& kv); ///< Метод, с помощта на който разчитаме параметрите в таговете.
    void skipSpaces(int& start); ///< Метод, който се грижи за пропускането на интервали, табулации, нов ред и преминаването към следващ текст.
    bool readWord(int start, int& end); ///< Метод, който съдържа алгоритъм за разчитане на дума.
    bool readSymbol(int start, int& end, char symbol); ///< Метод, който съдържа алгоритъм за разчитане на даден символ.
    String consume(int& start, int end); ///< Метод, който "консумира" всичко прочетено, така че то да не се чете повторно.
    bool readTo(int start, int& end, char symbol); ///< Метод, който чете до срещането на даден символ(в случая ").
};

#endif