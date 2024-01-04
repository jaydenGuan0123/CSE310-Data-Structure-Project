//************************************************************************
// ASU CSE310 Assignment #8 Spring 2023
// ASU ID:1220287159
// Name:Jiandong Guan
// Description: this is the main program that reads input from keyboard,
// it then use disjoint set data structure to perform Kruskal MST algorithm
// on the graph.
#include "Map.h"
using namespace std;

void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance);
int main()
{
    //Maximum possible sites and route number
    const int MAX_SITE_NUM = 50, MAX_ROUTE_NUM = 100;
    int numOfSites = 0, numOfRoutes = 0;  //counter used to track actual number of sites and routes
   //create an array of Site which store all Site (vertex of the graph)
   Site* setOfSites =new Site[MAX_SITE_NUM];

   //create an array of Route which store all Route (edges of the graph)
   Route* setOfRoutes=new Route[MAX_ROUTE_NUM];

   //declare all necessary local variables here
   string delimiter = ",";
   string oneLine;
   int pos;
   string token;
   string depCityName;
   string arrSiteName;
   double distance;
   Site* aNewSite;
   Site* bNewSite;
   Route* aNewRoute;
   int ret=-1;
   getline(cin, oneLine);

   while(oneLine.compare("End") != 0)
   {
      //get one line of the input, extract the first token
      //create a Site object if it does not exist in site array,
      //insert it inside the site array. This will be first point of the 'aNewRoute'
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      depCityName = token;
      oneLine.erase(0, pos + delimiter.length());
     
      for(int i=0;i<numOfSites;i++){
        if(setOfSites[i].siteName==depCityName){
           ret=i;
        }
      }
     
      if(ret==-1)
      {
      aNewSite=new Site(depCityName);
      setOfSites[numOfSites]=*aNewSite;
      aNewSite=&setOfSites[numOfSites];
      numOfSites++;
      }
      else
      {
       aNewSite=&setOfSites[ret];
        ret=-1;
      }
     
      while (oneLine != ""&&pos!=0){
      //extract the arrival site info. check whether it exists in
      //site array or not, if not, create a new Site object, add it inside.
      //This site will be the second point of the 'aNewRoute'
      pos = oneLine.find(delimiter);
      token = oneLine.substr(0, pos);
      if(pos!=0){
      getArrSiteInfo(token, arrSiteName, distance);
       for(int i=0;i<numOfSites;i++)
        if(setOfSites[i].siteName==arrSiteName)
           ret=i;
        
      if(ret==-1){
      bNewSite=new Site(arrSiteName);
      setOfSites[numOfSites]=*bNewSite;
      bNewSite=&setOfSites[numOfSites];
      numOfSites++;
      }
      else
      {
       bNewSite=&setOfSites[ret];
        ret=-1;
      }
 //by using the two sites we got above, create a new route, add
      //it inside route array
      aNewRoute=new Route(aNewSite,bNewSite,distance);
      setOfRoutes[numOfRoutes]=*aNewRoute;
      numOfRoutes++;
      }
      oneLine.erase(0, pos + delimiter.length());
      }
      //get next line
      getline(cin, oneLine);
   } //repeat until the 'End'
   //Create a Map object by using site array and route array
    Map* map=new Map(numOfSites,numOfRoutes,setOfSites,setOfRoutes);
   cout << "Total historical sites you will visit: " << numOfSites << endl;
   //Run Kruskal MST algorithm on above map
   map->MST_Kruskal();
}

//****************************************************************
//By giving a string, for example 'Pantheon(300.5)', this function
//extract the arrival site 'Pantheon' and distance '300.5' meters
//Note: the delimiter is left and right parenthesis
//****************************************************************
void getArrSiteInfo(string oneArrSiteInfo, string& arrSiteName, double& distance)
{
   string leftParentheses = "(";
  string rightParentheses = ")";
  int pos = oneArrSiteInfo.find(leftParentheses);
  string token = oneArrSiteInfo.substr(0, pos);
  arrSiteName = token;
  oneArrSiteInfo.erase(0, pos + leftParentheses.length());
  pos = oneArrSiteInfo.find(rightParentheses);
  token = oneArrSiteInfo.substr(0, pos);
  distance = stod(token);
}
