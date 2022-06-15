#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "processor_XML.h"

using std::cout;
using std::endl;
using std::fstream;
using std::ifstream;
using std::ofstream;
using std::string;
using std::vector;

#ifndef _COMMANDS_
#define _COMMANDS_

enum Commands_enum
{
    // basic commands
    e_OPEN,
    e_CLOSE,
    e_SAVE,
    e_SAVE_AS,
    e_HELP,
    e_EXIT,
    // needed commands
    e_PRINT,
    e_SELECT,
    e_CHILDREN,
    e_CHILD,
    e_TEXT,
    e_DELETE,
    e_NEWCHILD,
    e_XPATH,
    e_UNKNOWN
};

const vector<string> listOfCommands{// basic commands
                                    "OPEN",
                                    "CLOSE",
                                    "SAVE",
                                    "SAVE_AS",
                                    "HELP",
                                    "EXIT",
                                    // needed commands
                                    "PRINT",
                                    "SELECT",
                                    "CHILDREN",
                                    "CHILD",
                                    "TEXT",
                                    "DELETE",
                                    "NEWCHILD",
                                    "XPATH",
                                    "UNKNOWN"};

/// The class where all of the functionality with the commands is made
/// Singleton class
class Commands
{
private:
    Commands() = default;

    // function toUpper for the inputted commands
    void toUpper(string &given_command);

    /// function used for converting stream to string
    string convertStreamToString(std::ifstream &in);

    // function which get the index of the inputted command from the local list
    int findCommandIndex(string &given_command);

    /// helper function used to check if a path to given file is valid
    bool checkIfPathIsValid(string path);

    Processor instance;
    string path;

public:
    static Commands &getInstance()
    {
        static Commands ref;
        return ref;
    }

    Commands &operator=(const Commands &e) = delete;

    Commands(const Commands &e) = delete;

    /// basic functions
    void open(const string &path);

    /// closing the file
    void close();

    // saving changes on file
    void save();

    /// the command requires a path - where to be saved the file.
    void saveAs(const string &path);

    /// function help - prints the basic menu
    void help();

    /// exits the program
    void exit();

    // XML functions

    /// prints the read info from the XML file and prints the output in formated version
    void print();
    /// prints a value of attribute by given ID of element and key of attribute
    ///Извежда стойност на атрибут по даден идентификатор на елемента и ключ на атрибута
    void select(const string &id, const string &key);

    /// sets value of attribute
    void set(const string &id, const string &key, const string &value);

    /// returns vector of all nested elements of the given element
    const vector<Element> &children(const string &id);

    /// returns the n'th child of the element
    const Element &child(const string &id, int index);

    /// returns the text of the element
    const string &text(const string &id);

    /// deletes an attribute of element by given key
    void deleteAttribute(const string &id, const string &givenKey);

    /// adds a new child to Element, which has only ID, nothing else
    void newchild(const string &IDOfnewChild);

    ///операции за изпълнение на прости XPath 2.0 заявки към даден елемент, която връща списък от XML елементи
    void xpath(const string &id, const string &XPath);
};

#endif // _COMMANDS_