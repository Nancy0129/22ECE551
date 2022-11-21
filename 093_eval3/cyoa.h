#ifndef __CYOA_H__
#define __CYOA_H__
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>
int getLineType(const std::string & line) {
  size_t findAt = line.find("@");
  if (findAt != std::string::npos) {
    return 1;
  }
  size_t findC1 = line.find(":");
  if (findC1 != std::string::npos) {
    size_t findB = line.find("[");
    if (findB != std::string::npos && findB < findC1) {
      return 4;
    }
    size_t findC2 = line.find(":", findC1);
    if (findC2 != std::string::npos) {
      return 2;
    }
    size_t find_e = line.find("=", findC1);
    if (find_e != std::string::npos) {
      return 3;
    }
  }
  throw std::invalid_argument("There is a invalid line with wrong format in the file!");
}
size_t getValidNum(const char * word) {
  char * endtr;  // store the non-number characters
  long number = strtoll(word, &endtr, 10);
  if (number >= 0) {                   // It is non-negative  number
    if (endtr[0] == '\0') {            //The string contains only numbers
      return strtoul(word, NULL, 10);  // return the unsigned value
    }
  }
  // indicates it is not a legal number
  throw std::invalid_argument("Cannot convert to a valid number!");
}
class Path {
  std::vector<size_t> paths;
  std::vector<size_t> options;
  std::set<size_t> passed;

 public:
  Path(size_t start) :
      paths(std::vector<size_t>()),
      options(std::vector<size_t>()),
      passed(std::set<size_t>()) {
    paths.push_back(start);
    passed.insert(start);
  }
  Path(const Path & rhs) : paths(rhs.paths), options(rhs.options), passed(rhs.passed) {}
  Path & operator=(const Path & rhs) {
    if (this != &rhs) {
      paths = rhs.paths;
      options = rhs.options;
      passed = rhs.passed;
    }
    return *this;
  }
  Path addNode(size_t p, size_t o) const {
    Path pathCopy(*this);
    pathCopy.paths.push_back(p);
    pathCopy.options.push_back(o);
    pathCopy.passed.insert(p);
    return pathCopy;
  }
  bool find(const size_t & key) {
    std::set<size_t>::iterator it = passed.find(key);
    return it != passed.end();
  }
  size_t last() { return paths[paths.size() - 1]; }
  friend std::ostream & operator<<(std::ostream & stream, const Path & rhs);
};
std::ostream & operator<<(std::ostream & stream, const Path & rhs) {
  for (size_t i = 0; i < rhs.options.size(); i++) {
    stream << rhs.paths[i];
    stream << "(" << rhs.options[i] << "),";
  }
  stream << rhs.paths[rhs.options.size()];
  stream << "(win)\n";
  return stream;
}
#endif
