
/*
 * File:   main.cpp
 * Author: Thi Nguyen
 *
 * Created on June 1, 2022, 9:34 AM
 */

#include "BinaryTree.h"

BinaryTree::BinaryTree() {
    this->size = 0;
}

BinaryTree::BinaryTree(int size) {
    if (size <= 0)
        this->size = 0;
    else
        this->size = size;
}

bool BinaryTree::insert(string data, string content) {
    Node *z = new Node(data, content);
    Node *y = NULL;
    Node *x = this->root;
    while (x != NULL) {
        y = x;
        if (data.compare(x->getData()) < 0)
            x = x->getLeft();
        else
            x = x->getRight();
    }
    z->setParent(y);
    if (y == NULL)
        this->root = z;
    else if (data.compare(y->getData()) < 0) {
        y->setLeft(z);
    } else {
        y->setRight(z);
    }
    balance(y);
    return true;
}

bool BinaryTree::deleteNode(string data) {
    Node *nodeZ = search(this->root, data);
    if (nodeZ == NULL)
        return false;
    if (nodeZ->getLeft() == NULL) {
        transplant(nodeZ, nodeZ->getRight());
    } else if (nodeZ->getRight() == NULL) {
        transplant(nodeZ, nodeZ->getLeft());
    } else {
        Node *nodeY = nodeZ->getLeft();
        while (nodeY != NULL && nodeY->getRight() != NULL) {
            nodeY = nodeY->getRight();
        }

        if (nodeY != nodeZ->getLeft()) {
            transplant(nodeY, nodeY->getLeft());
            nodeY->setLeft(nodeZ->getLeft());
            nodeY->getLeft()->setParent(nodeY);
        }
        transplant(nodeZ, nodeY);
        nodeY->setRight(nodeZ->getRight());
        nodeY->getRight()->setParent(nodeY);
    }
    balance(nodeZ->getParent());
    delete nodeZ;
    return true;
}

Node *BinaryTree::leftLeft(Node *x) {
    Node *y = x->getRight();
    x->setRight(y->getLeft());
    if (y->getLeft() != NULL) {
        y->getLeft()->setParent(x);
    }
    y->setParent(x->getParent()); // link x's parent to y
    if (x->getParent() == NULL)
        this->root = y;
    else if (x == x->getParent()->getLeft()) {
        x->getParent()->setLeft(y);
    } else
        x->getParent()->setRight(y);
    y->setLeft(x); // set y's left is x
    x->setParent(y); // set x's parent is y
    return y;
}

Node *BinaryTree::rightRight(Node *y) {
    Node *x = y->getLeft();
    y->setLeft(x->getRight());
    if (x->getRight() != NULL)
        x->getRight()->setParent(y);
    x->setParent(y->getParent());
    if (y->getParent() == NULL)
        this->root = x; // if parent of y is null , mean y is root, so root set to x
    else if (y ==
            y->getParent()->getRight()) { // if y is on a right of its parent,
        // set x to right of y's parent
        y->getParent()->setRight(x);
    } else
        y->getParent()->setLeft(x);
    x->setRight(y);
    y->setParent(x);
    return x;
}

Node *BinaryTree::rightLeft(Node *node) {
    Node *tmp = node->getRight();
    node->setRight(rightRight(tmp));
    return leftLeft(node);
}

Node *BinaryTree::leftRight(Node *node) {
    Node *tmp = node->getLeft();
    node->setLeft(leftLeft(tmp));
    return rightRight(node);
}

Node *BinaryTree::rebalance(Node *x) {
    int type = unbalancedType(x);
    if (type > 1) { // left heavy
        if (unbalancedType(x->getLeft()) >= 0) { // subtree is left heavy
            x = rightRight(x);
        } else {
            x = leftRight(x);
        }

    } else if (type < -1) { // right heavy
        if (unbalancedType(x->getRight()) <= 0) { // subtree is right heavy
            x = leftLeft(x);
        } else {
            x = rightLeft(x);
        }
    }
    return x;
}

