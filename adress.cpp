#include <string>
#include <string.h>
#include "logic.hpp"
#include <final/final.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/* Befüllen der Adresslistenübersicht */
void fillList(finalcut::FListView *adresslist, const string &input)
{
  /* Einlesen der Kontaktliste */
  std::ifstream test(input); 
  
  if (!test) return; // Abfangen, falls der Dateipfad nicht existiert
  contact_list l;
  test.close();

  contact *cont;
  l.readContacts(input);
  cont = l.getFirstElement();
  adresslist->clear();

  /* Darstellung der Kontakte aus der Kontakliste:
    - Geh die eingelesene Kontaktliste vom ersten bis zum letzten Element durch;
    - Setze vor jedem Durchlauf den Vektor tmp zurück;
    - Speichere die Felder der Einträge im "inneren" Vektor tmp;
    - Speichere schließlich den Vektor tmp im "äußeren" Vektor contactVector  
    - zip_buffer wird benötigt, damit die PLZ korrekt mit führenden Nullen dargestellt werden*/
  vector<vector<string>> contactVector;
  vector<string> tmp;
  std::stringstream zip_buffer;
  
  while (cont->next != NULL)
  {
    tmp.clear();
    zip_buffer.str("");
    zip_buffer << setfill('0') << setw(5) << cont->zip_code << endl;
    tmp.push_back(cont->surname);
    tmp.push_back(cont->firstname);
    tmp.push_back(cont->dob);
    tmp.push_back(cont->phone_number);
    tmp.push_back(cont->street_name);
    tmp.push_back(to_string(cont->house_number));
    tmp.push_back(zip_buffer.str());
    tmp.push_back(cont->city);

    contactVector.push_back(tmp);

    cont = cont->next;
  }

  for (const auto &entry : contactVector)
  {
    const finalcut::FStringList line(entry.begin(), entry.end());
    adresslist->insert(line);
    adresslist->redraw();
  }
}

/* Callback-Funktion für "Datei auswählen"-Button */
void cb_openPath(finalcut::FLineEdit *filepath, finalcut::FListView *adresslist)
{
  
  if (filepath->getText().isEmpty() == false)
  {
    fillList(adresslist, filepath->getText().toString());
  }
}

/* Callback-Funktion für "Kontakt finden"-Button */
void cb_findEntry(
    finalcut::FLineEdit *lastname,
    finalcut::FLineEdit *firstname,
    finalcut::FLineEdit *dob,
    finalcut::FLineEdit *phone,
    finalcut::FLineEdit *street,
    finalcut::FLineEdit *number,
    finalcut::FLineEdit *zip,
    finalcut::FLineEdit *city,
    finalcut::FDialog *search,
    const string &in)
{
  contact_list l;
  contact *element;
  contact zip_element;
  l.readContacts(in);
  element = l.getFirstElement();

  /* Falls das der Funktion übergebene Textfeld nicht leer ist, wird anhand des darin befindlichen Textes ein 
    Kontakt aus der Kontaktliste herausgesucht. */
  if (lastname->getText().isEmpty() == false)
    element = l.findContact(lastname->getText().toString(), 0);
  else if (firstname->getText().isEmpty() == false)
    element = l.findContact(firstname->getText().toString(), 1);
  else if (dob->getText().isEmpty() == false)
    element = l.findContact(dob->getText().toString(), 5);
  else if (phone->getText().isEmpty() == false)
    element = l.findContact(phone->getText().toString(), 2);
  else if (street->getText().isEmpty() == false)
    element = l.findContact(street->getText().toString(), 3);
  else if (number->getText().isEmpty() == false)
    element = l.findContact(number->getText().toString(), 6);
  else if (zip->getText().isEmpty() == false)
    element = l.findContact(zip->getText().toString(), 7);
  else if (city->getText().isEmpty() == false)
    element = l.findContact(city->getText().toString(), 4);
  
  /* Darstellung des ermittelten Kontaktes innerhalb einer FMessageBox */
  std::stringstream zip_buffer;
  zip_buffer << setfill('0') << setw(5) << element->zip_code << endl;
  finalcut::FMessageBox info(
      "Suchergebnis",
      "Nachname: " + element->surname + "\n"
                                        "Vorname: " +
          element->firstname + "\n"
                               "Geburtsdatum: " +
          element->dob + "\n"
                         "Telefon: " +
          element->phone_number + "\n"
                                  "Straße: " +
          element->street_name + "\n"
                                 "Hausnummer: " +
          std::to_string(element->house_number) + "\n"
                                                  "Postleitzahl: " +
          zip_buffer.str() + "\n"
                             "Wohnort: " +
          element->city + "\n",
      finalcut::FMessageBox::ButtonType::Ok,
      finalcut::FMessageBox::ButtonType::Reject,
      finalcut::FMessageBox::ButtonType::Reject,
      search);
  info.setAlwaysOnTop();
  //search->setAlwaysOnTop(false); 
  info.show();
}

/* Callback-Funktion für "Anwendung beenden"-Button */
void cb_quit(const finalcut::FApplication &app)
{
  app.quit();
}

