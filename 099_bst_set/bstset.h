#include <iostream>
#include <stdexcept>

#include "set.h"
template<typename T>
class BstSet : public Set<T> {
 private:
  class Node {
   public:
    T value;
    Node * left;
    Node * right;
    Node(const T & v) : value(v), left(NULL), right(NULL) {}
    Node(const T & v, Node * l, Node * r) : value(v), left(l), right(r) {}
  };
  Node * root;
  Node * deepCopy(Node * rhs) {
    if (rhs == NULL) {
      return NULL;
    }
    Node * curr = new Node(rhs->value);
    curr->left = deepCopy(rhs->left);
    curr->right = deepCopy(rhs->right);
    return curr;
  }
  void findAdd(Node * curr, const T & value) {
    if (curr->value == value) {
      return;
    }
    else if (curr->value < value) {
      if (curr->right == NULL) {
        curr->right = new Node(value);
      }
      else {
        findAdd(curr->right, value);
      }
    }
    else {
      if (curr->left == NULL) {
        curr->left = new Node(value);
      }
      else {
        findAdd(curr->left, value);
      }
    }
  }

  bool find(Node * curr, const T & key) const {
    //std::cout << "Findding " << key << "\n";
    if (curr == NULL) {
      return false;
    }
    if (curr->value == key) {
      return true;
    }
    if (curr->value < key) {
      if (curr->right == NULL) {
        return false;
      }
      return find(curr->right, key);
    }
    else {
      if (curr->left == NULL) {
        return false;
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

  Node * findRm(Node * curr, const T & key) {
    if (curr == NULL) {
      return NULL;
    }
    if (curr->value == key) {
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
        curr->value = minNode->value;
        T minName = minNode->value;
        curr->right = findRm(curr->right, minName);
        return curr;
      }
    }
    else if (curr->value < key) {
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
      std::cout << curr->value << " (";
      preOrder(curr->left);
      std::cout << ") (";
      preOrder(curr->right);
      std::cout << ")";
    }
  }

 public:
  BstSet() : root(NULL) {}

  BstSet(const BstSet & rhs) : root(NULL) { root = this->deepCopy(rhs.root); }
  BstSet & operator=(const BstSet & rhs) {
    if (this != &rhs) {
      Node * temp = this->deepCopy(rhs.root);
      this->postRM(root);
      root = temp;
      //std::swap(temp.root, root);
    }
    return *this;
  }

  virtual void add(const T & value) {
    if (root == NULL) {
      root = new Node(value);
    }
    else {
      this->findAdd(root, value);
    }
  }

  virtual bool contains(const T & key) const { return this->find(root, key); }
  virtual void remove(const T & key) {
    //std::cout << "remove " << key << "\n";
    root = this->findRm(root, key);
  }
  virtual ~BstSet() { this->postRM(root); }

  void print_tree() {
    this->preOrder(root);
    std::cout << "\n";
  };
};
