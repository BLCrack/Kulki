#pragma once
#include "zmienne_i_typy.h"
#include "gracz.h"
#include <Windows.h>
#include <cstdio>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <queue>
#include "funkcje_pomocnicze.h"
using namespace std;


bool sprawdz_ruch(kulka (*tab)[ROZM_PLANSZY],int x_pocz, int y_pocz, int x_doc, int y_doc);	//sprawdza poprawnosc ruchu true,false

unsigned int czy_zbito(kulka (*tab)[ROZM_PLANSZY]);									//sprawdza czy jest zbicie 

void wypisz_plansze(kulka (*tab)[ROZM_PLANSZY],gracz *uzytkownik,int *kolory_kulek);		//wypisuje aktualna plansze gry, informacje o graczu i kulkach

void losuj_kolory_kulek(int *kolory_kulek);								//losuje kolory kulek ktore nastepnie pojawia sie na planszy

void losuj_kulki(kulka (*tab)[ROZM_PLANSZY],int *kolory_kulek);			//losuje kulki i ustawia na planszy

bool plansza_ok(kulka(*tab)[ROZM_PLANSZY]);								//sprawdza czy ca³a plansza jest juz zapelniona lub pusta i koniec gry

bool czy_jest_kulka(kulka(*tab)[ROZM_PLANSZY], unsigned int x, unsigned int y);	//sprawdza czy w podanym miejscu znajduje sie kulka					

void zasady();														//wyswietla informacje o grze na poczatku programu

void przesun_kulke(kulka (*tab)[ROZM_PLANSZY],unsigned int x_pocz, unsigned int y_pocz, unsigned int x_doc, unsigned int y_doc); //przesuwa kulke

															//szablon funkcji po³¹czony z definicja, rozdzielenie powoduje b³ad LNK
template <class Zwracany, class Argument>
Zwracany wczytaj_wspolrzedna(Argument znak)					//wczytuje i sprawdza czy podana wspolrzedna jest w zakresie tablicy i czy nie konczy gry
{
	Zwracany wczytana = 0;

	while (true)
	{
		bool bufor_zapelniony = false;

		cout << znak << ":" << endl;
		cin >> wczytana;

		if (cin.get() != '\n')
			bufor_zapelniony = true;
		else
			bufor_zapelniony = false;

		while (cin.fail() || bufor_zapelniony)
		{
			komunikat("PODANO BLEDNE DANE (np. napis, niewlasciwa liczba).", czerwony);
			czysc_bufor();
			cout << znak << ":" << endl;
			cin >> wczytana;
			if (cin.get() != '\n')
				bufor_zapelniony = true;
			else
				bufor_zapelniony = false;
		}

		if (wczytana == 100)
			break;
		else if (wczytana < 0 || wczytana > 8)
		{
			komunikat("Wspolrzedna poza zakresem planszy ! Wspolrzedna : [0,8] lub 100-konczy gre !", czerwony); // i wraca do wczytania
		}
		else
			break;
	}

	return wczytana;
}
