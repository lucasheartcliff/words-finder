#pragma once
#include "nodes.cpp"
#include <iostream>

#include <list>
#include <map>
#include <set>
#include <string>

using std::list;
using std::map;
using std::set;
using std::string;

using namespace std;

// The type T should extends Node class

class AVLTree {

  WordNode *root;

  int stringCompare(string a, string b) { return a.compare(b); }

  bool containsKey(map<unsigned int, FileNode> *generalMap, unsigned int key) {
    return generalMap->find(key) != generalMap->end();
  }

  void mergeOrCreateFileAssociation(WordNode *newT, WordNode *t) {
    map<unsigned int, FileNode> *filesMap = &newT->files;

    if (filesMap != NULL && filesMap->size()) {
      map<unsigned int, FileNode>::iterator iter = filesMap->begin();

      while (iter != filesMap->end()) {
        unsigned int key = iter->first;
        FileNode value = iter->second;

        if (this->containsKey(&t->files, key)) {
          FileNode fileNode = t->files[key];

          fileNode.count += value.count;
          fileNode.lines.insert(value.lines.begin(), value.lines.end());
        } else {
          t->files[key] = value;
        }

        iter++;
      }
    }
  }

  void mergeEqualsNode(WordNode *newT, WordNode *t) {
    t->count += newT->count;
    this->mergeOrCreateFileAssociation(newT, t);
  }

  void makeEmpty(WordNode *t) {
    if (t == NULL)
      return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  WordNode *insert(WordNode *newNode, WordNode *t) {
    if (t == NULL) {
      t = newNode;
    } else {
      int compareResult = this->stringCompare(newNode->word, t->word);

      switch (compareResult) {
      case -1:
        t->left = insert(newNode, t->left);
        if (height(t->left) - height(t->right) == 2) {
          int rCompare = this->stringCompare(newNode->word, t->left->word);
          if (rCompare == -1)
            t = singleRightRotate(t);
          else if (rCompare == 1)
            t = doubleRightRotate(t);
        }
        break;
      case 0:
        this->mergeEqualsNode(newNode, t);
        break;

      case 1:
        t->right = insert(newNode, t->right);
        if (height(t->right) - height(t->right) == 2) {
          int rCompare = this->stringCompare(newNode->word, t->right->word);
          if (rCompare == -1)
            t = doubleRightRotate(t);
          else if (rCompare == 1)
            t = singleRightRotate(t);
        }
        break;
      }
    }

    t->height = max(height(t->left), height(t->right)) + 1;
    return t;
  }

  WordNode *singleRightRotate(WordNode *&t) {
    WordNode *u = t->left;
    t->left = u->right;
    u->right = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(u->left), t->height) + 1;
    return u;
  }

  WordNode *singleLeftRotate(WordNode *&t) {
    WordNode *u = t->right;
    t->right = u->left;
    u->left = t;
    t->height = max(height(t->left), height(t->right)) + 1;
    u->height = max(height(t->right), t->height) + 1;
    return u;
  }

  WordNode *doubleLeftRotate(WordNode *&t) {
    t->right = singleRightRotate(t->right);
    return singleLeftRotate(t);
  }

  WordNode *doubleRightRotate(WordNode *&t) {
    t->left = singleLeftRotate(t->left);
    return singleRightRotate(t);
  }

  WordNode *findMin(WordNode *t) {
    if (t == NULL)
      return NULL;
    else if (t->left == NULL)
      return t;
    else
      return findMin(t->left);
  }

  WordNode *findMax(WordNode *t) {
    if (t == NULL)
      return NULL;
    else if (t->right == NULL)
      return t;
    else
      return findMax(t->right);
  }

  WordNode *remove(string word, WordNode *t) {
    WordNode *temp;
 int compareResult = stringCompare(word,t->word);
    // Element not found
    if (t == NULL)
      return NULL;
    // Searching for element
    else if (compareResult == -1)
      t->left = remove(word, t->left);
    else if (compareResult == 1)
      t->right = remove(word, t->right);

    // Element found
    // With 2 children
    else if (t->left && t->right) {
      temp = findMin(t->right);
      t->word = temp->word;
      t->right = remove(t->word, t->right);
    }
    // With one or zero child
    else {
      temp = t;
      if (t->left == NULL)
        t = t->right;
      else if (t->right == NULL)
        t = t->left;
      delete temp;
    }
    if (t == NULL)
      return t;

    t->height = max(height(t->left), height(t->right)) + 1;

    // If T is unbalanced
    // If left T is deleted, right case
    if (height(t->left) - height(t->right) == 2) {
      // right right case
      if (height(t->left->left) - height(t->left->right) == 1)
        return singleLeftRotate(t);
      // right left case
      else
        return doubleLeftRotate(t);
    }
    // If right T is deleted, left case
    else if (height(t->right) - height(t->left) == 2) {
      // left left case
      if (height(t->right->right) - height(t->right->left) == 1)
        return singleRightRotate(t);
      // left right case
      else
        return doubleRightRotate(t);
    }
    return t;
  }

  int height(WordNode *t) { return (t == NULL ? -1 : t->height); }

  int getBalance(WordNode *t) {
    if (t == NULL)
      return 0;
    else
      return height(t->left) - height(t->right);
  }

  void inorder(WordNode *t) {
    if (t == NULL)
      return;
    inorder(t->left);
    cout << t->word << " ";
    inorder(t->right);
  }

public:
  AVLTree() { root = NULL; }

  void insert(WordNode* node) { root = insert(node, root); }

  void remove(string x) { root = remove(x, root); }

  void display() {
    inorder(root);
    cout << endl;
  }
};