/* Main-Methode */
int main(int argc, char *argv[])
{
  /* Einlesen der Default-Belegung der Adresslistenübersicht; falls ein Kommandozeilenargument mitübergeben wird,
    wird der Inhalt dieser Datei angezeigt. */
  string input = "contacts"; 
  if (argv[1] != NULL)
    input = argv[1];

  /* Hauptapplikation erstellen */
  finalcut::FApplication app(argc, argv);

  /* Fenster innerhalb der Hauptapplikation erstellen:
  
    Hauptfenster */
  finalcut::FDialog *adress = new finalcut::FDialog(&app);
  adress->setText("Adressbuch");
  adress->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{210, 50});
  //adress->setAlwaysOnTop(false);

  /* Adressliste */
  finalcut::FDialog *list = new finalcut::FDialog(adress);
  list->setText("Liste");
  list->setGeometry(finalcut::FPoint{5, 5}, finalcut::FSize{160, 45});
  list->setAlwaysOnTop();

  /* Button zum Beenden der Anwendung */
  finalcut::FButton *quit = new finalcut::FButton(adress);
  quit->setGeometry(finalcut::FPoint{167, 45}, finalcut::FSize{20, 1});
  quit->setText(L"&Anwendung beenden");
  quit->addCallback(
      "clicked",
      &cb_quit,
      std::ref(app));

  /* Fenster für die Auswahl einer anzuzeigenden Datei */
  finalcut::FDialog *open_contactlist = new finalcut::FDialog(adress);
  open_contactlist->setText("Dateipfad");
  open_contactlist->setGeometry(finalcut::FPoint{167, 32}, finalcut::FSize{40, 10});
  open_contactlist->setAlwaysOnTop();

  /* Textfeld zur Eingabe der Datei */
  finalcut::FLineEdit *filepath = new finalcut::FLineEdit(open_contactlist);
  filepath->setGeometry(finalcut::FPoint{167, 1}, finalcut::FSize{30, 1});
  filepath->setLabelText(L"&Dateipfad");

  /* Button zur Anzeige der Datei */
  finalcut::FButton *openPath = new finalcut::FButton(open_contactlist);
  openPath->setGeometry(finalcut::FPoint{167, 3}, finalcut::FSize{20, 1});
  openPath->setText(L"&Dateipfad öffnen");

  /* Suchfenster inkl. Textfelder zur Kontaktsuche */
  finalcut::FDialog *search = new finalcut::FDialog(adress);
  search->setAlwaysOnTop();
  search->setText("Suche");
  search->setGeometry(finalcut::FPoint{167, 5}, finalcut::FSize{40, 22});

  finalcut::FLineEdit *lastname = new finalcut::FLineEdit(search);
  lastname->setGeometry(finalcut::FPoint{167, 1}, finalcut::FSize{30, 1});
  lastname->setLabelText(L"&Nachname");

  finalcut::FLineEdit *firstname = new finalcut::FLineEdit(search);
  firstname->setGeometry(finalcut::FPoint{167, 3}, finalcut::FSize{30, 1});
  firstname->setLabelText(L"&Vorname");

  finalcut::FLineEdit *dob = new finalcut::FLineEdit(search);
  dob->setGeometry(finalcut::FPoint{167, 5}, finalcut::FSize{30, 1});
  dob->setLabelText(L"&Geburtsdatum");

  finalcut::FLineEdit *phone = new finalcut::FLineEdit(search);
  phone->setGeometry(finalcut::FPoint{167, 7}, finalcut::FSize{30, 1});
  phone->setLabelText(L"&Telefon");

  finalcut::FLineEdit *street = new finalcut::FLineEdit(search);
  street->setGeometry(finalcut::FPoint{167, 9}, finalcut::FSize{30, 1});
  street->setLabelText(L"&Strasse");

  finalcut::FLineEdit *number = new finalcut::FLineEdit(search);
  number->setGeometry(finalcut::FPoint{167, 11}, finalcut::FSize{30, 1});
  number->setLabelText(L"&Hausnummer");

  finalcut::FLineEdit *zip = new finalcut::FLineEdit(search);
  zip->setGeometry(finalcut::FPoint{167, 13}, finalcut::FSize{30, 1});
  zip->setLabelText(L"&PLZ");

  finalcut::FLineEdit *city = new finalcut::FLineEdit(search);
  city->setGeometry(finalcut::FPoint{167, 15}, finalcut::FSize{30, 1});
  city->setLabelText(L"&Wohnort");

  finalcut::FButton *findEntry = new finalcut::FButton(search);
  findEntry->setGeometry(finalcut::FPoint{167, 17}, finalcut::FSize{20, 1});
  findEntry->setText(L"&Kontakt finden");
  /* ### */

  /* Adresslistenansicht erstellen & befüllen */
  finalcut::FListView *adresslist = new finalcut::FListView(list);
  adresslist->setGeometry(finalcut::FPoint{2, 2}, finalcut::FSize{150, 40});
  adresslist->addColumn("Nachname");
  adresslist->addColumn("Vorname");
  adresslist->addColumn("Geburtsdatum");
  adresslist->addColumn("Telefon");
  adresslist->addColumn("Straße");
  adresslist->addColumn("Hausnummer");
  adresslist->addColumn("PLZ");
  adresslist->addColumn("Wohnort");
  
  findEntry->addCallback(
      "clicked",
      &cb_findEntry,
      lastname, firstname, dob, phone, street, number, zip, city, search, input);

  openPath->addCallback(
      "clicked",
      &cb_openPath,
      filepath, adresslist);

  //fillList(adresslist, "contacts2");
 
  fillList(adresslist, input);

  /* Setzt das Hauptfenster als sog. "Main Widget" & stellt es dar */
  finalcut::FWidget::setMainWidget(adress);
  adress->show();

  return app.exec();
}