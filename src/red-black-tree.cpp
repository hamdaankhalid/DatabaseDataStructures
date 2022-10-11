#include <database-data-structures/data-structures.hpp>
#include <iostream>

// Lets have our RBLNode in red black trees keep track of their parent, and have a color
class RBLNode {
  public:
    int val;
    bool isBlack;
    std::shared_ptr<RBLNode> parent;
    std::shared_ptr<RBLNode> left;
    std::shared_ptr<RBLNode> right;
    // every new node is red during insertion
    RBLNode(int value, bool black = false): val(value), isBlack(black), parent(nullptr), left(nullptr), right(nullptr) {}
};


DatabaseDataStructure::RedBlackTree::RedBlackTree() {
  root = nullptr;
}


void DatabaseDataStructure::RedBlackTree::add(int value) {
  // do regular add then call a subprocedure to fix the tree up
  std::shared_ptr<RBLNode> new_node = std::make_shared<RBLNode>(value);
  if (root == nullptr) {
    new_node->isBlack = true;
    root = new_node;
    return;
  }
  std::shared_ptr<RBLNode> parent = nullptr;
  auto current = root;
  while (current != nullptr) {
    parent = current;
    if (value < current->val) {
      current = current->left;
    } else if (value > current->val) {
      current = current->right;
    } else {
      // looks like this value already exists in RBLTree, we do not handle duplicates
      return;
    }
  }

  new_node->parent = parent;
  int parent_val = parent->val;
  if (value < parent_val) {
    parent->left = new_node;
  } else if (value > parent_val) {
    parent->right = new_node;
  } else {
    return;
  }

  rebalance_tree(new_node);
}


void DatabaseDataStructure::RedBlackTree::rebalance_tree(std::shared_ptr<RBLNode> node) {
  while (node->parent!=nullptr && node->parent->parent!=nullptr && !node->parent->isBlack) {  
    if (node->parent == node->parent->parent->left) { // is node's parent is a left child
      std::shared_ptr<RBLNode> aunty = node->parent->parent->right;
      if (aunty != nullptr && !aunty->isBlack) {
        
        node->parent->isBlack = true;
        aunty->isBlack = true;
        node->parent->parent->isBlack = false;
        node = node->parent->parent;
      } else { // the aunt is black
      
        if (node == node->parent->right) {
          node = node->parent;
          rotate_left(node);
        }
        node->parent->isBlack = true;
        node->parent->parent->isBlack = false;
        rotate_right(node->parent->parent);
      }
    } else {
      std::shared_ptr<RBLNode> aunty = node->parent->parent->left;

      if (aunty != nullptr && !aunty->isBlack) {
        node->parent->isBlack = true;
        aunty->isBlack = true;
        node->parent->parent->isBlack = false;
      } else {
        if (node == node->parent->left) {
          node = node->parent;
          rotate_right(node);
        }
        node->parent->isBlack = true;
        node->parent->parent->isBlack = false;

        rotate_left(node->parent->parent);
      }
    }
  }
  root->isBlack = true;
}


bool DatabaseDataStructure::RedBlackTree::find(int value) {
  auto current = root;
  while (current != NULL) {
    if (current->val == value)
      return true;
    if (value < current->val) {
      current = current->left;
    } else {
      current = current->right;
    }
  }
  return false;
}


void DatabaseDataStructure::RedBlackTree::_remove_fix_up(std::shared_ptr<RBLNode> node) {
  while(node != nullptr && node != root && node->isBlack) {
    if (node == node->parent->left) {
      auto sibling = node->parent->right;
      if (sibling != nullptr && !sibling->isBlack) {
        sibling->isBlack = true;
        node->parent->isBlack = false;
        rotate_left(node->parent);
        sibling = node->parent->right;
      }
      
      if (
        (sibling->left == nullptr && sibling->right == nullptr) ||
        (sibling->left->isBlack && sibling->right->isBlack)
      ) {
        sibling->isBlack = false;
        node = node->parent;
      } else {
        if(sibling && (sibling->right == nullptr || sibling->right->isBlack)) {
          sibling->left->isBlack = true;
          sibling->isBlack = false;
          rotate_right(sibling);
          sibling = node->parent->right;
        }

        if (sibling)
          sibling->isBlack = node->parent->isBlack;
        node->parent->isBlack = true;
        node->right->isBlack = true;
        rotate_left(node->parent);
        node = root;
      }
    }
  }
  if (node!=nullptr)
    node->isBlack = true;
}

