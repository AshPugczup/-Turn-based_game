/**
 * @file main.cpp
 * @brief Opis pliku
 *
 * Plik ten jest projektem na ZAP II polegającym na grze turowej typu RPG.
 */
/**
 *\mainpage
 *\par Projekt ZAP II Gra turowa typu RPG
 *Program ten to gra turowa typu RPG z rozwojem postaci i elementami walki turowej.
 *\author Grzegorz Jabłoński
 *\date 29.05.2023
 *\version 1.0
*/
#include <iostream>
#include <iomanip>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <windows.h>
#include <cmath>
#include <sstream>

using namespace std;

/**
 * @struct statystyki
 * @brief Struktura przechowująca statystyki postaci
 *
 * Struktura zawiera pola opisujące różne statystyki postaci, takie jak siła, zdrowie, inteligencja itd.
 * Dodatkowo przechowuje informacje o klasie postaci, poziomie trudności oraz atakach.
 */
struct statystyki
{
    int sila; /**< Siła postaci */
    int zdrowie; /**< Zdrowie postaci */
    int inteligencja; /**< Inteligencja postaci */
    int zwinnosc; /**< Zwinność postaci */
    int odpornosc; /**< Odporność postaci */
    int celnosc; /**< Celność postaci */
    int szczescie; /**< Szczęście postaci */
    char klasa; /**< Klasa postaci */
    char poziom_trudnosci; /**< Poziom trudności gry */
    string atak1; /**< Pierwszy atak postaci */
    string atak2; /**< Drugi atak postaci */
    string atak3; /**< Trzeci atak postaci */
    string atak4; /**< Czwarty atak postaci */
    string imie; /**< Imię postaci */
    int stamina = 100; /**< Wytrzymałość postaci */
    int wielkosc_ekwipunku = 0; /**< Wielkość ekwipunku postaci */
    int mz = 0; /**< Miejsce w ekwipunku - Zbroja */
    int ms = 0; /**< Miejsce w ekwipunku - Sztylet */
    int mw = 0; /**< Miejsce w ekwipunku - Włócznia */
};

/**
 * @struct Ekwipunek
 * @brief Struktura przechowująca elementy ekwipunku
 *
 * Struktura zawiera pole z opisem miejsca w ekwipunku oraz wskaźniki na poprzedni i następny element.
 */
struct Ekwipunek {
    string miejsce_w_ekwipunku; /**< Miejsce w ekwipunku */
    Ekwipunek* poprz; /**< Wskaźnik na poprzedni element */
    Ekwipunek* nast; /**< Wskaźnik na następny element */
};

int wczytano;
Ekwipunek* glowa = nullptr;
statystyki gracz, wrog, aktualne;

/**
 * @brief Resetuje statystyki postaci
 * @param zero Referencja do struktury statystyki, której statystyki mają zostać zresetowane
 */
void reset_statystyk(statystyki &zero);

/**
 * @brief Dodaje element do ekwipunku
 * @param przedmiot Opis dodawanego przedmiotu
 */
void dodajElement(string przedmiot);

/**
 * @brief Usuwa element z ekwipunku
 * @param przedmiot Opis usuwanego przedmiotu
 */
void usunElement(string przedmiot);

/**
 * @brief Przechodzi do następnego elementu w ekwipunku
 */
void przejdzDoNastepnego();

/**
 * @brief Przechodzi do poprzedniego elementu w ekwipunku
 */
void przejdzDoPoprzedniego();

/**
 * @brief Wyświetla aktualnie wybrany element z ekwipunku
 */
void wyswietlAktualnyElement();

/**
 * @brief Usuwa wszystkie elementy z ekwipunku
 */
void usunWszystkieElementy();

/**
 * @brief Sprawdza, czy ekwipunek jest pusty
 * @return Wartość logiczna informująca o tym, czy ekwipunek jest pusty
 */
bool czyListaPusta();

/**
 * @brief Losuje klasę postaci
 * @param klasa Referencja do zmiennej, która przechowa wylosowaną klasę postaci
 */
void losowanie_klas(char &klasa);

/**
 * @brief Losuje ataki postaci
 * @param odp Referencja do zmiennej, która przechowa wylosowane ataki postaci
 * @param pomoc1 Pierwszy parametr pomocniczy
 * @param pomoc2 Drugi parametr pomocniczy
 * @param pomoc3 Trzeci parametr pomocniczy
 * @param pomoc4 Czwarty parametr pomocniczy
 */
void losowanie_atakow(char &odp, int pomoc1, int pomoc2, int pomoc3, int pomoc4);

/**
 * @brief Przypisuje wartości statystyk dla danej klasy postaci
 * @param klasa Klasa postaci
 */
void klasy(char klasa);

/**
 * @brief Przypisuje wartości statystyk dla danej klasy postaci
 * @param sila Referencja do zmiennej, która przechowa wartość siły postaci
 * @param zdrowie Referencja do zmiennej, która przechowa wartość zdrowia postaci
 * @param inteligencja Referencja do zmiennej, która przechowa wartość inteligencji postaci
 * @param zwinnosc Referencja do zmiennej, która przechowa wartość zwinności postaci
 * @param odpornosc Referencja do zmiennej, która przechowa wartość odporności postaci
 * @param celnosc Referencja do zmiennej, która przechowa wartość celności postaci
 * @param szczescie Referencja do zmiennej, która przechowa wartość szczęścia postaci
 * @param klasa Klasa postaci
 */
void statystyki(int &sila, int &zdrowie, int &inteligencja, int &zwinnosc, int &odpornosc, int &celnosc, int &szczescie, char klasa);

/**
 * @brief Wyświetla statystyki postaci
 * @param sila Siła postaci
 * @param zdrowie Zdrowie postaci
 * @param inteligencja Inteligencja postaci
 * @param zwinnosc Zwinność postaci
 * @param odpornosc Odporność postaci
 * @param celnosc Celność postaci
 * @param szczescie Szczęście postaci
 */
void wyswietlanie_statystyk(int sila, int zdrowie, int inteligencja, int zwinnosc, int odpornosc, int celnosc, int szczescie);

/**
 * @brief Przypisuje zestaw ataków dla danej klasy postaci
 * @param atak1 Referencja do zmiennej, która przechowa pierwszy atak postaci
 * @param atak2 Referencja do zmiennej, która przechowa drugi atak postaci
 * @param atak3 Referencja do zmiennej, która przechowa trzeci atak postaci
 * @param atak4 Referencja do zmiennej, która przechowa czwarty atak postaci
 * @param klasa Klasa postaci
 */
void zestaw_atakow(string &atak1, string &atak2, string &atak3, string &atak4, char klasa);

/**
 * @brief Wyświetla zestaw ataków postaci
 * @param atak1 Pierwszy atak postaci
 * @param atak2 Drugi atak postaci
 * @param atak3 Trzeci atak postaci
 * @param atak4 Czwarty atak postaci
 * @param klasa Klasa postaci
 */
void wyswietlanie_atakow(string atak1, string atak2, string atak3, string atak4, char klasa);

/**
 * @brief Wyświetla aktualnie używany atak postaci
 * @param atak1 Pierwszy atak postaci
 * @param atak2 Drugi atak postaci
 * @param atak3 Trzeci atak postaci
 * @param atak4 Czwarty atak postaci
 * @param odp Wybrany atak
 * @param aktualny_atak Referencja do zmiennej, która przechowa opis aktualnie używanego ataku
 */
