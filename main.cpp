#include <iostream>
#include "winbgim.h"
#include <stdlib.h>
#include <fstream>

using namespace std;
ifstream fin("pvp.txt");
ofstream fout("pvp.txt", ios_base::app);
ifstream gin("pvc.txt");
ofstream gout("pvc.txt", ios_base::app);

#define MAX 20
int FUNDAL = BLACK;
#define SPATIU 0
int PIESA = WHITE;

void iesireUrgenta()
{
	char tasta;
	if (kbhit())
	{
		tasta = getch();
		if (tasta == 27)
		{
			closegraph();
			exit(0);
		}
	}
}

int stanga, sus, width, height, latura, numar, alegere, player = 1, stopComputer;
bool gata;
void meniu(int &alegere);
void initMeniu();
int TablaDeJoc[MAX][MAX];


void resetarescor(int alegere) {
	if (alegere == 1) {
		fout.close();
		fout.open("pvp.txt");
		fout << "";
		fout.close();
		fout.open("pvp.txt", ios_base::app);
	}
	if (alegere == 2) {
		gout.close();
		gout.open("pvc.txt");
		gout << "";
		gout.close();
		gout.open("pvc.txt", ios_base::app);
	}
}

void adaugarescor(int s1, int s2, int alegere) {
	if (alegere == 1)
		fout << s1 << ' ' << s2 << endl;
	if (alegere == 2)
		gout << s1 << ' ' << s2 << endl;
}

void afisarescor() {
	cleardevice();
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	outtextxy(midx - 50, 60, "Tabel scor");

	outtextxy(midx - 290, 130, "Jucator vs Jucator");
	rectangle(midx - 350, 150, midx - 25, 700);

	outtextxy(midx + 70, 130, "Jucator vs Calculator");
	rectangle(midx + 25, 150, midx + 350, 700);

	int i = 0, j = 0, ip, jp, x, y, a1[20][2], a2[20][2];
	char v[50];

	while (fin >> x >> y) {
		a1[i][0] = x;
		a1[i][1] = y;
		i++;
		if (i > 19) break;
	}
	while (gin >> x >> y) {
		a2[j][0] = x;
		a2[j][1] = y;
		j++;
		if (j > 19) break;
	}
	i--;j--;
	ip = jp = 160;

	while (i >= 0) {
		if (a1[i][0] > a1[i][1])
			sprintf(v, "Jucatorul 1 a castigat (%d-%d)", a1[i][0], a1[i][1]);
		if (a1[i][0] < a1[i][1])
			sprintf(v, "Jucatorul 2 a castigat (%d-%d)", a1[i][0], a1[i][1]);
		if (a1[i][0] == a1[i][1])
			sprintf(v, "Remiza (%d-%d)", a1[i][0], a1[i][1]);

		outtextxy(midx - 345, ip, v);
		i--;
		ip += 20;
	}
	while (j >= 0) {
		if (a2[j][0] > a2[j][1])
			sprintf(v, "Jucatorul a castigat (%d-%d)", a2[j][0], a2[j][1]);
		if (a2[j][0] < a2[j][1])
			sprintf(v, "Calculatorul a castigat (%d-%d)", a2[j][0], a2[j][1]);
		if (a2[j][0] == a2[j][1])
			sprintf(v, "Remiza (%d-%d)", a2[j][0], a2[j][1]);

		outtextxy(midx + 30, jp, v);
		j--;
		jp += 20;
	}

	getch();
}

void culoarefundal() { //monica
	cleardevice();

	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
	
	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 30, (150 + 230) / 2 - 10, "Negru");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 20, (250 + 330) / 2 - 10, "Verde");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 40, (350 + 430) / 2 - 10, "Albastru");

	rectangle(midx - 200, 450, midx + 200, 530);
	outtextxy(midx - 25, (450 + 530) / 2 - 10, "Rosu");

	rectangle(midx - 200, 550, midx + 200, 630);
	outtextxy(midx - 35, (550 + 630) / 2 - 10, "Turcoaz");

	int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();

			if ((x >= midx - 200 && x <= midx + 200 && y >= 150 && y <= 230) != 0) {//optiuni meniu
				FUNDAL = BLACK;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 250 && y <= 330) != 0) {
				FUNDAL = GREEN;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				FUNDAL = BLUE;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 450 && y <= 530) != 0) {
				FUNDAL = RED;
				break;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 550 && y <= 630) != 0) {
				FUNDAL = CYAN;
				break;
			}
		}
	}
	initMeniu();
}

