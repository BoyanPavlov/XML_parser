#include "..\catch.hpp"
#include <iostream>
#include <string>
#include <vector>

#include "element.h"
#include "processor_XML.h"
#include "commands.h"

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

TEST_CASE("function:processClosingTag")
{
    Processor pr;
    SECTION("closingTag1")
    {
        string givenTag = "</motherfucker>";

        Element elem;
        string expectedName = "motherfucker";
        elem.setNameOfElement(expectedName);

        int from = 0;

        string error;
        try
        {
            pr.processClosingTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
        }
    }

    SECTION("closingTag2")
    {
        string givenTag = "</  hello  >";

        Element elem;
        string expectedName = "hey";
        elem.setNameOfElement(expectedName);

        int from = 0;

        string error;
        try
        {
            pr.processClosingTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
        }
        string expectedError = "Invalid structure of XML\n";

        REQUIRE(error == expectedError);
    }

    SECTION("closingTag3")
    {
        string givenTag = "< / hello  >";

        Element elem;
        string expectedName = "hey";
        elem.setNameOfElement(expectedName);

        int from = 0;

        string error;
        try
        {
            pr.processClosingTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
        }
        string expectedError = "Invalid structure of XML\n";

        REQUIRE(error == expectedError);
    }

    SECTION("closingTag4")
    {
        string givenTag = "<  hello  >";

        Element elem;
        string expectedName = "hello";
        elem.setNameOfElement(expectedName);

        int from = 0;

        string error;
        try
        {
            pr.processClosingTag(givenTag, from, elem);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
        }
        string expectedError = "couldn't find \"</\" \n";

        REQUIRE(error == expectedError);
    }
}

