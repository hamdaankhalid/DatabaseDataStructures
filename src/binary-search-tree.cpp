#include <database-data-structures/data-structures.hpp>

#include <memory>
#include <string>
#include <iostream>

class Node {
  public:
    int val;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(int value): val(value), left(nullptr), right(nullptr) {}
};


struct FindResult {
  std::shared_ptr<Node> node;
  std::shared_ptr<Node> parent;
};

void DatabaseDataStructure::BinarySearchTree::_print_tree(std::string& prefix, std::shared_ptr<Node> node, bool is_left) {
	if (node == nullptr) return;

	std::cout << prefix;

	std::cout << (is_left ? "├──" : "└──" );

	std::cout << node->val << std::endl;
	std::string new_prefix = prefix + (is_left ? "│   " : "    ");
	_print_tree( new_prefix, node->left, true);
	_print_tree( new_prefix, node->right, false);
};

std::shared_ptr<Node> DatabaseDataStructure::BinarySearchTree::_find_inorder_successor(std::shared_ptr<Node> node) {
	// this gets us the min value after the passed node
	std::shared_ptr<Node> n = node;
	while (n->left != nullptr) {
		n = n->left;
	}
	return n;
}

void _inorder(std::shared_ptr<Node> node) {
	if (!node) {
		return;
	}
	_inorder(node->left);
	std::cout << node->val << std::endl;
	_inorder(node->right);
}

DatabaseDataStructure::BinarySearchTree::BinarySearchTree(){
	root = nullptr;
};


void DatabaseDataStructure::BinarySearchTree::add(int value) {
	std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
	std::shared_ptr<Node> current_node = root;
	std::shared_ptr<Node> parent = nullptr;
	while (current_node != nullptr) {
		parent = current_node;
		// based on current_node's value as compared to value decide whether to go left or to go right
		if(value > current_node->val) {
			current_node = current_node->right;
		} else if (value < current_node->val) {
			current_node = current_node->left;
		} else { return; }
	}
	// now we need to make the decision whether the new node will be a right child or left child of the parent
	// or if this is the first node being inserted then make this the root
	if (parent == nullptr) {
		root = new_node;
	} else if(value < parent->val) {
		parent->left = new_node;
	} else {
		parent->right = new_node;
	}
};


FindResult DatabaseDataStructure::BinarySearchTree::_recur_find(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, int value) {
      if (node == nullptr) {
        return {nullptr, nullptr};
      }

      FindResult found_right;
      FindResult found_left;
      if (value < node->val){
        found_right = _recur_find(node->left, node, value);
      } else if (value > node->val){
        found_left = _recur_find(node->right, node, value);
      } else {
        return {node, parent};
      }

      if (found_left.node != nullptr) {
        return found_left;
      } else if (found_right.node != nullptr) {
        return found_right;
      } else {
        return { nullptr, nullptr };
      }
    }

void DatabaseDataStructure::BinarySearchTree::remove(int value) {
	// find the node to be deleted
      FindResult find_res = _recur_find(root, nullptr, value);
      std::shared_ptr<Node> node_to_be_deleted = find_res.node;
      std::shared_ptr<Node> parent = find_res.parent;
      if (node_to_be_deleted == nullptr) {
        return;
      }
      // if the node to be deleted is leaf, or not.
      if (node_to_be_deleted->left == nullptr && node_to_be_deleted->right == nullptr) {
        if (parent == nullptr) {
          root = nullptr;
        } else if(parent->left == node_to_be_deleted) {
          parent->left = nullptr;
        } else {
          parent->right = nullptr;
        }
      } else if (node_to_be_deleted->left != nullptr && node_to_be_deleted->right == nullptr){
        // node has left child and no right child.
        if(parent->left == node_to_be_deleted) {
          parent->left = node_to_be_deleted->left;
        } else {
          parent->right = node_to_be_deleted->left;
        }
      } else if (node_to_be_deleted->right != nullptr && node_to_be_deleted->left == nullptr){
        // node has right child and no left child.
        if(parent->left == node_to_be_deleted) {
          parent->left = node_to_be_deleted->right;
        } else {
          parent->right = node_to_be_deleted->right;
        }
      } else {
        // node has both a left and a right child
        // in this case we need to find the node_to_be_deleted's inorder successor
        // Copy contents of the inorder successor to the node and delete the inorder successor.
        std::shared_ptr<Node> inorder_successor = _find_inorder_successor(node_to_be_deleted);
        int val_for_node_to_be_deleted = inorder_successor->val;
        remove(inorder_successor->val);
        node_to_be_deleted->val = val_for_node_to_be_deleted;
      }
}

bool DatabaseDataStructure::BinarySearchTree::find(int value) {
 	FindResult res = _recur_find(root, nullptr, value);
  return res.node != nullptr;
}

void DatabaseDataStructure::BinarySearchTree::b_tree_print() {
	std::string start = "";
  _print_tree(start, root, false);
}

void DatabaseDataStructure::BinarySearchTree::print() {
	_inorder(root);
};
