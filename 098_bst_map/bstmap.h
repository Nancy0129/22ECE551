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
  void findAdd(Node * curr, const K & key, const V & value) {
    if (curr == NULL) {
      curr = new Node(key, value);
    }
    if (curr->name == key) {
      curr->value = value;
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
  const V & find(Node * curr, const K & key) const {
    if (curr == NULL) {
      throw std::exception();
    }
    if (curr->name == key) {
      return curr->value;
    }
    if (curr->name < key) {
      return find(curr->right, key);
    }
    else {
      return find(curr->left, key);
    }
  }

  Node * findMin(Node * curr) {
    if (curr->left == NULL) {
      return curr;
    }
    return findMin(curr->left);
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
        curr->right = findRm(curr->right, minNode->name);
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
    if (curr == NULL) {
      return;
    }
    postRM(curr->left);
    postRM(curr->right);
    delete curr;
  }

 public:
  BstMap() : root(NULL) {}
  virtual void add(const K & key, const V & value) { this->findAdd(root, key, value); }
  virtual const V & lookup(const K & key) const throw(std::invalid_argument) {
    return this->find(root, key);
  }
  virtual void remove(const K & key) { root = this->findRm(root, key); }
  virtual ~BstMap() { this->postRM(root); }
};
