#include <iostream>

using namespace std;

#ifndef UZYTKOWNIK_H
    #define UZYTKOWNIK_H

class Uzytkownik {

private:
    int idUzytkownika;
    string nazwaUzytkownika, haslo;

public:
    Uzytkownik(int = 0, string = "", string = "");
    void ustawId(int);
    void ustawNazweUzytkownika();
    void ustawHaslo();
    void zmienHaslo();
    int pobierzId();
    string pobierzNazweUzytkownika();
    bool zaloguj(string);

    friend void zapiszUzytkownikaDoPliku(Uzytkownik);

};

#endif
