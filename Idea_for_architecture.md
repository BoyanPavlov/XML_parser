class commands

void print()
  XML_obj = readFromFile(path);
  XML_obj.format();
  XML_obj.print();

  
class element

id - string
vector <string> attributes;
vector<string> nestedElements;
string text;

checkID()
 is there an ID 
 -yes
	isIDUnique()
		-yes okay
		-no
			search for a  "_" 
				it has _ - okay number++
				it hasn't and "_1"
 -no 
	generateID()


search for "/" - print all of this ...
search for "[num]" - print the [num] element in this file
search for "@" - prints all attributes of elemens in this file
search for "=" ... some other condition here - used for filter