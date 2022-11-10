#include <iostream>
#include <stdexcept>

#include "map.h"
template<typename K, typename V>
class BstMap : public Map<K, V> {
 private:
  class Node {
   public:
    K * name;
    V * value;
    Node * left;
    Node * right;
    Node(const K & n, const V & v) :
        name(new K(n)), value(new V(v)), left(NULL), right(NULL) {}
    Node(const K & n, const V & v, Node * l, Node * r) :
        name(new K(n)), value(new V(v)), left(l), right(r) {}
  };
  Node * root;
  Node * findAdd(Node * curr, const K & key, const V & value) {
    //std::cout << key << "\n";
    if (curr == NULL) {
      //std::cout << "aaa\n";
      return new Node(key, value);
      //return;
    }
    if (*(curr->name) == key) {
      *(curr->value) = value;
      return curr;
    }
    else if (*(curr->name) < key) {
      curr->right = findAdd(curr->right, key, value);
      return curr;
    }
    else {
      curr->left = findAdd(curr->left, key, value);
      return curr;
    }
  }

  const V & find(Node * curr, const K & key) const throw(std::invalid_argument) {
    //std::cout << "Findding " << key << "\n";
    if (curr == NULL) {
      throw std::invalid_argument("No items!");
    }
    if (*(curr->name) == key) {
      //V * res = new V(curr->value);
      //return *res;
      return *curr->value;
    }
    if (*(curr->name) < key) {
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

  Node * findRm(Node * curr, const K & key, bool clean) {
    if (curr != NULL) {
      if (key > *(curr->name)) {
        curr->right = findRm(curr->right, key, clean);
      }
      else if (*(curr->name) > key) {
        curr->left = findRm(curr->left, key, clean);
      }
      else {
        if (curr->left == NULL && curr->right == NULL) {
          if (clean) {
            delete curr->name;
            delete curr->value;
          }
          delete curr;
          return NULL;
        }
        if (curr->left == NULL && curr->right != NULL) {
          Node * temp = curr->right;
          if (clean) {
            delete curr->name;
            delete curr->value;
          }
          delete curr;
          return temp;
        }
        if (curr->left != NULL && curr->right == NULL) {
          Node * temp = curr->left;
          if (clean) {
            delete curr->name;
            delete curr->value;
          }
          delete curr;
          return temp;
        }
        if (curr->left != NULL && curr->right != NULL) {
          Node * minNode = findMin(curr->right);
          if (clean) {
            delete curr->name;
            delete curr->value;
          }
          curr->name = minNode->name;
          curr->value = minNode->value;

          curr->right = findRm(curr->right, *(curr->name), false);
          return curr;
        }
      }
    }
    return curr;
  }
  void postRM(Node * curr) {
    if (curr != NULL) {
      postRM(curr->left);
      postRM(curr->right);
      delete curr->name;
      delete curr->value;
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
  BstMap() : root(NULL) { /*std::cout << "begin\n"; */
  }

  virtual void add(const K & key, const V & value) {
    // std::cout << key << "\n";
    root = findAdd(root, key, value);
  }

  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return this->find(root, key);
  }
  virtual void remove(const K & key) {
    //std::cout << "remove " << key << "\n";
    root = this->findRm(root, key, true);
  }
  virtual ~BstMap() { this->postRM(root); }

  void print_tree() {
    this->preOrder(root);
    std::cout << "\n";
  };
};
