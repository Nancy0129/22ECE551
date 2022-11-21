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
  void addNormalChoice(std::string & line) {
    size_t findC1 = line.find(":");
    size_t findC2 = line.find(":", findC1 + 1);
    size_t fromPage = getValidNum(line.substr(0, findC1).c_str());
    size_t toPage = getValidNum(line.substr(findC1 + 1, findC2 - (findC1 + 1)).c_str());
    if (fromPage >= pages.size()) {
      throw std::invalid_argument("Add choices before a page declaration!");
    }
    if (pages[fromPage].isLose() || pages[fromPage].isWin()) {
      throw std::invalid_argument("Add choices to a Win/Lose page!");
    }
    allDestPage.insert(toPage);
    pages[fromPage].addChoice(toPage, line.substr(findC2 + 1));
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
    return pages[curr].getChoiceDest(userC - 1);
  }

 public:
  std::vector<Page> pages;
  Story(std::string dir) :
      pageNum(0),
      directory(dir),
      hasWin(false),
      hasLose(false),
      allDestPage(std::set<size_t>()),
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
          addNormalChoice(line);
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
