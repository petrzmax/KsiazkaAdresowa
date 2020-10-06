#include <iostream>
#include <windows.h>
#include <conio.h>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

/*
Plan main / menu:
1. Utworz tablice osob adresaci[100] oraz int iloscAdresatow = 0;
2. Jesli istnieje plik adresaci.txt wczytaj z niego dane do tablicy
    i do iloscAdresatow wpisz ilosc zaladowanych osob.
3.Wyswietl menu programu.

Plan dodajAdresata(vector<Adresat> &adresaci, int &iloscAdresatow)
1. W nowyAdresat Zapisz dane nowego adresata
2. Wczytaj imie nazwisko itp.
3. Nadaj osobie id rowne iloscAdresatow
4. Zwieksz zmienna iloscAdresatow o 1

Plan wyswietlWszystkichAdresatow(vector<Adresat> &adresaci, int iloscAdresatow)
1. Wyczysc ekran
2. w petli for przejdz po elementach adresaci[] tyle razy ile iloscAdresatow
3. Wypisz kazda osobe: id tab Imie tab nazwisko tab itp. endl
4. Zaczekaj na wcisniecie dowolnego klawisza

Plan wyswietlAdresatowOImieniu(vector<Adresat> &adresaci, int iloscAdresatow, string imie)
1. Wyczysc ekran
2. w petli for przejdz po elementach adresaci[] tyle razy ile iloscAdresatow
3. Wypisz kazda osobe, ktorej imie jest rowne imie.
4. Zaczekaj na wcisniecie dowolnego klawisza

Plan int wczytajAdresatowZPliku(vector<Adresat> &adresaci, string nazwaPliku)
1. Otworz plik nazwaPliku w trybie odczytu.
2. Jezeli nie istnieje zwroc 0
    Jezeli plik istnieje to przejdz w petli po wszystkich liniach
3. Wczytuj kazdy fragment do odpowiedniej zmiennej string. Dane sa oddzielone tabulatorami.
4. Przypisz odczytane stringi do odpowiednich zmiennych w tablicy adresaci, konwertujac na odpowiedni typ.
5. Co kazda odczytana linie zwiekszaj licznik iloscAdresatow.
6. Zamknij plik.
7. Zwroc iloscAdresatow.

Plan void zapiszAdresatowDoPliku(Adresat adresat, string nazwaPliku)
1. Otworz plik nazwaPliku w trybie dopisywania.
2. Dopisz dane przekazanego adresata
3. Zamknij plik.

*/

#define CZAS_WYSWIETLANIA_WIADOMOSCI 1500

struct Adresat {
    int id = 0;
    string imie, nazwisko, numerTelefonu, email, adres;
};

void wyswietlKomunikat(string komunikat) {
    cout << komunikat;
    Sleep(CZAS_WYSWIETLANIA_WIADOMOSCI);
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci, string nazwaPliku) {
    fstream plik;
    string wiersz, id, imie, nazwisko, numerTelefonu, email, adres;

    plik.open(nazwaPliku, ios::in);

    if(plik.good()) {
        while(!plik.eof()) {
            getline(plik, wiersz, '\n');

            if(wiersz.length() < 6) break;

            istringstream strumienWiersza(wiersz);

            Adresat wczytywanyAdresat;

            getline(strumienWiersza,id, '|');
            getline(strumienWiersza,imie, '|');
            getline(strumienWiersza,nazwisko, '|');
            getline(strumienWiersza,numerTelefonu, '|');
            getline(strumienWiersza,email, '|');
            getline(strumienWiersza,adres, '|');

            wczytywanyAdresat.id = atoi(id.c_str());
            wczytywanyAdresat.imie = imie;
            wczytywanyAdresat.nazwisko = nazwisko;
            wczytywanyAdresat.numerTelefonu = numerTelefonu;
            wczytywanyAdresat.email = email;
            wczytywanyAdresat.adres = adres;

            adresaci.push_back(wczytywanyAdresat);
        }

        plik.close();
        return;
    } else {
        plik.close();
        return;
    }
}

void zapiszAdresataDoPliku(Adresat adresat, string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku,ios::out | ios::app);

    plik << adresat.id << '|'
         << adresat.imie << '|'
         << adresat.nazwisko << '|'
         << adresat.numerTelefonu << '|'
         << adresat.email << '|'
         << adresat.adres << '|' << endl;

    plik.close();
}

void wyczyscPlik(string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku,ios::out | ios::trunc);
    plik.close();
}

void aktualizujPlik(vector<Adresat> adresaci, string nazwaPliku) {
    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator itr = adresaci.begin();

    wyczyscPlik(nazwaPliku);

    for(itr; itr != koncowyIterator; ++itr)
        zapiszAdresataDoPliku(*itr,nazwaPliku);

}

