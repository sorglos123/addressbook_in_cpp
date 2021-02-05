#include<ncurses.h>
#include<string>
#include<form.h>
#include<string.h>
#include "logic.hpp"

using namespace std;

WINDOW * createWindow(int verDim, int horDim, int verPos, int horPos, const char* label)
{
    /* NCurses: newwin(verticalDim, horizontalDim, verticalPos, horizontalPos) */
    WINDOW * temp = newwin(verDim, horDim, verPos, horPos);
	box(temp,0,0);
	mvwprintw(temp,0,2,label);

    return temp;
}

void initWindow(contact* entry, int counter)
{   
    int c; 

    /* Drucken des Ausgabefensters */ 
    WINDOW * display        = createWindow(53, 155, 1, 5, "Mein Adressbuch");
    WINDOW * lastNames      = createWindow(50, 20, 3, 6, "Nachname");
    WINDOW * firstNames     = createWindow(50, 20, 3, 25, "Vorname");
    WINDOW * phoneNumbers   = createWindow(50, 20, 3, 44, "Telefonnummer");
    WINDOW * streetNames    = createWindow(50, 20, 3, 63, "Strasse");
    WINDOW * houseNumbers   = createWindow(50, 20, 3, 82, "Hausnummer");
    WINDOW * zipCodes       = createWindow(50, 20, 3, 101, "Postleitzahl");
    WINDOW * cities         = createWindow(50, 20, 3, 120, "Wohnort");
    WINDOW * dobs           = createWindow(50, 20, 3, 139, "Geburtsdatum");

	refresh();
    wrefresh(display);
    wrefresh(lastNames);
    wrefresh(firstNames);
    wrefresh(phoneNumbers);
    wrefresh(streetNames);
    wrefresh(houseNumbers);
    wrefresh(zipCodes);
    wrefresh(cities);
    wrefresh(dobs);
    
    /* While-Schleife für Ausgabe der Listenelemente mit int counter */
    while(entry->next != NULL)
    {
        char *tmp_surname = new char[entry->surname.length()+1];
        char *tmp_firstname = new char[entry->firstname.length()+1];
        char *tmp_phoneNumber = new char[entry->phone_number.length()+1];
        char *tmp_streetName = new char[entry->street_name.length()+1];
        char *tmp_city = new char[entry->city.length()+1];
        char *tmp_dob = new char[entry->dob.length()+1];

        string tmphn = to_string(entry->house_number);
        char *tmp_houseNumber = new char[tmphn.length()+1];

        string tmpzip = to_string(entry->zip_code);
        char *tmp_zipCode = new char[tmpzip.length()+1];
        
        strcpy(tmp_surname, entry->surname.c_str());

        strcpy(tmp_firstname, entry->firstname.c_str());
        strcpy(tmp_phoneNumber, entry->phone_number.c_str());
        strcpy(tmp_streetName, entry->street_name.c_str());
        strcpy(tmp_houseNumber, tmphn.c_str());
        strcpy(tmp_zipCode, tmpzip.c_str());
        strcpy(tmp_city, entry->city.c_str());
        strcpy(tmp_dob, entry->dob.c_str());

        mvwprintw(lastNames,counter,1,tmp_surname);
        mvwprintw(firstNames,counter,1,tmp_firstname);
        mvwprintw(phoneNumbers,counter,1,tmp_phoneNumber);
        mvwprintw(streetNames,counter,1,tmp_streetName);
        mvwprintw(houseNumbers,counter,1,tmp_houseNumber);
        mvwprintw(zipCodes,counter,1,tmp_zipCode);
        mvwprintw(cities,counter,1,tmp_city);
        mvwprintw(dobs,counter,1,tmp_dob);
        
        wrefresh(lastNames);
        wrefresh(firstNames);
        wrefresh(phoneNumbers);
        wrefresh(streetNames);
        wrefresh(houseNumbers);
        wrefresh(zipCodes);
        wrefresh(cities);
        wrefresh(dobs);
        
        counter = counter + 2;
        entry = entry->next;
    }
}