void culoarepiese() { //monica
	cleardevice();

	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 30, (150 + 230) / 2 - 10, "Verde");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 20, (250 + 330) / 2 - 10, "Alb");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 40, (350 + 430) / 2 - 10, "VERDE");

	rectangle(midx - 200, 450, midx + 200, 530);
	outtextxy(midx - 25, (450 + 530) / 2 - 10, "Rosu");

	rectangle(midx - 200, 550, midx + 200, 630);
	outtextxy(midx - 35, (550 + 630) / 2 - 10, "Portocaliu");

	int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();

			if ((x >= midx - 200 && x <= midx + 200 && y >= 150 && y <= 230) != 0) {//optiuni meniu
				PIESA = RGB(0, 255, 0);
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 250 && y <= 330) != 0) {
				PIESA = WHITE;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				PIESA = RGB(100, 100, 0);
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 450 && y <= 530) != 0) {
				PIESA = RGB(250, 0, 0);
				break;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 550 && y <= 630) != 0) {
				PIESA = RGB(250,120,0);
				break;
			}
		}
	}
	initMeniu();
}

void stergePiesa(int linia, int coloana)
{
	int x1, y1, x2, y2, xmijloc, ymijloc;
	x1 = stanga + latura * (coloana - 1);
	y1 = sus + latura * (linia - 1);
	x2 = x1 + latura; y2 = y1 + latura;
	xmijloc = (x1 + x2) / 2; ymijloc = (y1 + y2) / 2;
	setcolor(BLUE); rectangle(x1, y1, x2, y2);
	setcolor(FUNDAL); setfillstyle(SOLID_FILL, FUNDAL);
	bar(xmijloc - 20, ymijloc - 20, xmijloc + 20, ymijloc + 20);
}

void deseneazaPiesa(int linia, int coloana, int codPiesa)
{
	int x1, y1, x2, y2, xmijloc, ymijloc;
	x1 = stanga + latura * (coloana - 1);
	y1 = sus + latura * (linia - 1);
	x2 = x1 + latura; y2 = y1 + latura;
	xmijloc = (x1 + x2) / 2; ymijloc = (y1 + y2) / 2;
	setcolor(BLUE);
	rectangle(x1, y1, x2, y2); setcolor(FUNDAL);
	setfillstyle(SOLID_FILL, FUNDAL);
	bar(xmijloc - 20, ymijloc - 20, xmijloc + 20, ymijloc + 20);
	setcolor(codPiesa);
	setfillstyle(SOLID_FILL, codPiesa);
	fillellipse(xmijloc, ymijloc, 18, 15);
}

bool inInterior(int x, int y, int x1, int y1, int x2, int y2)
{
	return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}

int verifCastigator(int player, int codPiesa) { //Monica - verifica daca a castigat player
	if (player == 1) { //Verific pentru al doilea jucator
		for (int i = 2;i <= numar;i++)
			for (int j = 1;j <= numar;j++)
				if (TablaDeJoc[i][j] == PIESA && TablaDeJoc[i - 1][j] == SPATIU)
					return 0;
	}
	else { //al doilea jucator
		for (int i = 1;i <= numar;i++)
			for (int j = 1;j < numar;j++)
				if (TablaDeJoc[i][j] == PIESA && TablaDeJoc[i][j + 1] == SPATIU)
					return 0;
	}
	return 1;
}

