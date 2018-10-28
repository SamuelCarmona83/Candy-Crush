#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <ctype.h>
#include <conio.h>


#define AZUL 5
#define NARANJA 30
#define MORADO 15
#define VERDE 4
#define GRIS 254
#define ROJO 3

int candy[9][9][6]={0};
char name[5]={0};
int score=0,move=40,gelatina=81,scoreg=0;

// [9][9][0] <====== Guarda las golosinas
// [9][9][1] <====== Guarda si hay o no Gelatina
// [9][9][2] <====== Guarda las combinaciones a borrar
// [9][9][3] <====== Guarda los caramelos rayados horizontales
// [9][9][4] <====== Guarda los caramelos rayados verticales
// [9][9][5] <====== Guarda las gelatinas que se borrar con las combinaciones

//-----------------Color innecesario-------------------------------------------

void SetColor(int ForgC){
 	WORD wColor;
 	//This handle is needed to get the current background attribute

 	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
 	CONSOLE_SCREEN_BUFFER_INFO csbi;
 	//csbi is used for wAttributes word

 	if(GetConsoleScreenBufferInfo(hStdOut, &csbi)){
      	//To mask out all but the background attribute, and to add the color
      	wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
      	SetConsoleTextAttribute(hStdOut, wColor);
 	}
}
//------------------------Cosas innecesariamente bonitas--------------

void ventana(){
    
	SMALL_RECT rect;
	COORD coord;
	coord.X = 250; // Defining our X and
	coord.Y = 50;  // Y size for buffer.

	rect.Top = 0;
	rect.Left = 0;
	rect.Bottom = coord.Y-1; // height for window
	rect.Right = coord.X-1;  // width for window

	HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE); // get handle
	SetConsoleScreenBufferSize(hwnd, coord);   	// set buffer size
	SetConsoleWindowInfo(hwnd, TRUE, &rect);   	// set window size
    
	//---------------------centrada----------------------------------
    

	//Get the window console handle(isn't the right code but works for these sample
	HWND ConsoleWindow;
	ConsoleWindow=GetForegroundWindow();

	//Getting the desktop hadle and rectangule
	HWND   hwndScreen;
	RECT   rectScreen;   	 
	hwndScreen=GetDesktopWindow ();  
	GetWindowRect(hwndScreen,&rectScreen);    	 
    
	//Set windows size(see the width problem)
	SetWindowPos (ConsoleWindow,NULL,0,0,1000,600, SWP_SHOWWINDOW);

	// Get the current width and height of the console
	RECT rConsole;
	GetWindowRect (ConsoleWindow,&rConsole);    	 
	int Width = rConsole.left = rConsole.right;
	int Height = rConsole.bottom - rConsole.top;
    
	//caculate the window console to center of the screen    
	int ConsolePosX;
	int ConsolePosY;   	 
	ConsolePosX = ((rectScreen.right-rectScreen.left)/2-Width/2 );
	ConsolePosY = ((rectScreen.bottom-rectScreen.top)/2- Height/2 );    
	SetWindowPos(ConsoleWindow,NULL,ConsolePosX,ConsolePosY, Width, Height, SWP_SHOWWINDOW || SWP_NOSIZE);
}

void gotoxy(int x, int y){
HANDLE hCon=GetStdHandle(STD_OUTPUT_HANDLE);
COORD dwPos;
dwPos.X=x;
dwPos.Y=y;

SetConsoleCursorPosition(hCon, dwPos);
}

