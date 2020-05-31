#ifndef XMLTAG_H_
#define XMLTAG_H_

#include "String.h"
#include "KeyArray.h"
#include "DynArray.h"

/// Деекларация на клас XMLTag.

/**
 * Този клас ще се използва за разпознаване на различните видове xml тагове, които се срещат в един SVG файл.
 * Има няколко член-данни, конструктори и методи.
*/

class XMLTag
{
private:
    String tagName; ///< Член-данна, която да пази името на tag-а.
    String text; ///< Член-данна, която ще пази текст, ако такъв има в SVG файл-а.
    bool textTag; ///< Булева променлива, която проверява един таг дали е с параметри, или с текст.
    KeyArray parameters; ///< Член-данна от клас KeyArray, който е масив от параметри.
    DynArray<XMLTag*> children; ///< Член-данна, която показва дали даден таг съдържа в себе си подтагове, които наричаме негови "деца".

    /**
     * Член-данната children е от тип DynArray - шаблонен клас за масив, който в случая съдържа елементи, които са указатели към обекти от клас XMLTag.
    */

public:
    XMLTag(); ///< Конструктор по подразбиране.
    XMLTag(String str, bool _textTag = false); ///< Конструктор с параметри.

    /**
     * Get-методи за достъп до член-данните, които са частни.
    */

    String& getName();
    KeyArray& getPar();
    DynArray<XMLTag*>& getChildren();
    String getCode(int indent = 0); // възстановява кода по параметрите му
};

#endif