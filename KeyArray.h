#ifndef KEYARRAY_H_
#define KEYARRAY_H_

#include "KeyValue.h"
#include "DynArray.h"

/// Декларация на клас KeyArray.

/**
 * Клас KeyArray се използва за създаването на динамичен масив посредством шаблонния клас DynArray.
 * Елементите на този масив са от тип KeyValue, т.е всеки елемент притежава key & value.
 * Този клас се използва за съхранението на параметри от SVG файовете.
*/

class KeyArray
{
private:
    DynArray<KeyValue> data; ///< Динамичен масив с елементи от клас KeyValue.

public:
    String& operator[](String key); ///< Предефиниран оператор за индексиране на елементи(key) от масива.
    String& operator[](const char *key);

    int length(); ///< Метод, който показва размера на масива data.

    bool hasKey(String key);

    KeyValue& getKeyValue(int i); ///< Get-метод, който позволява достъпването на елемент от частния масива data.
};

#endif
