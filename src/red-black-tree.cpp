#include <database-data-structures/data-structures.hpp>


// Lets have our Node in red black trees keep track of their parent, and have a color
class Node {
  public:
    int val;
    bool isBlack;
    std::shared_ptr<Node> parent;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    // every new node is red during insertion
    Node(int value, bool black = false): val(value), isBlack(black), parent(nullptr), left(nullptr), right(nullptr) {}
};


DatabaseDataStructure::RedBlackTree::RedBlackTree() {
  root = nullptr;
}


void DatabaseDataStructure::RedBlacktree::add() {
  // do regular add then call a subprocedure to fix the tree up
  std::shared_ptr<Node> new_node = std::make_shared<Node>(value);
  if (root == nullptr) {
    new_node->isBlack = true;
    root = new_node;
    return;
  }
  parent = nullptr;
  current = root;
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
  if (value < parent->val) {
    parent->left = new_node;
  } else if (value > parent->val) {
    parent->right = new_node;
  } else {
    return;
  }
  
  rebalance_tree(new_node);
}

void DatabaseDataStructure::RedBlackTree::rebalance_tree(std::shared_ptr<Node> node) {
  // TODO: Rebalancing
}


bool DatabaseDataStructure::RedBlacktree::find(int value) {

}


void DatabaseDataStructure::RedBlacktree::remove() {

}


void DatabaseDataStructure::RedBlacktree::print() {

}


void DatabaseDataStructure::RedBlacktree::b_tree_print() {

}


void DatabaseDataStructure::RedBlacktree::rotate_left(std::shared_ptr<Node> node) {

}


void DatabaseDataStructure::RedBlacktree::rotate_right(std::shared_ptr<Node> node) {

}
