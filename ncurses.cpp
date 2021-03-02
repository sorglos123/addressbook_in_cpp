#include<ncurses.h>
#include<string>
#include<form.h>
#include<string.h>
#include "logic.hpp"
#include<tuple>

using namespace std;

WINDOW * createWindow(int verDim, int horDim, int verPos, int horPos, const char* label)
{
    /* NCurses: newwin(verticalDim, horizontalDim, verticalPos, horizontalPos) */
    WINDOW * temp = newwin(verDim, horDim, verPos, horPos);
	box(temp,0,0);
	mvwprintw(temp,0,2,label);

    return temp;
}

std::tuple<FIELD*, FORM*> createForm(FIELD *field[8], FORM *addressData) {
    // FIELD *field[8];
	// FORM *addressData;

    /* Erstellung der Formularfelder für die Eingabe der Daten */
	/* NCurses: new_field(rows, cols, frow, fcol, offrows, offcols) */
	field[0] = new_field(1, 20, 5, 195, 0, 0);
	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP);

	field[1] = new_field(1, 20, 9, 195, 0, 0);
	set_field_back(field[1], A_UNDERLINE);
	field_opts_off(field[1], O_AUTOSKIP);

	field[2] = new_field(1, 20, 13, 195, 0, 0);
	set_field_back(field[2], A_UNDERLINE);
	field_opts_off(field[2], O_AUTOSKIP);

	field[3] = new_field(1, 20, 17, 195, 0, 0);
	set_field_back(field[3], A_UNDERLINE);
	field_opts_off(field[3], O_AUTOSKIP);

	field[4] = new_field(1, 20, 21, 195, 0, 0);
	set_field_back(field[4], A_UNDERLINE);
	field_opts_off(field[4], O_AUTOSKIP);
	
	field[5] = new_field(1, 20, 25, 195, 0, 0);
	set_field_back(field[5], A_UNDERLINE);
	field_opts_off(field[5], O_AUTOSKIP);
	
	field[6] = new_field(1, 20, 29, 195, 0, 0);
	set_field_back(field[6], A_UNDERLINE);
	field_opts_off(field[6], O_AUTOSKIP);
	
	field[7] = new_field(1, 20, 33, 195, 0, 0);
	set_field_back(field[7], A_UNDERLINE);
	field_opts_off(field[7], O_AUTOSKIP);
	
	field[8] = NULL;

	addressData = new_form(field);
	post_form(addressData);
	// refresh();

	mvprintw(3, 195, "Nachname:");
	mvprintw(7, 195, "Vorname:");	
	mvprintw(11, 195, "Geburtsdatum:");
	mvprintw(15, 195, "Telefonnummer:");
	mvprintw(19, 195, "Strasse:");
	mvprintw(23, 195, "Hausnummer:");
	mvprintw(27, 195, "Postleitzahl:");
	mvprintw(31, 195, "Wohnort:");

    return {field[8], addressData};
}

void initWindow(contact* entry, int counter)
{   
    int c; 

    /* Drucken des Ausgabefensters */ 
    WINDOW * display        = createWindow(53, 155, 1, 5, "Mein Adressbuch");
    WINDOW * lastNames      = createWindow(50, 20, 3, 6, "Nachname");
    WINDOW * firstNames     = createWindow(50, 20, 3, 25, "Vorname");
    WINDOW * dobs           = createWindow(50, 20, 3, 44, "Geburtsdatum");
    WINDOW * phoneNumbers   = createWindow(50, 20, 3, 63, "Telefonnummer");
    WINDOW * streetNames    = createWindow(50, 20, 3, 82, "Strasse");
    WINDOW * houseNumbers   = createWindow(50, 20, 3, 101, "Hausnummer");
    WINDOW * zipCodes       = createWindow(50, 20, 3, 120, "Postleitzahl");
    WINDOW * cities         = createWindow(50, 20, 3, 139, "Wohnort");

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

    return temp;
}

