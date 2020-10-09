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

// USTAWIENIA
#define NAZWA_PLIKU_Z_UZYTKOWNIKAMI "uzytkownicy.txt"
#define NAZWA_PLIKU_Z_ADRESATAMI "adresaci.txt"
#define NAZWA_PLIKU_TYMCZASOWEGO "adresaci_tymczasowy.txt"
#define CZAS_WYSWIETLANIA_WIADOMOSCI 1500


struct Adresat {
    int id = 0, idUzytkownika = 0;;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik {
    int idUzytkownika = 0;
    string nazwaUzytkownika, haslo;
};

void wyswietlKomunikat(string komunikat) {
    cout << komunikat;
    Sleep(CZAS_WYSWIETLANIA_WIADOMOSCI);
}

int znajdzNajwiekszeIdAdresataWPliku(vector<Adresat> adresaci) {
    int najwiekszeId = 0;
    string wiersz, sprawdzaneId;
    fstream plik;
    const int MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA = 6;

    plik.open(NAZWA_PLIKU_Z_ADRESATAMI, ios::in);

    if(plik.good())
        while(!plik.eof()) {
            getline(plik, wiersz);

            if(wiersz.length() < MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA) break;

            istringstream strumienWiersza(wiersz);
            getline(strumienWiersza, sprawdzaneId, '|');

            if(atoi(sprawdzaneId.c_str()) > najwiekszeId)
                najwiekszeId = atoi(sprawdzaneId.c_str());
        }

    return najwiekszeId;
}

int znajdzNajwiekszeIdUzytkownika(vector<Uzytkownik> uzytkownicy) {
    int najwiekszeId = 0;

    vector<Uzytkownik>::iterator koncowyIterator = uzytkownicy.end();
    vector<Uzytkownik>::iterator itr = uzytkownicy.begin();

    for(itr; itr != koncowyIterator; ++itr)
        if(itr->idUzytkownika > najwiekszeId)
            najwiekszeId = itr->idUzytkownika;

    return najwiekszeId;
}

void wyczyscPlik(string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku,ios::out | ios::trunc);
    plik.close();
}

void zapiszUzytkownikaDoPliku(Uzytkownik uzytkownik) {
    fstream plik;
    plik.open(NAZWA_PLIKU_Z_UZYTKOWNIKAMI, ios::out | ios::app);

    plik << uzytkownik.idUzytkownika << '|'
         << uzytkownik.nazwaUzytkownika << '|'
         << uzytkownik.haslo << endl;

    plik.close();
}

void aktualizujPlikUzytkownikow(vector<Uzytkownik> uzytkownicy) {
    vector<Uzytkownik>::iterator koncowyIterator = uzytkownicy.end();
    vector<Uzytkownik>::iterator itr = uzytkownicy.begin();

    wyczyscPlik(NAZWA_PLIKU_Z_UZYTKOWNIKAMI);

    for(itr; itr != koncowyIterator; ++itr)
        zapiszUzytkownikaDoPliku(*itr);
}

void stworzNowegoUzytkownika(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik;

    system("cls");
    cout << "Podaj nazwe uzytkownika: ";
    cin >> nowyUzytkownik.nazwaUzytkownika;

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    while(iteratorUzytkownika != iteratorKoncowy) {
        if(iteratorUzytkownika->nazwaUzytkownika == nowyUzytkownik.nazwaUzytkownika) {
            cout << "Taki uzytkownik juz istnieje! Wpisz inna nazwe uzytkownika: ";
            cin >> nowyUzytkownik.nazwaUzytkownika;
            iteratorUzytkownika = uzytkownicy.begin();
        } else
            ++iteratorUzytkownika;
    }

    cout << "Podaj haslo: ";
    cin >> nowyUzytkownik.haslo;
    nowyUzytkownik.idUzytkownika = znajdzNajwiekszeIdUzytkownika(uzytkownicy) + 1;

    uzytkownicy.push_back(nowyUzytkownik);
    zapiszUzytkownikaDoPliku(nowyUzytkownik);

    wyswietlKomunikat("Konto zalozone!");
}

int logowanie(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik logowanyUzytkownik;
    const int ILOSC_PROB = 3;

    system("cls");

    cout << "Podaj nazwe uzytkownika: ";
    cin >> logowanyUzytkownik.nazwaUzytkownika;

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    while(iteratorUzytkownika != iteratorKoncowy) {
        if(iteratorUzytkownika->nazwaUzytkownika == logowanyUzytkownik.nazwaUzytkownika) {
            for(int i = 0; i < ILOSC_PROB; i++) {
                cout << "Podaj haslo. Pozostalo prob " << ILOSC_PROB - i << ": ";
                cin >> logowanyUzytkownik.haslo;
                if(logowanyUzytkownik.haslo == iteratorUzytkownika->haslo) {
                    cout << "Zalogowales sie!";
                    return iteratorUzytkownika->idUzytkownika;
                }
            }
            cout << "Podales 3 razy bledne haslo. Program zablokowany na 3 sekundy!";
            Sleep(3000);
            return 0;
        } else
            ++iteratorUzytkownika;
    }

    wyswietlKomunikat("Nie udalo sie zalogowac.");
    return 0;
}

