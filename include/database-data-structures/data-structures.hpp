#pragma once

#include<memory>
#include <functional>
#include <vector>

class Node;
struct FindResult;

class RBLNode;

namespace DatabaseDataStructure {
	class Tree {
		public:
			virtual ~Tree(){};
			virtual void add(int value) = 0;
			virtual bool find(int value) = 0;
			virtual void remove(int value) = 0;
			virtual void print() = 0;
	};

	class BinarySearchTree : public Tree {
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

	class RedBlackTree : public Tree {
		std::shared_ptr<RBLNode> root;
		void rebalance_tree(std::shared_ptr<RBLNode> node);
		void rotate_left(std::shared_ptr<RBLNode> node);
		void rotate_right(std::shared_ptr<RBLNode> node);
		void _print_tree(std::string& prefix, std::shared_ptr<RBLNode> node, bool is_left);
		void _inorder(std::shared_ptr<RBLNode> node);
		void _remove_fix_up(std::shared_ptr<RBLNode> node);
		void _transplant(std::shared_ptr<RBLNode> node_to_remove, std::shared_ptr<RBLNode> replacement_node);

		public:
		RedBlackTree();
		void add(int value);
		bool find(int value);
		void remove(int value);
		void print();
		void b_tree_print();
	};

	class BloomFilter {
		public:
		BloomFilter(int size);
		void add(std::string item);
		bool does_probably_exist(std::string item);

		private:
		std::vector<bool> _bit_flowers;
		std::vector<std::hash<std::string>> _hashers;
	};
}
