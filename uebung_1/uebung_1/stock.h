class Stock
{
private:
	typedef struct data {
		std::string date;
		float open;
		float high;
		float low;
		float close;
		float adj_close;
		unsigned volume;
	}data;
};
#pragma once
