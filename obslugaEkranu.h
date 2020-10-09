#include <iostream>
#include <windows.h>
#include <iomanip>
#include <vector>
#include <conio.h>
#include "struktury.h"

using namespace std;

//-----------USTAWIENIA-----------
#define CZAS_WYSWIETLANIA_KOMUNIKATU 1500

void wyswietlKomunikat(string);
char pobierzZnak();
char wybierzOpcjeZMenu();
char wybierzOpcjeZMenuEdycji();
char wybierzOpcjeZMenuLogowania();
char wybierzOpcjeZMenuWyszukiwania();
void wyswietlRubrykeOsob();
void wypiszAdresata(Adresat);
void wyswietlWszystkichAdresatow(vector<Adresat>);
void wyswietlAdresatowOImieniu(vector<Adresat>);
void wyswietlAdresatowONazwisku(vector<Adresat>);
