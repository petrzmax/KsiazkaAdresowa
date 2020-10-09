#include "obslugaEkranu.h"

void wyswietlKomunikat(string komunikat) {
    cout << komunikat;
    Sleep(CZAS_WYSWIETLANIA_KOMUNIKATU);
}

char pobierzZnak() {
    string znak;

    while(true) {
        cin >> znak;
        if(znak.length() > 1)
            cout << "To nie jest pojedynczy znak!\n";
        else
            return znak[0];
    }
}

char wybierzOpcjeZMenu() {
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
    return pobierzZnak();
}

char wybierzOpcjeZMenuEdycji() {
    cout << "\nWybierz dane do edycji:\n"
         << "1. Imie\n"
         << "2. Nazwisko\n"
         << "3. Numer telefonu\n"
         << "4. Email\n"
         << "5. Adres\n"
         << "6. Powrot do menu\n";
    return pobierzZnak();
}

char wybierzOpcjeZMenuLogowania() {
    cout << "1. Rejestracja\n"
         << "2. Logowanie\n"
         << "9. Zamknij program\n";
    return pobierzZnak();
}

char wybierzOpcjeZMenuWyszukiwania() {
    cout << "\nKSIAZKA ADRESOWA\n"
         << "1. Wyszukaj kolejna osobe\n2. Powrot do menu\n";

    return pobierzZnak();
}

void wyswietlRubrykeOsob() {
    cout << left << setw(5) << "id"
         << left << setw(15) << "Imie"
         << left << setw(15) << "Nazwisko"
         << left << setw(15) << "Nr Telefonu"
         << left << setw(25) << "Email"
         << left << setw(25) << "Adres" << endl;
}

