#include <iostream>
#include <windows.h>
#include <cstdlib>
#include <fstream>
#include <string.h>
#include <vector>
#include <cstdio>


using namespace std;

int idZalogowanegoUzytkownika =0;

int max_id =0;
int max_id_uzytkownika = 0;

struct Uzytkownik
{

    int id;
    string login, haslo;

};

void wczytajDaneZPlikuDoStrukturyUzytkownicy (vector <Uzytkownik> &uzytkownicy)
{
    int nr_linii = 1;

    string linia;
    Uzytkownik uzytkownik;

    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    if (plik.good() == false)
    {
        cout<<"Nie udalo sie otworzyc pliku";
        Sleep(1000);
    }
    else
    {

        while (getline(plik, linia))
        {
            char linijka[linia.length()];

            for (int j =0; j<linia.length(); j++)
            {
                linijka[j] = linia[j];
            }

            char *pch;
            string tablica[6];
            int i =0;

            pch = strtok (linijka, "|");
            while (pch != NULL && i<3)
            {

                tablica[i] = ("%s", pch);
                pch = strtok (NULL, "|");
                i++;
            }


            uzytkownik.id = atoi(tablica[0].c_str());

            uzytkownik.login = tablica[1];

            uzytkownik.haslo = tablica[2];


            uzytkownicy.push_back(uzytkownik);

            if (uzytkownik.id > max_id_uzytkownika)
                max_id_uzytkownika = uzytkownik.id;

            nr_linii++;
        }
    }
    plik.close();

}

