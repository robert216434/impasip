#include <iostream>
#include <graphics.h>
#include <winbgim.h>

void meniu(){
    int pozx,pozy;
    pozx = getmaxwidth() / 2;
    pozy = getmaxheight() / 2;
    outtextxy(pozx-50,pozy/6,"Impas");



    getch();
    cleardevice();

}

void tabla(int dimensiune,int latime,int inaltime){
    int i,j,pozitiex,pozitiey,latura;

    latura=latime/dimensiune;
    pozitiex=(getmaxx()-inaltime)/2; //pozitionare patratel
    pozitiey=(getmaxy()-inaltime)/2;

    for(i=1;i<=dimensiune;i++)//afisare tabla pe coloane din stanga sus
        for(j=1;j<=dimensiune;j++)
            rectangle(pozitiex+latura*(i-1),pozitiey+latura*(j-1),pozitiex+latura*i,pozitiey+latura*j);
}

int main(){
    int dimensiune,latime,inaltime;
    initwindow(1915,1010);

    meniu();

    tabla(dimensiune=8,latime=800,inaltime=800);
    //6,800,800
    getch();
    closegraph();
    return 0;
}
