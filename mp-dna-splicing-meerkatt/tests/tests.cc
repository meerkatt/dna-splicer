//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//                  MP : DNA Splicing : Student Test Cases                  //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "dna_strand.hpp"
#include "doubly_linked_list.hpp"
#include "node.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//               MP : Doubly Linked List : Student Test Cases               //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "doubly_linked_list.hpp"
#include "node.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("Testing Constructor", "[constructor]") {
  SECTION("Default Constructor") {
    DoublyLinkedList<char> list;

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty() == true);
  }
  SECTION("Parameterized Constructor Normal") {
    char x = 'x';
    DoublyLinkedList<char> list(x);

    REQUIRE(list.getHead()->data == x);
    REQUIRE(list.getTail()->data == x);
    REQUIRE(list.size() == 1);
    REQUIRE(list.empty() == false);
  }
  SECTION("Parameterized Constructor List") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);

    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getHead()->next->prev->data == '1');
    REQUIRE(list.getHead()->next->data == '2');
    REQUIRE(list.getHead()->next->next->prev->data == '2');
    REQUIRE(list.getHead()->next->next->data == '3');
    REQUIRE(list.getHead()->next->next->next->prev->data == '3');
    REQUIRE(list.getHead()->next->next->next->data == '4');

    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.size() == 4);
    REQUIRE(list.empty() == false);
  }
  SECTION("Parameterized Constructor List (Edge)") {
    std::vector<char> values;
    DoublyLinkedList<char> list(values);
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty() == true);
  }
  SECTION("Deep Copy  Constructor Base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    DoublyLinkedList<char> copy(list);
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
  SECTION("Deep Copy Constructor Edge") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    DoublyLinkedList<char> copy(list);
    copy.getHead()->data = 2;
    copy.getTail()->data = 3;
    REQUIRE(copy.getHead()->data != list.getHead()->data);
    REQUIRE(copy.getTail()->data != list.getTail()->data);
  }
}

TEST_CASE("Testing Assignment Operator", "[operator]") {
  SECTION("Deep Copy Assignment Empty") {
    std::vector<char> values;
    DoublyLinkedList<char> list(values);
    DoublyLinkedList<char> copy = list;
    REQUIRE(copy.getHead() == nullptr);
    REQUIRE(copy.getTail() == nullptr);
  }
  SECTION("Deep Copy Assignment Base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    DoublyLinkedList<char> copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
    copy.getHead()->data = 2;
    copy.getTail()->data = 3;
    REQUIRE(copy.getHead()->data != list.getHead()->data);
    REQUIRE(copy.getTail()->data != list.getTail()->data);
  }
  SECTION("Deep Copy Assignment Edge 1") {
    std::vector<char> values;
    values.push_back('1');
    DoublyLinkedList<char> list(values);
    DoublyLinkedList<char> copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
  SECTION("Deep Copy Assignment Edge 2") {
    std::vector<char> values;
    values.push_back('1');
    DoublyLinkedList<char> list(values);
    values.push_back('2');
    DoublyLinkedList<char> copy(values);
    copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
}

TEST_CASE("push_back", "[push_back]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'a');
    REQUIRE(list.size() == 1);
  }
  SECTION("base") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');

    REQUIRE(list.size() == 4);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'd');
  }
}

TEST_CASE("push_front", "[push_front]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    list.push_front('a');
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'a');
    REQUIRE(list.size() == 1);
  }
  SECTION("base") {
    DoublyLinkedList<char> list;
    list.push_front('a');
    list.push_front('b');
    list.push_front('c');
    list.push_front('d');

    REQUIRE(list.size() == 4);
    REQUIRE(list.getHead()->data == 'd');
    REQUIRE(list.getTail()->data == 'a');
  }
}

TEST_CASE("pop_back", "[push_back]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    REQUIRE_THROWS_AS(list.pop_back(), std::runtime_error);
  }
  SECTION("base") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();

    REQUIRE(list.size() == 3);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'c');
  }
  SECTION("multiple") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();
    list.pop_back();

    REQUIRE(list.size() == 2);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'b');
  }
  SECTION("Edge 1") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();
    list.pop_back();
    list.pop_back();

    REQUIRE(list.size() == 1);
    REQUIRE(list.getHead() == list.getTail());
  }
  SECTION("Edge 2") {
    DoublyLinkedList<char> list;
    list.push_back('a');
    list.pop_back();
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("insert_at", "[insert]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    list.insert_at(0, 'x');
    REQUIRE(list.getHead()->data == 'x');
    REQUIRE(list.getTail()->data == 'x');
  }
  SECTION("base") {
    DoublyLinkedList<char> list;
    list.insert_at(0, 'x');
    list.insert_at(1, 'y');
    REQUIRE(list.getHead()->data == 'x');
    REQUIRE(list.getTail()->data == 'y');
    REQUIRE(list.size() == 2);
  }
  SECTION("base 2") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    list.insert_at(1, 'x');
    REQUIRE(list.size() == 5);
    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.getHead()->next->data == 'x');
  }
}

