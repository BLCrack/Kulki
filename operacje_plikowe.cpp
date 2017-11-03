#include "operacje_plikowe.h"


void zapisz_aktualny_stan(fstream &file, kulka(*tab)[ROZM_PLANSZY], gracz *uzytkownik)
{
	file.clear();
	file << uzytkownik->get_nazwagracza() << endl;
	file << uzytkownik->get_punkty() << endl;

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

	for (int i = 0; i < ROZM_PLANSZY; i++)
	{
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			file << tab[i][j] << " ";
		}
		file << endl;
	} 
}

void wczytaj_ostatni_stan(fstream &file, kulka(*tab)[ROZM_PLANSZY], gracz *uzytkownik)
{
	string nazwa_gracza;
	int punkty;
	int pom;

	file >> nazwa_gracza;
	file >> punkty;

	uzytkownik->set_nazwagracza(nazwa_gracza);
	uzytkownik->set_punkty(punkty);

	for (int i = 0; i < ROZM_PLANSZY; i++)
	{
		for (int j = 0; j < ROZM_PLANSZY; j++)
		{
			file >> pom;
			if (pom == 0)
				tab[i][j] = BRAK;
			else if (pom == 9)
				tab[i][j] = NIEBIESKI;
			else if (pom == 10)
				tab[i][j] = ZIELONY;
			else if (pom == 11)
				tab[i][j] = BLEKITNY;
			else if (pom == 12)
				tab[i][j] = CZERWONY;
			else if (pom == 13)
				tab[i][j] = ROZOWY;
			else if (pom == 14)
				tab[i][j] = ZOLTY;
			else if (pom == 15)
				tab[i][j] = BIALY;
			else if (pom == 57)
				tab[i][j] = NOWY_NIEBIESKI;
			else if (pom == 58)
				tab[i][j] = NOWY_ZIELONY;
			else if (pom == 59)
				tab[i][j] = NOWY_BLEKITNY;
			else if (pom == 60)
				tab[i][j] = NOWY_CZERWONY;
			else if (pom == 61)
				tab[i][j] = NOWY_ROZOWY;
			else if (pom == 62)
				tab[i][j] = NOWY_ZOLTY;
			else if (pom == 63)
				tab[i][j] = NOWY_BIALY;
		}
	}
}

void zapisz_wynik(fstream &file, gracz *uzytkownik)
{
	struct wynik
	{
		string nazwa_gracza;
		int punkty;
		//struct wynik *nast;
	};
	wynik gracz;
	
	vector <wynik> wszyscy_gracze;
	string pom;
	
	//spr czy plik z wynikami pusty
	file.open("wyniki.txt", ios::in);
	if (file.good())
	{
		file >> pom;
		if (file.eof())
		{
			file.close();
			file.open("wyniki.txt", ios::out);
			file << uzytkownik->get_nazwagracza() << "\t" << uzytkownik->get_punkty() << endl;
		}
		else
		{
			//wczytywanie dotychczasowych wynikow
			file.close();
			file.open("wyniki.txt", ios::in);
			
			while (file >> gracz.nazwa_gracza >> gracz.punkty)
			{
				wszyscy_gracze.push_back(gracz);
			}
			file.close();

			//zapisanie z uwzglednieniem aktualnego wyniku
			file.open("wyniki.txt", ios::out);
			bool czy_wpisano = false;

			for (unsigned int i = 0; i < wszyscy_gracze.size(); i++)
			{
				if (!czy_wpisano && (uzytkownik->get_punkty() >= wszyscy_gracze[i].punkty))
				{
					file << uzytkownik->get_nazwagracza() << "\t" << uzytkownik->get_punkty() << endl;
					czy_wpisano = true;
				}
				file << wszyscy_gracze[i].nazwa_gracza << "\t" << wszyscy_gracze[i].punkty << endl;
			}
			if (!czy_wpisano)
				file << uzytkownik->get_nazwagracza() << "\t" << uzytkownik->get_punkty() << endl;;		//najnizszy wynik
			
			file.close();
		}
	}
	else							//jesli pliku nie ma z wynikami
	{
		file.open("wyniki.txt", ios::out);
		file << uzytkownik->get_nazwagracza() << "\t" << uzytkownik->get_punkty();
		file.close();
	}
}

void pokaz_tablice_wynikow(fstream &file)
{
	string nazwa;
	int wynik;
	int ile=0;
	HANDLE kolor_tekstu;
	kolor_tekstu = GetStdHandle(STD_OUTPUT_HANDLE);

	file.open("wyniki.txt", ios::in);
	file >> nazwa;
	if (!file.good() || file.eof())
	{
		cout << "BRAK WYNIKOW !" << endl;
		file.close();
	}
	else
	{
		file.close();
		file.open("wyniki.txt", ios::in);
		SetConsoleTextAttribute(kolor_tekstu, 10);
		cout << endl << "TABLICA WYNIKOW :" << endl;
		SetConsoleTextAttribute(kolor_tekstu, 7);
		cout << "NAZWA GRACZA :\tWYNIK:" << endl;
		while (file >> nazwa >> wynik)
		{
			cout << nazwa << "\t\t" << wynik << endl;
		}
		file.close();
	}
}

bool niedokonczona_gra(fstream &file)
{
	file.open("temp.txt",ios::in);
												//czy istnieje plik z ostatnia rozgrywka
	if (file.good())
	{
		string pom;
		file >> pom;								
		if (file.eof())
		{
			file.close();
			return false;							//pusty
		}								
		else
		{
			file.close();
			return true;							//jesli nie pusty i mozemy czytac
		}
	}
	else
	{
		file.close();
		return false;								//pliku nie ma, zostanie stworzony
	}
}