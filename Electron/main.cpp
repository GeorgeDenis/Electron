#include <iostream>
#include<graphics.h>
#include <winbgim.h>
#include <windows.h>
#include "Structuri.h"
#include "Legaturi.h"
#include <stdlib.h>
using namespace std;
#define MAX1 20
#define MAX2 60
#define NrPieseMeniu 13


void Selector(int,int,int);
void Accesare(Schema &Electron,Schema &Open);

// Incarcare
void baraIncarcare()
{
    setfillstyle(LTSLASH_FILL,BLUE);
    floodfill(0.3, 0.0, WHITE);
    setcolor(WHITE);
    rectangle(870,500,1050,510);
    setcolor(CYAN);
    for(int i=0; i<=176; i++)
    {
        line(871+i,502,871+i,508);
        delay(10);
    }
    cleardevice();
}
void MeniuPrincipal()
{
    setbkcolor(BLACK);
    cleardevice();
    readimagefile("imaginiProgram\\meniu..jpg",0,0,2000,1050);
    settextstyle(0,HORIZ_DIR,6);
    delay(10);
}
void Inapoi(Schema &Electron,Schema &Open)
{
    bool click=false;
    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            if(xMouse>20&&xMouse<130&&yMouse>20&&yMouse<60)
            {

                cleardevice();
                baraIncarcare();
                MeniuPrincipal();
                Accesare(Electron,Open);
            }
        }
        while(!click);
}
void butoane(Schema &Electron)
{
    setcolor(Electron.culoare);
    rectangle(300,1,400,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(307,13,"INAPOI");
    setcolor(Electron.culoare);
    rectangle(400,1,500,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(420,13,"TEMA");
    setcolor(Electron.culoare);
    rectangle(500,1,600,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(507,13,"STERGE");
    setcolor(Electron.culoare);
    rectangle(600,1,700,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(615,13,"EDIT");
    setcolor(Electron.culoare);
    rectangle(700,1,900,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(720,13,"MENIU PIESE");
    setcolor(Electron.culoare);
    rectangle(900,1,1040,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(940,13,"MUTA");
    setcolor(Electron.culoare);
    rectangle(1040,1,1170,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1055,13,"SALVARE");
    setcolor(Electron.culoare);
    rectangle(1170,1,1320,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1190,13,"LEGATURI");
    setcolor(Electron.culoare);
    rectangle(1320,1,1500,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1330,13,"ZOOM IN/OUT");
    setcolor(Electron.culoare);
    rectangle(1500,1,1630,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(1520,13,"ROTESTE");
    setcolor(Electron.culoare);
    rectangle( 50,1,280,40);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy(60,13,"CIRCUIT AUTOMAT");
    setcolor(Electron.culoare);
    rectangle( 115,45,215,84);
    setcolor(WHITE);
    settextstyle(0,HORIZ_DIR,2);
    outtextxy( 130,57,"CLEAR");
    setcolor(Electron.culoare);
    rectangle(1630,1,1730,40);
    setcolor(WHITE);
    settextstyle(8,HORIZ_DIR,1);
    outtextxy( 1638,5,"VERIFICA");
    outtextxy( 1645,20,"CIRCUIT");
    setcolor(Electron.culoare);
    rectangle( 1730,1,1860,40);
    setcolor(WHITE);
    settextstyle(8,HORIZ_DIR,1);
    outtextxy( 1742,5,"INVERSEAZA");
    outtextxy( 1752,20,"LEGATURA");
}
void Accesare(Schema&Electron,Schema &Open)
{
    bool click=false;

    int xMouse,yMouse,i;
    do
        if(ismouseclick(WM_LBUTTONDOWN) && !click)
        {
            clearmouseclick(WM_LBUTTONDOWN);
            xMouse=mousex();
            yMouse=mousey();
            if(xMouse>770&&xMouse<1230&&yMouse>390&&yMouse<470)
            {
                cleardevice();
                baraIncarcare();
                butoane(Electron);
                deseneazaProiect(Electron);
                ProiectNou(Electron);
                baraIncarcare();
                MeniuPrincipal();
                Accesare(Electron,Open);
                click=true;
            }
            else
                if(xMouse>770&&xMouse<1230&&yMouse>510&&yMouse<590)
            {
                cleardevice();
                baraIncarcare();
                readimagefile("imaginiProgram\\Piese_Electron5.jpg",0,0,getmaxwidth(), getmaxheight());
                Inapoi(Electron,Open);
            }
            else if(xMouse>770&&xMouse<1230&&yMouse>630&&yMouse<700)
                {
                    cleardevice();
                    baraIncarcare();
                    butoane(Open);
                    deseneazaProiect(Open);
                    refacereCircuit(Open);
                    OpenNou(Open);
                    baraIncarcare();
                    MeniuPrincipal();
                    Accesare(Electron,Open);
                    click=true;
                }
                else if(xMouse>770&&xMouse<1230&&yMouse>740&&yMouse<820)
                 {
                     exit(0);
                 }

        }
    while (!click);
}
int main()
{
    int window2 = initwindow(getmaxwidth(), getmaxheight(),"Electron");
    Schema Electron;
    Schema Open;
    baraIncarcare();
    MeniuPrincipal();
    Accesare(Electron,Open);
    getch();
    closegraph(window2);
    return 0;
}
