#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;


struct Uzytkownik {
    int idUser = 0;
    string login = "", haslo = "";
};

struct Adresat {
    int idAdresat = 0, idUzytkownik;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};

string wczytajLinie() {
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

char wczytajZnak() {
    string wejscie = "";
    char znak  = {0};

    while (true) {
        getline(cin, wejscie);

        if (wejscie.length() == 1) {
            znak = wejscie[0];
            break;
        }
        cout << "To nie jest pojedynczy znak. Wpisz ponownie." << endl;
    }
    return znak;
}

int wczytajLiczbeCalkowita() {
    string wejscie = "";
    int liczba = 0;

    while (true) {
        getline(cin, wejscie);

        stringstream myStream(wejscie);
        if (myStream >> liczba)
            break;
        cout << "To nie jest liczba. Wpisz ponownie. " << endl;
    }
    return liczba;
}

string konwerjsaIntNaString(int liczba) {
    ostringstream ss;
    ss << liczba;
    string str = ss.str();

    return str;
}

string zamienPierwszaLitereNaDuzaAPozostaleNaMale(string tekst) {
    if (!tekst.empty()) {
        transform(tekst.begin(), tekst.end(), tekst.begin(), ::tolower);
        tekst[0] = toupper(tekst[0]);
    }
    return tekst;
}

Adresat pobierzDaneAdresata(string daneAdresataOddzielonePionowymiKreskami) {
    Adresat adresat;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneAdresataOddzielonePionowymiKreskami.length(); pozycjaZnaku++) {
        if (daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += daneAdresataOddzielonePionowymiKreskami[pozycjaZnaku];
        } else {
            switch(numerPojedynczejDanejAdresata) {
            case 1:
                adresat.idAdresat = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 2:
                adresat.idUzytkownik = atoi(pojedynczaDanaAdresata.c_str());
                break;
            case 3:
                adresat.imie = pojedynczaDanaAdresata;
                break;
            case 4:
                adresat.nazwisko = pojedynczaDanaAdresata;
                break;
            case 5:
                adresat.numerTelefonu = pojedynczaDanaAdresata;
                break;
            case 6:
                adresat.email = pojedynczaDanaAdresata;
                break;
            case 7:
                adresat.adres = pojedynczaDanaAdresata;
                break;
            }
            pojedynczaDanaAdresata = "";
            numerPojedynczejDanejAdresata++;
        }
    }
    return adresat;
}

void wczytajAdresatowZPliku(vector<Adresat> &adresaci,int idUzytkownika, string nazwaPlikuAdresatow) {
    Adresat adresat;
    string daneJednegoAdresataOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuAdresatow.c_str(), ios::in);

    if (plikTekstowy.good()) {
        while (getline(plikTekstowy, daneJednegoAdresataOddzielonePionowymiKreskami)) {
            adresat = pobierzDaneAdresata(daneJednegoAdresataOddzielonePionowymiKreskami);
            if(idUzytkownika==adresat.idUzytkownik)
                adresaci.push_back(adresat);
        }
        plikTekstowy.close();
    }
}

void wypiszWszystkichAdresatow(vector<Adresat> &adresaci) {
    system("cls");
    if (!adresaci.empty()) {
        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            cout << "Id:                 " << itr->idAdresat << endl;
            cout << "Imie:               " << itr->imie << endl;
            cout << "Nazwisko:           " << itr->nazwisko << endl;
            cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
            cout << "Email:              " << itr->email << endl;
            cout << "Adres:              " << itr->adres << endl << endl;
        }
        cout << endl;
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }

    system("pause");
}

