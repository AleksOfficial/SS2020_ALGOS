#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#pragma once
typedef struct node {
	
	node(int& val) :m_value(val), m_left(nullptr), m_right(nullptr){}
	int m_value;
	struct node* m_left;
	struct node* m_right;
}node;

class tree {
private:
	//Variables
	node *root;
	float avg;
	int max;
	int min;
	int count;
	int total;
	bool avl_tree;

	void delete_tree(node* node);
	void delete_tree();

	bool get_tree(std::string& filename);
	bool insert_value(int& val);
	void print_tree(const std::string& prefix, const node* node, bool is_left);
	void print_tree();
	bool create_own_tree();
	void check_avl_condition();
	bool check_avl_condition(node* node);
	void search_value();
	void search_subtree();
	int height(node* node);
public:
	bool run;
	tree() : root(nullptr), avg(-1.0f), max(-1),min(-1),count(0), run(true), avl_tree(false)
	{}
	~tree();
	void print_menu();
	void handle_input(std::string& input);



};