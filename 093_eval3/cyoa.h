#ifndef __CYOA_H__
#define __CYOA_H__
#include <cstdlib>
#include <iostream>
#include <set>
#include <stdexcept>
#include <string>
#include <vector>

// Property pair to store "val" and "value" for step 4
typedef std::pair<std::string, long int> propPair;

/*
The Choice class to store choice-related content(saved in the Page class).
There are two types of choices:
 - The normal choice that only has basic choice contents
 - The fancy choice (for step 4) that has additional condition information
*/
class Choice {
 public:
  size_t dest;          // the destination page
  std::string content;  // the content to display
  bool hasCond;         // indicates whether the choice object has condition
  bool satisfied;       //indicates whether the condition (if any) has been satisfied
  std::string cond;     // the variable name in the condition
  long int val;         // the desired variable value in the condition

  // Initialize a normal choice object
  Choice(size_t toP, const std::string & c) :
      dest(toP),
      content(c),
      hasCond(false),       // no additional condition
      satisfied(true),      // no condition -> alreadly satisfied
      cond(std::string()),  // empty string
      val(0) {}

  // Initialize a fancy choice object
  Choice(size_t toP, const std::string & c, const std::string & prop, long int v) :
      dest(toP),
      content(c),
      hasCond(true),    //there is a condition
      satisfied(true),  // the condition is satisfied as default
      cond(prop),
      val(v) {}
};

/*
 A list of nodes for path search (in step 3)
 Used in the Story class
 */
class Path {
  std::vector<size_t> paths;    // page numbers in the path
  std::vector<size_t> options;  // option numbers in the path
  std::set<size_t> passed;      // the page that alreadly visited in the path

 public:
  // The path constructor with a start node
  Path(size_t start) :
      paths(std::vector<size_t>()),
      options(std::vector<size_t>()),
      passed(std::set<size_t>()) {
    paths.push_back(start);
    passed.insert(start);
  }
  // Copy constructor
  Path(const Path & rhs) : paths(rhs.paths), options(rhs.options), passed(rhs.passed) {}
  // Copy operator
  Path & operator=(const Path & rhs) {
    if (this != &rhs) {
      paths = rhs.paths;
      options = rhs.options;
      passed = rhs.passed;
    }
    return *this;
  }
  // Destructor for ROT
  ~Path() {}
  // Add a node in the path
  Path addNode(size_t p, size_t o) const {
    Path pathCopy(*this);
    pathCopy.paths.push_back(p);
    pathCopy.options.push_back(o);
    pathCopy.passed.insert(p);
    return pathCopy;
  }
  // Check if a page alreadly visited in this path
  bool find(const size_t & key) {
    std::set<size_t>::iterator it = passed.find(key);
    return it != passed.end();
  }
  // Get the last node in the path
  size_t last() { return paths[paths.size() - 1]; }
  friend std::ostream & operator<<(std::ostream & stream, const Path & rhs);
};

// Overloading << operator to display path
std::ostream & operator<<(std::ostream & stream, const Path & rhs) {
  for (size_t i = 0; i < rhs.options.size(); i++) {
    stream << rhs.paths[i];                   // show page
    stream << "(" << rhs.options[i] << "),";  //show option
  }
  stream << rhs.paths[rhs.options.size()];
  stream << "(win)\n";
  return stream;
}

/*
Get an input line from the story.txt file and get the types
  - type 1: number@type:filename
  - type 2: pagenum:destpage:text
  - type 3: pagenum$var=value
  - type 4: pagenum[var=value]:dest:text
*/
int getLineType(const std::string & line) {
  size_t firstSpe = line.find_first_of("@:[$");  //find the first special symbol
  if (firstSpe != std::string::npos) {
    size_t findC = line.find(":", firstSpe + 1);
    if (line[firstSpe] == '@' && findC != std::string::npos) {
      return 1;  // has @ before : ->type 1
    }
    if (line[firstSpe] == ':' && findC != std::string::npos) {
      return 2;  // has 2 : -> type 2
    }
    if (line[firstSpe] == '$') {
      return 3;  // has $ -> type 3
    }
    if (line[firstSpe] == '[' && findC != std::string::npos) {
      return 4;  // has [ before : -> type 4
    }
  }
  // Indicate the invalid format
  std::cerr << "At \"" << line << "\"\n";
  throw std::invalid_argument("The input line has invalid format!");
}

// Get the unsigned number for page and choice number
size_t getValidNum(const char * word) {
  if (word[0] != '\0') {
    char * endtr;                             // store the non-number characters
    long number = strtoll(word, &endtr, 10);  // convert to signed number first
    if (number >= 0) {                        // see if it is non-negative  number
      if (endtr[0] == '\0') {                 // see if the string contains only numbers
        return strtoul(word, NULL, 10);       // return the unsigned value
      }
    }
  }
  // indicates it is not a legal number
  throw std::invalid_argument("Cannot convert to a valid number!");
}

// Get the long int number for property value
long int getValidLong(const char * word) {
  if (word[0] != '\0') {
    char * endtr;
    long int number = strtol(word, &endtr, 10);
    if (endtr[0] == '\0') {  //The string contains only numbers
      return number;
    }
  }
  // indicates it is not a legal number
  throw std::invalid_argument("Cannot convert to a valid long int!");
}

// Change the property pairs in the set (pSet) to the propPair p
void findAddProp(std::set<propPair> & pSet, const propPair & p) {
  std::set<propPair>::iterator it;
  for (it = pSet.begin(); it != pSet.end(); it++) {
    if (it->first == p.first) {  // find the corresponding pair
      pSet.erase(it);            // delete the original pair
      break;
    }
  }
  pSet.insert(p);  // insert the new pair
}

/*
Check the format "pagenum[var=value]:dest:text"
c1,c2: the position of the first and second ":"
bl,br: the position of the "[" and "]"
e: the positon of "="
 */
void checkType4(size_t c1, size_t c2, size_t bl, size_t e, size_t br) {
  if (c2 != std::string::npos && br != std::string::npos && e != std::string::npos) {
    if (bl < e && e < br && br < c1 && c1 < c2) {
      //"[" needs to come before "=" before "]" before ":"
      return;
    }
  }  // throw error to indicate invalid format
  throw std::invalid_argument("Cannot convert the line to the fancy choice!");
}
#endif