void mutarePrimulJucator(int coloana1, int coloana2, int linia1, int linia2, int &ok) { //monica mutarea primului jucator
	int midx;
	midx = getmaxwidth() / 2;
	if (coloana2 == coloana1) {
		if (TablaDeJoc[linia2][coloana2] == SPATIU)
		{
			if (linia2 < linia1) {
				ok = 1;
				for (int i = linia2; i < linia1; i++) {
					if (TablaDeJoc[i][coloana2] == PIESA) ok = 0;
				}
				if (ok == 1) {
					stopComputer = 0;
					TablaDeJoc[linia1][coloana1] = SPATIU;
					TablaDeJoc[linia2][coloana2] = PIESA;
					stergePiesa(linia1, coloana1);
					deseneazaPiesa(linia2, coloana2, PIESA);
				}
				else {
					outtextxy(midx - 110, 80, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
				}
			}
			else {
				outtextxy(midx - 110, 110, "Muta doar in sus! Te rog sa selectezi din nou o piesa.");
			}
		}
		else {
			outtextxy(midx - 110, 100, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
		}
	}
	else {
		outtextxy(midx - 110, 80, "Muta doar pe verticala! Te rog sa selectezi din nou o piesa.");
	}
}
void mutareAlDoileaJucator(int coloana1, int coloana2, int linia1, int linia2, int &ok) { //monica mutarea celui de-al doilea jucator
	int midx;
	midx = getmaxwidth() / 2;
	if (linia2 == linia1) {
		if (TablaDeJoc[linia2][coloana2] == SPATIU)
		{
			if (coloana2 > coloana1) {
				ok = 1;
				for (int i = coloana2; i > coloana1; i--) {
					if (TablaDeJoc[linia2][i] == PIESA) ok = 0;
				}
				if (ok == 1) {
					TablaDeJoc[linia1][coloana1] = SPATIU;
					TablaDeJoc[linia2][coloana2] = PIESA;
					stergePiesa(linia1, coloana1);
					deseneazaPiesa(linia2, coloana2, PIESA);
				}
				else {
					outtextxy(midx - 110, 80, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
				}
			}
			else {
				outtextxy(midx - 110, 110, "Muta doar in dreapta! Te rog sa selectezi din nou o piesa.");
			}
		}
		else {
			outtextxy(midx - 110, 100, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
		}
	}	
	else {
		outtextxy(midx - 110, 90, "Muta doar pe orizontala! Te rog sa selectezi din nou o piesa.");
	}
}

void mutareCalculator() { //monica mutarea calculatorului
	for (int i = 1;i <= numar;i++)
		for (int j = 1;j < numar;j++)
			if (TablaDeJoc[i][j] == PIESA && TablaDeJoc[i][j + 1] == SPATIU) {
				TablaDeJoc[i][j] = SPATIU;
				TablaDeJoc[i][j+1] = PIESA;
				stergePiesa(i, j);
				deseneazaPiesa(i, j+1, PIESA);
				i = numar + 1; j = numar;
			}
}

void verifCastigMutare(int ok, int &player) { //monica verifica player-ul care a castigat
	int midx;
	midx = getmaxwidth() / 2;
	if (ok == 0)
		if (player == 1) player = 2; //Al doilea jucator va avea din nou valoarea 2
		else player = 1;
	else
		if (verifCastigator(player, PIESA) == 1)
			if (player == 2) {
				outtextxy(midx - 110, 90, "Player 1 a castigat."); stopComputer = 1; //oprim computer-ul din mutarea automata dupa ce a pierdut
			}
			else if (alegere == 2) outtextxy(midx - 110, 90, "Calculatorul a castigat.");
			else outtextxy(midx - 110, 90, "Jucatorul 2 a castigat.");
}
void DisplayErrors() { //monica afisarea erorilor din mutari
	int midx = getmaxwidth() / 2;
	setcolor(FUNDAL);
	outtextxy(midx - 90, 70, "Selecteaza un cerc");
	outtextxy(midx - 110, 80, "Muta doar pe verticala! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 110, 90, "Muta doar pe orizontala! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 110, 100, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 95, 110, "Muta doar in sus! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 100, 110, "Muta doar in dreapta! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 110, 80, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
	setcolor(WHITE);
}
void mutarePiesa(int codPiesa) //Monica - mutare piesa pentru ambele variante de joc + afisare jucatori
{
	int linia1, coloana1, linia2, coloana2, x, y, ok=0;
	int x1, y1, x2, y2;
	int xmijloc, ymijloc;
	int midx = getmaxwidth() / 2;
	bool mutareCorecta;

	if (player == 1) player = 2;
	else player = 1;
	//inversam valorile


	if (alegere == 1) { //jucator vs jucator
		if (player == 1) {
			setcolor(FUNDAL); outtextxy(midx - 50, 40, "Jucator 2"); //ascunzi textul Jucatorul 2
			setcolor(WHITE); outtextxy(midx - 50, 40, "Jucator 1");
		}
		else {
			setcolor(FUNDAL); outtextxy(midx - 50, 40, "Jucator 1"); //ascunzi textul Jucatorul 1
			setcolor(WHITE); outtextxy(midx - 50, 40, "Jucator 2");
		}
	} //Afisam jucatorul curent pentru jucator vs jucator

	do
	{
		
		iesireUrgenta();
		mutareCorecta = false;
		if (alegere == 1) {
			if (ismouseclick(WM_LBUTTONDOWN) && inInterior(x = mousex(), y = mousey(), stanga, sus, stanga + width, sus + height))
			{
				clearmouseclick(WM_LBUTTONDOWN);
				DisplayErrors(); //ascunzi erorile
				linia1 = (y - sus) / latura + 1;
				coloana1 = (x - stanga) / latura + 1;
				if (TablaDeJoc[linia1][coloana1] == codPiesa) //daca s-a selectat o piesa
				{
					do
					{
						iesireUrgenta();
						int ok = 0; //resetam ok
						if (ismouseclick(WM_LBUTTONDOWN) && inInterior(x = mousex(), y = mousey(), stanga, sus, stanga + width, sus + height))
						{
							clearmouseclick(WM_LBUTTONDOWN);
							linia2 = (y - sus) / latura + 1;
							coloana2 = (x - stanga) / latura + 1;
							if (player == 2) { //Primul jucator trebuie sa mearga pe verticala, player e 2 pentru ca au fost inversate la inceput
								mutarePrimulJucator(coloana1, coloana2, linia1, linia2, ok); //verifici daca e posibil sa muti si apoi muti
							}
							else
								mutareAlDoileaJucator(coloana1, coloana2, linia1, linia2, ok);//verifici daca e posibil sa muti si apoi muti
							mutareCorecta = true; //iesim din do
							verifCastigMutare(ok, player); //verifici daca a castigat
						}
					} while (!mutareCorecta);
				}
				else {
					setcolor(WHITE);
					outtextxy(midx - 90, 70, "Selecteaza un cerc");
				}
			}
		}
		else {
			if (ismouseclick(WM_LBUTTONDOWN) && inInterior(x = mousex(), y = mousey(), stanga, sus, stanga + width, sus + height) && player == 2)
			{ //daca e primul jucator si a dat click

				clearmouseclick(WM_LBUTTONDOWN);
				DisplayErrors(); //ascunzi erorile
				linia1 = (y - sus) / latura + 1;
				coloana1 = (x - stanga) / latura + 1;
				if (TablaDeJoc[linia1][coloana1] == codPiesa)
				{
					do
					{
						iesireUrgenta();
						int ok = 0; //resetam ok
						if (ismouseclick(WM_LBUTTONDOWN) && inInterior(x = mousex(), y = mousey(), stanga, sus, stanga + width, sus + height))
						{
							clearmouseclick(WM_LBUTTONDOWN);
							linia2 = (y - sus) / latura + 1;
							coloana2 = (x - stanga) / latura + 1;
							mutarePrimulJucator(coloana1, coloana2, linia1, linia2, ok);//verifici daca e posibil sa muti si apoi muti
							mutareCorecta = true; //iesim din do
							verifCastigMutare(ok, player); //verifici daca jucatorul a castigat si stopComputer se transforma in 1 astfel
							//incat functia automata pentru a misca piesele de catre computer nu va mai putea fi accesata pentru ca
							//computerul a pierdut
						}
					} while (!mutareCorecta);
				}
				else {
					setcolor(WHITE);
					outtextxy(midx - 90, 70, "Selecteaza un cerc");
				}
			}
			else if (player == 1 && stopComputer == 0) {
				mutareCalculator();
				ok = 1; //mutarea e mereu corecta pentru ca e automata
				verifCastigMutare(ok, player); //verifici daca a castigat calculatorul
				player = 2; //trece la al doilea jucator fara a reseta mutareCorecta
			}
		}
	} while (!mutareCorecta);
}


void initTabla()
{
	cleardevice();
	//numar=numar/2;
	int linia, coloana;
	for (linia = 1; linia <= numar; linia++)
		for (coloana = 1; coloana <= numar; coloana++)
			if (linia < numar / 2 + 1 || coloana > numar / 2)
				TablaDeJoc[linia][coloana] = SPATIU;
			else
				TablaDeJoc[linia][coloana] = PIESA;
}

void desenTabla()
{

	setbkcolor(FUNDAL); cleardevice();


	int linia, coloana;
	for (linia = 1; linia <= numar; linia++)
		for (coloana = 1; coloana <= numar; coloana++)
		{
			if (linia < numar/2+1 || coloana > numar/2)
				stergePiesa(linia, coloana);
			else
				deseneazaPiesa(linia, coloana, TablaDeJoc[linia][coloana]);
		}
}

void initializariDimensiuni()
{
	numar = 0;
	cleardevice();
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	outtextxy(midx - 170, 70, "Alege dimensiunea tablei de joc");

	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 15, (150 + 230) / 2 - 10, "4x4");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 15, (250 + 330) / 2 - 10, "6x6");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 15, (350 + 430) / 2 - 10, "8x8");

	int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();

			if ((x >= midx - 200 && x <= midx + 200 && y >= 150 && y <= 230) != 0) {
				numar = 4;
				width = 400;
				height = 400;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 250 && y <= 330) != 0) {
				numar = 6;
				width = 600;
				height = 600;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				numar = 8;
				width = 800;
				height = 800;
			}
			latura = width / numar;
			sus = (getmaxy() - width) / 2;
			stanga = (getmaxx() - height) / 2;
		}
		if (numar != 0)
			break;
	}
}

