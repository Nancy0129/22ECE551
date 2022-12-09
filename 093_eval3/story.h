#ifndef __STORY_H__
#define __STORY_H__
#include <stack>

#include "page.h"

class Story {
  size_t pageNum;                 // the number of pages in the story
  std::string directory;          // the directory that contents the story
  bool hasWin, hasLose;           // whether the story has at least a WIN/LOSE page
  std::set<size_t> allDestPage;   // store all destination pages
  std::set<propPair> properties;  // all properties shown in the whole story
  std::vector<Page> pages;        // save the pages

  // Add a page to the story according to "number@type:filename"
  void addPage(const std::string & line) {
    //make sure it has "@" and ":"
    size_t findAt = line.find("@");
    size_t findC = line.find(":", findAt);
    if (findC == std::string::npos) {
      throw std::invalid_argument("Cannot convert the input line to a page!");
    }
    size_t number = getValidNum(line.substr(0, findAt).c_str());
    if (number != pageNum) {  // make sure page declarations appear in order
      throw std::invalid_argument("Page declarations are not in order!");
    }
    std::string fName = directory + "/" + line.substr(findC + 1);
    std::ifstream tryOpen(fName.c_str());
    if (!tryOpen.is_open()) {  // check the existence of the page file
      throw std::invalid_argument("Invalid page file name!");
    }
    std::string type = line.substr(findAt + 1, findC - (findAt + 1));
    if (type == "W") {
      hasWin = true;  // indicate that the story has at least a WIN page
    }
    if (type == "L") {  // indicate that the story has at least a LOSE page
      hasLose = true;
    }
    Page newP(fName, type);  // create a new page object
    pages.push_back(newP);
    pageNum++;  // update the number number
  }

  // Add a choice to a page, which has 2 possible formats:
  // - Normal: "pagenum:destpage:text" (fancy = false)
  // - Fancy: "pagenum[var=value]:dest:text" (fancy = true)
  void addChoice(std::string & line, bool fancy = false) {
    size_t findC1 = line.find(":");
    size_t findC2 = line.find(":", findC1 + 1);
    size_t findBl = 0;  // [ (fancy)
    size_t findE = 0;   // = (fancy)
    size_t findBr = 0;  // ] (fancy)
    size_t fromPage;    // which page to insert the choice
    long int propV;     // property val for fancy
    if (fancy) {
      findBl = line.find("[");
      findE = line.find("=");
      findBr = line.find("]");
      checkType4(findC1, findC2, findBl, findE, findBr);  // check the format
      fromPage = getValidNum(line.substr(0, findBl).c_str());
      propV = getValidLong(line.substr(findE + 1, findBr - (findE + 1)).c_str());
    }
    else {
      fromPage = getValidNum(line.substr(0, findC1).c_str());
    }
    size_t toPage = getValidNum(line.substr(findC1 + 1, findC2 - (findC1 + 1)).c_str());
    if (fromPage >= pages.size()) {  // check if the page already exist
      throw std::invalid_argument("Add choices before a page declaration!");
    }
    if (pages[fromPage].isLose() || pages[fromPage].isWin()) {
      throw std::invalid_argument("Add choices to a Win/Lose page!");
    }
    if (fromPage != toPage) {      // if the page is reference by another page
      allDestPage.insert(toPage);  // add the destination to the list for later check
    }
    if (fancy) {  // create a fancy choice and add to the page
      pages[fromPage].addChoice(toPage,
                                line.substr(findC2 + 1),
                                line.substr(findBl + 1, findE - (findBl + 1)),
                                propV);
      // Set the property val to 0 in story's property pair set
      properties.insert(propPair(line.substr(findBl + 1, findE - (findBl + 1)), 0));
    }
    else {  // create a normal choice and add to the page
      pages[fromPage].addChoice(toPage, line.substr(findC2 + 1));
    }
  }

  // Add a property pair to the story according to "pagenum$var=value"
  void addProperty(std::string & line) {
    size_t findD = line.find("$");
    size_t findE = line.find("=", findD);
    if (findE == std::string::npos) {  //check if it has "="
      throw std::invalid_argument("Invalid line format for adding properties!");
    }
    size_t atPage = getValidNum(line.substr(0, findD).c_str());
    if (atPage >= pages.size()) {  // check if the page already exists
      throw std::invalid_argument("Add properties before a page declaration!");
    }
    long int value = getValidNum(line.substr(findE + 1).c_str());  //get val
    pages[atPage].addProp(line.substr(findD + 1, findE - (findD + 1)), value);
    // Set the property val to 0 in story's property pair set
    properties.insert(propPair(line.substr(findD + 1, findE - (findD + 1)), 0));
  }

  // Verify the conditions are met for the story as a whole
  void checkStory() {
    if (!hasWin || !hasLose) {  // should have WIN and LOSE pages
      throw std::range_error("There is no WIN / LOSE page!");
    }
    // Check if every page is referenced by another page
    std::set<size_t> set_copy(allDestPage);
    std::set<size_t>::iterator pos;  // to find the page num
    pos = set_copy.find(0);
    if (pos != set_copy.end()) {
      set_copy.erase(pos);
    }
    for (size_t i = 1; i < pages.size(); i++) {
      pos = set_copy.find(i);       // if i in referenced
      if (pos == set_copy.end()) {  // if not, indicate the error
        throw std::range_error("A page has no reference!");
      }
      set_copy.erase(i);
    }
    // Check if every referenced page exists -> the set is emptied
    if (set_copy.size() > 0) {  // if not, indicate the error
      throw std::range_error("A page reference is not valid!");
    }
  }