void wyswietlanie_aktualnego_ataku(string atak1, string atak2, string atak3, string atak4, char odp, string &aktualny_atak);

/**
 * @brief Przelicza obrażenia zadawane przez atak
 * @param stamina Wytrzymałość postaci
 * @param obrazenia Referencja do zmiennej, która przechowa wartość obrażeń
 * @param efekt Efekt ataku
 * @param odp Wybrany atak
 * @param klasa Klasa postaci
 * @param sila_atakujacy Siła atakującego
 * @param zdrowie_atakujacy Zdrowie atakującego
 * @param inteligencja_atakujacy Inteligencja atakującego
 * @param zwinnosc_atakujacy Zwinność atakującego
 * @param odpornosc_atakujacy Odporność atakującego
 * @param celnosc_atakujacy Celność atakującego
 * @param szczescie_atakujacy Szczęście atakującego
 * @param sila_broniacy Siła broniącego się
 * @param zdrowie_broniacy Zdrowie broniącego się
 * @param inteligencja_broniacy Inteligencja broniącego się
 * @param zwinnosc_broniacy Zwinność broniącego się
 * @param odpornosc_broniacy Odporność broniącego się
 * @param celnosc_broniacy Celność broniącego się
 * @param szczescie_broniacy Szczęście broniącego się
 * @param wpadl Informacja o trafieniu ataku
 */
void przeliczanie_obrazen(int &stamina, int &obrazenia, char efekt, char odp, char klasa, int &sila_atakujacy, int &zdrowie_atakujacy, int &inteligencja_atakujacy, int &zwinnosc_atakujacy, int &odpornosc_atakujacy, int &celnosc_atakujacy, int &szczescie_atakujacy, int &sila_broniacy, int &zdrowie_broniacy, int &inteligencja_broniacy, int &zwinnosc_broniacy, int &odpornosc_broniacy, int &celnosc_broniacy, int &szczescie_broniacy, int &wpadl);

/**
 * @brief Sprawdza, czy postać ma wystarczającą ilość wytrzymałości na wykonanie ataku
 * @param klasa Klasa postaci
 * @param stamina Wytrzymałość postaci
 * @param odp Wybrany atak
 * @param sprawdz Informacja o sprawdzeniu wytrzymałości
 */
void sprawdzanie_staminy(char klasa, int &stamina, char odp, int &sprawdz);

/**
 * @brief Dodaje określoną ilość statystyk do postaci
 * @param ile Ilość statystyk do dodania
 * @param sila Referencja do zmiennej przechowującej siłę postaci
 * @param zdrowie Referencja do zmiennej przechowującej zdrowie postaci
 * @param inteligencja Referencja do zmiennej przechowującej inteligencję postaci
 * @param zwinnosc Referencja do zmiennej przechowującej zwinność postaci
 * @param odpornosc Referencja do zmiennej przechowującej odporność postaci
 * @param celnosc Referencja do zmiennej przechowującej celność postaci
 * @param szczescie Referencja do zmiennej przechowującej szczęście postaci
 * @param ktora_osoba Informacja o której osobie mowa: 0 - gracz, 1 - wrog
 */
void dodawanie_statystyk(int ile, int &sila, int &zdrowie, int &inteligencja, int &zwinnosc, int &odpornosc, int &celnosc, int &szczescie, int ktora_osoba);

/**
 * @brief Losuje przedmioty
 * @param losujaca_liczba Liczba losująca przedmioty
 */
void losowanie_przedmiotow(int losujaca_liczba);

/**
 * @brief Losuje wartość uniku dla wroga
 * @param unik Referencja do zmiennej przechowującej wartość uniku
 */
void losowanie_unik(int &unik);

/**
 * @brief Tworzy postać gracza
 */
void tworzenie_postaci();

/**
 * @brief Przechodzi przez samouczek gry
 */
void samouczek();

/**
 * @brief Rozpoczyna grę
 * @param licznik_zabic Licznik zabitych przeciwników
 */
void gra(int licznik_zabic);
/**

@brief Główna funkcja programu

@return Wartość zwracana przez program
*/
int main()
{
    int licznik_zabic;
    srand(time(NULL));
    while(true)
    {
    Menu:
        reset_statystyk(gracz);
        reset_statystyk(wrog);
        reset_statystyk(aktualne);
        usunWszystkieElementy();
        licznik_zabic=0;
        cout<<"MENU"<<endl;
        cout<<"1.Start"<<endl;
        cout<<"2.Wczytaj zapis"<<endl;
        cout<<"3.Wyjdz"<<endl;
        char *menu = new char;
        *menu = cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        switch (*menu)
        {
        case '1':
        {
            system("cls");
            if(menu !=nullptr)
            {
                delete menu;
            }
            char *sam = new char;
            *sam=0;
            while(*sam !='t' && *sam !='T' && *sam !='n' && *sam !='N' && *sam != 'p' && *sam != 'P')
            {
                cout<<"Czy chcesz przejsc samouczek"<<endl;
                cout<<"T.Tak"<<endl;
                cout<<"N.Nie"<<endl;
                cout<<"P.Powrot do menu"<<endl;
                *sam=cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
            }
            if(*sam=='p'||*sam=='P')
            {
                goto Menu;
                delete sam;
            }
            if(*sam=='t' || *sam=='T')
            {
                samouczek();
            }
            delete sam;
            tworzenie_postaci();
            if(wczytano==1)
            {
                wczytano = 0;
                system("cls");
                goto Menu;

            }
            gra(licznik_zabic);
            break;
        }

        case '2':
        {
            system("cls");
            cout<<"Podaj kod zapisu:"<<endl;
            cout<<"P-.Powrot do menu"<<endl;
            cin.get(gracz.klasa);
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            if(gracz.klasa=='p'||gracz.klasa=='P')
            {
                while(*menu != '\n')
                {
                    cout<<"Nacisnij enter aby kontynuowac"<<endl;
                    *menu=cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                }
                if(menu !=nullptr)
                {
                    delete menu;
                }
                system("cls");
                break;
            }
            getline(cin, gracz.imie, '-');
            cin >> gracz.stamina;
            cin.ignore(numeric_limits<streamsize>::max(), '-');

            cin >> gracz.poziom_trudnosci;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            getline(cin, gracz.atak1, '-');

            getline(cin, gracz.atak2, '-');

            getline(cin, gracz.atak3, '-');

            getline(cin, gracz.atak4, '-');

            cin >> gracz.sila;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.zdrowie;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.inteligencja;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.zwinnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.odpornosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.celnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.szczescie;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.stamina;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin.get(wrog.klasa);
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            getline(cin, wrog.atak1, '-');
            getline(cin, wrog.atak2, '-');
            getline(cin, wrog.atak3, '-');
            getline(cin, wrog.atak4, '-');
            cin >> wrog.sila;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.zdrowie;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.inteligencja;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.zwinnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.odpornosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.celnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> wrog.szczescie;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> licznik_zabic;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.mz;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.ms;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> gracz.mw;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin.get(aktualne.klasa);
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            getline(cin, aktualne.imie, '-');
            cin >> aktualne.stamina;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.poziom_trudnosci;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            getline(cin, aktualne.atak1, '-');

            getline(cin,aktualne.atak2, '-');

            getline(cin, aktualne.atak3, '-');

            getline(cin, aktualne.atak4, '-');
            cin >> aktualne.sila;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.zdrowie;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.inteligencja;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.zwinnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.odpornosc;
            cin.ignore(numeric_limits<streamsize>::max(), '-');
            cin >> aktualne.celnosc;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            for(int i=gracz.mz; i>0; i--)
            {
                dodajElement("Mikstura Zdrowia +10");
            }
            for(int i=gracz.ms; i>0; i--)
            {

                dodajElement("Mikstura Staminy +10");
            }
            for(int i=gracz.mw; i>0; i--)
            {
                dodajElement("Mikstura Wszystkiego +10");
            }
            if(menu !=nullptr)
            {
                delete menu;
            }
            wczytano=1;
            gra(licznik_zabic);
            break;
        }
        case '3':
            system("cls");
            if(menu !=nullptr)
            {
                delete menu;
            }
            return 0;
        default:
            system("cls");
            cout<<"Wprowadz poprawna opcje"<<endl;
            Sleep(1000);
            system("cls");
            if(menu !=nullptr)
            {
                delete menu;
            }
            break;
        }
    }
}

