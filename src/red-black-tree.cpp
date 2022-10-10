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
  { std::cout << "I AM " << node->val << " AND MY PARENT IS ";
  if (node->parent!=nullptr)
    std::cout << node->parent->val << std::endl;
  else
    std::cout << "Nobody :(" << std::endl;
  }

  while (node->parent!=nullptr && node->parent->parent!=nullptr && !node->parent->isBlack) {
    std::cout << "rebala\n";
    // TODO: SEGFAULT HERE
    if (node->parent == node->parent->parent->left) { // is node's parent a left child
      std::shared_ptr<RBLNode> aunty = node->parent->parent->right;
      if (!aunty->isBlack) {
        node->parent->isBlack = true;
        aunty->isBlack = true;
        node->parent->parent->isBlack = false;
        node = node->parent->parent;
      } else {
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
      if (!aunty->isBlack) {
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


void DatabaseDataStructure::RedBlackTree::remove(int value) {

}


void DatabaseDataStructure::RedBlackTree::print() {

}


void DatabaseDataStructure::RedBlackTree::b_tree_print() {

}


void DatabaseDataStructure::RedBlackTree::rotate_left(std::shared_ptr<RBLNode> node) {
  auto right_child = node->right;
  node->right = right_child->left;
  if (right_child->left == nullptr) {
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
  if (left_child->right == nullptr) {
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
