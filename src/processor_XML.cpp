#include "processor_XML.h"

// #include <iostream>
// #include <vector>
// #include <string>

// using std::string;
// using std::vector;

// skip spaces till <
// remove spaces
// get word
// remove spaces
// if next char != > - we have text
//                      if the text has = save it in attributes
//                      else in text
// until >
// jobs done

//===========================================
// logic for containment - recursion here
// read row by row

// search for opening
//   if > found
//       recursive call
//   not found
//       save everything a string buffer
//       search for <\ 


//===========================================

// look for a closing tag
// look for <
// remove spaces
// if next == "\" search for name
// remove spaces
// if next char != ">"  - throw exception

// add bool closed element, can add new one - can be add new element-
// example <b><i> <\i><\b>
// example <b><i> <\b><\i> BAD BAD

bool Processor::isOpeningOrClosingTag(const string &text, int &index)
{
    // spaces skipped
    if (text[index] == '<')
    {
        index++;
    }
    skipSpaces(text, index);
    if (text[index] == '\\')
    {
        return 1;
    }
    return 0;
}

void Processor::skipSpaces(const string &text, int &from)
{
    while (text[from] == ' ')
    {
        from++;
    }
}

bool Processor::isLetter(char letter)
{
    if ('a' <= letter && letter <= 'z' ||
        'A' <= letter && letter <= 'Z')
    {
        return true;
    }
    return false;
}

string Processor::extractNameOfElement(const string &text, int &index)
{
    string buffer;
    while (isLetter(text[index]))
    {
        buffer += text[index];
        index++;
    }
    return buffer;
}

string Processor::extractText(const string &text, int &index, bool &equalSignFound)
{
    // spaces skipped
    string buffer;
    while (text[index] != '\"' || text[index] != '\'' || text[index] != '>')
    {
        if (text[index] == '=')
        {
            equalSignFound = true;
        }

        buffer += text[index];
        index++;
    }
    return buffer;
}

void Processor::processOpeningTag(const string &text, int &index)
{
    skipSpaces(text, index);
    // search for "<"
    // skip spaces;

    string nameOfElement = extractNameOfElement(text, index);
    // element.setNameOfElement(nameOfElement);
    skipSpaces(text, index);

    bool equalSignFound = false;
    string text = extractText(text, index, equalSignFound);

    // extracting Attributes here
    if (equalSignFound)
    {
        // element.setAttribute(text);
    }
    else
    {
        // element.setText(text);
    }

    skipSpaces(text, index);

    if (text[index] != '>')
    {
        throw std::invalid_argument("Invalid opening tag");
    }
}

void Processor::processClosingTag(const string &text, int &index)
{
}
