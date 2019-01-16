#include "winbgim.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <algorithm>
#include <iterator>
#include <windows.h>

using namespace std;
ifstream fin("pvp.txt");
ofstream fout("pvp.txt", ios_base::app);
ifstream gin("pvc.txt");
ofstream gout("pvc.txt", ios_base::app);

DWORD screenWidth =GetSystemMetrics(SM_CXSCREEN);
DWORD screenHeight= GetSystemMetrics(SM_CYSCREEN);

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

int stanga, sus, width, height, latura, numar, alegere, player = 1, stopComputer, gameOver;
bool gata;
void meniu(int &alegere);
void initMeniu();
int TablaDeJoc[MAX][MAX];
int memJ[3][5];

void afisareButonMeniu(){ //robert
    setcolor(WHITE);
    int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
    outtextxy(midx *1.72  , midy/2.75 , "Meniu");
	rectangle(midx *1.8, midy /3, midx *1.7, midy /2.4);
}

void resetarescor(int alegere) { //robert
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

void adaugarescor(int alegere, int s) { //robert
    //alegere = 1 - player vs player
    //alegere = 2 - player vs calculator
    //s = 1 - player 1
    //s = 2 - player 2/calculator
	if (alegere == 1)
		fout << s << endl;
	if (alegere == 2)
		gout << s << endl;
}

void melodiefundal(){ //robert
    PlaySound("sound\\menu.wav", NULL, SND_LOOP | SND_ASYNC);
}

void afisarescor() { //robert
	cleardevice();
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	outtextxy(midx - 50, 60, "Tabel scor");

	outtextxy(midx - 290, 100, "Jucator vs Jucator");
	rectangle(midx - 350, 120, midx - 25, midy+200);

	outtextxy(midx + 70, 100, "Jucator vs Calculator");
	rectangle(midx + 25, 120, midx + 350, midy+200);

	outtextxy(midx - 260, midy+225, "Resetare scor");
	rectangle(midx - 275, midy+210, midx -100, midy+260);

	outtextxy(midx + 115, midy+225, "Resetare scor");
	rectangle(midx + 100, midy+210, midx + 275, midy+260);

	outtextxy(midx /10 +15 , midy/7.5 , "Inapoi");
	rectangle(midx /10, midy /10, midx /5, midy /5);

	int i = 0, j = 0, ip, jp, k, a1[20], a2[20];
	char v[50];

    fin.close();
    fin.open("pvp.txt");
    gin.close();
    gin.open("pvc.txt");
    for(i=0;i<20;i++){
        a1[i] = 0;
        a2[i] = 0;
    }
    i=0;j=0;

	while (fin >> k) {
		a1[i] = k;
		i++;
		if (i > 19) break;
	}
	while (gin >> k) {
		a2[j] = k;
		j++;
		if (j > 19) break;
	}
	i--;j--;
	ip = jp = 130;

	while (i >= 0) {
		if (a1[i] == 1)
			sprintf(v, "Jucatorul 1 a castigat");
		if (a1[i] == 2)
			sprintf(v, "Jucatorul 2 a castigat");

		outtextxy(midx - 335, ip, v);
		i--;
		ip += 30;
	}
	while (j >= 0) {
		if (a2[j] == 1)
			sprintf(v, "Ai castigat");
		if (a2[j] == 2)
			sprintf(v, "Calculatorul a castigat");

		outtextxy(midx + 40, jp, v);
		j--;
		jp += 30;
        }

    int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();
            if(x>(midx-275)&&x<(midx-100)&&y>(midy+100)&&y<(midy+260)){
                resetarescor(1);
                afisarescor();
                break;
            }
            if(x>(midx+100) && x<(midx+275) && y>(midy+210) && y<(midy+260)){
                resetarescor(2);
                afisarescor();
                break;
            }
            if(x>(midx/10) && x<(midx/5) && y>(midy/10) && y<(midy/5)){
                cleardevice();
                initMeniu();
                return;
            }
        }
	}
    getch();
}

