#ifndef STRUCTURI_H_INCLUDED
#define STRUCTURI_H_INCLUDED

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <graphics.h>
#include <winbgim.h>
#include <windows.h>
#include "Legaturi.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
using namespace std;
#define MAX1 20
#define MAX2 60
#define MAX3 80
struct DescrierePiesa
{
    char comanda[MAX1];
    unsigned nComenzi;
    float x1[MAX1], y1[MAX1], x2[MAX1], y2[MAX1];
};
struct PunctLegatura
{
    int id;
    float x, y;
};
struct Piesa
{
    unsigned id;
    char nume[MAX3];
    char rezistenta[MAX3]= {'0'};
    char voltaj[MAX3]= {'0'};
    int x,y;
    int orientare=0;
    int numarOrdine;
    int culoare;
    char continut[MAX2];
    unsigned nrLegaturi;
    PunctLegatura pLeg[4];
    PunctLegatura pLe[4];
    int puncte[4];
    int modLeg[4];
    DescrierePiesa descriere;
    int zoom;
};
struct Legatura
{
    int nod1, nod2; // cele doua piese ce se leaga
    int punct1, punct2;
    int modLeg;
};
struct Schema
{
    Piesa Meniu[MAX1];
    Piesa Piese[MAX2];
    int nrPieseMeniu=13;
    int nrPiese=0;
    unsigned nrPiesaAleasa;
    Legatura vecLegaturi[MAX2];
    int nrLegaturi=0;
    int indiceLegatura=0;
    char fisiere[MAX3][MAX3];
    int nrFisiere=-1;
    char numeFisier[MAX3];
    int xIntrerupator;
    int yIntrerupator;
    int culoare=15;
    int k=1;
};
void piesaDinFisier(Piesa& P,Schema &Electron)
{
    char numeFisier[MAX1],s[MAX1];
    strcpy(numeFisier,"PieseMeniu");
    strcat(numeFisier,"\\\\");
    strcat(numeFisier,P.nume);
    strcat(numeFisier,".ps");
    FILE* f=fopen(numeFisier,"rt");
    fscanf(f,"%s",&P.nume);//NUME
    fscanf(f,"%d",&P.zoom);
    fscanf(f,"%d",&P.numarOrdine);
    fscanf(f,"%d",&P.nrLegaturi);
    fscanf(f,"%d",&P.culoare);
    for (unsigned i=1; i<=P.nrLegaturi; i++)
    {
        fscanf(f,"%f%f",&P.pLe[i].x,&P.pLe[i].y);
    }
    fscanf(f,"%d\n",&P.orientare);
    fscanf(f,"%d\n",&P.descriere.nComenzi);//Cate operatii trebuie sa faca pentru a desena
    for(int i=1; i<=P.descriere.nComenzi; i++)
    {
        fscanf(f,"%c%f%f%f%f\n",&P.descriere.comanda[i],&P.descriere.x1[i],&P.descriere.y1[i],&P.descriere.x2[i],&P.descriere.y2[i]);
    }
    fclose(f);
}
void roteste (float x, float y, float & xnou, float & ynou)
{
    xnou = y;
    ynou = -x;
}
void deseneazaLinie(Piesa &P,int i)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descriere.x1[i];
    y1=P.descriere.y1[i];
    x2=P.descriere.x2[i];
    y2=P.descriere.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        roteste(x2,y2,x_2,y_2);
        break;
    }
    line(P.x+P.zoom*x_1,P.y+P.zoom*y_1,P.x+P.zoom*x_2,P.y+P.zoom*y_2);
}
void deseneazaCerc(Piesa &P, unsigned i)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descriere.x1[i];
    y1=P.descriere.y1[i];
    x2=P.descriere.x2[i];
    y2=P.descriere.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        x_2=x2;
        y_2=x2;
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        x_2=x2;
        y_2=x2;
    }
    circle(P.x+P.zoom*x_1,P.y+P.zoom*y_1,x_2+P.zoom);
}
void deseneazaLeg(Piesa &P, unsigned i,int k)
{
    float x_1,y_1,x_2,y_2;
    float x1,y1,x2,y2;
    x1=P.descriere.x1[i];
    y1=P.descriere.y1[i];
    x2=P.descriere.x2[i];
    y2=P.descriere.y2[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        x_2=y2+3;
        y_2=x2;
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        x_2=y2+3;
        y_2=x2;
        break;
    }
    circle(P.x+P.zoom*x_1,P.y+P.zoom*y_1,P.zoom*x_2/10);
    P.pLeg[k].x=P.x+x_1*P.zoom;
    P.pLeg[k].y=P.y+y_1*P.zoom;
}
void colorareNod(Piesa &P, unsigned i, int culoare)
{
    float x1,y1,x2,y2;
    float x_1,y_1,x_2,y_2;
    x1=P.descriere.x1[i];
    y1=P.descriere.y1[i];
    switch (P.orientare)
    {
    case 0:
        x_1=x1;
        y_1=y1;
        x_2=x2;
        y_2=y2;
        break;
    case 1:
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        break;
    case 2:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        x_1=x1;
        y_1=y1;
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        x_2=x2;
        y_2=y2;
        break;
    case 3:
        roteste(x1,y1,x_1,y_1);
        roteste(x_1,y_1,x1,y1);
        roteste(x1,y1,x_1,y_1);
        roteste(x2,y2,x_2,y_2);
        roteste(x_2,y_2,x2,y2);
        roteste(x2,y2,x_2,y_2);
        break;
    }
    circle(P.x+x_1*P.zoom,P.y+y_1*P.zoom,x_2);
    setfillstyle(SOLID_FILL, culoare);
    floodfill(P.x+x_1*P.zoom,P.y+y_1*P.zoom, culoare);
}
//-------------------------------------------------------------------------------------------------------------------------------------------
void bec(int x,int y)
{
    setcolor(CYAN);
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    circle(x+70,y,13);
    line(x+84,y,x+99,y);
    line( x+70, y, x+78, y+10);
    line( x+70, y, x+78, y-10);
    line(x+78, y-10, x+60, y+9);
    line(x+78, y+10, x+61, y-10);
    circle(x+103,y,3);
}
void ampermetru(int x, int y)
{
    setcolor(CYAN);
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    circle(x+70,y,13);
    line(x+84,y,x+99,y);
    circle(x+103,y,3);
    line(x+70, y-12,x+63, y+9 );
    line(x+70, y-12, x+77, y+9);
    line(x+67, y, x+74, y);
}
void voltmetru(int x, int y)
{
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    circle(x+70,y,13);
    line(x+84,y,x+99,y);
    circle(x+103,y,3);
    line(x+61, y-10, x+70, y+12);
    line(x+78, y-10, x+70, y+12);
}
void condensator(int x, int y)
{
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    line(x+60,y,x+75,y);
    circle(x+77,y,3);
    line (x+55,y-10, x+55, y+10);
    line(x+60,y-10, x+60, y+10);
}
void rezistor(int x, int y)
{
    setcolor(CYAN);
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    line(x+84,y,x+99,y);
    circle(x+103,y,3);
    line(x+55,y-5, x+55, y+5);
    line(x+84, y-5, x+84, y+5);
    line(x+55,y-5,x+84, y-5);
    line(x+55, y+5, x+84, y+5);
}
void generator(int x,int y)
{
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    line(x+60,y,x+75,y);
    circle(x+77,y,3);
    line (x+55,y-5, x+55, y+5);
    line(x+60,y-10, x+60, y+10);
}
void Siguranta(int x,int y)
{
    setcolor(CYAN);
    circle(x+37,y,3);
    line(x+40,y,x+55,y);
    line(x+84,y,x+99,y);
    circle(x+103,y,3);
    line(x+55,y-5, x+55, y+5);
    line(x+84, y-5, x+84, y+5);
    line(x+55,y-5,x+84, y-5);
    line(x+55, y+5, x+84, y+5);
    line(x+55,y,x+84,y);
}
void rezistor_i(int x, int y)
{
    setcolor(CYAN);
    rectangle(x,y,x+10, y+30);
    line(x+5, y-10,x+5,y);
    line(x+5, y+30, x+5, y+40);
    circle(x+5, y+41, 3);
    circle(x+5, y-12,3);
}
void polariz(int x, int y)
{
    circle(x+39,y,3);
    line(x+43,y,x+58,y);
    line(x+74,y,x+89,y);
    circle(x+93,y,3);
    line(x+60, y-5, x+60, y+5);
    line(x+65, y-10, x+66, y+10);
    line(x+70, y-5, x+70, y+5);
    line(x+75, y-10, x+75, y+10);
}
void nod (int x,int y)
{
    circle(x,y,10);
    setfillstyle(SOLID_FILL, CYAN);
    floodfill(x,y, CYAN);
}
void numarPieseEcran(Schema &Electron)
{
    char s[101];
    setcolor(Electron.culoare);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1630,100,"Piese pe ecran:");
    int numar=sprintf(s,"%d",Electron.nrPiese);
    outtextxy(1850,100,s);
}
void linii1()
{
    int i;
    for(i=1; i<=277; i++)
    {
        setcolor(YELLOW);
        circle(237, 500+i,1);
        delay(1);
    }
    for(i=1; i<=250; i++)
    {
        setcolor(YELLOW);
        circle(237+i, 777,1);
        delay(1);
    }
    for(i=1; i<=100; i++)
    {
        setcolor(YELLOW);
        circle(303, 500-i,1);
        delay(1);
    }
    for(i=1; i<=30; i++)
    {
        setcolor(YELLOW);
        circle(303+i,400,1);
        delay(0.7);
    }
    for(i=1; i<=100; i++)
    {
        setcolor(YELLOW);
        circle(403,400+i,1);
        delay(1);
    }
    for(i=1; i<=230; i++)
    {
        setcolor(YELLOW);
        circle(403+i,500,1);
        delay(1);
    }
    for(i=1; i<=110; i++)
    {
        setcolor(YELLOW);
        circle(558,777+i,1);
        delay(1);
    }
    for(i=1; i<=180; i++)
    {
        setcolor(YELLOW);
        circle(558+i, 888,1);
        delay(1);
    }
    for(i=1; i<=250; i++)
    {
        setcolor(YELLOW);
        circle(703, 500-i, 1);
        delay(1);
    }
    for(i=1; i<=130; i++)
    {
        setcolor(YELLOW);
        circle(703+i, 250, 1);
        delay(1);
    }
    for(i=1; i<=215; i++)
    {
        setcolor(YELLOW);
        circle(877, 252+i, 1);
        delay(1);
    }
    for(i=1; i<=155; i++)
    {
        setcolor(YELLOW);
        circle(877+i,  468,1);
        delay(1);
    }
    for(i=1; i<=30; i++)
    {
        setcolor(YELLOW);
        circle(1103, 468+i, 1);
        delay(1);
    }
    for(i=1; i<=290; i++)
    {
        setcolor(YELLOW);
        circle(1103+i, 500, 1);
        delay(1);
    }
    for(i=1; i<=180; i++)
    {
        setcolor(YELLOW);
        circle(1400,510+i,  1);
        delay(1);
    }
    for(i=1; i<=105; i++)
    {
        setcolor(YELLOW);
        circle(1400-i, 689, 1);
        delay(1);
    }
    for(i=1; i<=200; i++)
    {
        setcolor(YELLOW);
        circle(1237, 689+i, 1);
        delay(1);
    }
    for(i=1; i<=460; i++)
    {
        setcolor(YELLOW);
        circle(1237-i, 888, 1);
        delay(1);
    }
}
void linii2()
{
    int i;
    for(i=1; i<=35; i++)
    {
        setcolor(YELLOW);
        circle(335-i,300,1);
        delay(1);
    }
    for(i=1; i<=190; i++)
    {
        setcolor(YELLOW);
        circle(300,300+i, 1);
        delay(1);
    }
    for(i=1; i<=230; i++)
    {
        setcolor(YELLOW);
        circle(405+i, 300, 1);
        delay(1);
    }
    for(i=1; i<=230; i++)
    {
        setcolor(YELLOW);
        circle(705+i, 300, 1);
        delay(1);
    }
    for(i=1; i<=230; i++)
    {
        setcolor(YELLOW);
        circle(1003+i, 300, 1);
        delay(1);
    }
    for(i=1; i<=400; i++)
    {
        setcolor(YELLOW);
        circle(1305, 300+i, 1);
        delay(1);
    }
    for(i=1; i<=335; i++)
    {
        setcolor(YELLOW);
        circle(1243-i, 700, 1);
        delay(1);
    }
    for(i=1; i<=200; i++)
    {
        setcolor(YELLOW);
        circle(835-i, 700, 1);
        delay(1);
    }
}
void piese_circuit(int x, int y, Schema &Electron)
{
    int i;
    if(Electron.k==1)
    {
        rezistor(x, y-100);
        delay(1000);
        nod(x,y+100);
        delay(1000);
        ampermetru(x+300, y-100);
        delay(1000);
        bec(x+600,y-100);
        delay(1000);
        Siguranta(x+500, y+300);
        delay(1000);
        condensator(x+250, y+300);
        delay(1000);
        voltmetru(x+900, y-100);
        delay(1000);
        polariz(x+907, y+300);
        delay(1000);
        linii2();
        delay(100);
        bec(x-33, y+300);
        for(i=1; i<=210; i++)
        {
            setcolor(YELLOW);
            circle(587-i, 700, 1);
            delay(1);
        }
        for(i=1; i<=190; i++)
        {
            setcolor(YELLOW);
            circle(300, 700-i,1);
            delay(1);
        }
    setcolor(Electron.culoare);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1630,100,"Piese pe ecran:");
    outtextxy(1850,100,"9");
    }
    if(Electron.k==2)
    {
        bec(x,y);
        delay(1000);
        ampermetru(x-100,y+100);
        delay(1000);
        voltmetru(x+300, y+100);
        delay(1000);
        condensator(x+500, y-150);
        delay(1000);
        rezistor(x+700, y+68);
        delay(1000);
        generator(x+400, y+488);
        delay(1000);
        Siguranta(x+155, y+377);
        delay(1000);
        nod(x+1100,y+100);
        delay(1000);
        polariz(x+900, y+289);
        delay(1000);
        linii1();
        setcolor(Electron.culoare);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1630,100,"Piese pe ecran:");
    outtextxy(1850,100,"9");
    }
    else if(Electron.k==3)
    {
        Siguranta(x, y-100);
        delay(1000);
        nod(x,y+100);
        delay(1000);
        bec(x+300, y-100);
        delay(1000);
        voltmetru(x+600,y-100);
        delay(1000);
        Siguranta(x+500, y+300);
        delay(1000);
        condensator(x+250, y+300);
        delay(1000);
        rezistor(x+900, y-100);
        delay(1000);
        polariz(x+907, y+300);
        linii2();
        delay(100);
        ampermetru(x-33, y+300);
        for(i=1; i<=210; i++)
        {
            setcolor(YELLOW);
            circle(587-i, 700, 1);
            delay(1);
        }
        for(i=1; i<=190; i++)
        {
            setcolor(YELLOW);
            circle(300, 700-i,1);
            delay(1);
        }
        bec(x+300, y+100);
        delay(1000);
        bec(x+600, y+100);
        delay(1000);
        delay(1000);
        for(i=1; i<=330; i++)
        {
            setcolor(YELLOW);
            circle(310+i, 500, 1);
            delay(1);
        }
        for(i=1; i<=230; i++)
        {
            setcolor(YELLOW);
            circle(700+i, 500, 1);
            delay(1);
        }
        for(i=1; i<=300; i++)
        {
            setcolor(YELLOW);
            circle(1005+i, 500, 1);
            delay(1);
        }
        setcolor(Electron.culoare);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1630,100,"Piese pe ecran:");
    outtextxy(1850,100,"10");
    }
    else if (Electron.k==4)
    {
        Siguranta(x,y);
        delay(1000);
        nod(x+1100,y+100);
        delay(1000);
        ampermetru(x-100,y+100);
        delay(1000);
        voltmetru(x+300, y+100);
        delay(1000);
        condensator(x+500, y-150);
        delay(1000);
        rezistor(x+700, y+68);
        delay(1000);
        generator(x+400, y+488);
        delay(1000);
        Siguranta(x+155, y+377);
        delay(1000);
        polariz(x+900, y+289);
        delay(1000);
        linii1();
        setcolor(Electron.culoare);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1630,100,"Piese pe ecran:");
    outtextxy(1850,100,"9");
        Electron.k=1;
    }
}
unsigned _circuit(Schema &Electron)
{
    piese_circuit(300,400,Electron);
    Electron.k++;
    rectangle(50,1,280,40);
    setcolor(WHITE);
}
unsigned clear_( Schema & Electron, int &x, int &y)
{
    bool click=false;
    unsigned i, nrPiesaAleasa=0;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();

            if ((xMouse < 215) && (yMouse < 84 ) && abs( 215 - xMouse)<=100 && abs(84 - yMouse)<=39)
            {
                rectangle( 115,45,215,84);
                click=true;
                setcolor(Electron.culoare);
                rectangle(150,140,1740, 970);
                setfillstyle(SOLID_FILL,BLACK);
                bar(151,141,1739,969);

            }
            Electron.nrPiese=0;
            Electron.nrLegaturi=0;
            Electron.indiceLegatura=0;
            setfillstyle(SOLID_FILL,BLACK);
            bar(1630,80,1900,130);
            numarPieseEcran(Electron);

        }
    while (!click);
}
void mutaPiesa(Piesa vectorPiese[MAX2], unsigned PiesaAleasa);
void deseneaza(Piesa &P, int culoare)
{
    setcolor(culoare);
    int k=0;
    for (unsigned i=1; i<=P.descriere.nComenzi; i++)
    {
        switch(P.descriere.comanda[i])
        {
        case 'L':
            deseneazaLinie(P,i);
            break;
        case 'C':
            deseneazaCerc(P,i);
            break;
        case 'S':
            deseneazaLeg(P,i,k);
            k++;
            break;
        case 'N':
            colorareNod(P,i,culoare);
            break;
        }
    }
}
void amplaseaza(Piesa& P, unsigned x, unsigned y,int culoare)
{
    P.x=x;//40
    P.y=y;//90
    deseneaza(P, culoare);
}
void amplaseazaGalben(Piesa& P, unsigned x, unsigned y)
{
    P.x=x;//40
    P.y=y;//90
    deseneaza(P, YELLOW);
}
void colorareNegru(Piesa& P, unsigned x, unsigned y)
{
    P.x=x;//40
    P.y=y;//90
    deseneaza(P, BLACK);
}

