#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>

#define RCERCHIOEST 32  ///Più il valore è alto più il cerchio è ristretto
#define RCERCHIOINT 58 ///Più il valore è alto più il cerchio è ristretto
#define GRANDEZZAFINESTRA 750
#define DISTCROCE 50
#define DIM 3   ///Grandezza Griglia

void disegnaGriglia();
void disegnaCroce(int, int);
int giocoTris(int,char [][DIM]);
void controlloCoord(int*);
int riempiMatr(char [][DIM],char,int,int);
void stampaMatr(char[][DIM]);
int checkWin(char [][DIM]);
void azzeraStr(char []);


int main()
{
    ///int altSchermo=GetSystemMetrics(SM_CYSCREEN),larghSchermo=GetSystemMetrics(SM_CXSCREEN);        ///Trovo la risoluzione dello schermo per aprire il programma in fullscreen
    int larghSchermo=GRANDEZZAFINESTRA,altSchermo=GRANDEZZAFINESTRA;
    char tris[DIM][DIM]={0};
    int i=0,win=0,rit=0;

    initwindow(larghSchermo,altSchermo,"",GetSystemMetrics(SM_CXSCREEN)/3,GetSystemMetrics(SM_CXSCREEN)/8);
    setbkcolor(YELLOW);
    while((!kbhit()&&i<9)&&win==0){
        disegnaGriglia();
        rit=giocoTris(i,tris);
        win=checkWin(tris);
        i+=rit;
    }

    if(win==0)
        outtextxy(0,0,"TIE");
    else if(win==2)
        outtextxy(0,0,"Vince Cerchio");
    else
        outtextxy(0,0,"Vince Croce");
    outtextxy(20,20,"FINE GIOCO");
    Sleep(2000);
    closegraph();

    return 0;
}

void disegnaGriglia(){
        setcolor(YELLOW);
        setlinestyle(0,0,0);
            ///Linee Orizzontali
        line(0,GRANDEZZAFINESTRA/3,GRANDEZZAFINESTRA,GRANDEZZAFINESTRA/3); ///Prima linea di divisone
        line(0,GRANDEZZAFINESTRA/1.5,GRANDEZZAFINESTRA,GRANDEZZAFINESTRA/1.5);  ///Seconda linea di divisione della griglia
            ///Linee Verticali
        line(GRANDEZZAFINESTRA/3,0,GRANDEZZAFINESTRA/3,GRANDEZZAFINESTRA); ///Prima linea di divisione della griglia
        line(GRANDEZZAFINESTRA/1.5,0,GRANDEZZAFINESTRA/1.5,GRANDEZZAFINESTRA);  ///Seconda linea di divisone della griglia
}

void disegnaCroce(int xMouse,int yMouse){
    setcolor(RED);
    setlinestyle(0,0,10);
    line(xMouse+DISTCROCE,yMouse+DISTCROCE,xMouse-DISTCROCE+GRANDEZZAFINESTRA/3,yMouse-DISTCROCE+GRANDEZZAFINESTRA/3);
    line(xMouse-DISTCROCE+GRANDEZZAFINESTRA/3,yMouse+DISTCROCE,xMouse+DISTCROCE,yMouse-DISTCROCE+GRANDEZZAFINESTRA/3);
}
void disegnaCerchio(int xMouse,int yMouse){
        ///Cerchio Esterno
    setcolor(LIGHTBLUE);
    circle(xMouse+GRANDEZZAFINESTRA/6,yMouse+GRANDEZZAFINESTRA/6,GRANDEZZAFINESTRA/6-RCERCHIOEST);
        ///Cerchio Interno
    setcolor(LIGHTBLUE);
    circle(xMouse+GRANDEZZAFINESTRA/6,yMouse+GRANDEZZAFINESTRA/6,GRANDEZZAFINESTRA/6-RCERCHIOINT);

    setfillstyle(SOLID_FILL,LIGHTBLUE);
    floodfill(xMouse+GRANDEZZAFINESTRA/18,yMouse+GRANDEZZAFINESTRA/6,LIGHTBLUE);

}

int giocoTris(int turni,char griglia[][DIM]){
    int coordMouseX,coordMouseY,rit;
    while(!ismouseclick(WM_LBUTTONDOWN));
    getmouseclick(WM_LBUTTONDOWN,coordMouseX,coordMouseY);

    controlloCoord(&coordMouseX);
    controlloCoord(&coordMouseY);
    if(turni%2==0){
        rit=riempiMatr(griglia,'x',coordMouseX,coordMouseY);
        if(rit==0)
            disegnaCroce(coordMouseX,coordMouseY);
    }else{
        rit=riempiMatr(griglia,'o',coordMouseX,coordMouseY);
        if(rit==0)
            disegnaCerchio(coordMouseX,coordMouseY);
    }
    if(rit!=0)
        return 0;
    else
        return 1;
}

