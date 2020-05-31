#include <iostream>
#include "Figures.h"
using namespace std;

class Rectangle : public Figures
{
public:
    Rectangle(KeyArray& _parameters) : Figures(_parameters) {}

    String toString()
    {
        return getName() + " " +
            getParStr("x") + " " + getParStr("y") + " " +
            getParStr("width") + " " + getParStr("height");
    }

    String getName()
    {
        return String("Rectangle");
    }

    bool containsPoint(int x, int y)
    {
        int rx = getPar("x");
        int ry = getPar("y");
        int rwidth = getPar("width");
        int rheight = getPar("height");

        if(x >= rx && x <= rx + rwidth &&
            y >= ry && y <= ry + rheight)
            return true;
        return false;
    }

    virtual bool contains(Figures& fig)
    {
        if(fig.getName() == "Line")
        {
            int lx1 = fig.getPar("x1");
            int ly1 = fig.getPar("y1");
            int lx2 = fig.getPar("x2");
            int ly2 = fig.getPar("y2");

            if(containsPoint(lx1, ly2) && containsPoint(lx2, ly2))
                return true;
            return false;
        }

        if(fig.getName() == "Rectangle")
        {
            int rx2 = fig.getPar("x");
            int ry2 = fig.getPar("y");
            int rwidth2 = fig.getPar("width");
            int rheight2 = fig.getPar("height");
            
            if(containsPoint(rx2, ry2) && containsPoint(rx2 + rwidth2, ry2 + rheight2)) //проверяваме само диагоналните точки
                return true;
            return false;
        }
        
        if(fig.getName() == "Circle")
        {
            int cx = fig.getPar("cx");
            int cy = fig.getPar("cy");
            int r = fig.getPar("r");
            
            if(containsPoint(cx + r, cy) && containsPoint(cx - r, cy) &&
                containsPoint(cx, cy + r) && containsPoint(cx, cy - r))
                return true;
            return false;
        }
        
        return false;
    }

    void translate(int horizontal, int vertical)
    {
        int x = getPar("x");
        int y = getPar("y");

        x += horizontal;
        y += vertical;

        setPar("x", x);
        setPar("y", y);
    }
};