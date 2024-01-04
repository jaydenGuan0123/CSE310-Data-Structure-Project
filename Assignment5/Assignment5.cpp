// ASU CSE310 Assignment #5 Spring 2023
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: this is the main program that reads input from a text file,
// it then call hash functions to execute hash commands given in the input.

/*****************************************************************************
//(1)Describe here what is your hash function? How do you get an input Employee
//   object's hash value.
I use the first letter of first name ascii plus the id, then use the result modulo by the size of hash table.
//(2)Did your hash function work well? For each of the four test cases, list here
//   They all work well. 
//(3)If you had to change your hash function to reduce the number of collisions,
//   how will you change it?
// Using hash-by-multiplication.
********************************************************************************/

#include "Hash.h"
#include <sstream>
#include <cmath>


using namespace std;

//This function used to get an Employee key which is the combination of firstName, lastName and id
string getKey(string oneLine, string&firstName, string& lastName, int& id);
void getInfo(string oneLine, string&firstName, string& lastName, int& id,double& salary);
int main()
{
   int size = 0 ;
   int numOfCommand = 0;
   string firstName, lastName;
   int id;
   double salary;
   string oneLine;
   string commandLine;

   //declare any other necessary variables here
   //----

   cout << "Enter the size of the hash table: ";
   cin >> size;
   cin.ignore(20, '\n');

   Hash* hash=new Hash(size);
   int data=0;
   do {
         cin>>oneLine;
         if(oneLine=="InsertionEnd")
           break;
         getInfo(oneLine,firstName,lastName,id,salary);
         hash->hashInsert(firstName,lastName,id,salary);  
         data++;
   } while(true);

   cout << "\nEnter number of commands: ";   //***need to comment out in submitting
   cin >> numOfCommand;
   cin.ignore(20, '\n');

   for(int i= 0; i < numOfCommand; i++)
   {
    cin>>commandLine;
      if(commandLine.compare("hashDisplay") == 0)
      {
         hash->hashDisplay();
      }
      else if(commandLine.compare("hashLoadFactor")==0){
           double data1=data;
           double size1=size;
           double idealLoadFactor=data1/size1;
           double realLoadFactor=hash->hashLoadFactor();
           double performance=realLoadFactor/idealLoadFactor;
           cout<<"The ideal load factor is: "<<idealLoadFactor<<endl;
           cout<<"My hash table real load factor is: "<<realLoadFactor<<endl;
           cout<<"My hash table performance ratio is: "<<performance<<endl;
         }
      else  //more than one tokens, check the command name, extract the remaining tokens
      {
         string command=getKey(commandLine,firstName,lastName,id);
         if(command.compare("hashSearch")==0)
            bool search=hash->hashSearch(firstName,lastName,id);
            
         else  if(command.compare("hashDelete")==0)
            bool exit=hash->hashDelete(firstName,lastName,id);
            
         else
            cout<<"Invalid command"<<endl;
      }
   } //end for loop
   return 0;
}

//****************************************************************************************
//Given one line, this function extracts firstName, lastName, id info. of an Employee
//This function is completed and given here as a study guide for extracting tokens
string getKey(string oneLine, string& firstName, string& lastName, int& id){
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   string command = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());
   return command;

}

void getInfo(string oneLine, string&firstName, string& lastName, int& id,double& salary)
{
   string delimiter = ",";
   int pos=oneLine.find(delimiter);
   string token = oneLine.substr(0,pos);
   firstName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   lastName = token;
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   id = stoi(token);
   oneLine.erase(0, pos+delimiter.length());

   pos=oneLine.find(delimiter);
   token = oneLine.substr(0,pos);
   salary = stod(token);
   oneLine.erase(0, pos+delimiter.length());

}
