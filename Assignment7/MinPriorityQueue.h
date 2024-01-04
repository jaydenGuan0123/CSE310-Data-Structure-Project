 //********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: //---- is where you should add your own code
//********************************************************************

//include necessary header file here
//----
#include <string>
#include <cmath>
#include "ArrivalCityList.h"
using namespace std;

//Each node of the graph which is a departure City
struct DepCity
{
    string depCityName;
    int d;
    struct DepCity* pi;
    ArrivalCityList* arrCityList;
};

//class MinPriorityQueue represents a Min-heap that contains DepCity objects.
//The key of each DepCity is its d value.
class MinPriorityQueue
{
    private:
        struct DepCity* depCityArr;	        //a DepCity array
        int capacity, size;

	public:
        MinPriorityQueue(int capacity);
        ~MinPriorityQueue();

        DepCity* getDepCityArr();
        int getSize();
        int getCapacity();
        int isFound(string oneDepCityName);
        bool decreaseKey(int index, DepCity oneDepCityWithNewDValue);
        bool insert(DepCity oneDepCity);
        void heapify(int index);
        DepCity getHeapMin();
        void extractHeapMin();
        int leftChild(int parentIndex);
        int rightChild(int parentIndex);
        int parent(int childIndex);
        void printHeap();
        void build_min_heap();
};


//*********************************************************
void MinPriorityQueue::printHeap()
{

		cout << "\nHeap size = " << getSize() << "\n" << endl;
		cout << left;
		cout << setw(15) << "Dep. City"
             << setw(12)<<"d Value"
             << setw(15) << "PI"
             << "Arrival City List";
  for (int i = 0; i < size; i++) {
      cout<<"\n"<< setw(15)<<depCityArr[i].depCityName<< setw(12)<<depCityArr[i].d<<setw(15)<<"No Parent";
      if(depCityArr[i].arrCityList==NULL)
        cout<<"Arrival city list is empty";
    else
      depCityArr[i].arrCityList->printArrCityList();
    }
}

 MinPriorityQueue::MinPriorityQueue(int capacity){
   depCityArr=new DepCity[capacity];
   this->capacity=capacity;
   size=0;
 }

 MinPriorityQueue::~MinPriorityQueue(){
   delete[] depCityArr;
 }

DepCity* MinPriorityQueue::getDepCityArr(){
  return depCityArr;
}

int MinPriorityQueue::getSize(){
  return size;
}

int MinPriorityQueue::getCapacity(){
  return capacity;
}

int MinPriorityQueue::isFound(string oneDepCityName){
  for(int i=0;i<size;i++)
    if(depCityArr[i].depCityName==oneDepCityName)
      return i;
  return -1;
}

bool MinPriorityQueue::decreaseKey(int index, DepCity oneDepCityWithNewDValue){
   if(index>=getSize()){
     cout<<""<<endl;
     return false;
   }
  else{
  depCityArr[index]=oneDepCityWithNewDValue;
  while (index > 0 &&depCityArr[parent(index)].d > oneDepCityWithNewDValue.d) {
      depCityArr[index] = depCityArr[parent(index)];
      depCityArr[parent(index)] = oneDepCityWithNewDValue;
      index=parent(index);
    }
    return true;
}
}

//************************************************************
//when you create the dummy node, initialize its d value to be
//30000 which represents infinite
bool MinPriorityQueue::insert(DepCity oneDepCity){
  if(isFound(oneDepCity.depCityName)!=-1){
    cout<<""<<endl;
    return false;
  }
   if (size == capacity) 
  {
    DepCity* tempArr=new DepCity[capacity];
    tempArr=depCityArr;
    depCityArr=new DepCity[2 * capacity];
    for(int i=0;i<size;i++)
      { depCityArr[i]=tempArr[i];
        }
    cout << "\nReach the capacity limit, double the capacity now.\nThe new capacity "
            "now is "
         << 2 * capacity << endl;
    capacity=capacity*2;
  }
  size++;
  DepCity temp=*new DepCity();
  temp=oneDepCity;
  temp.d=30000;
  depCityArr[size-1]=temp;
  if(size!=1)
    decreaseKey(size-1, oneDepCity);
  else
    depCityArr[0]=oneDepCity;
  return true;
}

void MinPriorityQueue::heapify(int index){
  int l=leftChild(index);
  int r=rightChild(index);
  int smallest=index;
  if(l<size&&depCityArr[l].d<depCityArr[index].d)
    smallest=l;
  if(l<size&&depCityArr[l].d==depCityArr[index].d)
    if(depCityArr[l].depCityName<depCityArr[index].depCityName)
      smallest=l;
  if(r<size&&depCityArr[r].d<depCityArr[smallest].d)
    smallest=r;
  if(l<size&&depCityArr[r].d==depCityArr[index].d)
    if(depCityArr[r].depCityName<depCityArr[index].depCityName)
      smallest=r;
  if(smallest!=index){
    DepCity temp=*new DepCity();
    temp=depCityArr[index];
    depCityArr[index]=depCityArr[smallest];
    depCityArr[smallest]=temp;
    heapify(smallest);
  }
}

DepCity MinPriorityQueue::getHeapMin(){
  return depCityArr[0];
}

void MinPriorityQueue::extractHeapMin(){
  depCityArr[0]=depCityArr[size-1];
  size--;
  heapify(0);
}

int MinPriorityQueue::leftChild(int parentIndex){
  return 2 * parentIndex+1;
}

int MinPriorityQueue::rightChild(int parentIndex){
  return 2 * parentIndex+2;  
}

int MinPriorityQueue::parent(int childIndex){
  if(childIndex%2==0)
     return childIndex/2-1;
  else
     return floor(childIndex / 2); 
}

void MinPriorityQueue::build_min_heap(){
  
}