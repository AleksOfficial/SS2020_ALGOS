typedef struct data {
	std::string date;
	float open;
	float high;
	float low;
	float close;
	float adj_close;
	unsigned volume;
	struct data* next;
}data
;
class Stock
{
public:
	std::string tag;
	data* first_values;
	data* last_values;

};
#pragma once
