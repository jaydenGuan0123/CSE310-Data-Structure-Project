//************************************************************************
// ASU CSE310 Assignment #6 Spring 2023
// Author:Jiandong Guan
// ASU ID:1220287159
// Description: this is the main program that reads input from keyboard,
// it then execute various red-black tree operations which is given in the input.
//**************************************************************************

#include "RedBlackTree.h"

using namespace std;

//This function used to get all info. of an Employee
void getEmployeeInfo(string oneLine, int& id, string& firstName, string& lastName, double& salary);

int main()
{

   int id;
   string firstName, lastName;
   double salary;
   string command, oneLine, token;
   string delimiter = ",";

   int pos = 0;

   //Create a RedBlackTree object here, use it throughout the program
   RedBlackTree* tree=new RedBlackTree();

   do
   {
      getline(cin, oneLine);
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      command = token;
      oneLine.erase(0, pos + delimiter.length());

      if(command.compare("quit")==0)
      {
         cout << "\nCommand: quit" << endl;
           delete tree;
         break;
      }
      else if(command.compare("tree_preorder")==0)
      {
         cout << "\nCommand: tree_preorder" << endl;
            tree->treePreorder();
      }
      else if(command.compare("tree_inorder")==0)
      {
         cout << "\nCommand: tree_inorder" << endl;
            tree->treeInorder();
      }
      else if(command.compare("tree_postorder")==0)
      {
         cout << "\nCommand: tree_postorder" << endl;
            tree->treePostorder();
      }
      else if(command.compare("tree_minimum")==0)
      {
         cout << "\nCommand: tree_minimum" << endl;
        cout<<"The MINIMUM is:"<<endl;
            tree->treeMinimum();
      }
      else if(command.compare("tree_maximum")==0)
      {
         cout << "\nCommand: tree_maximum" << endl;
         cout<<"The MAXIMUM is:"<<endl;
            tree->treeMaximum();
      }
      else if(command.compare("tree_predecessor")==0)
      {
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        id = stoi(token);
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        firstName = token;
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        lastName = token;
        oneLine.erase(0, pos + delimiter.length());
        cout << "\nCommand: tree_predecessor" << endl;
        Node* x=tree->treeSearch(id,firstName, lastName);
        if(x->id!=0){
        if(tree->findPredecessorNode(x)->id==0)
          cout<<"Its Predecessor does NOT exist"<<endl;
        else{
          cout<<"Its Predecessor is:"<<endl;
        tree->print(tree->findPredecessorNode(x));
        }
        }
        else
          cout<<"Its Predecessor does NOT exist"<<endl;
      }
      else if(command.compare("tree_successor")==0)
      {
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        id = stoi(token);
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        firstName = token;
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        lastName = token;
        oneLine.erase(0, pos + delimiter.length());
         cout << "\nCommand: tree_successor" << endl;
        Node* x=tree->treeSearch(id,firstName, lastName);
        if(x->id!=0){
        if(tree->findSuccessorNode(x)->id==0)
          cout<<"Its Successor does NOT exist"<<endl;
        else{
          cout<<"Its Successor is:"<<endl;
        tree->print(tree->findSuccessorNode(x));
        }
        }
        else
          cout<<"Its Successor does NOT exist"<<endl;
      }
      else if(command.compare("tree_search")==0)
      {
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        id = stoi(token);
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        firstName = token;
        oneLine.erase(0, pos + delimiter.length());
        pos = oneLine.find(delimiter);
        token = oneLine.substr(0, pos);
        lastName = token;
        oneLine.erase(0, pos + delimiter.length());
        cout << "\nCommand: tree_search" << endl;
        tree->treeSearch(id,firstName,lastName);
      }
      else if(command.compare("tree_insert")==0)
      {
         getEmployeeInfo(oneLine,id,firstName, lastName, salary);
        tree->treeInsert(id, firstName, lastName,salary);
         cout << "\nCommand: tree_insert" << endl;
         cout << left;
         cout << setw(8)  << id
              << setw(12) << firstName
              << setw(12) << lastName
              << setw(10) << fixed << setprecision(2) << salary << endl;
        }
   } while(true);  //continue until 'quit'
   return 0;
}

//************************************************************************************************
//This function from one line, extract tokens and get all info. of an Employee
void getEmployeeInfo(string oneLine, int& id, string& firstName, string& lastName, double& salary)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

  pos=oneLine.find(delimiter);
  token = oneLine.substr(0,pos);
   salary = stod(oneLine);
   oneLine.erase(0, pos+delimiter.length());
}