void zmienHaslo(vector<Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika) {
    string noweHaslo;

    system("cls");
    cout << "Podaj nowe haslo: ";
    cin >> noweHaslo;

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    for(iteratorUzytkownika; iteratorUzytkownika != iteratorKoncowy; ++iteratorUzytkownika)
        if(iteratorUzytkownika->idUzytkownika == idZalogowanegoUzytkownika)
            iteratorUzytkownika->haslo = noweHaslo;

    aktualizujPlikUzytkownikow(uzytkownicy);
    wyswietlKomunikat("Haslo pomyslnie zmienione!");
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy) {
    fstream plik;
    string wiersz, idUzytkownika, nazwaUzytkownika, haslo;
    const int MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA = 5;

    plik.open(NAZWA_PLIKU_Z_UZYTKOWNIKAMI, ios::in);

    if(plik.good()) {
        while(!plik.eof()) {
            getline(plik, wiersz, '\n');

            if(wiersz.length() < MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA) break;

            istringstream strumienWiersza(wiersz);

            Uzytkownik wczytywanyUzytkownik;

            getline(strumienWiersza,idUzytkownika, '|');
            getline(strumienWiersza,nazwaUzytkownika, '|');
            getline(strumienWiersza,haslo);

            wczytywanyUzytkownik.idUzytkownika = atoi(idUzytkownika.c_str());
            wczytywanyUzytkownik.nazwaUzytkownika = nazwaUzytkownika;
            wczytywanyUzytkownik.haslo = haslo;

            uzytkownicy.push_back(wczytywanyUzytkownik);
        }

        plik.close();
        return;
    } else {
        plik.close();
        return;
    }
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    fstream plik;
    string wiersz, id, idUzytkownika, imie, nazwisko, numerTelefonu, email, adres;
    const int MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA = 9;

    plik.open(NAZWA_PLIKU_Z_ADRESATAMI, ios::in);

    if(plik.good()) {
        while(!plik.eof()) {
            getline(plik, wiersz, '\n');

            if(wiersz.length() < 6) break;

            istringstream strumienWiersza(wiersz);

            Adresat wczytywanyAdresat;

            getline(strumienWiersza,id, '|');
            getline(strumienWiersza,idUzytkownika, '|');
            getline(strumienWiersza,imie, '|');
            getline(strumienWiersza,nazwisko, '|');
            getline(strumienWiersza,numerTelefonu, '|');
            getline(strumienWiersza,email, '|');
            getline(strumienWiersza,adres, '|');

            wczytywanyAdresat.id = atoi(id.c_str());
            wczytywanyAdresat.idUzytkownika = atoi(idUzytkownika.c_str());
            wczytywanyAdresat.imie = imie;
            wczytywanyAdresat.nazwisko = nazwisko;
            wczytywanyAdresat.numerTelefonu = numerTelefonu;
            wczytywanyAdresat.email = email;
            wczytywanyAdresat.adres = adres;

            if(wczytywanyAdresat.idUzytkownika == idZalogowanegoUzytkownika)
                adresaci.push_back(wczytywanyAdresat);
        }

        plik.close();
        return;
    } else {
        plik.close();
        return;
    }
}

void zapiszAdresataDoPliku(Adresat adresat) {
    fstream plik;
    plik.open(NAZWA_PLIKU_Z_ADRESATAMI,ios::out | ios::app);

    plik << adresat.id << '|'
         << adresat.idUzytkownika << '|'
         << adresat.imie << '|'
         << adresat.nazwisko << '|'
         << adresat.numerTelefonu << '|'
         << adresat.email << '|'
         << adresat.adres << '|' << endl;

    plik.close();
}

