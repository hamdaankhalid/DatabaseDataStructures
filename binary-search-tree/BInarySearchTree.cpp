#include <iostream>
#define INVALID_INPUT -5


class Node {
  public:
    int val;
    std::shared_ptr<Node> left;
    std::shared_ptr<Node> right;
    Node(int value) {
      val = value;
      left = nullptr;
      right = nullptr;
    }
};

struct FindResult {
  std::shared_ptr<Node> node;
  std::shared_ptr<Node> parent;
};

class BinarySearchTree {
  private:
    std::shared_ptr<Node> root;

    void _inorder(std::shared_ptr<Node> node) {
      if (!node) {
        return;
      }
      _inorder(node->left);
      std::cout << node->val << std::endl;
      _inorder(node->right);
    }

    FindResult _recur_find(std::shared_ptr<Node> node, std::shared_ptr<Node> parent, int value) {
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

    std::shared_ptr<Node> _find_inorder_successor(std::shared_ptr<Node> node) {
      // this gets us the min value after the passed node
      std::shared_ptr<Node> n = node;
      while (n->left != nullptr) {
        n = n->left;
      }

      return n;
    }

  public:

    BinarySearchTree() {
      root = nullptr;
    };

    void print(){
      _inorder(root);
    }

    void add(int value) {
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
    }

    bool find(int value){
      FindResult res = _recur_find(root, nullptr, value);
      return res.node != nullptr;
    }

    void remove(int value) {
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
};

int main() {
  BinarySearchTree binaryTree;
  std::cout << "Binary Tree Program" << std::endl;
  int input = 0;

  while(true) {
    std::cout << "Enter the number to choose an operation: \n\
    1. Add int to binary tree. \n\
    2. Remove int from binary tree. \n\
    3. Check if a value exists in a binary tree. \n\
    4. Exit program. \n";

    std::cin >> input;
    int val;
    switch (input){
      case 1: {
        std::cout << "Enter val to add" << std::endl;
        std::cin >> val;
        binaryTree.add(val);   
        break;
      }
      case 2: {
        std::cout << "Enter val to remove" << std::endl;
        std::cin >> val;
        binaryTree.remove(val);
        break;
      }
      case 3:{
        std::cout << "Enter val to find" << std::endl;
        std::cin >> val;
        bool found = binaryTree.find(val);
        std::cout << "Finding result (0 if not found, 1 if found): " << found << std::endl;
        break;
      }
      case 4:{
        std::cout << "Thank you!" << std::endl;
        return 0;
      }
      default: {
        std::cout << "Invalid input" << std::endl;
        input = INVALID_INPUT;
        break;
      }
    }

    std::cout << "**** Your BST *****" << std::endl;
    binaryTree.print();
    std::cout << "*******\n";
  }
}
