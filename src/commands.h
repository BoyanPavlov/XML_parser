#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef _COMMANDS_
#define _COMMANDS_

///class used for commands in the program
class Commands
{
private:
    
public:
    Commands(/* args */);

///prints the read info from the XML file and prints the output in formated version
//print()

///prints a value of attribute by given ID of element and key of attribute
///Извежда стойност на атрибут по даден идентификатор на елемента и ключ на атрибута
// select

/// sets value of attribute
// void set(const string& value);

/// returns vector of all nested elements of the given element
// const vector <Element>& children();

///returns the n'th child of the element
// const Element& child(int index);

///returns the text of the element
// const string& text()const;

///deletes an attribute of element by given key
// void delete(const string& givenKey);

///adds a new child to Element, which has only ID, nothing else
// newchild(const string& IDOfnewChild);

///операции за изпълнение на прости XPath 2.0 заявки към даден елемент, която връща списък от XML елементи
//xpath();
};

Commands::Commands(/* args */)
{
}

#endif // _COMMANDS_