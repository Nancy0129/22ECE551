#include <iostream>

#include "bstset.h"
using namespace std;

int main() {
  BstSet<int> bm;
  bm.add(1);
  bm.add(0);
  bm.add(3);
  bm.add(-1);
  bm.add(2);
  bm.add(1);
  bm.add(80);
  bm.add(40);
  bm.add(-18);
  cout << "The tree bm is now: \n";
  bm.print_tree();
  cout << '\n';

  BstSet<int> bmCopy(bm);
  BstSet<int> bm2;
  bm2 = bm;

  cout << "Looking for key -1: " << bm.contains(-1) << endl;
  cout << "Looking for key 0: " << bm.contains(0) << endl;
  cout << "Looking for key 2: " << bm.contains(2) << endl;
  cout << "Looking for key 4: " << bm.contains(4) << endl;
  cout << "Looking for key 5: " << bm.contains(5) << endl;
  cout << "Looking for key 80: " << bm.contains(80) << endl;

  bm.remove(1);
  cout << "After removing 0, the tree bm is now: \n";
  bm.print_tree();
  cout << '\n';

  bm.remove(-1);
  cout << "After removing -1, the tree bm is now: \n";
  bm.print_tree();
  cout << '\n';

  bm.remove(3);
  cout << "After removing 3, the tree bm is now: \n";
  bm.print_tree();
  cout << '\n';

  bm.remove(5);
  cout << "After removing 5, the tree bm is now: \n";
  bm.print_tree();
  cout << '\n';

  bm2.add(76);
  bm2.remove(80);
  cout << "The tree bm2 is now: \n";
  bm2.print_tree();
  cout << '\n';

  cout << "The tree bmCopy is now: \n";
  bmCopy.print_tree();
  cout << '\n';

  return 0;
}
