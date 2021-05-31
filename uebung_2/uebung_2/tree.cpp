

#include "tree.h"
bool tree::get_tree(std::string& filename, bool use_root)
{
	FILE* input_data;
	std::ifstream fin;
	fin.open(filename);
	if (!fin)
	{
		std::cout << "Error (404): File not Found. ";
		return false;
	}
	std::string val;
	while (fin >> val)
	{
		try {
				int value = std::stoi(val);
			if (!this->insert_value(value, use_root))
				std::cout << "Error(409): " << val << " already exists" << std::endl;
			else {
				//std::cout << "Insertion of " << val << " was successful!" << std::endl;
				if (!use_root) {
					sub_tree_size++;
				}
			}
		}
		catch (...)
		{ 
			std::cout << "Error(500):" << val << " could not be converted into a number." << std::endl;

		}
			
		
	}
	fin >> val;
	return true;
}

bool tree::insert_value(int& val, bool use_root)
{
	//construct a new node
	node* head;
	if (use_root) {
		head = root;
	}
	else {
		head = sub_tree;
	}
	node* new_element = new node(val);
	if (head == nullptr) {
		head = new_element;
		if (use_root) {
			root = head;
		}
		else {
			sub_tree = head;
		}
		
	}
	else
	{
		node* traveller = head;
		while (42)
		{
			if (traveller->m_value == new_element->m_value)
			{
				delete(new_element);
				return false;
			}
			else if (traveller->m_value < new_element->m_value)
			{
				if (traveller->m_right == nullptr)
				{
					traveller->m_right = new_element;
					/*
					if (use_root) {
						root = head;
					}
					else {
						sub_tree = head;
					}*/
					return true;
				}
				else
					traveller = traveller->m_right;
			}
			else 
			{
				if (traveller->m_left == nullptr)
				{
					traveller->m_left = new_element;
					/*
					if (use_root) {
						root = head;
					}
					else {
						sub_tree = head;
					}*/
					return true;
				}
				else
					traveller = traveller->m_left;
			}
		}
	}
}

tree::~tree()
{
	delete_tree();
	delete_tree(sub_tree);
}

void tree::delete_tree(node * node)
{
	if (node == NULL)
		return;
	delete_tree(node->m_left);
	delete_tree(node->m_right);
	delete node;
	node = nullptr;

}
void tree::delete_tree()
{
	delete_tree(root);
	root = nullptr;
	min = -1;
	max = -1;
	avg = -1.0f;
	total = 0;
	count = 0;
}

void tree::print_tree(const std::string& prefix, const node* node, bool is_left)
{
	if (node != nullptr)
	{
		std::cout << prefix;

		std::cout << (is_left ? "|---" : "\\---");

		// print the value of the node
		std::cout << node->m_value << std::endl;

		// enter the next tree level - left and m_right branch
		print_tree(prefix + (is_left ? "|   " : "    "), node->m_left, true);
		print_tree(prefix + (is_left ? "|   " : "    "), node->m_right, false);
	}
}

void tree::print_tree(node * node)
{
	print_tree("", node, false);
}

void tree::print_tree()
{
	print_tree("", root, false);
}

void tree::print_menu()
{
	std::cout << "### -- Tree Constructer Program -- ###" << std::endl << std::endl;
	std::cout << "These inputs are possible: " << std::endl;
	std::cout << "   - input file path       -> (path to file)" << std::endl;
	std::cout << "   - create own tree(cmd)  -> (create)" << std::endl;
	std::cout << "   - print tree            -> (print)" << std::endl;
	std::cout << "   - AVL condition         -> (AVL)" << std::endl;
	std::cout << "   - search value/subtree  -> (search)" << std::endl;
	std::cout << "   - terminate program     -> (exit)" << std::endl;

}

void tree::handle_input(std::string& input)
{

	if (input == "create")
	{
		delete_tree();
		if (create_own_tree(true))
			print_tree();
		run = true;
		
	}
	else if (input == "print")
	{
		print_tree();
		run = true;
	}
	else if (input == "AVL")
	{
		check_avl_condition();
		run = true;
	}
	else if (input == "search")
	{
		delete_tree(sub_tree);
		create_own_tree(false);
		search();
		run = true;
	}
	else if (input == "help")
		print_menu();
	else if (input == "exit")
		run = false;

	else
	{
		delete_tree();
		if (get_tree(input, true))
		{
			print_tree();
			check_avl_condition();

		}
		

	}
}

void tree::handle_input(std::string& input1, std::string& input2)
{
	if (get_tree(input1, true))
		if (get_tree(input2, false))
			search();
	delete_tree();

}

bool tree::create_own_tree(bool use_root)
{
	std::string numbers;
	std::cout << "Enter your number in the following order: #,#,#,#,..." << std::endl;
	std::cin >> numbers;
	std::istringstream num(numbers);
	std::vector<int> x;
	while (std::getline(num, numbers, ','))
	{
		try {
				x.push_back(std::stoi(numbers));
			}
		catch (...) { std::cout << "Error(500): Could not convert " << numbers << " into a number!" << std::endl;  }
	}
	for (int i = 0; i < x.size(); i++)
	{
		if (use_root)
		{
			if (insert_value(x[i], true))
				std::cout << x[i] << " successfully inserted. " << std::endl;
			else
				std::cout << "Error(409): " << x[i] << " already exists" << std::endl;
		}
		else
		{
			if (insert_value(x[i], false))
			{
				std::cout << x[i] << " successfully inserted. " << std::endl;
				sub_tree_size++;

			}
			else
				std::cout << "Error(409): " << x[i] << " already exists" << std::endl;
		}
	}
	return true;
}