int znajdzNajwiekszeId(vector<Adresat> adresaci) {
    int najwiekszeId = 0;

    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator itr = adresaci.begin();

    for(itr; itr != koncowyIterator; ++itr)
        if((*itr).id > najwiekszeId)
            najwiekszeId = (*itr).id;

    return najwiekszeId;
}

void dodajAdresata(vector<Adresat> &adresaci, string nazwaPliku) {
    system("cls");

    Adresat nowyAdresat;
    nowyAdresat.id = znajdzNajwiekszeId(adresaci)+1;

    cout << "Imie: ";
    cin >> nowyAdresat.imie;
    cout << "Nazwisko: ";
    cin >> nowyAdresat.nazwisko;
    cout << "Numer telefonu: ";
    cin >> nowyAdresat.numerTelefonu;
    cout << "Email: ";
    cin >> nowyAdresat.email;
    cout << "Adres: ";

    cin.sync();
    getline(cin,nowyAdresat.adres);

    adresaci.push_back(nowyAdresat);

    zapiszAdresataDoPliku(nowyAdresat, nazwaPliku);

    wyswietlKomunikat("Adresat dodany!");
}

void wypiszAdresata(Adresat adresat) {
    cout << left << setw(5) << adresat.id
         << left << setw(15) << adresat.imie
         << left << setw(15) << adresat.nazwisko
         << left << setw(15) << adresat.numerTelefonu
         << left << setw(25) << adresat.email
         << left << setw(25) << adresat.adres << endl;
}

void wyswietlRubrykeOsob() {
    cout << left << setw(5) << "id"
         << left << setw(15) << "Imie"
         << left << setw(15) << "Nazwisko"
         << left << setw(15) << "Nr Telefonu"
         << left << setw(25) << "Email"
         << left << setw(25) << "Adres" << endl;
}

void wyswietlWszystkichAdresatow(vector<Adresat> adresaci) {
    system("cls");

    wyswietlRubrykeOsob();
    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator itr = adresaci.begin();

    for(itr; itr != koncowyIterator; ++itr)
        wypiszAdresata(*itr);

    cout << "\nWcisnij dowolny przycisk aby powrocic do menu.";
    getch();
}

void wyswietlAdresatowOImieniu(vector<Adresat> adresaci) {
    string imie;
    char wybor;

    while(true) {
        system("cls");

        cout << "Podaj imie: ";
        cin >> imie;

        wyswietlRubrykeOsob();

        vector<Adresat>::iterator koncowyIterator = adresaci.end();
        vector<Adresat>::iterator itr = adresaci.begin();

        for(itr; itr != koncowyIterator; ++itr) {
            if((*itr).imie == imie)
                wypiszAdresata(*itr);
        }
        cout << "\nKSIAZKA ADRESOWA\n"
             << "1. Wyszukaj kolejna osobe\n2. Powrot do menu\n";

        cin >> wybor;

        if(wybor == '1') continue;
        else if(wybor == '2') break;
        else {
            wyswietlKomunikat("Opcja nie istnieje!");
            break;
        }
    }
}

void wyswietlAdresatowONazwisku(vector<Adresat> adresaci) {
    string nazwisko;
    char wybor;

    while(true) {
        system("cls");

        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        wyswietlRubrykeOsob();

        vector<Adresat>::iterator koncowyIterator = adresaci.end();
        vector<Adresat>::iterator itr = adresaci.begin();

        for(itr; itr != koncowyIterator; ++itr) {
            if((*itr).nazwisko == nazwisko)
                wypiszAdresata(*itr);
        }

        cout << "\nKSIAZKA ADRESOWA\n"
             << "1. Wyszukaj kolejna osobe\n2. Powrot do menu\n";

        cin >> wybor;

        if(wybor == '1') continue;
        else if(wybor == '2') break;
        else {
            wyswietlKomunikat("Opcja nie istnieje!");
            break;
        }
    }
}