void aktualizujPlikAdresatow(vector<Adresat> adresaci, int idEdytowanegoAdresata) {

    fstream plikWejscia, plikWyjscia;
    bool usuwanie = false;
    string wiersz, idAdresata;

    const int MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA = 6;

    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator itr = adresaci.begin();

    for(itr; itr != koncowyIterator; ++itr)
        if(itr->id == idEdytowanegoAdresata) break;

    if(itr == koncowyIterator) usuwanie = true;

    plikWejscia.open(NAZWA_PLIKU_Z_ADRESATAMI, ios::in);
    plikWyjscia.open(NAZWA_PLIKU_TYMCZASOWEGO, ios::out);

    if(plikWejscia.good())
        while(!plikWejscia.eof()) {
            getline(plikWejscia,wiersz);

            if(wiersz.length() < MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA) break;

            istringstream strumienWiersza(wiersz);
            getline(strumienWiersza, idAdresata, '|');

            if(atoi(idAdresata.c_str()) == idEdytowanegoAdresata) {
                if(usuwanie) continue;
                else {
                    plikWyjscia << itr->id << '|'
                                << itr->idUzytkownika << '|'
                                << itr->imie << '|'
                                << itr->nazwisko << '|'
                                << itr->numerTelefonu << '|'
                                << itr->email << '|'
                                << itr->adres << '|' << endl;
                }
            } else plikWyjscia << wiersz << endl;
        }

    plikWejscia.close();
    plikWyjscia.close();

    remove(NAZWA_PLIKU_Z_ADRESATAMI);
    rename(NAZWA_PLIKU_TYMCZASOWEGO, NAZWA_PLIKU_Z_ADRESATAMI);
}

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika) {
    system("cls");

    Adresat nowyAdresat;
    nowyAdresat.id = znajdzNajwiekszeIdAdresataWPliku(adresaci)+1;
    nowyAdresat.idUzytkownika = idZalogowanegoUzytkownika;

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

    zapiszAdresataDoPliku(nowyAdresat);

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
            if(itr->imie == imie)
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
            if(itr->nazwisko == nazwisko)
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

void usunAdresata(vector<Adresat> &adresaci) {
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
    aktualizujPlikAdresatow(adresaci, idOsobyDoUsuniecia);
    wyswietlKomunikat("Adresat usuniety!");
}

void edytujAdresata(vector<Adresat> &adresaci) {
    char wybor;
    int idAdresataDoEdycji;

    system("cls");

    cout << "Podaj id adresata, ktorego dane chcesz edytowac: ";

    cin >> idAdresataDoEdycji;

    vector<Adresat>::iterator koncowyIterator = adresaci.end();
    vector<Adresat>::iterator iteratorEdytowanegoAdresata = adresaci.begin();

    for(iteratorEdytowanegoAdresata; iteratorEdytowanegoAdresata != koncowyIterator; ++iteratorEdytowanegoAdresata)
        if(iteratorEdytowanegoAdresata->id == idAdresataDoEdycji) break;

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
        cin >> iteratorEdytowanegoAdresata->imie;
        break;

    case '2':
        cout << "Podaj nowe nazwisko: ";
        cin >> iteratorEdytowanegoAdresata->nazwisko;
        break;

    case '3':
        cout << "Podaj nowy numer telefonu: ";
        cin >> iteratorEdytowanegoAdresata->numerTelefonu;
        break;

    case '4':
        cout << "Podaj nowy email: ";
        cin >> iteratorEdytowanegoAdresata->email;
        break;

    case '5':
        cout << "Podaj nowy adres: ";
        cin >> iteratorEdytowanegoAdresata->adres;
        break;

    case '6':
        return;
    default:
        wyswietlKomunikat("Opcja nie istnieje!");
        return;
    }

    aktualizujPlikAdresatow(adresaci, idAdresataDoEdycji);
    wyswietlKomunikat("Dane pomyslnie zmienione!");
}

int main() {
    char wybor;
    int idZalogowanegoUzytkownika = 0;

    vector<Uzytkownik> uzytkownicy;
    vector<Adresat> adresaci;

    wczytajUzytkownikowZPliku(uzytkownicy);

    while(true) {
        system("cls");
        if(idZalogowanegoUzytkownika == 0) {
            cout << "1. Rejestracja\n"
                 << "2. Logowanie\n"
                 << "9. Zamknij program\n";
            cin >> wybor;

            if(wybor == '1') stworzNowegoUzytkownika(uzytkownicy);
            else if(wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                if(idZalogowanegoUzytkownika > 0)
                    wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
            } else exit(0);
        } else {

            cout << "KSIAZKA ADRESOWA\n"
                 << "1. Dodaj adresata\n"
                 << "2. Wyszukaj po imieniu\n"
                 << "3. Wyszukaj po nazwisku\n"
                 << "4. Wyswietl wszystkich adresatow\n"
                 << "5. Usun adresata\n"
                 << "6. Edytuj adresata\n"
                 << "7. Zmien haslo\n"
                 << "9. Wyloguj\n"
                 << "Twoj wybor: ";

            cin.sync();
            cin >> wybor;

            if(wybor == '1') dodajAdresata(adresaci, idZalogowanegoUzytkownika);
            else if(wybor == '2') wyswietlAdresatowOImieniu(adresaci);
            else if(wybor == '3') wyswietlAdresatowONazwisku(adresaci);
            else if(wybor == '4') wyswietlWszystkichAdresatow(adresaci);
            else if(wybor == '5') usunAdresata(adresaci);
            else if(wybor == '6') edytujAdresata(adresaci);
            else if(wybor == '7') zmienHaslo(uzytkownicy, idZalogowanegoUzytkownika);
            else if(wybor == '9') {
                idZalogowanegoUzytkownika = 0;
                adresaci.clear();
            } else wyswietlKomunikat("Opcja nie istnieje!");
        }
    }
    return 0;
}