int logowanie (vector <Uzytkownik> &uzytkownicy)
{

    string login, haslo;
    cout << "Podaj login: "<<endl;
    cin >> login;

    int i =0;
    while (i<uzytkownicy.size())
    {

        if (uzytkownicy[i].login == login)
        {

            for (int j=0; j<3; j++)
            {
                cout << "Podaj haslo. Pozostalo prob " << 3-j << endl;
                cin >> haslo;

                if (uzytkownicy[i].haslo == haslo)
                {
                    cout << "Zalogowales sie."<< endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }

            }
            cout << "Podales 3 razy bledne haslo. Poczekaj 3 s przed kolejna proba." << endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }

    cout << "Nie istnieje uzytkownik o podanym loginie." << endl;
    Sleep(1500);
    return 0;
}

void rejestracja (vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    int id;
    Uzytkownik uzytkownik;
    cout << "Podaj login: " << endl;
    cin >> login;

    int i =0;
    while (i<uzytkownicy.size())
    {

        if (uzytkownicy[i].login == login)
        {

            cout << "Podany uzytkownik juz istnieje. Wybierz inny login." << endl;
            cin >> login;
            i = 0;
        }
        else
            i++;
    }

    cout << "Podaj haslo: "<< endl;
    cin >> haslo;

    max_id_uzytkownika++;

    uzytkownik.login = login;
    uzytkownik.haslo = haslo;
    uzytkownik.id = max_id_uzytkownika;

    uzytkownicy.push_back(uzytkownik);


    Sleep(1000);

    fstream plik;
    if(plik.good())
    {
        plik.open("Uzytkownicy.txt",ios::out | ios::app);

        plik<<uzytkownik.id<<"|"<<uzytkownik.login<<"|"<<uzytkownik.haslo<<endl;

        plik.close();

        cout << "Konto zalozone." << endl;
        Sleep(1000);
    }

    else
    {
        cout << "Nie mozna otworzyc pliku: Uzytkownicy.txt" << endl;
    }

}

void zmianaHasla (vector <Uzytkownik> &uzytkownicy, int idZalogowanegoUzytkownika)
{
    string haslo;
    cout << "Podaj nowe haslo: " << endl;
    cin >> haslo;

    for (int i =0; i<uzytkownicy.size(); i++)
    {
        if (uzytkownicy[i].id == idZalogowanegoUzytkownika)
        {
            uzytkownicy[i].haslo = haslo;
            cout << "Haslo zostalo zmienione." << endl;
            Sleep(1500);
        }
    }

    fstream plik;
    if(plik.good())
    {
        plik.open("Uzytkownicy.txt", fstream::out | fstream::trunc);

        for(int i=0; i<uzytkownicy.size(); i++)
        {
            plik<<uzytkownicy[i].id<<"|"<<uzytkownicy[i].login<<"|"<<uzytkownicy[i].haslo<<endl;
        }
        plik.close();
    }

}

struct Adresat
{
    int id =0;
    string imie="", nazwisko="", numerTelefonu="", email="", adres="";
};


void dodajAdresataDoKsiazkiAdresowej (vector <Adresat> &adresaci)
{
    string imie, nazwisko, numerTelefonu, adres, email;
    system("cls");

    Adresat adresat;

    cout << "Podaj imie. " << endl;
    cin >> imie;
    cout << "Podaj nazwisko. " << endl;
    cin >> nazwisko;

    cout << "Podaj numer telefonu adresata." << endl;
    cin >> numerTelefonu;

    cout << "Podaj adres zamieszkania adresata." << endl;
    cin.ignore();
    getline(cin,adres);

    cout << "Podaj e-mail adresata." << endl;
    cin>> email;

    adresat.imie = imie;
    adresat.nazwisko = nazwisko;
    adresat.numerTelefonu = numerTelefonu;
    adresat.adres = adres;
    adresat.id = (max_id + 1 );
    adresat.email = email;

    adresaci.push_back(adresat);

    max_id++;

    fstream plik;
    if(plik.good())
    {
        plik.open("Adresaci.txt",ios::out | ios::app);

        plik<<adresat.id<<"|"<<idZalogowanegoUzytkownika<<"|"<<imie<<"|"<<nazwisko<<"|"<<numerTelefonu<<"|"<<adres<<"|"<<email<<"|"<<endl;

        plik.close();

        cout << "Adresat dodany." << endl;
        Sleep(1000);
    }

    else
    {
        cout << "Nie mozna otworzyc pliku: Adresaci.txt" << endl;
    }


}

void wyswietlAdresatowOPodanymImieniu (vector <Adresat> adresaci)
{
    string imie;
    system("cls");
    cout << "Podaj imie" << endl;
    cin >> imie;


    for (int i=0; i < adresaci.size(); i++)
    {
        if (adresaci[i].imie == imie)
        {
            cout << adresaci[i].id<< endl;
            cout << adresaci[i].imie<<endl;
            cout << adresaci[i].nazwisko<< endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].adres << endl;
            cout << adresaci[i].email << endl << endl;
        }
    }
    Sleep(3000);
}


void wyswietlAdresatowOPodanymNazwisku (vector <Adresat> adresaci)
{
    string nazwisko;
    system("cls");
    cout << "Podaj nazwisko" << endl;
    cin >> nazwisko;


    for (int i=0; i<adresaci.size(); i++)
    {

        if (adresaci[i].nazwisko == nazwisko)
        {
            cout << adresaci[i].id<< endl;
            cout << adresaci[i].imie<<endl;
            cout << adresaci[i].nazwisko<< endl;
            cout << adresaci[i].numerTelefonu << endl;
            cout << adresaci[i].adres << endl;
            cout << adresaci[i].email << endl << endl;
        }
    }
    Sleep(3000);

}

void wyswietlDaneWszystkichAdresatow (vector <Adresat> adresaci)
{
    int i =0;
    system("cls");
    while (i < adresaci.size())
    {

        cout << adresaci[i].id << endl;
        cout << adresaci[i].imie <<endl;
        cout << adresaci[i].nazwisko << endl;
        cout << adresaci[i].numerTelefonu << endl;
        cout << adresaci[i].adres << endl ;
        cout << adresaci[i].email << endl << endl;

        i++;
    }

    Sleep(3000);
}

