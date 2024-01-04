//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: //---- is where you should add your own code
//********************************************************************
// include necessary header file here
#include <string>
using namespace std;
#include "Graph.h"

void getCityInfo(string oneLine, string &depCityName,ArrivalCityList *arrCityList);
void getArrCityInfo(string oneArrCityInfo, string &arrCityName, int &distance);

int main() {
  int count; // a variable for number of nodes
  string oneLine, sourceCityName;
  string answer ="yes"; // a variable to decide whether to run Dijkstra multiple times

  // cout << "Enter number of cities: ";
  cin >> count;
  cin.ignore(20, '\n');

  // For each line of the file, we will create an ArrivalCityList(which is a
  // linked list) for a specific departure city. It represents all its reachable
  // arrival cities with distance info. Here we use an array of DepCity to store
  // them
  DepCity *depCityArr = new DepCity[count];

  // Initialize depCityArr. Set each node's d value to be very large 10000
  // initialize each arrival city list
  for (int i = 0; i < count; i++) {
    depCityArr[i].d =
        10000 + i; //***this is to make sure each node has different d value
    depCityArr[i].arrCityList=NULL;
    
  }

  // get input line by line and create the depCityArr
  for (int i = 0; i < count; i++) {
    getline(cin, oneLine);
    ArrivalCityList* arrCityList=new ArrivalCityList();
    getCityInfo(oneLine, depCityArr[i].depCityName, arrCityList);
    depCityArr[i].arrCityList=arrCityList;
  }

  // create a Graph object
  MinPriorityQueue *cityHeap = new MinPriorityQueue(count);
  for (int i = 0; i < count; i++) {
    cityHeap->insert(depCityArr[i]);
  }
  Graph *graph = new Graph(count, cityHeap);

  // print the graph adjacency list before running Dijkstra algorithm
  cout << "\nPrint the graph adjacency list before running Dijkstra algorithm"
       << endl;
  cityHeap->printHeap();
  cout<<"\n";
  // Next you need to design a sentinel value controlled while loop base on
  // answer If user answer is 'yes', get source city name, run Dijkstra
  // algorithm, print shortest path, then ask whether user want to continue or
  // not...
  answer="yes";
  while (answer == "yes") {
    cout<<"\nEnter source city name: "<<endl;
    getline(cin,sourceCityName);
    if(graph->findOneCity(sourceCityName)==-1)
      cout<<sourceCityName+" does NOT exist";
    else{
    cout<<"\n\nPrint the Dijkstra algorithm running result\n"<<endl;
    graph->printDijkstraPath(sourceCityName);
    }
    cout<<"\n\nFind shortest path for another departure city(yes or no): \n";
    getline(cin,answer);
  }
  cout<<"\nProgram terminate"<<endl;
}

//************************************************************************
// Give one line in input file, this function extract tokens and get departure
// city name and its arrival cities info.
void getCityInfo(string oneLine, string &depCityName,
                 ArrivalCityList *arrCityList) {
  string delimiter = ",";
  int pos = oneLine.find(delimiter);
  string token = oneLine.substr(0, pos);
  depCityName = token;
  oneLine.erase(0, pos + delimiter.length());
  string arrCityName;
  int distance;
  ArrivalCityList *temp = new ArrivalCityList();
  while (oneLine != ""&&pos!=0) {
    pos = oneLine.find(delimiter);
    token = oneLine.substr(0, pos);
    if(pos!=0){
    getArrCityInfo(token, arrCityName, distance);
    oneLine.erase(0, pos + delimiter.length());
    arrCityList->addArrCity(arrCityName, distance);
    }
  }
}

//****************************************************************************
// Given one arrival city info. format of, such as Z(60), this function
// extract arrival city name 'Z' and distance 60 from it.
// this function is optional. Feel free to extract tokens using your own way
void getArrCityInfo(string oneArrCityInfo, string &arrCityName, int &distance) {
  string leftParentheses = "(";
  string rightParentheses = ")";
  int pos = oneArrCityInfo.find(leftParentheses);
  string token = oneArrCityInfo.substr(0, pos);
  arrCityName = token;
  oneArrCityInfo.erase(0, pos + leftParentheses.length());
  pos = oneArrCityInfo.find(rightParentheses);
  token = oneArrCityInfo.substr(0, pos);
  distance = stoi(token);
}