#include "logic.hpp"
#include<string>
#include<string.h>
#include<iostream>
#include<fstream>
#include<iomanip>


int compare_birthday(string d1, string d2)
{
	//returns -1 if d1 is before d2
	// returns 0 if d1==d2
	// returns 1 if d1 is after d2

	char *d1_char = new char[d1.length()+1];
	strcpy(d1_char, d1.c_str());

	char *d2_char = new char[d2.length()+1];
	strcpy(d2_char, d2.c_str());
	
	int d1_day;
	int d1_month;
	int d1_year;

	int d2_day;
	int d2_month;
	int d2_year;

	d1_day = atoi(strtok(d1_char, "."));
	d1_month = atoi(strtok(NULL, "."));
	d1_year = atoi(strtok(NULL, "\n"));

	d2_day = atoi(strtok(d2_char, "."));
	d2_month = atoi(strtok(NULL, "."));
	d2_year = atoi(strtok(NULL, "\n"));
	
	if (d1_year < d2_year) return -1; 
    if (d1_year == d2_year && d1_month < d2_month) return -1; 
    if (d1_year == d2_year && d1_year == d2_year && d1_day < d2_day) return -1; 
	if (d1_year == d2_year && d1_year == d2_year && d1_day == d2_day) return 0;
	return 1;
}

contact *contact_list::getPivotElement(contact * contact_list)
{
	//Empty list
	if(contact_list == NULL) return NULL;
	//List with 1 element
	if(contact_list->prev == NULL && contact_list->next == NULL) return contact_list;
	//counters to find middle
	int counter =0;
	int halfcounter =0;
	contact_list=this->getFirstElement(contact_list);
	while(contact_list->next != NULL) {counter++; contact_list=contact_list->next;}
	halfcounter = counter/2;
	while(halfcounter<counter){counter--; contact_list=contact_list->prev;}
	return contact_list;
}

//for string input
contact * contact_list::findContact(const string &input, int field){
	return findContact(input, this->elements, field);
}

