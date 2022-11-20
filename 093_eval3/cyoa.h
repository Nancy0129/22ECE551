#ifndef __CYOA_H__
#define __CYOA_H__
#include <cstdlib>
#include <stdexcept>
#include <string>
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
#endif