WINDOW * createInfoWindow(int verDim, int horDim, int verPos, int horPos, const char* label)
{
    /* NCurses: newwin(verticalDim, horizontalDim, verticalPos, horizontalPos) */
    WINDOW * temp = newwin(verDim, horDim, verPos, horPos);
	box(temp,0,0);
	mvwprintw(temp,0,2,label);

    mvwprintw(temp,2,1,"q: Nachname (absteigend)");	
	mvwprintw(temp,4,1,"a: Nachname (aufsteigend)");
	mvwprintw(temp,6,1,"w: Vorname (absteigend)");
	mvwprintw(temp,8,1,"s: Vorname (aufsteigend)");
	mvwprintw(temp,10,1,"e: Tel. (absteigend)");
	mvwprintw(temp,12,1,"d: Tel. (aufsteigend)");
	mvwprintw(temp,14,1,"r: Strasse (absteigend)");
	mvwprintw(temp,16,1,"f: Strasse (aufsteigend)");
    mvwprintw(temp,18,1,"t: Hausnr. (absteigend)");
	mvwprintw(temp,20,1,"g: Hausnr. (aufsteigend)");
    mvwprintw(temp,22,1,"z: PLZ (absteigend)");
	mvwprintw(temp,24,1,"h: PLZ (aufsteigend)");
    mvwprintw(temp,26,1,"u: Ort (absteigend)");
	mvwprintw(temp,28,1,"j: Ort (aufsteigend)");
    mvwprintw(temp,30,1,"i: Geb. (absteigend)");
	mvwprintw(temp,32,1,"k: Geb. (aufsteigend)");
    mvwprintw(temp,34,1,"Enter: Abbruch");
    mvwprintw(temp,36,1,"Bitte die jew. Taste 2x,");
    mvwprintw(temp,37,1," bzw. Enter 3x drücken!");

    return temp;
}

typedef void (* functionCall)(int order);

void funct(int order, functionCall sortFunction)
{
   sortFunction(order);
}

void sortList(WINDOW *window, const char* print, functionCall funct, int order, contact_list l, contact * entry, int counter)
{
    mvwprintw(window,2,2,print);
    /* Hier kommt es zum Speicherabzug */
    funct(order);
    entry = l.getFirstElement();
    initWindow(entry, counter);
    wrefresh(window);
}

int main(int argc, char ** argv)
{   
    string input = "names01";
	contact_list l;
	contact *contact; 
	l.readContacts(input);	
	contact = l.getFirstElement();

    /* START NCURSES */
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);

    int c,yMax,xMax, counter;
	getmaxyx(stdscr, yMax, xMax);

    getch();

    WINDOW * info = createInfoWindow(40, 30, 3, 160, "Sortierung");
	wrefresh(info);

    getch();

    WINDOW * output = createWindow(5, 10, 43, 160, "Taste");
    wrefresh(output);

    getch();

    counter = 2;
    while(1)
    {
        initWindow(contact, counter);

        getch();
        
        wmove(stdscr, 0, 0);
        c = getch();

        /* Abbruch, wenn Enter-Taste betätigt wird */
        if(c == 10) break;

        switch(c)
		{
			case 'q':
				/* Funktioniert leider noch nicht:
                sortList(output, "q", (functionCall)l.sortBySurname(0), 0, l, contact, counter); */
                mvwprintw(output,2,2,"q");
                l.sortBySurname(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
			case 'a':
				mvwprintw(output,2,2,"a");
                l.sortBySurname(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'w':
				mvwprintw(output,2,2,"w");
                l.sortByFirstname(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 's':
				mvwprintw(output,2,2,"s");
                l.sortByFirstname(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'e':
				mvwprintw(output,2,2,"e");
                l.sortByPhone(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'd':
				mvwprintw(output,2,2,"d");
                l.sortByPhone(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'r':
				mvwprintw(output,2,2,"r");
                l.sortByStreetName(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'f':
				mvwprintw(output,2,2,"f");
                l.sortByStreetName(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
                break;
            case 't':
				mvwprintw(output,2,2,"t");
                l.sortByHouseNumber(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
			case 'g':
				mvwprintw(output,2,2,"g");
                l.sortByHouseNumber(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'z':
				mvwprintw(output,2,2,"z");
                l.sortByZip(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'h':
				mvwprintw(output,2,2,"h");
                l.sortByZip(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'u':
				mvwprintw(output,2,2,"u");
                l.sortByCity(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'j':
				mvwprintw(output,2,2,"j");
                l.sortByCity(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'i':
				mvwprintw(output,2,2,"i");
                l.sortByDOB(0);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
				break;
            case 'k':
				mvwprintw(output,2,2,"k");
                l.sortByDOB(1);
                contact = l.getFirstElement();
                initWindow(contact, counter);
                wrefresh(output);
                wmove(output, 2, 2);
                break;
			default:
				break;
		}
    }

    getch();
    endwin();
	/* END NCURSES */
}