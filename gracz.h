#pragma once
#include <string>
#include <iostream>
using namespace std;

class gracz									
{
protected:
	string nazwa_gracza;
	unsigned int punkty;
public:
	gracz();									//konstr. domyslny dla klasy bazowej

	gracz(string pom_nazwa, int pom_punkty);	//konstr argumentowy
												
	void set_nazwagracza(string pom_nazwa);		//settery i gettery

	string get_nazwagracza();

	void set_punkty(unsigned int pom_punkty);

	unsigned int get_punkty();

	virtual void wypisz()=0;					//wypisanie informacji o graczu, metoda czysto wirtualna

	virtual ~gracz();							//virtualny destruktor
};

class gracz_czlowiek : public gracz
{
public:
	gracz_czlowiek();

	gracz_czlowiek(string pom_nazwa, int pom_punkty);
									
	virtual void wypisz();

	~gracz_czlowiek();
};
