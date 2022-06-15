#include <iostream>
#ifndef _EXCEPTIONS_
#define _EXCEPTIONS_

class InvalidPath : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Invalid Path\n";
    }
};

class FileCouldntOpen : public std::exception
{
public:
    const char *what() const throw()
    {
        return "File couldn't open";
    }
};

class InvalidComand : public std::exception
{
public:
    const char *what() const throw()
    {
        return "Given invalid command";
    }
};

#endif // _EXCEPTIONS_