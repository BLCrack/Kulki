#include "gracz.h"

//klasa bazowa
gracz::gracz()
{
	nazwa_gracza = "Nieznany gracz";
	punkty = 0;
}

gracz::gracz(string pom_nazwa, int pom_punkty)
{
	nazwa_gracza = pom_nazwa;
	if (pom_punkty >= 0)
		punkty = pom_punkty;
	else
	{
		cout << "Podano punkty ujemne ! Przyjeto standardowo : 0 .";
		punkty = 0;
	}
}

void gracz::set_nazwagracza(string pom_nazwa)
{
	nazwa_gracza = pom_nazwa;
}

string gracz::get_nazwagracza()
{
	return nazwa_gracza;
}

void gracz::set_punkty(unsigned int pom_punkty)
{
	if (pom_punkty >= 0)
		punkty = pom_punkty;
	else
	{
		cout << "Podano punkty ujemne ! Przyjeto standardowo : 0 .";
		punkty = 0;
	}
}

unsigned int gracz::get_punkty()
{
	return punkty;
}

void gracz::wypisz()
{
}

gracz::~gracz()
{
}

//gracz czlowiek
gracz_czlowiek::gracz_czlowiek() : gracz()
{
}

gracz_czlowiek::gracz_czlowiek(string pom_nazwa, int pom_punkty) : gracz(pom_nazwa,pom_punkty)
{
}

void gracz_czlowiek::wypisz()
{
	cout << "Nazwa gracza : " << nazwa_gracza <<"\t" << "Punkty : " << punkty << endl;
}

gracz_czlowiek::~gracz_czlowiek()
{
}