contact * contact_list::findContact(const string &input, contact *contact_list, int field)
{
	//0 surname
	//1 firstname 
	//2 phone
	//3 street
	//4 city
	//5 dob
	//6 house number
	//7 zip code
	
	contact *no_result = contact_list; 
	
	if(contact_list == NULL || &input == NULL|| (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;
	contact_list = this->getFirstElement();
	while(contact_list != NULL)
	{
		switch(field)
		{
			case 0: if (contact_list->surname.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			case 1: if (contact_list->firstname.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			case 2: if (contact_list->phone_number.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			case 3: if (contact_list->street_name.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			case 4: if (contact_list->city.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			case 5: if (contact_list->dob.compare(input) == 0) return contact_list; else contact_list = contact_list->next; break; 
			
		}
	} 
	//using c as focused contact; returning if result returns nothing
	return no_result;
	
}

//find int input
contact * contact_list::findContact(int input, int field){
	return findContact(input, this->elements, field);
}

contact * contact_list::findContact(int input, contact *contact_list, int field)
{
	//0 surname
	//1 firstname 
	//2 phone
	//3 street
	//4 city
	//5 dob
	//6 house number
	//7 zip code
	
	contact *no_result = contact_list; 
	
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;
	contact_list = this->getFirstElement();
	while(contact_list != NULL)
	{
		switch(field)
		{
			case 6: if (contact_list->house_number == input) return contact_list; else contact_list = contact_list->next; break; 
			case 7: if (contact_list->zip_code == input ) return contact_list; else contact_list = contact_list->next; break; 
		}
	} 
	//using no_result as focused contact; returning if result returns nothing
	return no_result;
	
}

contact * contact_list::sortByPhone(int i)
{
	//i = 0 decreasing order
	//i = 1 increasing order
	return sortByPhone(this->elements, i);
}

contact * contact_list::sortByPhone(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			//Phone numbers must be entered in canonincal formatting
			//cleaning cannonical formatting to compare as int
			string tmp_cur = curelement->phone_number;
			tmp_cur.erase(0,1);
			
			string tmp_piv = pivotelement->phone_number;
			tmp_piv.erase(0, 1);
			
			int cur_phone = stol(tmp_cur);
			int piv_phone = stol(tmp_piv);

			switch(i)
			{
				case 0: if(cur_phone > piv_phone) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
				case 1: if(cur_phone < piv_phone) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
			}
			
		}
		curelement = nextelement;	
	}
	left = sortByPhone(left, i);
	right = sortByPhone(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortBySurname(int i)
{
	//i = 0 decreasing order
	//i = 1 increasing order
	return sortBySurname(this->elements, i);
}

contact * contact_list::sortBySurname(contact *contact_list,int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch(i)
			{
				case 0: if(curelement->surname.compare(pivotelement->surname) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
				case 1: if(curelement->surname.compare(pivotelement->surname) < 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
			}
			
		}
		curelement = nextelement;	
	}
	left = sortBySurname(left, i);
	right = sortBySurname(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByFirstname(int i)
{
	//i = 0 decreasing order
	//i = 1 increasing order
	return sortByFirstname(this->elements, i);
}

contact * contact_list::sortByFirstname(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch(i)
			{
				case 0: if(curelement->firstname.compare(pivotelement->firstname) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
				case 1: if(curelement->firstname.compare(pivotelement->firstname) < 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
			}
						
		}
		curelement = nextelement;	
	}
	left = sortByFirstname(left, i);
	right = sortByFirstname(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByStreetName(int i)
{
	return sortByStreetName(this->elements, i);
}

contact * contact_list::sortByStreetName(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
		switch(i)
			{
				case 0: if(curelement->street_name.compare(pivotelement->street_name) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
				case 1: if(curelement->street_name.compare(pivotelement->street_name) < 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break; 
			}			
		}
		curelement = nextelement;	
	}
	left = sortByStreetName(left, i);
	right = sortByStreetName(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByHouseNumber(int i)
{
	return sortByHouseNumber(this->elements, i);
}

contact * contact_list::sortByHouseNumber(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch(i)
			{
				case 0: if(curelement->house_number > pivotelement->house_number) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
				case 1: if(curelement->house_number < pivotelement->house_number) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			}	
		}
		curelement = nextelement;	
	}
	left = sortByHouseNumber(left, i);
	right = sortByHouseNumber(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByZip(int i)
{
	return sortByZip(this->elements, i);
}

contact * contact_list::sortByZip(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch (i)
			{
			case 0: if(curelement->zip_code > pivotelement->zip_code) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			case 1: if(curelement->zip_code < pivotelement->zip_code) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			}		
		}
		curelement = nextelement;	
	}
	left = sortByZip(left, i);
	right = sortByZip(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByCity(int i)
{
	return sortByCity(this->elements, i);
}

contact * contact_list::sortByCity(contact *contact_list,int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch (i)
			{
			case 0: if(curelement->city.compare(pivotelement->city) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			case 1: if(curelement->city.compare(pivotelement->city) < 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			}					
		}
		curelement = nextelement;	
	}
	left = sortByCity(left, i);
	right = sortByCity(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

contact * contact_list::sortByDOB(int i)
{
	return sortByDOB(this->elements, i);
}

contact * contact_list::sortByDOB(contact *contact_list, int i)
{
	//Using qsort
	if(contact_list == NULL || (contact_list->prev == NULL & contact_list->next == NULL)) return contact_list;

	contact * pivotelement = this->getPivotElement(contact_list);
	contact_list = this->getFirstElement(contact_list);

	contact *curelement = contact_list;

	contact *left = NULL;
	contact *right = NULL; 
	while (curelement != NULL)
	{
		contact *nextelement = curelement->next;
		if (curelement == pivotelement)
		{
			pivotelement->prev=NULL;
			pivotelement->next=NULL;
		}
		else
		{
			switch (i)
			{
			case 0: if(compare_birthday(curelement->dob, pivotelement->dob) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			case 1: if(compare_birthday(curelement->dob, pivotelement->dob) > 0) right = appendElement(right, curelement); else left = appendElement(left, curelement); break;
			}
		}
		curelement = nextelement;	
	}
	left = sortByDOB(left, i);
	right = sortByDOB(right, i);

	left = getLastElement(left);
	right = getFirstElement(right);

	pivotelement->prev = left;
	if (left != NULL) left->next = pivotelement;

	pivotelement->next = right;
	if (right != NULL) right->prev = pivotelement;

	return pivotelement;
}

void contact_list::addElement(const string &surname, const string &firstname, const string &phone_number , const string &street_name, int house_number, int zip_code, const string &city, const string &dob)
{
	contact *newelement = this->newElement(surname, firstname, phone_number, street_name, house_number, zip_code, city,dob);
	if (this->elements == NULL) elements = newelement;
	else
	{
		newelement->prev = this->getLastElement();
		if(newelement->prev != NULL) newelement->prev->next = newelement; //Rückwertsverknüpfung des Elements
	}
	
}

contact * contact_list::appendElement(contact *contact_list, contact *element)
{
	if (element->next!=NULL) element->next->prev = NULL;
	element->next = NULL;
	if (element->prev!=NULL) element->prev->next = NULL;
	element->prev = NULL;

	if (contact_list==NULL) return element;

	contact_list = this->getLastElement(contact_list);

	contact_list->next = element;
	element->prev = contact_list;

	return element;
}

contact * contact_list::newElement(const string &surname, const string &firstname, const string &phone_number , const string &street_name, int house_number, int zip_code, const string &city, const string &dob)
{
	contact *newelement = new contact;
	newelement->surname = surname;
	newelement->firstname = firstname;
	newelement->phone_number = phone_number;
	newelement->street_name = street_name;
	newelement->house_number = house_number;
	newelement->zip_code = zip_code;
	newelement->city = city;
	newelement->dob = dob;
	return newelement;
}

contact * contact_list::getLastElement(contact *contact_list)
{
	if (contact_list == NULL) return NULL;
	while(contact_list->next != NULL) contact_list=contact_list->next;
	return contact_list;
}

contact * contact_list::getFirstElement(contact *contact_list)
{
	if (contact_list == NULL) return NULL;
	while(contact_list->prev != NULL) contact_list=contact_list->prev;
	return contact_list;
}

contact * contact_list::getNext()
{
	return getNext(this->elements);
}

contact * contact_list::getNext(contact *contact_list)
{
	if(contact_list->next == NULL) return contact_list;
	else
	{
		contact_list = contact_list->next;
		return contact_list;
	}
	
}

contact * contact_list::getPrev()
{
	return getPrev(this->elements);
}

contact * contact_list::getPrev(contact *contact_list)
{
	if(contact_list->prev == NULL) return contact_list;
	else
	{
		contact_list = contact_list->prev;
		return contact_list;
	}
	
}

void contact_list::output()
{
	contact *tempelement = this->getFirstElement();
	
	while(tempelement != NULL)
	{
		cout <<"Vorn: " << tempelement->surname << "/" << tempelement->firstname<<"/"<< tempelement->city << "/"<<tempelement->street_name<< "/ " << tempelement->house_number << " / "  << setfill('0') << setw(5) << tempelement->zip_code <<  "/" << tempelement->phone_number<< " / " << tempelement->dob<<  endl;
		tempelement = tempelement->next;
	}
}

void contact_list::output(contact *contact_list)
{
	if(contact_list == NULL) return;
	while(contact_list->prev != NULL) contact_list = contact_list-> prev;
	while(contact_list != NULL)
	{
		//cout <<"Vorn: " << contact_list->surname << "/" << contact_list->firstname<<"/"<< contact_list->city<< endl;
	}
}

contact_list::~contact_list()
{
	this->elements = this->getFirstElement();
	while(this->elements != NULL)
	{
		contact *nextelement = this->elements->next;
		delete this->elements;
		this->elements = nextelement; 
	}
}

void contact_list::readContacts(string filePath)
{
	//Getting path as string and reading input
	//input format surname:firstname:phone_number:street_name:house_number:zip_code:city:dob
	//taking everything as string and casting afterwards
	
	string line;
	char *tmp = NULL;
	char *surname_tmp = NULL;
	char *firstname_tmp = NULL;
	char *phone_number_tmp = NULL;
	char *street_name_tmp = NULL;
	char *house_number_str_tmp = NULL;
	char *zip_code_str_tmp = NULL;
	char *city_tmp = NULL;
	char *dob_tmp = NULL; 

	int house_number_tmp = 0;
	int zip_code_tmp = 0;

	ifstream instream(filePath);
	if(instream.is_open())
	{
		while(getline(instream,line))
		{	
			
			//whole line gets read into tmp initially
			//init the tmp with read length and dont forget the closing zero
			tmp = new char[line.length()+1];
			//copy the line to the variable
			strcpy(tmp,line.c_str());
			//chop chop time
			surname_tmp = strtok(tmp,":");
			firstname_tmp = strtok(NULL, ":");
			phone_number_tmp = strtok(NULL, ":");
			street_name_tmp = strtok(NULL, ":");
			house_number_str_tmp = strtok(NULL, ":");
			zip_code_str_tmp = strtok(NULL, ":");
			city_tmp = strtok(NULL, ":");
			dob_tmp = strtok(NULL, "\n");

			//casting time
			house_number_tmp = atoi(house_number_str_tmp);
			zip_code_tmp = atoi(zip_code_str_tmp);

			//adding extracted element to the contact list
			if((surname_tmp != NULL) && (firstname_tmp != NULL) && (phone_number_tmp != 0) && (street_name_tmp != 0) && (house_number_tmp != 0) && (zip_code_tmp != 0) && (city_tmp != 0) && (dob_tmp != 0)) 
			{
				this->addElement(surname_tmp, firstname_tmp, phone_number_tmp, street_name_tmp, house_number_tmp,zip_code_tmp,city_tmp, dob_tmp);
				//cout << surname_tmp << endl;
			}
			
		}
		instream.close();
	}

}