void ZapiszStruktureAdresaciDoPliku (vector <Adresat> &Adresaci)
{

    fstream plik;
    if(plik.good())
    {
        plik.open("Adresaci.txt", fstream::out | fstream::trunc);

        for(int i=0; i<Adresaci.size(); i++)
        {
            plik<<Adresaci[i].id<<"|"<<Adresaci[i].imie<<"|"<<Adresaci[i].nazwisko<<"|"<<Adresaci[i].numerTelefonu<<"|"<<Adresaci[i].adres<<"|"<<Adresaci[i].email<<"|"<<endl;
        }
        plik.close();

    }
}


void wczytajDaneZPlikuDoStrukturyAdresaci (vector <Adresat> &Adresaci)
{
    int nr_linii = 1;

    string linia;
    Adresat adresat;

    fstream plik;
    plik.open("Adresaci.txt", ios::in);

    if (plik.good() == false)
    {
        cout<<"Nie udalo sie otworzyc pliku";
        Sleep(1000);
    }
    else
    {

        while (getline(plik, linia))
        {
            char linijka[linia.length()];

            for (int j =0; j<linia.length(); j++)
            {
                linijka[j] = linia[j];
            }

            char *pch;
            string tablica[6];
            int i =0;

            pch = strtok (linijka, "|");
            while (pch != NULL && i<7)
            {

                tablica[i] = ("%s", pch);
                pch = strtok (NULL, "|");
                i++;
            }


            adresat.id = atoi(tablica[0].c_str());

            int pomocniczaZmienna = atoi(tablica[1].c_str());

            adresat.imie = tablica[2];

            adresat.nazwisko = tablica[3];

            adresat.numerTelefonu = tablica[4];

            adresat.email = tablica[5];

            adresat.adres = tablica[6];

            if (pomocniczaZmienna == idZalogowanegoUzytkownika)
            {
                Adresaci.push_back(adresat);

                if (adresat.id > max_id)
                    max_id = adresat.id;
            }


            nr_linii++;
        }
    }
    plik.close();

}

void usunAdresata (vector <Adresat> &Adresaci)
{
    int id;

    cout<< "Podaj id adresata, ktorego chcesz usunac."<<endl;
    cin>> id;


    for (int i=0; i<Adresaci.size(); i++)
    {
        if (Adresaci[i].id == id)
        {
            cout<< "Czy na pewno chcesz usunac wybranego adresata? Jeœli tak, wpisz litere 't'." <<endl;
            cout<< "Jesli nie, nacisnij dowolny przycisk (inny niz litera 't')."<<endl;


            char znak;
            cin>> znak;

            if (znak == 't')
            {
                if (Adresaci[i].id == max_id)
                    max_id--;

                Adresaci.erase(Adresaci.begin() + i);


                cout << "Adresat usuniety. " << endl;
                Sleep(1000);
            }
        }
    }

    ZapiszStruktureAdresaciDoPliku (Adresaci);
}



