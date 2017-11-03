#include "silnik_gry.h"


bool sprawdz_ruch(kulka(*tab)[ROZM_PLANSZY], int x_pocz, int y_pocz, int x_doc, int y_doc)
{
	//pomocnicza plansza do oznaczania pól odwiedzonych
	//false- nie odwiedzone i dostepne, true- odwiedzone/niedostpne
	struct wspolrzedne
	{
		int x;
		int y;
		bool czy_odwiedzone;
	};
	wspolrzedne pom[ROZM_PLANSZY][ROZM_PLANSZY];
	queue <wspolrzedne> kolejka;
	bool czy_ruch_mozliwy = 0;

	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			pom[i][j].x = i;
			pom[i][j].y = j;
			if (tab[i][j] == BRAK)
				pom[i][j].czy_odwiedzone = false;		//dostepne punkty
			else
				pom[i][j].czy_odwiedzone = true;		//niedostepne punkty
		}

	kolejka.push(pom[x_pocz][y_pocz]);
	pom[x_pocz][y_pocz].czy_odwiedzone = true;

	while (!kolejka.empty())
	{
		int x = kolejka.front().x;
		int y = kolejka.front().y;
		kolejka.pop();									//usuwam punkt z kolejki
		
		//sprawdzenie, czy dotarlem do punktu docelowego
		if (x == x_doc && y == y_doc)
			czy_ruch_mozliwy = 1;
		//dodanie sasiadow obecnego punktu do kolejki
		//gora
		if (x - 1 >= 0 && pom[x - 1][y].czy_odwiedzone == false)
		{
			pom[x - 1][y].czy_odwiedzone = true;
			kolejka.push(pom[x - 1][y]);
		}
		//dol
		if(x+1<=ROZM_PLANSZY-1 && pom[x + 1][y].czy_odwiedzone == false)
		{
			pom[x + 1][y].czy_odwiedzone = true;
			kolejka.push(pom[x + 1][y]);
		}
		//lewa
		if (y-1>= 0 && pom[x][y-1].czy_odwiedzone == false)
		{
			pom[x][y-1].czy_odwiedzone = true;
			kolejka.push(pom[x][y-1]);
		}
		//prawa
		if (y + 1 <= ROZM_PLANSZY-1 && pom[x][y + 1].czy_odwiedzone == false)
		{
			pom[x][y + 1].czy_odwiedzone = true;
			kolejka.push(pom[x][y + 1]);
		}
	}
	
	return czy_ruch_mozliwy;
}

unsigned int czy_zbito(kulka (*tab)[ROZM_PLANSZY])
{
	unsigned int punkty=0;
	unsigned int ile = 0;
	int k = 0, l = 0;
	
	//kasowanie podswietlenia dla ostatnio wylosowanych kulek
	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			if (tab[i][j] == NOWY_BIALY)
				tab[i][j] = BIALY;
			else if (tab[i][j] == NOWY_BLEKITNY)
				tab[i][j] = BLEKITNY;
			else if (tab[i][j] == NOWY_CZERWONY)
				tab[i][j] = CZERWONY;
			else if (tab[i][j] == NOWY_NIEBIESKI)
				tab[i][j] = NIEBIESKI;
			else if (tab[i][j] == NOWY_ROZOWY)
				tab[i][j] = ROZOWY;
			else if (tab[i][j] == NOWY_ZIELONY)
				tab[i][j] = ZIELONY;
			else if (tab[i][j] == NOWY_ZOLTY)
				tab[i][j] = ZOLTY;
		}

	//sprawdzanie punktow
	for (int i = 0; i < ROZM_PLANSZY; i++)
	{
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			if (tab[i][j] != BRAK)
			{
				ile = 0;
				//poziom na lewo
				k = j;
				while (k >= 0 && tab[i][k] == tab[i][j])
				{
					ile++;
					k--;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = j; ile > 0; k--, ile--)
						tab[i][k] = BRAK;
					continue;
				}
				//poziom na prawo
				ile = 0;
				k = j;
				while (k <= ROZM_PLANSZY-1 && tab[i][k] == tab[i][j])
				{
					ile++;
					k++;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = j; ile > 0; k++,ile--)
						tab[i][k] = BRAK;
					continue;
				}
				//góra
				ile = 0;
				k = i;
				while (k >= 0 && tab[k][j] == tab[i][j])
				{
					ile++;
					k--;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i; ile > 0; k--,ile--)
						tab[k][j] = BRAK;
					continue;
				}
				//dó³
				ile = 0;
				k = i;
				while (k <=ROZM_PLANSZY-1 && tab[k][j] == tab[i][j])
				{
					ile++;
					k++;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i; ile > 0; k++, ile--)
						tab[k][j] = BRAK;
					continue;
				}
				//skos lewy do³
				ile = 0;
				k = i;
				l = j;
				while (k<=ROZM_PLANSZY-1 && l>=0 && tab[k][l] == tab[i][j])
				{
					ile++;
					k++;
					l--;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i, l = j; ile > 0; k++,l--,ile--)
						tab[k][l] = BRAK;
					continue;
				}
				//skos prawy dól
				ile = 0;
				k = i;
				l = j;
				while (k <= ROZM_PLANSZY-1 && l<= 8 && tab[k][l] == tab[i][j])
				{
					ile++;
					k++;
					l++;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i, l = j; ile > 0; k++, l++, ile--)
						tab[k][l] = BRAK;
					continue;
				}
				//skos lewy góra
				ile = 0;
				k = i;
				l = j;
				while (k >= 0 && l>=0 && tab[k][l] == tab[i][j])
				{
					ile++;
					k--;
					l--;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i, l = j; ile > 0; k--, l--, ile--)
						tab[k][l] = BRAK;
					continue;
				}
				//skos prawy góra
				ile = 0;
				k = i;
				l = j;
				while (k >= 0 && l <= ROZM_PLANSZY-1 && tab[k][l] == tab[i][j])
				{
					ile++;
					k--;
					l++;
				}
				if (ile >= 5)
				{
					punkty += ile;
					//usuwanie zbitych
					for (k = i, l = j; ile > 0; k--, l++, ile--)
						tab[k][l] = BRAK;
					continue;
				}
				
			}
		}
	}
	
	return punkty;
}

