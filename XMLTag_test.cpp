#include <iostream>
#include "XMLTag.h"
using namespace std;

int main()
{
    XMLTag tag("svg");
    tag.getPar()["width"] = "12cm";
    tag.getPar()["height"] = "4cm";

    XMLTag *c1 = new XMLTag("circle");
    c1->getPar()["r"] = "5cm";
    tag.getChildren().add(c1);

    XMLTag *c2 = new XMLTag("rect");
    c2->getPar()["x"] = "7cm";
    tag.getChildren().add(c2);

    XMLTag *c3 = new XMLTag("line");
    c3->getPar()["y"] = "3cm";
    c2->getChildren().add(c3);
    
    cout << tag.getCode() << endl;

    return 0;
}