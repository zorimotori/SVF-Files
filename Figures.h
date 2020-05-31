#ifndef FIGURES_H_
#define FIGURES_H_

#include "String.h"
#include "KeyArray.h"
#include "XMLTag.h"

class Figures
{
protected:
    KeyArray parameters;
     
public:
    Figures(KeyArray& _parameters);

    void initXMLTag(XMLTag& tag);
    int getPar(String key);
    String getParStr(String key);
    void setPar(String key, int value);
    void setParStr(String key, String value);

    virtual String toString() = 0;
    virtual String getName() = 0;
    virtual bool containsPoint(int x, int y) = 0;
    virtual bool contains(Figures& fig) = 0;
    virtual void translate(int vertical, int horizontal) = 0;
};

#endif