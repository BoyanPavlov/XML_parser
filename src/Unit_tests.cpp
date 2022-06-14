#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "element.h"
#include "processor_XML.h"

using std::string;
using std::vector;

TEST_CASE("function:isOpeningTagIsClosingOr_")
{
    Processor pr;
    SECTION("opening tag")
    {
        string text = "<something>";
        int from = 0;
        int result = pr.isOpeningTagIsClosingOr_(text, from);
        REQUIRE(result == opening_tag);
    }
    SECTION("closing tag")
    {
        string text = "</something>";
        int from = 0;
        int result = pr.isOpeningTagIsClosingOr_(text, from);
        REQUIRE(result == closing_tag);
    }
    SECTION("text1")
    {
        string text = "something";
        int from = 0;
        int result = pr.isOpeningTagIsClosingOr_(text, from);
        REQUIRE(result == text_tag);
    }
    SECTION("text2")
    {
        string text = "123something";
        int from = 0;
        int result = pr.isOpeningTagIsClosingOr_(text, from);
        REQUIRE(result == text_tag);
    }
}

TEST_CASE("function:skipSpaces")
{
    Processor pr;
    SECTION("skipSpacess1")
    {
        string text = "    <something>";
        int from = 0;
        pr.skipSpaces(text, from);
        REQUIRE(text[from] == '<');
    }
    SECTION("skipSpacess2")
    {
        string text = "<    something>";
        int from = 1;
        pr.skipSpaces(text, from);
        REQUIRE(text[from] == 's');
    }
    SECTION("skipSpacess3")
    {
        string text = "     ";
        int from = 0;
        pr.skipSpaces(text, from);
        REQUIRE(text.size() == from);
    }
}

TEST_CASE("function:isLetter")
{
    Processor pr;
    SECTION("letter")
    {
        char letter = 'a';
        REQUIRE(pr.isLetter(letter) == true);
    }
    SECTION("number")
    {
        char letter = '1';
        REQUIRE(pr.isLetter(letter) == false);
    }
}

TEST_CASE("function:extractNameOfElement")
{
    Processor pr;
    SECTION("name1")
    {
        string name = "< motherfucker>";
        string expectedOutput = "motherfucker";
        int from = 1;
        pr.skipSpaces(name, from);
        string extracted = pr.extractNameOfElement(name, from);
        REQUIRE(expectedOutput == extracted);
    }
    SECTION("name2")
    {
        string name = "<hello>";
        string expectedOutput = "hello";
        int from = 1;
        string extracted = pr.extractNameOfElement(name, from);
        REQUIRE(expectedOutput == extracted);
    }

    SECTION("name3")
    {
        string name = "<'hello'>";
        string expectedOutput = "";
        int from = 1;
        string extracted = pr.extractNameOfElement(name, from);
        REQUIRE(expectedOutput == extracted);
    }

    SECTION("name4")
    {
        string name = "<      hey'>";
        string expectedOutput = "hey";
        int from = 1;
        pr.skipSpaces(name, from);
        string extracted = pr.extractNameOfElement(name, from);
        REQUIRE(expectedOutput == extracted);
    }
}

TEST_CASE("function:processOpeningTag")
{
    Processor pr;
    SECTION("openingTag1")
    {
        string givenTag = "<motherfucker>";

        Element elem;
        string expectedName = "motherfucker";
        string expectedAttributes = "";
        int expectedLevel = 0;
        int from = 0;

        try
        {
            pr.processOpeningTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        string extractedName = elem.getNameOfElement();
        string extractedAttributes = elem.getAttribute();
        int extractedLevel = elem.getLevel();

        REQUIRE(expectedName == extractedName);
        REQUIRE(expectedAttributes == extractedAttributes);
        REQUIRE(expectedLevel == extractedLevel);
    }

    SECTION("openingTag2")
    {
        string givenTag = "<  hello  >";

        Element elem;
        string expectedName = "hello";
        string expectedAttributes = "";
        int expectedLevel = 0;
        int from = 0;

        try
        {
            pr.processOpeningTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        string extractedName = elem.getNameOfElement();
        string extractedAttributes = elem.getAttribute();
        int extractedLevel = elem.getLevel();

        REQUIRE(expectedName == extractedName);
        REQUIRE(expectedAttributes == extractedAttributes);
        REQUIRE(expectedLevel == extractedLevel);
    }

    SECTION("openingTag3")
    {
        string givenTag = "<hello id=\'0\'>";

        Element elem;
        elem.setLevel(1);
        string expectedName = "hello";
        string expectedAttributes = "id=\'0\'";
        int expectedLevel = 1;
        int from = 0;

        try
        {
            pr.processOpeningTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        string extractedName = elem.getNameOfElement();
        string extractedAttributes = elem.getAttribute();
        int extractedLevel = elem.getLevel();

        REQUIRE(expectedName == extractedName);
        REQUIRE(expectedAttributes == extractedAttributes);
        REQUIRE(expectedLevel == extractedLevel);
    }

    SECTION("openingTag4")
    {
        string givenTag = "<hello id=\'0\'     >";

        Element elem;
        elem.setLevel(1);
        string expectedName = "hello";
        string expectedAttributes = "id=\'0\'";
        int expectedLevel = 1;
        int from = 0;

        try
        {
            pr.processOpeningTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            std::cerr << e.what() << '\n';
        }
        string extractedName = elem.getNameOfElement();
        string extractedAttributes = elem.getAttribute();
        int extractedLevel = elem.getLevel();

        REQUIRE(expectedName == extractedName);
        REQUIRE(expectedAttributes == extractedAttributes);
        REQUIRE(expectedLevel == extractedLevel);
    }
}


