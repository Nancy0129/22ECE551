#ifndef __STORY_H__
#define __STORY_H__
#include <fstream>

#include "cyoa.h"
#include "page.h"
class Story {
 protected:
  size_t pageNum;
  std::string directory;

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
    Page newP(number, fName, line.substr(findAt + 1, findC - (findAt + 1)));
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
    pages[fromPage].addChoice(toPage, line.substr(findC2 + 1));
  }

 public:
  std::vector<Page> pages;
  Story(std::string dir) : pageNum(0), directory(dir), pages(std::vector<Page>()) {
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
