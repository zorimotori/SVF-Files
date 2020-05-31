#include <iostream>
#include "Figures.h"
using namespace std;

class Circle : public Figures
{
public:
    Circle(KeyArray& _parameters) : Figures(_parameters) {}

    String toString()
    {
        return getName() + " " +
            getParStr("cx") + " " + getParStr("cy") + " " +
            getParStr("r");
    }

    String getName()
    {
        return String("Circle");
    }

    bool containsPoint(int x, int y)
    {
        int cx = getPar("cx");
        int cy = getPar("cy");
        int r = getPar("r");

        int dx = abs(cx - x);
        int dy = abs(cy - y);

        if(dx * dx + dy * dy <= r * r)
            return true;
        return false;
    }

    virtual bool contains(Figures& fig) //проверява дали фигурата се съдържа в кръга
    {
        if(fig.getName() == "Line")
        {
            int lx1 = getPar("x1");
            int ly1 = getPar("y1");
            int lx2 = getPar("x2");
            int ly2 = getPar("y2");

            if(containsPoint(lx1, ly1) && containsPoint(lx2, ly2))
                return true;
            return false;
        }

        if(fig.getName() == "Rectangle")
        {
            int rx = fig.getPar("x");
            int ry = fig.getPar("y");
            int rwidth = fig.getPar("width");
            int rheight = fig.getPar("height");

            if(containsPoint(rx, ry) && containsPoint(rx + rwidth, ry) &&
                containsPoint(rx, ry + rheight) && containsPoint(rx + rwidth, ry + rheight))
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
        int cx = getPar("cx");
        int cy = getPar("cy");

        cx += horizontal;
        cy += vertical;

        setPar("cx", cx);
        setPar("cy", cy);
    }
};