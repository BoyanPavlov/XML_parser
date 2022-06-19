#include <iostream>
#include <fstream>
#include "customExceptions.h"
#include "commands.h"

using std::cin;
using std::cout;
using std::endl;
using std::fstream;
using std::string;
#ifndef _INTERFACE
#define _INTERFACE


///Interface classed used for communication between the user and the program
class Interface
{
private:
    // unnecessary variable for better view;
    const string line = "=============================\n";

    Interface &instance = Interface::getInstance();

    int openChosen();

    int entrance();

    int exitChosen(bool saved);

    Interface() = default;

public:
    static Interface &getInstance()
    {
        static Interface ref;
        return ref;
    }

    Interface &operator=(const Interface &e) = delete;
    Interface(const Interface &e) = delete;
    
    void start();
};
#endif // _INTERFACE