void samouczek()
{
    char *samouk_odp = new char;
    *samouk_odp=0;
    while(*samouk_odp != 't' && *samouk_odp != 'T')
    {
        *samouk_odp=0;

        while(*samouk_odp != 't' && *samouk_odp != 'T' && *samouk_odp != 'n' && *samouk_odp != 'N')
        {
            cout<<"Ta gra polega na niekonczoncej sie walce turowej z losowymi przeciwnikami."<<endl;
            cout<<"W grze znajduja sie takie rzeczy jak statystyki ktore beda odpowiadaly za rozne rzeczy w zaleznosci od klasy"<<endl;
            cout<<"Walka bedzie trwac dopoki twoje zdrowie nie spadnie ponizej zera"<<endl;
            // tu zrobic jakis samouczek
            cout<<"Czy zrozumiales"<<endl;
            cout<<"T.Tak"<<endl;
            cout<<"N.Nie"<<endl;
            *samouk_odp = cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }
    }
    delete samouk_odp;
}
void reset_statystyk(struct statystyki &zero)
{
    zero.atak1=" ";
    zero.atak2=" ";
    zero.atak3=" ";
    zero.atak4=" ";
    zero.celnosc=0;
    zero.inteligencja=0;
    zero.odpornosc=0;
    zero.imie="0";
    zero.sila=0;
    zero.szczescie=0;
    zero.zdrowie=0;
    zero.zwinnosc=0;
    zero.klasa=0;
    zero.stamina=100;
    zero.poziom_trudnosci=0;
}
void dodajElement(string przedmiot)
{
    Ekwipunek* nowy_element = new Ekwipunek;
    nowy_element->miejsce_w_ekwipunku = przedmiot;

    if (glowa == nullptr) {
        nowy_element->poprz = nowy_element;
        nowy_element->nast = nowy_element;
        glowa = nowy_element;
    } else {
        Ekwipunek* ostat = glowa->poprz;
        nowy_element->poprz = ostat;
        nowy_element->nast = glowa;
        ostat->nast = nowy_element;
        glowa->poprz = nowy_element;
    }
    gracz.wielkosc_ekwipunku++;
}

void usunElement(string przedmiot)
{
    if (glowa == nullptr) {
        cout << "Ekwipunek jest pusty." << endl;
        return;
    }

    Ekwipunek* aktualny = glowa;
    while (aktualny->miejsce_w_ekwipunku != przedmiot) {
        aktualny = aktualny->nast;
        if (aktualny == glowa) {
            return;
        }
    }

    Ekwipunek* poprzedni_element = aktualny->poprz;
    Ekwipunek* nastepny_element = aktualny->nast;
    poprzedni_element->nast = nastepny_element;
    nastepny_element->poprz = poprzedni_element;

    if (aktualny == glowa) {
        glowa = nastepny_element;
    }

    delete aktualny;
    gracz.wielkosc_ekwipunku--;
}

void przejdzDoNastepnego() {
    if (glowa == nullptr) {
        cout << "Ekwipunek jest pusty." << endl;
        return;
    }

    glowa = glowa->nast;
}

void przejdzDoPoprzedniego() {
    if (glowa == nullptr) {
        cout << "Ekwipunek jest pusty." << endl;
        return;
    }

    glowa = glowa->poprz;
}

void wyswietlAktualnyElement() {
    if (glowa == nullptr) {
        cout << "Ekwipunek jest pusty." << endl;
        return;
    }

    cout << "Aktualny element: " << glowa->miejsce_w_ekwipunku << endl;
}
void usunWszystkieElementy()
{
    if (glowa == nullptr) {
        return;
    }

    Ekwipunek* aktualny = glowa;
    Ekwipunek* nastepny_element;
    do {
        nastepny_element = aktualny->nast;
        delete aktualny;
        aktualny = nastepny_element;
    } while (aktualny != glowa);

    glowa = nullptr;
}