void BinaryTree::balance(Node *x) {
    Node *y = NULL;
    while (x != NULL) {

        y = x->getParent();

        if (y == NULL) {
            this->root = rebalance(x);
        } else if ((y->getLeft() != NULL) && (y->getLeft() == x)) {
            y->setLeft(rebalance(x));
        } else {
            y->setRight(rebalance(x));
        }

        x = y;
    }
}

int BinaryTree::getHeight(Node *x) {
    if (x == NULL)
        return 0;
    return 1 + max(getHeight(x->getLeft()), getHeight(x->getRight()));
}

int BinaryTree::unbalancedType(Node *x) {
    if (x == NULL)
        return 0;
    int heightLeft, heightRight;
    heightLeft = x->getLeft() != NULL ? getHeight(x->getLeft()) : 0;
    heightRight = x->getRight() != NULL ? getHeight(x->getRight()) : 0;
    return heightLeft - heightRight;
}

void BinaryTree::transplant(Node *u, Node *v) {
    if (u->getParent() == NULL)
        this->root = v;
    else if (u == u->getParent()->getLeft())
        (u->getParent())->setLeft(v);
    else
        (u->getParent())->setRight(v);
    if (v != NULL)
        v->setParent(u->getParent());
}

Node *BinaryTree::minimum(Node *node) {
    Node *tmp = node->getLeft();
    if (tmp == NULL)
        return node;
    Node *previous = tmp;
    while (tmp != NULL) {
        previous = tmp;
        tmp = tmp->getRight();
    }
    return previous;
}

Node *BinaryTree::search(Node *node, string data) {
    if (node == NULL || data.compare(node->getData()) == 0)
        return node;
    if (data.compare(node->getData()) < 0)
        return search(node->getLeft(), data);
    return search(node->getRight(), data);
}

Node *BinaryTree::search(string data) {
    return search(this->root, data);
}

void BinaryTree::printPost(Node *node) {
    if (node == NULL)
        return;
    printPost(node->getLeft());
    printPost(node->getRight());
    cout << node->getData() << " ";
}

void BinaryTree::printPre(Node *node) {
    if (node == NULL)
        return;
    cout << node->getData() << " ";
    printPre(node->getLeft());
    printPre(node->getRight());
}

void BinaryTree::printIn(Node *node) {
    if (node == NULL)
        return;
    printIn(node->getLeft());
    cout << node->getData() << " ";
    printIn(node->getRight());
}

void BinaryTree::printLevel() {

    queue<Node *> levelNodes;
    Node *currentNode;
    levelNodes.push(this->root);
    levelNodes.push(NULL);

    int currentLevel = 0;
    int height = getHeight(this->root);

    while (currentLevel <= height) {

        currentNode = levelNodes.front();
        levelNodes.pop();

        while (currentNode != NULL) { // end of a level
            cout << currentNode->getData() << " ";
            if (currentNode->getLeft() != NULL)
                levelNodes.push(currentNode->getLeft());
            if (currentNode->getRight() != NULL)
                levelNodes.push(currentNode->getRight());
            currentNode = levelNodes.front();
            levelNodes.pop();
        }
        levelNodes.push(NULL); // push NULL node to end of a level
        currentLevel++; // go to next level
    }
}

void BinaryTree::printTree(int type) {
    if (type == 1 || type == -1) { // pre order traversal = root left right
        cout << "Pre order traversal: ";
        printPre(this->root);
        cout << endl;
    }
    if (type == 2 || type == -1) { // inorder traversal = left root right
        cout << "In order traversal: ";
        Node *minLeaves = minimum(this->root);
        printIn(this->root);
        cout << endl;
    }
    if (type == 3 || type == -1) { // post order traversal = left right root
        cout << "Post order traversal: ";
        printPost(this->root);
        cout << endl;
    }
    if (type == 0 || type == -1) { // level order traversal
        cout << "Level order traversal: ";
        printLevel();
        cout << endl;
    }
}
