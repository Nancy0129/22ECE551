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
    std::string content;
    bool hasCond;
    bool satisfied;
    std::string cond;
    long int val;

    Choice(size_t toP, const std::string & c) :
        dest(toP),
        content(c),
        hasCond(false),
        satisfied(true),
        cond(std::string()),
        val(0) {}
    Choice(size_t toP, const std::string & c, const std::string & prop, long int v) :
        dest(toP), content(c), hasCond(true), satisfied(false), cond(prop), val(v) {}
    ~Choice() {}
  };
  size_t pageInd;
  std::vector<Choice> choices;
  std::string fileName;
  bool lose;
  bool win;
  std::set<std::pair<std::string, long int> > newProps;

 public:
  Page(size_t num, const std::string & fName, const std::string & type) :
      pageInd(num),
      choices(std::vector<Choice>()),
      fileName(fName),
      lose(false),
      win(false),
      newProps(std::set<std::pair<std::string, long int> >()) {
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
  void addChoice(size_t destPage, std::string contain, std::string cond, long int value) {
    Choice newChoice(destPage, contain, cond, value);
    choices.push_back(newChoice);
  }

  const char * getFile() const { return fileName.c_str(); }
  size_t numChoice() const { return choices.size(); }

  const std::string & getChoice(size_t ind) const { return choices[ind].content; }
  size_t getChoiceDest(size_t ind) const { return choices[ind].dest; }
  bool choiceHasCond(size_t ind) const { return choices[ind].hasCond; }
  std::pair<std::string, long int> getChoiceCond(size_t ind) const {
    std::pair<std::string, long int> condPair(choices[ind].cond, choices[ind].val);
    return condPair;
  }
  void setChoiceStatus(size_t ind, bool s) { choices[ind].satisfied = s; }
  bool getChoiceSat(size_t ind) const { return choices[ind].satisfied; }
  void addProp(const std::string & prop, const long int & value) {
    findAddProp(newProps, std::pair<std::string, long int>(prop, value));
  }
  const std::set<std::pair<std::string, long int> > & getProp() { return newProps; }
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
      if (rhs.getChoiceSat(i)) {
        s << i + 1 << "." << rhs.getChoice(i) << "\n";
        // s << " " << i + 1 << ". " << rhs.getChoice(i) << "\n";
      }
      else {
        //s << " " << i + 1 << ". <UNAVAILABLE>\n";
        s << i + 1 << ".<UNAVAILABLE>\n";
      }
    }
  }
  return s;
}
#endif