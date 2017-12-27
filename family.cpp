// CS211
// Created by Mariah on 12/2/2017.
//-------------------------------------
#include "family.h"
#include <fstream>
#include <utility>
using namespace std;
Person::Person()
{
  SSN = 0;
  fname = lname = " ";
}
//----------------------------------------------------------------
Person::Person(long id, string fn, string ln)
{
  SSN = id; 
  fname = fn;
  lname = ln;
}
//----------------------------------------------------------------
Husband::Husband()
{
  SSN = 0;
  fname = lname = " ";
  nextFamily = NULL; //placed in very beginning
  mywife = NULL; //placed in very beginning
}
//----------------------------------------------------------------
Husband::Husband(long id, string fn, string ln):Person(id, fn, ln)
{
  nextFamily = NULL;
  mywife = NULL;
}
//----------------------------------------------------------------
Wife::Wife()
{
  SSN = 0;
  fname = lname = " ";
  mychild = NULL; //placed in very beginning
}
//----------------------------------------------------------------
Wife::Wife(long id, string fn, string ln):Person(id, fn, ln)
{
  mychild = NULL;
}
//----------------------------------------------------------------
Child::Child()
{
  SSN = 0;
  fname = lname = " ";
  mysibling = NULL; //placed in very beginning
}
//----------------------------------------------------------------
Child::Child(long id, string fn, string ln):Person(id, fn, ln)
{
  mysibling = NULL;
}
//-------------------------------------------------
//begin coding the transaction stuff here
//-------------------------------------------------
bool Family::success = true;
bool Family::failure = false;

/*--------------------------------------------------------------------------------
 * adding a husband based off of assigning the husband id and pointing to its destination
 */
bool Family::addHusband(long id, string fn, string ln)
{
  //first check if husband exists
  if(top == NULL)
    {
      husbandptr newHus = new Husband(id, fn, ln);
      newHus->nextFamily = NULL; //top
      top = newHus;
      end = top;

      return Family::success;
    }
  if(!checkhusband(id))
    {
      cout << "This husband exists already"<< endl;
      return Family::failure;
    }
  
  //if husband doesn't exist, adding method is shown below
  husbandptr newHus = new Husband(id, fn, ln);
  end->nextFamily = newHus;
  end = end->nextFamily;
 

  return Family::success;
}
/*
 * checkhusband checks negatively for the husband id----------------------------------------
 */
bool Family::checkhusband(long id)
{
  husbandptr p = top;
  while(p != NULL) //this runs while top exists and is not null
    {
      if(id == p->SSN) //not ssn?
        {
	  return Family::failure; //husband exists
        }
      
      p = p->nextFamily;

    }//end of while loop
  return Family::success; //return this if husband doesn't exist
}
/*
 * adding the wife function here------------------------------------------------------------
 */
bool Family::addWife(long id, string fn, string ln, long HusbandSSN)
{
  husbandptr p = top;
  wifeptr h;
  if(checkhusband(HusbandSSN))
    {
      cout<<"This wife's husband doesn't exist." <<endl; //referencing Ana Tarr's supposedly husband ID, which doesn't exist
      return Family::failure;
    }
  //adding function is below
  while(p != NULL)
    {
      if(p->SSN == HusbandSSN)
        {
	  h = new Wife(id, fn, ln); //make a new wife
	  p->mywife = h; //add info into this pointer
	  return Family::success;
        }

      p = p->nextFamily; //move onto next info

    }//end of while loop
  return Family::failure;
}
/*
 * check if the wife exists through her id?-------------------------------------------------
 */
bool Family::checkwife(long id)
{
  husbandptr p = top;
  wifeptr h;
  while(p != NULL) //run this while top exists
    {
      if(p->SSN == id)
        {
	  h = p->mywife;
	  if(h == NULL)
            {
	      return Family::failure; //return false if wife doesn't exist
            }
        }
      p = p->nextFamily;

    }//end of while loop
  return Family::success; //return true if the wife exists
}
/*
 * adding a child to the list---------------------------------------------------------------
 */
