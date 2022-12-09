#ifndef __PAGE_H__
#define __PAGE_H__
#include <fstream>
#include <utility>

#include "cyoa.h"
/*
The Page class, saved in the Story class, stores page-related content. 
It has multiple methods to add content and properties to the page.
It also contents some methods to show the status and contents of this page and its choices. 
*/
class Page {
  std::vector<Choice> choices;  // a list of choices in this page
  std::string fileName;         // the file with the content to display
  bool lose;                    // whether this page is a LOSE page
  bool win;                     // whether this page is a WIN page
  std::set<propPair> newProps;  // the property pairs for step 4

 public:
  // The methods to add content and properties:
  //The page constructor
  Page(const std::string & fName, const std::string & type) :
      choices(std::vector<Choice>()),  // initialize the choice list as empty
      fileName(fName),
      lose(false),
      win(false),
      newProps(std::set<propPair>()) {
    // Set win and lose according to the input type (W, L, N)
    if (type == "W") {
      win = true;
    }
    else if (type == "L") {
      lose = true;
    }
    else if (type != "N") {  // indicate invalide type name
      throw std::invalid_argument("Invalid page type: not N, W, or L!");
    }
  }
  // Add a normal chocie to the page
  void addChoice(size_t destPage, std::string contain) {
    Choice newChoice(destPage, contain);
    choices.push_back(newChoice);
  }
  // Add a fancy chocie to the page
  void addChoice(size_t destPage, std::string contain, std::string cond, long int value) {
    Choice newChoice(destPage, contain, cond, value);
    choices.push_back(newChoice);
  }
  // Set the chocie satisfied status
  void setChoiceStatus(size_t ind, bool s) { choices[ind].satisfied = s; }

  // Add a property pair to the page's property list
  void addProp(const std::string & prop, const long int & value) {
    findAddProp(newProps, propPair(prop, value));
  }

  // Methods to show the status and properties of the page
  // e.g. WIN/LOSE page, filename, number of chocies...
  bool isWin() const { return win; }
  bool isLose() const { return lose; }
  const char * getFile() const { return fileName.c_str(); }
  size_t numChoice() const { return choices.size(); }
  // Get choice content for printing
  const std::string & getChoice(size_t ind) const { return choices[ind].content; }
  // Get choice destination for next page
  size_t getChoiceDest(size_t ind) const { return choices[ind].dest; }
  // Check the choice is a normal (false) or fancy (true) type
  bool choiceHasCond(size_t ind) const { return choices[ind].hasCond; }
  // Get the required condition of the corresponding choice
  propPair getChoiceCond(size_t ind) const {
    propPair condPair(choices[ind].cond, choices[ind].val);
    return condPair;
  }
  // Check if the corresponding choice's condition is satisfied (able to display)
  bool getChoiceSat(size_t ind) const { return choices[ind].satisfied; }
  // Get the property pairs in this page to update the properties in story
  const std::set<propPair> & getProp() const { return newProps; }
};

// Overloading the << operator to display the page
std::ostream & operator<<(std::ostream & s, const Page & rhs) {
  std::ifstream pFile(rhs.getFile());  //open the file with page content
  std::string line;
  if (!pFile.is_open()) {  // if cannot open -> indicate failure
    throw std::invalid_argument("Cannot open the page file when printing!");
  }
  while (std::getline(pFile, line)) {
    s << line << "\n";  // show the file content
  }
  s << "\n";
  if (rhs.isWin()) {
    s << "Congratulations! You have won. Hooray!\n";
  }
  else if (rhs.isLose()) {
    s << "Sorry, you have lost. Better luck next time!\n";
  }
  else {  // show choices
    s << "What would you like to do?\n \n";
    for (size_t i = 0; i < rhs.numChoice(); i++) {
      if (rhs.getChoiceSat(i)) {  // if the choice's condition is satisfied
        s << " " << i + 1 << ". " << rhs.getChoice(i) << "\n";
      }
      else {
        s << " " << i + 1 << ". <UNAVAILABLE>\n";
      }
    }
  }
  return s;
}
#endif
