#include <iostream>
#include "Figures.h"
using namespace std;

class Line : public Figures
{
public:
    Line(KeyArray& _parameters) : Figures(_parameters) {}

    String toString()
    {
        return getName() + " " +
            getParStr("x1") + " " + getParStr("y1") + " " +
            getParStr("x2") + " " + getParStr("y2");
    }
    
    String getName()
    {
        return String("Line");
    }

    bool containsPoint(int x, int y)
    {
        return false;
    }

    virtual bool contains(Figures& fig)
    {
        return false;
    }

    void translate(int horizontal, int vertical)
    {
        int x1 = getPar("x1");
        int y1 = getPar("y1");
        int x2 = getPar("x2");
        int y2 = getPar("y2");
        
        x1 += horizontal;
        y1 += vertical;
        x2 += horizontal;
        y2 += vertical;
        
        setPar("x1", x1);
        setPar("y2", y1);
        setPar("x2", x2);
        setPar("y2", y2);
    }
};