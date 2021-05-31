#include "graph.h"
bool graph::constructGraph(std::string filename)
{
	FILE* inputData;
	std::ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		std::cout << "Error: File not found. " << std::endl;
		return false;
	}
	std::string fileline;
	while (std::getline(fin, fileline))
	{
		std::stringstream linestream(fileline);
		std::string val;
		std::string line;
		linestream >> line;
		line.resize(line.size() - 1);
		int count = 0;
		station previous;
		connection con;
		std::getline(linestream, val, '"');
		metroline newLine;
		newLine.s_line = line;
		newLine.p_startpoint;

		while (std::getline(linestream, val,'"'))
		{
			//name1 cost name2 cost name3 cost
			
			if (count != 0)
			{
				//Get cost
				
				val = val.substr(1, val.size() - 2);

				//create a connection
				con.m_destination = &this->m_allElements[previous.s_name];
				con.n_cost = atoi(val.c_str());
				con.s_line = line;

				std::getline(linestream, val, '"');
				//connect current with previous node
				this->m_allElements[val].m_connections.push_back(con);

				//connect previous node with current one
				con.m_destination = &this->m_allElements[val];
				this->m_allElements[previous.s_name].m_connections.push_back(con);

				
			}

			struct station current;
			

			current.s_name = val;
			current.p_previousElement = NULL;
			current.n_total_cost = INFINITY;
			current.m_connections = this->m_allElements[val].m_connections;

			//create a station
			if(this->m_allElements.find(val)!=this->m_allElements.end())
				this->m_allElements[val] = current;



			if (count == 0)
				newLine.p_startpoint = &this->m_allElements[val];

			
			previous = current;
			count++;
		}
		newLine.n_total_stops = count;
		this->m_lines.push_back(newLine);
	}

	return true;
}

graph::graph()
{
	std::string name;
	std::cout << "Enter the filename of your graph: " << std::endl;
	std::cin >> name;
	constructGraph(name);
}

graph::graph(std::string filename)
{
	constructGraph(filename);
}




void graph::printGraph()
{

	for (auto it = this->m_allElements.begin(); it != m_allElements.end(); it++)
	{
		station current = it->second;
		std::cout << current.s_name << std::endl;
		if (current.s_name == "Schottentor")
			std::cout << "Hello";
		for (int j = 0; j < current.m_connections.size(); j++)
		{
			std::cout << "connected to: " << std::endl;

			std::cout << "\t" << current.m_connections[j].s_line << std::endl;
			std::cout << "\t" << current.m_connections[j].n_cost<< std::endl;
			std::cout << "\t" << current.m_connections[j].m_destination->s_name << std::endl;
		}

	}
}

void graph::printMenu()
{
	
}
