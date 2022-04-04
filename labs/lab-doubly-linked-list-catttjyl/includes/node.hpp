#ifndef NODE_H
#define NODE_H

// Definition of node provided to you
struct Node {
  Node() = default;
  Node(char data) : data(data) {}

  char data = '\0'; // NOLINT
  Node *next = nullptr; // NOLINT
  Node *prev = nullptr; // NOLINT
};

#endif