void edytujAdresata (vector <Adresat> &Adresaci)
{

    int id;

    cout<< "Podaj id adresata, ktorego dane chcesz edytowac."<<endl;
    cin>> id;



    for (int i=0; i<Adresaci.size(); i++)
    {
        if (Adresaci[i].id == id)
        {
            cout << endl;
            cout << "1 - imie" << endl;
            cout << "2 - nazwisko" << endl;
            cout << "3 - numer telefonu" << endl;
            cout << "4 - e-mail" << endl;
            cout << "5 - adres" << endl;
            cout << "6 - powrot do menu" << endl;

            cout<< endl <<"Podaj numer opcji, ktora chcesz zmienic u wybranego uzytkownika : "<<endl;

            char wybor;
            cin >> wybor;

            if(wybor == '1')
            {
                string imie;
                cout << "Podaj nowe imie uzytkownika."<< endl;
                cin >> imie;

                Adresaci[i].imie = imie;
                cout << endl << "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '2')
            {
                string nazwisko;
                cout<< "Podaj nowe nazwisko uzytkownika."<< endl;
                cin>> nazwisko;
                Adresaci[i].nazwisko = nazwisko;

                cout << endl<<"Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }


            else if (wybor == '3')
            {
                string numerTelefonu;
                cout<< "Podaj nowy numer telefonu uzytkownika."<< endl;
                cin>> numerTelefonu;
                Adresaci[i].numerTelefonu = numerTelefonu;
                cout << endl<< "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '4')
            {
                string email;
                cout << "Podaj nowy adres e-mail uzytkownika."<< endl;
                cin >> email;
                Adresaci[i].email = email;
                cout << endl<< "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '5')
            {
                string adres;
                cout << "Podaj nowy adres uzytkownika."<< endl;
                cin >> adres;
                Adresaci[i].adres = adres;
                cout << endl << "Dane uzytkownika zostaly zmienione." <<endl;
                Sleep(1500);
            }

            else if (wybor == '6')
            {
                system("cls");
            }

            else
            {
                cout << "Wybierz poprawny numer dostepnych opcji." << endl;
                Sleep(1500);
            }
        }
    }

    ZapiszStruktureAdresaciDoPliku(Adresaci);
}



int main()
{
    vector <Uzytkownik> uzytkownicy;
    vector <Adresat> Adresaci;
    wczytajDaneZPlikuDoStrukturyAdresaci(Adresaci);
    wczytajDaneZPlikuDoStrukturyUzytkownicy(uzytkownicy);


    if (idZalogowanegoUzytkownika ==0)
    {
        char wybor;

        while(true)
        {
            system ("cls");
            cout << "1. Logowanie" << endl;
            cout << "2. Rejestracja" << endl;
            cout << "9. Zamknij program" << endl;

            cout<< endl <<"Twoj wybor: "<<endl;
            cin >> wybor;

            if(wybor == '1')
            {

                idZalogowanegoUzytkownika = logowanie (uzytkownicy);
            }

            else if (wybor == '2')
            {
                rejestracja (uzytkownicy);

            }


            else if (wybor == '9')
            {
                exit(0);
            }
        }
    }

    else
    {

        char wybor;

        while(true)
        {
            system ("cls");
            cout << "1. Dodaj adresata." << endl;
            cout << "2. Wyszukaj po imieniu." << endl;
            cout << "3. Wyszukaj po nazwisku." << endl;
            cout << "4. Wyswietl wszystkich adresatow." << endl;
            cout << "5. Usun adresata." << endl;
            cout << "6. Edytuj adresata." << endl;
            cout << "7. Zmien haslo." << endl;
            cout << "8. Wyloguj sie." << endl;
            cout << "9. Zakoncz program." << endl;

            cout<< endl <<"Twoj wybor: "<<endl;
            cin >> wybor;


            if(wybor == '1')
            {
                dodajAdresataDoKsiazkiAdresowej (Adresaci);
            }

            else if (wybor == '2')
            {
                wyswietlAdresatowOPodanymImieniu (Adresaci);

            }


            else if (wybor == '3')
            {
                wyswietlAdresatowOPodanymNazwisku (Adresaci);
            }

            else if (wybor == '4')
            {
                wyswietlDaneWszystkichAdresatow (Adresaci);

            }

            else if (wybor == '5')
            {
                usunAdresata(Adresaci);
            }

            else if (wybor == '6')
            {
                edytujAdresata(Adresaci);
            }

            else if (wybor == '7')
            {
                zmianaHasla (uzytkownicy, idZalogowanegoUzytkownika);
            }

            else if (wybor == '8')
            {
                idZalogowanegoUzytkownika =0;
            }


            else if (wybor == '9')
            {
                exit(0);
            }


            else
            {
                cout << "Wybierz poprawny numer dostepnych opcji." << endl;
                Sleep(1500);
            }
        }
    }

    return 0;
}
