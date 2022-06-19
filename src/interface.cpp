#include "interface.h"

int Interface::entrance()
{
    string line = "=============================\n";
    cout << "\nHello and welcome to my XML parser\n";
    cout << line;

    size_t choice = 0;

    cout << "Your current options are:\n"
         << "OPEN:   to open a file where you have a XML -  enter: "
         << e_OPEN << endl

         << "EXIT:   to exit the program enter: "
         << e_EXIT << endl;
    cout << line;

    cin >> choice;

    while (choice != e_OPEN && choice != e_EXIT)
    {
        cout << "Invalid input, try again\n";
        cin >> choice;
    }

    return choice;
}

// open, close, save, saveAs, help, exit
//===============
// print, select, set, children, child, text, deleteAttribute, newChild, xPath

int Interface::openChosen()
{
    size_t choice = 0;
    cout << line << endl;
    cout << "Your current options are:\n"

         //  << "CLOSE:  to close the program enter: "
         //  << listOfCommands[e_CLOSE] << endl

         << "SAVE:   to save current changes in file enter: "
         << listOfCommands[e_SAVE] << endl

         << "SAVE AS:  to save the XML in a new file with chosen name by you, enter: "
         << listOfCommands[e_SAVE_AS] << endl

         << "HELP: to Print the current options enter: "
         << listOfCommands[e_HELP] << endl

         << "EXIT:   to exit the program enter: "
         << listOfCommands[e_EXIT] << endl

         //=============================

         << "PRINT:  to print XML enter: "
         << listOfCommands[e_PRINT] << endl

         << "SELECT: to prints a value of attribute by given ID of element\n and key of attribute in XML enter: "
         << listOfCommands[e_SELECT] << endl

         << "SET:   to set value of attribute enter: "
         << listOfCommands[e_SET] << endl

         << "CHILDREN:   to get the vector of all nested elements of the given element enter: "
         << listOfCommands[e_CHILDREN] << endl

         << "CHILD:   to get the the n'th child of the element enter: "
         << listOfCommands[e_CHILD] << endl

         << "TEXT:   to get the text of the element of given element enter: "
         << listOfCommands[e_TEXT] << endl

         << "DELETE_ATTRIBUTE:   to delete an attribute of element by given key enter: "
         << listOfCommands[e_DELETE_ATTRIBUTE] << endl

         << "NEW_CHILD:   to adds a new child to element by given ID enter: "
         << listOfCommands[e_NEWCHILD] << endl

         << "xPATH:   to return a list of simple XPath 2.0 operations for given elements(menu) enter: "
         << listOfCommands[e_XPATH] << endl;
    cout << line;

    cin >> choice;

    while (choice != e_SAVE && choice != e_SAVE_AS &&
           choice != e_HELP && choice != e_EXIT && choice != e_PRINT &&
           choice != e_SET && choice != e_SELECT && choice != e_CHILDREN &&
           choice != e_CHILD && choice != e_TEXT && choice != e_DELETE_ATTRIBUTE &&
           e_NEWCHILD && e_XPATH)
    {
        cout << "Invalid input, try again\n";
        cin >> choice;
    }
    return choice;
}

int Interface::exitChosen(bool saved)
{
    int choice = 0;
    cout << "You have chosen EXIT\n";
    if (saved == false)
    {
        cout << "You have an open file with unsaved changes, please select: \n ";
    }
    cout << "CLOSE:   to close the file, file remains unchanged -  enter: "
         << e_CLOSE << endl

         << "SAVE:   to save changes in current file enter: "
         << e_SAVE << endl

         << "SAVE_AS:   to save in new file enter: "
         << e_SAVE_AS << endl;
    cout << line;

    cin >> choice;

    while (choice != e_CLOSE && choice != e_SAVE && choice != e_SAVE)
    {
        cout << "Invalid command, try again\n";
        cin >> choice;
    }

    return choice;
}

void Interface::start()
{
    Commands &instance = Commands::getInstance();

    bool isFileSaved = false;
    bool opened = false;
    bool wrongCommand = true;
    bool alreadyEntered = false;

    int currentchoice = 0;
    int choice = e_UNKNOWN;
    string path;

    do
    {
        if (!alreadyEntered)
        {
            choice = entrance();
            alreadyEntered = true;
        }

        if (choice == e_OPEN)
        {
            cout << "\nEnter path: \n";
            cin >> path;
            try
            {
                instance.open(path);
                cout << endl;
                currentchoice = openChosen();
                choice = currentchoice;
                opened = true;
                isFileSaved = true;
            }
            catch (const InvalidPath &e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const FileCouldntOpen &e)
            {
                std::cerr << e.what() << '\n';
            }
            catch (const std::invalid_argument &e)
            {
                std::cerr << e.what() << '\n';
                return;
            }
        }

        if (choice == e_PRINT)
        {
            instance.print();
            // printMenu();
        }

        if (choice == e_SELECT)
        {
            string id;
            string key;
            cout << "Please enter name of Element(ID) and its attibute name (key)\n";
            cin >> id >> key;
            instance.select1(id, key);

            // printMenu();
        }

        if (choice == e_SET)
        {
            string id;
            string key;
            string value;
            cout << "Please enter name of Element(ID) and its attibute name (key) and value\n";
            cin >> id >> key >> value;
            instance.set(id, key, value);
            isFileSaved = false;
        }

        if (choice == e_CHILDREN)
        {
        }

        if (choice == e_CHILD)
        {
        }

        if (choice == e_TEXT)
        {
        }

        if (choice == e_DELETE_ATTRIBUTE)
        {
            string id;
            string key;

            cout << "Please enter name of Element(ID) and its attibute name (key) \n";
            cin >> id >> key;
            instance.deleteAttribute(id, key);
        }

        if (choice == e_NEWCHILD)
        {
            string id;
            cout << "Please enter name of Element(ID)\n";
            cin >> id;
            instance.newchild(id);
            cout << "Element with id:" << id << "added succesfully\n";
        }

        if (choice == e_XPATH)
        {
        }


        if (choice == e_CLOSE)
        {
            instance.close();
        }

        if (choice == e_SAVE)
        {
            instance.save();
            isFileSaved == true;

            // printMenu();
        }

        if (choice == e_SAVE_AS)
        {
            cout << "Please enter path or name of the new file\n";
            do
            {
                cin >> path;
                if (!Commands::checkIfPathIsValid(path))
                {
                    cout << "Please enter VALID path or name of the new file\n";
                }
            } while (!Commands::checkIfPathIsValid(path));
            instance.saveAs(path);
            isFileSaved = true;

            // printMenu();
        }

        // EXIT

        if (choice == e_EXIT && opened)
        {

            cout << "\nDo you want to save changes or save in new file\n";
            cout << "To save in new file enter: " << e_SAVE_AS << endl;
            cout << "To save: " << e_SAVE << endl;
            cout << " If you don't want to enter a key \n";
            cin >> currentchoice;
            if (currentchoice == e_SAVE)
            {
                instance.save();
                isFileSaved = true;
            }
            else if (currentchoice == e_SAVE_AS)
            {
                instance.saveAs(path);
                isFileSaved = true;
            }
            else
            {
                instance.close();
                return;
            }
        }

        if (wrongCommand)
        {
            cout << "Invalid command please try again";
        }

    } while (choice != e_CLOSE);
}
