#ifndef DNA_STRAND_HPP
#define DNA_STRAND_HPP

#include "node.hpp"

class DNAstrand {
public:
  DNAstrand() = default;
  DNAstrand(const char* pt);
  DNAstrand(const DNAstrand& rhs) = delete;
  DNAstrand& operator=(const DNAstrand& rhs) = delete;
  ~DNAstrand();

  // helper remove func
  void RemoveIdx(unsigned int& idx, const char* pattern);
  void RemoveAt(unsigned int index);

  // helper insert func
  void InsertAtFront(Node*& begin, Node*& end);
  void InsertMiddle(unsigned int index, Node*& begin, Node*& end);
  void InsertAtEnd(Node*& begin, Node*& end);

  // helper size func
  int Size();

  void SpliceIn(const char* pattern, DNAstrand& to_splice_in);

  // helper print func
  // void PrintDNA(const DNAstrand& dna);

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
};

unsigned int StrLen(const char* input);

#endif