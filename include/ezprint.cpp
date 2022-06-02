#ifndef ezprint_cpp
#define ezprint_cpp

#include <iostream>
#include <string>

/*
  Purpose: this module contains functions to speed up the printing of strings and integers/doubles/etc. if labeled, done so by strings.
*/

namespace ezp {

template <typename T> void print_item(T& item) {
  std::cout << item << '\n';
}

template <typename T>
void print_labeled_item(std::string label, T item) {
  std::cout << label << item << '\n';
}

}

#endif /* ezprint_cpp */