void pintar_limites(){
for (int i=1; i<100; i++){
gotoxy(i,0);  printf("%c",205);
gotoxy(i,23); printf("%c",205);
}

for (int i=0; i<23; i++){
gotoxy(1,i);  printf("%c",186);
gotoxy(100,i);printf("%c",186);
}

gotoxy(1,0);   printf("%c",201);
gotoxy(1,23);  printf("%c",200);
gotoxy(100,0); printf("%c",187);
gotoxy(100,23);printf("%c",188);

    	//impresiones actualizadas de movimientos y puntuaciones
    	gotoxy(70,6);
    	SetColor(12);
    	printf("Jugador ");
    	for(int i=0;i<3;i++)
    	printf("%c",name[i]);
		
		gotoxy(70,8);
		SetColor(13);
    	printf("Puntuacion %i",score+scoreg);
   	 
    	gotoxy(70,10);
    	SetColor(14);
    	printf("Movimientos %i",move);
    	
		gotoxy(70,12);
		SetColor(10);
    	printf("Gelatina %i",gelatina);
    	
    	gotoxy(100,23);
   	 	SetColor(15);
   	 
}
//----------------------------------------------------------------------------
void pintar_limites2(){
	SetColor(12);
for (int i=1; i<100; i++){
gotoxy(i,0);  printf("%c",205);
gotoxy(i,23); printf("%c",205);
}

for (int i=0; i<23; i++){
gotoxy(1,i);  printf("%c",186);
gotoxy(100,i);printf("%c",186);
}

gotoxy(1,0);   printf("%c",201);
gotoxy(1,23);  printf("%c",200);
gotoxy(100,0); printf("%c",187);
gotoxy(100,23);printf("%c",188);
	SetColor(15);
}

//----------------------------------------------------------------------------
void extra () {
	
	system("cls");
	pintar_limites2();
	SetColor(15);
	gotoxy(10,6);
	printf(" -------------------------------- CANDY CRUSH --------------------------------");
	gotoxy(10,8);
	printf("Ingrese nombre de jugador: (3 caracteres) \n");
	
	for(int i=0;i<3;i++){
	gotoxy(20+i,9);
	scanf(" %c", &name[i]);
	}
	
	char des='n';
	do{
	gotoxy(10,10);
	//printf("Desea ingresar una cantidad de movimientos? S=Si y N=No");
	gotoxy(20,11);
	//scanf(" %c",&des);
	
	}while(des!='s' && des!='n' && des!='N' && des!='S');
	
	if(des=='S' || des=='s'){
		do{
			gotoxy(10,12);
			printf("Ingrese la cantidad de movimientos con los que desea jugar. Rango: 10-40");
			gotoxy(20,13);
			scanf("%i",&move);
		}while(move<10 || move>40);
	}
		
	
	system("cls");
	pintar_limites2();
	SetColor(14);
	gotoxy(10,6);
	printf(" ----------------------------------- AYUDA -----------------------------------");
	gotoxy(10,8);
	printf(" Objetivos del juego:");
	gotoxy(10,9);
	printf(" - Intercambiar caramelos para crear combinaciones y borrar gelatinas.");
	gotoxy(10,10);
	printf(" - Borrar todas las gelatinas dentro del rango de movimientos permitidos.");
    gotoxy(10,11);
	printf(" Reglas del juego:");
	gotoxy(10,12);
	printf(" - Los caramelos solo pueden ser intercambiados con caramelos de igual color.");
	gotoxy(10,13);
	printf(" - Solo se puede intercambiar un caramelo con otro por movimiento.");
	gotoxy(10,14);
	printf(" - Cuatro caramelos juntos crean un caramelo rayado de ese mismo color.");
	gotoxy(10,15);
	printf(" - Intercambiar 2 caramelos rallados eliminara la fila y la columna.");
	gotoxy(10,16);
	printf(" - Ocho caramelos juntos crean dos caramelos rayados de ese mismo color.\n");
	gotoxy(10,18);
    
}

//----------------------------------------------------------------------------

void generar(int azar[]){
    	srand(time(0));//  Numeros aleatorios en funcion del tiempo
    	for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++){
        	candy[i][j][0]=azar[rand()%6];//asigna la gelatina
        	candy[i][j][1]=1; // Genera gelatina
        	candy[i][j][2]=0;
        	candy[i][j][3]=0;
        	candy[i][j][4]=0;
        	candy[i][j][5]=0;
    	}
    	}
}
//----------------------------------------------------------------------------

void rellenar(int azar[]){
    
	for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++){
        	if(candy[i][j][0]==0)
        	candy[i][j][0]=azar[rand()%6];//asigna la gelatina
    	}
    	}    
}

