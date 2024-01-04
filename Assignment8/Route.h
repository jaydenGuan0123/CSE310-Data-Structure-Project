//********************************************************************
// ASU CSE310 Spring 2023 Assignment #8
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: This route.h file
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//Site represents one vertex of the map
struct Site
{
    string siteName;
    int rank;
    struct Site* parent;

   //C++ don't provide a default constructor, need it here.
   Site()
   { siteName="";
     rank=0;
     parent=NULL;
   }

   //overloaded constructor
   Site(string name)
   {
     siteName=name;
     rank=0;
     parent=NULL;
   }
};

//Route represents one edge of the map which connects two historical sites of Rome
class Route
{
    private:
       struct Site* site1;
       struct Site* site2;
       double distance;

	public:
	   Route();
       Route(Site* site1, Site* site2, double distance);
       Site* getSite1();
       Site* getSite2();
       double getDistance();
       void printRoute();
};

Route::Route(){
    site1=NULL;
    site2=NULL;
    distance=300000;
}
Route::Route(Site* site1, Site* site2, double distance){
   this->site1=site1;
   this->site2=site2;
   this->distance=distance;
}
Site* Route::getSite1(){
   return site1;
}
Site* Route::getSite2(){
   return site2;
}
double Route::getDistance(){
  return distance;
}

void Route::printRoute()
{
   cout << left;
    cout << setw(33) << site1->siteName
         << setw(8) << "<--->"
         << setw(33) << site2->siteName
         << setw(3) << " = "
         << setw(8) << right << fixed << setprecision(1) << getDistance()
         << endl;
}