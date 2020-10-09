#include "obslugaPlikow.h"

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

void wyczyscPlik(string nazwaPliku) {
    fstream plik;
    plik.open(nazwaPliku,ios::out | ios::trunc);
    plik.close();
}



