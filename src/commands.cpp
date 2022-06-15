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
        //TODO FIX!!!!!!!!!!!!!!!!
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
        return false;
    }
    return true;
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
    }
    else
    {
        throw InvalidPath();
    }
}

void Commands::close()
{
    cout << "Exitting the program...\n";
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
    // print menu;
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