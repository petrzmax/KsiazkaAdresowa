#include <iostream>
#include <algorithm>
#include <iterator>
#include "struktury.h"
#include "Uzytkownik.h"
#include "obslugaEkranu.h"
#include "obslugaPlikow.h"

using namespace std;

//-----------USTAWIENIA-----------
// LOGOWANIE
#define ILOSC_PROB_LOGOWANIA 3

int znajdzNajwiekszeIdUzytkownika(vector<Uzytkownik> uzytkownicy) {
    return uzytkownicy.back().pobierzId();
}

void stworzNowegoUzytkownika(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik nowyUzytkownik(znajdzNajwiekszeIdUzytkownika(uzytkownicy) + 1);

    system("cls");
    nowyUzytkownik.ustawNazweUzytkownika();

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    while(iteratorUzytkownika != iteratorKoncowy) {
        if(iteratorUzytkownika->pobierzNazweUzytkownika() == nowyUzytkownik.pobierzNazweUzytkownika()) {
            cout << "Taki uzytkownik juz istnieje! Wpisz inna nazwe uzytkownika.\n";
            nowyUzytkownik.ustawNazweUzytkownika();
            iteratorUzytkownika = uzytkownicy.begin();
        } else
            ++iteratorUzytkownika;
    }

    nowyUzytkownik.ustawHaslo();

    uzytkownicy.push_back(nowyUzytkownik);
    zapiszUzytkownikaDoPliku(nowyUzytkownik);

    wyswietlKomunikat("Konto zalozone!");
}

int logowanie(vector<Uzytkownik> &uzytkownicy) {
    Uzytkownik logowanyUzytkownik;
    string haslo;

    system("cls");

    logowanyUzytkownik.ustawNazweUzytkownika();

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    while(iteratorUzytkownika != iteratorKoncowy) {
        if(iteratorUzytkownika->pobierzNazweUzytkownika() == logowanyUzytkownik.pobierzNazweUzytkownika()) {
            for(int i = 0; i < ILOSC_PROB_LOGOWANIA; i++) {
                cout << "Podaj haslo. Pozostalo prob " << ILOSC_PROB_LOGOWANIA - i << ": ";
                cin >> haslo;
                if(iteratorUzytkownika->zaloguj(haslo)) {
                    wyswietlKomunikat("Zalogowales sie!");
                    return iteratorUzytkownika->pobierzId();
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

    vector<Uzytkownik>::iterator iteratorUzytkownika = uzytkownicy.begin();
    vector<Uzytkownik>::iterator iteratorKoncowy = uzytkownicy.end();

    for(iteratorUzytkownika; iteratorUzytkownika != iteratorKoncowy; ++iteratorUzytkownika)
        if(iteratorUzytkownika->pobierzId() == idZalogowanegoUzytkownika){
            iteratorUzytkownika->zmienHaslo();
        }

    aktualizujPlikUzytkownikow(uzytkownicy);
    wyswietlKomunikat("Haslo pomyslnie zmienione!");
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

    wybor = wybierzOpcjeZMenuEdycji();

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

            wybor = wybierzOpcjeZMenuLogowania();

            if(wybor == '1') stworzNowegoUzytkownika(uzytkownicy);
            else if(wybor == '2') {
                idZalogowanegoUzytkownika = logowanie(uzytkownicy);
                if(idZalogowanegoUzytkownika > 0)
                    wczytajAdresatowZPliku(adresaci, idZalogowanegoUzytkownika);
            } else exit(0);
        } else {

            wybor = wybierzOpcjeZMenu();

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
