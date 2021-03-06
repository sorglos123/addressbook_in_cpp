#include<string>
#include<string.h>
#include<iostream>
#include<fstream>
#include<iomanip>

using namespace std;

//Struct to save contact data
struct contact
{
	//input format surname:firstname:phone_number:street_name:house_number:zip_code:city:dob
	string surname;
	string firstname;
	string phone_number;
	string street_name;
	int house_number;
	int zip_code;
	string city;
	string dob;
	contact *next = NULL;
	contact *prev = NULL;
};

//class to save contact data as a list
class contact_list
{
	public:
		void addElement(const string &, const string &, const string& , const string&, int house_number, int zip_code, const string &, const string &);
		void output();
		void output(contact *);
		
		contact * getLastElement() {return this->getLastElement(this->elements); }
		contact * getFirstElement() {return this->getFirstElement(this->elements); }
		contact * getLastElement(contact *);
		contact * getFirstElement(contact *);
		contact * getNext();
		contact * getNext(contact *contact_list);
		contact * getPrev();
		contact * getPrev(contact *contact_list);

		contact * appendElement(contact * element) {return this->appendElement(this->elements, element);}
		contact * appendElement(contact *, contact *);
		void readContacts(string filePath);

		contact *sortBySurname(int);
		contact *sortBySurname(contact *contact_list, int);
		contact *sortByFirstname(int);
		contact *sortByFirstname(contact *contact_list, int);
		contact *sortByPhone(int);
		contact *sortByPhone(contact *contact_list, int);
		contact *sortByStreetName(int);
		contact *sortByStreetName(contact *contact_list, int);
		contact *sortByHouseNumber(int i);
		contact *sortByHouseNumber(contact *contact_list, int i);
		contact *sortByZip(int i);
		contact *sortByZip(contact *contact_list, int i);
		contact *sortByCity(int i);
		contact *sortByCity(contact *contact_list, int i);
		contact *sortByDOB(int i);
		contact *sortByDOB(contact *contact_list, int i);

		contact *qSort(const string &, const char &);
		contact *qSort(contact *contact_list, const string &, const char &);

		contact * findContact(const string &, int);
		contact * findContact(const string &, contact *contact_list, int);

		// contact * sortSurname(WINDOW *, string, contact * (contact contact_list::*sorter), int, contact_list, contact *, int);
		contact * (contact_list::*x)();

		~contact_list();

	private:
		contact *elements=NULL;
		contact *getPivotElement(contact *);
		contact *newElement(const string &, const string &, const string& , const string&, int house_number, int zip_code, const string &, const string &);
};