bool Family::addChild(long id, string fn, string ln, long papaSSN)
{
  husbandptr p = top;
  wifeptr h;
  childptr q;

  //check if dad exists
  if(checkhusband(papaSSN))
    {
      cout<<"This kid's dad doesn't exist"<<endl;
      return Family::failure;
    }
  //check if the mom exists
  if(!checkwife(papaSSN))
    {
      cout<<"This kid's mom doesn't exist"<<endl;
      return Family::failure;
    }

  //adding child method is shown below
  while(p != NULL)
    {
      if(p->SSN == papaSSN)
        {
	  q = new Child(id, fn, ln); //make a new child here
	  h = p->mywife;
	  
	  if(h->mychild == NULL)
            {
	      h->mychild = q; //child can be added here for the first child
	      return Family::success;
            }

	  //the sibling of the childptr counts as a child to the wifeptr
	  childptr t = h->mychild; //for every next child, this process does tihs
	  while(t->mysibling != NULL)
            {
	      //add child at the end of "t"
	      t = t->mysibling;
            }
	  
	  t->mysibling = q;
	  return Family::success;
        }

      p = p->nextFamily;
    }//end of while loop
}
/*
 * removehusband function goes here--------------------------------------------------------
 */
bool Family::removeHusband(long id)
{
  //check if the husband exists
  if(!checkhusband(id))
    {
      return Family::failure;
    }

  //check if the wife exists?
  if(!checkwife(id))
    {
      removeWife(id);
    }

  //removing function is shown below
  husbandptr p = top;
  husbandptr next;
  husbandptr prev;

  if(p == NULL) //check if top exists, if not, then autofail
    {
      return Family::failure;
    }
  else if(p->nextFamily == NULL) //assuming this is the last data type in line
    {
      delete p;
      p = NULL;
      return Family::failure;
    }
  else
    {
      next = p->nextFamily;
      prev = p;
      p = p->nextFamily;
    }
  next = p->nextFamily;
  delete p;

  prev->nextFamily = next;
  return Family::success; //return this when process is completed
}
/*
 *remove wife function is below-------------------------------------------------------------
 */
bool Family::removeWife(long HusbandSSN)
{
  //check if wife's husband exists, if not, don't do anything
  if(!checkhusband(HusbandSSN))
    {
      cout<<"This wife's husband doesn't exist"<<endl;
      return Family::failure;
    }

  //check if the wife herself exists
  if(!checkwife(HusbandSSN)) //using long variable type
    {
      cout<<"This wife doesn't exist"<<endl;
      return Family::failure;
    }

  //removing wife method is shown below
  husbandptr p = top;
  wifeptr h;
  childptr q;
  childptr qq; //sibling child
  while(p != NULL)
    {
      if(p->SSN == HusbandSSN)
        {
	  h = p->mywife;
	  if(h != NULL)
            {
	      q = h->mychild;
	      
	      while(q != NULL)
                {
		  qq = q->mysibling;
		  h->mychild = qq;
		  delete q;
		  q = qq;

                }//end of while loop
	      
	      delete h;
	      p->mywife = NULL;
            }
        }
      p = p->nextFamily;
    }
}
/*
 * removing child function here-------------------------------------------------------------
 */
