#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef _PROCESSOR_
#define _PROCESSOR_

/// class which manage validation, extraction and processing of the elements and so on
class Processor
{
private:
    void checkForClosingTag();
    void extractAttribute();

    /// function which returns index of first char different from space
    void skipSpaces(const string &text, int &from);

    /// function which checks if a character is letter
    bool isLetter(char);

public:
    /// function which returns string - name of the element
    string extractNameOfElement(const string &text, int &index);
    /// function which returns string - text in the opening tag
    string extractText(const string &text, int &index, bool &equalSignFound);
    /// returns 0 for opening, 1 for closing
    bool isOpeningOrClosingTag(const string &text, int &from);

    void processOpeningTag(const string &text, int &index);
    void processClosingTag(const string &text, int &index);

    Processor(/* args */);

    void parseXML();
};

#endif // _PROCESSOR_