//----------------------------------------------------------------------------

int  gelatinarestante(){
	int cont=0;
	for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
    
    	if(candy[i][j][1]!=0)
    	cont++;
	}
	}
    gelatina=cont;
    scoreg=(81-cont)*2;
	return cont;
	
	
}

//----------------------------------------------------------------------------
int contar(int i,int j,char x){
    
	int cont=1;
   	 
    	if(x=='f'){
   	 
    	for(int k=j+1;k<9;k++){//recorre las coincidencias horizontales
   	 
    	if(candy[i][j][0]==candy[i][k][0]){
        	cont++;
    	}else{
        	break;//si uno es diferente evalua la siguiente casilla
    	}
   	 
    	}


    	}else{
   	 
    	for(int k=i+1;k<9;k++){//recorre las coincidencias verticales
   	 
    	if(candy[i][j][0]==candy[k][j][0]){
        	cont++;
    	}else{
        	break;//si uno es diferente evalua la siguiente casilla
    	}
   	 
    	}
   	 
    	}
return cont;
}
//-----------------------------borrar----------------------------------------

void borrar(){
	
	for(int i=0;i<9;i++){
		for(int j=0;j<9;j++){
			
			if(candy[i][j][2]!=0)
   	 		candy[i][j][0]=0;
   	 	
    		if(candy[i][j][5]!=0){
        	candy[i][j][1]=0;//borra gelatina
        	candy[i][j][5]=0;
        	
       	 	
       	 
    		}else{
       			candy[i][j][5]=0;
    		}
    		//borra limpia la matriz de borrado luego borrar
    		candy[i][j][2]=0;
		}
		
	}
		
}

//----------------------------------------------------------------------------
void limpiar(){
    
	//------------------------------------------------------------------------
	for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
    
   	 
    	int cont=contar(i,j,'f');//retorna la cantidad de combinaciones horizontales
    	if(cont==3){//combinaciones de 3
        	//printf("\n taka *%i *%i *%i\n",i,j,cont);
        	for(int b=j;b<j+3;b++){
        	candy[i][b][2]=3;//asigna caracter para borrado
        	candy[i][b][5]=3;//acumular borrado de gelatinas en otra dimension
        	}
    	}else if(cont>=4){//combinaciones de 4
        	//printf("\n taka *%i *%i *%i\n",i,j,cont);
        	for(int b=j;b<j+cont;b++){
        	candy[i][b][2]=3;//asigna caracter para borrado
        	candy[i][b][5]=3;//acumular borrado de gelatinas en otra dimension
        	}
        	if(cont==4){
       	 
        	candy[i][j][4]=4;//rallado vertical aleatorio
        	candy[i][j][2]=0;// borra la gelatina
        	score+=3;
        	}
    	}
    	else if(cont==8){// combinaciones de 8    
    		candy[i][j][4]=4;//rallado vertical aleatorio
        	candy[i][j][2]=0;// borra la gelatina
        	candy[i][j+7][3]=4;//rallado vertical aleatorio
        	candy[i][j+7][2]=0;// borra la gelatina
        	score+=6;
    	
		}else{
    	}
   	 
    	int cont2=contar(i,j,'c');//retorna la cantidad de combinaciones verticales
   	 
    	if(cont2==3){//combinaciones de 3
        	for(int b=i;b<i+3;b++){
        	candy[b][j][2]=3;//asigna carracter para borrado
        	candy[b][j][5]=3;//acumular borrado de gelatinas en otra dimension
        	}
    	}else if(cont2>=4){//combinaciones de 4
        	for(int b=i;b<i+cont;b++){
        	candy[b][j][2]=3;//asigna carracter para borrado
        	candy[b][j][5]=3;//acumular borrado de gelatinas en otra dimension
        	}
        	if(cont2==4){
        	candy[i][j][3]=4;//rallado horizontal aleatorio
        	candy[i][j][2]=0;// no borra el rallado nuevo ( deberia borrar la gelatina)
        	score+=3;
       	 
        	}
       	 
    	}
    	else if(cont2==8){// combinaciones de 8    
    		
			candy[i][j][4]=4;//rallado vertical aleatorio
        	candy[i][j][2]=0;// borra la gelatina
        	candy[i+7][j][3]=4;//rallado vertical aleatorio
        	candy[i+7][j][2]=0;// borra la gelatina
        	score+=6;
    	
		
		}else{
    	}
   	 
       	 
    	}//for2
	}//for1
    
	//-----------------Borrar---------------------------------------------------
    
	for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
    
    
       	 
    	if(candy[i][j][2]!=0 && candy[i][j][3]==0 && candy[i][j][4]==0){//si hay algo en la dimension 2 borrara las golosinas y las gelatinas
       	 
        	candy[i][j][0]=0;//borra golosina
       	 
       	 
    	}else if(candy[i][j][2]!=0 && candy[i][j][4]==0 && candy[i][j][3]!=0){
         	 
          	//horizontales
          	//printf("BOOMH %i %i !",i,j);
         	 
          	for(int b=0;b<9;b++){
                 	 
                  	candy[i][b][2]=3;//borra la columna de caramelos
                 	 
                  	candy[i][b][5]=3;//borra las columna de gelatina
                 	 
                  	candy[i][j][3]=0;//elimina el rayado
                 	 
          	}
         	 
         	 
     	}else if(candy[i][j][2]!=0 && candy[i][j][3]==0 && candy[i][j][4]!=0){
           	 
            	//verticales  
            	//printf("BOOMV %i %i !",i,j);
           	 
            	for(int b=0;b<9;b++){
                 	 
                  	candy[b][j][2]=3;//borra la fila de golosinas
                 	 
                  	candy[b][j][5]=3;//llena la fila para borrar gelatina
                 	 
                  	candy[i][j][4]=0;//elimina el rayado
                 	 
          	}
                      	 
     	}
		
	}//for i
	}//for j
    
    	
    borrar();
    /*
    for(int i=0;i<9;i++){
    	for(int j=0;j<9;j++){
    		int cont=contar(i,j,'f');
    		int cont2=contar(i,j,'c');
    		if(cont>2 || cont2>2)
    			limpiar();
    			break;
		}
    	
	}
    */
    
	}//funcion

