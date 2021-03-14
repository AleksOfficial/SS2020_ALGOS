#include "stock.h"

class Hashtable
{
//class-variables
private:
	int n_max_length; //of stocks
	int max_collisions = 0;
	Stock * stocks;
//Constructor
public:
	Hashtable()
		: n_max_length(find_next_prime(1000))
	{
		stocks = new Stock[n_max_length];
	}
//private-Methods
	int find_next_prime(int start_val)
	{
		bool divisible;
		for (int i = start_val;; i++)
		{
			divisible = false;
			for (int j = 2; j < i; j++)
			{
				if ((i % j) == 0)
				{
					divisible = true;
					break;
				}
			}
			if (!divisible)
				return i;
		}
	}
//functions of the hashtable
public:
	bool add()
	{
		std::cout << "Hello World! I am add" << std::endl;
		return true;
	}
	bool del()
	{
		std::cout << "Hello World! I am del" << std::endl;
		return true;
	}
	bool import_data()
	{
		std::cout << "Hello World! I am import" << std::endl;
		return true;
	}
	bool search()
	{
		std::cout << "Hello World! I am search" << std::endl;
		return true;
	}
	bool plot()
	{
		std::cout << "Hello World! I am plot" << std::endl;
		return true;
	}

	bool save()
	{
		std::cout << "Hello World! I am save" << std::endl;
		return true;
	}
	bool load()
	{
		std::cout << "Hello World! I am load" << std::endl;
		return true;
	}
	bool quit()
	{
		std::cout << "Hello World! I am quit" << std::endl;
		return true;
	}
};
