#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
#include <fstream>
#include <conio.h>
using namespace std;

struct Adresat {
    int id = 0;
    string imie = "", nazwisko = "", numerTelefonu = "", email = "", adres = "";
};
int dodajOsobe(vector <Adresat> &adresaci, int iloscOsob) {
    string imie, nazwisko, numerTelefonu, email, adres;
    int szukajNajwiekszegoId, osobaId;
    system("cls");
    cout << "Dodawanie osoby" << endl;
    cout << "Podaj imie uzytkownika: ";
    cin >> imie;
    cout << "Podaj nazwisko uzytkownika: ";
    cin >> nazwisko;
    cout << "Podaj numer telefonu uzytkownika: ";
    cin.sync();
    getline(cin, numerTelefonu);
    cout << "Podaj email uzytkownika: ";
    cin >> email;
    cout << "Podaj adres uzytkownika: ";
    cin.sync();
    getline(cin, adres);

    osobaId = 1;

    if(adresaci.size()>0) {
        szukajNajwiekszegoId=adresaci[0].id;
        for(int i =1; i<adresaci.size(); i++) {
            if (szukajNajwiekszegoId<adresaci[i].id)
                szukajNajwiekszegoId=adresaci[i].id;
        }
        osobaId=szukajNajwiekszegoId+1;
    }
    adresaci.push_back(Adresat());
    adresaci[iloscOsob].id = osobaId;
    adresaci[iloscOsob].imie = imie;
    adresaci[iloscOsob].nazwisko = nazwisko;
    adresaci[iloscOsob].numerTelefonu = numerTelefonu;
    adresaci[iloscOsob].email = email;
    adresaci[iloscOsob].adres = adres;

    fstream plik;
    plik.open("KsiazkaAdresowa.txt", ios::out | ios::app);
    if (plik.good()) {
        plik << adresaci[iloscOsob].id<<"|"
             <<adresaci[iloscOsob].imie<<"|"
             <<adresaci[iloscOsob].nazwisko<<"|"
             <<adresaci[iloscOsob].numerTelefonu<<"|"
             <<adresaci[iloscOsob].email <<"|"
             << adresaci[iloscOsob].adres <<"|"<<endl;


        plik.close();

        cout << "Osoba zostala dodana." << endl;
        Sleep(1000);
    } else {
        cout << "Nie mozna otworzyc pliku: KsiazkaAdresowa.txt" << endl;
    }
    iloscOsob++;
    return iloscOsob;
}


int wczytajOsobyZPliku(vector <Adresat> &adresaci, int iloscOsob) {
    fstream plik;
    plik.open("KsiazkaAdresowa.txt",ios::in);

    if(plik.good()==false) {
        cout<<"Plik nie istnieje!";
        Sleep(1000);
    }
    string linia, pamiec;
    size_t pozycja;
    while(getline(plik,linia)) {

        adresaci.push_back(Adresat());
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].id = atoi(pamiec.c_str());
        linia.erase(0,pozycja+1);
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].imie = pamiec;
        linia.erase(0,pozycja+1);
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].nazwisko = pamiec;
        linia.erase(0,pozycja+1);
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].numerTelefonu = pamiec;
        linia.erase(0,pozycja+1);
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].email = pamiec;
        linia.erase(0,pozycja+1);
        pozycja=linia.find('|');
        pamiec = linia.substr(0,pozycja);
        adresaci[iloscOsob].adres = pamiec;
        iloscOsob++;
    }

    plik.close();

    return iloscOsob;
}

void szukajPoImieniu(vector <Adresat> &adresaci,int iloscOsob, string szukajImie) {
    cout <<endl;
    int licznik = 0;
    for (int i = 0; i<iloscOsob; i++) {
        if (szukajImie==adresaci[i].imie) {
            cout << adresaci[i].id << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl;
            cout <<endl;
            licznik++;
        }
    }
    if (licznik == 0)
        cout << "Brak uzytkownika o imieniu " << szukajImie;

    getch();

}

void szukajPoNazwisku(vector <Adresat> &adresaci,int iloscOsob, string szukajNazwisko) {
    cout <<endl;
    int licznik = 0;
    for (int i = 0; i<iloscOsob; i++) {
        if (szukajNazwisko==adresaci[i].nazwisko) {
            cout << adresaci[i].id << endl;
            cout << adresaci[i].imie << endl;
            cout << adresaci[i].nazwisko << endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].email << endl;
            cout << adresaci[i].adres << endl;
            cout <<endl;
            licznik++;
        }
    }
    if (licznik == 0)
        cout << "Brak uzytkownika o nazwisku " << szukajNazwisko;
    getch();
}

void wypiszWszystkich(vector <Adresat> &adresaci,int iloscOsob) {
    cout <<endl;
    for (int i = 0; i <iloscOsob; i++) {
        cout << adresaci[i].id << endl;
        cout << adresaci[i].imie << endl;
        cout << adresaci[i].nazwisko << endl;
        cout << adresaci[i].numerTelefonu << endl;
        cout << adresaci[i].email << endl;
        cout << adresaci[i].adres << endl;
        cout <<endl;
    }
    getch();
}