//----------------------Seleccion----------------------------------------------
void seleccion (int &x, int &y){
	
	SetColor(10);
	printf("Introduzca la fila del caramelo que desea mover.  ");
	scanf("%i", &x);
	printf("\nIntroduzca la columna del caramelo que desea mover.  ");
	scanf("%i", &y);
    
}

//-----------------------------Cambios-------------------------------------------

void cambioW(int bi,int bj, int x){
	int hold=0;
	hold=candy[bi-1][bj][x];
	candy[bi-1][bj][x]=candy[bi][bj][x];
	candy[bi][bj][x]=hold;
}

void cambioD(int bi,int bj,int x){
	int hold=0;
	hold=candy[bi][bj+1][x];
	candy[bi][bj+1][x]=candy[bi][bj][x];
	candy[bi][bj][x]=hold;
}

void cambioS(int bi,int bj,int x){
	int hold=0;
	hold=candy[bi+1][bj][x];
	candy[bi+1][bj][x]=candy[bi][bj][x];
	candy[bi][bj][x]=hold;
}

void cambioA(int bi,int bj,int x){
	int hold=0;
	hold=candy[bi][bj-1][x];
	candy[bi][bj-1][x]=candy[bi][bj][x];
	candy[bi][bj][x]=hold;
}
//-------------------------------------------------------------------------------