void DatabaseDataStructure::RedBlackTree::_transplant(std::shared_ptr<RBLNode> node_to_remove, std::shared_ptr<RBLNode> replacement_node) {
  if (node_to_remove->parent == nullptr) {
    root = replacement_node;
    return;
  }
  if (node_to_remove == node_to_remove->parent->left) {
    node_to_remove->parent->left = replacement_node;
  } else {
    node_to_remove->parent->right = replacement_node;
  }

  if (replacement_node != nullptr)
    replacement_node->parent = node_to_remove->parent;
}

void DatabaseDataStructure::RedBlackTree::remove(int value) {
 // find the node to delete then call fix up based on the node and its children scenario
  auto curr = root;
  while (curr!=nullptr) {
    if (value == curr->val) {
      break;
    } else if (value < curr->val) {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
  }
  if (curr == nullptr) return;

  if (curr->left == nullptr) {
    _transplant(curr, curr->right);
    _remove_fix_up(curr->right);
  } else if (curr->right == nullptr) {
    _transplant(curr, curr->left);
    _remove_fix_up(curr->left);
  } else {
    // find min in right subtree
    auto right_subtree_curr = curr->right;
    std::shared_ptr<RBLNode> right_subtree_min = right_subtree_curr;
    while(right_subtree_curr !=nullptr) {
      right_subtree_curr = right_subtree_curr->left;
      if (right_subtree_curr!=nullptr){
        right_subtree_min = right_subtree_curr;
      }
    }
    _transplant(curr, right_subtree_min);
    _remove_fix_up(right_subtree_min);
  }
}


void DatabaseDataStructure::RedBlackTree::print() {
  std::string start = "";
  _print_tree(start, root, false);
}

void DatabaseDataStructure::RedBlackTree::_print_tree(std::string& prefix, std::shared_ptr<RBLNode> node, bool is_left){
  if (node == nullptr) return;

	std::cout << prefix;

	std::cout << (is_left ? "├──" : "└──" );

	std::cout << node->val << std::endl;
	std::string new_prefix = prefix + (is_left ? "│   " : "    ");
	_print_tree( new_prefix, node->left, true);
	_print_tree( new_prefix, node->right, false);
}

void DatabaseDataStructure::RedBlackTree::_inorder(std::shared_ptr<RBLNode> node) {
  if (!node) {
		return;
	}
	_inorder(node->left);
	std::cout << node->val << std::endl;
	_inorder(node->right);
}

void DatabaseDataStructure::RedBlackTree::b_tree_print() {
  std::string start = "";
  _print_tree(start, root, false);
}


void DatabaseDataStructure::RedBlackTree::rotate_left(std::shared_ptr<RBLNode> node) {
  std::shared_ptr<RBLNode> right_child = node->right;
  node->right = right_child->left;
  if (right_child->left != nullptr) {
    right_child->left->parent = node;
  }
  right_child->parent = node->parent;
  if (node->parent == nullptr) {
    root = right_child;
  } else if (node == node->parent->left) {
    node->parent->left = right_child;
  } else {
    node->parent->right = right_child;
  }
  right_child->left = node;
  node->parent = right_child;
}


void DatabaseDataStructure::RedBlackTree::rotate_right(std::shared_ptr<RBLNode> node) {
  auto left_child = node->left;
  node->left = left_child->left;
  if (left_child->right != nullptr) {
    left_child->right->parent = node;
  }
  left_child->parent = node->parent;
  if (node->parent == nullptr) {
    root = left_child;
  } else if (node == node->parent->right) {
    node->parent->right = left_child;
  } else {
    node->parent->left = left_child;
  }
  left_child->right = node;
  node->parent = left_child;
}