void usunAdresata(vector<Adresat> &adresaci, string nazwaPliku) {
    int idOsobyDoUsuniecia;
    char wybor;

    system("cls");

    cout << "Podaj id adresata, ktorego chcesz usunac: ";
    cin >> idOsobyDoUsuniecia;

    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator iteratorUsuwanegoAdresata = adresaci.begin();

    for(iteratorUsuwanegoAdresata; iteratorUsuwanegoAdresata != koncowyIterator; ++iteratorUsuwanegoAdresata)
        if((*iteratorUsuwanegoAdresata).id == idOsobyDoUsuniecia) break;

    if(iteratorUsuwanegoAdresata == koncowyIterator) {
        wyswietlKomunikat("Blad!\nAdresat o podanym id nie istnieje!");
        return;
    }

    system("cls");
    wyswietlRubrykeOsob();
    wypiszAdresata(*iteratorUsuwanegoAdresata);

    cout << endl;

    do {
        cout << "UWAGA!\nZa chwile adresat zostanie nieodwracalnie usuniety!"
             << "\nCzy na pewno chcesz kontynuowac?\nt - Tak, n - Nie\n";
        wybor = getch();

        switch(wybor) {
        case 't':
            cout << "Usuwanie w toku...";
            break;

        case 'n':
            wyswietlKomunikat("Usuwanie anulowane!");
            return;
            break;

        default:
            wyswietlKomunikat("Blad wyboru! ");
            system("cls");
            break;
        }
    } while (wybor != 't');


    adresaci.erase(iteratorUsuwanegoAdresata);
    aktualizujPlik(adresaci, nazwaPliku);
    wyswietlKomunikat("Adresat usuniety!");
}


void edytujAdresata(vector<Adresat> &adresaci, string nazwaPliku) {
    char wybor;
    int idAdresataDoEdycji;

    system("cls");

    cout << "Podaj id adresata, ktorego dane chcesz edytowac: ";

    cin >> idAdresataDoEdycji;

    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator iteratorEdytowanegoAdresata = adresaci.begin();

    for(iteratorEdytowanegoAdresata; iteratorEdytowanegoAdresata != koncowyIterator; ++iteratorEdytowanegoAdresata)
        if((*iteratorEdytowanegoAdresata).id == idAdresataDoEdycji) break;

    if(iteratorEdytowanegoAdresata == koncowyIterator) {
        wyswietlKomunikat("Blad!\nAdresat o podanym id nie istnieje!");
        return;
    }

    system("cls");
    wyswietlRubrykeOsob();
    wypiszAdresata(*iteratorEdytowanegoAdresata);

    cout << "\nWybierz dane do edycji:\n"
         << "1. Imie\n"
         << "2. Nazwisko\n"
         << "3. Numer telefonu\n"
         << "4. Email\n"
         << "5. Adres\n"
         << "6. Powrot do menu\n";

    cin >> wybor;

    switch(wybor) {
    case '1':
        cout << "Podaj nowe imie: ";
        cin >> (*iteratorEdytowanegoAdresata).imie;
        break;

    case '2':
        cout << "Podaj nowe nazwisko: ";
        cin >> iteratorEdytowanegoAdresata->nazwisko;
        break;

    case '3':
        cout << "Podaj nowy numer telefonu: ";
        cin >> (*iteratorEdytowanegoAdresata).numerTelefonu;
        break;

    case '4':
        cout << "Podaj nowy email: ";
        cin >> (*iteratorEdytowanegoAdresata).email;
        break;

    case '5':
        cout << "Podaj nowy adres: ";
        cin >> (*iteratorEdytowanegoAdresata).adres;
        break;

    case '6':
        return;
    default:
        wyswietlKomunikat("Opcja nie istnieje!");
        return;
    }

    aktualizujPlik(adresaci, nazwaPliku);
    wyswietlKomunikat("Dane pomyslnie zmienione!");
}

int main() {
    char wybor;
    const string NAZWA_PLIKU = "adresaci.txt";

    vector<Adresat> adresaci;

    wczytajAdresatowZPliku(adresaci, NAZWA_PLIKU);

    for(;;) {
        system("cls");
        cout << "KSIAZKA ADRESOWA\n"
             << "1. Dodaj adresata\n"
             << "2. Wyszukaj po imieniu\n"
             << "3. Wyszukaj po nazwisku\n"
             << "4. Wyswietl wszystkich adresatow\n"
             << "5. Usun adresata\n"
             << "6. Edytuj adresata\n"
             << "9. Zakoncz program\n"
             << "Twoj wybor: ";

        cin.sync();
        cin >> wybor;

        switch(wybor) {

        case '1':
            dodajAdresata(adresaci, NAZWA_PLIKU);
            break;

        case '2':
            wyswietlAdresatowOImieniu(adresaci);
            break;

        case '3':
            wyswietlAdresatowONazwisku(adresaci);
            break;

        case '4':
            wyswietlWszystkichAdresatow(adresaci);
            break;

        case '5':
            usunAdresata(adresaci, NAZWA_PLIKU);
            break;
        case '6':
            edytujAdresata(adresaci, NAZWA_PLIKU);
            break;
        case '9':
            exit(0);
            break;

        default:
            wyswietlKomunikat("Opcja nie istnieje!");
            break;
        }
    }
    return 0;
}
