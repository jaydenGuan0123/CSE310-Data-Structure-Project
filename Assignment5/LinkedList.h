// ASU CSE310 Assignment #5 Spring 2023
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: A simple linked list that implements a list of Employee objects. A user can
//              perform searching, insertion or deletion on the linked list.
//              //---- is where you should add your own code

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

struct Employee
{
   string firstName, lastName;
   int id;
   double salary;
   struct Employee* next;
};

class LinkedList
{
   private:
     struct Employee* head;
     int size;      //a variable represents number of Employees inside the list
   public:
     LinkedList();
     ~LinkedList();
     Employee* getHead();
     int getSize();
     bool searchEmployee(string firstName, string lastName, int id);
     bool insertEmployee(string firstName, string lastName, int id, double salary);
     bool deleteEmployee(int id);
     void displayList();
};

//Constructor
LinkedList::LinkedList()
{
  head=NULL;
}

//Destructor
LinkedList::~LinkedList()
{ 
  struct Employee* temp;
  while(head!=NULL){
    temp=head;
    head=head->next;
    free(temp);
    }
}

Employee* LinkedList::getHead()
{
    return head;
}

//Return number of Employees inside the Linked list
int LinkedList::getSize()
{ 
  int size=0;
  struct Employee* temp=head;
  while(temp!=NULL)
    {
      temp=temp->next;
      size++;
    }
  return size;
}

//This function does a linear search on the Employee list with the given Employee id
//it returns true if the corresponding Employee is found, otherwise it returns false.
bool LinkedList::searchEmployee(string firstName, string lastName, int id)
{
  struct Employee* temp=head;
  while(temp!=NULL)
    {
      if((temp->id == id)&&(temp->firstName==firstName)&&(temp->lastName==lastName))        
			return true;     
      else
		  temp = temp->next;
    }
    return false;
}

//Insert the parameter Employee at the head of the linked list.
//return true if it is inserted successfully and false otherwise
bool LinkedList::insertEmployee(string firstName, string lastName, int id, double salary)
{
    struct Employee* temp = new(struct Employee);
    temp->firstName=firstName;
    temp->lastName=lastName;
    temp->id=id;
    temp->salary=salary;
    temp->next=head;
    head=temp;
    return true;
}

//Delete the Employee with the given id from the linked list.
//Return true if it is deleted successfully and false otherwise
bool LinkedList::deleteEmployee(int id)//only Employee being found then it will be deleted, so I didn't change the signature here.
{
    struct Employee* temp = head;
    if(head->id==id){
      head=head->next;
      return true;
      }
    temp=head;
    while(temp->next!=NULL){
      if(temp->next->id==id){
      temp->next=temp->next->next;
      return true;
      }
      else
      temp=temp->next;
      }
     return false;
}

//This function displays the content of the linked list.
void LinkedList::displayList()
{
   struct Employee *temp = head;
   if(head == NULL)
   {
   	cout<<""<<endl;
   }
   else
   {
      while(temp != NULL)
      {
         cout << left    << setw(18) << temp->firstName
              << left    << setw(18) << temp->lastName
              << right   << setw(8)  << temp->id
              << setw(10) << fixed << setprecision(2) << temp->salary << "\n";
         temp = temp->next;
      }
   }
}