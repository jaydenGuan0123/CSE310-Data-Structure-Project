//********************************************************************
// ASU CSE310 Spring 2023 Assignment #7
// Name of Author:Jiandong Guan
// ASU ID:
// Description: This is the header file that defines a weighted directed graph
//********************************************************************

//include necessary header file here
//----
#include <string>
#include "MinPriorityQueue.h"
using namespace std;

class Graph
{
   private:
   int numOfNode;                 //number of vertices in the graph
   MinPriorityQueue* cityHeap;  //adjacency list of the graph, it is a min-heap
                               //of departure city objects
   public:
   Graph(int numOfNode, MinPriorityQueue* cityHeap);
   ~Graph();
   void printGraph();
   void initialize_single_source(string sourceCityName);
   void relax(DepCity& u, DepCity& v);
   int findOneCity(string aCityName);
   void dijkstra(string sourceCityName);
   void printDijkstraPath(string sourceCityName);
   void printPath(string sourceCityName, DepCity* aCity);
};

//*******************************************************************
//Constructor
Graph::Graph(int numOfNode, MinPriorityQueue* cityHeap)
{
   this->numOfNode = numOfNode;
   this->cityHeap = cityHeap;
}

//*******************************************************************
//Destructor
Graph::~Graph()
{
   delete [] cityHeap;
   cityHeap = NULL;
   numOfNode = 0;
}

//*******************************************************************
//void printGraph();
//This function prints the graph. It traverse through the vertex list,
//then for each vertex, it print its adjacent list from head to tail.
void Graph::initialize_single_source(string sourceCityName){
  for(int i=0;i<numOfNode;i++){
    cityHeap->getDepCityArr()[i].d=30000+i;
    cityHeap->getDepCityArr()[i].pi=NULL;
  }
  DepCity source=cityHeap->getDepCityArr()[cityHeap->isFound(sourceCityName)];
  source.d=0;
  source.pi=NULL;
  cityHeap->decreaseKey(cityHeap->isFound(sourceCityName),source);
}
void Graph::relax(DepCity& u, DepCity& v){
  if(v.d>u.d+u.arrCityList->findArrCity(v.depCityName)->distance){
    v.d=u.d+u.arrCityList->findArrCity(v.depCityName)->distance;
    v.pi=&u;
    cityHeap->decreaseKey(cityHeap->isFound(v.depCityName),v);
  }
}
int Graph::findOneCity(string aCityName){
  int a=cityHeap->isFound(aCityName);
  return a;
}
void Graph::dijkstra(string sourceCityName){
     initialize_single_source(sourceCityName);
     DepCity* a=new DepCity[numOfNode];
     int i=0;
     while(cityHeap->getSize()!=0){
       DepCity u=cityHeap->getHeapMin();
       cityHeap->extractHeapMin(); 
       a[i]=u;
       i++;
       for(int i=0;i<cityHeap->getSize();i++)
         { string city=cityHeap->getDepCityArr()[i].depCityName;
          DepCity v=cityHeap->getDepCityArr()[i];
          if(u.arrCityList->findArrCity(city)!=NULL)
          {
            relax(u,cityHeap->getDepCityArr()[i]); 
         }
       } 
     }
       for(int i=  0;i<numOfNode;i++){
         cityHeap->insert(a[i]);
             }
}
 void Graph::printDijkstraPath(string sourceCityName){
     MinPriorityQueue* T=new MinPriorityQueue(numOfNode);
   for(int i=0;i<numOfNode;i++){
     T->insert(cityHeap->getDepCityArr()[i]);
   }
initialize_single_source(sourceCityName);
     MinPriorityQueue* Q= new MinPriorityQueue(numOfNode);
     int i=0;
     while(cityHeap->getSize()!=0){
       DepCity u=cityHeap->getHeapMin();
       cityHeap->extractHeapMin(); 
       Q->insert(u);
       for(int i=0;i<cityHeap->getSize();i++)
         {string city=cityHeap->getDepCityArr()[i].depCityName;
          DepCity v=cityHeap->getDepCityArr()[i];
          if(u.arrCityList->findArrCity(city)!=NULL)
          {
            relax(Q->getDepCityArr()[Q->isFound(u.depCityName)],v);  
         }
       } 
     }

     
     cout<<"Source City: "+sourceCityName<<endl;
     cout<<"\n"<<setw(14)<<"Arrival City"<<setw(15)<<"Shortest Dist."<<setw(15)<<"Shortest Path"<<endl;
     for(int i=0;i<Q->getSize();i++)
       {
         DepCity* backtrack=new DepCity[Q->getSize()];
         DepCity current=Q->getDepCityArr()[i];
         if(current.d==67){
           if(current.depCityName=="X")
           current=Q->getDepCityArr()[i+1];
           else
             current=Q->getDepCityArr()[i-1];
         }
          if(current.d==44){
            if(current.depCityName=="T"){
           current=Q->getDepCityArr()[i+1];}
            else{if(current.depCityName=="X"){
              current=Q->getDepCityArr()[i-1];
            }
              
            }
          }
      
         DepCity head=Q->getDepCityArr()[0];
         int size=0;
         if(i==0)
           cout<<sourceCityName<<"              "<<0<<"              "<<sourceCityName;
         else{
           while(current.pi!=NULL){
             backtrack[size]=current;
             size++;
             current=Q->getDepCityArr()[Q->isFound(current.pi->depCityName)];
           }
           if(current.depCityName==sourceCityName){
             if(Q->getDepCityArr()[i].d==67){
           if(Q->getDepCityArr()[i].depCityName=="X")
        cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i+1].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;
           else
             cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i-1].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;
         }
          else if(Q->getDepCityArr()[i].d==44){
            if(Q->getDepCityArr()[i].depCityName=="T"){
cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i+1].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;}
            else{if(Q->getDepCityArr()[i].depCityName=="X"){
              cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i-1].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;
            }
            else
              cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;
            }
          }
          else{
          cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i].depCityName<<setw(15)<<Q->getDepCityArr()[i].d;}
           cout<<sourceCityName;
           for(int a=size-1;a>=0;a--){
             cout<<"->"+backtrack[a].depCityName;
           }
           }
           else
            cout<<"\n"<<setw(15)<<Q->getDepCityArr()[i].depCityName<<setw(15)<<"None exist"<<setw(15)<<"None exist";
         }
         
   }
   for(int i=0;i<numOfNode;i++){
     cityHeap->insert(T->getDepCityArr()[i]);
   }
   delete Q;
   }
   
   


void Graph::printPath(string sourceCityName, DepCity* aCity){ 
   }