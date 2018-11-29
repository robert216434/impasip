#include <iostream>
#include <winbgim.h>
#include <stdlib.h>

using namespace std;

#define MAX 20
#define FUNDAL WHITE

    int stanga,sus,width,height,latura, numar;
    bool gata;

    int TablaDeJoc[MAX][MAX];

    int scor;

    void afiseazaScor()
    {
        char sirScor[10];
        setcolor(FUNDAL);
        itoa (scor,sirScor,10);
        outtextxy(200,50,sirScor);
        int i,j;
        scor=0;
        for (i=1;i<=numar;i++)
        for (j=1;j<=numar;j++)
            if (TablaDeJoc[i][j]==2)
            scor++;
            setcolor(BLUE);
            itoa(scor,sirScor,10);
            outtextxy(200,50,sirScor);
    }

    void punerePiesa()
    {
        int linia,coloana,x,y;
        int x1, y1, x2, y2;
        int xmijloc, ymijloc;

        if(ismouseclick(WM_LBUTTONDOWN))
        {
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if (!(x>=stanga && x<=stanga+width && y>=sus&&y<=sus+height))
        gata=true;
        else
        {
            linia=(y-sus)/latura+1;
            coloana=(x-stanga)/latura+1;
            if (TablaDeJoc[linia][coloana]==0)
            {

                TablaDeJoc[linia][coloana]=1;
                // stergere
                setcolor(FUNDAL);
                setfillstyle(SOLID_FILL,FUNDAL);
                x1=stanga+latura*(coloana-1);
                y1=sus+latura*(linia-1);
                x2=x1+latura;
                y2=y1+latura;
                xmijloc=(x1+x2)/2;
                ymijloc=(y1+y2)/2;
                bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
                // afisez cerc rosu aprins
                setcolor(LIGHTRED);
                setfillstyle(SOLID_FILL,LIGHTRED);
                fillellipse(xmijloc,ymijloc,18,18);

        }
    else
    if (TablaDeJoc[linia][coloana]==1)
    {
        TablaDeJoc[linia][coloana]=2;
        setcolor(FUNDAL);
        setfillstyle(SOLID_FILL,FUNDAL);
        x1=stanga+latura*(coloana-1);
        y1=sus+latura*(linia-1);
        x2=x1+latura;
        y2=y1+latura;
        xmijloc=(x1+x2)/2;
        ymijloc=(y1+y2)/2;
        bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
        // afisez un patrat galben
        setcolor(LIGHTRED);
        setfillstyle(SOLID_FILL,YELLOW);
        bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
        }
            else // 2-> 0
            {
            TablaDeJoc[linia][coloana]=0;
            setcolor(FUNDAL);
            setfillstyle(SOLID_FILL,FUNDAL);
            x1=stanga+latura*(coloana-1);
            y1=sus+latura*(linia-1);
            x2=x1+latura;
            y2=y1+latura;
            xmijloc=(x1+x2)/2;
            ymijloc=(y1+y2)/2;
            bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);

                }
        afiseazaScor();
            }
        }
    }

    void desen()
    {
        int i,j;
        numar=4;
        width=400;
        height=400;
        latura=width/numar;
        sus=(getmaxy()-width)/2;
        stanga=(getmaxx()-height)/2;
        setbkcolor(FUNDAL); clearviewport(); setcolor(BLUE);
        for(i=1; i<=numar; i++)
        for(j=1; j<=numar; j++)
        rectangle(stanga+latura*(i-1),sus+latura*(j-1),stanga+latura*i,sus+latura*j);
    }

    int main(){
        initwindow(800,600);
        scor=0;
        desen();
        afiseazaScor();
        gata=false;
    do{
    punerePiesa();
    }
    while (!gata);
    getch();
    closegraph();
    return 0;
    }
