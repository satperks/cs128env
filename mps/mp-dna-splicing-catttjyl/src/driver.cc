#include <iostream>

#include "dna_strand.hpp"

int main() {
  // const char* sequence = "ctgaattcg";
  // const char* pattern = "gaattc";
  // const char* to_splice = "tgatc";
  // DNAstrand seq(sequence);
  // DNAstrand splice(to_splice);
  // std::cout << "--seq before: ";
  // seq.PrintDNA(seq);
  // std::cout << "--splice before: ";
  // splice.PrintDNA(splice);

  // seq.SpliceIn(pattern, splice);

  // std::cout << "--seq after: ";
  // seq.PrintDNA(seq);
  // std::cout << "--splice after: ";
  // splice.PrintDNA(splice);

  const char* sequence = "ctata";
  const char* pattern = "ta";
  const char* to_splice = "tga";
  DNAstrand seq(sequence);
  DNAstrand splice(to_splice);
  std::cout << "--seq before: ";

  seq.PrintDNA(seq);
  std::cout << "--splice before: ";
  splice.PrintDNA(splice);

  seq.SpliceIn(pattern, splice);

  std::cout << "--seq after: ";
  seq.PrintDNA(seq);
  std::cout << "--splice after: ";
  splice.PrintDNA(splice);
  std::cout << "reach bottom" << std::endl;

  return 0;
}