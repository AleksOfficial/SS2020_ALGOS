#include <iostream>
#include "tree.h"
int main()
{
	//1 treecheck; Dateina
	//maybe it would be fun to implement a function which creates a tree on the fly. :)

	tree x;
	std::string input;
	while (x.run)
	{
		x.print_menu();
		std::cin >> input;
		x.add_search();
		x.handle_input(input);
	}
	 

}