void Rotire (Piesa &P,int x, int y)
{
    colorareNegru(P,x,y);
    float xnou,ynou;
    xnou = y;
    ynou = x;
    amplaseaza(P,xnou,ynou,P.culoare);
};
void colorareDreptunghi(Piesa& P, unsigned x, unsigned y,int cul)
{
    P.x=x;
    P.y=y;
    setcolor(cul);
    rectangle(P.x-P.zoom*4,P.y-P.zoom*4,P.x+P.zoom*4,P.y+P.zoom*4);
}
void deseneazaLiniiMeniu(int x, int y,Schema &Electron)
{
    setcolor(Electron.culoare);
    for(int i=250; i<=900; i=i+150)
        line(x+60,i,y+150,i);
}
void deseneazaChenarCuloare(Schema &Electron,int x,int y)
{
    int k=0;
    setcolor(Electron.culoare);
    rectangle(x,y,x+200,y+80);
    line(x+50,y,x+50,y+80);
    line(x+100,y,x+100,y+80);
    line(x+150,y,x+150,y+80);
    line(x,y+20,x+200,y+20);
    line(x,y+40,x+200,y+40);
    line(x,y+60,x+200,y+60);
    for(int j=0; j<=3; j++)
    {
        setfillstyle(SOLID_FILL,j);
        bar(x+1+50*k,y+1,x+49+50*k,y+19);
        k++;
    }
    k=0;
    for(int j=4; j<=7; j++)
    {
        setfillstyle(SOLID_FILL,j);
        bar(x+1+50*k,y+21,x+49+50*k,y+39);
        k++;
    }
    k=0;
    for(int j=8; j<=11; j++)
    {
        setfillstyle(SOLID_FILL,j);
        bar(x+1+50*k,y+41,x+49+50*k,y+59);
        k++;
    }
    k=0;
    for(int j=12; j<=15; j++)
    {
        setfillstyle(SOLID_FILL,j);
        bar(x+1+50*k,y+61,x+49+50*k,y+79);
        k++;
    }
}
void deseneazaProiect(Schema &Electron)
{
    setcolor(Electron.culoare);
    rectangle(60,140,150,970);
    rectangle( 1740, 140, 1830, 970);
    deseneazaLiniiMeniu(0,0,Electron);
    line( 70,140, 1750, 140);
    line( 150,970,1830,970);
    deseneazaLiniiMeniu(1680,1680,Electron);
    setcolor(Electron.culoare);
    strcpy(Electron.Meniu[1].nume,"DIODA");
    strcpy(Electron.Meniu[2].nume,"CONDENSATOR");
    strcpy(Electron.Meniu[3].nume,"REZISTOR");
    strcpy(Electron.Meniu[4].nume,"BEC");
    strcpy(Electron.Meniu[5].nume,"AMPERMETRU");
    strcpy(Electron.Meniu[6].nume,"VOLTMETRU");
    strcpy(Electron.Meniu[7].nume,"SIGURANTA");
    strcpy(Electron.Meniu[8].nume,"GENERATOR");
    strcpy(Electron.Meniu[9].nume,"POLARIZ");
    strcpy(Electron.Meniu[10].nume,"TRANZPNP");
    strcpy(Electron.Meniu[11].nume,"TRANZNPN");
    strcpy(Electron.Meniu[12].nume,"INTRERUPATOR_DESCHIS");
    strcpy(Electron.Meniu[13].nume,"INTRERUPATOR_INCHIS");
    int lat=getmaxx()/(Electron.nrPieseMeniu);
    for (unsigned i=1; i<=Electron.nrPieseMeniu/2; i++)
    {
        piesaDinFisier(Electron.Meniu[i],Electron);
        if(i==1)
            amplaseaza(Electron.Meniu[i],lat-40,(i*170),Electron.Meniu[i].culoare);
        else amplaseaza(Electron.Meniu[i],lat-40,(i*150),Electron.Meniu[i].culoare);
    }
    int k=0;
    for(unsigned i=Electron.nrPieseMeniu/2+1; i<=Electron.nrPieseMeniu; i++)
    {
        k++;
        piesaDinFisier(Electron.Meniu[i],Electron);
        if(k==1)
            amplaseaza(Electron.Meniu[i],lat+1640, (k*170),Electron.Meniu[i].culoare);
        else if(k==6)
        {
            amplaseaza(Electron.Meniu[i], lat+1640, (k*150),Electron.Meniu[i].culoare);
        }
        else amplaseaza(Electron.Meniu[i], lat+1640, (k*150),Electron.Meniu[i].culoare);
    }
    colorareNegru(Electron.Meniu[13],Electron.Meniu[13].x,Electron.Meniu[13].y);
}
/*---------------------------------------------------------------------------------Alege piese din meniu------------------------------------------------*/
void coordonate(int &x,int &y)
{
    bool click=false;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            click=true;
        }
    while (!click);
    x=xMouse;
    y=yMouse;
}
unsigned alegePiesaMeniu(Schema &Electron,int &x,int &y,bool &ok)
{
    bool click=false;
    unsigned i, nrPiesaAleasa=0;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPieseMeniu; i++)
                if (abs(Electron.Meniu[i].x - xMouse)<=10 && abs(Electron.Meniu[i].y - yMouse)<=10)
                {
                    nrPiesaAleasa=i;
                    click=true;
                }
            if ((xMouse < 900) && (yMouse < 40 ) &&abs( 900 - xMouse)<=200 && abs(40 - yMouse)<=40)
            {
                x=xMouse;
                y=yMouse;
                rectangle(700,1,900,40);
                setcolor(Electron.culoare);
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void amplaseazaPiesa(Piesa& P)
{
    bool click=false;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            amplaseaza(P,xMouse,yMouse,P.culoare);
            click=true;
        }
    while (!click);
}
void IaPiesaDinMeniu(Schema &Electron)
{
    unsigned PiesaAleasa,nrPiesaAleasa;
    bool ok=1;
    int i;
    do
    {
        int xMouse,yMouse;
        PiesaAleasa=alegePiesaMeniu(Electron,xMouse,yMouse,ok);
        if ((xMouse < 900) && (yMouse < 40 ) &&abs( 900 - xMouse)<=200 && abs(40 - yMouse)<=40)
        {
            ok=0;
            setcolor(Electron.culoare);
            rectangle(700,1,900,40);
        }
        else
        {
            Electron.nrPiese++;
            Electron.Piese[Electron.nrPiese]=Electron.Meniu[PiesaAleasa];
            Electron.Piese[Electron.nrPiese].id=Electron.nrPiese;
            for(i=0; i<Electron.Piese[Electron.nrPiese].nrLegaturi; i++)
                Electron.Piese[Electron.nrPiese].puncte[i]=0;
            amplaseazaPiesa(Electron.Piese[Electron.nrPiese]);
            numarPieseEcran(Electron);
        }
    }
    while(ok==1);
}
/*--------------------------------------------------------------Muta piesele pe ecran----------------------------------------------------------------------*/
unsigned  alegePiesaPusa(Schema &Electron,int &x,int&y)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if ((xMouse < 1040) && (yMouse < 40 ) &&abs( 1040 - xMouse)<=130 && abs(40 - yMouse)<=40)
            {
                x=xMouse;
                y=yMouse;
                rectangle(900,1,1040,40);
                setcolor(Electron.culoare);
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void schimbaPozPiesaPusa(Piesa& P,int modLeg)
{
    bool click=false;
    int xMouse,yMouse;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            if(xMouse <1720 && xMouse >180 && yMouse>150 && yMouse<960)
            {
                colorareDreptunghi(P,P.x,P.y,0);
                colorareNegru(P,P.x,P.y);
                amplaseaza(P,xMouse,yMouse,P.culoare);
            }
            else
            {
                colorareDreptunghi(P,P.x,P.y,0);
                amplaseaza(P,P.x,P.y,P.culoare);
                showerrorbox("Piesa depaseste zona de desenare!");
            }
            click=true;
        }
    while (!click);
}
/*-----------------------------------------------------------------------INVERSEAZA-LEGATURI------------------------------------------------------*/
void drawLine(int x1, int y1, int x2, int y2, int cul,int modLeg);
void  redeseneazaLegaturi(Schema &Electron);
unsigned  alegePiesaInversare(Schema &Electron,int &x,int&y)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if(xMouse>1730  && xMouse<1860  && yMouse>1 && yMouse<40)
            {
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void alegeLegaturaInversare(Schema &Electron,int PiesaAleasa)
{
    int i,j,v,a,ok=1,x,y;
    while(1 && ok==1)
    {
        coordonate(x,y);
        if(x>1730  && x<1860  && y>1 && y<40)
            ok=0;
        else
            for(i=0; i<Electron.Piese[PiesaAleasa].nrLegaturi; i++)
            {
                if (abs(Electron.Piese[PiesaAleasa].pLeg[i].x - x)<=5 && abs(Electron.Piese[PiesaAleasa].pLeg[i].y - y)<=5)
                    for(j=1; j<=Electron.nrPiese; j++)
                    {
                        for(a=0; a<Electron.Piese[j].nrLegaturi; a++)
                            if(abs(Electron.Piese[PiesaAleasa].puncte[i])==abs(Electron.Piese[j].puncte[a]) && PiesaAleasa!=j)
                            {
                                if(Electron.Piese[PiesaAleasa].puncte[i]>0)
                                {
                                    drawLine(Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,0,Electron.Piese[PiesaAleasa].modLeg[i]);
                                    drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,14,Electron.Piese[j].modLeg[a]);                                    //Electron.Piese[PiesaAleasa].puncte[i]=0;
                                    Electron.Piese[j].puncte[a]=Electron.Piese[PiesaAleasa].puncte[i];
                                    Electron.Piese[PiesaAleasa].puncte[i]=-Electron.Piese[j].puncte[a];
                                }
                                else if(Electron.Piese[j].puncte[a]>0)
                                {
                                    drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,0,Electron.Piese[j].modLeg[a]);
                                    drawLine(Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,14,Electron.Piese[PiesaAleasa].modLeg[i]);
                                    Electron.Piese[PiesaAleasa].puncte[i]=Electron.Piese[j].puncte[a];
                                    Electron.Piese[j].puncte[a]=-Electron.Piese[PiesaAleasa].puncte[i];
                                }
                            }
                    }
                else if(x>1730  && x<1860  && y>1 && y<40)
                {
                    ok=0;
                }
            }
    }
}
void inverseazaLegaturi(Schema &Electron)
{
    int ok=1,xMouse,yMouse,PiesaAleasa,x,y;
    coordonate(xMouse,yMouse);
    while(1 && ok==1)
    {
        PiesaAleasa=alegePiesaInversare(Electron,xMouse,yMouse);
        if(PiesaAleasa!=0)
        {
            alegeLegaturaInversare(Electron,PiesaAleasa);
            setcolor(BLACK);
            rectangle(Electron.Piese[PiesaAleasa].x-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].x+Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y+Electron.Piese[PiesaAleasa].zoom*4);
        }
        else
        {
            ok=0;
        }
    }
    colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
    redeseneazaLegaturi(Electron);
    for(int i=1; i<=Electron.nrPiese; i++)
        amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
}
/*-----------------------------------------------------------------------LEGATURI------------------------------------------------------*/
void drawLine(int x1, int y1, int x2, int y2, int cul,int modLeg);
void mutaLegaturi(Schema &Electron,int PiesaAleasa)
{
    int i,j,v,a;
    for(i=0; i<Electron.Piese[PiesaAleasa].nrLegaturi; i++)
    {
        if(Electron.Piese[PiesaAleasa].puncte[i]!=0)
            for(j=1; j<=Electron.nrPiese; j++)
            {
                for(a=0; a<Electron.Piese[j].nrLegaturi; a++)
                    if(abs(Electron.Piese[PiesaAleasa].puncte[i])==abs(Electron.Piese[j].puncte[a]) && PiesaAleasa!=j)
                    {

                        if(Electron.Piese[PiesaAleasa].puncte[i]>0)
                            drawLine(Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,0,Electron.Piese[PiesaAleasa].modLeg[i]);
                        if(Electron.Piese[j].puncte[a]>0)
                            drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,0,Electron.Piese[j].modLeg[a]);
                    }
            }
    }
}
void refaLegatura(Schema &Electron,int PiesaAleasa)
{
    int i,j,v,a;
    for(i=0; i<Electron.Piese[PiesaAleasa].nrLegaturi; i++)
    {
        if(Electron.Piese[PiesaAleasa].puncte[i]!=0)
            for(j=1; j<=Electron.nrPiese; j++)
            {
                for(a=0; a<Electron.Piese[j].nrLegaturi; a++)
                    if(abs(Electron.Piese[PiesaAleasa].puncte[i])==abs(Electron.Piese[j].puncte[a]) && PiesaAleasa!=j)
                    {
                        if(Electron.Piese[PiesaAleasa].puncte[i]>0)
                            drawLine(Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,0,Electron.Piese[PiesaAleasa].modLeg[i]);
                        if(Electron.Piese[j].puncte[a]>0)
                            drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,0,Electron.Piese[j].modLeg[a]);
                    }
            }
    }
}
void  redeseneazaLegaturi(Schema &Electron)
{
    int i,j,v,a,z;
    for(z=1; z<=Electron.nrPiese; z++)
    {
        for(i=0; i<Electron.Piese[z].nrLegaturi; i++)
        {
            if(Electron.Piese[z].puncte[i]!=0)
                for(j=1; j<=Electron.nrPiese; j++)
                {
                    for(a=0; a<Electron.Piese[j].nrLegaturi; a++)
                        if(abs(Electron.Piese[z].puncte[i])==abs(Electron.Piese[j].puncte[a]) && z!=j)
                        {
                            if(Electron.Piese[z].puncte[i]>0)
                                drawLine(Electron.Piese[z].pLeg[i].x,Electron.Piese[z].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,14,Electron.Piese[z].modLeg[i]);
                            if(Electron.Piese[j].puncte[a]>0)
                                drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[z].pLeg[i].x,Electron.Piese[z].pLeg[i].y,14,Electron.Piese[j].modLeg[a]);
                        }
                }
        }
    }
}
void recoloreaza(Schema &Electron)
{
    setcolor(Electron.culoare);
    rectangle(60,140,150,970);
    rectangle( 1740, 140, 1830, 970);
    deseneazaLiniiMeniu(0,0,Electron);
    line( 70,140, 1750, 140);
    line( 150,970,1830,970);
    deseneazaLiniiMeniu(1680,1680,Electron);
}
void mutaPieselePuse(int modLeg, Schema &Electron)
{
    int PiesaAleasa,nrPiesaAleasa;
    bool ok=1;
    do
    {
        int xMouse,yMouse;
        PiesaAleasa=alegePiesaPusa(Electron,xMouse,yMouse);
        if ((xMouse < 1040) && (yMouse < 40) &&abs( 1040 - xMouse)<=140 && abs(40 - yMouse)<=40)
        {
            setcolor(Electron.culoare);
            rectangle(900,1,1040,40);
            ok=0;
            redeseneazaLegaturi(Electron);
            colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
            for(int i=1; i<=Electron.nrPiese; i++)
                amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        }
        else
        {
            mutaLegaturi(Electron,PiesaAleasa);
            schimbaPozPiesaPusa(Electron.Piese[PiesaAleasa],modLeg);
            redeseneazaLegaturi(Electron);
            colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
            for(int i=1; i<=Electron.nrPiese; i++)
                amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
            recoloreaza(Electron);
        }
    }
    while(ok==1);
}
/*--------------------------------------------------------------DeseneazaLegaturi--------------------------------------------------------*/
void drawLine(int x1, int y1, int x2, int y2, int cul,int modLeg)
{
    if(modLeg==0)
    {
        setcolor(cul);
        line(x1,y1,x1,y2);
        line(x1,y2,(x1+x2)/2,y2);
        line((x1+x2)/2,y2,x2,y2);
    }
    else
    {
        setcolor(cul);
        line(x1,y1,(x1+x2)/2,y1);
        line((x1+x2)/2,y1,(x1+x2)/2,y2);
        line((x1+x2)/2,y2,x2,y2);
    }
}
void selectorTipLeg(int &modLeg)
{
    int xMouse,yMouse;
    coordonate(xMouse,yMouse);
    if((xMouse < 1320) && (yMouse < 80 ) && abs(1320 - xMouse)<=150 && abs(80 - yMouse)<=80)
        modLeg=0;
    else if((xMouse < 1320) && (yMouse < 120 ) && abs(1320 - xMouse)<=150 && abs(120- yMouse)<=120)
        modLeg=1;
    setcolor(BLACK);
    rectangle(1170,41,1320,80);
    outtextxy(1185,55,"LEGATURA1");
    rectangle(1170,80,1320,120);
    outtextxy(1185,95,"LEGATURA2");
    setcolor(CYAN);
    line(1170,40,1320,40);


}
void deseneazaLegatura(int &idNod1, int &p1, int &idNod2, int &p2,Schema &Electron,int modLeg,int &g,int &ok)
{
    bool click=false;
    int i, xMouse,yMouse;
    g=0;
    ok=1;
    int ok1=0;
    // aleg un punct de legatura (p1) de la nodul 1 (idNod1)
    do
    {
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            ok=1;
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            rectangle(1170,1,1320,40);
            if(xMouse>1170 && xMouse<1320 && yMouse>1 && yMouse<40)
            {
                ok=0;
                click=true;
            }
            else
            {
                for (i=1; i<=Electron.nrPiese; i++)
                    if (abs(Electron.Piese[i].pLeg[0].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[0].y - yMouse)<=5)
                    {
                        idNod1=i;
                        p1=0;
                        click=true;
                    }
                    else if (abs(Electron.Piese[i].pLeg[1].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[1].y - yMouse)<=5)
                    {
                        idNod1=i;
                        p1=1;
                        click=true;
                    }
                    else if (abs(Electron.Piese[i].pLeg[2].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[2].y - yMouse)<=5)
                    {
                        idNod1=i;
                        p1=2;
                        click=true;
                    }
                    else if (abs(Electron.Piese[i].pLeg[3].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[3].y - yMouse)<=5)
                    {
                        idNod1=i;
                        p1=3;
                        click=true;
                    }


            }
        }
    }
    while (!click);
    // aleg un punct de legatura (p2) de la nodul 2 (idNod2)
    // pana aleg, desenez mereu o linie
    if(ok==1)
    {
        click=false;
        int x1,y1,x2,y2;
        int ok=0;
        x1=Electron.Piese[idNod1].pLeg[p1].x;
        y1=Electron.Piese[idNod1].pLeg[p1].y;
        xMouse=mousex();
        yMouse=mousey();
        do
        {
            drawLine(x1,y1,xMouse,yMouse, YELLOW,modLeg);
            delay(50);
            drawLine(x1,y1,xMouse,yMouse,BLACK,modLeg);
            xMouse=mousex();
            yMouse=mousey();
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                clearmouseclick(WM_LBUTTONDOWN);
                xMouse=mousex();
                yMouse=mousey();
                for (i=1; i<=Electron.nrPiese; i++)
                    if (abs(Electron.Piese[i].pLeg[0].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[0].y - yMouse)<=5)
                    {
                        idNod2=i;
                        p2=0;
                        click=true;
                        ok=1;
                    }
                    else if (abs(Electron.Piese[i].pLeg[1].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[1].y - yMouse)<=5)
                    {
                        idNod2=i;
                        p2=1;
                        click=true;
                        ok=1;
                    }
                    else if (abs(Electron.Piese[i].pLeg[2].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[2].y - yMouse)<=5)
                    {
                        idNod2=i;
                        p2=2;
                        click=true;
                        ok=1;
                    }
                    else if (abs(Electron.Piese[i].pLeg[3].x - xMouse)<=5 && abs(Electron.Piese[i].pLeg[3].y - yMouse)<=5)
                    {
                        idNod2=i;
                        p2=3;
                        click=true;
                        ok=1;
                    }
                click=true;
            }

        }
        while (!click);
        if(ok==1)
        {
            x2=Electron.Piese[idNod2].pLeg[p2].x;
            y2=Electron.Piese[idNod2].pLeg[p2].y;
        }
        if(ok==1)
        {
            if(idNod1==idNod2)
            {
                redeseneazaLegaturi(Electron);
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                for(int i=1; i<=Electron.nrPiese; i++)
                    amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
                showerrorbox("Atentie, nu este posibil!");
            }
            else if(Electron.Piese[idNod2].puncte[p2] !=0 || Electron.Piese[idNod1].puncte[p1]!=0)
            {
                redeseneazaLegaturi(Electron);
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                for(int i=1; i<=Electron.nrPiese; i++)
                    amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
                showerrorbox("Atentie, nu este posibil!");
            }
            else
            {
                drawLine(x1,y1,x2,y2, YELLOW,modLeg);
                g=1;
            }
        }
        else
        {
            drawLine(x1,y1,xMouse,yMouse, BLACK,modLeg);
            colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
            redeseneazaLegaturi(Electron);
            for(int i=1; i<=Electron.nrPiese; i++)
                amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        }
    }
}
void SelecteazaNod(int &idNod1, int &p1, int &idNod2, int &p2,Schema &Electron,int modLeg)
{
    int xMouse,yMouse;
    int ok=1,g,ok1;
    do
    {
        deseneazaLegatura(idNod1,p1,idNod2,p2,Electron,modLeg,g,ok1);
        if(g==1)
        {
            Electron.indiceLegatura++;
            Electron.nrLegaturi++;
            Electron.Piese[idNod1].pLeg[p1].id=Electron.indiceLegatura;
            Electron.Piese[idNod2].pLeg[p2].id=Electron.indiceLegatura;
            Electron.Piese[idNod1].modLeg[p1]=modLeg;
            Electron.Piese[idNod2].modLeg[p2]=modLeg;
            Electron.Piese[idNod1].puncte[p1]=Electron.indiceLegatura;
            Electron.Piese[idNod2].puncte[p2]=-(Electron.indiceLegatura);
            redeseneazaLegaturi(Electron);
            colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
            for(int i=1; i<=Electron.nrPiese; i++)
                amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        }
        colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
        for(int i=1; i<=Electron.nrPiese; i++)
            amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        if(ok1==0)
        {
            ok=0;
        }
        else
        {
            coordonate(xMouse,yMouse);
        }

    }
    while (ok==1);
}
/*----------------------------------------------------------------------ZOOM--------------------------------------------------------*/
unsigned  alegePiesaRedimensionare(Schema &Electron,int &x,int&y)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if(xMouse>1320 && xMouse<1500 && yMouse>1 && yMouse<40)
            {
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void redimensioneaza(Schema &Electron)
{
    int ok=1,xMouse,yMouse,PiesaAleasa,x,y;
    while(1 && ok==1)
    {
        PiesaAleasa=alegePiesaRedimensionare(Electron,xMouse,yMouse);
        if(PiesaAleasa==0)
            ok=0;
        while(1 && ok==1)
        {
            if(xMouse>1320 && xMouse<1410 && yMouse>41 && yMouse<80)
            {
                colorareNegru(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y);
                refaLegatura(Electron,PiesaAleasa);
                if(Electron.Piese[PiesaAleasa].zoom>7)
                {
                    colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,0);
                    Electron.Piese[PiesaAleasa].zoom-=1;
                    colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,3);
                }
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                amplaseaza(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,Electron.Piese[PiesaAleasa].culoare);
                redeseneazaLegaturi(Electron);
            }
            else if(xMouse>1410 && xMouse<1500 && yMouse>41 && yMouse<80)
            {
                {
                    colorareNegru(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y);
                    refaLegatura(Electron,PiesaAleasa);
                    if(Electron.Piese[PiesaAleasa].zoom<25)
                    {
                        colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,0);
                        Electron.Piese[PiesaAleasa].zoom+=1;
                        colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,3);
                    }
                    colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                    amplaseaza(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,Electron.Piese[PiesaAleasa].culoare);
                    redeseneazaLegaturi(Electron);
                }
            }
            else if(xMouse>1320 && xMouse<1500 && yMouse>1 && yMouse<40)
            {
                ok=0;
                colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,0);
            }
            if(ok==1)
                coordonate(xMouse,yMouse);
        }
    }
}
/*----------------------------------------------------------------------ROTIRE------------------------------------------------------*/
unsigned  alegePiesaRotire(Schema &Electron,int &x,int&y)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if(xMouse>1500 && xMouse<1630 && yMouse>1 && yMouse<40)
            {
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void rotestePiesa(Schema &Electron)
{
    int ok=1,xMouse,yMouse,PiesaAleasa,x,y;
    while(1 && ok==1)
    {
        PiesaAleasa=alegePiesaRotire(Electron,xMouse,yMouse);
        if(PiesaAleasa==0)
            ok=0;
        while(1 && ok==1)
        {
            if(xMouse>1500 && xMouse<1565 && yMouse>41 && yMouse<80)
            {
                colorareNegru(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y);
                refaLegatura(Electron,PiesaAleasa);
                if(Electron.Piese[PiesaAleasa].orientare<3)
                    Electron.Piese[PiesaAleasa].orientare+=1;
                else
                {
                    Electron.Piese[PiesaAleasa].orientare=0;
                }
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                amplaseaza(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,Electron.Piese[PiesaAleasa].culoare);
                redeseneazaLegaturi(Electron);
            }
            else if(xMouse>1566 && xMouse<1630 && yMouse>41 && yMouse<80)
            {
                colorareNegru(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y);
                refaLegatura(Electron,PiesaAleasa);
                if(Electron.Piese[PiesaAleasa].orientare>0)
                    Electron.Piese[PiesaAleasa].orientare-=1;
                else
                {
                    Electron.Piese[PiesaAleasa].orientare=3;
                }
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                amplaseaza(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,Electron.Piese[PiesaAleasa].culoare);
                redeseneazaLegaturi(Electron);
            }
            else if(xMouse>1500 && xMouse<1630 && yMouse>1 && yMouse<40)
            {
                ok=0;
                colorareDreptunghi(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,0);
                colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
                amplaseaza(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y,Electron.Piese[PiesaAleasa].culoare);
                redeseneazaLegaturi(Electron);
            }
            if(ok==1)
                coordonate(xMouse,yMouse);
        }
    }
}
/*----------------------------------------------------------------------EDIT-----------------------------------------------------*/
unsigned  alegePiesaEditare(Schema &Electron,int &x,int&y,int x1,int x2,int y1,int y2)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if(xMouse>x1 && xMouse<x2 && yMouse>y1 && yMouse<y2)
            {
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void CitesteSir(int x, int y, char mesaj[MAX3], char S[MAX3] )
{
    char Enter = 9;
    char Space = 32;
    char BackSpace = 8;
    char Escape = 27;
    char s2[2];
    s2[1]='\0';
    char MultimeDeCaractereAcceptabile[300]="0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ~!`@#$%+-^&*/\\()_=[],;.?<>:;{} ";
    char SIR[MAX3]="";
    char S_initial[MAX3];
    char tasta;
    char S_[MAX3];
    strcpy(S_initial,S);
    settextstyle(DEFAULT_FONT,HORIZ_DIR,2);
    strcpy(S_,"");
    strcat(S_,"_");
    setcolor(BLACK);
    s2[0]=tasta;
    int xNou,yNou;
    xNou=x+textwidth(S);
    yNou=y+textheight(S);
    setfillstyle(SOLID_FILL,BLACK);
    bar(x,y,xNou,yNou);
    do
    {
        tasta=getch();
        if (tasta==0)
        {
            tasta=getch();
            Beep(1000,500);
        }
        else if (strchr(MultimeDeCaractereAcceptabile, tasta))
        {
            // stergem fostul sir
            strcpy(S_,SIR);
            strcat(S_,"_");
            setcolor(BLACK);
            outtextxy(x,y,S_);
            s2[0]=tasta;
            strcat(SIR,s2);
            strcpy(S_,SIR);
            strcat(S_,"_");
            setcolor(WHITE);
            outtextxy(x,y,S_);
        }
        if (tasta==BackSpace)
            if (!(strcmp(SIR,""))) Beep(500,100);
            else
            {
                setcolor(BLACK);
                outtextxy(x,y,S_);
                setcolor(WHITE);
                SIR[strlen(SIR)-1]='\0';
                strcpy(S_,SIR);
                strcat(S_,"_") ;
                outtextxy(x,y,S_);
                Beep(200,20);
            }
        else if (tasta!=Space && tasta!=Escape)
        {
            Beep(200,20);
        }
    }
    while (tasta!=Space && tasta!=Escape);
    if (tasta == Escape)
        strcpy(SIR,S_initial);
    setcolor(BLACK);
    outtextxy(x,y,S_);
    setcolor(WHITE);
    outtextxy(x,y,SIR);
    SIR[strlen(SIR)-1]='\0';
    strcpy(S,SIR);
}
void Culoare(Piesa &P,int culoare)
{
    colorareNegru(P,P.x,P.y);
    amplaseaza(P,P.x,P.y,culoare);
    P.culoare=culoare;
}
void schimbaCuloare(Piesa &P,int x1,int y1)
{
    int x,y;
    coordonate(x,y);
    if(x > x1 && x < x1+50 && y > y1 && y < y1+20)
    {
        Culoare(P,0);
    }
    else if(x > x1+50 && x < x1+100 && y > y1 && y < y1+20)
    {
        Culoare(P,1);
    }
    else if(x > x1+100 && x < x1+150 && y > y1 && y < y1+20)
    {
        Culoare(P,2);
    }
    else if(x > x1+150 && x < x1+200 && y > y1 && y < y1+20)
    {
        Culoare(P,3);
    }
    else if(x > x1 && x < x1+50 && y > y1+20 && y < y1+40)
    {
        Culoare(P,4);
    }
    else if(x > x1+50 && x < x1+100 && y > y1+20 && y < y1+40)
    {
        Culoare(P,5);
    }
    else if(x > x1+100 && x < x1+150 && y > y1+20 && y < y1+40)
    {
        Culoare(P,6);
    }
    else if(x > x1+150 && x < x1+200 && y > y1+20 && y < y1+40)
    {
        Culoare(P,7);
    }
    else if(x > x1 && x < x1+50 && y > y1+40 && y < y1+60)
    {
        Culoare(P,8);
    }
    else if(x > x1+50 && x < x1+100 && y > y1+40 && y < y1+60)
    {
        Culoare(P,9);
    }
    else if(x > x1+100 && x < x1+150 && y > y1+40 && y < y1+60)
    {
        Culoare(P,10);
    }
    else if(x > x1+150 && x < x1+200 && y > y1+40 && y < y1+60)
    {
        Culoare(P,11);
    }
    else if(x > x1 && x < x1+50 && y > y1+60 && y < y1+80)
    {
        Culoare(P,12);
    }
    else if(x > x1+50 && x < x1+100 && y > y1+60 && y < y1+80)
    {
        Culoare(P,13);
    }
    else if(x > x1+100 && x < x1+150 && y > y1+60 && y < y1+80)
    {
        Culoare(P,14);
    }
    else if(x > x1+150 && x < x1+200 && y > y1+60 && y < y1+80)
    {
        Culoare(P,15);
    }
    else
        Culoare(P,P.culoare);
}
void editeaza(Schema &Electron)
{
    int ok=1,ok1=1,xMouse,yMouse,PiesaAleasa,x,y;
    coordonate(xMouse,yMouse);
    if((xMouse < 700) && (yMouse < 40 ) && abs(700 - xMouse)<=100 && abs(40 - yMouse)<=40)
    {
        setcolor(CYAN);
        rectangle(600,1,700,40);
        while(1 && ok==1)
        {
            PiesaAleasa=alegePiesaEditare(Electron,xMouse,yMouse,601,699,1,40);
            if(PiesaAleasa!=0)
            {
                setfillstyle(SOLID_FILL,BLACK);
                bar(760,440,1400,600);
                readimagefile("imaginiProgram\\ceva.jpg",650,430,1280,530 );
                outtextxy(760, 453,Electron.Piese[PiesaAleasa].nume);
                outtextxy(800, 472,Electron.Piese[PiesaAleasa].rezistenta);
                outtextxy(758, 492,Electron.Piese[PiesaAleasa].voltaj);
                ok1=1;
                coordonate(xMouse,yMouse);
                while(ok1==1)
                {
                    if(xMouse>760 && xMouse<1500 && yMouse>453 && yMouse<470)
                    {
                        CitesteSir(760,453,"NUME: ",Electron.Piese[PiesaAleasa].nume);
                    }
                    else if(xMouse>800 && xMouse<1500 && yMouse>472 && yMouse<490)
                    {
                        CitesteSir(800,472,"REZISTENTA: ",Electron.Piese[PiesaAleasa].rezistenta);
                    }

                    else if(xMouse>758 && xMouse<1500 && yMouse>492 && yMouse<510)
                    {
                        CitesteSir(755,492,"VOLTAJ: ",Electron.Piese[PiesaAleasa].voltaj);
                    }
                    else
                    {
                        ok1=0;
                        setcolor(BLACK);
                        rectangle(Electron.Piese[PiesaAleasa].x-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].x+Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y+Electron.Piese[PiesaAleasa].zoom*4);
                    }
                    if(ok1==1)
                        coordonate(xMouse,yMouse);
                }

            }
            else
            {
                ok=0;
                setfillstyle(SOLID_FILL,BLACK);
                bar(500,400,1400,600);
            }
            if(ok==1)
                coordonate(xMouse,yMouse);
        }
        colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
        redeseneazaLegaturi(Electron);
        for(int i=1; i<=Electron.nrPiese; i++)
            amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
    }
    else if((xMouse < 700) && (yMouse < 80 ) && abs(700 - xMouse)<=100 && abs(80 - yMouse)<=40)
    {
        setcolor(Electron.culoare);
        rectangle(600,1,700,40);
        setcolor(CYAN);
        rectangle(600,40,700,80);
        deseneazaChenarCuloare(Electron,700,40);
        while(1 && ok==1)
        {
            PiesaAleasa=alegePiesaEditare(Electron,xMouse,yMouse,600,700,40,80);
            if(PiesaAleasa!=0)
            {
                schimbaCuloare(Electron.Piese[PiesaAleasa],700,40);
                setcolor(BLACK);
                rectangle(Electron.Piese[PiesaAleasa].x-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].x+Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y+Electron.Piese[PiesaAleasa].zoom*4);
            }
            else
                ok=0;
        }
        setcolor(Electron.culoare);
        rectangle(600,40,700,80);
        setfillstyle(SOLID_FILL,BLACK);
        bar(700,41,901,121);
    }
}

