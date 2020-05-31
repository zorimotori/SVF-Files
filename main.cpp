#include <iostream>
#include <cstring>
#include "Tokenizer.h"
#include "String.h"
#include "Parser.h"
#include "XMLTag.h"
#include "Figures.h"
#include "Line.cpp"
#include "Circle.cpp"
#include "Rectangle.cpp"
#include "KeyArray.h"
using namespace std;

DynArray<Figures*> list; 

void command();
String readLine();
DynArray<Figures*> xmlToFigures(XMLTag* _xml);
Figures* createFigure(Tokenizer& t);

int main()
{
    command();

    return 0;
}

void command()
{
    String line;
    do
    {
        char *s;

        cout << "> ";
        line = readLine();

        Tokenizer t(line.getString());
        s = t.next();

        if(s == nullptr)
        {
            continue;
        }

        if(strcmp(s, "open") == 0)
        {
            delete[] s;
            s = t.next();
            if(s == nullptr)
                continue;

            String str;

            ifstream in(s);
            if(in.is_open())
            {   
                in >> str;

                Parser p1(str);
                XMLTag* xml = p1.parse();

                in.close();
                list = xmlToFigures(xml);
            }
            delete[] s;
        }

        if(strcmp(s, "print") == 0)
        {
            for(int i = 0; i < list.length(); i++)
            {
                cout << (i + 1) << ". " << list[i]->toString() << endl;
            }
        }

        if(strcmp(s, "erase") == 0)
        {
            delete[] s;
            s = t.next();
            if(s == nullptr)
                continue;
            
            int n = atoi(s) - 1;
            if(n < 0 || n >= list.length()) {
                cout << "There is no figure number " << (n+1) << endl;
                continue;
            }
            
            String name = list[n]->getName();
            list.remove(n);
            cout << "Erased a " << name << " (" << (n+1) << ")" << endl;
            
        }
        
        if(strcmp(s, "create") == 0)
        {
            Figures *f = createFigure(t);
            
            if(f != nullptr)
            {
                list.add(f);
                cout << "Successfilly created " << f->getName() << endl;
            }
        }
        
        if(strcmp(s, "within") == 0)
        {
            Figures *f = createFigure(t);
            
            int n = 1;
            for(int i = 0; i < list.length(); i++)
            {
                if(f->contains(*list[i]))
                {
                    cout << n << ". " << list[i]->toString() << endl;
                    n++;
                }
            }
        }
        
        if(strcmp(s, "translate") == 0)
        {
            char *s;
            int horizontal = 0;
            int vertical = 0;
            while((s = t.next()))
            {
                if(strncmp(s, "horizontal=", 11) == 0)
                {
                    horizontal = atoi(s + 11);
                }
                
                if(strncmp(s, "vertical=", 9) == 0)
                {
                    vertical = atoi(s + 9);
                }
            }
            
            for(int i = 0; i < list.length(); i++)
            {
                list[i]->translate(horizontal, vertical);
            }
            
            cout << "Translated all figures" << endl;
        }
        
        if(strcmp(s, "exit") == 0)
        {
            cout << "Exit" << endl;
            return;
        }

    } while (true);
    
}

Figures* createFigure(Tokenizer& t)
{
    char *name = t.next();
    if(name == nullptr)
        return nullptr;
        
    if(strcmp(name, "rectangle") == 0)
    {
        char *x = t.next();
        char *y = t.next();
        char *width = t.next();
        char *height = t.next();
        char *color = t.next();
        if(x == nullptr || y == nullptr || width == nullptr || height == nullptr)
            return nullptr;
        KeyArray par;
        par["x"] = x;
        par["y"] = y;
        par["width"] = width;
        par["height"] = height;
        if(color != nullptr)
            par["stroke"] = color;
        return new Rectangle(par);
    }
    
    if(strcmp(name, "circle") == 0)
    {
        char *cx = t.next();
        char *cy = t.next();
        char *r = t.next();
        char *color = t.next();
        if(cx == nullptr || cy == nullptr || r == nullptr)
            return nullptr;
        KeyArray par;
        par["cx"] = cx;
        par["cy"] = cy;
        par["r"] = r;
        if(color != nullptr)
            par["stroke"] = color;
        return new Circle(par);
    }
    
    if(strcmp(name, "line") == 0)
    {
        char *x1 = t.next();
        char *y1 = t.next();
        char *x2 = t.next();
        char *y2 = t.next();
        char *color = t.next();
        if(x1 == nullptr || y1 == nullptr || x2 == nullptr || y2 == nullptr)
            return nullptr;
        KeyArray par;
        par["x1"] = x1;
        par["y1"] = y1;
        par["x2"] = x2;
        par["y2"] = y2;
        if(color != nullptr)
            par["stroke"] = color;
        return new Line(par);
    }
    
    return nullptr;
}

String readLine()
{
    String result = "";
    char c;
    while(cin.get(c))
    {
        if(c == '\n')
            break;

        result += c;
    }
    return result;
}

DynArray<Figures*> xmlToFigures(XMLTag* _xml)
{
    DynArray<Figures*> result; // указател към динамичен масив, който съдържа указатели
    DynArray<XMLTag*>& children = _xml->getChildren(); // & - четем без да копираме
    for(int i = 0; i < children.length(); i++)
    {
        if(children[i]->getName() == "line")
        {
            Line *l1 = new Line(children[i]->getPar());
            result.add(l1);
        }
        if(children[i]->getName() == "rect")
        {
            Rectangle *r1 = new Rectangle(children[i]->getPar());
            result.add(r1);
        }
        if(children[i]->getName() == "circle")
        {
            Circle *c1 = new Circle(children[i]->getPar());
            result.add(c1);
        }
    }

    return result;
}