  // Get the destination page from the corresponding choice
  // The input is current page (curr) and user's input (userIn)
  size_t getNextPage(size_t curr, const std::string & userIn) {
    // Check whether user choice a valid choice
    size_t userC = getValidNum(userIn.c_str());
    if (userC > pages[curr].numChoice() || userC == 0) {
      // if not , throw the invalid_argument error to indicate that
      throw std::invalid_argument("Choice index out of range!");
    }
    // Check whether the condition of the choice is satisfied
    if (!pages[curr].getChoiceSat(userC - 1)) {
      // if not , throw the range_error to indicate that
      throw std::range_error("Unvaliable Option!");
    }
    // return the valid destination page
    return pages[curr].getChoiceDest(userC - 1);
  }

  // Update the property pairs set of the story when arrive a new page
  void updateProp(const size_t & currPage) {
    // Get all new properties from the current page
    std::set<propPair> newProps = pages[currPage].getProp();
    std::set<propPair>::iterator it;
    for (it = newProps.begin(); it != newProps.end(); it++) {
      findAddProp(properties, *it);  // update the properties
    }
    // Update the choices' satisfied status in current page
    for (size_t i = 0; i < pages[currPage].numChoice(); i++) {
      if (pages[currPage].choiceHasCond(i)) {              // find the fancy choice
        propPair cond = pages[currPage].getChoiceCond(i);  // get its condition
        // See if it is satisfied
        //  (i.e. the desired pair is in story's property pair set)
        bool sat = (properties.find(cond) != properties.end());
        pages[currPage].setChoiceStatus(i, sat);  // update the status
      }
    }
  }

 public:
  // The Story Constructor
  // set each field to the default values first  and generate the story
  Story(std::string dir) :
      pageNum(0),
      directory(dir),
      hasWin(false),
      hasLose(false),
      allDestPage(std::set<size_t>()),
      properties(std::set<std::pair<std::string, long int> >()),
      pages(std::vector<Page>()) {
    // Open the story file and read the contents in it
    std::string storyDir = directory + "/story.txt";
    std::ifstream sFile(storyDir.c_str());
    std::string line;
    if (!sFile.is_open()) {
      throw std::invalid_argument("Cannot open the story.txt file!");
    }
    while (std::getline(sFile, line)) {
      // Ignore the blank lines (there are content other than " ","\n"," \t")
      if (line.find_first_not_of(" \n\t") != std::string::npos) {
        // Check format and get corresponding types (see cyoa.h)
        int lineType = getLineType(line);
        // Send the line to corresponding function to handle
        if (lineType == 1) {
          addPage(line);
        }
        else if (lineType == 2) {
          addChoice(line);  // to noraml choice
        }
        else if (lineType == 3) {
          addProperty(line);
        }
        else if (lineType == 4) {
          addChoice(line, true);  // to fancy chocie
        }
      }
    }
  }

  // For step 2 and 4: let user play the game
  void play() {
    checkStory();                 // check sotry format beforehand
    std::string userChoice;       // user's input choice
    size_t currPos = 0;           // current page number
    std::cout << pages[currPos];  // print current page
    while (std::getline(std::cin, userChoice)) {
      try {
        // Update page number
        currPos = getNextPage(currPos, userChoice);
        // Update the property pair set and the status of chocies
        updateProp(currPos);
        std::cout << pages[currPos];  // display the page
        if (pages[currPos].isWin() || pages[currPos].isLose()) {
          return;  // if win/lose -> end the game
        }
      }  // catch the exception for invalid choice and let user choose again
      catch (std::invalid_argument & ex) {  // indicate the input is not valid
        std::cout << "That is not a valid choice, please try again\n";
      }
      catch (std::range_error & ex) {  // indicate the choice is not available
        std::cout << "That choice is not available at this time, please try again\n";
      }
    }
    // Get the end of input but the story is not end -> error
    throw std::invalid_argument("The game is not end!\n");
  }

  // Use DFS to find all winning path
  void showWinPath() {
    checkStory();  // check the sotry format beforehand
    std::stack<Path> todo;
    todo.push(Path(0));
    bool noWin = true;  // whether the game is winnable
    while (!todo.empty()) {
      Path currPath = todo.top();  // get the top one in todo
      todo.pop();
      size_t currNode = currPath.last();  // get the last node
      if (pages[currNode].isWin()) {
        noWin = false;          // indicate the game is winnable
        std::cout << currPath;  // show the winning path
      }
      else {
        for (size_t i = 0; i < pages[currNode].numChoice(); i++) {
          size_t dest = pages[currNode].getChoiceDest(i);
          if (!currPath.find(dest)) {  // check if the destination has visited
            todo.push(currPath.addNode(dest, i + 1));
          }
        }
      }
    }
    if (noWin) {  // indiate there is no winning path
      std::cout << "This story is unwinnable !\n";
    }
  }
  friend std::ostream & operator<<(std::ostream & s, const Story & rhs);
};

// Overloading the << operator to display the whole story for step 1
std::ostream & operator<<(std::ostream & s, const Story & rhs) {
  for (size_t i = 0; i < rhs.pages.size(); i++) {
    s << "Page " << i << "\n";
    s << "==========\n";
    s << rhs.pages[i];
  }
  return s;
}

#endif
