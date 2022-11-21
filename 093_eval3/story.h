#ifndef __STORY_H__
#define __STORY_H__
#include <fstream>
#include <set>
#include <stack>

#include "cyoa.h"
#include "page.h"
class Story {
  size_t pageNum;
  std::string directory;
  bool hasWin, hasLose;
  std::set<size_t> allDestPage;
  std::set<std::pair<std::string, long int> > properties;
  void addPage(const std::string & line) {
    size_t findAt = line.find("@");
    size_t findC = line.find(":", findAt);
    if (findC == std::string::npos) {
      throw std::invalid_argument("Cannot convert the input line to a page!");
    }
    size_t number = getValidNum(line.substr(0, findAt).c_str());
    if (number != pageNum) {
      throw std::invalid_argument("Page declarations are in order!");
    }
    std::string fName = directory + "/" + line.substr(findC + 1);
    std::ifstream tryOpen(fName.c_str());
    if (!tryOpen.is_open()) {
      throw std::invalid_argument("Invalid page file name!");
    }
    std::string type = line.substr(findAt + 1, findC - (findAt + 1));
    if (type == "W") {
      hasWin = true;
    }
    if (type == "L") {
      hasLose = true;
    }
    Page newP(number, fName, type);
    pages.push_back(newP);
    pageNum++;
  }
  void addChoice(std::string & line, bool fancy = false) {
    size_t findC1 = line.find(":");
    size_t findC2 = line.find(":", findC1 + 1);
    size_t fromPage;
    size_t findBl = 0;
    size_t findE = 0;
    size_t findBr = 0;
    long int propV;
    if (fancy) {
      findBl = line.find("[");
      findE = line.find("=");
      findBr = line.find("]");
      checkType4(findC1, findC2, findBl, findE, findBr);
      fromPage = getValidNum(line.substr(0, findBl).c_str());
      propV = getValidLong(line.substr(findE + 1, findBr - (findE + 1)).c_str());
    }

    else {
      fromPage = getValidNum(line.substr(0, findC1).c_str());
    }
    size_t toPage = getValidNum(line.substr(findC1 + 1, findC2 - (findC1 + 1)).c_str());
    if (fromPage >= pages.size()) {
      throw std::invalid_argument("Add choices before a page declaration!");
    }
    if (pages[fromPage].isLose() || pages[fromPage].isWin()) {
      throw std::invalid_argument("Add choices to a Win/Lose page!");
    }
    allDestPage.insert(toPage);
    if (fancy) {
      pages[fromPage].addChoice(toPage,
                                line.substr(findC2 + 1),
                                line.substr(findBl + 1, findE - (findBl + 1)),
                                propV);
    }
    else {
      pages[fromPage].addChoice(toPage, line.substr(findC2 + 1));
    }
  }
  void addProperty(std::string & line) {
    size_t findD = line.find("$");
    size_t findE = line.find("=", findD);
    if (findE == std::string::npos) {
      throw std::invalid_argument("Invalid line format for adding properties!");
    }
    size_t atPage = getValidNum(line.substr(0, findD).c_str());
    if (atPage >= pages.size()) {
      throw std::invalid_argument("Add properties before a page declaration!");
    }
    long int value = getValidNum(line.substr(findE + 1).c_str());
    pages[atPage].addProp(line.substr(findD + 1, findE - (findD + 1)), value);
    properties.insert(
        std::pair<std::string, long int>(line.substr(findD + 1, findE - (findD + 1)), 0));
  }