bool contarW(int bi,int bj){
	
	if(candy[bi][bj][0]==candy[bi-1][bj-1][0]  && candy[bi][bj][0]==candy[bi-1][bj+1][0])
		return true;
	if(candy[bi-1][bj][0]==candy[bi][bj-1][0]  && candy[bi-1][bj][0]==candy[bi][bj+1][0])
		return true;
	
	int cont=1,cont2=1,cont3=1;
		
	for(int k=bi-2;k>=0;k--){
		if(candy[bi][bj][0]==candy[k][bj][0])
		cont++;
		else
		break;
	}
	
	for(int k2=bj+1;k2<9;k2++){
		if(candy[bi][bj][0]==candy[bi-1][k2][0])
		cont2++;
		else
		break;
	}
	
	for(int k3=bj-1;k3>=0;k3--){
		if(candy[bi-1][k3][0]==candy[bi][bj][0])
		cont3++;
		else
		break;
	}
	
	if(cont>2 || cont2>2 || cont3>2)
		return true;/*
	else if(candy[bi][bj][0]==candy[bi-1][bj-1][0]==candy[bi-1][bj+1][0])
		return true;
	else if(candy[bi-1][bj][0]==candy[bi][bj-1][0]==candy[bi][bj+1][0])
		return true;*/
	else 
		return false;
	
}

////----------------------------------------------------------------------------


bool contarS(int bi,int bj){
	
	if(candy[bi][bj][0]==candy[bi+1][bj-1][0] && candy[bi][bj][0]==candy[bi+1][bj+1][0])
		return true;
	if(candy[bi+1][bj][0]==candy[bi][bj-1][0]  && candy[bi+1][bj][0]==candy[bi][bj+1][0])	
		return true;
	
	int cont=1,cont2=1,cont3=1;
	
	//vertical
	for(int k=bi+2;k<9;k++){
		if(candy[bi][bj][0]==candy[k][bj][0])
		cont++;
		else
		break;
	}
	//derecha
	for(int k2=bj+1;k2<9;k2++){
		if(candy[bi][bj][0]==candy[bi+1][k2][0])
		cont2++;
		else
		break;
	}
	
	//izquierda
	for(int k3=bj-1;k3>=0;k3--){
		if(candy[bi+1][k3][0]==candy[bi][bj][0])
		cont3++;
		else
		break;
	}
	
	if(cont>2 || cont2>2 || cont3>2)
		return true;/*
	else if(candy[bi][bj][0]==candy[bi+1][bj-1][0]==candy[bi+1][bj+1][0])
		return true;
	else if(candy[bi+1][bj][0]==candy[bi][bj-1][0]==candy[bi][bj+1][0])	
		return true;*/
	else 
		return false;
	
}
//-----------------------------------------------------------------------------

bool contarD(int bi,int bj){
	
	if(candy[bi][bj][0]==candy[bi-1][bj+1][0] && candy[bi][bj][0]==candy[bi+1][bj+1][0])
		return true;
	if(candy[bi][bj+1][0]==candy[bi-1][bj][0] && candy[bi][bj+1][0]==candy[bi+1][bj][0])
		return true;
	
		
	int cont=1,cont2=1,cont3=1;
	
	//arriba
	for(int k=bi-1 ;k>=0;k--){
		if(candy[bi][bj][0]==candy[k][bj+1][0])
		cont++;
		else
		break;
	}
	///abajo
	for(int k2=bi+1;k2<9;k2++){
		if(candy[bi][bj][0]==candy[k2][bj+1][0])
		cont2++;
		else
		break;
	}
	
	//derecha
	for(int k3=bj+2;k3<9;k3++){
		if(candy[bi][bj][0]==candy[bi][k3][0])
		cont3++;
		else
		break;
	}
	
	if(cont>2 || cont2>2 || cont3>2)
		return true;/*
	else if(candy[bi][bj][0]==candy[bi-1][bj+1][0]==candy[bi+1][bj+1][0])
		return true;
	else if(candy[bi][bj+1][0]==candy[bi-1][bj][0]==candy[bi+1][bj][0])
		return true;*/
	else 
		return false;
	
}
//------------------------------------------------------------------------------

