#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define TAMANIO 1000

using namespace std;
string palabras[TAMANIO]; //aca se copian los valores leidos del txt 

/*struct nodo
{
  string nombre;
  int contador;
  struct nodo *izq,*der,*padre; //hay q implementar para n links
};

void inserta(struct nodo*insercion,struct nodo*elemento);
void imprime(struct nodo *p);
void borra(struct nodo *p);*/



//FUNCION LECTOR DE TEXTO

void leerTxt()
{
	//string palabras[TAMANIO];//deberia ir en main creo
	//string nombreArchivo="palabras.txt";
  ifstream archivo("palabras.txt");
	string linea;
	int i=0;
	while (getline(archivo, linea)) {
        // pasamos las palabras del archivo hacia el arreglo palabras habria que pasarlos a una cola de string
        palabras[i]=linea;
        i++;
    }
    //return palabras[string];
}

//CLASE PILA reutilizada sobre un areglo

template <class T> class Pila{

		T d[TAMANIO]; 
		int p; //Posicion de la cabeza de la pila
	public:
		Pila() {p = -1 ;};
		T tope(void) { return d[p]; };
		void desapilar(void) {if(!this -> pila_vacia()) --p;}; 
		bool pila_vacia() {return p == -1;};
		int tamanio(){return p;};
		void vaciar_pila(){
			while(!this -> pila_vacia()){
				this -> desapilar();
			}
		}
	
};

//CLASE COLA reutilizada sobre un arreglo

template <class T> class Cola{

		T d[TAMANIO]; 
		int p; //Posicion del primer elemento que ingresa a la cola (mas proximo a salir)
		int u; //Posicion del ultimo elemento que ingreso a la cola (ultimo en salir)
		int n; // indica la cantidad de elementos que hay en la cola
	public:
		Cola() { p = 0 ; u = -1; n = 0;};
		
		void encolar(T x) {
			if(n< TAMANIO){
				n++; //Suma 1 a la cantidad de elementos
				if(u==(TAMANIO-1)) u=-1; //Si es el final del arreglo, vuelve a cargar en el principio
				d[++u] = x; //Agrega elemento a la derecha 
			}
			else cout<<"Error, no hay mas lugar en la cola"<<endl; 
		}
		void desencolar(void) {
			if(!this -> colavacia()){  
				n--; 
				if(p == (TAMANIO-1)) p = -1; //Si llegua al final del arreglo, vuelve al principio
				p++;  
			}
			else cout<<"Error, cola vacia"<< endl;
		};
		T primero(void) {if(!this -> colavacia()) return d[p];}; 
		T ultimo(void) {if(!this -> colavacia()) return d[u];};
		bool colavacia() {return n == 0;};
		
	};



//DECLARACION DE FUNCIONES 

void leerTxt();
int preguntarN();
void testImprimirPalabras();
void armarHeap(int n );
void ordenarHeap();
void escribirHeapOrdenada();
//void crearCola(nodoPalabra *&padre *&hijos[]);
//CLASE PRINCIPAL
int main()
{
  int contadorC;
  int numeroDeHijos;
  struct nodo *raiz,*temp;
  raiz=NULL;
  string palabras[TAMANIO];
  

	numeroDeHijos= preguntarN();
	cout<<"el numero de n sera:"<<numeroDeHijos;
	leerTxt();
	testImprimirPalabras();

  /*printf("Teclea nombres, seguido por un caracter no numerico\n");
  do{   
    gets(name);
    getchar();
    {
      temp=(struct nodo*)malloc(sizeof(struct nodo));
      temp->der=NULL;
      temp->izq=NULL;
      strcpy(temp->nombre,name);
      if(raiz==NULL)
      {
        raiz=temp;
      }
      else
      {
        inserta(raiz,temp);
      }
    }
  }

  printf("Listo\n");
  printf("Nombres impresos en orden\n");
  imprime(raiz);
  borra(raiz);
}

void inserta(struct nodo*insercion, struct nodo*elemento)
{
  struct nodo*avanza,*nuevo;

  avanza=insercion;

  if(avanza!=NULL)
  {
    if(strcmp(elemento->nombre,avanza->nombre)>0)
    {
      if(avanza->der!=NULL)
      {
        inserta(avanza->der,elemento);
      }
      else
      {
        avanza->der=elemento;
        return;
      }
    }
    if(strcmp(elemento->nombre,avanza->nombre)<=0)
    {
      if(avanza->izq!=NULL)
      {
        inserta(avanza->izq,elemento);
      }
      else
      {
        avanza->izq=elemento;
        return;
      }
    }
  }*/
}


void testImprimirPalabras()
{
	//palabras[1000]="vacio LPM";
	for(int i=0;i<TAMANIO;i++)
	{
		cout<<palabras[i]<<endl;
	}
}

int preguntarN()
{
	  //solicita ingresar el numero de hijos y comprueba si la rta es correcta (chequear porque no funciona cuando no es un num)
 
  int n=-1;
  while(n<=0 ||n==NULL ||isdigit(n)){
  	cout <<"Ingrese el numero de n: ";
	cin >>n;
	//if(!isdigit(n)){n=-1;}
  	}
	return n;
}


//CLASE NODO

typedef string palabra;
struct nodoPalabra{
       palabra dato;
       int contador; // 
       nodoPalabra *padre;
       nodoPalabra* hijos[TAMANIO];//se define un arreglo de nodos de 1000
       int indice;//para ubicar nodo en la cola
       
};
typedef nodoPalabra * pnodo;
class arbol{
    pnodo raiz;
    void Insert(int x, bool &aumento, nodoPalabra* &A);
    void show(pnodo aux, int n);
    void recorerIRD(nodoPalabra* &A);

    
public:
    arbol(){raiz=NULL;};
    ~arbol(){};
    void CreaArbol(palabra x);
    void VerArbol(){ show(raiz,0); }
};

void armarHeap(int n )
{
 nodoPalabra *padre;
 nodoPalabra *hijos[n];
 
 
 for(int i=0 ; i<TAMANIO;i++)
 {
 nodoPalabra *nuevaPalabra = new (nodoPalabra);
 nuevaPalabra->dato=palabras[i];
 //if(false)
  }
  
 
 //crearCola(nodoPalabra *&padre *&hijos[])	
 //	nodoPalabra heap
}

void ordenarHeap(){}


void escribirHeapOrdenada(){}

/*void crearCola(nodoPalabra *&padre*&hijos)
{
	palabraNodo *nuevaCola= new palabraNodo();
	
}*/
/*template <class T> class nodo {
public:
    T info;
    nodo* padre;
    nodo* hijos[TAMANIO];//se define un arreglo de nodos de 1000;
    int contador
};

template <class T> class arbol {
private:
    nodo<T>* raiz, * q;
    void ArbolBusq(T x, nodo<T>*& nuevo);
   // void rid(nodo<T>* aux);
    void ird(nodo<T>* aux);
   // void idr(nodo<T>* aux);
   // void show(nodo<T>* aux, int n);

public:
    arbol() { raiz = NULL; };
    ~arbol() {};
    void CreaArbolBus(T x);
    void RID() { rid(raiz); }
    void IRD() { ird(raiz); }
    void IDR() { idr(raiz); }
   // void VerArbol() { show(raiz, 0); }

};*/
