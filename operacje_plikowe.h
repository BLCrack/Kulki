#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <Windows.h>
#include "zmienne_i_typy.h"
#include "gracz.h"
#include <vector>
using namespace std;

void zapisz_aktualny_stan(fstream &file, kulka (*tab)[ROZM_PLANSZY],gracz *uzytkownik);		//zapisuje aktualny stan gry do pliku temp

void wczytaj_ostatni_stan(fstream &file, kulka (*tab)[ROZM_PLANSZY],gracz *uzytkownik);		//wczytuje ostatnio przerwana gre, sprawdza istnienie

void zapisz_wynik(fstream &file, gracz *uzytkownik);								//zapisuje wyniki prawidlowo ukonczonej gry

void pokaz_tablice_wynikow(fstream &file);									//wczytuje tablice wynikow

bool niedokonczona_gra(fstream &file);							//sprawdzenie czy isteieje rozgrywka niedokonczona