bool contarI(int bi,int bj){
	
	if(candy[bi][bj][0]==candy[bi-1][bj-1][0] && candy[bi][bj][0]==candy[bi+1][bj-1][0])
		return true;
	if(candy[bi][bj-1][0]==candy[bi-1][bj][0] && candy[bi][bj-1][0]==candy[bi+1][bj][0])
		return true;
	
	
		
	int cont=1,cont2=1,cont3=1;
	
	//arriba
	for(int k=bi-1 ;k>=0;k--){
		if(candy[bi][bj][0]==candy[k][bj-1][0])
		cont++;
		else
		break;
	}
	///abajo
	for(int k2=bi+1;k2<9;k2++){
		if(candy[bi][bj][0]==candy[k2][bj-1][0])
		cont2++;
		else
		break;
	}
	
	//izquierda
	for(int k3=bj-2;k3>=0;k3--){
		if(candy[bi][bj][0]==candy[bi][k3][0])
		cont3++;
		else
		break;
	}
	
	if(cont>2 || cont2>2 || cont3>2)
		return true;/*
	else if(candy[bi][bj][0]==candy[bi-1][bj-1][0]==candy[bi+1][bj-1][0])
		return true;
	else if(candy[bi][bj-1][0]==candy[bi-1][bj][0]==candy[bi+1][bj][0])
		return true;*/
	else 
		return false;
	
}



//----------------------Intercambio----------------------------------------------

void intercambio(int bi,int bj, char dir) {
	//int hold=0;
	dir=toupper(getch());
    
	if (dir=='W' && bi!=0 && (contarW(bi,bj)==true || contarS(bi-1,bj)==true )){
	//cambio principal
	cambioW(bi,bj,0);
	//cambio de rallados 3 horizontales
	cambioW(bi,bj,3);
	//cambio de rallados 4 verticales
	cambioW(bi,bj,4);
	move--;
	
	}
    
	if (dir=='D' && bj!=8 && (contarD(bi,bj)==true || contarI(bi,bj+1)==true ) ){
	
	cambioD(bi,bj,0);
	cambioD(bi,bj,3);
	cambioD(bi,bj,4);
	move--;
	}
	if (dir=='S' && bi!=8 && (contarS(bi,bj)==true || contarW(bi+1,bj)==true ) ){
	
	cambioS(bi,bj,0);
	cambioS(bi,bj,3);
	cambioS(bi,bj,4);
	move--;
	
	}
	if (dir=='A' && bj!=0 && (contarI(bi,bj)==true || contarD(bi,bj-1)==true )){
		
	cambioA(bi,bj,0);
	cambioA(bi,bj,3);
	cambioA(bi,bj,4);
	move--;
	
	}
	
	//el beta de los rayados
	/*
	if(dir=='W' && bi!=0 && ( candy[bi][bj][3]!=0 || candy[bi][bj][4]!=0 ) && (candy[bi-1][bj][3]!=0 || candy[bi-1][bj][4]!=0) ){
	
		for(int i=0;i<9;i++){
			candy[bi-1][i][2]=3;
			candy[bi-1][i][5]=3;
			candy[i][bj][2]=3;
			candy[i][bj][5]=3;
			
			candy[bi][bj][0]=0;
			candy[bi][bj][3]=0;
			candy[bi][bj][4]=0;
			
			
		}
		move--;
		score+=5;
	}
	
	if(dir=='S' && bj!=8 && ( candy[bi][bj][3]!=0 || candy[bi][bj][4]!=0 ) && (candy[bi+1][bj][3]!=0 || candy[bi+1][bj][4]!=0) ){
	
		for(int i=0;i<9;i++){
			candy[bi+1][i][2]=3;
			candy[bi+1][i][5]=3;
			candy[i][bj][2]=3;
			candy[i][bj][5]=3;
			
			candy[bi][bj][0]=0;
			candy[bi][bj][3]=0;
			candy[bi][bj][4]=0;
		}
		move--;
		score+=5;
	}
		
	if(dir=='A' && bj!=0 && ( candy[bi][bj][3]!=0 || candy[bi][bj][4]!=0 ) && (candy[bi][bj-1][3]!=0 || candy[bi][bj-1][4]!=0) ){
		
		for(int i=0;i<9;i++){
			candy[bi][i][2]=3;
			candy[bi][i][5]=3;
			candy[i][bj-1][2]=3;
			candy[i][bj-1][5]=3;
			
			candy[bi][bj][0]=0;
			candy[bi][bj][3]=0;
			candy[bi][bj][4]=0;
		}
		move--;
		score+=5;
		
	}
	if(dir=='D' && bi!=8 && ( candy[bi][bj][3]!=0 || candy[bi][bj][4]!=0 ) && (candy[bi][bj+1][3]!=0 || candy[bi][bj+1][4]!=0) ){
		
		for(int i=0;i<9;i++){
			candy[bi][i][2]=3;
			candy[bi][i][5]=3;
			candy[i][bj+1][2]=3;
			candy[i][bj+1][5]=3;
			
			candy[bi][bj][0]=0;
			candy[bi][bj][3]=0;
			candy[bi][bj][4]=0;
			
		}
		move--;
		score+=5;
	}
	*/
	
}

