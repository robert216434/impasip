#include <iostream>
#include <winbgim.h>
#include <stdlib.h>
#include <fstream>

using namespace std;
ifstream fin("pvp.txt");
ofstream fout("pvp.txt",ios_base::app);
ifstream gin("pvc.txt");
ofstream gout("pvc.txt",ios_base::app);

#define MAX 20
#define FUNDAL CYAN
#define SPATIU 0
#define PIESA1 BLUE
#define PIESA2 RED

void iesireUrgenta()
{
   char tasta;
   if (kbhit())
   {
     tasta=getch();
     if (tasta==27)
        {
          closegraph();
         exit(0);
       }
  }
}

int stanga,sus,width,height,latura,numar,alegere;
bool gata;

int TablaDeJoc[MAX][MAX];

void resetarescor(int alegere){
    if(alegere==1){
    fout.close();
    fout.open("pvp.txt");
    fout<<"";
    fout.close();
    fout.open("pvp.txt",ios_base::app);
    }
    if(alegere==2){
    gout.close();
    gout.open("pvc.txt");
    gout<<"";
    gout.close();
    gout.open("pvc.txt",ios_base::app);
    }
}

void adaugarescor(int s1,int s2,int alegere){
    if(alegere==1)
        fout<<s1<<' '<<s2<<endl;
    if(alegere==2)
        gout<<s1<<' '<<s2<<endl;
}

void afisarescor(){
    cleardevice();
    int midx,midy;
    midx=getmaxwidth()/2;
    midy=getmaxheight()/2;

    outtextxy(midx-50,60,"Tabel scor");

    outtextxy(midx-290,130,"Jucator vs Jucator");
    rectangle(midx-350,150,midx-25,700);

    outtextxy(midx+70,130,"Jucator vs Calculator");
    rectangle(midx+25,150,midx+350,700);

    int i=0,j=0,ip,jp,x,y,a1[20][2],a2[20][2];
    char v[50];

    while(fin>>x>>y){
        a1[i][0]=x;
        a1[i][1]=y;
        i++;
        if(i>19) break;
    }
    while(gin>>x>>y){
        a2[j][0]=x;
        a2[j][1]=y;
        j++;
        if(j>19) break;
    }
    i--;j--;
    ip=jp=160;

    while(i>=0){
        if(a1[i][0]>a1[i][1])
        sprintf(v,"Jucatorul 1 a castigat (%d-%d)",a1[i][0],a1[i][1]);
        if(a1[i][0]<a1[i][1])
        sprintf(v,"Jucatorul 2 a castigat (%d-%d)",a1[i][0],a1[i][1]);
        if(a1[i][0]==a1[i][1])
        sprintf(v,"Remiza (%d-%d)",a1[i][0],a1[i][1]);

        outtextxy(midx-345,ip,v);
        i--;
        ip+=20;
    }
    while(j>=0){
        if(a2[j][0]>a2[j][1])
        sprintf(v,"Jucatorul a castigat (%d-%d)",a2[j][0],a2[j][1]);
        if(a2[j][0]<a2[j][1])
        sprintf(v,"Calculatorul a castigat (%d-%d)",a2[j][0],a2[j][1]);
        if(a2[j][0]==a2[j][1])
        sprintf(v,"Remiza (%d-%d)",a2[j][0],a2[j][1]);

        outtextxy(midx+30,jp,v);
        j--;
        jp+=20;
    }

    getch();
}

void stergePiesa(int linia, int coloana)
{
   int x1,y1,x2,y2,xmijloc,ymijloc;
   x1=stanga+latura*(coloana-1);
   y1=sus+latura*(linia-1);
   x2=x1+latura; y2=y1+latura;
   xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
   setcolor(BLUE); rectangle(x1,y1,x2,y2);
   setcolor(FUNDAL); setfillstyle(SOLID_FILL,FUNDAL);
   bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
}

void deseneazaPiesa(int linia, int coloana, int codPiesa)
{
   int x1,y1,x2,y2,xmijloc,ymijloc;
   x1=stanga+latura*(coloana-1);
   y1=sus+latura*(linia-1);
   x2=x1+latura; y2=y1+latura;
   xmijloc=(x1+x2)/2; ymijloc=(y1+y2)/2;
   setcolor(BLUE);
   rectangle(x1,y1,x2,y2); setcolor(FUNDAL);
   setfillstyle(SOLID_FILL,FUNDAL);
   bar(xmijloc-20,ymijloc-20,xmijloc+20,ymijloc+20);
   setcolor(codPiesa);
   setfillstyle(SOLID_FILL,codPiesa);
   fillellipse(xmijloc,ymijloc,18,15);
}

bool inInterior(int x, int y, int x1, int y1, int x2, int y2)
{
   return x1<=x && x<=x2 && y1<=y && y<=y2;
}

