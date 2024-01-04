//************************************************************************
// ASU CSE310 Assignment #6 Spring 2023
// Author:Jiandong Guan
// ASU ID:1220287159
// Description: Red black tree implementation. See RedBlackTree.h
//              for the Red Black Tree definition
//************************************************************************

#include "RedBlackTree.h"

using namespace std;
int i=0;
Node *nul=new Node();

//*******************************************************************
//constructor
RedBlackTree::RedBlackTree()
{
  root=nul;
}

//*******************************************************************
//destructor
RedBlackTree::~RedBlackTree()
{
  int nodeSize=deleteNode(root);
	cout << "The number of deleted nodes: " << nodeSize << endl;
}

Node* RedBlackTree::getRoot(){
  return root;
}
int RedBlackTree::deleteNode(Node *node){
  if(node->leftChild!=nul){
    deleteNode(node->leftChild);
  }
  if(node->rightChild!=nul){
    deleteNode(node->rightChild);
  }
  delete node;
  i++;
  return i;
}
void RedBlackTree::insertNode(Node *node){
  Node* y=nul;
  Node* x=root;
  while(x!=nul)
    {
      y=x;
      if(node->id<x->id)
        x=x->leftChild;
      else
        x=x->rightChild;
    }
  node->parent=y;
  if(y==nul)
    root=node;
  else if(node->id<y->id)
    y->leftChild=node;
  else 
    y->rightChild=node;
  node->leftChild=nul;
  node->rightChild=nul;
  node->color="RED";
  fixUp(node);
  }
void RedBlackTree::fixUp(Node *node){
 while(node->parent->color=="RED"){
  if(node->parent==node->parent->parent->leftChild){
    Node* y=node->parent->parent->rightChild;
    if(y->color=="RED")
    {
      node->parent->color="BLACK";
      y->color="BLACK";
      node->parent->parent->color="RED";
      node=node->parent->parent;
    }
    else 
    {
      if(node==node->parent->rightChild){
      node=node->parent;
      leftRotate(node);}
      node->parent->color="BLACK";
      node->parent->parent->color="RED";
      rightRotate(node->parent->parent); 
    }
  }
  else {
  Node* y=node->parent->parent->leftChild;
    if(y->color=="RED")
    {
      node->parent->color="BLACK";
      y->color="BLACK";
      node->parent->parent->color="RED";
      node=node->parent->parent;
    }
    else 
    {
      if(node==node->parent->leftChild){
      node=node->parent;
      rightRotate(node);}
      node->parent->color="BLACK";
      node->parent->parent->color="RED";
      leftRotate(node->parent->parent); 
    }
  }
}
root->color="BLACK";
}
void RedBlackTree::preOrderTraversal(Node *node){
  if(node!=nul){
  print(node);
  preOrderTraversal(node->leftChild);
  preOrderTraversal(node->rightChild);
  }
}
void RedBlackTree::inorderTraversal(Node *node){
  if(node!=nul){
  inorderTraversal(node->leftChild);
  print(node);
  inorderTraversal(node->rightChild);
  }
}
void RedBlackTree::postOrderTraversal(Node *node){
  if(node!=nul){
  postOrderTraversal(node->leftChild);
  postOrderTraversal(node->rightChild);
  print(node);
  }
}
Node* RedBlackTree::findMaximumNode(Node *node){
  while(node->rightChild!=nul)
    node=node->rightChild;
  return node;
}
Node* RedBlackTree::findMinimumNode(Node *node){
  while(node->leftChild!=nul)
    node=node->leftChild;
  return node;
}
Node* RedBlackTree::treeSearch(int id, string firstName, string lastName){
  Node* x=root;
  while(x!=nul&&(x->id!=id||x->firstName!=firstName||x->lastName!=lastName))
    {
      if(id<x->id)
        x=x->leftChild;
      else
        x=x->rightChild;
    }
  if(x!=nul){
    cout << left;
         cout << setw(8)  << id
           << setw(12) << firstName
           << setw(12) << lastName<<"is found."<<endl;}
  else{
        cout << left;
         cout << setw(8)  << id
           << setw(12) << firstName
           << setw(12) << lastName<<"is NOT found."<<endl;}
  return x;
}
void RedBlackTree::leftRotate(Node *node){
  Node* y=node->rightChild;
  node->rightChild=y->leftChild;
  if(y->leftChild!=nul)
    y->leftChild->parent=node;
  y->parent=node->parent;
  if(node->parent==nul)
    root=y;
  else if(node==node->parent->leftChild)
    node->parent->leftChild=y;
  else
    node->parent->rightChild=y;
  y->leftChild=node;
  node->parent=y;
}
void RedBlackTree::rightRotate(Node *node){
  Node* y=node->leftChild;
  node->leftChild=y->rightChild;
  if(y->rightChild!=nul)
    y->rightChild->parent=node;
  y->parent=node->parent;
  if(node->parent==nul)
    root=y;
  else if(node==node->parent->leftChild)
    node->parent->leftChild=y;
  else
    node->parent->rightChild=y;
  y->rightChild=node;
  node->parent=y;
}
Node* RedBlackTree::findPredecessorNode(Node *node){
  if(node->leftChild!=nul)
    return findMaximumNode(node->leftChild);
  Node*y =node->parent;
  while(y!=nul&&node==y->leftChild)
    {
      node=y;
      y=y->parent;
    }
  return y;
}
Node* RedBlackTree::findSuccessorNode(Node *node){
  if(node->rightChild!=nul)
    return findMinimumNode(node->rightChild);
  Node*y =node->parent;
  while(y!=nul&&node==y->rightChild)
    {
      node=y;
      y=y->parent;
    }
  return y;
}
void RedBlackTree::treeMinimum(){
  print(findMinimumNode(root));
}
 void RedBlackTree::treeMaximum(){
   print(findMaximumNode(root));
 }
void RedBlackTree::treePreorder(){
  preOrderTraversal(root);
}
void RedBlackTree::treeInorder(){
  inorderTraversal(root);
}
void RedBlackTree::treePostorder(){
  postOrderTraversal(root);
}
void RedBlackTree::treePredecessor(int id, string firstName, string lastName){
  Node* x=treeSearch(id,firstName,lastName);
  if(x!=NULL)
  Node* predecessor=findPredecessorNode(x);
}
  void RedBlackTree::treeSucessor(int id, string firstName, string lastName){
    Node* x=treeSearch(id,firstName,lastName);
    if(x!=nul)
    Node* sucessor=findSuccessorNode(x);
        }
  void RedBlackTree::treeInsert(int id, string firstName, string lastName, double salary){
    Node* x=new Node();
    x->id=id;
    x->firstName=firstName;
    x->lastName=lastName;
    x->salary=salary;
    x->color="RED";
    insertNode(x);
  }

void RedBlackTree::print(Node *node)
{
      
      cout << left;
      cout << setw(8)  << node->id
           << setw(12) << node->firstName
           << setw(12) << node->lastName
           << setw(10) << fixed << setprecision(2) << node->salary;
      cout << right << setw(7) << node->color << endl;
}