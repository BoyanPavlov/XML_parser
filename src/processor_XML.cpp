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
        if (text[index] == '/')
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
    while (text[from] == ' ' || text[from] == '\n' || text[from] == '\t')
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
    while (text[index] != '>' && text[index] != '<')
    {
        buffer += text[index];
        index++;
    }
    int tempIndex = 0;

    while (tempIndex != buffer.size())
    {
        if (buffer[tempIndex] == ' ' && (!isLetter(buffer[tempIndex + 1])))
        {
            // buffer.erase(buffer.begin() + tempIndex + 1);
            buffer.erase(buffer.begin() + tempIndex);
        }
        else if (buffer.back() == ' ')
        {
            buffer.pop_back();
        }
        tempIndex++;
    }
    return buffer;
}

string Processor::extractAttribute(const string &text, int &index)
{
    // spaces skipped
    string buffer = extractText(text, index);

    int tempIndex = 0;
    char c1;
    char c2;
    while (tempIndex != buffer.size())
    {
        if ((buffer[tempIndex] == '\'' || buffer[tempIndex] == '\"') && buffer[tempIndex + 1] == ' ')
        {
            c1 = buffer[tempIndex];
            c2 = buffer[tempIndex + 1];
            buffer.erase(buffer.begin() + tempIndex + 1);
            continue;
        }
        tempIndex++;
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

    // extracts only letters and puts them into buffer - spaces must be skipped
    string nameOfElement = extractNameOfElement(text, index);
    element.setNameOfElement(nameOfElement);
    skipSpaces(text, index);

    // string extractedText = extractText(text, index);
    string extractedText = extractAttribute(text, index);

    // extracting Attributes here
    if (extractedText.size() > 0)
    {
        element.setAttribute(extractedText);
    }

    skipSpaces(text, index);

    if (text[index] != '>')
    {
        throw std::invalid_argument("Invalid opening tag");
    }
    index++;
}

void Processor::processClosingTag(const string &text, int &index, const Element &element)
{
    // spaces skipped
    string name;
    char curChar = text[index];
    if (text[index] == '<')
    {
        index++;
        skipSpaces(text, index);
        if (text[index] == '/')
        {
            index++;
            skipSpaces(text, index);
            name = extractNameOfElement(text, index);
        }
        skipSpaces(text, index);
        if (!(text[index] == '>'))
        {
            throw std::invalid_argument("couldn't find \"</\" \n");
        }
        index++;
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
    // std::cout << "succesfull\n";
}

void Processor::parseChildrenForTag(const string &text, int &index, Element *current)
{
    if (text.size() <= index + 1)
    {
        return;
    }

    Element child(current);

    skipSpaces(text, index);

    int tempIndex = index;
    int opt = isOpeningTagIsClosingOr_(text, index);

    if (opt == opening_tag)
    {
        index = tempIndex;
        processOpeningTag(text, index, child);
        parseChildrenForTag(text, index, &child);
    }
    else if (opt == closing_tag)
    {
        index = tempIndex;
        processClosingTag(text, index, *current);
        current->getParent()->addElement(*current);
        parseChildrenForTag(text, index, current->getParent());
    }
    else
    {
        // processing text
        string textOfElement = extractText(text, index);
        current->setText(textOfElement);

        // look for closing tag
        // closing tag found - ok
        // closing tag not found - exception

        skipSpaces(text, index);
        processClosingTag(text, index, *current);
        current->getParent()->addElement(*current);
        parseChildrenForTag(text, index, current->getParent());
    }
}

void Processor::parseXML()
{
    // text is extracted from file succesfully and ready for parsing;
    static Element tempRoot;
    tempRoot.setLevel(-1);

    parseChildrenForTag(text, index, &tempRoot);
    if (tempRoot.getElements().size() == 1)
    {
        root = &tempRoot.getElements()[0];
    }
    else
    {
        std::cout << "Mustn't enter here, error in parseXML function";
    }
}

Processor::Processor()
    : index(0)
{
}

void Processor::setText(const string &givenText)
{
    text = givenText;
}

Element &Processor::getRoot()
{
    return *root;
}
const string &Processor::getText()
{
    return text;
}
const int &Processor::getIndex()
{
    return index;
}

string Processor::getKeyOfAttribute(const string &givenAttribute, Element &elem)
{
    string attribute = elem.getAttribute();
    string attributeKey;
    int i = 0;

    while (attribute[i] != '=' && ((i + 1) != attribute.size()))
    {
        attributeKey += attribute[i];
        i++;
    }
    return attributeKey;
}

string Processor::getValueOfKey(const string &givenAttribute, Element &elem)
{
    string attribute = elem.getAttribute();
    string attributeVal;
    int i = 0;
    while (attribute[i] != '=')
    {
        i++;
    }
    while (i != attribute.size())
    {
        attributeVal += attribute[i];
        i++;
    }
    return attributeVal;
}