void controlloCoord(int *mouseCoord){
    if(*mouseCoord<=GRANDEZZAFINESTRA/3)
        *mouseCoord=0;
    else if(*mouseCoord<=GRANDEZZAFINESTRA/1.5)
        *mouseCoord=GRANDEZZAFINESTRA/3;
    else if(*mouseCoord>GRANDEZZAFINESTRA/1.5)
        *mouseCoord=GRANDEZZAFINESTRA/1.5;
}

int riempiMatr(char matrice[][DIM], char carattere,int coordMouseX,int coordMouseY){
    if(coordMouseY==0){
        if(coordMouseX==0){
            if(matrice[0][0]!='x'&&matrice[0][0]!='o')
                matrice[0][0]=carattere;
            else
                return 1;
        }else if(coordMouseX==GRANDEZZAFINESTRA/3){
            if(matrice[0][1]!='x'&&matrice[0][1]!='o')
                matrice[0][1]=carattere;
            else
                return 1;
        }else{
            if(matrice[0][2]!='x'&&matrice[0][2]!='o')
                matrice[0][2]=carattere;
            else
                return 1;
        }
    }
    if(coordMouseY==GRANDEZZAFINESTRA/3){
        if(coordMouseX==0){
            if(matrice[1][0]!='x'&&matrice[1][0]!='o')
                matrice[1][0]=carattere;
            else
                return 1;
        }else if(coordMouseX==GRANDEZZAFINESTRA/3){
            if(matrice[1][1]!='x'&&matrice[1][1]!='o')
                matrice[1][1]=carattere;
            else
                return 1;
        }else{
            if(matrice[1][2]!='x'&&matrice[1][2]!='o')
                matrice[1][2]=carattere;
            else
                return 1;
        }
    }
    if(coordMouseY==GRANDEZZAFINESTRA/1.5){
        if(coordMouseX==0){
            if(matrice[2][0]!='x'&&matrice[2][0]!='o')
                matrice[2][0]=carattere;
            else
                return 1;
        }else if(coordMouseX==GRANDEZZAFINESTRA/3){
            if(matrice[2][1]!='x'&&matrice[2][1]!='o')
                matrice[2][1]=carattere;
            else
                return 1;
        }else{
            if(matrice[2][2]!='x'&&matrice[2][2]!='o')
                matrice[2][2]=carattere;
            else
                return 1;
        }
    }
    return 0;
}

int checkWin(char matr[][DIM]){
    int i,k,check,ritorno=0;
    char str[DIM+1]={0};
    char serieX[]={"xxx"};
    char serieO[]={"ooo"};

    for(i=0;i<DIM&&ritorno==0;i++){
        for(k=0;k<DIM;k++)
            str[k]=matr[i][k];
        check=strcmp(str,serieX);
        if(check==0){
            ritorno=1;
        }
        else{
            check=strcmp(str,serieO);
            if(check==0)
                ritorno=2;
        }
        azzeraStr(str);
    }
    azzeraStr(str);
    for(i=0;i<DIM&&ritorno==0;i++){
        for(k=0;k<DIM;k++)
            str[k]=matr[k][i];
        check=strcmp(str,serieX);
        if(check==0){
            ritorno=1;
        }
        else{
            check=strcmp(str,serieO);
            if(check==0)
                ritorno=2;
        }
        azzeraStr(str);
    }
    azzeraStr(str);
    for(i=0;i<DIM&&ritorno==0;i++){
        str[i]=matr[i][i];
    }
    check=strcmp(str,serieX);
    if(check==0){
        ritorno=1;
    }
    else{
        check=strcmp(str,serieO);
        if(check==0)
            ritorno=2;
    }
    azzeraStr(str);

    for(i=0,k=DIM-1;i<DIM&&ritorno==0;i++,k--)
            str[i]=matr[i][k];
        check=strcmp(str,serieX);
        if(check==0){
            ritorno=1;
        }
        else{
            check=strcmp(str,serieO);
            if(check==0)
                ritorno=2;
        }
        azzeraStr(str);

    return ritorno;
}
void azzeraStr(char str[]){
    int i;

    for(i=0;i<DIM+1;i++)
        str[i]='\0';
}
