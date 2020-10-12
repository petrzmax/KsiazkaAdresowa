#include "obslugaPlikow.h"

int znajdzNajwiekszeIdAdresataWPliku(vector<Adresat> adresaci) {
    int najwiekszeId = 0;
    string wiersz, sprawdzaneId;
    fstream plik;

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

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy) {
    fstream plik;
    string wiersz, idUzytkownika, nazwaUzytkownika, haslo;

    plik.open(NAZWA_PLIKU_Z_UZYTKOWNIKAMI, ios::in);

    if(plik.good()) {
        while(!plik.eof()) {
            getline(plik, wiersz, '\n');

            if(wiersz.length() < MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA) break;

            istringstream strumienWiersza(wiersz);

            getline(strumienWiersza,idUzytkownika, '|');
            getline(strumienWiersza,nazwaUzytkownika, '|');
            getline(strumienWiersza,haslo);

            Uzytkownik wczytywanyUzytkownik(atoi(idUzytkownika.c_str()), nazwaUzytkownika, haslo);

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