void culoarefundal() { //Monica - alege culoarea de fundal
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

	outtextxy(midx /10 +15 , midy/7.5 , "Inapoi");
	rectangle(midx /10, midy /10, midx /5, midy /5);

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
			if(x>(midx/10) && x<(midx/5) && y>(midy/10) && y<(midy/5)){
                cleardevice();
                initMeniu();
                return;
            }
		}
	}
	cleardevice();
    initMeniu();
}

void culoarepiese() { //Monica - alege culoarea pieselor si a liniilor
	cleardevice();

	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 30, (150 + 230) / 2 - 10, "Verde");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 20, (250 + 330) / 2 - 10, "Alb");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 40, (350 + 430) / 2 - 10, "Violet");

	rectangle(midx - 200, 450, midx + 200, 530);
	outtextxy(midx - 25, (450 + 530) / 2 - 10, "Rosu");

	rectangle(midx - 200, 550, midx + 200, 630);
	outtextxy(midx - 35, (550 + 630) / 2 - 10, "Portocaliu");

	outtextxy(midx /10 +15 , midy/7.5 , "Inapoi");
	rectangle(midx /10, midy /10, midx /5, midy /5);

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
				PIESA = RGB(100, 50, 150);
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
			if(x>(midx/10) && x<(midx/5) && y>(midy/10) && y<(midy/5)){
                cleardevice();
                initMeniu();
                return;
            }
		}
	}
	cleardevice();
    initMeniu();
}

void stergePiesa(int linia, int coloana)
{
	int x1, y1, x2, y2, xmijloc, ymijloc;
	x1 = stanga + latura * (coloana - 1);
	y1 = sus + latura * (linia - 1);
	x2 = x1 + latura; y2 = y1 + latura;
	xmijloc = (x1 + x2) / 2; ymijloc = (y1 + y2) / 2;
	setcolor(PIESA); rectangle(x1, y1, x2, y2);
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
	setcolor(PIESA);
	rectangle(x1, y1, x2, y2); setcolor(FUNDAL);
	setfillstyle(SOLID_FILL, FUNDAL);
	bar(xmijloc - 20, ymijloc - 20, xmijloc + 20, ymijloc + 20);
	setcolor(codPiesa);
	setfillstyle(SOLID_FILL, codPiesa);
	fillellipse(xmijloc, ymijloc, 18, 15);
}

void deseneazaMutariPosibile(int linia, int coloana, int codPiesa) //robert
{
	int x1, y1, x2, y2, xmijloc, ymijloc;
	x1 = stanga + latura * (coloana - 1);
	y1 = sus + latura * (linia - 1);
	x2 = x1 + latura; y2 = y1 + latura;
	xmijloc = (x1 + x2) / 2; ymijloc = (y1 + y2) / 2;
	setcolor(PIESA);
	rectangle(x1, y1, x2, y2); setcolor(FUNDAL);
	setfillstyle(SOLID_FILL, FUNDAL);
	bar(xmijloc - 20, ymijloc - 20, xmijloc + 20, ymijloc + 20);
	setcolor(YELLOW);
	setfillstyle(SOLID_FILL, YELLOW);
	fillellipse(xmijloc, ymijloc, 18, 15);
}

void stergereMutariPosibile(int linia,int coloana, int codPiesa){ //robert
    int x1, y1, x2, y2, xmijloc, ymijloc;
	x1 = stanga + latura * (coloana - 1);
	y1 = sus + latura * (linia - 1);
	x2 = x1 + latura; y2 = y1 + latura;
	xmijloc = (x1 + x2) / 2; ymijloc = (y1 + y2) / 2;
	setcolor(PIESA);
	rectangle(x1, y1, x2, y2); setcolor(FUNDAL);
	setfillstyle(SOLID_FILL, FUNDAL);
	bar(xmijloc - 20, ymijloc - 20, xmijloc + 20, ymijloc + 20);
	setcolor(FUNDAL);
	setfillstyle(SOLID_FILL, FUNDAL);
	fillellipse(xmijloc, ymijloc, 18, 15);
}

