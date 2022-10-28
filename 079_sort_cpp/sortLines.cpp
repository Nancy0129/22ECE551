#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;
void showRes(vector<string> v) {
  for (size_t i = 0; i < v.size(); i++) {
    cout << v[i] << "\n";
  }
}
int main(int argc, char ** argv) {
  string s;
  if (argc == 1) {
    vector<string> v1;
    while (getline(cin, s)) {
      v1.push_back(s);
    }
    sort(v1.begin(), v1.end());
    showRes(v1);
  }
  else {
    for (int i = 1; i < argc; i++) {
      vector<string> v1;
      ifstream f(argv[i]);
      if (!f.is_open()) {
        cerr << "Cannot open the file!" << endl;
        exit(EXIT_FAILURE);
      }
      while (getline(f, s)) {
        v1.push_back(s);
      }
      sort(v1.begin(), v1.end());
      showRes(v1);
    }
  }
}
