#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "processor_XML.h"
#include "element.h"

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
    e_SET,
    e_CHILDREN,
    e_CHILD,
    e_TEXT,
    e_DELETE_ATTRIBUTE,
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
                                    "SET",
                                    "CHILDREN",
                                    "CHILD",
                                    "TEXT",
                                    "DELETE_ATTRIBUTE",
                                    "NEWCHILD",
                                    "XPATH",
                                    "UNKNOWN"};

/// The class where all of the functionality with the commands is made
/// Singleton class
class Commands
{
private:
    Commands() = default;

    Processor instance;
    string path;

    // function toUpper for the inputted commands
    void toUpper(string &given_command);

    /// function used for converting stream to string
    string convertStreamToString(std::ifstream &in);

    // function which get the index of the inputted command from the local list
    int findCommandIndex(string &given_command);

    // /// recursive helper function for select; - not using anymore
    // void selectRec(const string &id, const string &key, Element &element);

    /// function for parsing the Xpath
    void parseXPath(const string &XPath);

public:
    vector<Element *> extractedElements;

    /// function for getting an instance
    static Commands &getInstance()
    {
        static Commands ref;
        return ref;
    }
    /// helper function used to check if a path to given file is valid
    static bool checkIfPathIsValid(string path);
    /// deleted operator=
    Commands &operator=(const Commands &e) = delete;
    /// deleted copy constr
    Commands(const Commands &e) = delete;

    // basic functions
    /// returns reference to the extracted root of XML elem
    Element &open(const string &path);

    /// closing the file
    void close();

    // saving changes on file
    void save();

    /// the command requires a path - where to be saved the file.
    void saveAs(const string &path);

    /// function help - prints the basic menu
    // void help(); -- in interface
    
    // XML functions

    /// prints the read info from the XML file and prints the output in formated version
    void print();

    /// prints a value of attribute by given ID of element and key of attribute
    ///Извежда стойност на атрибут по даден идентификатор на елемента и ключ на атрибута
    void select1(const string &id, const string &key);

    // recursive version
    // void select(const string &id, const string &key);

    /// sets value of attribute
    void set(const string &id, const string &key, const string &value);

    /// prints all nested elements of the given element
    void children(const string &id);

    /// prints the n'th child of the element
    void child(const string &id, int index);

    /// prints the text of the element
    void text(const string &id);

    /// deletes an attribute of element by given key
    void deleteAttribute(const string &id, const string &givenKey);

    /// adds a new child to Element, which has only ID, nothing else
    void newchild(const string &id);

    ///операции за изпълнение на прости XPath 2.0 заявки към даден елемент, която връща списък от XML елементи
    /// returns a list of simple XPath 2.0 operations for given elemnts(menu)
    /// in the given list(menu) - you have some options and commands for the chosen element
    void xpath(const string &id, const string &XPath);

    /// other functions
    /// function used for extracting all of the elements and storing them in a vector
    void extractElements(Element &elem);
    /// function for setting a processor
    void setProcessor(const Processor &givenPr);
};

#endif // _COMMANDS_