bool Family::removeChild(long papaSSN, long childSSN)
{
  //check if dad exists
  if(checkhusband(papaSSN))
    {
      return Family::failure;
    }
  //check if mom exists
  if(!checkwife(papaSSN))
    {
      return Family::failure;
    }

  //removing function is shown below
  husbandptr p = top;
  wifeptr h;
  childptr q;
  childptr qq; //sibling child
  while(p != NULL)
    {
      if(p->SSN == papaSSN)
        {
	  h = p->mywife;
	  if(h != NULL)
            {
	      q = h->mychild;
	      qq = q;
	      
	      while(q->mysibling != NULL)
                {
		  if(q->SSN == childSSN)
                    {
		      qq = q->mysibling;
		      h->mychild = qq;
		      delete q;
		      cout << "A child has been deleted" << endl;
		      return Family::success; //return this if the child is deleted
                    }
		  q = q->mysibling;
                }
            }
        }
      p = p->nextFamily;
    }
  cout << "The child's ID doesn't exist or no child has been deleted " <<endl;
  return Family::failure;
}
/*
 * print one family only--------------------------------------------------------------------
 */
bool Family::printFamily(long papaSSN)
{
  husbandptr p = top;
  wifeptr h;
  childptr q;

  //if check passes, do this:
  while(p != NULL)
    {
      if(p->SSN == papaSSN)
        {
	  cout << "--------------------------------------------------------------------------------"<< endl;
	  cout << "Husband ID: " << p->SSN << "\t" << "First name:" << p->fname << "\t" << "Last Name:" << p->lname << "\t" << endl;
	  cout << endl;
	  
	  if (p->mywife != NULL)
            {
	      h = p->mywife;
	      cout << "--------------------------------------------------------------------------------" << endl;
	      cout << "Wife ID: " << h->SSN << "\t" << "First name:" << h->fname << "\t" << "Last Name:" << h->lname << "\t" << endl;
	      cout << endl;
	      
	      q = h->mychild;
	      int count = 1;
	      while (q != NULL)
                {
		  cout << "--------------------------------------------------------------------------------"<< endl;
		  cout << "Child Info#" << count << ":" << " Child ID: " << q->SSN << "\t" << "First name:" << q->fname << "\t" << "Last Name:" << q->lname << "\t"<< endl;
		  cout << endl;
		  
		  count++; //incriment the amount of children in the list
		  q = q->mysibling; //go to next child
                }
            }
        }
      p = p->nextFamily;
    }//end of main while loop
}
/*
 * gotta print all the families here.-----------------------------------------------------
 */
bool Family::printAllFamilies()
{
  cout << "===========================Printing All Families here=============================="<<endl;
  husbandptr p = top;

  while(p != NULL)
    {
      long ssn = p->SSN;
      printFamily(ssn);
      p = p->nextFamily;
    }
  cout << "==================================================================================="<<endl;
  cout << endl;
}
/*
 * process the transaction file here, featuring the appropriate
 * commands with the proper function written above---------------------------------------
 */
bool Family::processTransactionfile()
{
  long id, husbandID, famID;
  string command, firstname, lastname;
  fstream fin;

  fin.open("transactionfile.txt");
  if(!fin)
    {
      cout << "Can't open this file"<<endl;
      return Family::failure;
    }
  else
    {
      while(fin >> command)
        {
	  if(command == "AddHusband")
            {
	      fin >> id >> firstname >> lastname;
	      addHusband(id, firstname, lastname);
            }
	  if(command == "RemoveHusband")
            {
	      fin >> id;
	      removeHusband(id);
            }
	  if(command == "AddWife")
            {
	      fin >> id >> firstname >> lastname >> husbandID;
	      addWife(id, firstname, lastname, husbandID);
            }
	  if(command == "RemoveWife")
            {
	      fin >> husbandID;
	      removeWife(husbandID);
            }
	  if(command == "AddAchild")
            {
	      fin >> id >> firstname >> lastname >> famID;
	      addChild(id, firstname, lastname, famID);
            }
	  if(command == "RemoveAchild")
            {
	      fin >> famID >> id;
	      removeChild(famID, id);
            }
	  if(command == "PrintAFamily")
            {
	      fin >> id;
	      printFamily(id);
            }
	  if(command == "PrintAllFamilies")
            {
	      printAllFamilies();
            }
	  
        }//end of while loop

    } //end of else loop
  
  fin.close();
}
