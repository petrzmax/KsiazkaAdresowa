#include <fstream>
#include <vector>
#include <sstream>
#include "struktury.h"
#include "Uzytkownik.h"

using namespace std;

//-----------USTAWIENIA-----------
#define MINIMALNA_DLUGOSC_POPRAWNEGO_WIRSZA 5
#define NAZWA_PLIKU_Z_UZYTKOWNIKAMI "uzytkownicy.txt"
#define NAZWA_PLIKU_Z_ADRESATAMI "adresaci.txt"
#define NAZWA_PLIKU_TYMCZASOWEGO "adresaci_tymczasowy.txt"

int znajdzNajwiekszeIdAdresataWPliku(vector<Adresat>);
void wyczyscPlik(string);
void zapiszUzytkownikaDoPliku(Uzytkownik);
void aktualizujPlikUzytkownikow(vector<Uzytkownik>);
void wczytajUzytkownikowZPliku(vector<Uzytkownik> &);
void wczytajAdresatowZPliku(vector<Adresat> &, int);
void zapiszAdresataDoPliku(Adresat adresat);
void aktualizujPlikAdresatow(vector<Adresat>, int);
