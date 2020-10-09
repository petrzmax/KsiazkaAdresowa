using namespace std;

#ifndef STRUKTURY_H
    #define STRUKTURY_H

    struct Adresat {
        int id = 0, idUzytkownika;
        string imie, nazwisko, numerTelefonu, email, adres;
    };

    struct Uzytkownik {
        int idUzytkownika;
        string nazwaUzytkownika, haslo;
    };

#endif
