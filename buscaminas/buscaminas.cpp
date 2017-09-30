#include<iostream>
#include<stdlib.h>
#include<time.h>
using namespace std;
int rellenar(int **most,int **A,int n,int m){//rellena inicialmente la matriz segun ubicacion de las bombas
    //-1 es bomba
    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            int x=0;
                if(A[i][j]!=-1){
                if(i-1>=0 and j-1>=0 and A[i-1][j-1]==-1)x++;
                if(i-1>=0 and A[i-1][j]==-1)x++;
                if(j-1>=0 and A[i][j-1]==-1)x++;
                if(i+1<n and j+1<m and A[i+1][j+1]==-1)x++;
                if(i+1<n and A[i+1][j]==-1)x++;
                if(j+1<m and A[i][j+1]==-1)x++;
                if(j-1>=0 and i+1<n and A[i+1][j-1]==-1)x++;
                if(j+1<m and i-1>=0 and A[i-1][j+1]==-1)x++;
                A[i][j]=x;
		most[i][j]=x;
            }
        }
    }
}
int bfs(int **A,bool **mascara,int x,int y,int tam1,int tam2){//recorre las celdas adaycentes
    mascara[x][y]=true;
    if(x-1>=0 and A[x-1][y]>0 and not mascara[x-1][y]){
        mascara[x-1][y]=true;
    }
    if(x+1<tam1 and A[x+1][y]>0 and not mascara[x+1][y]){
        mascara[x+1][y]=true;
    }
    if(y-1>=0 and A[x][y-1]>0 and not mascara[x][y-1]){
        mascara[x][y-1]=true;
    }
    if(y+1<tam2 and A[x][y+1]>0 and not mascara[x][y+1]){
        mascara[x][y+1]=true;
    }
    if(x-1>=0 and A[x-1][y]==0 and not mascara[x-1][y]){
        bfs(A,mascara,x-1,y,tam1,tam2);
    }
    if(x+1<tam1 and A[x+1][y]==0 and not mascara[x+1][y]){
        bfs(A,mascara,x+1,y,tam1,tam2);
    }
    if(y-1>=0 and A[x][y-1]==0 and not mascara[x][y-1]){
        bfs(A,mascara,x,y-1,tam1,tam2);
    }
    if(y+1<tam2 and A[x][y+1]==0 and not mascara[x][y+1]){
        bfs(A,mascara,x,y+1,tam1,tam2);
    }
    return 0;
}
bool impresion(int **A,bool **mascara,int tam1,int tam2,int p1,int p2){//imprime una matriz
    cout<<"\a"<<endl;
    system("cls");
    for(int i=0;i<tam1;i++){
        for(int j=0;j<tam2;j++){
	    if(i==p1 and j==p2){cout<<'@';}
	    else if(mascara[i][j]){
                if(A[i][j]==-1)cout<<"*";
                else cout<<A[i][j];
            }
	    else{cout<<"?";}
	    cout<<" ";
        }cout<<endl;
    }
    cout<<endl<<endl;;
}
bool recorrer(int **A,bool **mascara,int a,int b,int tam1,int tam2){//recorre la matriz
    for(int i=0;i<tam1;i++){
    	for(int j=0;j<tam2;j++){
		if(mascara[i][j] and A[i][j]==-1){return false;}
	}
    }
    if(A[a][b]==0)bfs(A,mascara,a,b,tam1,tam2);
    impresion(A,mascara,tam1,tam2,a,b);
    return true;
}
bool primo(int a){//saber si un numero es primo
	bool t=true;
	for(int i=2;i<a;i++)t=t and not (a%i==0);
	return t;
}
int aleatorio(int **A,int a,int b,int i,int j,int &k){//determina numeros aleatorios a partir de primos
	while(not primo(k))k++;
	srand(k);
	if(rand()%(a*b)+1<=(30*a*b)/(256))A[i][j]=-1;
	else A[i][j]=0;
}
int semilla(){//primer valor que inicializara el random
	srand(time(NULL));
	int k=rand();
	while(k<30){srand(time(NULL));k=rand();}
	k=k%1000;
	return k;
}
int creator_mat(int **most,int **matriz,int a,int b){//crea matrices
    for(int i=0;i<a;i++){
        *(matriz+i)=new int[b];
	*(most+i)=new int [b];
    }
    int k=semilla();
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            aleatorio(matriz,a,b,i,j,k);
	    most[i][j]=matriz[i][j];
	    k++;
        }
    }
    rellenar(most,matriz,a,b);
}
int creator_mask(bool **mascara,int a,int b){//crea una matriz de booleanos
    for(int i=0;i<a;i++){
        *(mascara+i)=new bool[b];
    }
    for(int i=0;i<a;i++){
            for(int j=0;j<b;j++){
                mascara[i][j]=false;
            }
    }
}
bool develar(int **matriz,bool **mascara,int x,int y,int a,int b){//revela los valores de la matriz de a pocos
	mascara[x][y]=true;
	if(not recorrer(matriz,mascara,x,y,a,b))return false;
	return true;
}
void mostrar(int **A,int a,int b){//muestra toda la matriz
    cout<<"\a"<<endl;
    system("cls");
	for(int i=0;i<a;i++){
		for(int j=0;j<b;j++){
			if(A[i][j]!=-1)cout<<A[i][j];
			else cout<<'*';
			cout<<" ";
		}
		cout<<endl;
	}
}
int contar_bool(bool **mask,int a,int b){
    int x=0;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++)x+=mask[i][j];
    }
    return x;
}
bool mov(int **A,int **matriz,bool **mascara,int x,int y,int a,int b,int c){//movimiento de arroba
	char r;
	cin>>r;
	if(x>0 and r=='w') x--;
	else if(x<a-1 and r=='s') x++;
	else if(y<b-1 and r=='d') y++;
	else if(y>0 and r=='a') y--;
	if(r=='o'){
		if(not develar(matriz,mascara,x,y,a,b)){
			mostrar(A,a,b);
			cout<<"PERDISTE"<<endl;
			return false;
		}
	}
	else {impresion(matriz,mascara,a,b,x,y);}
	int d=contar_bool(mascara,a,b);
	if(d==c){mostrar(A,a,b);cout<<"GANASTE"<<endl;return 0;}
	return mov(A,matriz,mascara,x,y,a,b,c);
}
int borrar(int **A,int a,int b){//borra matriz de enteros
	for(int i=0;i<a;i++){
		delete []A[i];
	}
	delete[]A;
	return 0;
}
int borrar(bool **A,int a,int b){//borra matriz de booleanos
	for(int i=0;i<a;i++){
		delete []A[i];
	}
	delete[]A;
	return 0;
}
int cuenta(int **A,int a,int b){
    int x=0;
    for(int i=0;i<a;i++){
        for(int j=0;j<b;j++){
            if(A[i][j]==-1)x++;
        }
    }
    return a*b-x;
}
int main(){
    int a,b;
    cout<<"w:arriba\n"<<"s:abajo\n"<<"a:izquierdo\n"<<"d:derecha\n"<<"o:mostrar\n";
    cout<<"ingrese las dimensiones"<<endl;
    cin>>a>>b;
    int **most=new int*[a];
    int **matriz=new int*[a];
    bool **mascara=new bool*[a];
    creator_mat(most,matriz,a,b);
    creator_mask(mascara,a,b);
    impresion(matriz,mascara,a,b,0,0);
    mov(most,matriz,mascara,0,0,a,b,cuenta(most,a,b));
    borrar(matriz,a,b);
    borrar(mascara,a,b);
    borrar(most,a,b);
    return 0;
}