bool czyListaPusta()
{
    return glowa == nullptr;
}
void wyswietlanie_atakow(string atak1, string atak2,string atak3,string atak4,char klasa)
{
    int stamina_atak1=0,stamina_atak2=0,stamina_atak3=0,stamina_atak4=0;
    if(klasa=='m')
    {
        stamina_atak1=20;
        stamina_atak2=20;
        stamina_atak3=40;
        stamina_atak4=30;
    }
    else if(klasa=='r')
    {
        stamina_atak1=30;
        stamina_atak2=15;
        stamina_atak3=20;
        stamina_atak4=40;
    }
    else if(klasa=='l')
    {
        stamina_atak1=20;
        stamina_atak2=20;
        stamina_atak3=20;
        stamina_atak4=20;
    }
    cout<<"Atak 1: "<<atak1<<" Stamina: "<<stamina_atak1<<endl;
    cout<<"Atak 2: "<<atak2<<" Stamina: "<<stamina_atak2<<endl;
    cout<<"Atak 3: "<<atak3<<" Stamina: "<<stamina_atak3<<endl;
    cout<<"Atak 4: "<<atak4<<" Stamina: "<<stamina_atak4<<endl;
}
void sprawdzanie_staminy(char klasa, int &stamina, char odp, int &sprawdz)
{
    int stamina_atak1=0,stamina_atak2=0,stamina_atak3=0,stamina_atak4=0;
    if(klasa=='m')
    {
        stamina_atak1=20;
        stamina_atak2=20;
        stamina_atak3=40;
        stamina_atak4=30;
    }
    else if(klasa=='r')
    {
        stamina_atak1=30;
        stamina_atak2=15;
        stamina_atak3=20;
        stamina_atak4=40;
    }
    else if(klasa=='l')
    {
        stamina_atak1=20;
        stamina_atak2=20;
        stamina_atak3=20;
        stamina_atak4=20;
    }
    if(odp == '1')
    {
        if(stamina>=stamina_atak1)
        {
            sprawdz=1;
        }
        else
        {
            sprawdz=0;
        }
    }
    else if(odp == '2')
    {
        if(stamina>=stamina_atak2)
        {
            sprawdz=1;
        }
        else
        {
            sprawdz=0;
        }
    }
    else if(odp == '3')
    {
        if(stamina>=stamina_atak3)
        {
            sprawdz=1;
        }
        else
        {
            sprawdz=0;
        }
    }
    else if(odp == '4')
    {
        if(stamina>=stamina_atak4)
        {
            sprawdz=1;
        }
        else
        {
            sprawdz=0;
        }
    }
}
void zestaw_atakow(string &atak1, string &atak2,string &atak3,string &atak4, char klasa)
{
    if(klasa=='m')
    {
        atak1="Ognisty pocisk";
        atak2="Lodowy strzal";
        atak3="Kula ognia";
        atak4="Deszcz meteorow";
    }
    else if(klasa=='r')
    {
        atak1="Ciecie mieczem";
        atak2="Tarcza";
        atak3="Pchniecie mieczem";
        atak4="Niszczycielski cios";
    }
    else if(klasa=='l')
    {
        atak1="Strzal";
        atak2="Zatruta strzala";
        atak3="Strzal ognia";
        atak4="Szybki pocisk";
    }
}
void losowanie_przedmiotow(int losujaca_liczba)
{
    char odp=0;
    srand(time(NULL));
    losujaca_liczba=(rand() % 100 );
    if(losujaca_liczba>=0 && losujaca_liczba<34)
    {
        dodajElement("Mikstura Zdrowia +10");
        while(odp != '\n')
        {
            cout<<"Dodano do ekwipunku: Mikstura Zdrowia +10 "<<endl;
            cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
            odp=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }
    }
    if(losujaca_liczba>=34 && losujaca_liczba<75)
    {
        dodajElement("Mikstura Staminy +10");
        while(odp != '\n')
        {
            cout<<"Dodano do ekwipunku: Mikstura Staminy +10"<<endl;
            cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
            odp=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }

    }
    if(losujaca_liczba>=75 && losujaca_liczba<=100)
    {
        dodajElement("Mikstura Wszystkiego +10");
        while(odp != '\n')
        {
            cout<<"Dodano do ekwipunku: Mikstura Wszystkiego +10"<<endl;
            cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
            odp=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }

    }

}
void wyswietlanie_statystyk(int sila, int zdrowie, int inteligencja, int zwinnosc, int odpornosc, int celnosc, int szczescie)
{
    cout<<"zdrowie: "<<zdrowie<<endl;
    cout<<"sila: "<<sila<<endl;
    cout<<"inteligencja: "<<inteligencja<<endl;
    cout<<"zwinnosc: "<<zwinnosc<<endl;
    cout<<"odpornosc: "<<odpornosc<<endl;
    cout<<"celnosc: "<<celnosc<<endl;
    cout<<"szczescie: "<<szczescie<<endl;
}
void wyswietlanie_aktualnego_ataku(string atak1, string atak2, string atak3, string atak4, char odp, string &aktualny_atak)
{
    if(odp == '1')
    {
        aktualny_atak=atak1;
    }
    else if(odp == '2')
    {
        aktualny_atak=atak2;
    }
    else if(odp == '3')
    {
        aktualny_atak=atak3;
    }
    else if(odp == '4')
    {
        aktualny_atak=atak4;
    }
}
void przeliczanie_obrazen(int &stamina,int &obrazenia,char efekt, char odp, char klasa, int &sila_atakujacy, int &zdrowie_atakujacy, int &inteligencja_atakujacy, int &zwinnosc_atakujacy, int &odpornosc_atakujacy, int &celnosc_atakujacy, int &szczescie_atakujacy, int &sila_broniacy, int &zdrowie_broniacy, int &inteligencja_broniacy, int &zwinnosc_broniacy, int &odpornosc_broniacy, int &celnosc_broniacy, int &szczescie_broniacy, int &wpadl)
{
    //usunac nie potrzebne rzeczy
    srand(time(NULL));
    int czy_kryt;
    int czy_kryt_poz;
    int *czy_kryt_tab = new int[100];
    obrazenia = 0;
    if(klasa=='m')
    {
        if(odp == '1')
        {
            obrazenia = 10*((inteligencja_atakujacy/100.00)+1);
            stamina-=20;

        }
        else if(odp == '2')
        {
            obrazenia = 10*((inteligencja_atakujacy/100.00)+1);
            stamina-=20;
            zwinnosc_broniacy -=1;
        }
        else if(odp == '3')
        {
            obrazenia = 20*((inteligencja_atakujacy/100.00)+1);
            stamina-=40;

        }
        else if(odp == '4')
        {
            obrazenia = 15*((inteligencja_atakujacy/100.00)+1);
            stamina-=30;
        }
    }
    else if(klasa=='r')
    {
        if(odp == '1')
        {
            obrazenia = 15*((sila_atakujacy/100.00)+1);
            stamina-=30;
        }
        else if(odp == '2')
        {
            obrazenia = 5*((sila_atakujacy/100.00)+1);
            stamina-=15;
            odpornosc_atakujacy+=5;
        }
        else if(odp == '3')
        {
            obrazenia = 10*((sila_atakujacy/100.00)+1);
            stamina-=20;

        }
        else if(odp == '4')
        {
            obrazenia = 20*((sila_atakujacy/100.00)+1);
            stamina-=40;

        }
    }
    else if(klasa=='l')
    {
        if(odp == '1')
        {
            obrazenia = 10*((sila_atakujacy/100.00)+1);
            stamina-=20;
        }
        else if(odp == '2')
        {
            obrazenia = 10*((sila_atakujacy/100.00)+1);
            stamina-=20;

        }
        else if(odp == '3')
        {
            obrazenia = 10*((sila_atakujacy/100.00)+1);
            stamina-=20;

        }
        else if(odp == '4')
        {
            obrazenia = 10*((sila_atakujacy/100.00)+1);
            stamina-=20;

        }
    }
    for(int i=0; i<100;i++)
    {
        czy_kryt=(rand() % 100 );
        czy_kryt_tab[i]=czy_kryt;
    }
    czy_kryt_poz=(rand() % 100 );
    czy_kryt=czy_kryt_tab[czy_kryt_poz];
    if(czy_kryt>0 && czy_kryt<szczescie_atakujacy*0.50)
    {
        obrazenia=obrazenia*1.5;
        wpadl=1;
    }
    delete[] czy_kryt_tab;
}

