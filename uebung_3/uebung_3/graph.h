#pragma once
#include <map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

struct connection;


typedef struct station {
	std::string s_name;
	std::vector<connection> m_connections;
	station* p_previousElement;
	int n_total_cost;
	//station();
	//station(std::string name) : s_name(name), m_connections(NULL), p_previousElement(NULL), n_total_cost(INFINITY) {}
	
}station;

typedef struct connection {
	int n_cost;
	std::string s_line;
	station* m_destination;
	//connection();
	//connection(int cost, std::string line, station* destination) : n_cost(cost), s_line(line), m_destination(destination) {}
}connection;

typedef struct metroline
{
	std::string s_line;
	station* p_startpoint;
	int n_total_stops;
}metroline;

class graph {

private:
	std::vector<metroline> m_lines; //name of line, startstation


public:
	std::map<std::string, station> m_allElements;
	bool constructGraph(std::string filename);
	bool constructGraph();
	graph(std::string filename);
	graph();
	void printMenu();
	void printMetroline();
	void printGraph();


};