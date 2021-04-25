#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
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
	node* sub_tree;
	int sub_tree_size;
	float avg;
	int max;
	int min;
	int count;
	int total;
	std::vector<int> search_nodes;
	bool avl_tree;
	int subtree_found;

	void delete_tree(node* node);
	void delete_tree();

	bool get_tree(std::string& filename, bool use_root);
	bool insert_value(int& val, bool use_root);
	void print_tree(const std::string& prefix, const node* node, bool is_left);
	void print_tree();
	bool create_own_tree();
	void check_avl_condition();
	bool check_avl_condition(node* node);
	void search();
	void search_value(node* head);
	void search_subtree(node* head, node* search_head);
	int height(node* node);
	void get_max();
	int get_max(node* node);
	void get_min();
	int get_min(node* node);

public:
	bool run;
	tree() : root(nullptr), sub_tree(nullptr), avg(-1.0f), max(-1),min(-1),count(0), run(true), avl_tree(false), subtree_found(0), sub_tree_size(0)
	{}
	~tree();
	void print_menu();
	void handle_input(std::string& input);

	void add_search();



};