//-----------------------------------------------------------------------------
void imprimir(int x){
	printf("\n\n\t     ");
	for(int i=0;i<9;i++){
	if(i==0){
        	SetColor(15);
        	for(int z=1;z<10;z++)
        	printf(" {%d} ",z-1);
        	printf("\n\t");
                	}
	for(int j=0;j<9;j++){
    
    	if(j==0){
    	SetColor(15);
        	printf(" {%d} ",i);
     	}
           	 
    	if(candy[i][j][0]==AZUL)
        	SetColor(9);
    	else if(candy[i][j][0]==NARANJA)
        	SetColor(14);
    	else if(candy[i][j][0]==MORADO)
        	SetColor(13);
    	else if(candy[i][j][0]==VERDE)
        	SetColor(10);
    	else if(candy[i][j][0]==GRIS)
        	SetColor(7);
    	else
        	SetColor(12);
   	 
             	 
    	if(candy[i][j][1]==1 && candy[i][j][3]!=4 && candy[i][j][4]!=4 )
        	printf(" [%c] ",candy[i][j][x]);//[] gelatina
   	 
    	else if(candy[i][j][1]==1 && candy[i][j][3]==4 )
        	printf("[-%c-]",candy[i][j][x]);
   	 
    	else if(candy[i][j][1]==1 && candy[i][j][4]==4)
        	printf("[!%c!]",candy[i][j][x]);
       	 
    	else if(candy[i][j][3]==4)
        	printf(" -%c- ",candy[i][j][x]);
    	else if(candy[i][j][4]==4)
        	printf(" !%c! ",candy[i][j][x]);
    	else
        	printf("  %c  ",candy[i][j][x]);	 
          	 
	}
    
	printf("\n\n\t");
	}
	SetColor(11);//color de las palabras.
}
//--------------------------------------------------------------------------
void cambiar(int i,int j,int cont,int x){
  	 

	int aux=candy[i-cont][j][x];
	candy[i][j][x]=aux;
	candy[i-cont][j][x]=0;
    
}

//--------------------------------------------------------------------------
void dezplazar(){
    
	for(int i=9;i>0;i--){
	for(int j=0;j<9;j++){
   	 
    	int cont=1,aux=0;//variables de cambio
   	 
    	if(candy[i][j][0]==0 && i>0 && i<9){//condicion de cambio y limites
       	 
        	for(int k=i-1;k>0;k--){
           	 
            	if(candy[k][j][0]==0)
            	cont++;//mientras encuentre espacios suma la cantidad de cambios
            	else
            	break;
           	 
        	}
       	 
        	if(cont>1){//condicion para cambio de multiples espacios en blanco
       	 
        	//cambio en los caramelos
        	cambiar(i,j,cont,0);
        	//cambio en los rayados verticales
        	cambiar(i,j,cont,4);
        	//cambio en los rayados horizontales
        	cambiar(i,j,cont,3);
       	 
       	 
        	}else if(candy[i][j][0]==0 && candy[i-1][j][0]!=0){//condicion de cambio para un unico espacio en blanco
            	//caramelos
            	cambiar(i,j,1,0);
            	//rayados verticales
            	cambiar(i,j,1,4);
            	//rayados horizontales
            	cambiar(i,j,1,3);
        	}
       	 
    	}//condicion de cambio y limites
   	 
   	 
   	 
    	}//for 2
	}//for 1
}//funcion

