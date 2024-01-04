//************************************************************************
// ASU CSE310 Assignment #6 Spring 2023
// Author:Jiandong Guan
// ASU ID:1220287159
// Description: Red black tree header file. It defines the Node and the
//              red black tree functionalities.
//************************************************************************
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <string>

using namespace std;

#ifndef REDBLACKTREE_H_
#define REDBLACKTREE_H_

//Node represents one node of the RBT which is an Employee
struct Node
{
   string firstName, lastName;
   int id;
   double salary;
   Node *parent;
   Node *leftChild;
   Node *rightChild;
   string color="BLACK";
};

class RedBlackTree
{
    private:
        Node *root;
    public:
        RedBlackTree();
        ~RedBlackTree();
        Node* getRoot();
        int deleteNode(Node *node);
        void insertNode(Node *node);
        void fixUp(Node *node);

        void preOrderTraversal(Node *node);
        void inorderTraversal(Node *node);
        void postOrderTraversal(Node *node);

        Node* findMinimumNode(Node *node);
        Node* findMaximumNode(Node *node);
        Node* treeSearch(int id, string firstName, string lastName);
        void leftRotate(Node *node);
        void rightRotate(Node *node);
        Node* findPredecessorNode(Node *node);
        Node* findSuccessorNode(Node *node);

        void treeMinimum();
        void treeMaximum();
        void treePreorder();
        void treeInorder();
        void treePostorder();
        void treePredecessor(int id, string firstName, string lastName);
        void treeSucessor(int id, string firstName, string lastName);
        void treeInsert(int id, string firstName, string lastName, double salary);

        void print(Node *node);
};
#endif
