#include <iostream>
#include <string>
#include <vector>

#include "dna_strand.hpp"
#include "doubly_linked_list.hpp"

using namespace std;

int main() {
  DNAstrand list("A");
  DNAstrand better("T");
  DNAstrand copy("AAAAAA");
  copy.SpliceIn(list, better);
  std::cout << copy.Str() << std::endl;
  DNAstrand other("TT");
  DNAstrand p2("C");
  copy.SpliceIn(other, p2);
  std::cout << copy.Str() << std::endl;
}
