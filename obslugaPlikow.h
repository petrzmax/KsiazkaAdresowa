#include <fstream>
#include <vector>
#include <sstream>

using namespace std;

// PLIKI
#define NAZWA_PLIKU_Z_UZYTKOWNIKAMI "uzytkownicy.txt"
#define NAZWA_PLIKU_Z_ADRESATAMI "adresaci.txt"
#define NAZWA_PLIKU_TYMCZASOWEGO "adresaci_tymczasowy.txt"

struct Adresat;

int znajdzNajwiekszeIdAdresataWPliku(vector<Adresat>);
void wyczyscPlik(string);
