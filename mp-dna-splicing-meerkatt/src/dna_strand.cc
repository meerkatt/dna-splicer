#include "dna_strand.hpp"

DNAstrand::DNAstrand(const std::vector<char>& sequence) {
  std::vector<char> temp = sequence;
  for (size_t i = 0; i < temp.size(); ++i) {
    char val = temp.at(i);
    int check = CheckChar(temp.at(i));
    if (check == 0) {
      throw std::runtime_error("Invalid Character");
    } else if (check == 2) {
      val -= 32;
      temp.at(i) = val;
    }
  }
  DNAstrand::DoublyLinkedList();
  for (size_t i = 0; i < temp.size(); ++i) {
    push_back(temp.at(i));
  }
}
DNAstrand::DNAstrand(const std::string& sequence) {
  std::string temp = sequence;

  for (size_t i = 0; i < temp.size(); ++i) {
    char val = temp.at(i);
    int check = CheckChar(temp.at(i));
    if (check == 0) {
      throw std::runtime_error("Invalid Character");
    } else if (check == 2) {
      val -= 32;
      temp.at(i) = val;
    }
  }
  DNAstrand::DoublyLinkedList();
  for (size_t i = 0; i < temp.size(); ++i) {
    push_back(temp.at(i));
  }
}
DNAstrand::DNAstrand(const DNAstrand& rhs): DoublyLinkedList(rhs) {}
DNAstrand& DNAstrand::operator=(const DNAstrand& rhs) {
  if (this->head_ == rhs.getHead()) {
    return *this;
  }

  clear();
  if (rhs.empty()) {
    return *this;
  }
  Node<char>* curr = rhs.getHead();

  while (curr->next) {
    this->push_back(curr->data);
    curr = curr->next;
  }
  this->push_back(curr->data);
  return *this;
}
DNAstrand::~DNAstrand() { DNAstrand::~DoublyLinkedList(); }

void DNAstrand::SpliceIn(const DNAstrand& pattern,
                         const DNAstrand& to_splice_in) {
  if (this == &pattern || &to_splice_in == &pattern || this == &to_splice_in) {
    throw std::runtime_error("can't use same strand");
  }
  std::string pat = pattern.Str();
  std::string seq = Str();
  std::string splicestr = to_splice_in.Str();
  size_t node_idx = 0;
  while (seq.find(pat, node_idx) != std::string::npos) {
    node_idx = seq.find(pat, node_idx);
    Node<char>* curr = head_;
    Node<char>* splice = to_splice_in.getHead();
    for (size_t it = 0; it < node_idx; ++it) {
      curr = curr->next;
    }
    for (size_t it = 0; it < pat.size(); ++it) {
      if (splice == nullptr) {
        erase_at(node_idx);
        // node_idx;
        continue;
      }
      curr->data = splice->data;
      // std::cout << splice->data << std::endl;
      curr = curr->next;
      splice = splice->next;
      ++node_idx;
      if (curr == pattern.getHead() || pattern.getHead() == splice) {
        throw std::runtime_error("can't use same strand");
      }
    }
    while (splice) {
      // std::cout << splice->data << std::endl;
      insert_at(node_idx, splice->data);
      splice = splice->next;
      ++node_idx;
    }
    seq = Str();
  }
}

std::string DNAstrand::Str() const {
  std::ostringstream oss;
  oss << *this;
  std::string dna = oss.str();
  return dna;
}

int DNAstrand::CheckChar(char dna) {
  if (dna == 'a' || dna == 'c' || dna == 't' || dna == 'g') {
    return 2;
  } else if (dna == 65 || dna == 67 || dna == 71 || dna == 84) {
    return 1;
  } else {
    return 0;
  }
}

std::ostream& operator<<(std::ostream& os, const DNAstrand& dna_strand) {
  Node<char>* curr = dna_strand.getHead();
  while (curr) {
    os << curr->data;
    curr = curr->next;
  }
  return os;
}