void dopiszAdresataDoPliku(Adresat adresat, string nazwaPlikuAdresatow) {
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuAdresatow.c_str(), ios::out | ios::app);

    if (plikTekstowy.good()) {
        plikTekstowy << adresat.idAdresat << '|';
        plikTekstowy << adresat.idUzytkownik << '|';
        plikTekstowy << adresat.imie << '|';
        plikTekstowy << adresat.nazwisko << '|';
        plikTekstowy << adresat.numerTelefonu << '|';
        plikTekstowy << adresat.email << '|';
        plikTekstowy << adresat.adres << '|' << endl;
        plikTekstowy.close();

        cout << endl << "Adresat zostal dodany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}

void wyszukajAdresatowPoImieniu(vector<Adresat> &adresaci) {
    string imiePoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O IMIENIU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o imieniu: ";
        imiePoszukiwanegoAdresata = wczytajLinie();

        imiePoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(imiePoszukiwanegoAdresata);

        for (vector<Adresat>::iterator  itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->imie == imiePoszukiwanegoAdresata) {
                cout << endl;
                cout << "Id:                 " << itr->idAdresat << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
                cout << "Email:              " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout << endl << "Nie ma adresatow z tym imieniem w ksiazce adresowej" << endl;
        } else {
            cout << endl << "Ilosc adresatow z imieniem: >>> " << imiePoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

void wyszukajAdresatowPoNazwisku(vector<Adresat> &adresaci) {
    string nazwiskoPoszukiwanegoAdresata = "";
    int iloscAdresatow = 0;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> WYSZUKIWANIE ADRESATOW O NAZWISKU <<<" << endl << endl;

        cout << "Wyszukaj adresatow o nazwisku: ";
        nazwiskoPoszukiwanegoAdresata = wczytajLinie();
        nazwiskoPoszukiwanegoAdresata = zamienPierwszaLitereNaDuzaAPozostaleNaMale(nazwiskoPoszukiwanegoAdresata);

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->nazwisko == nazwiskoPoszukiwanegoAdresata) {
                cout << endl;
                cout << "Id:                 " << itr->idAdresat << endl;
                cout << "Imie:               " << itr->imie << endl;
                cout << "Nazwisko:           " << itr->nazwisko << endl;
                cout << "Numer telefonu:     " << itr->numerTelefonu << endl;
                cout << "Email:              " << itr->email << endl;
                cout << "Adres:              " << itr->adres << endl << endl;
                iloscAdresatow++;
            }
        }
        if (iloscAdresatow == 0) {
            cout << endl << "Nie ma adresatow z tym nazwiskiem w ksiazce adresowej" << endl;
        } else {
            cout << endl << "Ilosc adresatow z nazwiskiem: >>> " << nazwiskoPoszukiwanegoAdresata << " <<<";
            cout << " w ksiazce adresowej wynosi: " << iloscAdresatow << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }
    cout << endl;
    system("pause");
}

int pobierzIdAdresataZPliku(string linijkaZDanymiAdresata) {
    int idPobraneZPliku =0;
    string pojedynczaDanaAdresata = "";
    int numerPojedynczejDanejAdresata = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < linijkaZDanymiAdresata.length(); pozycjaZnaku++) {
        if (linijkaZDanymiAdresata[pozycjaZnaku] != '|') {
            pojedynczaDanaAdresata += linijkaZDanymiAdresata[pozycjaZnaku];
        } else {
            idPobraneZPliku = atoi(pojedynczaDanaAdresata.c_str());
            break;
        }
    }
    return idPobraneZPliku;
}

