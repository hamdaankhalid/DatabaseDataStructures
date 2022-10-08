#pragma once

#include<memory>

class Node;
struct FindResult;

namespace DatabaseDataStructure {
 
	class BinarySearchTree {

		std::shared_ptr<Node> root;
		std::shared_ptr<Node> _find_inorder_successor(std::shared_ptr<Node> node);
		FindResult _recur_find(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, int value);
		void _print_tree(std::string& prefix, std::shared_ptr<Node> node, bool is_left);
		void _inorder(std::shared_ptr<Node> node);

		public:
		BinarySearchTree();
		void add(int value);
		bool find(int value);
		void remove(int value);
		void print();
		void b_tree_print();
	};

}