//===========================================
//=============simplest obj==================
TEST_CASE("function:parseChildrenForTag")
{
    Processor pr;
    SECTION("XML1")
    {
        string givenText = "<person>  </person>";

        Element root;
        root.setNameOfElement("root");

        string expectedName = "person";
        string expectedAttribute = "";
        int expectedLevel = 1;

        int from = 0;

        string error;
        try
        {
            pr.parseChildrenForTag(givenText, from, &root);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string givenName = root.getElements()[0].getNameOfElement();
        string givenAttr = root.getElements()[0].getAttribute();
        int givenLevel = root.getElements()[0].getLevel();

        REQUIRE(expectedName == givenName);
        REQUIRE(expectedAttribute == givenAttr);
        REQUIRE(expectedLevel == givenLevel);
    }

    SECTION("XML2")
    {
        string givenText = "<person id=\'1\'>  </person>";

        Element root;
        root.setNameOfElement("root");

        string expectedName = "person";
        string expectedAttribute = "id=\'1\'";
        int expectedLevel = 1;

        int from = 0;

        string error;
        try
        {
            pr.parseChildrenForTag(givenText, from, &root);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string givenName = root.getElements()[0].getNameOfElement();
        string givenAttr = root.getElements()[0].getAttribute();
        int givenLevel = root.getElements()[0].getLevel();

        REQUIRE(expectedName == givenName);
        REQUIRE(expectedAttribute == givenAttr);
        REQUIRE(expectedLevel == givenLevel);
    }

    SECTION("XML3")
    {
        string givenText = "<person id=\'1\'> Kapaci </person>";

        Element root;
        root.setNameOfElement("root");

        string expectedName = "person";
        string expectedAttribute = "id=\'1\'";
        string expectedText = "Kapaci";
        int expectedLevel = 1;

        int from = 0;

        string error;
        try
        {
            pr.parseChildrenForTag(givenText, from, &root);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string givenName = root.getElements()[0].getNameOfElement();
        string givenTxt = root.getElements()[0].getTexts();
        string givenAttr = root.getElements()[0].getAttribute();
        int givenLevel = root.getElements()[0].getLevel();

        REQUIRE(expectedName == givenName);
        REQUIRE(expectedAttribute == givenAttr);
        REQUIRE(expectedText == givenTxt);
        REQUIRE(expectedLevel == givenLevel);
    }
}
//========nested elements=================
TEST_CASE("function:parseChildrenForTag_complexTests")
{
    SECTION("XML1")
    {
        Processor pr;
        string givenText = "<person id=\"0\">  \n      < name > John Smith< / name>   \n     <address>USA< / address>    \n    < / person>";

        Element root;
        root.setNameOfElement("root");

        // first child
        string expectedName = "person";
        string expectedAttribute = "id=\"0\"";
        string expectedText = "";
        int expectedLevel = 1;
        // first child - first child
        string expectedName1 = "name";
        string expectedAttribute1 = "";
        string expectedText1 = "John Smith";
        int expectedLevel1 = 2;
        // first child - second child
        string expectedName2 = "address";
        string expectedAttribute2 = "";
        string expectedText2 = "USA";
        int expectedLevel2 = 2;

        int from = 0;

        string error;
        try
        {
            pr.parseChildrenForTag(givenText, from, &root);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string givenName = root.getElements()[0].getNameOfElement();
        string givenTxt = root.getElements()[0].getTexts();
        string givenAttr = root.getElements()[0].getAttribute();
        int givenLevel = root.getElements()[0].getLevel();

        string givenName1 = root.getElements()[0].getElements()[0].getNameOfElement();
        string givenTxt1 = root.getElements()[0].getElements()[0].getTexts();
        string givenAttr1 = root.getElements()[0].getElements()[0].getAttribute();
        int givenLevel1 = root.getElements()[0].getElements()[0].getLevel();

        string givenName2 = root.getElements()[0].getElements()[1].getNameOfElement();
        string givenTxt2 = root.getElements()[0].getElements()[1].getTexts();
        string givenAttr2 = root.getElements()[0].getElements()[1].getAttribute();
        int givenLevel2 = root.getElements()[0].getElements()[1].getLevel();

        REQUIRE(expectedName == givenName);
        REQUIRE(expectedAttribute == givenAttr);
        REQUIRE(expectedText == givenTxt);
        REQUIRE(expectedLevel == givenLevel);

        REQUIRE(expectedName1 == givenName1);
        REQUIRE(expectedAttribute1 == givenAttr1);
        REQUIRE(expectedText1 == givenTxt1);
        REQUIRE(expectedLevel1 == givenLevel1);

        REQUIRE(expectedName2 == givenName2);
        REQUIRE(expectedAttribute2 == givenAttr2);
        REQUIRE(expectedText2 == givenTxt2);
        REQUIRE(expectedLevel2 == givenLevel2);
    }

    SECTION("XML2")
    {
        Processor pr;
        string givenText = "<person id=\"0\">\n < name > John Smith</ name>\n <address> USA</ address>\n</ person>\n<person id = \"1\">\n<name> Ivan Petrov</ name>\n <address> Bulgaria</ address>\n</ person> ";
        // string givenText = "<person id=\"0\">\n < name > John Smith</ name>\n <address> USA</ address>\n</ person>\n<person id=\"1\">\n<name> Ivan Petrov</ name>\n <address> Bulgaria</ address>\n</ person> ";
        Element root;
        root.setNameOfElement("root");

        // first child
        string expectedName0_1 = "person";
        string expectedAttribute0_1 = "id=\"0\"";
        string expectedText0_1 = "";
        int expectedLevel0_1 = 1;
        // first child - first child
        string expectedName1_1 = "name";
        string expectedAttribute1_1 = "";
        string expectedText1_1 = "John Smith";
        int expectedLevel1_1 = 2;
        // first child - second child
        string expectedName2_1 = "address";
        string expectedAttribute2_1 = "";
        string expectedText2_1 = "USA";
        int expectedLevel2_1 = 2;

        // second child
        string expectedName0_2 = "person";
        string expectedAttribute0_2 = "id=\"1\"";
        string expectedText0_2 = "";
        int expectedLevel0_2 = 1;
        // second child - first child
        string expectedName1_2 = "name";
        string expectedAttribute1_2 = "";
        string expectedText1_2 = "Ivan Petrov";
        int expectedLevel1_2 = 2;
        // second child - second child
        string expectedName2_2 = "address";
        string expectedAttribute2_2 = "";
        string expectedText2_2 = "Bulgaria";
        int expectedLevel2_2 = 2;

        int from = 0;

        string error;
        try
        {
            pr.parseChildrenForTag(givenText, from, &root);
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string givenName0_1 = root.getElements()[0].getNameOfElement();
        string givenTxt0_1 = root.getElements()[0].getTexts();
        string givenAttr0_1 = root.getElements()[0].getAttribute();
        int givenLevel0_1 = root.getElements()[0].getLevel();

        string givenName1_1 = root.getElements()[0].getElements()[0].getNameOfElement();
        string givenTxt1_1 = root.getElements()[0].getElements()[0].getTexts();
        string givenAttr1_1 = root.getElements()[0].getElements()[0].getAttribute();
        int givenLevel1_1 = root.getElements()[0].getElements()[0].getLevel();

        string givenName2_1 = root.getElements()[0].getElements()[1].getNameOfElement();
        string givenTxt2_1 = root.getElements()[0].getElements()[1].getTexts();
        string givenAttr2_1 = root.getElements()[0].getElements()[1].getAttribute();
        int givenLevel2_1 = root.getElements()[0].getElements()[1].getLevel();

        string givenName0_2 = root.getElements()[1].getNameOfElement();
        string givenTxt0_2 = root.getElements()[1].getTexts();
        string givenAttr0_2 = root.getElements()[1].getAttribute();
        int givenLevel0_2 = root.getElements()[1].getLevel();

        string givenName1_2 = root.getElements()[1].getElements()[0].getNameOfElement();
        string givenTxt1_2 = root.getElements()[1].getElements()[0].getTexts();
        string givenAttr1_2 = root.getElements()[1].getElements()[0].getAttribute();
        int givenLevel1_2 = root.getElements()[1].getElements()[0].getLevel();

        string givenName2_2 = root.getElements()[1].getElements()[1].getNameOfElement();
        string givenTxt2_2 = root.getElements()[1].getElements()[1].getTexts();
        string givenAttr2_2 = root.getElements()[1].getElements()[1].getAttribute();
        int givenLevel2_2 = root.getElements()[1].getElements()[1].getLevel();

        REQUIRE(givenName0_1 == expectedName0_1);
        REQUIRE(givenTxt0_1 == expectedText0_1);
        REQUIRE(givenAttr0_1 == expectedAttribute0_1);
        REQUIRE(givenLevel0_1 == expectedLevel0_1);

        REQUIRE(givenName1_1 == expectedName1_1);
        REQUIRE(givenTxt1_1 == expectedText1_1);
        REQUIRE(givenAttr1_1 == expectedAttribute1_1);
        REQUIRE(givenLevel1_1 == expectedLevel1_1);

        REQUIRE(givenName2_1 == expectedName2_1);
        REQUIRE(givenTxt2_1 == expectedText2_1);
        REQUIRE(givenAttr2_1 == expectedAttribute2_1);
        REQUIRE(givenLevel2_1 == expectedLevel2_1);

        REQUIRE(givenName0_2 == expectedName0_2);
        REQUIRE(givenTxt0_2 == expectedText0_2);
        REQUIRE(givenAttr0_2 == expectedAttribute0_2);
        REQUIRE(givenLevel0_2 == expectedLevel0_2);

        REQUIRE(givenName1_2 == expectedName1_2);
        REQUIRE(givenTxt1_2 == expectedText1_2);
        REQUIRE(givenAttr1_2 == expectedAttribute1_2);
        REQUIRE(givenLevel1_2 == expectedLevel1_2);

        REQUIRE(givenName2_2 == expectedName2_2);
        REQUIRE(givenTxt2_2 == expectedText2_2);
        REQUIRE(givenAttr2_2 == expectedAttribute2_2);
        REQUIRE(givenLevel2_2 == expectedLevel2_2);
    }
}
//====

TEST_CASE("final test")
{
    SECTION("The test")
    {
        Processor pr;
        string givenText = "<people>  <person id=\"0\">\n < name > John Smith</ name>\n <address> USA</ address>\n</ person>\n<person id = \"1\">\n<name> Ivan Petrov</ name>\n <address> Bulgaria</ address>\n</ person> </people>";

        // root
        string expectedNameRoot = "people";
        string expectedAttributeRoot = "";
        string expectedTextRoot = "";
        int expectedLevelRoot = 0;

        // first child
        string expectedName0_1 = "person";
        string expectedAttribute0_1 = "id=\"0\"";
        string expectedText0_1 = "";
        int expectedLevel0_1 = 1;
        // first child - first child
        string expectedName1_1 = "name";
        string expectedAttribute1_1 = "";
        string expectedText1_1 = "John Smith";
        int expectedLevel1_1 = 2;
        // first child - second child
        string expectedName2_1 = "address";
        string expectedAttribute2_1 = "";
        string expectedText2_1 = "USA";
        int expectedLevel2_1 = 2;

        // second child
        string expectedName0_2 = "person";
        string expectedAttribute0_2 = "id=\"1\"";
        string expectedText0_2 = "";
        int expectedLevel0_2 = 1;
        // second child - first child
        string expectedName1_2 = "name";
        string expectedAttribute1_2 = "";
        string expectedText1_2 = "Ivan Petrov";
        int expectedLevel1_2 = 2;
        // second child - second child
        string expectedName2_2 = "address";
        string expectedAttribute2_2 = "";
        string expectedText2_2 = "Bulgaria";
        int expectedLevel2_2 = 2;

        int from = 0;

        string error;
        try
        {
            pr.setText(givenText);
            pr.parseXML();
        }
        catch (const std::invalid_argument &e)
        {
            error = e.what();
            std::cout << error << '\n';
        }

        string rootName = pr.getRoot().getNameOfElement();
        string rootText = pr.getRoot().getTexts();
        string rootAttr = pr.getRoot().getAttribute();
        int rootLevel = pr.getRoot().getLevel();

        string givenName0_1 = pr.getRoot().getElements()[0].getNameOfElement();
        string givenTxt0_1 = pr.getRoot().getElements()[0].getTexts();
        string givenAttr0_1 = pr.getRoot().getElements()[0].getAttribute();
        int givenLevel0_1 = pr.getRoot().getElements()[0].getLevel();

        string givenName1_1 = pr.getRoot().getElements()[0].getElements()[0].getNameOfElement();
        string givenTxt1_1 = pr.getRoot().getElements()[0].getElements()[0].getTexts();
        string givenAttr1_1 = pr.getRoot().getElements()[0].getElements()[0].getAttribute();
        int givenLevel1_1 = pr.getRoot().getElements()[0].getElements()[0].getLevel();

        string givenName2_1 = pr.getRoot().getElements()[0].getElements()[1].getNameOfElement();
        string givenTxt2_1 = pr.getRoot().getElements()[0].getElements()[1].getTexts();
        string givenAttr2_1 = pr.getRoot().getElements()[0].getElements()[1].getAttribute();
        int givenLevel2_1 = pr.getRoot().getElements()[0].getElements()[1].getLevel();

        string givenName0_2 = pr.getRoot().getElements()[1].getNameOfElement();
        string givenTxt0_2 = pr.getRoot().getElements()[1].getTexts();
        string givenAttr0_2 = pr.getRoot().getElements()[1].getAttribute();
        int givenLevel0_2 = pr.getRoot().getElements()[1].getLevel();

        string givenName1_2 = pr.getRoot().getElements()[1].getElements()[0].getNameOfElement();
        string givenTxt1_2 = pr.getRoot().getElements()[1].getElements()[0].getTexts();
        string givenAttr1_2 = pr.getRoot().getElements()[1].getElements()[0].getAttribute();
        int givenLevel1_2 = pr.getRoot().getElements()[1].getElements()[0].getLevel();

        string givenName2_2 = pr.getRoot().getElements()[1].getElements()[1].getNameOfElement();
        string givenTxt2_2 = pr.getRoot().getElements()[1].getElements()[1].getTexts();
        string givenAttr2_2 = pr.getRoot().getElements()[1].getElements()[1].getAttribute();
        int givenLevel2_2 = pr.getRoot().getElements()[1].getElements()[1].getLevel();

        REQUIRE(rootName == expectedNameRoot);
        REQUIRE(rootText == expectedTextRoot);
        REQUIRE(rootAttr == expectedAttributeRoot);
        REQUIRE(rootLevel == expectedLevelRoot);

        REQUIRE(givenName0_1 == expectedName0_1);
        REQUIRE(givenTxt0_1 == expectedText0_1);
        REQUIRE(givenAttr0_1 == expectedAttribute0_1);
        REQUIRE(givenLevel0_1 == expectedLevel0_1);

        REQUIRE(givenName1_1 == expectedName1_1);
        REQUIRE(givenTxt1_1 == expectedText1_1);
        REQUIRE(givenAttr1_1 == expectedAttribute1_1);
        REQUIRE(givenLevel1_1 == expectedLevel1_1);

        REQUIRE(givenName2_1 == expectedName2_1);
        REQUIRE(givenTxt2_1 == expectedText2_1);
        REQUIRE(givenAttr2_1 == expectedAttribute2_1);
        REQUIRE(givenLevel2_1 == expectedLevel2_1);

        REQUIRE(givenName0_2 == expectedName0_2);
        REQUIRE(givenTxt0_2 == expectedText0_2);
        REQUIRE(givenAttr0_2 == expectedAttribute0_2);
        REQUIRE(givenLevel0_2 == expectedLevel0_2);

        REQUIRE(givenName1_2 == expectedName1_2);
        REQUIRE(givenTxt1_2 == expectedText1_2);
        REQUIRE(givenAttr1_2 == expectedAttribute1_2);
        REQUIRE(givenLevel1_2 == expectedLevel1_2);

        REQUIRE(givenName2_2 == expectedName2_2);
        REQUIRE(givenTxt2_2 == expectedText2_2);
        REQUIRE(givenAttr2_2 == expectedAttribute2_2);
        REQUIRE(givenLevel2_2 == expectedLevel2_2);
        //========commands testing=================
        //=====print
        std::cout << pr.getRoot();
        std::cout << '\n';

        //========select
        Commands &commandsInstance = Commands::getInstance();
        commandsInstance.setProcessor(pr);
        commandsInstance.extractElements(pr.getRoot());
        string temp_id = "id";

        // commandsInstance.select(expectedName0_1, temp_id);
        std::cout << '\n';
        commandsInstance.select1(expectedName0_1, temp_id);

        //========set
        commandsInstance.set(expectedName0_1, temp_id, "salam");
        cout << "\n";
        commandsInstance.select1(expectedName0_1, temp_id);

        int stop = 0;
    }
}
