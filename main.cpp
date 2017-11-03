#include <iostream>
#include <string>
#include <Windows.h>
#include <fstream>
#include "gracz.h"
#include "silnik_gry.h"
#include "operacje_plikowe.h"
#include "zmienne_i_typy.h"
#include "funkcje_pomocnicze.h"
#include <ctime>
#define ILE_KULEK_LOSUJE 5
using namespace std;


int main()
{
	unsigned int wybor = 2;
	unsigned int co_robic = 1;
	fstream temp;
	fstream wyniki;
	bool przerwana_gra = false;
	bool bufor_zapelniony = false;
	int kolory_kulek[ILE_KULEK_LOSUJE];											//kolory kolejnych kulek ktore maja byc wylosowane w nastepnej turze

	srand(time(NULL));

	zasady();																	//wyswietla zasady gry

	while (true)
	{
		menu();																	//wyswietla menu
																				//kontrola poprawnosci
		while (!(cin >> co_robic) || co_robic!=1 && co_robic!=2 && co_robic!=100 || getchar() != '\n')
		{
			komunikat("NIEDOZWOLONY ZNAK. NIE MA TAKIEJ OPCJI ! WYBIERZ PONOWNIE :", czerwony);
			czysc_bufor();
			menu();
		}

		if (co_robic == 1)
		{
			gracz *uzytkownik = new gracz_czlowiek;
			kulka plansza[ROZM_PLANSZY][ROZM_PLANSZY] = { BRAK };				//tworzenie tablicy kulek
			przerwana_gra = false;
																				//spr. plik z niedokonczon¹ gra
			if (niedokonczona_gra(temp))
			{
				komunikat("Istnieje ostatnio niedokonczona gra", zielony);
				menu_2();
				while (!(cin >> wybor) || wybor != 1 && wybor != 2 || getchar() != '\n')
				{
					komunikat("NIEDOZWOLONY ZNAK. NIE MA TAKIEJ OPCJI ! WYBIERZ PONOWNIE :", czerwony);
					czysc_bufor();
					menu_2();
				}

				if (wybor == 2)
				{
					kulka pom[ROZM_PLANSZY][ROZM_PLANSZY];
					gracz *pom_uzytkownik=new gracz_czlowiek;
																			//zapisanie ostatnio zdobytych punktow do wynikow
					temp.open("temp.txt", ios::in);							//do odczytu
					wczytaj_ostatni_stan(temp, pom, pom_uzytkownik);		//wczytuje ostatni stan gry
					temp.clear();											//czyszczenie pliku
					temp.close();

					if (pom_uzytkownik->get_punkty() > 0)
					{
						zapisz_wynik(wyniki, pom_uzytkownik);				//zapisanie ostatnich punktow jesli jakies byly	
						komunikat("ZAPISANO TWOJ POPRZEDNI WYNIK.", zielony);
					}
				}
			}

			if (wybor == 1)
			{
				temp.open("temp.txt", ios::in);								//do odczytu
				wczytaj_ostatni_stan(temp, plansza, uzytkownik);			//wczytuje ostatni stan gry
				losuj_kolory_kulek(kolory_kulek);
				komunikat("WCZYTANO POPRAWNIE.", zielony);
				temp.clear();
				temp.close();
			}
			else if (wybor == 2)
			{
				string nazwa_gracza;

				cout << "Podaj nazwe gracza :" << endl;
				cin >> nazwa_gracza;
				uzytkownik->set_nazwagracza(nazwa_gracza);
				losuj_kolory_kulek(kolory_kulek);
				losuj_kulki(plansza,kolory_kulek);
				losuj_kolory_kulek(kolory_kulek);
			}

			temp.open("temp.txt", ios::out);									//do zapisu

			cout << endl << "ZACZYNAMY GRE !" << endl << endl;
			wypisz_plansze(plansza, uzytkownik,kolory_kulek); 
																				//start gry
			while (plansza_ok(plansza))
			{
				unsigned int x_pocz = 0;
				unsigned int y_pocz = 0;
				unsigned int x_doc = 0;
				unsigned int y_doc = 0;
				unsigned int punkty = 0;
																				//ktora kulke przesuwamy
				cout << "Podaj wspolrzedne kulki ktora chcesz przesunac :" << endl;
				x_pocz = wczytaj_wspolrzedna<unsigned int, char>('x');
				if (x_pocz == 100)
				{
					przerwana_gra = true;
					break;
				}
				y_pocz = wczytaj_wspolrzedna<unsigned int, char>('y');
				if (y_pocz == 100)
				{
					przerwana_gra = true;
					break;
				}
																			//sprawdzanie czy jest tam kulka
				while (czy_jest_kulka(plansza, x_pocz, y_pocz) == false)
				{
					komunikat("TO MIEJSCE JEST PUSTE !", czerwony);
					cout << "Podaj wspolrzedne kulki ktora chcesz przesunac :" << endl;
					x_pocz = wczytaj_wspolrzedna<unsigned int, char>('x');
					if (x_pocz == 100)
					{
						przerwana_gra = true;
						break;
					}
					y_pocz = wczytaj_wspolrzedna<unsigned int, char>('y');
					if (y_pocz == 100)
					{
						przerwana_gra = true;
						break;
					}
				}
				if (przerwana_gra)
					break;
																					//miejsce docelowe przesuniecia
				cout << "Podaj wspolrzedne miejsca docelowego :" << endl;
				x_doc = wczytaj_wspolrzedna<unsigned int, char>('x');
				if (x_doc == 100)
				{
					przerwana_gra = true;
					break;
				}
				y_doc = wczytaj_wspolrzedna<unsigned int, char>('y');
				if (y_doc == 100)
				{
					przerwana_gra = true;
					break;
				}
																	//sprawdzanie ruchu
				while (sprawdz_ruch(plansza, x_pocz, y_pocz, x_doc, y_doc) == false)
				{
					komunikat("NIE MOZNA TAM PRZESUNAC. WYBIERZ INNE MIEJSCE !", czerwony);
					cout << "Podaj wspolrzedne miejsca docelowego :" << endl;
					x_doc = wczytaj_wspolrzedna<unsigned int, char>('x');
					if (x_doc == 100)
					{
						przerwana_gra = true;
						break;
					}
					y_doc = wczytaj_wspolrzedna<unsigned int, char>('y');
					if (y_doc == 100)
					{
						przerwana_gra = true;
						break;
					}
				}
				if (przerwana_gra)
					break;	
				//pozwolenie na kolejny ruch gdy uzytkownik zostawia kulke w tym samym miejscu
				if (x_pocz == x_doc && y_pocz == y_doc)
				{
					komunikat("KULKA ZOSTAJE W SWOIM MIEJSCU.", zielony);
					continue;
				}
																			//przesuniecie kulki
				przesun_kulke(plansza, x_pocz, y_pocz, x_doc, y_doc);
																			//spr zbicia
				punkty = czy_zbito(plansza);
				if (punkty >= 5)
				{
					uzytkownik->set_punkty(uzytkownik->get_punkty() + punkty);
				}
				else
				{
					losuj_kulki(plansza,kolory_kulek);
					losuj_kolory_kulek(kolory_kulek);
				}
																			//wypisanie po ruchu
				wypisz_plansze(plansza, uzytkownik,kolory_kulek);

				punkty = czy_zbito(plansza);								//w przypadku gdy po wylosowaniu kulki sie dobrze uloza
				if (punkty >= 5)
				{
					uzytkownik->set_punkty(uzytkownik->get_punkty() + punkty);
					komunikat("Kulka wylosowana na twoja korzysc ! Masz punkty ! \n", zielony);
				}
			}
																			//jezeli uzytkownik przerwal gre
			if (przerwana_gra)
			{
				zapisz_aktualny_stan(temp, plansza, uzytkownik);
				temp.close();
				komunikat("GRA PRZERWANA! \nZAPISANO STAN.GRE MOZESZ DOKONCZYC PRZY PONOWNYM URUCHOMIENIU.", zielony);
				continue;
			}
			else															//zapisanie do wynikow
			{
				komunikat("KONIEC GRY! TWOJ WYNIK TO : \n", zielony);
				cout << uzytkownik->get_punkty() << endl;
				komunikat("ZOSTAL ZAPISANY DO TABELI WYNIKOW.\n",zielony);
				zapisz_wynik(wyniki, uzytkownik);
				continue;
			}
		}
		else if (co_robic == 2)
		{
			pokaz_tablice_wynikow(wyniki);
			continue;
		}
		else if (co_robic == 100)
		{
			komunikat("KONIEC GRY. DO ZOBACZENIA!", zielony);
			break;
		}
	}
}