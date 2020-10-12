#include "Uzytkownik.h"

Uzytkownik::Uzytkownik(int id, string n, string h)
{
    idUzytkownika = id;
    nazwaUzytkownika = n;
    haslo = h;
}

void Uzytkownik::ustawId(int id){

    idUzytkownika = id;
}

void Uzytkownik::ustawNazweUzytkownika(){

    cout << "Podaj nazwe uzytkownika: ";
    cin >> nazwaUzytkownika;
}

void Uzytkownik::ustawHaslo(){

    cout << "Podaj haslo: ";
    cin >> haslo;
}

void Uzytkownik::zmienHaslo(){

    cout << "Podaj nowe haslo: ";
    cin >> haslo;
}

int Uzytkownik::pobierzId(){

    return idUzytkownika;
}

string Uzytkownik::pobierzNazweUzytkownika(){

    return nazwaUzytkownika;
}

bool Uzytkownik::zaloguj(string h){

    if(haslo == h) return true;
    else return false;
}