int usunUzytkownika(vector <Adresat> &adresaci,int iloscOsob) {
    int idLiczba;
    string linijka, idTekst;
    char znak;
    cout <<"Wprowadz ID adresata, ktorego chcesz usunac: "<<endl;
    cin>>idLiczba;
    for (int i = 0; i<=adresaci.size(); i++) {
        if (adresaci[i].id==idLiczba) {
            cout << "Czy chcesz usunac uztkownika o ID: "<<idLiczba<<" wcisnij t"<<endl;
            cin>>znak;
            if(znak = 't')   {
                idTekst = to_string(idLiczba);
                idTekst = idTekst+'|';


                fstream wejscie;
                wejscie.open("KsiazkaAdresowa.txt", ios::in );
                ofstream wyjscie;
                wyjscie.open("tymczasowy.txt",ios::out);
                if (wejscie.good()) {
                    {
                        while(getline(wejscie,linijka)) {
                            if(linijka.find(idTekst))
                                wyjscie << linijka <<endl;
                        }
                    }
                    wejscie.close();
                    wyjscie.close();
                    remove("KsiazkaAdresowa.txt");
                    rename("tymczasowy.txt","KsiazkaAdresowa.txt");
                    cout << "Osoba zostala usunieta." << endl;
                    adresaci.erase(adresaci.begin()+i);
                    iloscOsob--;
                    Sleep(1000);
                }
            }
        }
    }
    if(idTekst=="") {
        cout<< "Brak uzytkownika o podanym ID."<<endl;
        Sleep(1000);
    }
    return iloscOsob;
}
void edycja(const vector <Adresat> &adresaci) {

    ofstream wyjscie;
    wyjscie.open("tymczasowy.txt",ios::out);
    if (wyjscie.good()) {
        {
            for(int i =0; i < adresaci.size(); i++) {
                wyjscie << adresaci[i].id<<"|"<<adresaci[i].imie<<"|"<<adresaci[i].nazwisko<<"|"<<adresaci[i].numerTelefonu
                        <<"|"<<adresaci[i].email <<"|"<< adresaci[i].adres <<"|"<<endl;
            }
        }

        wyjscie.close();
        remove("KsiazkaAdresowa.txt");
        rename("tymczasowy.txt","KsiazkaAdresowa.txt");
        cout << "Dane uzytkownika zostaly zmienione." << endl;
        Sleep(1000);
    }

}

int edytujUzytkownika(vector <Adresat> &adresaci,int iloscOsob) {
    int idLiczba;
    string zmiana, idTekst;
    char znak='0';
    cout <<"Wprowadz ID adresata, ktorego chcesz edytowac: "<<endl;
    cin>>idLiczba;
    for (int i = 0; i<=adresaci.size(); i++) {
        if (adresaci[i].id==idLiczba) {
            cout << "Wybierz co chcesz zmienic:"<<endl;
            cout << "1. Imie" << endl;
            cout << "2. Nazwisko" << endl;
            cout << "3. numer telefonu" << endl;
            cout << "4. email" << endl;
            cout << "5. adres" << endl;
            cout << "6. Powrot do menu" << endl;
            cout << "Twoj wybor: ";
            cin >> znak;
            idTekst = to_string(idLiczba)+'|';
            if(znak == '1') {
                cout << "Wprowadz nowe imie: "<< endl;
                cin >> zmiana;
                adresaci[i].imie = zmiana;
                edycja(adresaci);
            } else if (znak == '2') {
                cout << "Wprowadz nowe nazwisko: "<< endl;
                cin >> zmiana;
                adresaci[i].nazwisko = zmiana;
                edycja(adresaci);
            } else if (znak == '3') {
                cout << "Wprowadz nowy numer telefonu: "<< endl;
                cin >> zmiana;
                adresaci[i].numerTelefonu = zmiana;
                edycja(adresaci);
            } else if (znak == '4') {
                cout << "Wprowadz nowy email: "<< endl;
                cin >> zmiana;
                adresaci[i].email = zmiana;
                edycja(adresaci);
            } else if (znak == '5') {
                cout << "Wprowadz nowy adres: "<< endl;
                cin.sync();
                getline(cin,zmiana);
                adresaci[i].adres = zmiana;
                edycja(adresaci);
            } else if (znak == '6') {

            }
        }

    }
    if(idTekst=="") {
        cout<< "Brak uzytkownika o podanym ID."<<endl;
        Sleep(1000);
    }
    return iloscOsob;
}

int main() {
    int iloscOsob =0;
    vector <Adresat> adresaci;
    string szukajImie, szukajNazwisko, idTekst;
    iloscOsob = wczytajOsobyZPliku(adresaci,iloscOsob);
    char wybor;

    while (true) {
        system("cls");
        cout << "1. Dodaj adresata" << endl;
        cout << "2. Wyszukaj po imieniu" << endl;
        cout << "3. Wyszukaj po nazwisku" << endl;
        cout << "4. Wyswietl wszystkich adresatow" << endl;
        cout << "5. Usun adresata" << endl;
        cout << "6. Edytuj adresata" << endl;
        cout << "9. Zakoncz program" << endl;
        cout << "Twoj wybor: ";
        cin >> wybor;

        if (wybor == '1') {
            iloscOsob = dodajOsobe(adresaci,iloscOsob);
        }
        if (wybor == '2') {
            cout << "Wprowadz Imie: " << endl;
            cin >> szukajImie;
            szukajPoImieniu(adresaci,iloscOsob,szukajImie);
        } else if (wybor == '3') {
            cout << "Wprowadz Nazwisko: " << endl;
            cin >> szukajNazwisko;
            szukajPoNazwisku(adresaci,iloscOsob,szukajNazwisko);
        } else if (wybor == '4') {
            wypiszWszystkich(adresaci, iloscOsob);
        } else if(wybor== '5') {
            iloscOsob = usunUzytkownika(adresaci,iloscOsob);
        } else if(wybor== '6') {
            iloscOsob = edytujUzytkownika(adresaci,iloscOsob) ;

        } else if (wybor == '9') {

            exit(0);
        }
    }



    return 0;
}