int tree::get_max(node* node)
{
	if (node == nullptr)
		return 0;
	if (node->m_right == nullptr)
		return node->m_value;
	get_max(node->m_right);

}
int tree::get_min(node* node)
{
	if (node == nullptr)
		return 0;
	if (node->m_left == nullptr)
		return node->m_value;
	get_min(node->m_left);
}

void tree::get_max()
{
	max = get_max(root);
	std::cout << "Maximum: " << max;
}
void tree::get_min()
{
	min = get_min(root);
	std::cout << "Minimum: " << min;
}

int tree::height(node* node)
{
	if (node == nullptr)
		return 0;
	else
		return 1 + std::max(height(node->m_left),height(node->m_right));
}

bool tree::check_avl_condition(node* node)
{
	if (node == nullptr)
		return true;
	else
	{	
		//increase count
		count++;
		total += node->m_value;
		//setting min
		if (min < 0)
			min = node->m_value;
		if (min > node->m_value)
			min = node->m_value;
		//setting max
		if (max < 0)
			max = node->m_value;
		if (max < node->m_value)
			max = node->m_value;
		check_avl_condition(node->m_right);
		check_avl_condition(node->m_left);
		int right_half = height(node->m_right);
		int left_half = height(node->m_left);
		int diff = abs(right_half - left_half);
		std::cout << "bal(" << node->m_value << ") = " << diff << (diff>1 ? "(AVL violation!)":"") << std::endl;
		diff > 1 ? avl_tree = false:true;

	}
	return avl_tree;
}

void tree::check_avl_condition()
{
	//Reverse Inorder
	//search right subtree
	//check first node
	//search left subtree
	avl_tree = true;
	if (check_avl_condition(root))
		std::cout << "AVL: yes" << std::endl;
	else
		std::cout << "AVL: no" << std::endl;
	avg = (float)total / (float)count;
	std::cout << "min: " << min << " max: " << max << " avg: " << avg <<std::endl;
	
	return;
}

void tree::search() {
	std::cout << "Tree: " <<std::endl;
	print_tree();
	std::cout << "Subtree/Searchvalue:" << std::endl;
	print_tree(sub_tree);
	if (sub_tree_size == 1) {
		search_value(root);
	}
	else if(sub_tree_size != 0)
	{
		search_subtree(root, sub_tree);
	}
	else {
		std::cout << "No element in subtree!" << std::endl;
	}
	delete_tree(sub_tree);
	sub_tree = nullptr;
	sub_tree_size = 0;
	subtree_found = 0;
	search_nodes.clear();
}

void tree::search_value(node *head)
{
	if (head->m_value == sub_tree->m_value) {
		std::cout << sub_tree->m_value << " found ";
		if (!search_nodes.empty()) {
			for (auto it = search_nodes.begin(); it != search_nodes.end(); it++) {
				std::cout << *it;
				if (search_nodes.end() - 1 != it) {
					std::cout << ", ";
				}
			}
		}
		std::cout << std::endl;
	}
	else {
		node* temp = head;
		search_nodes.push_back(temp->m_value);
		if (temp->m_value < sub_tree->m_value) {
			if (temp->m_right != nullptr) {
				search_value(temp->m_right);
			}
			else {
				std::cout << sub_tree->m_value << "not found!" << std::endl;
				return;
			}
		}
		else {
			if (temp->m_left != nullptr) {
				search_value(temp->m_left);
			}
			else {
				std::cout << sub_tree->m_value << "not found!" << std::endl;
				return;
			}
		}
	}
	return;
}

void tree::search_subtree(node* head, node* search_head)
{
	if (head->m_value == search_head->m_value) {
		subtree_found++;
		if (search_head->m_left != nullptr) {
			if (head->m_left != nullptr) {
				search_subtree(head->m_left, search_head->m_left);
			}
			else {
				std::cout << "Subtree not found!" << std::endl;
				return;
			}
		}
		if (search_head->m_right != nullptr) {
			if (head->m_right != nullptr) {
				search_subtree(head->m_right, search_head->m_right);
			}
			else {
				std::cout << "Subtree not found!" << std::endl;
				return;
			}
		}
	}
	else {
		if (head->m_value < search_head->m_value) {
			if (head->m_right != nullptr) {
				search_subtree(head->m_right, search_head);
			}
			else {
				std::cout << "Subtree not found!" << std::endl;
				return;
			}
		}
		if (head->m_value > search_head->m_value) {
			if (head->m_left != nullptr) {
				search_subtree(head->m_left, search_head);
			}
			else {
				std::cout << "Subtree not found!" << std::endl;
				return;
			}
		}

	}
	if ((head->m_value == root->m_value)&&(subtree_found == sub_tree_size)) {
		std::cout << "Subtree found!" << std::endl;
	}
	return;
}