void wypisz_plansze(kulka (*tab)[ROZM_PLANSZY],gracz *uzytkownik,int *kolory_kulek)
{
	HANDLE kolor_tekstu;
	kolor_tekstu = GetStdHandle(STD_OUTPUT_HANDLE);

	SetConsoleTextAttribute(kolor_tekstu, 14);
	uzytkownik->wypisz();										//wywolanie polimorficznej metody wypisz
	cout << "Kolejne kulki : ";									//wypisanie kulek ktore pojawia sie w nastepnej turze
	SetConsoleTextAttribute(kolor_tekstu, kolory_kulek[0]);
	cout << "0 ";
	SetConsoleTextAttribute(kolor_tekstu, kolory_kulek[1]);
	cout << "0 ";
	SetConsoleTextAttribute(kolor_tekstu, kolory_kulek[2]);
	cout << "0 ";
	//dla 5 kulek
	SetConsoleTextAttribute(kolor_tekstu, kolory_kulek[3]);
	cout << "0 ";
	SetConsoleTextAttribute(kolor_tekstu, kolory_kulek[4]);
	cout << "0 " << endl;
	//

	SetConsoleTextAttribute(kolor_tekstu, 112);					//standard kolor dla tabeli to 7
	cout << "  | ";
	for (int i= 0; i < ROZM_PLANSZY; i++)
	{
		if(i<ROZM_PLANSZY-1)
			cout << i << " | ";
		else
			cout << i << " |";
	}
	SetConsoleTextAttribute(kolor_tekstu, 112);
	cout << endl;
	cout << "---";
	SetConsoleTextAttribute(kolor_tekstu,7);
	cout <<"------------------------------------" << endl;		
	for (int i = 0; i < ROZM_PLANSZY; i++)									//start od zerowego wiersza
	{
		SetConsoleTextAttribute(kolor_tekstu, 112);
		cout << i << " |";
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			SetConsoleTextAttribute(kolor_tekstu, tab[i][j]); //ustawiam kolor dla kazdej kulki
			cout << " 0 ";
			SetConsoleTextAttribute(kolor_tekstu, 7);
			cout <<"|";
		}
		cout << endl;
		SetConsoleTextAttribute(kolor_tekstu, 112);
		cout << "---";
		SetConsoleTextAttribute(kolor_tekstu, 7);
		cout << "------------------------------------" << endl;
	}
	cout << endl;
}

void losuj_kolory_kulek(int *kolory_kulek)
{
	const unsigned int ILE_KULEK = 5;

	for (int i = 0; i < ILE_KULEK; i++)
		 kolory_kulek[i]= rand() % 7 + 9;
}

