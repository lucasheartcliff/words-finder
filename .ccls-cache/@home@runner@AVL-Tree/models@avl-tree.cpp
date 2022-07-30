#pragma once
#include "nodes.cpp"
#include <iostream>

using namespace std;

// The type T should extends Node class

class AVLTree {

  WordNode *root;

  int stringCompare(string a, string b) { return a.compare(b); }

  

  void makeEmpty(WordNode *t) {
    if (t == NULL)
      return;
    makeEmpty(t->left);
    makeEmpty(t->right);
    delete t;
  }

  WordNode *insert(WordNode *newT, WordNode *t) {
    if (t == NULL) {
      t = newT;
    } else {
      int compareResult = this->stringCompare(newT->word, t->word);
      
      switch (compareResult) {
      case -1:
        t->left = insert(newT, t->left);
        if (height(t->left) - height(t->right) == 2) {
          int rCompare = this->stringCompare(newT->word, t->left->word);
          if (rCompare == -1)
            t = singleRightRotate(t);
          else if (rCompare == 1)
            t = doubleRightRotate(t);
        }
        break;
      case 0:

        break;

      case 1:
        t->right = insert(newT, t->right);
        if (height(t->right) - height(t->right) == 2) {
          int rCompare = this->stringCompare(newT->word, t->right->word);
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

  WordNode *remove(int x, WordNode *t) {
    WordNode *temp;

    // Element not found
    if (t == NULL)
      return NULL;

    // Searching for element
    else if (x < t->word)
      t->left = remove(x, t->left);
    else if (x > t->word)
      t->right = remove(x, t->right);

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

  void insert(int x) { root = insert(x, root); }

  void remove(int x) { root = remove(x, root); }

  void display() {
    inorder(root);
    cout << endl;
  }
};
