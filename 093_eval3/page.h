#ifndef __PAGE_H__
#define __PAGE_H__
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "cyoa.h"
class Page {
  class Choice {
   public:
    size_t dest;
    std::string contain;
    bool hasCond;
    std::string cond;
    long int val;

    Choice(size_t toP, const std::string & c) :
        dest(toP), contain(c), hasCond(false), cond(std::string()), val(0) {}
    Choice(size_t toP, const std::string & c, const std::string & prop, long int v) :
        dest(toP), contain(c), hasCond(true), cond(prop), val(v) {}
    ~Choice() {}
  };
  size_t pageInd;
  std::vector<Choice> choices;
  std::string fileName;
  bool lose;
  bool win;

 public:
  Page(size_t num, const std::string & fName, const std::string & type) :
      pageInd(num),
      choices(std::vector<Choice>()),
      fileName(fName),
      lose(false),
      win(false) {
    if (type == "W") {
      win = true;
    }
    else if (type == "L") {
      lose = true;
    }
    else if (type != "N") {
      throw std::invalid_argument("Invalid page type: not N, W, or L!");
    }
  }
  bool isWin() const { return win; }
  bool isLose() const { return lose; }
  void addChoice(size_t destPage, std::string contain) {
    Choice newChoice(destPage, contain);
    choices.push_back(newChoice);
  }
  const char * getFile() const { return fileName.c_str(); }
  size_t numChoice() const { return choices.size(); }
  const std::string & getChoice(size_t ind) const { return choices[ind].contain; }
  size_t getChoiceDest(size_t ind) const { return choices[ind].dest; }
  ~Page() {}
};
std::ostream & operator<<(std::ostream & s, const Page & rhs) {
  std::ifstream pFile(rhs.getFile());
  std::string line;
  if (!pFile.is_open()) {
    throw std::invalid_argument("Cannot open the page file when printing!");
  }
  while (std::getline(pFile, line)) {
    s << line << "\n";
  }
  s << "\n";
  if (rhs.isWin()) {
    s << "Congratulations! You have won. Hooray!\n";
  }
  else if (rhs.isLose()) {
    s << "Sorry, you have lost. Better luck next time!\n";
  }
  else {
    s << "What would you like to do?\n";
    s << "\n";
    for (size_t i = 0; i < rhs.numChoice(); i++) {
      s << " " << i + 1 << ". " << rhs.getChoice(i) << "\n";
    }
  }
  return s;
}
#endif
