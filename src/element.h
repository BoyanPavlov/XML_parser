#include <iostream>
#include <vector>
#include <string>

using std::string;
using std::vector;

#ifndef _ELEMENT_
#define _ELEMENT_

/// XML documents are formed as element trees.
/// An XML tree starts at a root element and branches from the root to child elements.
/// All elements can have sub elements (child elements)
class Element
{
private:
    /// parent
    Element *parent;
    /// children
    vector<Element> nested_elements;
    string text;

    string attribute;
    string nameOfElement;

    // TODO - might be in other class
    void checkForClosingTag();
    void extractAttribute();

public:
    Element(/* args */);

    const string &getNameOfElement() const;
};

Element::Element(/* args */)
{
}

#endif // _ELEMENT_