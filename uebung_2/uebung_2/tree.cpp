

#include "tree.h"
bool tree::get_tree(std::string& filename, bool use_root)
{
	FILE* input_data;
	std::ifstream fin;
	fin.open(filename);
	if (!fin)
		std::cout << "no. wrong path dude";
	int val;
	while (fin >> val)
	{
		if (!this->insert_value(val, use_root))
			std::cout << "There was an error during insertion of value: " << val << "; value already exists" << std::endl;
		else {
			std::cout << "Insertion of " << val << " was successful!" << std::endl;
			if (!use_root) {
				sub_tree_size++;
			}
		}
			
		
	}
	fin >> val;
	return false;
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
					if (use_root) {
						root = head;
					}
					else {
						sub_tree = head;
					}
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
					if (use_root) {
						root = head;
					}
					else {
						sub_tree = head;
					}
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

void tree::print_tree()
{
	print_tree("", root, false);
}

void tree::print_menu()
{
	std::cout << "### -- Tree Constructer Program -- ###" << std::endl << std::endl;
	std::cout << "These inputs are possible: " << std::endl;
	std::cout << "   - create tree 1    -> (input1)" << std::endl;
	std::cout << "   - create tree 2    -> (input2) " << std::endl;
	std::cout << "   - create own tree  -> (create)" << std::endl;
	std::cout << "   - print tree	    -> (print)" << std::endl;
	std::cout << "   - AVL condition    -> (AVL)" << std::endl;
	std::cout << "   - search value     -> (search)" << std::endl;
	std::cout << "   - search subtree   -> (subtree)" << std::endl;
	std::cout << "   - quit             -> (quit)" << std::endl;

}

void tree::handle_input(std::string& input)
{
	if (input == "input1")
	{
		delete_tree();
		input.append(".txt");
		std::cout << input;
		if(get_tree(input, true))
			std::cout << "Tree successfully constructed!" << std::endl;
		print_tree();
		return;
	}
	if (input == "input2")
	{
		delete_tree();
		if (get_tree(input.append(".txt"), false))
			std::cout << "Tree successfully constructed!" << std::endl;
		print_tree();
		return;
	}
	if (input == "create")
	{
		delete_tree();
		if (create_own_tree())
			print_tree();
	}
	if (input == "print")
		print_tree();
	if (input == "AVL")
		check_avl_condition();
	if (input == "search")
		search();
	if (input == "subtree")
		search_subtree(root, sub_tree);
	if (input == "quit")
		run = false;
}

bool tree::create_own_tree()
{
	std::string numbers;
	std::cout << "Enter your number in the following order: #,#,#,#,..." << std::endl;
	std::cin >> numbers;
	std::istringstream num(numbers);
	std::vector<int> x;
	while (std::getline(num, numbers, ','))
	{
		x.push_back(std::stoi(numbers));
	}
	for (int i = 0; i < x.size(); i++)
	{
		if (insert_value(x[i], root))
			std::cout << x[i] << " successfully inserted. " << std::endl;
		else
			std::cout <<"Error: "<< x[i] << " already exists" << std::endl;
	}
	return true;

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

void tree::add_search() {
	int val1 = 23;
	sub_tree = new node(val1);
	sub_tree_size = 1;
}