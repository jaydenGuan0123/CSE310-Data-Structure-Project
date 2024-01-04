// Assignment: ASU CSE310 HW#3 Spring 2023
// Name:Jiandong Guan
// ASU ID:1220287159
// ASU Email Address:jguan16@asu.edu
// Description: This program displays a menu of choices to a user
//              and performs the chosen task. It will keep asking a user to
//              enter the next choice until the choice of 'Q' (Quit) is entered.
//             	//---- is where you should add your own code
//********************************************************************************

#include "MaxHeap.h"


using namespace std;

void printMenu();
void heapSort(MaxHeap* oneMaxHeap);

int main()
{
	char input1 = 'Z';
	int id;
  int newID;
	string firstName, lastName;
    double salary;
	int capacity;   //array capacity and index
	bool success = false;
  int result;
	//declare any other variables in case you need them
    Employee anEmployee;
    int index;
	// instantiate an empty Heap
	MaxHeap* heap1 = nullptr;
  Employee* a=nullptr;
	printMenu();

	do {
		cout << "\nWhat action would you like to perform?" << endl;
		cin.get(input1);
		input1 = toupper(input1);
		cin.ignore(20, '\n');	//flush the buffer

		// matches one of the cases
		switch (input1)
		{
			case 'C':	//create empty Heap with the relevant capacity
				cout << "\nPlease enter the heap capacity: ";
				cin >> capacity;
				cin.ignore(20, '\n');	//flush the buffer
        heap1=new MaxHeap(capacity);        
				break;

			case 'D':	//delete the heap, call the destructor explicitly
				cout << "\nDelete the heap" << endl;
				delete heap1;
				//re-initialize it with capacity 4
				heap1=new MaxHeap(4);
				break;

			case 'E':	//Extract the maximum node
                if (heap1 == nullptr)
                    cout << "\nEmpty heap, can NOT extract max" << endl;
                else
                {
                  cout<<"Before extract heap max operation:"<<endl;
                  heap1->printHeap();
                  heap1->extractHeapMax();
                  cout<<"After extract heap max operation:"<<endl;
                  heap1->printHeap();
                }
				break;

			case 'F':	//Find an Employee
				cout << "\nEnter the Employee id you want to search: ";
				cin >> id;
				cin.ignore(20, '\n');	//flush the buffer
        result=heap1->isFound(id);
        if(result==-1)
          cout<<"Employee with id: "<<id<<"is NOT found"<<endl;
        else
          cout<<"Employee with id: "<<id<<"is found"<<endl;
				break;

			case 'I':	//Insert an Employee
				cout << "\nEnter the Employee firstName: ";
				cin >> firstName;

				cout << "\nEnter the Employee lastName: ";
				cin >> lastName;

				cout << "\nEnter the Employee id: ";
				cin >> id;

				cout << "\nEnter the Employee salary: ";
				cin >> salary;
				cin.ignore(20, '\n');	//flush the buffer
       
    if(heap1->heapInsert(id,firstName,lastName,salary)==true)
    {cout<<"\nEmployee \""<<firstName<<" "<<lastName<<"\" is added";}
     else{
       cout<<"\nDuplicated Employee. Not added\n\nEmployee \""<<firstName<<" "<<lastName<<"\" is NOT added";
     }
				break;

			case 'K':	//increase the ID
				cout << "\nEnter the old employee id you want to increase: ";
				cin >> id;
				cout << "\nEnter the new employee id: ";
				cin >> newID;
				cin.ignore(20, '\n');	//flush the buffer
        if(id>newID)
        {
          cout<<"Increase ID error: new id is smaller than current id"<<endl;
        }
        else{
        index=heap1->isFound(id);
        if(index==-1)
        {cout<<"\nThe old ID you try to increase does not exist"<<endl;}
        else{
        if(heap1->isFound(newID)!=-1)
        {
          cout<<"The new ID you entered already exist, increase id operation failed"<<endl;
        }
        else{
          cout<<"\nBefore increase ID operation:"<<endl;
        heap1->printHeap();
        a=heap1->getEmployeeArr();
        a[index].id=newID;
        heap1->heapIncreaseID(index, a[index]);
        cout<<"Employee with old id: "<<id<<" is increased to new id: "<<newID<<"\n\nAfter increase id operation:"<<endl;
        heap1->printHeap();
          }
          }
          }
				break;
      
        case 'M':
          if(heap1->getHeapMax().id==0)
            cout<<"Empty heap, can NOT get max node"<<endl;
          else{
        cout<<"The maximum heap node is:\n"<<heap1->getHeapMax().id<<"    "<<heap1->getHeapMax().firstName<<"    "<<heap1->getHeapMax().lastName<<"    "<<heap1->getHeapMax().salary<<endl;
            }

				break;

			case 'P':	heap1->printHeap();

				break;

			case 'S':	//HeapSort
				cout << "\nHeap sort. Employees will be sorted in increasing order of their IDs" << endl;
			 heapSort(heap1);

				break;

			case 'Q':	//Quit
				delete heap1;
				break;

			case '?':	//Display Menu
				printMenu();
				break;

			default:
				cout << "Unknown action\n";
				break;
		}
	} while (input1 != 'Q');
	return 0;
}

//*****************************************************
//Given a max heap, we want to sort it in increasing order according to ID, put the
//sorting result inside another array and print it out
void heapSort(MaxHeap* oneMaxHeap)
{
    int size=oneMaxHeap->getSize();
        struct Employee *newArray =new Employee[size];
          for(int i=size-1;i>-1;i--)
            {
              struct Employee *oldArray=oneMaxHeap->getEmployeeArr();
               newArray[i]=oldArray[0];
               oneMaxHeap->extractHeapMax();
              }
            for (int i = 0; i < size; i++) {
    cout << "\n" << endl;
    cout << left;
    cout << setw(8) << newArray[i].id << setw(12) << newArray[i].firstName
         << setw(12) << newArray[i].lastName << setw(8) << fixed
         << setprecision(2) << newArray[i].salary << endl;
              }
}

//**The function displays the menu to a user**
void printMenu()
{
	cout << "Choice\t\tAction\n";
	cout << "------\t\t------\n";
	cout << "C\t\tCreate a heap\n";
	cout << "D\t\tDelete the heap\n";
	cout << "E\t\tExtract max node\n";
	cout << "F\t\tFind an Employee by ID\n";
	cout << "I\t\tInsert an Employee\n";
	cout << "K\t\tIncrease the ID\n";
	cout << "M\t\tGet the max node\n";
	cout << "P\t\tPrint the heap\n";
	cout << "S\t\tHeap Sort\n";
	cout << "Q\t\tQuit\n";
	cout << "?\t\tDisplay Help\n\n";
}