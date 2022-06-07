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

public:
    Element();

    const vector<Element> &getElements() const;
    const string &getNameOfElement() const;
    const string &getAttribute() const;
    const string &getTexts() const;

    void addElement(const Element &element);
    void setNameOfElement(const string &name);
    void setAttribute(const string &attribute);
    void setTexts(const string &text);
};

Element::Element()
    : parent(nullptr)
{
}

#endif // _ELEMENT_