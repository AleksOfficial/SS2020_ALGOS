#include "stock.h"

class Hashtable
{
//class-variables
private:
	int n_max_length; //of stocks
	int max_collisions;
	Stock * stocks;
	Stock current_stock; //This can be used to access the last 
//Constructor
public:
	Hashtable()
		: n_max_length(find_next_prime(1000)),max_collisions(0)
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
	// Hash Function: H(s) = s[0]*(7^n-1)+ s[1] * (7^n-2) + ... + s[n-1]; n -> Length of string -1 ; 
	int hash_function(std::string s_stock_tag)
	{ 
		int n_hash_value = 0;
		for (int j = 0; j< s_stock_tag.length();j++)
		{
			int n_sum = (int)s_stock_tag[j];
			for (int i = 0; i < (s_stock_tag.length()-j); i++)
			{
				n_sum *= 7;
				n_sum %= n_max_length;
			}
			n_hash_value += n_sum;
			n_hash_value %= n_max_length;
		}
		return n_hash_value;
	}
	//Hqp(s) = H(s) +sum(i^2, amount_of_collisions)
	bool quadratic_probing_search(int n_hash_value,std::string stock_tag)
	{	
		int prev_hash_key = n_hash_value;
		for (int i = 1; i <= n_max_length; i++)
		{
			prev_hash_key += (i*i);
			prev_hash_key %= n_max_length;
			current_stock = stocks[prev_hash_key];
			if (current_stock.tag == stock_tag)
				return true;
		}
		return false;
	}
	//find_stock: returns true if the stock is found in the array, else false. the current_stock is set to the last search value
	bool find_stock(std::string stock_tag)
	{
		int hash_key = hash_function(stock_tag);
		current_stock = stocks[hash_key];
		if (current_stock.tag == stock_tag)
			return true;
		else
		{
			return quadratic_probing_search(hash_key, stock_tag);
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
