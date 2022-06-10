
/*
 * File:   main.cpp
 * Author: Thi Nguyen
 *
 * Created on June 1, 2022, 9:34 AM
 */
#include "Node.h"
#include <algorithm>
#include <queue>

using namespace std;

#ifndef BINARYTREE_H
#define BINARYTREE_H

class BinaryTree {
private:
    int size;
    Node *root;

public:
    BinaryTree();
    BinaryTree(int);
    bool deleteNode(string); // delete a node
    bool insert(string, string); // insert a node
    Node *rebalance(Node *); // rebalance at an node which unbalance occurs
    void balance(Node *); // balance unbalanced tree
    void transplant(Node *, Node *); // call after delete a node
    Node *minimum(Node *); // get node has min value
    Node *search(Node *, string); // search one node, return
    Node *search(string);
    Node *leftLeft(Node *); // left rotate
    Node *rightRight(Node *); // right rotate
    Node *leftRight(Node *); // double left rotate
    Node *rightLeft(Node *); // double right rotate
    int unbalancedType(Node *); // find out is left heavy or right heavy
    int getHeight(Node *); // get height of node's sub tree
    void preOrderTraversal(); // traversal root, left, right
    void inOrderTraversal(); // traversal  left, root, right
    void postOrderTraversal(); // traversal left, right, root
    void levelOrderTraversal(); // traversal  on every level
    void printPost(Node *);
    void printPre(Node *);
    void printIn(Node *);
    void printLevel();
    void printTree(int);
};

#endif /* BINARYTREE_H */