void dodajAdresata(vector<Adresat> &adresaci, int idZalogowanegoUzytkownika,string nazwaPlikuAdresatow) {
    Adresat adresat;
    string daneAdresataZPliku="";
    int najwiekszeIdAdresataZPliku=0, idAdresataZPliku = 0;
    system("cls");
    cout << ">>> DODAWANIE NOWEGO ADRESATA <<<" << endl << endl;

    fstream plikTekstowy ;
    plikTekstowy.open(nazwaPlikuAdresatow.c_str());
    if (!plikTekstowy.good()) {
        adresat.idAdresat = 1;
    }
     else {
        while(getline(plikTekstowy,daneAdresataZPliku)) {
        idAdresataZPliku = pobierzIdAdresataZPliku(daneAdresataZPliku);
        if(idAdresataZPliku>najwiekszeIdAdresataZPliku)
            najwiekszeIdAdresataZPliku = idAdresataZPliku;
        }
        adresat.idAdresat = najwiekszeIdAdresataZPliku + 1;
    }
    plikTekstowy.close();

    cout << "Podaj imie: ";
    adresat.imie = wczytajLinie();
    adresat.imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.imie);

    cout << "Podaj nazwisko: ";
    adresat.nazwisko  = wczytajLinie();
    adresat.nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(adresat.nazwisko);

    cout << "Podaj numer telefonu: ";
    adresat.numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    adresat.email = wczytajLinie();

    cout << "Podaj adres: ";
    adresat.adres = wczytajLinie();

    adresat.idUzytkownik = idZalogowanegoUzytkownika;

    adresaci.push_back(adresat);

    dopiszAdresataDoPliku(adresat,nazwaPlikuAdresatow);
}

void zakonczProgram() {
    cout << endl << "Koniec programu." << endl;
    exit(0);
}
int wylogujSie(vector<Adresat> &adresaci)
{
    adresaci.clear();
    int idUzytkownika=0;
    cout << "Wylogowano"<<endl;
    Sleep(1000);
    return idUzytkownika;
}
Uzytkownik pobierzDaneUzytkownika(string daneUzytkownikaOddzielonePionowymiKreskami) {
    Uzytkownik uzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczejDanejUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += daneUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejUzytkownika)
            {
            case 1:
                uzytkownik.idUser = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                uzytkownik.login = pojedynczaDanaUzytkownika;
                break;
            case 3:
                uzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
                }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczejDanejUzytkownika++;
}
    }
    return uzytkownik;
}

void wczytajUzytkownikowZPliku(vector<Uzytkownik> &uzytkownicy,string nazwaPlikuUzytkownikow) {
    Uzytkownik uzytkownik;
    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";

    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuUzytkownikow.c_str(), ios::in);

    if (plikTekstowy.good()) {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami)) {
            uzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(uzytkownik);
        }
        plikTekstowy.close();
    }
}

void dopiszUzytkownikaDoPliku(Uzytkownik uzytkownik, string nazwaPlikuUzytkownikow) {
    fstream plikTekstowy;
    plikTekstowy.open(nazwaPlikuUzytkownikow.c_str(), ios::out | ios::app);

    if (plikTekstowy.good()) {
        plikTekstowy << uzytkownik.idUser << '|';
        plikTekstowy << uzytkownik.login << '|';
        plikTekstowy << uzytkownik.haslo << '|'<<endl;
        plikTekstowy.close();

        cout << endl << "Uzytkownik " <<uzytkownik.login <<" zostal dodany" << endl;
        system("pause");
    } else {
        cout << "Nie udalo sie otworzyc pliku i zapisac w nim danych." << endl;
        system("pause");
    }
}
void dodajUzytkownika(vector<Uzytkownik> &uzytkownicy, string nazwaPlikuUzytkownikow) {
    Uzytkownik uzytkownik;
    bool czyIstniejeUzytkownik = false;

    system("cls");
    cout << ">>> DODAWANIE NOWEGO UZYTKOWNIKA <<<" << endl << endl;

    if (uzytkownicy.empty()) {
        uzytkownik.idUser = 1;
    } else {
        uzytkownik.idUser = uzytkownicy.back().idUser + 1;
    }
    cout << "Podaj Login: ";
    uzytkownik.login = wczytajLinie();
    cout << "Podaj Haslo: ";
    uzytkownik.haslo  = wczytajLinie();
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr->login == uzytkownik.login) {
            czyIstniejeUzytkownik = true;
            cout << "Uzytkownik o podanej nazwie juz istnieje, zmien nazwe uzytkownika." <<endl<<endl;
            system("pause");
        }
    }
    if(czyIstniejeUzytkownik==false) {
        uzytkownicy.push_back(uzytkownik);
        dopiszUzytkownikaDoPliku(uzytkownik,nazwaPlikuUzytkownikow);
    }
}

