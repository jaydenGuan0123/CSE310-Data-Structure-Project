// ASU CSE310 Assignment #5 Spring 2023
// Name of Author:Jiandong Guan
// ASU ID:1220287159
// Description: this is where you need to design functions on Hash hashTable,
// such as hashInsert, hashDelete, hashSearch and hashDisplay
// ---- is where you should add your own code

#include "LinkedList.h"

using namespace std;
#include<iostream>
#include<sstream>
class Hash
{
   private:
      LinkedList* hashTable;     //hashTable is a one-dimensional array of LinkedList
      int m;                     //slots number of the hash table
	public:
      Hash(int size);
      ~Hash();
      bool hashSearch(string firstName, string lastName, int id);
      bool hashInsert(string firstName, string lastName, int id, double salary);
      bool hashDelete(string firstName, string lastName, int id);
      int hashLoadFactor();
      void hashDisplay();
      int hashFunction(string key);
  };

//constructor
Hash::Hash(int size)
{
   hashTable=new LinkedList[size];
   m=size;
}

//Destructor
Hash::~Hash()
{
   delete[] hashTable;
}

//This function searches for a key inside the hash table and
//return true if it is found and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashSearch(string firstName, string lastName, int id)
{
   bool found = false;
   string key=firstName+" "+lastName+" "+to_string(id);
   found=hashTable[hashFunction(key)].searchEmployee(firstName,lastName,id);
   if (found == true){
      cout << "\n" << left
          << setw(18) << firstName
          << setw(18) << lastName
          << setw(8)  << id
          << " is found inside the hash table." << endl;}
        
   else{
      cout << "\n" << left
           << setw(18) << firstName
           << setw(18) << lastName
           << setw(8)  << id
           << " is NOT found inside the hash table." << endl;}
    return found;
}

//hashInsert inserts an Employee with the relevant info. into the hashTable.
//it returns true if the data is inserted successfully and false otherwise
bool Hash::hashInsert(string firstName, string lastName, int id, double salary)
{
   bool insert;
   string key=firstName+" "+lastName+" "+to_string(id);  insert=hashTable[hashFunction(key)].insertEmployee(firstName,lastName,id,salary);
   return insert;
}

//hashDelete deletes an Employee with the relevant key from the hashTable.
//it returns true if it is deleted successfully and false otherwise
//Note: key is the combination of firstName, lastName and id
bool Hash::hashDelete(string firstName, string lastName, int id)
{     
      bool delete1;
      bool found1;
      string key=firstName+" "+lastName+" "+to_string(id);
    
  found1=hashSearch(firstName, lastName,id);
  if(found1==true){
  delete1=hashTable[hashFunction(key)].deleteEmployee(id);
    if(delete1==true){
      cout << "\n";
      cout << setw(18) << firstName
           << setw(18) << lastName
           << setw(8)  << id
           << " is deleted from hash table." << endl;
      }
    return true;
    }
    else{
      cout << "\n";
      cout << setw(18) << firstName
           << setw(18) << lastName
           << setw(8)  << id
           << " is NOT deleted from hash table." << endl;
      return false;
      }
}

//This function computes your hash table real load factor
//it is the longest linked list size
int Hash::hashLoadFactor()
{
  int linkedlistsize=0;
  for(int i=0;i<m;i++){
      if(hashTable[i].getSize()>linkedlistsize)
        linkedlistsize=hashTable[i].getSize();
    }
  return linkedlistsize;
}

//This function prints all elements from the hashTable.
void Hash::hashDisplay()
{
   for(int i=0;i<m;i++){
      cout<<"HashTable["<<i<<"], size = "<<hashTable[i].getSize()<<endl;
      hashTable[i].displayList();
    }
}

//This is the hash function you need to design. Given a
//string key, the function should return the slot number
//where we should hash the key to
int Hash::hashFunction(string key)
{
   char firstLetter=key.at(0);
   int num=int(firstLetter);
   stringstream str_strm;
   str_strm << key;
   string temp_str;
   int temp_int;
    while(!str_strm.eof()) {
      str_strm >> temp_str; //take words into temp_str one by one
      if (stringstream(temp_str) >> temp_int)//try to convert string to int
      {
        return (temp_int+num)%m;
        }
}
  return (temp_int+num)%m;
}