//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: //---- is where you should add your own code
//********************************************************************

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//struct ArrCity represents an arrival city information with
//distance info. from a specific departure city
struct ArrCity
{
    string arrCityName;
    int distance;
    struct ArrCity* next;
};

//class ArrivalCityList is a linked list of ArrCity
class ArrivalCityList
{
    private:
        struct ArrCity* head;

    public:
        ArrivalCityList();
        ~ArrivalCityList();
        ArrCity* getHead();
        ArrCity* findArrCity(string oneCity);
        bool addArrCity(string oneCity, int distance);
        void printArrCityList();
};
ArrivalCityList::ArrivalCityList(){
  head=NULL;
}
ArrivalCityList::~ArrivalCityList(){
  struct ArrCity* temp;
  int city=0;
  while(head!=NULL){
    temp=head;
    head=head->next;
    free(temp);
    city++;
  }
}
ArrCity* ArrivalCityList::getHead(){
  return head;
}
//*******************************************************************
//ArrCity* findArrCity(string oneCity);
//A function to find whether the parameterized city is inside the LinkedList or not.
//returns a pointer that points to the city if it exist, otherwise return NULL
//*******************************************************************
ArrCity* ArrivalCityList::findArrCity(string oneCity){
  struct ArrCity* temp =new(struct ArrCity);
  temp=head;
  while(temp!=NULL&&temp->arrCityName!=oneCity){
    temp=temp->next;
  }
  return temp;
}
//bool addArrCity(string oneCity, int distance);
//Creates a new ArrCity and inserts it into the list at the right place.
//It also maintains an alphabetical ordering of the ArrCities while inserting
//it into the list. Note: you cannot insert duplicated ArrCity
//Return value: true if it is successfully inserted and false in case of failures.
bool ArrivalCityList::addArrCity(string oneCity, int distance){
  struct ArrCity* temp=new(struct ArrCity);
  struct ArrCity* current=new(struct ArrCity);
  current=head;
  temp->arrCityName=oneCity;
  temp->next=NULL;
  temp->distance=distance;
  if(temp==findArrCity(oneCity)){
    cout<<"it already exits"<<endl;
    return false;
  }
  else{
    if(head==NULL)
      head=temp;
    else if(oneCity.compare(head->arrCityName)<0){
      temp->next=head;
      head=temp;
    }
    else{
    while(current->next!=NULL&&oneCity.compare(current->next->arrCityName)>0)
      {
          current=current->next;
      }
    if(current->next==NULL)
    {
      current->next=temp;
      return true;
    }
    else
      temp->next=current->next;
      current->next=temp;
  }
    return true;
  }
}
void ArrivalCityList::printArrCityList(){
  struct ArrCity* current=head;
  if(head==NULL){
    cout<<"Arrival city list is empty";
  }
  while(current!=NULL)
    {
      cout<<current->arrCityName<<"("<<current->distance<<"),";
      current=current->next;
    }
}