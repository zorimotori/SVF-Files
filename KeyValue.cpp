#include<iostream>
#include "String.h"
#include "KeyValue.h"

/// Имплементация на клас KeyValue.

/**
 * Конструктор по подразбиране. Член-данните на класа автоматично се инициализират от конструктора по подразбиране на класа String.
*/

KeyValue::KeyValue() {} 

/**
 * Конструктор с параметър, който иницилизира член-данната key с подадения String _key.
*/

KeyValue::KeyValue(String _key) : key(_key) {}

/**
 * Конструктор с 2 параметъра, който иницилизира както key, така и value, със съответните подадени стойности.
*/ 

KeyValue::KeyValue(String _key, String _value) : key(_key), value(_value) {}

/**
 * Конструктор за копиране - той е опростен, тъй като данните на класа KeyValue могат да се иницилизират от конструктора за копиране на класа String.
 * Данните на подадения в () обект се използват за иницилиазиране на член-данните на обекта, който в момента се създава.
*/

KeyValue::KeyValue(const KeyValue& other)
{
    this->key = other.key;
    this->value = other.value;
}

/**
 * Предефиниране на оператор=: присвоява стойностите на обекта other на "нашия" this обект.
 * Връща стойностите на this.
*/

KeyValue& KeyValue::operator=(const KeyValue &other)
{
    this->key = other.key;
    this->value = other.value;

    return *this;
}

/**
 * Get-метод за достъпване на частната член-данна key.
*/

String KeyValue::getKey() const
{
    return this->key;
}

/**
 * Get-метод за достъпване на частната член-данна value.
*/

String& KeyValue::getValue()
{
    return this->value;
}