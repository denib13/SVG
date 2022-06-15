#include <iostream>
#include "SVGParser.h"
#include "MyString.h"

int main()
{
    SVGParser p;
    p.help();
    p.open("figures.svg");
    p.print();
}
