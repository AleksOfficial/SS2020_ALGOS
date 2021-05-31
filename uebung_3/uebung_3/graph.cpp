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

void graph::shortestPath(std::string src)
{
	std::map<std::string, station> heap;
	std::map<std::string, int> dist;

	for (auto it = this->m_allElements.begin(); it != this->m_allElements.end(); it++) {
		dist.insert(std::pair<std::string, int>(it->first, std::numeric_limits<int>::max()));
	}


	heap.insert(heap.begin(), std::pair<std::string, station>(src, this->m_allElements[src]));
	dist[src] = 0;

	while (!heap.empty()) {
		std::pair<std::string, station> tmp = std::make_pair(heap.begin()->first, heap.begin()->second);
		heap.erase(heap.begin());
		station u = tmp.second;
		for (auto i = u.m_connections.begin(); i != u.m_connections.end(); i++) {
			station v = *i->m_destination;
			int cost = i->n_cost;

			if (dist[v.s_name] > (dist[u.s_name] + cost)) {
				if (dist[v.s_name] != std::numeric_limits<int>::max()) {
					heap.erase(v.s_name);
				}
					dist[v.s_name] = dist[u.s_name] + cost;
					this->m_allElements[v.s_name].n_total_cost = dist[v.s_name];
					this->m_allElements[v.s_name].p_previousElement = &this->m_allElements[u.s_name];
					heap.insert(std::make_pair(v.s_name, v));
				
			}
		}
	}
	
}

void graph::printMenu()
{
	std::cout << std::endl;
	std::cout << "### -- Shortest Path -- ###" << std::endl << std::endl;
	std::cout << "These inputs are possible: " << std::endl;
	std::cout << "   - input file path\t-> (file)" << std::endl;
	std::cout << "   - set starting point\t-> (start)" << std::endl;
	std::cout << "   - set destination\t-> (dest)" << std::endl;
	std::cout << "   - find shortest Path\t-> (find)" << std::endl;
	std::cout << "   - terminate program\t-> (exit)" << std::endl;
}

void graph::handleInput() {
	std::string command;
	std::string file = "";
	std::string src = "";
	std::string dest = "";
	
	while (true)
	{

		std::cin >> command;
		if (command == "file") {
			do {
				std::cout << std::endl << "Path to file:" << std::endl;
				std::cin >> file;
			} while (!this->constructGraph(file));

		}
		else if (command == "start") {
			do {
				std::cout << std::endl << "Starting point:" << std::endl << std::endl;
				std::cin >> src;
			} while (this->m_allElements.find(src) == this->m_allElements.end());
			std::cout << std::endl << "Starting point set!" << std::endl;
		}
		else if (command == "dest") {
			do {
				std::cout << std::endl << "Destination:" << std::endl << std::endl;
				std::getline(std::cin, dest);
			} while (this->m_allElements.find(dest) == this->m_allElements.end());
			std::cout << std::endl << "Destination set!" << std::endl;
		}
		else if (command == "find") {
			if (src != "" && dest != "") {
				std::cout << std::endl;
				this->shortestPath(src);
				this->printPath(dest, src);

			}
			else {
				std::cout << std::endl << "Please set startingpoint and destination first!" << std::endl;
			}
		}
		else if (command == "exit") {
			break;
		}
		else
		{
			std::cout << std::endl << "Error! Wrong Command, try again." << std::endl;
		}
	}

}

void graph::printPath(std::string dest, std::string src)
{
	std::vector<station> path;
	station current = this->m_allElements[dest];
	while (current.s_name != src) {
		path.push_back(current);
		current = *current.p_previousElement;
	}
	for (auto it = path.rbegin(); it != path.rend(); it++) {
		
		auto next = it;
		next++;
		auto nextForConn = next;
		connection conn;
		connection nextConn;
		if (next != path.rend() && next->s_name != dest) {
			
			nextForConn++;
		}
		
		
		if (next != path.rend()) {
			for (int i = 0; i < next->m_connections.size(); i++) {
				if (next->s_name != dest) {
					if (next->m_connections[i].m_destination->s_name == nextForConn->s_name) {
						nextConn = next->m_connections[i];
					}

				}
			}

			for (int i = 0; i < it->m_connections.size(); i++) {
				if (it->m_connections[i].m_destination->s_name == next->s_name) {
					conn = it->m_connections[i];
				}
			}

			std::cout << "From Station: " << it->s_name << " to " << next->s_name << " in " << conn.n_cost << " Minute(s), with line: " << conn.s_line << std::endl << std::endl;
			if (conn.s_line != nextConn.s_line) {
				std::cout << "In Station " << next->s_name << " change from line " << conn.s_line << " to line " << nextConn.s_line << std::endl << std::endl;
			}
		}

	}
	std::cout << "Estimated Time: " << path[0].n_total_cost << std::endl;
}