//----------------------------------------------------------------------

void comprobar(int azar[]){
	
	int bi=4, bj=4, x=0, y=0;
	char dir;
	int cont=0;
    
	for(int i=0;i<9;i++){
	for(int j=0;j<9;j++){
    
    	int filas=contar(i,j,'f');//cuenta si hay que borrar filas
    	int columnas=contar(i,j,'c');//cuenta si hay que borrar columnas
   	 
    	if(filas>2)
        	cont+=filas;//si hay se suman
    	if(columnas>2)
        	cont+=columnas;
   	 
	}//for i
	}//for j
    
    if (gelatina>0){
	if(cont==0){// si no pues juega.
    	 
    	system("cls");//limpia las impresiones previas
    	imprimir(0);//imprime los cambios
    	pintar_limites();
    	 
    	 
    	printf("\n\n Realize su movimiento \n");
        	seleccion (x,y);
        	printf ("\nIndique orientacion del intercambio.");
        	printf ("\nW=Arriba, D=Derecha, S=Abajo, A=Izquierda.");
        	printf ("\n");
        	intercambio(x, y, dir);
   	 
	}else{//si hay que borrar repite
   	 
    	limpiar();//limpia
    	dezplazar();//baja los caramelos
    	rellenar(azar);//rellena  la matriz
    	gelatinarestante();
		system("cls");//limpia las impresiones previas
    	imprimir(0);//imprime los cambios
    	pintar_limites();
    	
    	comprobar(azar);// comprueba si no hay variaciones
	}
    }
}


//-----------------------------GameOver---------------------------

void GAMEOVER(bool &gameover){
    
	int cont=gelatinarestante();
	
	if (cont==0 || move<=0)//si no hay gelatina ganas o pierdes.
    	gameover=true;
}
//-----------------------------------------------------------------------

main(){
	
	ventana();
	char jugarnuevamente='a';
	
	do{
	score=0;
	move=40;
	gelatina=81;
	extra();
	
	system("pause");
 	system("cls");

	int azar[6]={AZUL,NARANJA,MORADO,VERDE,GRIS,ROJO};
	bool gameover=false;
    
	SetColor(15);//color de las palabras solo al iniciar.
    
	
	//system("mode 650");
    
	generar(azar);//genera una matriz al azar
	imprimir(0);//imprime la matriz general
	pintar_limites();//borde del tablero
    
	//Sleep(5000);//frena los procesos 5 segundos
    
	printf("\n Su tablero inicial es :\n");
	system("pause");
	system("cls");
    
	while(gameover!=true){
	
    	comprobar(azar);
    	GAMEOVER(gameover);
   	 
	}
	
	system("cls");
	if(move>0 && gelatina==0){
		score+=move*10;
		pintar_limites2();
		gotoxy(20,8);
		printf("Felicitaciones ");
		for(int i=0;i<3;i++){
			printf("%c",name[i]);
		}
		 printf(" has ganado! con una puntuacion de %i. \n",score+scoreg);
		
		
	}else{
		
		pintar_limites2();
		gotoxy(20,6);
		
		printf(" Juego Terminado! ");
		for(int i=0;i<3;i++){
			gotoxy(20+i,8);
			printf("%c",name[i]);
		}
		 printf(" has perdido! con una puntuacion de %i   ",score+scoreg);
		 gotoxy(20,9);
		 printf("y con tan solo %i gelatinas restantes.",gelatina);		
	}
	
	do{
	gotoxy(32,12);	
	printf(" Desea jugar nuevamente? S=Si y N=No.");
	gotoxy(25,14);
	scanf(" %c",&jugarnuevamente);
	}while(jugarnuevamente!='N' && jugarnuevamente!='n' && jugarnuevamente!='s' && jugarnuevamente!='S');
	
	}while(jugarnuevamente!='N' && jugarnuevamente!='n');

system("pause");
}
