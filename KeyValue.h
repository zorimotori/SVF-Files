#ifndef KEYVALUE_H_
#define KEYVALUE_H_

#include "String.h"

/**
 * Header file с дефиницията на клас KeyValue.
 * Този клас се използва за разделянето на параметрите от SVG файловете на две части.
 * Първата част узначавам с key - това са имената на параметрите: x, y, cx, cy, r, height, width и т.н.
 * Втората част узначавам с value - това е стойността, която се приравнява на името на параметъра и се намира в "" при SVG файловете. 
 * Двете член-данни key & value са от тип String, а за да може да се работи с тях са имплементирани:
 * конструктор по подразбиране, конструктор с параметър, конструктор за копиране, оператор=, както и два get-метода, 
 * които се използват за достъпване на частните член-данни.
*/

class KeyValue
{
private:
    String key;
    String value;

public:
    KeyValue();
    KeyValue(String);
    KeyValue(String, String);
    KeyValue(const KeyValue&);

    //operator String(); // cast operator
    KeyValue &operator=(const KeyValue&);
    String getKey() const;
    String& getValue();
};

#endif