  void checkStory() {
    if (!hasWin || !hasLose) {
      throw std::range_error("There is no WIN / LOSE page!");
    }
    std::set<size_t> set_copy(allDestPage);
    std::set<size_t>::iterator pos;
    pos = set_copy.find(0);
    if (pos != set_copy.end()) {
      set_copy.erase(pos);
    }
    for (size_t i = 1; i < pages.size(); i++) {
      pos = set_copy.find(i);
      if (pos == set_copy.end()) {
        throw std::range_error("A page has no reference!");
      }
      set_copy.erase(i);
    }
    if (set_copy.size() > 0) {
      throw std::range_error("A page reference is not valid!");
    }
  }
  size_t getNextPage(size_t curr, const std::string & userIn) {
    size_t userC = getValidNum(userIn.c_str());
    if (userC > pages[curr].numChoice() || userC == 0) {
      throw std::invalid_argument("Choice index out of range!");
    }

    if (!pages[curr].getChoiceSat(userC - 1)) {
      throw std::invalid_argument("Unvaliable Option!");
    }
    return pages[curr].getChoiceDest(userC - 1);
  }
  void updateProp(const size_t & currPage) {
    std::set<std::pair<std::string, long int> > newProps = pages[currPage].getProp();
    std::set<std::pair<std::string, long int> >::iterator it;
    for (it = newProps.begin(); it != newProps.end(); it++) {
      // std::cout << it->first << " " << it->second << "\n";
      findAddProp(properties, *it);
    }
    for (size_t i = 0; i < pages[currPage].numChoice(); i++) {
      if (pages[currPage].choiceHasCond(i)) {
        std::pair<std::string, long int> cond = pages[currPage].getChoiceCond(i);
        bool sat = (properties.find(cond) != properties.end());
        pages[currPage].setChoiceStatus(i, sat);
      }
    }
  }

 public:
  std::vector<Page> pages;
  Story(std::string dir) :
      pageNum(0),
      directory(dir),
      hasWin(false),
      hasLose(false),
      allDestPage(std::set<size_t>()),
      properties(std::set<std::pair<std::string, long int> >()),
      pages(std::vector<Page>()) {
    std::string storyDir = directory + "/story.txt";
    std::ifstream sFile(storyDir.c_str());
    std::string line;
    if (!sFile.is_open()) {
      throw std::invalid_argument("Cannot open the story.txt file!");
    }
    while (std::getline(sFile, line)) {
      if (!line.empty()) {
        int lineType = getLineType(line);
        if (lineType == 1) {
          addPage(line);
        }
        else if (lineType == 2) {
          addChoice(line);
        }
        else if (lineType == 3) {
          addProperty(line);
        }
        else if (lineType == 4) {
          addChoice(line, true);
        }
      }
    }
  }

  void play() {
    checkStory();
    std::string userChoice;
    size_t currPos = 0;
    std::cout << pages[currPos];
    while (std::getline(std::cin, userChoice)) {
      try {
        currPos = getNextPage(currPos, userChoice);
        updateProp(currPos);
        std::cout << pages[currPos];
        if (pages[currPos].isWin() || pages[currPos].isLose()) {
          return;
        }
      }
      catch (std::invalid_argument & ex) {
        std::cout << "That is not a valid choice, please try again\n";
      }
    }
  }
  void showWinPath() {
    checkStory();
    std::stack<Path> todo;
    todo.push(Path(0));
    bool noWin = true;
    while (!todo.empty()) {
      Path currPath = todo.top();
      todo.pop();
      size_t currNode = currPath.last();
      if (pages[currNode].isWin()) {
        noWin = false;
        std::cout << currPath;
      }
      else {
        for (size_t i = 0; i < pages[currNode].numChoice(); i++) {
          size_t dest = pages[currNode].getChoiceDest(i);
          if (!currPath.find(dest)) {
            todo.push(currPath.addNode(dest, i + 1));
          }
        }
      }
    }
    if (noWin) {
      std::cout << "This story is unwinnable !\n";
    }
  }
  ~Story() {}
};

std::ostream & operator<<(std::ostream & s, const Story & rhs) {
  for (size_t i = 0; i < rhs.pages.size(); i++) {
    s << "Page " << i << "\n";
    s << "==========\n";
    s << rhs.pages[i];
  }
  return s;
}

#endif