void losuj_kulki(kulka (*tab)[ROZM_PLANSZY], int *kolory_kulek)
{
	unsigned int ile_losuje = 5;
	unsigned int miejsca = 0;

	//kasowanie podswietlenia dla ostatnio wylosowanych kulek
	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			if (tab[i][j] == NOWY_BIALY)
				tab[i][j] = BIALY;
			else if (tab[i][j] == NOWY_BLEKITNY)
				tab[i][j] = BLEKITNY;
			else if (tab[i][j] == NOWY_CZERWONY)
				tab[i][j] = CZERWONY;
			else if (tab[i][j] == NOWY_NIEBIESKI)
				tab[i][j] = NIEBIESKI;
			else if (tab[i][j] == NOWY_ROZOWY)
				tab[i][j] = ROZOWY;
			else if (tab[i][j] == NOWY_ZIELONY)
				tab[i][j] = ZIELONY;
			else if (tab[i][j] == NOWY_ZOLTY)
				tab[i][j] = ZOLTY;
		}
	
	//sprawdzenie czy ilosc wolnych miejsc na planszy jest mniejsza niz ilosc losowanych kulek
	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
			if (tab[i][j] == BRAK)
				miejsca++;
	if (miejsca < ile_losuje)		//jesli jest mniej wolnych miejsc, losuje mniej kulek
		ile_losuje = miejsca;
	//losowanie

	for (int los = 0; los < ile_losuje; los++)
	{
		int i, j, kolor;
		kolor = kolory_kulek[los];

		i = rand() % 9;
		j = rand() % 9;
		while (tab[i][j] != BRAK)
		{
			i = rand() % 9;
			j = rand() % 9;
		}

		if (kolor == 9)
			tab[i][j] = NOWY_NIEBIESKI;
		else if (kolor == 10)
			tab[i][j] = NOWY_ZIELONY;
		else if (kolor == 11)
			tab[i][j] = NOWY_BLEKITNY;
		else if (kolor == 12)
			tab[i][j] = NOWY_CZERWONY;
		else if (kolor == 13)
			tab[i][j] = NOWY_ROZOWY;
		else if (kolor == 14)
			tab[i][j] = NOWY_ZOLTY;
		else if (kolor == 15)
			tab[i][j] = NOWY_BIALY;
	}
}

bool plansza_ok(kulka(*tab)[ROZM_PLANSZY])
{
	bool niezapelniona = false;
	bool niepusta = false;

	//czy nie zapelniona
	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
			if (tab[i][j] == BRAK)
				niezapelniona = true;
	//spr czy nie pusta
	for (int i = 0; i < ROZM_PLANSZY; i++)
		for (int j = 0; j < ROZM_PLANSZY; j++)
			if (tab[i][j] != BRAK)
				niepusta = true;

	return (niezapelniona && niepusta);			//zapelniona lub pusta
}

bool czy_jest_kulka(kulka(*tab)[ROZM_PLANSZY], unsigned int x, unsigned int y)
{
	if (tab[x][y] == BRAK)
		return false;
	
	return true;
}

void zasady()
{
	HANDLE kolor_tekstu;
	kolor_tekstu = GetStdHandle(STD_OUTPUT_HANDLE);

	cout << "Autor : Bartosz Lorenc." << endl << endl;
	cout << "WITAMY W GRZE KULKI !" << endl << endl;
	SetConsoleTextAttribute(kolor_tekstu, 14);
	cout << "ZASADY :" << endl;
	cout << "-Nalezy przesuwac kulki tak aby bylo obok siebie 5 lub wiecej kulek tego samego koloru, wtedy nastapi zbicie" << endl;
	cout << "-W przypadku gdy nie ma zbicia, losowane sa kolejne 3 losowe kulki" << endl;
	cout << "-Gra konczy sie w przypadku zapelnienia planszy lub gdy cala plansza jest pusta" << endl;
	cout << "-W kazdym momencie mozna przerwac gre podajac : 100 - zamiast wspolrzednej ruchu" << endl;
	cout << "Powodzenia!" << endl << endl;
	SetConsoleTextAttribute(kolor_tekstu, 7);
}

void przesun_kulke(kulka (*tab)[ROZM_PLANSZY],unsigned int x_pocz, unsigned int y_pocz, unsigned int x_doc, unsigned int y_doc)
{
		tab[x_doc][y_doc] = tab[x_pocz][y_pocz];
		tab[x_pocz][y_pocz] = BRAK;
}