// Assignment: ASU CSE310 HW#3 Spring 2023
// Your Name:Jiandong Guan
// ASU ID:1220287159
// ASU Email address:jguan16@asu.edu
// Description:
//********************************************************
#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

// Each Employee has a unique id
struct Employee {
  string firstName, lastName;
  int id;
  double salary;
};

// class MaxHeap represents a max heap that contains Employee objects. The
// underline data structure is a one dimensional array of Employee.
class MaxHeap {
private:
  struct Employee *employeeArr; // an array of Employees
  int capacity, size;
struct Employee *tempArr;

public:
  MaxHeap(int capacity);
  ~MaxHeap();
  Employee *getEmployeeArr();
  int getSize();
  int getCapacity();
  int isFound(int anID);
  bool heapIncreaseID(int index, Employee oneEmployeeWithNewID);
  bool heapInsert(int id, string firstName, string lastName, double salary);
  void heapify(int index);
  Employee getHeapMax();
  void extractHeapMax();
  int leftChild(int parentIndex);
  int rightChild(int parentIndex);
  int parent(int childIndex);
  void printHeap();
};

// Constructor to dynamically allocate memory for a heap with the specified
// capacity
MaxHeap::MaxHeap(int capacity) {
  employeeArr = new Employee[capacity];
  this->capacity=capacity;
  size = 0;
}

// Destructor
// Before termination, the destructor is called to free the associated memory
// occupied by the heap. and prints the number of nodes deleted by it.
MaxHeap::~MaxHeap() {
  int employeeCount = size;
  delete [] employeeArr;
  cout << "\nThe number of deleted Employees is: " << employeeCount << endl;
}

Employee *MaxHeap::getEmployeeArr() { return employeeArr; }

int MaxHeap::getSize() { return size; }

int MaxHeap::getCapacity() { return capacity; }


int MaxHeap::isFound(int anID) {
  for (int i = 0; i < size; i++)
    if (employeeArr[i].id == anID)
      return i;
  return -1;
}

//*******************************************************************
// increase the Employee's id located at the specific index
bool MaxHeap::heapIncreaseID(int index, Employee oneEmployeeWithNewID) {
  if (index > getSize()) {
    cout << "\nIncrease id error: index out of range" << endl;
    return false;
  } 
  else {
    employeeArr[index]=oneEmployeeWithNewID;
    while (index > 0 &&
           employeeArr[parent(index)].id < oneEmployeeWithNewID.id) {
      employeeArr[index] = employeeArr[parent(index)];
      employeeArr[parent(index)] = oneEmployeeWithNewID;
      index=parent(index);
    }
    return true;
  }
}
bool MaxHeap::heapInsert(int id, string firstName, string lastName,double salary) {
  if(isFound(id)!=-1)
  {
    return false;
  }
  if (size == capacity) 
  {
    tempArr=new Employee[capacity];
    tempArr=employeeArr;
    employeeArr=new Employee[2 * capacity];
    for(int i=0;i<size;i++)
      { employeeArr[i]=tempArr[i];
        }
    cout << "\nReach the capacity limit, double the capacity now.\nThe new capacity "
            "now is "
         << 2 * capacity << endl;
    capacity=capacity*2;
  }
  size++;
  employeeArr[size-1].id = -10000;
  Employee temp = *new Employee();
  temp.id = id;
  temp.firstName = firstName;
  temp.lastName = lastName;
  temp.salary = salary;
    if(size==1)
  {
    employeeArr[0]=temp;
  }
  else
    {
  heapIncreaseID(size-1, temp);
      }
  return true;
}
void MaxHeap::heapify(int index) {
  int l = leftChild(index);
  int r = rightChild(index);
  int largest = index;
  if (l < size && employeeArr[l].id > employeeArr[index].id)
    largest = l;
  if (r < size && employeeArr[r].id > employeeArr[largest].id)
    largest = r;
  if (largest != index) {
    Employee temp = *new Employee();
    temp = employeeArr[index];
    employeeArr[index] = employeeArr[largest];
    employeeArr[largest] = temp;
    heapify(largest);
  }
}
Employee MaxHeap::getHeapMax() { 
  return employeeArr[0]; }
void MaxHeap::extractHeapMax() {
    employeeArr[0] = employeeArr[size-1];
    size--;
    heapify(0);
  
}
int MaxHeap::leftChild(int parentIndex) { return 2 * parentIndex+1; }
int MaxHeap::rightChild(int parentIndex) { return 2 * parentIndex+2; }
int MaxHeap::parent(int childIndex) { 
  if(childIndex%2==0)
    return childIndex/2-1;
  else
  return floor(childIndex / 2); }
void MaxHeap::printHeap() {
  if (size == 0)
    cout << "Empty heap, no elements" << endl;
  else
    cout << "Heap capacity = " << capacity << "\nHeap size = " << size << endl;
  for (int i = 0; i < size; i++) {
    cout << "\n" << endl;
    cout << left;
    cout << setw(8) << employeeArr[i].id << setw(12) << employeeArr[i].firstName
         << setw(12) << employeeArr[i].lastName << setw(8) << fixed
         << setprecision(2) << employeeArr[i].salary << endl;
  }
}