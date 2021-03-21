#include <iostream>
#include <list>
#pragma once

class Stock
{
public:
	typedef struct data {
		std::string s_date;
		float f_open;
		float f_high;
		float f_low;
		float f_close;
		float f_adj_close;
		unsigned n_volume;
	}data;
	//Members
	std::string s_stock_number;
	std::string s_tag;
	std::string s_name;
	int n_collision_value;
	std::list<data> l_datavalues;
	bool b_set;
	bool b_data;
	int n_dataamount;
	//Constructor
	Stock()
		:s_stock_number(), s_tag(), s_name(), n_collision_value(0), l_datavalues(), b_set(false), b_data(false),n_dataamount(0)
	{}

	Stock(std::string name, std::string tag, std::string stock_number, int collisions, int load_data_amount) :
		s_stock_number(stock_number), s_tag(tag), s_name(name), n_collision_value(collisions), l_datavalues(),b_set(true), b_data(false),n_dataamount(0)
	{
		//insert loop here to load the data or call the function below? idk 
	}

	bool import_data(FILE * csv_file) //no error handling here. maybe during reading there could be an error handler or smth.
	{
		n_dataamount = 0;
		b_data = true;
		while (!feof(csv_file))
		{
			data datapoint;
			fscanf_s(csv_file, "%s,%lf,%lf,%lf,%lf,%lf,%u", &datapoint.s_date, &datapoint.f_open, &datapoint.f_high, &datapoint.f_low, &datapoint.f_close, &datapoint.f_adj_close, &datapoint.n_volume);
			if (n_dataamount > 30)
			{
				l_datavalues.erase(l_datavalues.begin(),l_datavalues.begin());
				n_dataamount--;
			}
			l_datavalues.push_back(datapoint);
			n_dataamount++;
		}
		return true;
	}


};

