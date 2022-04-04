#ifndef BINARYSEARCHTREE_HPP
#define BINARYSEARCHTREE_HPP

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "tree_node.hpp"

/******************************************************
 * CLASS DEFINITIONS + HELPER FUNCTION DECLARATIONS
 ******************************************************/

template <typename T>
class BinarySearchTree {
public:
  BinarySearchTree();
  BinarySearchTree(const BinarySearchTree& lhs) = delete;
  BinarySearchTree<T>& operator=(const BinarySearchTree& lhs) = delete;
  ~BinarySearchTree();

  /*
    Wrapper function to insert a value into the tree

    @param data the value to be inserted
    @return the root of the new tree
  */
  TreeNode<T>* InsertNode(const T& data);

  /*
    Wrapper function to delete a value from the tree

    @param data the value to be deleted
    @return the root of the new tree
  */
  TreeNode<T>* DeleteNode(const T& data);

  /*
    Wrapper function to calculate the height of the tree

    @return the height of the root of the tree
  */
  int GetHeight() const;

  /*
    Getter function for the root of the tree
  */
  TreeNode<T>* GetRoot() const;

  /*
    Allow overloaded output operator access to private data
  */
  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const BinarySearchTree<U>& bst);

private:
  TreeNode<T>* root_;

  /*
  Helper function to insert a node into the tree

  @param node the current tree node in the recursive call
  @param data the value to be inserted
  @return the root node of the new (sub)tree
  */
  TreeNode<T>* InsertNode(TreeNode<T>* node, const T& data);

  /*
  Helper function to delete a node in the tree

  @param node the current tree node in the recursive call
  @param data the value to be deleted
  @return the root of the (sub)tree
  */
  TreeNode<T>* DeleteNode(TreeNode<T>* node, const T& data);

  /*
  Helper function to get the height of the tree

  @param node the current tree node in the recursive call
  @return the height of the current node
  */
  int GetHeight(TreeNode<T>* node) const;

  /*
  Helper function for destructor

  @param node the current tree node in the recursive call
  */
  void Clear(TreeNode<T>* node);

  /*
  Adds printable data for the tree into the output vector

  @param node the current tree node in the recursive call
  @param output the output vector which stores the list of strings to be
  printed
  @param left the number of offset characters from the left
  @param top the number of offset characters from the top
  @param width width of the output based on height of the tree
  */

  void AddPrintableData(TreeNode<T>* node,
                        std::vector<std::string>& output,
                        int left,
                        int top,
                        int width) const;
};

/*
  Declaration of overloaded operator<< for pretty printing of
  BinarySearchTree<T>
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst);

/******************************************************
 * MEMBER FUNCTION + HELPER FUNCTION DEFINITIONS
 ******************************************************/