char * trim(char *str)
{
	char *end;

	/* Remove leading whitespaces */
	while(isspace(*str))
	{
  		str++;
	}

	if(*str == 0) return str;

	/* Remove trailing whitespaces */
  	end = str + strnlen(str, 128) - 1;

  	while(end > str && isspace(*end))
  	{
  		end--;
  	}

  	/* Important: Write new string terminator "\0" ! */
  	*(end+1) = '\0';

  	return str;
}

int main(int argc, char ** argv)
{   
    string input = "names01";
	contact_list l;
	contact *cont; 
    contact *element;
	l.readContacts(input);	
	cont = l.getFirstElement();

    /* START NCURSES */
    initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);

    int c1,c2,c3,c4,c5,c6,yMax,xMax, counter;
	getmaxyx(stdscr, yMax, xMax);

    WINDOW * info = createInfoWindow(40, 30, 3, 160, "Sortierung");
    WINDOW * hit = createWindow(5, 10, 43, 160, "Taste");
    WINDOW * level = createWindow(6, 30, 48, 160, "Ebene");
    
    WINDOW * form = createWindow(2, 40, 1, 190, "Suchen");
    WINDOW * output = createWindow(18, 40, 36, 190, "Ergebnis");
    
    FIELD *field[8];
	FORM *addressData;
    // tie(field[8], addressData) = createForm(field, addressData);
	// refresh();
   
    mvwprintw(level,2,2,"Navigation");
    wrefresh(level);

    getch();
    
    counter = 2;
    while(c1 = getch() != 10)
    {   
        mvwprintw(level,2,2,"Obere Ebene");
        wrefresh(level);
        c2 = getch();

        switch(c2)
		{
			case KEY_LEFT:
                
                refresh();
                initWindow(cont, counter);
                
                wrefresh(info);
                wrefresh(hit);

                mvwprintw(level,2,2,"Adressbuch");
                wrefresh(level);

                while(c3 = getch() != 10) 
                {
                    c4 = getch();
                    switch(c4) 
                    {
                        case 'q':
                            /* Funktioniert leider noch nicht: */
                            // l.x = contact_list::sortBySurname(0);
                            //l.sortSurname(hit, "q", contact * (contact_list::*sorter), 0, l, contact, counter);
                            // l.x = &contact_list::sortBySurname(1);
                            mvwprintw(hit,2,2,"q");
                            l.sortBySurname(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
			            case 'a':
                            mvwprintw(hit,2,2,"a");
                            l.sortBySurname(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'w':
                            mvwprintw(hit,2,2,"w");
                            l.sortByFirstname(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 's':
                            mvwprintw(hit,2,2,"s");
                            l.sortByFirstname(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'e':
                            mvwprintw(hit,2,2,"e");
                            l.sortByPhone(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'd':
                            mvwprintw(hit,2,2,"d");
                            l.sortByPhone(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'r':
                            mvwprintw(hit,2,2,"r");
                            l.sortByStreetName(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'f':
                            mvwprintw(hit,2,2,"f");
                            l.sortByStreetName(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 't':
                            mvwprintw(hit,2,2,"t");
                            l.sortByHouseNumber(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
			            case 'g':
                            mvwprintw(hit,2,2,"g");
                            l.sortByHouseNumber(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'z':
                            mvwprintw(hit,2,2,"z");
                            l.sortByZip(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'h':
                            mvwprintw(hit,2,2,"h");
                            l.sortByZip(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'u':
                            mvwprintw(hit,2,2,"u");
                            l.sortByCity(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'j':
                            mvwprintw(hit,2,2,"j");
                            l.sortByCity(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'i':
                            mvwprintw(hit,2,2,"i");
                            l.sortByDOB(0);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
                        case 'k':
                            mvwprintw(hit,2,2,"k");
                            l.sortByDOB(1);
                            cont = l.getFirstElement();
                            initWindow(cont, counter);
                            wrefresh(hit);
                            break;
			            default:
				            break;
                    }
                }
            case KEY_RIGHT:
                // Wechsle zur Suche
                refresh();
                tie(field[8], addressData) = createForm(field, addressData);
	            refresh();
                mvwprintw(level,2,2,"Suchformular");
                wrefresh(form);
                wrefresh(level);
                
                while(c5 = getch() != 10) 
                {
                    c6 = getch();
                    switch(c6) 
                    {
                        case KEY_DOWN:
                            form_driver(addressData, REQ_NEXT_FIELD);
                            form_driver(addressData, REQ_END_LINE);
                            break;
			            case KEY_UP:
                            form_driver(addressData, REQ_PREV_FIELD);
                            form_driver(addressData, REQ_END_LINE);
                            break;
			            case KEY_LEFT:
                            form_driver(addressData, REQ_PREV_CHAR);
                            break;
			            case KEY_RIGHT:
                            form_driver(addressData, REQ_NEXT_CHAR);
                            break;
			            case KEY_BACKSPACE:
                            form_driver(addressData, REQ_DEL_PREV);
                            break;
			            case KEY_F(5):	
                            form_driver(addressData, REQ_NEXT_FIELD);
                            form_driver(addressData, REQ_PREV_FIELD);
                            move(LINES-3, 2);
        			        for (int i = 0; field[i]; i++) 
				            {
          				        printw("%s", trim(field_buffer(field[i], 0)));

          				    if (field_opts(field[i]) & O_ACTIVE) printw(" : ");
          				    else printw("> : >");
        			        }

                            // Alle Fenster refreshen, damit alles weiterhin angezeigt wird!
        			        refresh();

        			        pos_form_cursor(addressData);
        			        break;	
			            default:
				        form_driver(addressData, c6);
				        break;
                    }
                }

                wrefresh(output);

                char * lastName		= field_buffer(field[0],0);
                char * firstName	= field_buffer(field[1],0);
                char * dateOfBirth	= field_buffer(field[2],0);
                char * phone		= field_buffer(field[3],0);
                char * street 		= field_buffer(field[4],0);
                char * number		= field_buffer(field[5],0);
                char * zipCode		= field_buffer(field[6],0);
                char * city 		= field_buffer(field[7],0);

                string sur_tmp(lastName);
                string first_tmp(lastName);
                string dob_tmp(dateOfBirth);
                string phone_tmp(phone);
                string street_tmp(street);
                string number_tmp(number);
                string zip_tmp(zipCode);
                string city_tmp(city);

                if(lastName != " ") {
                    element = l.findContact(sur_tmp, 0);
                } else if(firstName != " ") {
                    element = l.findContact(first_tmp, 1);
                } else if(dateOfBirth != " ") {
                    element = l.findContact(dob_tmp, 5);
                } else if(phone != " ") {
                    element = l.findContact(phone_tmp, 2);
                } else if(street != " ") {
                    element = l.findContact(street_tmp, 3);
                } else if(number != " ") {
                    element = l.findContact(number_tmp, 6);
                } else if(zipCode != " ") {
                    element = l.findContact(zip_tmp, 7);
                } else if(city != " ") {
                    element = l.findContact(city_tmp, 4);
                } 

                string tmp_hnr = to_string(element->house_number);
                string tmp_zip = to_string(element->zip_code);

                mvwprintw(output,2,1,"Nachname: %s", (element->surname).c_str());	
                mvwprintw(output,4,1,"Vorname: %s", (element->firstname).c_str());
                mvwprintw(output,6,1,"Geburtsdatum: %s", (element->dob).c_str());
                mvwprintw(output,8,1,"Telefonnummer: %s", (element->phone_number).c_str());
                mvwprintw(output,10,1,"Strasse: %s", (element->street_name).c_str());
                mvwprintw(output,12,1,"Hausnummer: %s", tmp_hnr.c_str()); // to int
                mvwprintw(output,14,1,"PLZ: %s", tmp_zip.c_str()); // to int
                mvwprintw(output,16,1,"Wohnort: %s", (element->city).c_str());
	
	            wrefresh(output);
		}
    }

    getch();

    unpost_form(addressData);
	free_form(addressData);
	free_field(field[0]);
	free_field(field[1]);
	free_field(field[2]);
	free_field(field[3]);
	free_field(field[4]);
	free_field(field[5]);
	free_field(field[6]);
	free_field(field[7]);
	free_field(field[8]);

    endwin();
	/* END NCURSES */
}