void mutariPosibile(int jucator,int coloana1,int linia1){ //robert
    if(jucator==1)
    for(int i = linia1-1;i>0;i--){
        if(TablaDeJoc[i][coloana1]==PIESA)
            break;
        else deseneazaMutariPosibile(i, coloana1, PIESA);
    }
    if(jucator==2)
    for(int i = coloana1+1;i<=numar;i++){
    if(TablaDeJoc[linia1][i]==PIESA)
        break;
    else deseneazaMutariPosibile(linia1, i, PIESA);
    }
}

void stergerePosibile(int jucator,int coloana1,int linia1){ //robert
    if(jucator==1)
    for(int i = linia1-1;i>0;i--){
        if(TablaDeJoc[i][coloana1]==SPATIU)
            stergereMutariPosibile(i, coloana1, PIESA);
        else break;
    }
    if(jucator==2)
    for(int i = coloana1+1;i<=numar;i++){
        if(TablaDeJoc[linia1][i]==SPATIU)
            stergereMutariPosibile(linia1, i, PIESA);
        else break;
    }
}

void afisareButonUndo(){ //robert - se afiseaza butonul undo doar atunci cand se poate folosi
    int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
    setcolor(WHITE);
    outtextxy(midx *1.72  , midy/2.15 , "Undo");
	rectangle(midx *1.8, midy /2.3, midx *1.7, midy /1.9);
}

void ascundereButonUndo(){ //robert
    int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
    setcolor(FUNDAL);
    outtextxy(midx *1.72  , midy/2.15 , "Undo");
	rectangle(midx *1.8, midy /2.3, midx *1.7, midy /1.9);
	setcolor(WHITE);
}

void undoMutare1(int linia1,int linia2,int coloana1,int coloana2){ //robert
        TablaDeJoc[linia1][coloana1] = PIESA;
        TablaDeJoc[linia2][coloana2] = SPATIU;
        stergePiesa(linia2, coloana2);
        deseneazaPiesa(linia1, coloana1, PIESA);
        ascundereButonUndo();
}

bool inInterior(int x, int y, int x1, int y1, int x2, int y2)
{
	return x1 <= x && x <= x2 && y1 <= y && y <= y2;
}

int verifCastigator(int player, int codPiesa) { //Monica - verifica daca a castigat player
	if (player == 1) { //Verific pentru primul jucator
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

void mutarePrimulJucator(int coloana1, int coloana2, int linia1, int linia2, int &ok) { //Monica - mutarea primului jucator
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
                    stergerePosibile(1,coloana1,linia1);
					stopComputer = 0;
					TablaDeJoc[linia1][coloana1] = SPATIU;
					TablaDeJoc[linia2][coloana2] = PIESA;
					stergePiesa(linia1, coloana1);
					deseneazaPiesa(linia2, coloana2, PIESA);
					PlaySound("sound\\move.wav", NULL, SND_ASYNC);
				}
				else {
				    stergerePosibile(1,coloana1,linia1);
                        setcolor(WHITE);
                    PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
					outtextxy(midx - 280, 70, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
				}
			}
			else {
                    stergerePosibile(1,coloana1,linia1);
                    setcolor(WHITE);
                PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
				outtextxy(midx - 280, 70, "Muta doar in sus! Te rog sa selectezi din nou o piesa.");
			}
		}
		else {
                stergerePosibile(1,coloana1,linia1);
                setcolor(WHITE);
            PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
			outtextxy(midx - 300, 70, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
		}
	}
	else {
            stergerePosibile(1,coloana1,linia1);
            setcolor(WHITE);
        PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
		outtextxy(midx - 300, 70, "Muta doar pe verticala! Te rog sa selectezi din nou o piesa.");
	}
}

