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

/// Interface classed used for communication between the user and the program
class Interface
{
private:
    // unnecessary variable for better view;
    const string line = "=============================\n";
    /// function used for constructing an obj of type Interface
    Interface &instance = Interface::getInstance();
    /// function used after entering the programs - prints menu and so on (command help)
    int openChosen();
    /// function for intro in the program
    int entrance();
    /// function used when you leave the program
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
    /// the main function in this class used for the all comunication and so on..
    void start();
};
#endif // _INTERFACE