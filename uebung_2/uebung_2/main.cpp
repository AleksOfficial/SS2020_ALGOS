#include <iostream>
#include "tree.h"

int main(int argc, char* argv[])
{
	
	//maybe it would be fun to implement a function which creates a tree on the fly. :)

	tree x;
	bool run_once = true;
	std::string input1;
	std::string input2;
	if (argc == 2)
	{
		if (run_once)
		{
			input1 = argv[1];
			x.handle_input(input1);
			run_once = false;
		}
		
	}
	if (argc == 3)
	{
		if (run_once)
		{
			input1 = argv[1];
			input2 = argv[2];
			x.handle_input(input1,input2);
			run_once = false;
		}
	}
	if (argc == 1)
	{
		x.run = true;
	}
	while (x.run)
	{
		x.print_menu();
		std::cin >> input1;
		x.handle_input(input1);
	}

	 

}