TEST_CASE("erase_at", "[erase]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    REQUIRE_THROWS_AS(list.erase_at(0), std::runtime_error);
  }
  SECTION("base") {
    DoublyLinkedList<char> list;
    list.insert_at(0, 'x');
    list.erase_at(0);
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
    REQUIRE(list.size() == 0);
  }
  SECTION("base 2") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    list.erase_at(1);
    REQUIRE(list.size() == 3);
    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.getHead()->next->data == '3');
  }
}

TEST_CASE("clear", "[clear]") {
  SECTION("Empty") {
    DoublyLinkedList<char> list;
    list.clear();
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
  }
  SECTION("base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList<char> list(values);
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
  }
}

TEST_CASE("String", "[str]") {
  SECTION("base") {
    DNAstrand copy("ATATG");
    REQUIRE(copy.Str() == "ATATG");
  }
}

TEST_CASE("Splice", "[splice]") {
  SECTION("front base") {
    DNAstrand list("A");
    DNAstrand better("ACG");
    DNAstrand copy("ATATG");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "ACGTACGTG");
  }
  SECTION("front edge 1") {
    DNAstrand list("A");
    DNAstrand better("ACG");
    DNAstrand copy("A");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "ACG");
  }
  SECTION("front edge 2") {
    DNAstrand list("A");
    DNAstrand better("C");
    DNAstrand copy("A");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "C");
  }
  SECTION("front edge 3") {
    DNAstrand list("AG");
    DNAstrand better("C");
    DNAstrand copy("AG");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "C");
  }
  SECTION("front edge 4") {
    DNAstrand list("AG");
    DNAstrand better("CAA");
    DNAstrand copy("AG");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "CAA");
  }
  SECTION("back base") {
    DNAstrand list("C");
    DNAstrand better("A");
    DNAstrand copy("AGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "AGTAA");
  }
  SECTION("back edge 1") {
    DNAstrand list("AC");
    DNAstrand better("G");
    DNAstrand copy("AGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "AGTG");
  }
  SECTION("back edge 2") {
    DNAstrand list("AC");
    DNAstrand better("GTA");
    DNAstrand copy("AGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "AGTGTA");
  }

  SECTION("middle base") {
    DNAstrand list("GT");
    DNAstrand better("AC");
    DNAstrand copy("ACGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "ACACAC");
  }
  SECTION("Combined 1") {
    DNAstrand list("GT");
    DNAstrand better("AC");
    DNAstrand copy("ACGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "ACACAC");
    DNAstrand other("C");
    DNAstrand p2("G");
    copy.SpliceIn(other, p2);
    REQUIRE(copy.Str() == "AGAGAG");
  }

  SECTION("Combined 2") {
    DNAstrand list("AC");
    DNAstrand better("TTG");
    DNAstrand copy("ACGTAC");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "TTGGTTTG");
    DNAstrand other("GG");
    DNAstrand p2("AC");
    copy.SpliceIn(other, p2);
    REQUIRE(copy.Str() == "TTACTTTG");
  }

  SECTION("Combined Edge") {
    DNAstrand list("A");
    DNAstrand better("T");
    DNAstrand copy("AAAAAA");
    copy.SpliceIn(list, better);
    REQUIRE(copy.Str() == "TTTTTT");
    DNAstrand other("TT");
    DNAstrand p2("C");
    copy.SpliceIn(other, p2);
    REQUIRE(copy.Str() == "CCC");
  }
  SECTION("Throw 2") {
    DNAstrand list("A");
    DNAstrand better("T");
    DNAstrand copy("AAAAAA");
    REQUIRE_THROWS_AS(copy.SpliceIn(copy, better), std::runtime_error);
  }
  SECTION("Throw 2") {
    DNAstrand list("A");
    DNAstrand better("T");
    DNAstrand copy("AAAAAA");
    REQUIRE_THROWS_AS(copy.SpliceIn(list, copy), std::runtime_error);
  }
  SECTION("Throw 3") {
    DNAstrand list("A");
    DNAstrand better("T");
    DNAstrand copy("AAAAAA");
    REQUIRE_THROWS_AS(copy.SpliceIn(better, better), std::runtime_error);
  }
}