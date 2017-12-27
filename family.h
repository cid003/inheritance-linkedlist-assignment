// CS211
// Created by Mariah Cid on 12/2/2017
//-------------------------------------

#ifndef FAMILY_H
#define FAMILY_H
#include <iostream>
#include <string>
using namespace std;

class Husband;
class Wife;
class Child;
class Person;
class Family;
//---------------------------
typedef Husband* husbandptr;
typedef Wife* wifeptr;
typedef Child* childptr;
//---------------------------
class Family
{
  friend class Person;

  husbandptr top = NULL; //top exists here NULL?
  husbandptr end = NULL;
  static bool success;
  static bool failure;

 public:
  bool processTransactionfile();
  bool addHusband(long id, string fn, string ln);
  bool addWife(long id, string fn, string ln, long HusbandSSN);
  bool addChild(long id, string fn, string ln, long papaSSN);
  bool removeHusband(long id);
  bool removeWife(long HusbandSSN);
  bool removeChild(long papaSSN, long childSSN);
  bool printAllFamilies();
  bool printFamily(long papaSSN);
  bool checkhusband(long id);
  bool checkwife(long id);
};
//---------------------------
class Person
{
  friend class Family;
 protected:
  long SSN;
  string fname;
  string lname;

 public:
  Person();//{SSN = 0; fname = lname = " ";}; //???? write it here?
  Person(long id, string fn, string ln);//{SSN = id; fname = fn; lname = ln;}
};
//-----------------------------
class Husband:public Person
{
  friend class Family;

 protected:
  husbandptr nextFamily;
  wifeptr mywife;

 public:
  Husband(); //ssn = 0, fname=lname=" "; nextFamily = mywife = NULL
  Husband(long id, string fn, string ln); //ssn = id, fname = fn, lname = ln, nextFamily=mywife=NULL
};
//-------------------------------
class Wife:public Person
{
  friend class Family;

 protected:
  childptr mychild;

 public:
  Wife(); //ssn =0, fname = lname= " "; mychild = NULL
  Wife(long id, string fn, string ln); //ssn = id, fname = fn, lname=ln, mychild = NULL
};
//----------------------------------
class Child:public Person
{
  friend class Family;

 protected:
  childptr mysibling;

 public:
  Child();
  Child(long id, string fn, string ln); //mysibling = NULL
};
//----------------------------------
#endif //FAMILY_H
