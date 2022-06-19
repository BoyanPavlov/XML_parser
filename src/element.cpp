#include "element.h"

Element::Element()
    : parent(nullptr), level(0)
{
}

Element::Element(Element *parent)
    : parent(parent), level(parent->getLevel() + 1)
{
}

vector<Element> &Element::getElements()
{
    return nested_elements;
}
const string &Element::getNameOfElement() const
{
    return nameOfElement;
}
const string &Element::getAttribute() const
{
    return attribute;
}
const string &Element::getTexts() const
{
    return text;
}
int Element::getLevel() const
{
    return level;
}
Element *Element::getParent() const
{
    return parent;
}

void Element::addElement(const Element &element)
{
    nested_elements.push_back(element);
}
void Element::setNameOfElement(const string &name)
{
    nameOfElement = name;
}
void Element::setAttribute(const string &attribute)
{
    this->attribute = attribute;
}
void Element::setText(const string &text)
{
    this->text = text;
}
void Element::setLevel(int level)
{
    this->level = level;
}

std::ostream &operator<<(std::ostream &out, const Element &element)
{
    int numberOfElements = element.getLevel();
    for (int i = 0; i < numberOfElements; i++)
    {
        out << '\t';
    }
    // opening tag
    out << "< " << element.getNameOfElement();
    if (element.getAttribute().size() > 0)
    {
        out << " " << element.getAttribute() << " >";
    }
    else
    {
        out << " >";
    }

    int numberOfNestedElements = element.nested_elements.size();
    for (int i = 0; i < numberOfNestedElements; i++)
    {
        out << '\n';
        operator<<(out, element.nested_elements[i]);
    }
    // closing tag
    if (element.getTexts().size() == 0)
    {
        out << '\n';
        for (int i = 0; i < numberOfElements; i++)
        {
            out << '\t';
        }
    }

    out << element.getTexts() << "</ " << element.getNameOfElement() << " >";

    return out;
}