template <typename T>
BinarySearchTree<T>::BinarySearchTree(): root_(nullptr) {}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(const T& data) {
  root_ = InsertNode(root_, data);
  return root_;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::InsertNode(TreeNode<T>* node, const T& data) {
  auto* tmp = new TreeNode<T>(data);
  if (root_ == nullptr) {
    root_ = tmp;
  } else {
    auto* iter = node;
    auto* parent = node;
    while (iter != nullptr) {
      parent = iter;
      if (data < iter->data)
        iter = iter->left;
      else
        iter = iter->right;
    }
    if (data < parent->data)
      parent->left = tmp;
    else
      parent->right = tmp;
  }
  return root_;
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(const T& data) {
  if (root_ == nullptr) {
    return nullptr;
  }

  root_ = DeleteNode(root_, data);
  return root_;
}

template <typename T>
void BinarySearchTree<T>::Clear(TreeNode<T>* node) {
  if (node) {
    Clear(node->left);
    Clear(node->right);
    delete node;
  }
}

template <typename T>
BinarySearchTree<T>::~BinarySearchTree() {
  Clear(root_);
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::DeleteNode(TreeNode<T>* node, const T& data) {
  if (data < node->data) {
    node->left = DeleteNode(node->left, data);
  } else if (data > node->data) {
    node->right = DeleteNode(node->right, data);
  } else {
    if (node->left == nullptr && node->right == nullptr) {
      std::cout << "leaf child" << std::endl;
      node = nullptr;
    } else if (node->left == nullptr) {
      std::cout << "with one right child" << std::endl;
      auto* right = node->right;
      delete node;
      node = right;
    } else if (node->right == nullptr) {
      std::cout << "with one left child" << std::endl;
      auto* left = node->left;
      delete node;
      node = left;
    } else {
      std::cout << "with two children" << std::endl;
      auto* succ_parent = node;
      auto* succ = node->right;
      while (succ->left != nullptr) {
        succ_parent = succ;
        succ = succ->left;
      }
      std::cout << "successor is " << succ->data << std::endl;
      if (succ_parent != node) {
        succ_parent->left = succ->right;
      } else {
        succ_parent->right = succ->right;
      }
      succ->left = node->left;
      succ->right = node->right;
      delete node;
      node = succ;
    }
  }

  return node;
}

template <typename T>
int BinarySearchTree<T>::GetHeight() const {
  return GetHeight(root_);
}

template <typename T>
int BinarySearchTree<T>::GetHeight(TreeNode<T>* node) const {
  if (node == nullptr) {
    return -1;
  }

  return 1 + std::max(GetHeight(node->left), GetHeight(node->right));
}

template <typename T>
TreeNode<T>* BinarySearchTree<T>::GetRoot() const {
  return root_;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const BinarySearchTree<T>& bst) {
  size_t root_height = bst.GetHeight() + 1;

  std::vector<std::string> output(2 * root_height - 1);
  for (size_t i = 0; i < output.size(); i++) {
    output[i] = std::string((4 << root_height) + 1, ' ');
  }

  bst.AddPrintableData(bst.root_, output, 0, 0, (4 << root_height) - 3);

  for (size_t i = 0; i < output.size(); i++) {
    os << output[i] << std::endl;
  }
  return os;
}

template <typename T>
void BinarySearchTree<T>::AddPrintableData(TreeNode<T>* node,
                                           std::vector<std::string>& output,
                                           int left,
                                           int top,
                                           int curr_width) const {
  std::stringstream ss;
  std::string str;
  ss << node->data;
  ss >> str;

  int left_start_shift = 1 - (str.length() - 1) / 2;
  for (size_t i = 0;
       i < str.length() && left + curr_width / 2 + i < output[top].length();
       i++) {
    output[top][left + curr_width / 2 + left_start_shift + i] = str[i];
  }

  int branchOffset = (curr_width + 3) >> 3;

  int center = left + curr_width / 2;
  int leftcenter = left + (curr_width / 2 - 1) / 2;
  int rightcenter = left + curr_width / 2 + 2 + (curr_width / 2 - 1) / 2;

  if (node->left) {
    int branch_pos = center - branchOffset + 1;
    for (int pos = center + left_start_shift - 2; pos > branch_pos; pos--) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '/';
    for (int pos = branch_pos - 1; pos > leftcenter + 2; pos--) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->left, output, left, top + 2, curr_width / 2 - 1);
  }

  if (node->right) {
    int branch_pos = center + branchOffset + 1;
    for (int pos = center + left_start_shift + str.length() + 1;
         pos < branch_pos;
         pos++) {
      output[top][pos] = '_';
    }

    output[top + 1][branch_pos] = '\\';
    for (int pos = branch_pos + 1; pos < rightcenter; pos++) {
      output[top + 1][pos] = '_';
    }

    AddPrintableData(node->right,
                     output,
                     left + curr_width / 2 + 2,
                     top + 2,
                     curr_width / 2 - 1);
  }
}

#endif  // BINARYSEARCHTREE_HPP