/*----------------------------------------------------------------------STERGE-----------------------------------------------------*/
unsigned  alegePiesaStergere(Schema &Electron,int &x,int&y)
{
    bool click=false;
    unsigned nrPiesaAleasa = 0;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            for (i=1; i<=Electron.nrPiese; i++)
                if (abs(Electron.Piese[i].x - xMouse)<=15 && abs(Electron.Piese[i].y - yMouse)<=15)
                {
                    setcolor(CYAN);
                    rectangle(Electron.Piese[i].x-Electron.Piese[i].zoom*4,Electron.Piese[i].y-Electron.Piese[i].zoom*4,Electron.Piese[i].x+Electron.Piese[i].zoom*4,Electron.Piese[i].y+Electron.Piese[i].zoom*4);
                    nrPiesaAleasa=i;
                    click=true;
                }
            if(xMouse>501 && xMouse<599 && yMouse>1 && yMouse<40)
            {
                click=true;
            }
        }
    while (!click);
    return nrPiesaAleasa;
}
void alegeLegatura(Schema &Electron,int PiesaAleasa)
{
    int i,j,v,a,ok=1,x,y;
    while(1 && ok==1)
    {
        coordonate(x,y);
        if(x>500 && x<600 && y>80 && y<120)
            ok=0;
        else
            for(i=0; i<Electron.Piese[PiesaAleasa].nrLegaturi; i++)
            {
                if (abs(Electron.Piese[PiesaAleasa].pLeg[i].x - x)<=5 && abs(Electron.Piese[PiesaAleasa].pLeg[i].y - y)<=5)
                    for(j=1; j<=Electron.nrPiese; j++)
                    {
                        for(a=0; a<Electron.Piese[j].nrLegaturi; a++)
                            if(abs(Electron.Piese[PiesaAleasa].puncte[i])==abs(Electron.Piese[j].puncte[a]) && PiesaAleasa!=j)
                            {
                                if(Electron.Piese[PiesaAleasa].puncte[i]>0)
                                {
                                    drawLine(Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,0,Electron.Piese[PiesaAleasa].modLeg[i]);
                                    Electron.Piese[PiesaAleasa].puncte[i]=0;
                                    Electron.Piese[j].puncte[a]=0;
                                    Electron.nrLegaturi--;

                                }
                                else if(Electron.Piese[j].puncte[a]>0)
                                {
                                    drawLine(Electron.Piese[j].pLeg[a].x,Electron.Piese[j].pLeg[a].y,Electron.Piese[PiesaAleasa].pLeg[i].x,Electron.Piese[PiesaAleasa].pLeg[i].y,0,Electron.Piese[j].modLeg[a]);
                                    Electron.Piese[PiesaAleasa].puncte[i]=0;
                                    Electron.Piese[j].puncte[a]=0;
                                    Electron.nrLegaturi--;
                                }
                            }
                    }
                else if(x>501 && x<599 && y>1 && y<40)
                {
                    ok=0;
                    break;
                }
            }
    }
}
void sterge(Schema &Electron)
{
    int ok=1,ok1=1,xMouse,yMouse,PiesaAleasa,x,y;
    coordonate(xMouse,yMouse);
    if(xMouse>500 && xMouse<600 && yMouse>40 && yMouse<80)
    {
        setcolor(CYAN);
        rectangle(500,40,600,80);
        while(1 && ok==1)
        {
            PiesaAleasa=alegePiesaStergere(Electron,xMouse,yMouse);
            if(PiesaAleasa!=0)
            {
                colorareNegru(Electron.Piese[PiesaAleasa],Electron.Piese[PiesaAleasa].x,Electron.Piese[PiesaAleasa].y);
                refaLegatura(Electron,PiesaAleasa);
                setcolor(BLACK);
                for(int a=0; a<Electron.Piese[PiesaAleasa].nrLegaturi; a++)
                    if(Electron.Piese[PiesaAleasa].puncte[a]!=0)
                    {
                        Electron.nrLegaturi--;
                    }
                for(int i=0; i<Electron.Piese[PiesaAleasa].nrLegaturi; i++)
                    if(Electron.Piese[PiesaAleasa].puncte[i]!=0)
                        for(int j=1; j<=Electron.nrPiese; j++)
                        {
                            for(int a=0; a<Electron.Piese[j].nrLegaturi; a++)
                                if(abs(Electron.Piese[PiesaAleasa].puncte[i])==abs(Electron.Piese[j].puncte[a]) && PiesaAleasa!=j)
                                {
                                    Electron.Piese[j].puncte[a]=0;

                                }
                        }
                rectangle(Electron.Piese[PiesaAleasa].x-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].x+Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y+Electron.Piese[PiesaAleasa].zoom*4);
                for(int i=PiesaAleasa; i<=Electron.nrPiese; i++)
                    Electron.Piese[i]=Electron.Piese[i+1];
                Electron.nrPiese--;
                setfillstyle(SOLID_FILL,BLACK);
            bar(1630,80,1900,130);
                numarPieseEcran(Electron);
            }
            else
            {
                ok=0;
            }
        }
    }
    else if(xMouse>500 && xMouse<600 && yMouse>80 && yMouse<120)
    {
        setcolor(CYAN);
        rectangle(500,80,600,120);
        while(1 && ok==1)
        {
            PiesaAleasa=alegePiesaStergere(Electron,xMouse,yMouse);
            if(PiesaAleasa!=0)
            {
                alegeLegatura(Electron,PiesaAleasa);
                setcolor(BLACK);
                rectangle(Electron.Piese[PiesaAleasa].x-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y-Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].x+Electron.Piese[PiesaAleasa].zoom*4,Electron.Piese[PiesaAleasa].y+Electron.Piese[PiesaAleasa].zoom*4);
            }
            else
            {
                ok=0;
            }
        }
    }
    colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
    redeseneazaLegaturi(Electron);
    for(int i=1; i<=Electron.nrPiese; i++)
        amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
}
/*----------------------------------------------------------------------PROIECT-----------------------------------------------------*/
void ferestraAtentie()
{
    showerrorbox("Nu este permis!");
}

