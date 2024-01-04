//********************************************************************
// ASU CSE310 Spring 2023 Assignment #8
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: This is the header file that defines an undirected graph
//              with an array of sites and routes
//********************************************************************

//include necessary header file here
//----
#include "Route.h"
using namespace std;
class Map
{
   private:
      int numOfSites, numOfRoutes;
      Site* setOfSites;   //an array of Site. Note: you are NOT allowed to change it to Site**
      Route* setOfRoutes; //an array of Route. Note: you are NOT allowed to change it to Route**

   public:
      Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray);
     ~Map();
      void make_set(Site* oneSite);
      Site* find_set(Site* oneSite);
      void link(Site* aSite, Site* bSite);
      void Union(Site* aSite, Site* bSite);
      void sortRoutes();
      void MST_Kruskal();
};
Map::Map(int numOfSites, int numOfRoutes, Site* siteArray, Route* routeArray){
  this->numOfRoutes=numOfRoutes;
  this->numOfSites=numOfSites;
  this->setOfSites=siteArray;
  this->setOfRoutes=routeArray;
}
Map::~Map(){
  numOfRoutes=0;
  numOfSites=0;
  delete [] setOfSites;
  delete [] setOfRoutes;
}
void Map::make_set(Site* oneSite){
  oneSite->parent=oneSite;
  oneSite->rank=0;
}
Site* Map::find_set(Site *oneSite){
  if(oneSite->parent!=oneSite)
    oneSite->parent=find_set(oneSite->parent);
  return oneSite->parent;
}
void Map::link(Site* aSite, Site* bSite){
  if((aSite->rank)>(bSite->rank)){
    bSite->parent=aSite;
  }
  else{
    aSite->parent=bSite;
    if((aSite->rank)==(bSite->rank))
    (bSite->rank)++;
  }
}
void Map::Union(Site* aSite, Site* bSite){
   link(find_set(aSite),find_set(bSite));
}
//insertion sort
void Map::sortRoutes(){
  Route key;
  int j;
  for(int i=1;i<numOfRoutes;i++){
    key=setOfRoutes[i];
    j=i-1;
    while(j>=0&&setOfRoutes[j].getDistance()>key.getDistance()){
      setOfRoutes[j + 1] = setOfRoutes[j];
            j = j - 1;
        }
    setOfRoutes[j + 1] = key;
  }
}
//*******************************************************************
//This function performs the Kruskal algorithm on the graph
void Map::MST_Kruskal()
{
   cout << "\nMST Kruskal Algorithm Result\n" << endl;
   double totalDistance = 0.0;
   Route* temp =new Route[numOfRoutes];
   for(int i=0;i<numOfRoutes;i++){
     make_set(setOfRoutes[i].getSite1());
     make_set(setOfRoutes[i].getSite2());
   }
   sortRoutes();
   int a=0;
   for(int i=0;i<numOfRoutes;i++){
     if(find_set(setOfRoutes[i].getSite1())!=find_set(setOfRoutes[i].getSite2())){
        temp[a]=setOfRoutes[i];
        a++;
        Union(setOfRoutes[i].getSite1(),setOfRoutes[i].getSite2());
        totalDistance=totalDistance+setOfRoutes[i].getDistance();
     }
   }
  
  for(int i=0;i<a;i++){
   temp[i].printRoute();
  }

   cout << "=====================================================================================" << endl;
    cout << "Total Distance: " << totalDistance << " meters" << endl;
}