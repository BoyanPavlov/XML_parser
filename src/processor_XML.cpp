#include "processor_XML.h"

// #include <iostream>
// #include <vector>
// #include <string>

// using std::string;
// using std::vector;

// create Element
// get Level - mark level
// if parent == nullptr => level = 0;
// else => level = parent.getlevel() + 1;

// skip spaces till <
// remove spaces
// get word
// remove spaces
// until > - we have text save it in attributes

// push the name of the elements and other characteristics for "opening" in the element

//---- should i add bool for isElementStillOpened?------
//- no you have levels u don't need that. Just check the level

//  jobs done

//===========================================
// logic for containment - recursion here
// read row by row
// while (index != text.size())

// case1
// extract text
// look for "<\"
// case2
//        recursive call

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

int Processor::isOpeningTagIsClosingOr_(const string &text, int &index)
{
    // spaces skipped
    if (text[index] == '<')
    {
        // is definitely a tag
        index++;
        skipSpaces(text, index);
        // determne is closing tag, else it's opening
        if (text[index] == '\\')
        {
            return closing_tag;
        }
        return opening_tag;
    }
    // is definitely not a tag
    return text_tag;
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

string Processor::extractText(const string &text, int &index)
{
    // spaces skipped
    string buffer;
    while (text[index] != '>')
    {
        buffer += text[index];
        index++;
    }
    return buffer;
}

void Processor::processOpeningTag(const string &text, int &index, Element &element)
{
    skipSpaces(text, index);
    // search for "<"
    if (!(text[index] == '<'))
    {
        throw std::invalid_argument("Invalid XML\n");
    }
    index++;
    // skip spaces;
    skipSpaces(text, index);

    string nameOfElement = extractNameOfElement(text, index);
    element.setNameOfElement(nameOfElement);
    skipSpaces(text, index);

    string text = extractText(text, index);

    // extracting Attributes here
    if (text.size() > 0)
    {
        element.setAttribute(text);
    }

    skipSpaces(text, index);

    if (text[index] != '>')
    {
        throw std::invalid_argument("Invalid opening tag");
    }
}

void Processor::processClosingTag(const string &text, int &index, const Element &element)
{
    // spaces skipped
    string name;
    if (text[index] == '<')
    {
        skipSpaces(text, index);
        if (text[index] == '\\')
        {
            name = extractNameOfElement(text, index);
        }
        skipSpaces(text, index);
        if (!(text[index] == '>'))
        {
            throw std::invalid_argument("couldn't find \'<\' \n");
        }
    }
    else
    {
        throw std::invalid_argument("expected closing tag\n");
    }
    // check the name of closing tag if matches with the last opening
    if (name != element.getNameOfElement())
    {
        throw std::invalid_argument("Invalid structure of XML\n");
    }
}

// you need some kind of traversing the string ...
void Processor::parseXML(const string &text, int &index, Element *parent)
{
    Element temp;

    skipSpaces(text, index);
    int opt = isOpeningTagIsClosingOr_(text, index);
    if (opt == opening_tag)
    {
        // opening tag
        processOpeningTag(text, index, temp);

        // extract text or get into recursion
        skipSpaces(text, index);
        if (text[index] == '<')
        {
            // recursion
            parseXML(text, index, &temp);
        }
        else
        {
            string textOfElement = extractText(text, index);
            temp.setText(textOfElement);

            // look for closing tag
            // closing tag found - ok
            // closing tag not found - exception

            skipSpaces(text, index);
            processClosingTag(text, index, temp);
            parent->addElement(temp);
            return;
        }
    }
    else if (opt == closing_tag)
    {
        string name;

        name = extractNameOfElement(text, index);
        skipSpaces(text, index);
        if (!(text[index] == '>'))
        {
            throw std::invalid_argument("couldn't find \'<\' \n");
        }

        if (name != parent->getNameOfElement())
        {
            throw std::invalid_argument("Invalid structure of XML\n");
        }
        parent->getElements().push_back(temp);
        elements.push_back(*parent);
    }
    else
    {
        // am i wrong?!?
        throw std::invalid_argument("Invalid structure of XML\n");
    }
}