void mutareAlDoileaJucator(int coloana1, int coloana2, int linia1, int linia2, int &ok) { //Monica - mutarea celui de-al doilea jucator
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
                    stergerePosibile(2,coloana1,linia1);
					TablaDeJoc[linia1][coloana1] = SPATIU;
					TablaDeJoc[linia2][coloana2] = PIESA;
					stergePiesa(linia1, coloana1);
					deseneazaPiesa(linia2, coloana2, PIESA);
					PlaySound("sound\\move.wav", NULL, SND_ASYNC);
				}
				else {
                        stergerePosibile(2,coloana1,linia1);
                        setcolor(WHITE);
                    PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
					outtextxy(midx - 280, 70, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
				}
			}
			else {
                    stergerePosibile(2,coloana1,linia1);
                    setcolor(WHITE);
                PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
				outtextxy(midx - 285, 70, "Muta doar in dreapta! Te rog sa selectezi din nou o piesa.");
			}
		}
		else {
                stergerePosibile(2,coloana1,linia1);
                setcolor(WHITE);
            PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
			outtextxy(midx - 300, 70, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
		}
	}
	else {
            stergerePosibile(2,coloana1,linia1);
            setcolor(WHITE);
        PlaySound("sound\\incorrectMove.wav", NULL, SND_ASYNC);
		outtextxy(midx - 300, 70, "Muta doar pe orizontala! Te rog sa selectezi din nou o piesa.");
	}
}

