#include <iostream>
#include <graphics.h>
#include <winbgim.h>
#include <fstream>

using namespace std;
ifstream fin("pvp.txt");
ofstream fout("pvp.txt",ios_base::app);
ifstream gin("pvc.txt");
ofstream gout("pvc.txt",ios_base::app);

int pozitiex,pozitiey,latime,inaltime,latura,dimensiune,alegere=0;
bool gata;

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
    cout<<midy;

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

void punerePiesa(){
    int linia,coloana,x,y;
    if(ismouseclick(WM_LBUTTONDOWN)){
        clearmouseclick(WM_LBUTTONDOWN);
        x=mousex();
        y=mousey();
        if(!(x>=pozitiex && x<=pozitiex+latime && y>=pozitiey&&y<=pozitiey+inaltime))
            gata=true;
        else{
            linia=(y-pozitiey)/latura+1;
            coloana=(x-pozitiex)/latura+1;
            circle(pozitiex+latura*(coloana-1)+latura/2,pozitiey+latura*(linia-1)+latura/2,10);
        }
    }
}

void tabla(int dimensiune,int latime,int inaltime){
    cleardevice();
    int i,j;

    latura=latime/dimensiune;
    pozitiex=(getmaxx()-inaltime)/2; //pozitionare tabla
    pozitiey=(getmaxy()-inaltime)/2;

    for(i=1;i<=dimensiune;i++)//afisare patratele pe coloane din stanga sus
        for(j=1;j<=dimensiune;j++)
            rectangle(pozitiex+latura*(i-1),pozitiey+latura*(j-1),pozitiex+latura*i,pozitiey+latura*j);

}


void alegeredimensiune(int &dimensiune,int &latime, int&inaltime){
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
            dimensiune=4;
            latime=800;
            inaltime=800;
            break;
        }

        if((x>=midx-200 && x<=midx+200 && y>=250 && y<=330)!=0){
            dimensiune=6;
            latime=800;
            inaltime=800;
            break;
        }

        if((x>=midx-200 && x<=midx+200 && y>=350 && y<=430)!=0){
            dimensiune=8;
            latime=800;
            inaltime=800;
            break;
        }

        }
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

int main(){
    initwindow(getmaxwidth(),getmaxheight());

    meniu(alegere);
    if(alegere==1)
        alegeredimensiune(dimensiune,latime,inaltime);
    if(alegere==2)
        alegeredimensiune(dimensiune,latime,inaltime);

    tabla(dimensiune,latime,inaltime);

    gata=false;
    do{
    punerePiesa();
    }
    while(!gata);

    closegraph();
    return 0;
}