int logowanie (vector <Uzytkownik> &uzytkownicy) {
    int  idUsera = 0;
    string sprawdzLogin, sprawdzHaslo;
    bool czyIstniejeUzytkownik = false;
    cout << "Wprowadz swoj login: "<<endl;
    sprawdzLogin = wczytajLinie();
    cout <<"Wpisz swoje haslo: "<<endl;
    sprawdzHaslo = wczytajLinie();
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
        if (itr->login == sprawdzLogin && itr->haslo == sprawdzHaslo) {
            czyIstniejeUzytkownik = true;
            idUsera = itr-> idUser;
            cout << "Jestes zalogowany" <<endl;
        }
    }
    if(czyIstniejeUzytkownik== false) {
        cout << "Bledny Login lub Haslo sprobuj ponownie"<<endl;
    }

    Sleep(1000);
    return idUsera;

}

void usuwanieAdresata (vector<Adresat> &adresaci, string nazwaPlikuAdresatow,  string nazwaPlikuTymczasowego)
{
    int idUsuwanegoAdresata = 0;
    char znak;
    bool czyIstniejeAdresat = false;
    string daneAdresataZPliku;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> USUWANIE WYBRANEJ OSOBY <<<" << endl << endl;
        cout << "Podaj numer ID adresata ktorego chcesz USUNAC: ";
        cin.sync();
        idUsuwanegoAdresata = wczytajLiczbeCalkowita();

            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->idAdresat == idUsuwanegoAdresata) {
                czyIstniejeAdresat = true;
                cout << endl << endl << "Potwierdz naciskajac klawisz 't': ";
                znak = wczytajZnak();
                if (znak == 't') {
                    adresaci.erase(itr);
                    cout << endl << endl << "Szukany adresat zostal USUNIETY" << endl << endl;
                fstream pobierz;
                pobierz.open(nazwaPlikuAdresatow.c_str(), ios::in );
                ofstream wypisz;
                wypisz.open(nazwaPlikuTymczasowego.c_str(),ios::out);
                if (pobierz.good())
                    {
                        while(getline(pobierz,daneAdresataZPliku)) {
                            if(idUsuwanegoAdresata!=pobierzIdAdresataZPliku(daneAdresataZPliku))
                                wypisz << daneAdresataZPliku <<endl;
                        }
                    pobierz.close();
                    wypisz.close();
                    remove(nazwaPlikuAdresatow.c_str());
                    rename(nazwaPlikuTymczasowego.c_str(),nazwaPlikuAdresatow.c_str());
                    }
                    break;
                } else {
                    cout << endl << endl << "Wybrany adresat NIE zostal usuniety" << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej" << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta" << endl << endl;
    }

    system("pause");
}
void zapiszEdytowanegoAdresata(vector<Adresat> &adresaci, int idEdytowanegoAdresata, string nazwaPlikuAdresatow, string nazwaPlikuTymczasowego)
{
    string daneAdresataZPliku="",liniaZDanymiAdresata="" ;
     fstream pobierz;
                pobierz.open(nazwaPlikuAdresatow.c_str(), ios::in );
                ofstream wypisz;
                wypisz.open(nazwaPlikuTymczasowego.c_str(),ios::out);
                if (pobierz.good())
                    {
                        while(getline(pobierz,daneAdresataZPliku)) {
                            if(idEdytowanegoAdresata==pobierzIdAdresataZPliku(daneAdresataZPliku)){

            for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
                    if(idEdytowanegoAdresata==itr->idAdresat){
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idAdresat) + '|';
            liniaZDanymiAdresata += konwerjsaIntNaString(itr->idUzytkownik) + '|';
            liniaZDanymiAdresata += itr->imie + '|';
            liniaZDanymiAdresata += itr->nazwisko + '|';
            liniaZDanymiAdresata += itr->numerTelefonu + '|';
            liniaZDanymiAdresata += itr->email + '|';
            liniaZDanymiAdresata += itr->adres + '|';
            wypisz << liniaZDanymiAdresata << endl;
                    }
                            }
                            }
                              else
                              {
                                  wypisz << daneAdresataZPliku <<endl;
                              }
                            }
                        }
                    pobierz.close();
                    wypisz.close();
                    remove(nazwaPlikuAdresatow.c_str());
                    rename(nazwaPlikuTymczasowego.c_str(),nazwaPlikuAdresatow.c_str());
                    }


