#include "funkcje_pomocnicze.h"

void czysc_bufor()
{
	cin.clear();
	while (cin.get() != '\n')
		;
}

void menu()
{
	cout << endl << "Co chcesz zrobic? :" << endl;
	cout << "1 - Graj" << endl;
	cout << "2 - Wyswietl wyniki" << endl;
	cout << "100 - Zakoncz gre" << endl;
}

void menu_2()
{
	cout << endl << "jesli chcesz do niej wrocic wcisnij : 1" << endl << "jesli chcesz zaczac od nowa wcisnij : 2" << endl;
}

void komunikat(string napis, unsigned int kolor)
{
	HANDLE kolor_tekstu;
	kolor_tekstu = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(kolor_tekstu, kolor);
	cout << napis << endl;
	SetConsoleTextAttribute(kolor_tekstu, 7);
}