/*--------------------------------------------------------------SAlVARE--------------------------------------------------------*/
void editeazaFisier(Schema &Electron,char nume[MAX3],int g)
{

    setfillstyle(SOLID_FILL,BLACK);
    bar(760,400,1400,600);

    if(g==0)
    {
        setcolor(CYAN);
        readimagefile("imaginiProgram\\nume.jpg",770,450,1170,510 );
        CitesteSir(910,473,"NUME: ",nume);
    }
    else if(g==1)
    {
        setcolor(CYAN);
        readimagefile("imaginiProgram\\extensie.jpg",770,450,1170,510 );
        CitesteSir(945,474,"EXTENSIE: ",nume);
    }
    else if(g==2)
    {
        setcolor(CYAN);
        readimagefile("imaginiProgram\\nume.jpg",770,450,1170,510 );
        CitesteSir(910,473,"NUME: ",nume);
    }
}
void salveazaPiese(Piesa& P,char folder2[MAX3],char extensie[MAX3],Schema &Electron)
{
    char numeFisier[MAX3],s[MAX3];
    strcpy(numeFisier,folder2);
    strcat(numeFisier,P.nume);
    strcat(numeFisier,extensie);
    FILE* f=fopen(numeFisier,"w");
    fprintf(f,"%s\n",P.nume);//NUME
    fprintf(f,"%s\n",P.rezistenta);
    fprintf(f,"%s\n",P.voltaj);
    fprintf(f,"%d\n",P.zoom);
    fprintf(f,"%d\n",P.numarOrdine);
    fprintf(f,"%d\n",P.nrLegaturi);
    fprintf(f,"%d\n",P.culoare);
    fprintf(f,"%d\n",P.x);
    fprintf(f,"%d\n",P.y);
    for (unsigned i=0; i<P.nrLegaturi; i++)
    {
        fprintf(f,"%d %d\n",P.puncte[i],P.modLeg[i]);
    }
    fprintf(f,"%d\n",P.orientare);
    fprintf(f,"%d\n",P.descriere.nComenzi);
    for(int i=1; i<=P.descriere.nComenzi; i++)
    {
        fprintf(f,"%c %f %f %f %f\n",P.descriere.comanda[i],P.descriere.x1[i],P.descriere.y1[i],P.descriere.x2[i],P.descriere.y2[i]);
    }
    fclose(f);
}
void salveazaDate(Schema &Electron,char folder[MAX3])
{
    FILE* f=fopen(folder,"w");
    fprintf(f,"%d\n",Electron.nrPiese);
    fprintf(f,"%d\n",Electron.nrLegaturi);
    fprintf(f,"%d\n",Electron.indiceLegatura);
    fprintf(f,"%d\n",Electron.culoare);
    for(int i=1; i<=Electron.nrPiese; i++)
        fprintf(f,"%s ",Electron.Piese[i].nume);
    fclose(f);
}
void salvare(Schema &Electron)
{
    int num,ok=1,x,y,g=0,g1=0;
    char nume[MAX3],folder[MAX3],folder2[MAX3],folderDate[MAX3],numeSalvare[MAX3],extensie[MAX3],imagine[MAX3],pathImagine[MAX3];
    coordonate(x,y);
    if(x>1040 && x<1170 && y>80 && y<120)
    {
        setcolor(Electron.culoare);
        rectangle(1040,1,1170,40);
        setcolor(CYAN);
        rectangle(1040,80,1170,120);
        g=2;
        strcpy(pathImagine,"imaginiSalvate");
        editeazaFisier(Electron,imagine,g);
        strcat(pathImagine,"\\\\");
        strcat(pathImagine,imagine);
        strcat(pathImagine,".jpg");
        setfillstyle(SOLID_FILL,BLACK);
        bar(760,440,1400,600);
        colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
        redeseneazaLegaturi(Electron);
        for(int i=1; i<=Electron.nrPiese; i++)
            amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        writeimagefile(pathImagine,150,140,1740,970);
    }
    else
    {
        if(x>1040 && x<1170 && y>1 && y<40)
            strcpy(extensie,".txt");
        else if(x>1040 && x<1170 && y>40 && y<80)
        {
            g=1;
            setcolor(Electron.culoare);
            rectangle(1040,1,1170,40);
            setcolor(CYAN);
            rectangle(1040,40,1170,80);
            editeazaFisier(Electron,extensie,g);
            g1=1;
        }
        g=0;
        editeazaFisier(Electron,nume,g);
        Electron.nrFisiere++;
        for(int i=0; i<Electron.nrFisiere && ok==1; i++)
            if(strcmp(Electron.fisiere[i],nume)==0)
            {
                editeazaFisier(Electron,nume,g);
                ok=0;
            }
        strcpy(Electron.fisiere[Electron.nrFisiere],nume);
        strcpy(folder,nume);
        mkdir(folder);
        strcpy(folderDate,folder);
        strcat(folderDate,"\\\\");
        if(g1==0)
            strcat(folderDate,"data.txt");
        else
        {
            strcat(folderDate,"data");
            strcat(folderDate,extensie);
        }
        salveazaDate(Electron,folderDate);
        strcat(folder,"\\\\");
        strcpy(folder2,folder);
        setfillstyle(SOLID_FILL,BLACK);
        bar(760,440,1400,600);
        for(int i=1; i<=Electron.nrPiese; i++)
            salveazaPiese(Electron.Piese[i],folder2,extensie,Electron);
        setfillstyle(SOLID_FILL,BLACK);
        bar(760,440,1400,600);
        colorareNegru(Electron.Meniu[13],Electron.xIntrerupator,Electron.yIntrerupator);
        redeseneazaLegaturi(Electron);
        for(int i=1; i<=Electron.nrPiese; i++)
            amplaseaza(Electron.Piese[i],Electron.Piese[i].x,Electron.Piese[i].y,Electron.Piese[i].culoare);
        //fclose(fptr);
    }
}
/*--------------------------------------------------------------OPEN-----------------------------------------------------------*/
void coloreazaEcran(Schema &Electron);
void pieseFisierNou(Schema &Open)
{
    char numeFisier[MAX3];
    readimagefile("imaginiProgram\\nume.jpg",770,450,1170,510 );
    CitesteSir(910,470,"NUME: ",numeFisier);
    setfillstyle(SOLID_FILL,BLACK);
    bar(760,440,1400,600);
    strcpy(Open.numeFisier,numeFisier);
    strcat(numeFisier,"\\\\");
    strcat(numeFisier,"data.txt");
    FILE* f=fopen(numeFisier,"rt");
    while(f == NULL)
    {
        showerrorbox("Folder inexistent!");
        readimagefile("imaginiProgram\\nume.jpg",770,450,1170,510 );
        CitesteSir(910,470,"NUME: ",numeFisier);
        setfillstyle(SOLID_FILL,BLACK);
        bar(760,440,1400,600);
        strcpy(Open.numeFisier,numeFisier);
        strcat(numeFisier,"\\\\");
        strcat(numeFisier,"data.txt");
        f=fopen(numeFisier,"rt");
    }
    fscanf(f,"%d",&Open.nrPiese);
    fscanf(f,"%d",&Open.nrLegaturi);
    fscanf(f,"%d",&Open.indiceLegatura);
    fscanf(f,"%d",&Open.culoare);
    coloreazaEcran(Open);
    for(int i=1; i<=Open.nrPiese; i++)
        fscanf(f,"%s ",&Open.Piese[i].nume);
}
void deschide(Piesa& P,Schema &Open)
{
    char numeFisier[MAX3],s[MAX3];
    strcpy(numeFisier,Open.numeFisier);
    strcat(numeFisier,"\\\\");
    strcat(numeFisier,P.nume);
    strcat(numeFisier,".txt");
    FILE* f=fopen(numeFisier,"rt");
    fscanf(f,"%s\n",&P.nume);//NUME
    fscanf(f,"%s\n",&P.rezistenta);
    fscanf(f,"%s\n",&P.voltaj);
    fscanf(f,"%d\n",&P.zoom);
    fscanf(f,"%d\n",&P.numarOrdine);
    fscanf(f,"%d\n",&P.nrLegaturi);
    fscanf(f,"%d\n",&P.culoare);
    fscanf(f,"%d\n",&P.x);
    fscanf(f,"%d\n",&P.y);
    for (unsigned i=0; i<P.nrLegaturi; i++)
    {
        fscanf(f,"%d %d\n",&P.puncte[i],&P.modLeg[i]);
    }
    fscanf(f,"%d\n",&P.orientare);
    fscanf(f,"%d\n",&P.descriere.nComenzi);
    for(int i=1; i<=P.descriere.nComenzi; i++)
    {
        fscanf(f,"%c %f %f %f %f\n",&P.descriere.comanda[i],&P.descriere.x1[i],&P.descriere.y1[i],&P.descriere.x2[i],&P.descriere.y2[i]);
    }
    fclose(f);
}
void tema(Schema &Electron);
void verifica(Schema &Electron);
void OpenNou(Schema &Electron)
{
    int ok=1;
    numarPieseEcran(Electron);
    while(1 && ok==1)
    {
        int xMouse,yMouse;
        coordonate(xMouse,yMouse);
        if((xMouse < 400) && (yMouse < 40 ) && abs(400 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            ok=0;
            cleardevice();
        }
        else if((xMouse < 500) && (yMouse < 40 ) && abs(500 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(400,1,500,40);
            tema(Electron);
            setcolor(Electron.culoare);
            rectangle(400,1,500,40);
        }
        else if((xMouse < 600) && (yMouse < 40 ) && abs(600 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(500,1,600,40);
            setcolor(Electron.culoare);
            rectangle(500,40,600,80);
            rectangle(500,80,600,120);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(523,50,"PIESA");
            outtextxy(508,90,"LEGATURA");
            sterge(Electron);
            setcolor(Electron.culoare);
            rectangle(500,1,600,40);
            setcolor(BLACK);
            rectangle(500,41,600,80);
            rectangle(500,80,600,120);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(523,50,"PIESA");
            outtextxy(508,90,"LEGATURA");
        }
        else if((xMouse < 700) && (yMouse < 40 ) && abs(700 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {

            setcolor(Electron.culoare);
            rectangle(600,40,700,80);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(610,50,"CULOARE");
            editeaza(Electron);
            setcolor(Electron.culoare);
            rectangle(600,1,700,40);
            setcolor(BLACK);
            rectangle(600,41,700,80);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(610,50,"CULOARE");


        }
        else if ((xMouse < 900) && (yMouse < 40 ) && abs(900 - xMouse)<=200 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(700,1,900,40);
            IaPiesaDinMeniu(Electron);
            setcolor(Electron.culoare);
            rectangle(700,1,900,40);
        }
        else if ((xMouse < 1040) && (yMouse < 40 ) && abs(1040 - xMouse)<=140 && abs(40 - yMouse)<=40)
        {
            int modLeg=1;
            setcolor(CYAN);
            rectangle(900,1,1040,40);
            mutaPieselePuse(modLeg,Electron);
            setcolor(Electron.culoare);
            rectangle(900,1,1040,40);

        }
        else if ((xMouse < 1170) && (yMouse < 40 ) && abs(1170 - xMouse)<=130 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1040,1,1170,40);
            setcolor(Electron.culoare);
            rectangle(1040,40,1170,80);
            rectangle(1040,80,1170,120);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1050,50,"SALVARE CA");
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1080,90,"POZA");
            salvare(Electron);
            setcolor(Electron.culoare);
            rectangle(1040,1,1170,40);
            setcolor(BLACK);
            rectangle(1040,41,1170,80);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1050,50,"SALVARE CA");
            rectangle(1040,80,1170,120);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1080,90,"POZA");
        }
        else if((xMouse < 1320) && (yMouse < 40 ) && abs(1320 - xMouse)<=150 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1170,1,1320,40);
            setcolor(Electron.culoare);
            delay(50);
            rectangle(1170,41,1320,80);
            rectangle(1170,80,1320,120);
            setcolor(WHITE);
            settextstyle(0, HORIZ_DIR, 2);
            outtextxy(1185,55,"LEGATURA1");
            outtextxy(1185,95,"LEGATURA2");
            setcolor(Electron.culoare);
            int modLeg;
            selectorTipLeg(modLeg);
            int idNod1,idNod2;
            int p1,p2;
            SelecteazaNod(idNod1,p1,idNod2,p2,Electron,modLeg);
            setcolor(Electron.culoare);
            rectangle(1170,1,1320,40);
        }
        else if((xMouse < 280) && (yMouse < 40 ) && abs(280 - xMouse)<=230 && abs(40 - yMouse)<=40 )
        {
            setcolor(CYAN);
            rectangle(50,1,280,40);
            setcolor(Electron.culoare);
            _circuit(Electron);
            rectangle(50,1,280,40);
            setcolor(Electron.culoare);
        }
        else if((xMouse < 215) && (yMouse < 84 ) && abs(215 - xMouse)<=100 && abs(84 - yMouse)<=40)
        {

            setcolor(CYAN);
            rectangle( 115,45,215,84);
            setcolor(Electron.culoare);
            clear_(Electron, xMouse, yMouse);
            rectangle( 115,45,215,84);
            setcolor(Electron.culoare);
        }
        else if((xMouse < 1500) && (yMouse < 40 ) && abs(1500 - xMouse)<=150 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1320,1,1500,40);
            setcolor(Electron.culoare);
            rectangle(1320,40,1500,80);
            setcolor(WHITE);
            line(1410,41,1410,80);
            line(1355,60,1375,60);
            line(1445,60,1465,60);
            line(1455,50,1455,70);
            redimensioneaza(Electron);
            setcolor(BLACK);
            rectangle(1320,41,1500,80);
            line(1410,41,1410,80);
            line(1355,60,1375,60);
            line(1445,60,1465,60);
            line(1455,50,1455,70);
            setcolor(Electron.culoare);
            rectangle(1320,1,1500,40);
        }
        else if((xMouse < 1630) && (yMouse < 40 ) && abs(1630 - xMouse)<=129 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1500,1,1630,40);
            setcolor(Electron.culoare);
            rectangle(1500,41,1630,80);
            line(1565,41,1565,80);
            setcolor(WHITE);
            outtextxy(1530,52,"S");
            outtextxy(1590,52,"D");
            rotestePiesa(Electron);
            setcolor(Electron.culoare);
            rectangle(1500,1,1630,40);
            setcolor(BLACK);
            rectangle(1500,41,1630,80);
            line(1565,41,1565,80);
            outtextxy(1530,52,"S");
            outtextxy(1590,52,"D");

        }
        else if((xMouse < 1730) && (yMouse < 40 ) && abs(1730 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1630,1,1730,40);
            verifica(Electron);
            setcolor(Electron.culoare);
            rectangle(1630,1,1730,40);
        }
        else if((xMouse < 1860) && (yMouse < 40 ) && abs(1860 - xMouse)<=130 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle( 1730,1,1860,40);
            inverseazaLegaturi(Electron);
            setcolor(Electron.culoare);
            rectangle(1730,1,1860,40);
        }
    }
}
void refacereCircuit(Schema &Open)
{
    pieseFisierNou(Open);
    for(int i=1; i<=Open.nrPiese; i++)
        deschide(Open.Piese[i],Open);
    for(int i=1; i<=Open.nrPiese; i++)
        amplaseaza(Open.Piese[i],Open.Piese[i].x,Open.Piese[i].y,Open.Piese[i].culoare);
    redeseneazaLegaturi(Open);
}
/*--------------------------------------------------------------VERIFICA--------------------------------------------------------*/
void verifica(Schema &Electron)
{
    int ok1=1,ok=1,i,j,g=0,g1=0;
    if(Electron.nrPiese==0)
        ok1=0;
    if(g==0 && ok1==1)
    {
        for(int a=1; a<=Electron.nrPiese; a++)
            if(Electron.Piese[a].numarOrdine==8)
                g=1;
    }
    if(g==1)
    {
        for(i=1; i<=Electron.nrPiese && ok==1; i++)
            for(j=0; j<Electron.Piese[i].nrLegaturi && ok==1; j++)
            {
                if(Electron.Piese[i].puncte[j]==0)
                {
                    ok=0;
                }
            }
    }
    if(ok1==0)
    {
        showerrorbox("Circuit inexistent!");
    }
    else
    {
        if(g==1)
        {
            if(ok==1)
            {
                for(int a=1; a<=Electron.nrPiese; a++)
                    if(Electron.Piese[a].numarOrdine==4)
                    {
                        colorareNegru(Electron.Piese[a],Electron.Piese[a].x,Electron.Piese[a].y);
                        amplaseazaGalben(Electron.Piese[a],Electron.Piese[a].x,Electron.Piese[a].y);
                        g1=1;
                    }
                for(int a=1; a<=Electron.nrPiese; a++)
                    if(Electron.Piese[a].numarOrdine==12)
                    {
                        colorareNegru(Electron.Piese[a],Electron.Piese[a].x,Electron.Piese[a].y);
                        Electron.Meniu[13].orientare=Electron.Piese[a].orientare;
                        Electron.Meniu[13].zoom=Electron.Piese[a].zoom;
                        amplaseaza(Electron.Meniu[13],Electron.Piese[a].x,Electron.Piese[a].y,Electron.Piese[a].culoare);
                        Electron.Meniu[13].x=Electron.Piese[a].x;
                        Electron.Meniu[13].y=Electron.Piese[a].y;
                        Electron.xIntrerupator=Electron.Meniu[13].x;
                        Electron.yIntrerupator=Electron.Meniu[13].y;
                    }
            }
            else
                showerrorbox("Circuit incorect, conectati toate piesele!");
        }
        else
            showerrorbox("Nu exista sursa de curent, generator");
    }
    if(ok==1 && g1==0 && g==1)
        showerrorbox("Circuitul este corect, dar nu ati plasat un bec!");
}
/*--------------------------------------------------------------TEMA--------------------------------------------------------*/
void schimbaCuloareTema(Schema &Electron,int x1,int y1,int &ok)
{
    int x,y;
    coordonate(x,y);
    if(x > x1 && x < x1+50 && y > y1 && y < y1+20)
    {
        Electron.culoare=0;
    }
    else if(x > x1+50 && x < x1+100 && y > y1 && y < y1+20)
    {
        Electron.culoare=1;
    }
    else if(x > x1+100 && x < x1+150 && y > y1 && y < y1+20)
    {
        Electron.culoare=2;
    }
    else if(x > x1+150 && x < x1+200 && y > y1 && y < y1+20)
    {
        Electron.culoare=3;
    }
    else if(x > x1 && x < x1+50 && y > y1+20 && y < y1+40)
    {
        Electron.culoare=4;
    }
    else if(x > x1+50 && x < x1+100 && y > y1+20 && y < y1+40)
    {
        Electron.culoare=5;
    }
    else if(x > x1+100 && x < x1+150 && y > y1+20 && y < y1+40)
    {
        Electron.culoare=6;
    }
    else if(x > x1+150 && x < x1+200 && y > y1+20 && y < y1+40)
    {
        Electron.culoare=7;
    }
    else if(x > x1 && x < x1+50 && y > y1+40 && y < y1+60)
    {
        Electron.culoare=8;
    }
    else if(x > x1+50 && x < x1+100 && y > y1+40 && y < y1+60)
    {
        Electron.culoare=9;
    }
    else if(x > x1+100 && x < x1+150 && y > y1+40 && y < y1+60)
    {
        Electron.culoare=10;
    }
    else if(x > x1+150 && x < x1+200 && y > y1+40 && y < y1+60)
    {
        Electron.culoare=11;
    }
    else if(x > x1 && x < x1+50 && y > y1+60 && y < y1+80)
    {
        Electron.culoare=12;
    }
    else if(x > x1+50 && x < x1+100 && y > y1+60 && y < y1+80)
    {
        Electron.culoare=13;
    }
    else if(x > x1+100 && x < x1+150 && y > y1+60 && y < y1+80)
    {
        Electron.culoare=14;
    }
    else if(x > x1+150 && x < x1+200 && y > y1+60 && y < y1+80)
    {
        Electron.culoare=15;
    }
    else
    {
        Electron.culoare=Electron.culoare;
        ok=0;
    }
}
void coloreazaEcran(Schema &Electron)
{
    setcolor(Electron.culoare);
    rectangle(300,1,400,40);
    rectangle(400,1,500,40);
    rectangle(500,1,600,40);
    rectangle(600,1,700,40);
    rectangle(700,1,900,40);
    rectangle(900,1,1040,40);
    rectangle(1040,1,1170,40);
    rectangle(1170,1,1320,40);
    rectangle(1320,1,1500,40);
    rectangle(1500,1,1630,40);
    rectangle(1630,1,1730,40);
    rectangle( 1730,1,1860,40);
    rectangle( 50,1,280,40);
    rectangle( 115,45,215,84);
    rectangle(60,140,150,970);
    rectangle( 1740, 140, 1830, 970);
    line( 70,140, 1750, 140);
    line( 150,970,1830,970);
    deseneazaLiniiMeniu(0,0,Electron);
    deseneazaLiniiMeniu(1680,1680,Electron);
}
void tema(Schema &Electron)
{
    int x,y,ok=1,ok1=1;
    deseneazaChenarCuloare(Electron,500,40);
    while(ok==1)
    {
        schimbaCuloareTema(Electron,500,40,ok1);
        coloreazaEcran(Electron);
        if(ok1==0)
            ok=0;
    }
    setfillstyle(SOLID_FILL,BLACK);
    bar(500,41,701,121);
}
/*--------------------------------------------------------------PROIECT--------------------------------------------------------*/
void ProiectNou(Schema &Electron)
{
    Electron.nrPiese=0;
    Electron.nrLegaturi=0;
    numarPieseEcran(Electron);
    int ok=1;
    while(1 && ok==1)
    {
        int xMouse,yMouse;
        coordonate(xMouse,yMouse);

        if((xMouse < 400) && (yMouse < 40 ) && abs(400 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            ok=0;
            cleardevice();
        }
        else if((xMouse < 500) && (yMouse < 40 ) && abs(500 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(400,1,500,40);
            tema(Electron);
            setcolor(Electron.culoare);
            rectangle(400,1,500,40);
        }
        else if((xMouse < 600) && (yMouse < 40 ) && abs(600 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(500,1,600,40);
            setcolor(Electron.culoare);
            rectangle(500,40,600,80);
            rectangle(500,80,600,120);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(523,50,"PIESA");
            outtextxy(508,90,"LEGATURA");
            sterge(Electron);
            setcolor(Electron.culoare);
            rectangle(500,1,600,40);
            setcolor(BLACK);
            rectangle(500,41,600,80);
            rectangle(500,80,600,120);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(523,50,"PIESA");
            outtextxy(508,90,"LEGATURA");
        }
        else if((xMouse < 700) && (yMouse < 40 ) && abs(700 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {

            setcolor(Electron.culoare);
            rectangle(600,40,700,80);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(610,50,"CULOARE");
            editeaza(Electron);
            setcolor(Electron.culoare);
            rectangle(600,1,700,40);
            setcolor(BLACK);
            rectangle(600,41,700,80);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(610,50,"CULOARE");

        }
        else if ((xMouse < 900) && (yMouse < 40 ) && abs(900 - xMouse)<=200 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(700,1,900,40);
            IaPiesaDinMeniu(Electron);
            setcolor(Electron.culoare);
            rectangle(700,1,900,40);

        }
        else if ((xMouse < 1040) && (yMouse < 40 ) && abs(1040 - xMouse)<=140 && abs(40 - yMouse)<=40)
        {
            int modLeg=1;
            setcolor(CYAN);
            rectangle(900,1,1040,40);
            setcolor(Electron.culoare);
            mutaPieselePuse(modLeg,Electron);

        }
        else if ((xMouse < 1170) && (yMouse < 40 ) && abs(1170 - xMouse)<=130 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1040,1,1170,40);
            setcolor(Electron.culoare);
            rectangle(1040,40,1170,80);
            rectangle(1040,80,1170,120);
            setcolor(WHITE);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1050,50,"SALVARE CA");
            outtextxy(1080,90,"POZA");
            salvare(Electron);
            setcolor(Electron.culoare);
            rectangle(1040,1,1170,40);
            setcolor(BLACK);
            rectangle(1040,41,1170,80);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1050,50,"SALVARE CA");
            rectangle(1040,80,1170,120);
            settextstyle(8, HORIZ_DIR, 1);
            outtextxy(1080,90,"POZA");
        }
        else if((xMouse < 1320) && (yMouse < 40 ) && abs(1320 - xMouse)<=150 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1170,1,1320,40);
            setcolor(Electron.culoare);
            delay(50);
            rectangle(1170,41,1320,80);
            rectangle(1170,80,1320,120);
            setcolor(WHITE);
            settextstyle(0, HORIZ_DIR, 2);
            outtextxy(1185,55,"LEGATURA1");
            outtextxy(1185,95,"LEGATURA2");
            setcolor(Electron.culoare);
            int modLeg;
            selectorTipLeg(modLeg);
            int idNod1,idNod2;
            int p1,p2;
            SelecteazaNod(idNod1,p1,idNod2,p2,Electron,modLeg);
            setcolor(Electron.culoare);
            rectangle(1170,1,1320,40);
        }
        else if((xMouse < 280) && (yMouse < 40 ) && abs(280 - xMouse)<=230 && abs(40 - yMouse)<=40 )
        {
            setcolor(CYAN);
            rectangle(50,1,280,40);
            setcolor(Electron.culoare);
            // delay(50);
            _circuit(Electron);
            rectangle(50,1,280,40);
            setcolor(Electron.culoare);

        }
        else if((xMouse < 215) && (yMouse < 84 ) && abs(215 - xMouse)<=100 && abs(84 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle( 115,45,215,84);
            setcolor(Electron.culoare);
            clear_(Electron, xMouse, yMouse);
            rectangle( 115,45,215,84);
            setcolor(Electron.culoare);
        }
        else if((xMouse < 1500) && (yMouse < 40 ) && abs(1500 - xMouse)<=150 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1320,1,1500,40);
            setcolor(Electron.culoare);
            rectangle(1320,40,1500,80);
            setcolor(WHITE);
            line(1410,41,1410,80);
            line(1355,60,1375,60);
            line(1445,60,1465,60);
            line(1455,50,1455,70);
            redimensioneaza(Electron);
            setcolor(BLACK);
            rectangle(1320,41,1500,80);
            line(1410,41,1410,80);
            line(1355,60,1375,60);
            line(1445,60,1465,60);
            line(1455,50,1455,70);
            setcolor(Electron.culoare);
            rectangle(1320,1,1500,40);
        }
        else if((xMouse < 1630) && (yMouse < 40 ) && abs(1630 - xMouse)<=129 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1500,1,1630,40);
            setcolor(Electron.culoare);
            rectangle(1500,41,1630,80);
            line(1565,41,1565,80);
            setcolor(WHITE);
            outtextxy(1530,52,"S");
            outtextxy(1590,52,"D");
            rotestePiesa(Electron);
            setcolor(Electron.culoare);
            rectangle(1500,1,1630,40);
            setcolor(BLACK);
            rectangle(1500,41,1630,80);
            line(1565,41,1565,80);
            outtextxy(1530,52,"S");
            outtextxy(1590,52,"D");
        }
        else if((xMouse < 1730) && (yMouse < 40 ) && abs(1730 - xMouse)<=100 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle(1630,1,1730,40);
            verifica(Electron);
            setcolor(Electron.culoare);
            rectangle(1630,1,1730,40);
        }
        else if((xMouse < 1860) && (yMouse < 40 ) && abs(1860 - xMouse)<=130 && abs(40 - yMouse)<=40)
        {
            setcolor(CYAN);
            rectangle( 1730,1,1860,40);
            inverseazaLegaturi(Electron);
            setcolor(Electron.culoare);
            rectangle(1730,1,1860,40);
        }

    }
}


#endif // STRUCTURI_H_INCLUDED