void statystyki(int &sila, int &zdrowie, int &inteligencja, int &zwinnosc, int &odpornosc, int &celnosc, int &szczescie, char klasa)
{
    if(klasa=='m')
    {
        sila=2;
        zdrowie=100;
        inteligencja=16;
        zwinnosc=4;
        odpornosc=8;
        celnosc=12;
        szczescie=10;
    }
    else if(klasa=='r')
    {
        sila=16;
        zdrowie=100;
        inteligencja=0;
        zwinnosc=2;
        odpornosc=14;
        celnosc=6;
        szczescie=10;
    }
    else if(klasa=='l')
    {
        sila=8;
        zdrowie=100;
        inteligencja=0;
        zwinnosc=16;
        odpornosc=6;
        celnosc=16;
        szczescie=10;
    }

}
void klasy(char klasa)
{
    if(klasa=='m' || klasa =='M')
    {
        char *wybor = new char;
        *wybor=0;
        while(*wybor !='N' && *wybor !='n' && *wybor !='T' && *wybor !='t')
        {
            cout<<"Ta klasa posiada takie umiejetnosci"<<endl;
            zestaw_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4, gracz.klasa);
            wyswietlanie_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4,gracz.klasa);
            cout<<"I takie statystyki bazowe"<<endl;
            statystyki(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie, gracz.klasa);
            wyswietlanie_statystyk(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie);
            cout<<"Czy jestes pewien wyboru"<<endl;
            cout<<"T.Tak"<<endl;
            cout<<"N.Nie"<<endl;
            *wybor=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(*wybor=='N' || *wybor=='n')
            {
                gracz.klasa='0';
            }
            system("cls");
        }
        delete wybor;
    }
    else if(klasa=='r' || klasa =='R')
    {
        char *wybor = new char;
        *wybor=0;
        while(*wybor !='N' && *wybor !='n' && *wybor !='T' && *wybor !='t')
        {
            cout<<"Ta klasa posiada takie umiejetnosci"<<endl;
            zestaw_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4, gracz.klasa);
            wyswietlanie_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4,gracz.klasa);
            cout<<"I takie statystyki bazowe"<<endl;
            statystyki(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie, gracz.klasa);
            wyswietlanie_statystyk(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie);
            cout<<"Czy jestes pewien wyboru"<<endl;
            cout<<"T.Tak"<<endl;
            cout<<"N.Nie"<<endl;
            *wybor=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(*wybor=='N' || *wybor=='n')
            {
                gracz.klasa='0';
            }
            system("cls");
        }
        delete wybor;
    }
    else if(klasa=='l' || klasa =='L')
    {
        char *wybor = new char;
        *wybor=0;
        while(*wybor !='N' && *wybor !='n' && *wybor !='T' && *wybor !='t')
        {
            cout<<"Ta klasa posiada takie umiejetnosci"<<endl;
            zestaw_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4, gracz.klasa);
            wyswietlanie_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4,gracz.klasa);
            cout<<"I takie statystyki bazowe"<<endl;
            statystyki(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie, gracz.klasa);
            wyswietlanie_statystyk(gracz.sila, gracz.zdrowie, gracz.inteligencja, gracz.zwinnosc, gracz.odpornosc, gracz.celnosc, gracz.szczescie);
            cout<<"Czy jestes pewien wyboru"<<endl;
            cout<<"T.Tak"<<endl;
            cout<<"N.Nie"<<endl;
            *wybor=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            if(*wybor=='N' || *wybor=='n')
            {
                gracz.klasa='0';
            }
            system("cls");
        }
        delete wybor;
    }
}
void losowanie_klas(char &klasa)
{
    srand(time(NULL));
    char **zestaw_klas;
    int w, k;
    w=7;
    k=7;
    zestaw_klas = new char *[w];
    for (int i = 0; i < w; i++)
    {
        zestaw_klas[i] = new char [k];
    }
    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int *x=new int;
            *x=(rand() % 60 )+1;
            if((*x>=1 && *x<5) || (*x>=20 && *x<25))
            {
                zestaw_klas[i][j]='r';
            }
            else if((*x>=5 && *x<10) || (*x>=25 && *x<30))
            {
                zestaw_klas[i][j]='m';
            }
            else if((*x>=15 && *x<20) || (*x>=35 && *x<40))
            {
                zestaw_klas[i][j]='l';
            }
            else if((*x>=30 && *x<35) || (*x>=45 && *x<50))
            {
                zestaw_klas[i][j]='R';
            }
            else if((*x>=40 && *x<45)|| (*x>=55 && *x<60))
            {
                zestaw_klas[i][j]='M';
            }
            else if((*x>=50 && *x<=55)||(*x>=10 && *x<15))
            {
                zestaw_klas[i][j]='L';
            }
        }
    }
    int *ktora_klasa_x = new int;
    int *ktora_klasa_y = new int;
    *ktora_klasa_x =rand()%(w-1);
    *ktora_klasa_y =rand()%(k-1);
    klasa=zestaw_klas[*ktora_klasa_x][*ktora_klasa_y];
    if(klasa == 'L')
    {
        klasa = 'l';
    }
    else if(klasa == 'M')
    {
        klasa = 'm';
    }
    else if(klasa == 'R')
    {
        klasa = 'r';
    }

    for (int i = 0; i < w; i++)
        delete [] zestaw_klas[i];
    delete [] zestaw_klas;
    delete ktora_klasa_x;
    delete ktora_klasa_y;
    if(klasa !='r' && klasa !='m' && klasa !='l')
    {
        losowanie_klas(klasa);
    }
}
void losowanie_atakow(char &odp,int pomoc1, int pomoc2, int pomoc3, int pomoc4)
{
    srand(time(NULL));
    char **zestaw_atakow;

    int w, k, l = 0,g;
    w=7;
    k=7;
    if(pomoc1==0)
    {
        l++;

    }
    if(pomoc2==0)
    {
        l++;

    }
    if(pomoc3==0)
    {
        l++;

    }
    if(pomoc4==0)
    {
        l++;

    }
    g=l;
    zestaw_atakow = new char *[w];
    char *dostepne_ataki= new char[l];
    for (int i = 0; i < w; i++)
    {
        zestaw_atakow[i] = new char [k];
    }
    if(pomoc4==0)
    {
        g--;
        dostepne_ataki[g]='4';
    }
    if(pomoc3==0)
    {
        g--;
        dostepne_ataki[g]='3';
    }
    if(pomoc2==0)
    {
        g--;
        dostepne_ataki[g]='2';
    }
    if(pomoc1==0)
    {
        g--;
        dostepne_ataki[g]='1';
    }

    for (int i = 0; i < w; i++)
    {
        for (int j = 0; j < k; j++)
        {
            int ktory_atak=(rand() % l );
            zestaw_atakow[i][j]=dostepne_ataki[ktory_atak];
        }
    }
    int *ktory_atak_x = new int;
    int *ktory_atak_y = new int;
    *ktory_atak_x =rand()%(w-1);
    *ktory_atak_y =rand()%(k-1);
    odp=zestaw_atakow[*ktory_atak_x][*ktory_atak_y];
    for (int i = 0; i < w; i++)
        delete [] zestaw_atakow[i];
    delete [] zestaw_atakow;
    delete [] dostepne_ataki;
    delete ktory_atak_x;
    delete ktory_atak_y;
    if(odp !='1' && odp !='2' && odp !='3' && odp != '4')
    {
        losowanie_atakow(odp,pomoc1,pomoc2,pomoc3,pomoc4);
    }
}
void losowanie_unik(int &unik)
{
    srand(time(NULL));
    int czy_unik_poz;
    int *czy_unik_tab = new int[100];
    for(int i=0; i<100;i++)
    {
        unik=(rand() % 100 );
        czy_unik_tab[i]=unik;
    }
    unik=0;
    czy_unik_poz=(rand() % 100 );
    unik=czy_unik_tab[czy_unik_poz];
    delete[] czy_unik_tab;
}
void dodawanie_statystyk(int ile,int &sila, int &zdrowie, int &inteligencja, int &zwinnosc, int &odpornosc, int &celnosc, int &szczescie,int ktora_osoba)
{
    srand(time(NULL));
    for(int i=ile; i>0; i--)
    {
        char *dodawanie_statystyk = new char;
        *dodawanie_statystyk=0;
        if(ktora_osoba==1)
        {
            while(*dodawanie_statystyk != '1' && *dodawanie_statystyk != '2' && *dodawanie_statystyk != '3' && *dodawanie_statystyk != '4' && *dodawanie_statystyk != '5' && *dodawanie_statystyk != '6' && *dodawanie_statystyk != '7')
            {
                cout<<"Dodaj punkty statystyk do swojej postaci(masz do dyspozycji jeszcze "<<i<<" )"<<endl;
                cout<<"1.Zdrowie+5"<<endl;
                cout<<"2.Sila+1"<<endl;
                cout<<"3.Inteligencja+1"<<endl;
                cout<<"4.Celnosc+1"<<endl;
                cout<<"5.Szczescie+1"<<endl;
                cout<<"6.Odpornosc+1"<<endl;
                cout<<"7.Zwinnosc+1"<<endl;
                cout<<"Twoje statystyki:"<<endl;
                wyswietlanie_statystyk(sila, zdrowie, inteligencja, zwinnosc, odpornosc, celnosc, szczescie);
                *dodawanie_statystyk = cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");

            }
        }
        if(ktora_osoba==0)
        {

            *dodawanie_statystyk=(rand() % 7 )+49;
        }
        if(*dodawanie_statystyk == '1')
        {
            zdrowie+=5;
        }
        else if(*dodawanie_statystyk == '2')
        {
            sila++;
        }
        else if(*dodawanie_statystyk == '3')
        {
            inteligencja++;
        }
        else if(*dodawanie_statystyk == '4')
        {
            celnosc++;
        }
        else if(*dodawanie_statystyk == '5')
        {
            szczescie++;
        }
        else if(*dodawanie_statystyk == '6')
        {
            odpornosc++;
        }
        else if(*dodawanie_statystyk == '7')
        {
            zwinnosc++;
        }

        delete dodawanie_statystyk;
    }
}
void tworzenie_postaci()
{
    while(gracz.poziom_trudnosci != 'l'&& gracz.poziom_trudnosci != 's'&& gracz.poziom_trudnosci != 't'&& gracz.poziom_trudnosci != 'T'&& gracz.poziom_trudnosci != 'S'&& gracz.poziom_trudnosci !='L' && gracz.poziom_trudnosci !='p' && gracz.poziom_trudnosci !='P')
    {
        cout<<"Wybierz poziom trudnosci"<<endl;
        cout<<"L.Latwy"<<endl;
        cout<<"S.Sredni"<<endl;
        cout<<"T.Trudny"<<endl;
        cout<<"P.Powrot do menu"<<endl;
        gracz.poziom_trudnosci = cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
    }
    if(gracz.poziom_trudnosci == 'p' || gracz.poziom_trudnosci == 'P')
    {
        wczytano =1;
        return;
    }
    if(gracz.poziom_trudnosci == 'L')
    {
        gracz.poziom_trudnosci = 'l';
    }
    else if(gracz.poziom_trudnosci == 'S')
    {
        gracz.poziom_trudnosci = 's';
    }
    else if(gracz.poziom_trudnosci == 'T')
    {
        gracz.poziom_trudnosci = 't';
    }
    while(gracz.klasa != 'l' && gracz.klasa != 'm' && gracz.klasa != 'r' && gracz.klasa != 'L' && gracz.klasa != 'M' && gracz.klasa !='R' && gracz.klasa !='p' && gracz.klasa !='P')
    {
        cout<<"Wybierz klase"<<endl;
        cout<<"M.Mag"<<endl;
        cout<<"R.Rycerz"<<endl;
        cout<<"L.Lucznik"<<endl;
        cout<<"P.Powrot do menu"<<endl;
        gracz.klasa = cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
        if(gracz.klasa == 'p' || gracz.klasa == 'P')
        {
            wczytano =1;
            return;
        }
        if(gracz.klasa == 'L')
        {
            gracz.klasa = 'l';
        }
        else if(gracz.klasa == 'M')
        {
            gracz.klasa = 'm';
        }
        else if(gracz.klasa == 'R')
        {
            gracz.klasa = 'r';
        }
        klasy(gracz.klasa);
    }
    dodawanie_statystyk(10,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,1);
    cout<<"Podaj Imie swojej postaci :"<<endl;
    cout<< "Po podaniu imienia nacisnij 2x enter aby kontynuowac"<<endl;
    getline(cin,gracz.imie,'\n');
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    system("cls");
    dodajElement("Mikstura Zdrowia +10");
    dodajElement("Mikstura Zdrowia +10");
    dodajElement("Mikstura Staminy +10");
    dodajElement("Mikstura Staminy +10");
    dodajElement("Mikstura Wszystkiego +10");
}
void gra(int licznik_zabic)
{
    int *czy_kryt_wpadl=new int;
    int *unik = new int;
    int *wartosc_unik = new int;
    licznik_zabic=0;
    string *aktualny_atak = new string;
    char *efekt_gracz = new char;
    *efekt_gracz=0;
    char *efekt_wrog= new char;
    int  *obrazenia= new int;
    int  *obrona= new int;
    char *odp_walka = new char;
    *odp_walka=0;
    int *sprawdzajaca_stamina =new int;
    *sprawdzajaca_stamina=0;
    int *pomocnicza_zmienna1 = new int;
    int *pomocnicza_zmienna2 = new int;
    int *pomocnicza_zmienna3 = new int;
    int *pomocnicza_zmienna4 = new int;
    int*do_losowania_przedmiotow = new int;
    *do_losowania_przedmiotow=0;
    if(wczytano==1)
    {
        wczytano=0;
        system("cls");
        goto Menu_walka;
    }
    while(gracz.zdrowie>0)
    {
        aktualne = gracz;
        reset_statystyk(wrog);
        losowanie_klas(wrog.klasa);
        statystyki(wrog.sila, wrog.zdrowie, wrog.inteligencja, wrog.zwinnosc, wrog.odpornosc, wrog.celnosc, wrog.szczescie, wrog.klasa);
        zestaw_atakow(wrog.atak1, wrog.atak2,wrog.atak3,wrog.atak4, wrog.klasa);
        if(gracz.poziom_trudnosci=='l')
        {
            dodawanie_statystyk((licznik_zabic + 0),wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,0);
        }
        if(gracz.poziom_trudnosci=='s')
        {
            dodawanie_statystyk((licznik_zabic + 5),wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,0);
        }
        if(gracz.poziom_trudnosci=='t')
        {
            dodawanie_statystyk((licznik_zabic + 10),wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,0);
        }

        while(*odp_walka != '\n')
        {
            cout<<"Pojawil sie przeciwnik "<<endl;
            cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
            *odp_walka=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
        }
        while(wrog.zdrowie>0)
        {
            if(gracz.zdrowie<0 || wrog.zdrowie<0)
            {
                break;
            }
        Menu_walka:

            while(*odp_walka != '1' && *odp_walka != '2' && *odp_walka != '3' && *odp_walka != '4' && *odp_walka !='5' && *odp_walka != '6' )
            {
                cout<<"Trwa walka!!"<<endl;
                cout<<"1.Ataki"<<endl;
                cout<<"2.Ekwipunek"<<endl;
                cout<<"3.Sprawdzenie przeciwnika"<<endl;
                cout<<"4.Czekaj"<<endl;
                cout<<"5.Zapisz gre"<<endl;
                cout<<"6.Wyjdz z gry"<<endl;
                cout<<"Twoje zdrowie: "<<gracz.zdrowie<<endl;
                cout<<"Twoja stamina: "<<gracz.stamina<<endl;
                cout<<"Zdrowie wroga: "<<wrog.zdrowie<<endl;
                cout<<"Stamina wroga: "<<wrog.stamina<<endl;
                *odp_walka=cin.get();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                system("cls");
            }
            switch (*odp_walka) {
            case '1':
                *odp_walka=0;
                *sprawdzajaca_stamina=0;
                while(*odp_walka != '1' && *odp_walka != '2' && *odp_walka != '3' && *odp_walka != '4')
                {
                    while(*sprawdzajaca_stamina !=1)
                    {
                        wyswietlanie_atakow(gracz.atak1, gracz.atak2,gracz.atak3,gracz.atak4,gracz.klasa);
                        cout<<"M.Powrot do menu"<<endl;
                        cout<<"Twoja stamina: "<<gracz.stamina<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        if(*odp_walka=='M'||*odp_walka=='m')
                        {
                            system("cls");
                            *odp_walka=0;
                            goto Menu_walka;
                        }
                        sprawdzanie_staminy(gracz.klasa,gracz.stamina,*odp_walka,*sprawdzajaca_stamina);
                        if(*sprawdzajaca_stamina==0)
                        {
                            while(*odp_walka != '\n')
                            {
                                cout<<"Nie masz wystarczajaca staminy"<<endl;
                                cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                                *odp_walka=cin.get();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                system("cls");
                            }
                        }
                        system("cls");
                    }
                }
                *wartosc_unik=(wrog.zwinnosc-gracz.celnosc+20)*0.50;
                if(*wartosc_unik<0)
                {
                    *wartosc_unik=0;
                }
                losowanie_unik(*unik);
                if(*unik>=*wartosc_unik && *unik<=100)
                {
                    przeliczanie_obrazen(gracz.stamina,*obrazenia,*efekt_gracz,*odp_walka,gracz.klasa,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,*czy_kryt_wpadl);
                    *obrona=1.50*((wrog.odpornosc/10.00)+1);
                    wrog.zdrowie=wrog.zdrowie-(*obrazenia-*obrona);
                    while(*odp_walka != '\n')
                    {
                        wyswietlanie_aktualnego_ataku(gracz.atak1,gracz.atak2,gracz.atak3,gracz.atak4,*odp_walka,*aktualny_atak);
                        cout<<"Uzyles :"<<*aktualny_atak<<endl;
                        cout<<"Zadano :"<<*obrazenia-*obrona<<" obrazen"<<endl;
                        if(*czy_kryt_wpadl==1)
                        {
                            cout<<"Zadales obrazenia krytyczne"<<endl;
                        }
                        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }
                }
                if(*unik>0 && *unik<wrog.zwinnosc)
                {
                    przeliczanie_obrazen(gracz.stamina,*obrazenia,*efekt_gracz,*odp_walka,gracz.klasa,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,*czy_kryt_wpadl);
                    while(*odp_walka != '\n')
                    {
                        cout<<"Wrog uniknal ataku"<<endl;
                        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }

                    *obrazenia=0;
                }
                *obrazenia=0;
                *obrona=0;
                *odp_walka=0;
                *sprawdzajaca_stamina=0;
                *unik = 0;
                *wartosc_unik=0;
                system("cls");
                break;
            case '2':
                while(true)
                {
                    while (*odp_walka != 'n' && *odp_walka != 'N' && *odp_walka != 'p' && *odp_walka != 'P' && *odp_walka != 'm' && *odp_walka != 'M'&& *odp_walka != 'u' && *odp_walka != 'U')
                    {
                        wyswietlAktualnyElement();
                        cout<<"N.Nastepny przedmiot"<<endl;
                        cout<<"P.Poprzedni przedmiot"<<endl;
                        cout<<"U.Uzyj przedmiotu"<<endl;
                        cout<<"M.Powrot do menu"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }
                    if(*odp_walka=='M'||*odp_walka=='m')
                    {
                        system("cls");
                        *odp_walka=0;
                        goto Menu_walka;
                    }
                    if(*odp_walka=='N' ||*odp_walka=='n' )
                    {
                        przejdzDoNastepnego();
                        *odp_walka=0;
                    }
                    if(*odp_walka=='P' ||*odp_walka=='p' )
                    {
                        przejdzDoPoprzedniego();
                        *odp_walka=0;
                    }
                    if(*odp_walka=='u' ||*odp_walka=='U' )
                    {
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Zdrowia +10")
                        {
                            while(*odp_walka != '\n')
                            {
                                cout<<"Uzyles Mikstury Zdrowia +10"<<endl;
                                cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                                *odp_walka=cin.get();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                system("cls");
                            }
                            usunElement("Mikstura Zdrowia +10");
                            gracz.zdrowie+=10;
                        }
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Staminy +10")
                        {
                            while(*odp_walka != '\n')
                            {
                                cout<<"Uzyles Mikstura Staminy +10"<<endl;
                                cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                                *odp_walka=cin.get();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                system("cls");
                            }
                            usunElement("Mikstura Staminy +10");
                            gracz.stamina+=10;
                        }
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Wszystkiego +10")
                        {
                            while(*odp_walka != '\n')
                            {
                                cout<<"Uzyles Mikstura Wszystkiego +10"<<endl;
                                cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                                *odp_walka=cin.get();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                system("cls");
                            }
                            usunElement("Mikstura Wszystkiego +10");
                            gracz.zdrowie+=10;
                            gracz.stamina+=10;
                            gracz.sila+=10;
                            gracz.inteligencja+=10;
                            gracz.celnosc+=10;
                            gracz.szczescie+=10;
                            gracz.odpornosc+=10;
                            gracz.zwinnosc+=10;
                        }
                        *odp_walka=0;
                        break;
                    }

                }
                *odp_walka=0;
                break;
            case '3':
                while(*odp_walka != '\n')
                {
                    wyswietlanie_statystyk(wrog.sila, wrog.zdrowie, wrog.inteligencja, wrog.zwinnosc, wrog.odpornosc, wrog.celnosc, wrog.szczescie);
                    wyswietlanie_atakow(wrog.atak1, wrog.atak2,wrog.atak3,wrog.atak4,wrog.klasa);
                    cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                    *odp_walka=cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                }
                *odp_walka=0;

                break;
            case '4':
            {
                break;
            }
            case '5':
            {
                while(*odp_walka != '\n')
                {
                    for(int i=gracz.wielkosc_ekwipunku; i>0; i--)
                    {
                        przejdzDoNastepnego();
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Zdrowia +10")
                        {
                            gracz.mz++;
                        }
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Staminy +10")
                        {
                            gracz.ms++;
                        }
                        if(glowa->miejsce_w_ekwipunku == "Mikstura Wszystkiego +10")
                        {
                            gracz.mw++;
                        }
                    }
                    cout<<"To twoj kod zapisu: "<<endl;
                    cout<<gracz.klasa<<"-"<<gracz.imie<<"-"<<gracz.stamina<<"-"<<gracz.poziom_trudnosci<<"-"<<gracz.atak1<<"-"<<gracz.atak2<<"-"<<gracz.atak3<<"-"<<gracz.atak4<<"-"<<gracz.sila<<"-"<< gracz.zdrowie<<"-"<< gracz.inteligencja<<"-"<< gracz.zwinnosc<<"-"<< gracz.odpornosc<<"-"<< gracz.celnosc<<"-"<< gracz.szczescie<<"-"<<wrog.stamina<<"-"<<wrog.klasa<<"-"<<wrog.atak1<<"-"<<wrog.atak2<<"-"<<wrog.atak3<<"-"<<wrog.atak4<<"-"<<wrog.sila<<"-"<< wrog.zdrowie<<"-"<< wrog.inteligencja<<"-"<< wrog.zwinnosc<<"-"<< wrog.odpornosc<<"-"<< wrog.celnosc<<"-"<< wrog.szczescie<<"-"<<licznik_zabic<<"-"<<gracz.mz<<"-"<<gracz.ms<<"-"<<gracz.mw<<"-"<<aktualne.klasa<<"-"<<aktualne.imie<<"-"<<aktualne.stamina<<"-"<<aktualne.poziom_trudnosci<<"-"<<aktualne.atak1<<"-"<<aktualne.atak2<<"-"<<aktualne.atak3<<"-"<<aktualne.atak4<<"-"<<aktualne.sila<<"-"<<aktualne.zdrowie<<"-"<<aktualne.inteligencja<<"-"<<aktualne.zwinnosc<<"-"<<aktualne.odpornosc<<"-"<<aktualne.celnosc<<"-"<<aktualne.szczescie<<endl;
                    cout<<"Musisz go zapamietac"<<endl;
                    cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                    *odp_walka=cin.get();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    system("cls");
                }
                goto Menu_walka;
                break;
            }
            case '6':
            {
                goto Koniec_gry;
                break;
            }
            default:
                break;
            }
            if(gracz.stamina<100)
            {
                gracz.stamina+=10;
                if(gracz.stamina>100)
                {
                    gracz.stamina=100;
                }
            }
            if(gracz.zdrowie<0 || wrog.zdrowie<0)
            {
                break;
            }

            *pomocnicza_zmienna1=0;
            *pomocnicza_zmienna2=0;
            *pomocnicza_zmienna3=0;
            *pomocnicza_zmienna4=0;
            while(*sprawdzajaca_stamina !=1)
            {
                if(*pomocnicza_zmienna1!=1 && *pomocnicza_zmienna2!=1 && *pomocnicza_zmienna3!=1 && *pomocnicza_zmienna4!=1)
                    *odp_walka=0;
                losowanie_atakow(*odp_walka,*pomocnicza_zmienna1,*pomocnicza_zmienna2,*pomocnicza_zmienna3,*pomocnicza_zmienna4);
                sprawdzanie_staminy(wrog.klasa,wrog.stamina,*odp_walka,*sprawdzajaca_stamina);
                if(*sprawdzajaca_stamina==0)
                {
                    if(*pomocnicza_zmienna1 != 1  || *pomocnicza_zmienna2 != 1 ||*pomocnicza_zmienna3 != 1 ||*pomocnicza_zmienna4 != 1)
                    {
                        if(*odp_walka=='1')
                        {
                            *pomocnicza_zmienna1=1;
                        }
                        else if(*odp_walka=='2')
                        {
                            *pomocnicza_zmienna2=1;
                        }
                        else if(*odp_walka=='3')
                        {
                            *pomocnicza_zmienna3=1;
                        }
                        else if(*odp_walka=='4')
                        {
                            *pomocnicza_zmienna4=1;
                        }
                    }
                }
                if(*pomocnicza_zmienna1==1 && *pomocnicza_zmienna2==1 && *pomocnicza_zmienna3==1 && *pomocnicza_zmienna4==1)
                {
                    while(*odp_walka != '\n')
                    {
                        cout<<"Przeciwnik niczego nie uzyl"<<endl;
                        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }
                    *odp_walka=0;
                    break;
                }
            }

            if(*odp_walka!=0)
            {
                *wartosc_unik=(gracz.zwinnosc-wrog.celnosc+20)*0.50;
                if(*wartosc_unik<0)
                {
                    *wartosc_unik=0;
                }
                losowanie_unik(*unik);
                if(*unik>=*wartosc_unik && *unik<=100)
                {
                    przeliczanie_obrazen(wrog.stamina,*obrazenia,*efekt_wrog,*odp_walka,wrog.klasa,wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,*czy_kryt_wpadl);
                    *obrona=1.50*((gracz.odpornosc/10.00)+1);
                    gracz.zdrowie=gracz.zdrowie-(*obrazenia-*obrona);
                    wyswietlanie_aktualnego_ataku(wrog.atak1,wrog.atak2,wrog.atak3,wrog.atak4,*odp_walka,*aktualny_atak);
                    while(*odp_walka != '\n')
                    {
                        cout<<"Przeciwnik uzyl: "<<*aktualny_atak<<endl;
                        cout<<"Zadano :"<<*obrazenia-*obrona<<" obrazen"<<endl;
                        if(*czy_kryt_wpadl==1)
                        {
                            cout<<"Wrog zadal obrazenia krytyczne"<<endl;
                        }
                        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }
                }
                if(*unik>0 && *unik<gracz.zwinnosc)
                {
                    przeliczanie_obrazen(wrog.stamina,*obrazenia,*efekt_wrog,*odp_walka,wrog.klasa,wrog.sila,wrog.zdrowie,wrog.inteligencja,wrog.zwinnosc,wrog.odpornosc,wrog.celnosc,wrog.szczescie,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,*czy_kryt_wpadl);
                    while(*odp_walka != '\n')
                    {
                        cout<<"Uniknales ataku"<<endl;
                        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
                        *odp_walka=cin.get();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        system("cls");
                    }
                    *obrazenia=0;
                }
            }
            if(wrog.stamina<100)
            {
                wrog.stamina+=10;
                if(wrog.stamina>100)
                {
                    wrog.stamina=100;
                }
            }
            *sprawdzajaca_stamina=0;
            *obrazenia=0;
            *obrona=0;
            *unik=0;
            *wartosc_unik=0;
            system("cls");
            *odp_walka=0;
            if(gracz.zdrowie<=0)
            {
                break;
            }
        }
        if(gracz.zdrowie>0)
        {
            gracz = aktualne;
            dodawanie_statystyk(1,gracz.sila,gracz.zdrowie,gracz.inteligencja,gracz.zwinnosc,gracz.odpornosc,gracz.celnosc,gracz.szczescie,1);
        }
        licznik_zabic=licznik_zabic+1;
        while(*odp_walka != '\n')
        {
            cout<<"Pokonales wroga"<<endl;
            cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
            *odp_walka=cin.get();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");

        }
        losowanie_przedmiotow(*do_losowania_przedmiotow);
        *do_losowania_przedmiotow=0;
    }
    while(*odp_walka != '\n')
    {
        cout<<"Przegrales"<<endl;
        cout<<"Pokonales"<<licznik_zabic-1<<" przeciwnikow"<<endl;
        cout<<"Nacisnij 2x enter aby kontynuowac"<<endl;
        *odp_walka=cin.get();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        system("cls");
    }
Koniec_gry:
    delete aktualny_atak;
    delete odp_walka;
    delete obrazenia;
    delete obrona;
    delete efekt_gracz;
    delete efekt_wrog;
    delete sprawdzajaca_stamina;
    delete pomocnicza_zmienna1;
    delete pomocnicza_zmienna2;
    delete pomocnicza_zmienna3;
    delete pomocnicza_zmienna4;
    delete do_losowania_przedmiotow;
    delete unik;
    delete wartosc_unik;
    delete czy_kryt_wpadl;
}