void mutarePiesa(int codPiesa)
{
   int linia1,coloana1,linia2,coloana2,x,y;
   int x1, y1, x2, y2;
   int xmijloc, ymijloc;
   bool mutareCorecta;
  do
   {
   iesireUrgenta();
   mutareCorecta=false;
   if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
   {
     clearmouseclick(WM_LBUTTONDOWN);
     // x=mousex(); y=mousey();
    linia1=(y-sus)/latura+1;
    coloana1=(x-stanga)/latura+1;
    // cout<<linia1<<","<<coloana1<<"=>";
    //circle(stanga+coloana1*latura+latura/2, sus+linia1*latura+latura/2,5);
    if (TablaDeJoc[linia1][coloana1]==codPiesa)
    {
      do
      {
        iesireUrgenta();
        if(ismouseclick(WM_LBUTTONDOWN) && inInterior(x=mousex(),y=mousey(),stanga,sus,stanga+width,sus+height))
        {
          clearmouseclick(WM_LBUTTONDOWN);
          // x=mousex(); y=mousey();
          linia2=(y-sus)/latura+1;
          coloana2=(x-stanga)/latura+1;
          // cout<<linia2<<","<<coloana2<<endl;
          if (TablaDeJoc[linia2][coloana2]==SPATIU)
          {
            mutareCorecta=true;
            TablaDeJoc[linia1][coloana1]=SPATIU;
            TablaDeJoc[linia2][coloana2]=codPiesa;
            stergePiesa(linia1,coloana1);
            deseneazaPiesa(linia2,coloana2,codPiesa);
          }
        }
      }
      while (!mutareCorecta);
    }
  }
 }
 while (!mutareCorecta);
}


void initTabla()
{
    cleardevice();
    //numar=numar/2;
 int linia, coloana;
 for (linia=1; linia<=numar; linia++)
     for (coloana=1; coloana<=numar; coloana++)
         if (rand()%4<2)
            TablaDeJoc[linia][coloana]=PIESA1;
         else
         if (rand()%4<3)
            TablaDeJoc[linia][coloana]=PIESA2;
         else
            TablaDeJoc[linia][coloana]=SPATIU;
}

void desenTabla()
{
   setbkcolor(FUNDAL); cleardevice();
   int linia,coloana;
   for (linia=1; linia<=numar; linia++)
   for (coloana=1; coloana<=numar; coloana++)
       {
         if (TablaDeJoc[linia][coloana]==SPATIU)
            stergePiesa(linia,coloana);
         else
            deseneazaPiesa(linia,coloana,TablaDeJoc[linia][coloana]);
       }
}

void initializariDimensiuni()
{
    numar=0;
   cleardevice();
    int midx,midy;
    midx=getmaxwidth()/2;
    midy=getmaxheight()/2;

    outtextxy(midx-170,70,"Alege dimensiunea tablei de joc");

    rectangle(midx-200,150,midx+200,230);
    outtextxy(midx-15,(150+230)/2-10,"4x4");

    rectangle(midx-200,250,midx+200,330);
    outtextxy(midx-15,(250+330)/2-10,"6x6");

    rectangle(midx-200,350,midx+200,430);
    outtextxy(midx-15,(350+430)/2-10,"8x8");

    int x,y;
    while(true){
    if(ismouseclick(WM_LBUTTONDOWN)!=0){
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();

        if((x>=midx-200 && x<=midx+200 && y>=150 && y<=230)!=0){
            numar=4;
            width=400;
            height=400;
        }

        if((x>=midx-200 && x<=midx+200 && y>=250 && y<=330)!=0){
            numar=6;
            width=600;
            height=600;
        }

        if((x>=midx-200 && x<=midx+200 && y>=350 && y<=430)!=0){
            numar=8;
            width=800;
            height=800;
        }
        latura=width/numar;
        sus=(getmaxy()-width)/2;
        stanga=(getmaxx()-height)/2;
    }
    if(numar!=0)
    break;
    }
}

void meniu(int &alegere){

    int midx,midy;
    midx=getmaxwidth()/2;
    midy=getmaxheight()/2;

    settextstyle(BOLD_FONT,HORIZ_DIR,1);
    outtextxy(midx-20,70,"Impas");

    rectangle(midx-200,150,midx+200,230);
    outtextxy(midx-100,(150+230)/2-10,"Jucator vs Jucator");

    rectangle(midx-200,250,midx+200,330);
    outtextxy(midx-100,(250+330)/2-10,"Jucator vs Calculator");

    rectangle(midx-200,350,midx+200,430);
    outtextxy(midx-25,(350+430)/2-10,"Scor");

    rectangle(midx-200,450,midx+200,530);
    outtextxy(midx-35,(450+530)/2-10,"Iesire");

    int x,y;
    while(true){
    if(ismouseclick(WM_LBUTTONDOWN)!=0){
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();

        if((x>=midx-200 && x<=midx+200 && y>=150 && y<=230)!=0){//optiuni meniu
            alegere=1;
            break;
        }

        if((x>=midx-200 && x<=midx+200 && y>=250 && y<=330)!=0){
            alegere=2;
            break;
        }

        if((x>=midx-200 && x<=midx+200 && y>=350 && y<=430)!=0){
            afisarescor();
            break;
        }

        if((x>=midx-200 && x<=midx+200 && y>=450 && y<=530)!=0){
            closegraph();
            break;
        }
        }
    }
}

int main()
{
  initwindow(getmaxwidth(),getmaxheight());
  meniu(alegere);
  if(alegere==1){
    initializariDimensiuni();
  initTabla();
  desenTabla();
  do {
       mutarePiesa(PIESA1);
       mutarePiesa(PIESA2);
  } while (true);
  }
  if(alegere==2){
    initializariDimensiuni();
    initTabla();
    desenTabla();
    getch();
  }
  return 0;
}
