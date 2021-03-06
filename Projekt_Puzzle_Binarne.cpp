#include "stdafx.h"
#include <stdio.h>
#include "conio2.h"
#include "Funkcje.h"


int main() {
	int zn = 0, x = POCZATEK_RAMKI_KOLUMNA + 1, y = POCZATEK_RAMKI_WIERSZ + 1, attr = 7, back = 0, zero = 0, wymiar = 12;
	int trybAutomatyczny = 0;
#ifndef __cplusplus
	Conio2_Init();
#endif
	settitle("Tomasz Michalski 171890");
	char** plansza = inicjalizacjaPlanszy(wymiar);
	char** szablon = inicjalizacjaSzablonu(wymiar);
	wczytanieNowejPlanszy(plansza, wymiar, szablon);
	do {
		textbackground(BLACK);
		clrscr();
		textcolor(LIGHTGRAY);

		wypisanieLegendy(zn, zero, x, y);

		textcolor(attr);
		textbackground(back);
		wypisaniePlanszy(plansza, wymiar, szablon, attr);
		if (trybAutomatyczny == WLACZONY)
		{
			gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 18);
			cputs("TRYB AUTOMATYCZNY WLACZONY");
			wskazowkaDoReguly2(plansza, wymiar, attr);
			if (sprawdzenieMozliwosciUkonczeniaGry(plansza, szablon, wymiar) != 0)
			{
				gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 20);
				cputs("NIE MOZNA UKONCZYC GRY");
				textbackground(back);
			}
		}
		gotoxy(x, y);

		zero = 0;
		zn = getch();

		if (zn == 0) {
			zero = 1;
			zn = getch();
			if (zn == 0x48) y--;
			else if (zn == 0x50) y++;
			else if (zn == 0x4b) x--;
			else if (zn == 0x4d) x++;
		}
		else if (zn == ' ') attr = (attr + 1) % 16;
		else if (zn == 0x0d) back = (back + 1) % 16;
		else if (zn == '0') wstawienieLiczby(plansza, wymiar, x, y, '0', szablon);
		else if (zn == '1') wstawienieLiczby(plansza, wymiar, x, y, '1', szablon);
		else if (zn == 'n' || zn == 'N') wczytanieNowejPlanszy(plansza, wymiar, szablon);
		else if (zn == 'o' || zn == 'O') losoweWypelnienie(plansza, szablon, wymiar);
		else if (zn == 'p' || zn == P_W_ASCII) podpowiedz(plansza, wymiar, x, y, szablon);
		else if (zn == 'r' || zn == 'R')
		{
			int rozmiar = zmianaRozmiaruPlanszy();
			if (rozmiar >= 2 && rozmiar % 2 == 0)
			{
				zwolnieniePamieci(plansza, szablon, wymiar);
				wymiar = rozmiar;
				plansza = inicjalizacjaPlanszy(wymiar);
				szablon = inicjalizacjaSzablonu(wymiar);
				wczytanieNowejPlanszy(plansza, wymiar, szablon);
				x = POCZATEK_RAMKI_KOLUMNA + 1, y = POCZATEK_RAMKI_WIERSZ + 1;
			}
			else
			{
				gotoxy(POCZATEK_LEGENDY_KOLUMNA, POCZATEK_LEGENDY_WIERSZ + 21);
				cputs("Nieprawidlowy format!");
				getch();
			}
		}
		else if (zn == 'k' || zn == 'K')
		{
			sprawdzenieMozliwosciUkonczeniaGry(plansza, szablon, wymiar);
			getch();
		}
		else if (zn == 'j' || zn == 'J') podswietlenieJednoznacznychPol(plansza, szablon, wymiar);
		else if (zn == 'd' || zn == 'D')
		{
			wskazowkaDoReguly2(plansza, wymiar, attr);
			getch();
		}
		else if (zn == 'a' || zn == 'A')
		{
			if (trybAutomatyczny == WYLACZONY)
				trybAutomatyczny = WLACZONY;
			else trybAutomatyczny = WYLACZONY;
		}
	} while (zn != ESC);
	zwolnieniePamieci(plansza, szablon, wymiar);
	return 0;
}