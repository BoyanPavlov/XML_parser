#include <iostream>
#include <string>
#include <vector>

#include "element.h"
#include "processor_XML.h"
#include "commands.h"
#include "interface.h"

using std::string;
using std::vector;

int main()
{
    Interface &instance = Interface::getInstance();
    instance.start();

    return 0;
}