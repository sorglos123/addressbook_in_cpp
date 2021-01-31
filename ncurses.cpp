#include<ncurses.h>
#include<string>
#include<form.h>
#include<string.h>
#include "logic.hpp"

using namespace std;

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
	//Input Datei zum Auslesen der Daten
	string input = "names01";
	//Struct zur Speicherung der Adressen
	contact_list l;
	// c ist Kontakt zur Anzeige im Adressbuch
	contact *contact; 
	l.readContacts(input);
	//Beginn mit ersten Kontakt; getLast ebenfalls möglich	
	contact = l.getFirstElement();
	//Aufruf der Feldinhalte über c->firstname etc. 
	// Ausgabe der PLZ immer Padden, damit führende Nullen mit ausgegeben werden;
	//<< setfill('0') << setw(5) << tempelement->zip_code <<  */ 
	cout << "Zeige Name: " << contact->firstname << endl;
	/* START NCURSES */
	
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, true);
	//curs_set(0);
	
	FIELD *field[8];
	FORM *addressData;
	int c,yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);

	/* Create fields for data input */
	/* Comment: new_field(rows, cols, frow, fcol, offrows, offcols) */
	field[0] = new_field(1, 20, 5, 30, 0, 0);
	set_field_back(field[0], A_UNDERLINE);
	field_opts_off(field[0], O_AUTOSKIP);

	field[1] = new_field(1, 20, 8, 30, 0, 0);
	set_field_back(field[1], A_UNDERLINE);
	field_opts_off(field[1], O_AUTOSKIP);

	field[2] = new_field(1, 20, 11, 30, 0, 0);
	set_field_back(field[2], A_UNDERLINE);
	field_opts_off(field[2], O_AUTOSKIP);

	field[3] = new_field(1, 20, 14, 30, 0, 0);
	set_field_back(field[3], A_UNDERLINE);
	field_opts_off(field[3], O_AUTOSKIP);

	field[4] = new_field(1, 20, 17, 30, 0, 0);
	set_field_back(field[4], A_UNDERLINE);
	field_opts_off(field[4], O_AUTOSKIP);
	
	field[5] = new_field(1, 20, 20, 30, 0, 0);
	set_field_back(field[5], A_UNDERLINE);
	field_opts_off(field[5], O_AUTOSKIP);
	
	field[6] = new_field(1, 20, 23, 30, 0, 0);
	set_field_back(field[6], A_UNDERLINE);
	field_opts_off(field[6], O_AUTOSKIP);
	
	field[7] = new_field(1, 20, 26, 30, 0, 0);
	set_field_back(field[7], A_UNDERLINE);
	field_opts_off(field[7], O_AUTOSKIP);
	
	field[8] = NULL;

	addressData = new_form(field);
	post_form(addressData);
	refresh();

	mvprintw(5, 10, "Last name:");
	mvprintw(8, 10, "First name:");	
	mvprintw(11, 10, "Date of birth:");
	mvprintw(14, 10, "Phone:");
	mvprintw(17, 10, "Street:");
	mvprintw(20, 10, "Number:");
	mvprintw(23, 10, "ZIP code:");
	mvprintw(26, 10, "City:");
	
	/* Refresh screen to display forms */
	refresh();
	
	/* Bad practice: Endlosschleife */
	while(1)
	{
		c = getch();

		switch(c)
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
        			refresh();
        			pos_form_cursor(addressData);
        			break;	
			default:
				form_driver(addressData, c);
				break;
		}

		if(c == 10) break;
	}

	getch();
	
	/* Create Window for data output */
	/* Comment: newwin(verticalDim, horizontalDim, verticalPos, horizontalPos) */
	WINDOW * display = newwin(20, 30, 30, 10);
	box(display,0,0);
	mvwprintw(display,0,2,"Display");
	wrefresh(display);
	
	getch();

	/* Save form field buffer for output. */
	char * lastName		= field_buffer(field[0],0);
	char * firstName	= field_buffer(field[1],0);
	char * dateOfBirth	= field_buffer(field[2],0);
	char * phone		= field_buffer(field[3],0);
	char * street 		= field_buffer(field[4],0);
	char * number		= field_buffer(field[5],0);
	char * zipCode		= field_buffer(field[6],0);
	char * city 		= field_buffer(field[7],0);
	
	/* Print the buffers' contents*/
	mvwprintw(display,2,1,"Nachname: %s", trim(lastName));	
	mvwprintw(display,4,1,"Vorname: %s", trim(firstName));
	mvwprintw(display,6,1,"Geburtsdatum: %s", trim(dateOfBirth));
	mvwprintw(display,8,1,"Telefonnummer: %s", trim(phone));
	mvwprintw(display,10,1,"Strasse: %s", trim(street));
	mvwprintw(display,12,1,"Hausnummer: %s", trim(number));
	mvwprintw(display,14,1,"PLZ: %s", trim(zipCode));
	mvwprintw(display,16,1,"Stadt: %s", trim(city));
	
	wrefresh(display);

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

	return 0;
}