void edytujAdresata(vector<Adresat> &adresaci,string nazwaPlikuAdresatow, string nazwaPlikuTymczasowego) {
    int idWybranegoAdresata = 0;
    char wybor;
    bool czyIstniejeAdresat = false;

    system("cls");
    if (!adresaci.empty()) {
        cout << ">>> EDYCJA WYBRANEGO ADRESATA <<<" << endl << endl;
        cout << "Podaj numer ID adresata u ktorego chcesz zmienic dane: ";
        idWybranegoAdresata = wczytajLiczbeCalkowita();

        for (vector<Adresat>::iterator itr = adresaci.begin(); itr != adresaci.end(); itr++) {
            if (itr->idAdresat == idWybranegoAdresata) {
                czyIstniejeAdresat = true;

                cout << endl << "Ktore dane zaktualizowac: " << endl;
                cout << "1 - Imie" << endl;
                cout << "2 - Nazwisko" << endl;
                cout << "3 - Numer telefonu" << endl;
                cout << "4 - Email" << endl;
                cout << "5 - Adres" << endl;
                cout << "6 - Powrot " << endl;
                cout << endl << "Wybierz 1-6: ";
                wybor = wczytajZnak();

                switch (wybor) {
                case '1':
                    cout << "Podaj nowe imie: ";
                    itr->imie = wczytajLinie();
                    itr->imie = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->imie);
                    cout << endl << "Imie zostalo zmienione" << endl << endl;
                    zapiszEdytowanegoAdresata(adresaci,idWybranegoAdresata,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                    break;
                case '2':
                    cout << "Podaj nowe nazwisko: ";
                    itr->nazwisko = wczytajLinie();
                    itr->nazwisko = zamienPierwszaLitereNaDuzaAPozostaleNaMale(itr->nazwisko);
                    cout << endl << "Nazwisko zostalo zmienione" << endl << endl;
            zapiszEdytowanegoAdresata(adresaci,idWybranegoAdresata,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                    break;
                case '3':
                    cout << "Podaj nowy numer telefonu: ";
                    itr->numerTelefonu = wczytajLinie();
                    cout << endl << "Numer telefonu zostal zmieniony" << endl << endl;
                    zapiszEdytowanegoAdresata(adresaci,idWybranegoAdresata,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                    break;
                case '4':
                    cout << "Podaj nowy email: ";
                    itr->email = wczytajLinie();
                    cout << endl << "Email zostal zmieniony" << endl << endl;
                  zapiszEdytowanegoAdresata(adresaci,idWybranegoAdresata,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                    break;
                case '5':
                    cout << "Podaj nowy adres zamieszkania: ";
                    itr->adres = wczytajLinie();
                    cout << endl << "Adres zostal zmieniony" << endl << endl;
                    zapiszEdytowanegoAdresata(adresaci,idWybranegoAdresata,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                    break;
                case '6':
                    cout << endl << "Powrot do menu glownego" << endl << endl;
                    break;
                default:
                    cout << endl << "Nie ma takiej opcji w menu! Powrot do menu glownego." << endl << endl;
                    break;
                }
            }
        }
        if (czyIstniejeAdresat == false) {
            cout << endl << "Nie ma takiego adresata w ksiazce adresowej." << endl << endl;
        }
    } else {
        cout << "Ksiazka adresowa jest pusta." << endl << endl;
    }
    system("pause");
}

void zmianaHasla(vector <Uzytkownik> &uzytkownicy,int idZalogowanegoUzytkownika, string nazwaPlikuUzytkownikow, string nazwaPlikuTymczasowego) {
    string stareHaslo,noweHaslo;
    bool poprawneHaslo = false;
    cout <<"Podaj swoje stare haslo: "<<endl;
    getline(cin,stareHaslo);
    for (vector<Uzytkownik>::iterator itr = uzytkownicy.begin(); itr != uzytkownicy.end(); itr++) {
    if (idZalogowanegoUzytkownika == itr-> idUser && stareHaslo==itr -> haslo) {
         poprawneHaslo = true;
        cout << "Podaj nowe haslo: "<<endl;
        getline(cin,noweHaslo);
        itr -> haslo = noweHaslo;
        ofstream wyjscie;
        wyjscie.open(nazwaPlikuTymczasowego.c_str(),ios::out);
        if (wyjscie.good()) {
            {
                for(int i =0; i < uzytkownicy.size(); i++) {
                    wyjscie << uzytkownicy[i].idUser<<"|"<<uzytkownicy[i].login<<"|"<<uzytkownicy[i].haslo<<"|"<<endl;
                }
            }
            wyjscie.close();
            remove(nazwaPlikuUzytkownikow.c_str());
            rename(nazwaPlikuTymczasowego.c_str(),nazwaPlikuUzytkownikow.c_str());
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1000);
        }

}
    }
if(poprawneHaslo==false){
    cout << "Podales bledne haslo."<<endl;
        Sleep(1000);
}
}

int main() {
    string nazwaPlikuAdresatow = "KsiazkaAdresowa.txt";
    string nazwaPlikuUzytkownikow = "Uzytkownicy.txt";
    string nazwaPlikuTymczasowego = "Ksiazka Tymczasowa.txt";
    vector<Adresat> adresaci;
    vector<Uzytkownik> uzytkownicy;
    char wybor;
    int idUzytkownika =0;
    wczytajUzytkownikowZPliku(uzytkownicy,nazwaPlikuUzytkownikow);
    while (true) {
        system("cls");
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        wybor = wczytajZnak();
        switch(wybor) {
        case '1':
            idUzytkownika = logowanie(uzytkownicy);
            wczytajAdresatowZPliku(adresaci,idUzytkownika,nazwaPlikuAdresatow);
            break;
        case '2':
            dodajUzytkownika(uzytkownicy,nazwaPlikuUzytkownikow);
            break;
        case '9':
            zakonczProgram();
            break;
        }
        while (idUzytkownika>0) {
            system("cls");
            cout << ">>> KSIAZKA ADRESOWA <<<" << endl << endl;
            cout << "1. Dodaj adresata" << endl;
            cout << "2. Wyszukaj po imieniu" << endl;
            cout << "3. Wyszukaj po nazwisku" << endl;
            cout << "4. Wyswietl wszystkich adresatow" << endl;
            cout << "5. Usun adresata" << endl;
            cout << "6. Edytuj adresata" << endl;
            cout << "7. Zmien haslo" <<endl;
            cout << "9. Wyloguj sie" << endl;
            cout << "Twoj wybor: ";
            wybor = wczytajZnak();

            switch(wybor) {
            case '1':
                dodajAdresata(adresaci,idUzytkownika,nazwaPlikuAdresatow);
                break;
            case '2':
                wyszukajAdresatowPoImieniu(adresaci);
                break;
            case '3':
                wyszukajAdresatowPoNazwisku(adresaci);
                break;
            case '4':
                wypiszWszystkichAdresatow(adresaci);
                break;
            case '5':
                usuwanieAdresata(adresaci,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                break;
            case '6':
                edytujAdresata(adresaci,nazwaPlikuAdresatow,nazwaPlikuTymczasowego);
                break;
                case '7':
            zmianaHasla(uzytkownicy,idUzytkownika,nazwaPlikuUzytkownikow,nazwaPlikuTymczasowego);
                break;
            case '9':
                idUzytkownika=wylogujSie(adresaci);
                break;
            }
        }
    }
    return 0;
}
