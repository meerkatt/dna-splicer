#ifndef DNA_STRAND_H
#define DNA_STRAND_H

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include "doubly_linked_list.hpp"
#include "node.hpp"

class InvalidNucleotide {};
class InvalidSpliceIn {};

class DNAstrand : public DoublyLinkedList<char> {  // you need to ensure this
                                                   // type implements as
                                                   // DoublyLinkedList<char>
public:
  DNAstrand(const std::vector<char>& sequence);
  DNAstrand(const std::string& sequence);
  DNAstrand(const DNAstrand& rhs);
  DNAstrand& operator=(const DNAstrand& rhs);
  ~DNAstrand();

  void SpliceIn(const DNAstrand& pattern, const DNAstrand& to_splice_in);

  std::string Str() const;
  int CheckChar(char dna);

private:
};

std::ostream& operator<<(std::ostream& os, const DNAstrand& dna_strand);

#endif