void meniu(int &alegere) { 

	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy(midx - 20, 70, "Impas");

	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 100, (150 + 230) / 2 - 10, "Jucator vs Jucator");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 100, (250 + 330) / 2 - 10, "Jucator vs Calculator");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 25, (350 + 430) / 2 - 10, "Scor");

	rectangle(midx - 200, 450, midx + 200, 530);
	outtextxy(midx - 100, (450 + 530) / 2 - 10, "Culoarea de fundal");

	rectangle(midx - 200, 550, midx + 200, 630);
	outtextxy(midx - 100, (550 + 630) / 2 - 10, "Culoarea pieselor");

	rectangle(midx - 200, 650, midx + 200, 730);
	outtextxy(midx - 35, (650 + 730) / 2 - 10, "Iesire");

	int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();

			if ((x >= midx - 200 && x <= midx + 200 && y >= 150 && y <= 230) != 0) {//optiuni meniu
				alegere = 1;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 250 && y <= 330) != 0) {
				alegere = 2;
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				afisarescor();
				break;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 450 && y <= 530) != 0) {
				culoarefundal();
				break;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 550 && y <= 630) != 0) {
				culoarepiese();
				break;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 650 && y <= 730) != 0) {
				closegraph();
				break;
			}
		}
	}
}

void initMeniu()
{
	meniu(alegere);
	initializariDimensiuni();
	initTabla();
	desenTabla();
	do {
		mutarePiesa(PIESA);
	} while (true);
}
int main()
{
	initwindow(getmaxwidth(), getmaxheight());
	initMeniu();
	return 0;
}
