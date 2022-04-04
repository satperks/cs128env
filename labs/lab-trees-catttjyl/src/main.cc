#include "binary_search_tree.hpp"

int main() {
  BinarySearchTree<int> bst;
  bst.InsertNode(10);
  bst.InsertNode(7);
  bst.InsertNode(4);
  bst.InsertNode(5);
  bst.InsertNode(15);
  bst.InsertNode(12);
  bst.InsertNode(18);
  bst.InsertNode(17);

  std::cout << "--------------------" << std::endl;
  std::cout << "Tree after insertion" << std::endl;
  std::cout << "--------------------" << std::endl;
  std::cout << bst << std::endl << std::endl;

  bst.DeleteNode(5);

  std::cout << "------------------------" << std::endl;
  std::cout << "Tree after deleting leaf" << std::endl;
  std::cout << "------------------------" << std::endl;
  std::cout << bst << std::endl << std::endl;

  bst.DeleteNode(18);

  std::cout << "---------------------------------------" << std::endl;
  std::cout << "Tree after deleting node with one child" << std::endl;
  std::cout << "---------------------------------------" << std::endl;
  std::cout << bst << std::endl << std::endl;

  bst.InsertNode(19);
  bst.DeleteNode(15);
  std::cout << "------------------------------------------" << std::endl;
  std::cout << "Tree after deleting node with two children" << std::endl;
  std::cout << "------------------------------------------" << std::endl;
  std::cout << bst << std::endl << std::endl;

  return 0;
}