#ifndef TREE_NODE_HPP
#define TREE_NODE_HPP

template <typename T>
struct TreeNode {
  TreeNode(const T& dat): data(dat), left(nullptr), right(nullptr) {}
  T data;           // NOLINT
  TreeNode* left;   // NOLINT
  TreeNode* right;  // NOLINT
};

#endif