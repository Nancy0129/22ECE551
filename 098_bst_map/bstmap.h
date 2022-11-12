#include <iostream>
#include <stdexcept>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K name;
    V value;
    Node * left;
    Node * right;
    Node(const K & n, const V & v) : name(n), value(v), left(NULL), right(NULL) {}
    Node(const K & n, const V & v, Node * l, Node * r) :
        name(n), value(v), left(l), right(r) {}
  };
  Node * root;
  Node * deepCopy(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * curr = new Node(rhs->name, rhs->value);
    curr->left = deepCopy(rhs->left);
    curr->right = deepCopy(rhs->right);
    return curr;
  }
  void findAdd(Node * curr, const K & key, const V & value) {
    if (curr->name == key) {
      curr->value = value;
      return;
    }
    else if (curr->name < key) {
      if (curr->right == NULL) {
        curr->right = new Node(key, value);
      }
      else {
        findAdd(curr->right, key, value);
      }
    }
    else {
      if (curr->left == NULL) {
        curr->left = new Node(key, value);
      }
      else {
        findAdd(curr->left, key, value);
      }
    }
  }

  const V & find(Node * curr, const K & key) const throw(std::invalid_argument) {
    //std::cout << "Findding " << key << "\n";
    if (curr == NULL) {
      throw std::invalid_argument("No items!");
    }
    if (curr->name == key) {
      return curr->value;
    }
    if (curr->name < key) {
      if (curr->right == NULL) {
        throw std::invalid_argument("wrong input key");
      }
      return find(curr->right, key);
    }
    else {
      if (curr->left == NULL) {
        throw std::invalid_argument("wrong input key");
      }
      return find(curr->left, key);
    }
  }
  Node * findMin(Node * curr) {
    Node * temp = curr;
    while (temp->left != NULL) {
      temp = temp->left;
    }
    return temp;
  }

  Node * findRm(Node * curr, const K & key) {
    if (curr == NULL) {
      return NULL;
    }
    if (curr->name == key) {
      if (curr->left == NULL && curr->right == NULL) {
        delete curr;
        return NULL;
      }
      if (curr->left == NULL && curr->right != NULL) {
        Node * temp = curr->right;
        delete curr;
        return temp;
      }
      if (curr->left != NULL && curr->right == NULL) {
        Node * temp = curr->left;
        delete curr;
        return temp;
      }
      if (curr->left != NULL && curr->right != NULL) {
        Node * minNode = findMin(curr->right);
        curr->name = minNode->name;
        curr->value = minNode->value;
        K minName = minNode->name;
        curr->right = findRm(curr->right, minName);
        return curr;
      }
    }
    else if (curr->name < key) {
      curr->right = findRm(curr->right, key);
      return curr;
    }
    else {
      curr->left = findRm(curr->left, key);
      return curr;
    }
    return curr;
  }
  void postRM(Node * curr) {
    if (curr != NULL) {
      postRM(curr->left);
      postRM(curr->right);
      delete curr;
    }
  }
  void preOrder(Node * curr) {
    if (curr != NULL) {
      std::cout << curr->name << " (";
      preOrder(curr->left);
      std::cout << ") (";
      preOrder(curr->right);
      std::cout << ")";
    }
  }

 public:
  BstMap() : root(NULL) {}

  BstMap(const BstMap & rhs) : root(NULL) { root = this->deepCopy(rhs.root); }
  BstMap & operator=(const BstMap & rhs) {
    if (this != &rhs) {
      Node * temp = this->deepCopy(rhs.root);
      this->postRM(root);
      root = temp;
      //std::swap(temp.root, root);
    }
    return *this;
  }

  virtual void add(const K & key, const V & value) {
    if (root == NULL) {
      root = new Node(key, value);
    }
    else {
      this->findAdd(root, key, value);
    }
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    //try {
    //std::cout << "find " << key << "\n";
    //return this->find(root, key);
    // }
    //catch (std::invalid_argument const & ex) {
    //std::cout << "Invalid: " << ex.what() << '\n';
    //   exit(EXIT_FAILURE);
    // }
    return this->find(root, key);
  }
  virtual void remove(const K & key) {
    //std::cout << "remove " << key << "\n";
    root = this->findRm(root, key);
  }
  virtual ~BstMap() { this->postRM(root); }

  void print_tree() {
    this->preOrder(root);
    std::cout << "\n";
  };
};
