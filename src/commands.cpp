#include "commands.h"
#include "customExceptions.h"

// utilities

void Commands::toUpper(string &given_command)
{
    for (int i = 0; i < given_command.size(); i++)
    {
        if (!('a' <= given_command[i] && given_command[i] <= 'z' || 'A' <= given_command[i] && given_command[i] <= 'Z'))
        {
            throw InvalidComand();
        }
        if ('a' <= given_command[i] && given_command[i] <= 'z')
        {
            given_command[i] = given_command[i] - 'a' + 'A';
        }
    }
}

string Commands::convertStreamToString(ifstream &in)
{
    string temp;
    string str;
    while (!in.eof())
    {
        // TODO FIX!!!!!!!!!!!!!!!!
        std::getline(in, temp);
        str += temp;
    }
    return str;
}

int Commands::findCommandIndex(string &given_command)
{
    toUpper(given_command);
    for (int i = 0; i < listOfCommands.size(); i++)
    {
        if (given_command == listOfCommands[i])
        {
            return i;
        }
    }
    return -1;
}

bool Commands::checkIfPathIsValid(string path)
{
    std::ifstream in(path, std::ios::in);
    if (!in)
    {
        in.close();
        return false;
    }
    in.close();
    return true;
}

void Commands::setProcessor(const Processor &givenPr)
{
    this->instance = givenPr;
}
// basic commands

void Commands::open(const string &path)
{
    if (checkIfPathIsValid(path))
    {
        std::ifstream in(path, std::ios::in);
        if (!in.is_open())
        {
            throw FileCouldntOpen();
        }
        instance.setText(convertStreamToString(in));
        cout << "File has opened successfully!\n";
        cout << "...\n";
        cout << "Loading elements\n";
        this->path = path;
        try
        {
            instance.parseXML();
        }
        catch (const std::exception &e)
        {
            std::cerr << e.what() << '\n';
            throw e.what();
        }
        cout << "...\n";
        cout << "Loaded succesfully\n";
        in.close();
    }
    else
    {
        throw InvalidPath();
    }
}

void Commands::close()
{
    cout << "Exitting the program, have a nice day!\n";
}

void Commands::save()
{
    std::ofstream out(path, std::ios::out | std::ios::trunc);
    out << instance.getRoot();
    if (!out.is_open())
    {
        cout << "Problem with saving the XML\n";
        return;
    }
    cout << "XML saved successfully\n";
    out.close();
}

void Commands::saveAs(const string &path)
{
    bool isPathValid = checkIfPathIsValid(path);
    if (!isPathValid)
    {
        // mustn't enter here
        throw InvalidPath();
    }
    else
    {
        std::ofstream out(path, std::ios::out | std::ios::trunc);
        out << instance.getRoot();
        if (!out.is_open())
        {
            cout << "Problem with saving the XML\n";
            return;
        }
        cout << "XML saved successfully in " << path << endl;
        out.close();
    }
}

/// function help - prints the basic menu
void Commands::help()
{
    cout << "The following commands are supported:\n";
    for (int i = 0; i < listOfCommands.size() - 1; i++)
    {
        cout << i << ". " << listOfCommands[i] << endl;
    }
}

/// exits the program
void Commands::exit()
{
    // check if file is saved
    // options :
    // save
    // save as
    // close
}

// XML commands

void Commands::print()
{
    cout << instance.getRoot();
}

// void Commands::select(const string &id, const string &key)
// {
//     cout << "Elements with this ID( " << id << " ) and key( " << key << " )found:\n";
//     selectRec(id, key, instance.getRoot());
//     return;
// }
//
// void Commands::selectRec(const string &id, const string &key, Element &element)
// {
//     if (element.getAttribute().size() > 0)
//     {
//         string currentKey = instance.getKeyOfAttribute(element.getAttribute(), element);
//         string currentValueOfKey = instance.getValueOfKey(element.getAttribute(), element);
//
//         if (id == element.getNameOfElement() && key == currentKey)
//         {
//             cout << "Value of Key:  " << currentKey << currentValueOfKey << '\n';
//         }
//     }
//
//     for (int i = 0; i < element.getElements().size(); i++)
//     {
//         selectRec(id, key, element.getElements()[i]);
//     }
//     return;
// }

void Commands::extractElements(Element &elem)
{
    extractedElements.push_back(&elem);
    for (int i = 0; i < elem.getElements().size(); i++)
    {
        extractElements(elem.getElements()[i]);
    }
    return;
}

void Commands::select1(const string &id, const string &key)
{
    cout << "Elements with this ID( " << id << " ) and key( " << key << " )found:\n";
    for (int i = 0; i < extractedElements.size(); i++)
    {
        if (extractedElements[i]->getAttribute().size() > 0)
        {
            string currentKey = instance.getKeyOfAttribute(extractedElements[i]->getAttribute(), *extractedElements[i]);
            string currentValueOfKey = instance.getValueOfKey(extractedElements[i]->getAttribute(), *extractedElements[i]);
            if (extractedElements[i]->getNameOfElement() == id && key == currentKey)
            {
                cout << "Value of Key:  " << currentKey << currentValueOfKey << '\n';
            }
        }
    }
}

void Commands::set(const string &id, const string &key, const string &value)
{
    cout << "First elements with this ID( " << id << " ) and key( " << key
         << " )found got new value of: " << value;
    for (int i = 0; i < extractedElements.size(); i++)
    {
        if (extractedElements[i]->getAttribute().size() > 0)
        {
            string currentKey = instance.getKeyOfAttribute(extractedElements[i]->getAttribute(), *extractedElements[i]);
            string currentValueOfKey = instance.getValueOfKey(extractedElements[i]->getAttribute(), *extractedElements[i]);
            if (extractedElements[i]->getNameOfElement() == id && key == currentKey)
            {
                string newAttr = currentKey + "=" + "\"" + value + "\"";
                extractedElements[i]->setAttribute(newAttr);

                // currentValueOfKey = instance.getValueOfKey(extractedElements[i]->getAttribute(), *extractedElements[i]);
                // cout << "Changed to - Value of Key:  " << currentKey << currentValueOfKey << '\n';
                // cout << extractedElements[i]->getAttribute() << endl;

                return;
            }
        }
    }
}

void Commands::deleteAttribute(const string &id, const string &givenKey)
{
    cout << "First elements with this ID( " << id << " ) and key( " << givenKey
         << " ) will lose it's attribute";
    for (int i = 0; i < extractedElements.size(); i++)
    {
        if (extractedElements[i]->getAttribute().size() > 0)
        {
            string currentKey = instance.getKeyOfAttribute(extractedElements[i]->getAttribute(), *extractedElements[i]);
            string currentValueOfKey = instance.getValueOfKey(extractedElements[i]->getAttribute(), *extractedElements[i]);
            if (extractedElements[i]->getNameOfElement() == id && givenKey == currentKey)
            {
                string newAttr;
                cout << "Attribute found: " << extractedElements[i]->getAttribute()
                     << " removed succesfully" << endl;
                extractedElements[i]->setAttribute(newAttr);
                return;
            }
        }
    }
}

void Commands::newchild(const string &id)
{
    Element newOne;
    newOne.setNameOfElement(id);
    newOne.setLevel(1);
    instance.getRoot().addElement(newOne);
    extractedElements.push_back(&newOne);
}