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

    int level;

public:
    Element(Element *parent);

    vector<Element> &getElements() const;
    const string &getNameOfElement() const;
    const string &getAttribute() const;
    const string &getTexts() const;
    int getLevel() const;
    Element *getParent() const;

    void addElement(const Element &element);
    void setNameOfElement(const string &name);
    void setAttribute(const string &attribute);
    void setText(const string &text);
    void setLevel(int level);
};

Element::Element(Element *parent)
{
    this->parent = parent;
}

#endif // _ELEMENT_