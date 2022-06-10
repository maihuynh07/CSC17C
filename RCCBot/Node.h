
/*
 * File:   main.cpp
 * Author: Thi Nguyen
 *
 * Created on June 1, 2022, 9:34 AM
 */
#include <iostream>
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
private:
    string data;
    string content;
    Node *left;
    Node *right;
    Node *parent;

public:

    Node(string data, string content) {
        this->data = data;
        this->content = content;
        this->left = NULL;
        this->right = NULL;
        this->parent = NULL;
    };

    string getData() const {
        return data;
    };

    string getContent() const {
        return content;
    };

    Node *getLeft() const {
        return left;
    };

    Node *getRight() const {
        return right;
    };

    Node *getParent() const {
        return parent;
    };

    void setParent(Node *parent) {
        this->parent = parent;
    };

    void setLeft(Node *left) {
        this->left = left;
    };

    void setRight(Node *right) {
        this->right = right;
    };

private:
};
#endif /* NODE_H */
