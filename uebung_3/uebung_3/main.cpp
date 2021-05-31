#include "graph.h"


int main(int argc, char* argv[])
{
	std::cout << "Hello World!" << std::endl;
	std::cout << argc << std::endl;
	graph hello(".\\ADS_Programmieraufgabe3_WienerVerkehrsNetz.txt");
	hello.printGraph();

	return 0;
}