void mutareCalculator() { //Monica - mutarea calculatorului

	int a[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::random_shuffle(std::begin(a), std::end(a)); //linia sa fie random

	int b[] = { 1, 2, 3, 4, 5, 6, 7, 8 };
	std::random_shuffle(std::begin(b), std::end(b)); //coloana sa fie random

	for (int i : a)
		if (i <= numar) {
			for (int j : b) {
				if (j < numar)
					if (TablaDeJoc[i][j] == PIESA && TablaDeJoc[i][j + 1] == SPATIU) {
						TablaDeJoc[i][j] = SPATIU;
						TablaDeJoc[i][j + 1] = PIESA;
						stergePiesa(i, j);
						deseneazaPiesa(i, j + 1, PIESA);
						PlaySound("sound\\move.wav", NULL, SND_ASYNC);
						return;
					}
			}
		}
}

void TerminareJoc() { //Monica - meniu pentru cand se termina jocul
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	rectangle(midx - 300, 130, midx - 110, 170);
	outtextxy(midx - 285, (130 + 170) / 2 - 10, "Incepe alt joc");

	rectangle(midx - 90, 130, midx + 100, 170);
	outtextxy(midx - 15, (130 + 170) / 2 - 10, "Scor");

	rectangle(midx + 110, 130, midx + 300, 170);
	outtextxy(midx + 170, (130 + 170) / 2 - 10, "Iesire");

	int x, y;
	while (true) {
		if (ismouseclick(WM_LBUTTONDOWN) != 0) {
			clearmouseclick(WM_LBUTTONDOWN);
			x = mousex();
			y = mousey();

			if ((x >= midx - 300 && x <= midx - 110 && y >= 130 && y <= 170) != 0) {//daca se alege sa se joace din nou
				closegraph();
				initwindow(screenWidth, screenHeight, "",-3,-3);
				melodiefundal();
				initMeniu();
				break;
			}

			if ((x >= midx - 90 && x <= midx + 100 && y >= 130 && y <= 170) != 0) {
				closegraph();
				initwindow(screenWidth, screenHeight, "",-3,-3);
				melodiefundal();
				afisarescor();
				break;
			}

			if ((x >= midx + 110 && x <= midx + 300 && y >= 130 && y <= 170) != 0) {
				exit(0);
				break;
			}
		}
	}
}

void verifCastigMutare(int ok, int &player) { //Monica - verifica player-ul care a castigat
	int midx;
	midx = getmaxwidth() / 2;
	if (ok == 0) //daca a fost vreo eroare luam de la capat
		if (player == 1) player = 2; //Al doilea jucator va avea din nou valoarea 2
		else player = 1;
	else
		if (verifCastigator(player, PIESA) == 1) {
			gameOver = 1; //oprim jocul
		    if(alegere==1 && player == 1){
                outtextxy(midx - 110, 80, "Jucatorul 1 castigat.");
                PlaySound("sound\\endgame.wav", NULL, SND_ASYNC);
                adaugarescor(1,1);
                TerminareJoc();
		    }
			if (alegere==1 && player==2) {
                outtextxy(midx - 110, 80, "Jucatorul 2 a castigat.");
                PlaySound("sound\\endgame.wav", NULL, SND_ASYNC);
                adaugarescor(1,2);
                TerminareJoc();
			}
			if (alegere == 2 && player == 2) {
				outtextxy(midx - 50, 80, "Ai castigat."); stopComputer = 1; //oprim computer-ul din mutarea automata dupa ce a pierdut
                adaugarescor(2,1);
                PlaySound("sound\\win.wav", NULL, SND_ASYNC);
                TerminareJoc();
			}
            if (alegere == 2) {
				outtextxy(midx - 110, 80, "Calculatorul a castigat.");
				PlaySound("sound\\lose.wav", NULL, SND_ASYNC);
				adaugarescor(2,2);
				TerminareJoc();
			}
		}
}

void DisplayErrors() { //Monica - afisarea erorilor din mutari
	int midx = getmaxwidth() / 2;
	setcolor(FUNDAL);
	outtextxy(midx - 90, 70, "Selecteaza un cerc");
	outtextxy(midx - 300, 70, "Muta doar pe verticala! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 300, 70, "Muta doar pe orizontala! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 300, 70, "Muta pe spatiile libere! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 280, 70, "Muta doar in sus! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 285, 70, "Muta doar in dreapta! Te rog sa selectezi din nou o piesa.");
	outtextxy(midx - 280, 70, "Nu sari alte piese! Te rog sa selectezi din nou o piesa.");
	setcolor(WHITE);
}

void mutarePiesa(int codPiesa) //Monica - mutare piesa pentru ambele variante de joc + afisare jucatori
{
	if (gameOver == 0) {
		int linia1, coloana1, linia2, coloana2, x, y, ok = 0;
		int clinia1,ccoloana1,clinia2,ccoloana2;
		int x1, y1, x2, y2;
		int xmijloc, ymijloc;
		int midx = getmaxwidth() / 2, midy = getmaxheight() / 2;
		bool mutareCorecta;

        int okUndo=0;

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
		    undo_0:
			iesireUrgenta();
			mutareCorecta = false;
			if(ismouseclick(WM_LBUTTONDOWN) && x<(midx*1.8) && x>(midx*1.7) && y>(midy/3) && y<(midy/2.4))
            {
            closegraph();
            initwindow(screenWidth, screenHeight, "",-3,-3);
            melodiefundal();
            initMeniu();
            break;
            }
            x=mousex();
            y=mousey();
            if(ismouseclick(WM_LBUTTONDOWN)&&x>(midx*1.7)&&x<(midx*1.8)&&y>(midy/2.3)&&y<(midy/1.9)){
                clearmouseclick(WM_LBUTTONDOWN);
                undoMutare1(clinia1,clinia2,ccoloana1,ccoloana2);
                if(player==1)player=2;
                else player=1;
                goto undo_0;
            }

			if (alegere == 1) {
				if (ismouseclick(WM_LBUTTONDOWN) && inInterior(x = mousex(), y = mousey(), stanga, sus, stanga + width, sus + height))
				{
					clearmouseclick(WM_LBUTTONDOWN);
					DisplayErrors(); //ascunzi erorile
					linia1 = (y - sus) / latura + 1;
					coloana1 = (x - stanga) / latura + 1;
					if (TablaDeJoc[linia1][coloana1] == codPiesa) //daca s-a selectat o piesa
					{
					    if(player==2)
					    mutariPosibile(1,coloana1,linia1);
					    else mutariPosibile(2,coloana1,linia1);

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
									ccoloana1=coloana1;
									ccoloana2=coloana2;
									clinia1=linia1;
									clinia2=linia2;
                                    afisareButonUndo();

								}

								else{
									mutareAlDoileaJucator(coloana1, coloana2, linia1, linia2, ok);//verifici daca e posibil sa muti si apoi muti
									ccoloana1=coloana1;
									ccoloana2=coloana2;
									clinia1=linia1;
									clinia2=linia2;
									afisareButonUndo();
								}
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
					    if(player==2)
					    mutariPosibile(1,coloana1,linia1);
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
}


void initTabla()
{
	cleardevice();
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
    afisareButonMeniu();
}

void initializariDimensiuni() //robert
{
	numar = 0;
	cleardevice();
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;
    settextstyle(BOLD_FONT, HORIZ_DIR, 3);
	outtextxy(midx /1.35 + 35, midy/6.7, "Alege dimensiunea tablei de joc");
    settextstyle(BOLD_FONT, HORIZ_DIR, 1);
	rectangle(midx - 200, 150, midx + 200, 230);
	outtextxy(midx - 15, (150 + 230) / 2 - 10, "4x4");

	rectangle(midx - 200, 250, midx + 200, 330);
	outtextxy(midx - 15, (250 + 330) / 2 - 10, "6x6");

	rectangle(midx - 200, 350, midx + 200, 430);
	outtextxy(midx - 15, (350 + 430) / 2 - 10, "8x8");

	outtextxy(midx /10 +15, midy/7.5 , "Inapoi");
	rectangle(midx /10, midy /10, midx /5, midy /5);

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
				width = 500;
				height = 500;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				numar = 8;
				width = 500;
				height = 500;
			}
			if(x>(midx/10) && x<(midx/5) && y>(midy/10) && y<(midy/5)){
                cleardevice();
                initMeniu();
                return;
            }
			latura = width / numar;
			sus = (getmaxy() - width) / 2;
			stanga = (getmaxx() - height) / 2;
		}
		if (numar != 0)
			break;
	}
}


void meniu(int &alegere) {//robert
    cleardevice();
	int midx, midy;
	midx = getmaxwidth() / 2;
	midy = getmaxheight() / 2;

	settextstyle(BOLD_FONT, HORIZ_DIR, 6);
	outtextxy(midx /1.08, midy/7, "Impas");
	settextstyle(BOLD_FONT, HORIZ_DIR, 1);

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

			if ((x >= midx - 200 && x <= midx + 200 && y >= 150 && y <= 230) != 0) {
				alegere = 1;
                initializariDimensiuni();
				return;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 250 && y <= 330) != 0) {
				alegere = 2;
				initializariDimensiuni();
				return;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 350 && y <= 430) != 0) {
				afisarescor();
				return;
			}

			if ((x >= midx - 200 && x <= midx + 200 && y >= 450 && y <= 530) != 0) {
				culoarefundal();
				return;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 550 && y <= 630) != 0) {
				culoarepiese();
				return;
			}
			if ((x >= midx - 200 && x <= midx + 200 && y >= 650 && y <= 730) != 0) {
				exit(0);
				return;
			}
		}
	}
}

void initMeniu()
{
    meniu(alegere);
	initTabla();
	desenTabla();
	gameOver = 0; //initiem gameOver cu 0 pentru ca e la inceputul jocului si nu am terminat inca
	player = 1;
	while (gameOver != 1) {
		mutarePiesa(PIESA);
	}
	TerminareJoc();
}

int main()
{
	initwindow(screenWidth, screenHeight, "",-3,-3);
	melodiefundal();
	initMeniu();
	return 0;
}
