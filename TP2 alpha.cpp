#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define TAMANIO 1000


using namespace std;
//string palabras[TAMANIO]; //aca se copian los valores leidos del txt 

//VARIABLES GLOBALES
int comp;//cantidad de comparaciones
int N; //orden del monticulo
//typedef string Palabra;
//CLASE NODO
//Clase secundaria para definir la lista
template <class T> class Nodo { 
	private:
    	T dato;
    	Nodo* next;
	public:
    //Constructores
    	Nodo() { next = NULL; };
    	Nodo(T a) { dato = a; next = NULL; };
	//Setters
    	void setDato(T a) { dato = a; };
    	void setNext(Nodo* n) { next = n; };
	//Getters
    	T getDato() { return dato; };
    	Nodo* getNext() { return next; };
    	bool nodoVacio() { return next == NULL; }
};

//CLASE LISTA
//Secundaria para crear cola y pila
template <class T> class Lista {
private: 
	Nodo<T>* czo;
public:
    Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    void agregar(T d);
    bool listaVacia(void){ return czo -> nodoVacio();};
    T cabeza(void);
	T ultimo(void);
    Lista* resto(void);
    void borrar(void); //borra la cabeza
    void borrarUltimo();//borra el ultimo
    void imprimirLista(int sentido);
    void invertir(Lista* l1);
};

template <class T> void Lista<T>::agregar(T d){
    Nodo<T>* nuevo = new Nodo<T>(d); //crea un nuevo nodo para almacenar el dato
    nuevo -> setNext(czo); // setea la dirección del nodo al último elemento que se había agregado a la lista
    czo = nuevo; //setea el comienzo de la lista a la dirección del nodo nuevo
}

template <class T> T Lista<T>::cabeza(void){
    if (listaVacia()) return NULL;
    return czo->getDato();
}

template <class T> T Lista<T>::ultimo(void){
	Lista<T>* aux = this;
    if (listaVacia()) return NULL;
	while(!((aux -> resto()) ->listaVacia())){
		aux = aux -> resto();
	}
    return aux -> cabeza();
}

template <class T> Lista<T>* Lista<T>::resto(void){
    Lista* l = new Lista (czo->getNext()); //El czo de la lista actual tiene la dirección del segundo elemento
    return (l);
}

template <class T> void Lista<T>::borrar(){
	if(!this.listaVacia){
		Nodo<T>* tmp = czo; 
		czo = czo ->getNext(); //(borrado lógico)
		delete tmp; //libera la memoria del nodo borrado (borrado físico)
	}
}

template <class T> void Lista<T>::borrarUltimo(){
	Nodo<T>* penultimo = czo;
	Nodo<T>* ultimo = penultimo -> getNext();
	if(!this -> listaVacia()){	
		while(!ultimo ->nodoVacio()){
			penultimo = ultimo;
			ultimo = ultimo -> getNext();
		}
		delete ultimo;
		penultimo -> setNext(NULL);
	}
};

template <class T> void Lista<T>::imprimirLista(int sentido){ 
    Lista<T>* aux;
	if (listaVacia()) cout<<"Vacio "<<endl;
	else if(sentido == 0){ //Imprime la lista como pila (de ultimo a primero)
		aux = this;
	}
	else if(sentido == 1){ //Imprime la lista como cola (de primero a ultimo)
		aux = new Lista();
		aux -> invertir(this);
	}
	else return;
	while(!((aux -> resto())->listaVacia())){
		cout << aux -> cabeza()<<endl;
		aux = aux -> resto();
	}
	cout<< aux -> cabeza() << "\n";
}

template <class T> void Lista<T>::invertir(Lista* l1){//
	if(!l1->listaVacia()){
		this -> agregar(l1->cabeza()); 
		this -> invertir(l1 -> resto());
	}
}

//CLASE COLA
template <class T> class Cola :public Lista<T> {
	public:
	    Cola(void) { Lista<T>(); };
	    Cola(Lista<T> lista){};
	    void encolar(T a) { this->agregar(a); };
	    void desencolar(void) { this->borrarUltimo(); };
	    T prox() {return this-> ultimo(); };
	    T ult() { return this->cabeza(); };
	    bool colaVacia(void) { return this->listaVacia(); };
	    void imprimirCola(){return this -> imprimirLista(1);};
};

//CLASE PILA
template <class T> class Pila:public Lista<T>{
	public:
		Pila(){Lista<T>();};
    	void apilar(T d){this->agregar(d);};
    	T tope(void){return this->cabeza();};
    	void desapilar(void){this->borrar();};
    	bool pilaVacia(){return this->listaVacia();};
    	void imprimirPila() { this -> imprimirLista(0); };
};                  


//void inserta(struct nodo*insercion,struct nodo*elemento);
//void imprime(struct nodo *p);
//void borra(struct nodo *p);*/

//DECLARACION DE FUNCIONES 
Cola<string>* leerTxt();
void preguntarN();
void testImprimirPalabras();
void armarHeap(string palabra);
void ordenarHeap();
void escribirHeapOrdenada();
//void crearCola(nodoPalabra *&padre *&hijos[]);


//CLASE PRINCIPAL
int main(){
	preguntarN();
	Cola<string>* colaPalabras = leerTxt(); //Carga el archivo y genera una cola con las palabras a ordenar
	//cout<<"Palabras del archivo sin ordenar:\n" <<endl;
	colaPalabras -> imprimirCola();
	
	/*cout<< "Primero "<< colaPalabras -> prox()<<endl<<endl;
	cout<< "Ultimo "<< colaPalabras -> ult()<<endl;
	colaPalabras -> imprimirCola();
	
	colaPalabras -> desencolar();
	
	cout<< "Primero "<< colaPalabras -> prox()<<endl;
	cout<< "Ultimo "<< colaPalabras -> ult()<<endl;
	colaPalabras -> desencolar();*/
	
	while(!(colaPalabras -> colaVacia())){
		armarHeap(colaPalabras -> prox());
		//cout << "Primero "<< colaPalabras -> proximo()<<endl;
		colaPalabras -> desencolar();
	}
	
  	//struct nodo *raiz,*temp;
  	//raiz=NULL;
  	//int numeroDeHijos;
  	//string palabras[TAMANIO];
  

	//numeroDeHijos= preguntarN();
	
	//cout<<"el numero de n sera:"<<N;
	//testImprimirPalabras();

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

//FUNCION LECTOR DE TEXTO

Cola<string>* leerTxt(){
	//string palabras[TAMANIO];//deberia ir en main creo
	//string nombreArchivo="palabras.txt";
	Cola<string> *c = new Cola<string>();
  	
	string linea;
	ifstream archivo;
	archivo.open("prueba.txt");
	
	if(!archivo){
		cout<< "No se puede abrir el archivo"<<endl;
		exit(1);
	}
	
	//int i=0;
	while (archivo >> linea) {
        // pasamos las palabras del archivo hacia el arreglo palabras habria que pasarlos a una cola de string
        //palabras[i]=linea;
        c -> encolar(linea);
        //c->imprimirCola();
    }
    return c;
    archivo.close();
    //return palabras[string];
}


/*void testImprimirPalabras(){
	//palabras[1000]="vacio LPM";
	for(int i=0;i<TAMANIO;i++)
	{
		//cout<<palabras[i]<<endl;
	}
}*/

void preguntarN(){
 //solicita ingresar el numero de hijos y comprueba si la rta es correcta (chequear porque no funciona cuando no es un num)
  //N=-1;
  	cout <<"Ingrese el orden del monticulo: ";
	cin >> N;
  	while(N <=0) {
  		cout <<"El valor ingresado no es un numero natural. Ingrese el orden del monticulo: ";
		cin >> N;
	}
  	//cout <<"Se usara un monticulo de orden "<< N<<endl;
	//return ;*/
}
//CLASE NODO PALABRA
//es el tipo de nodo que va formando la heap

class NodoPal { 
	private:
    	string palabra;
    	NodoPal* padre;
    	NodoPal* hijos[];
    	int repetidas;
    	Cola<NodoPal*>* colaNodo; 
	public:
    //Constructores
	    NodoPal(string p) { 
			palabra = p; 
			padre = NULL; 
			repetidas = 0;
			colaNodo = new Cola<NodoPal*>();
			for(int i=N; i>0; i--){
				hijos[i] = NULL;
				colaNodo -> encolar(hijos[i]);
			}
		};
	//Setters
	    //void set_dato(T a) { dato = a; };
	    void setPadre(NodoPal* p) { padre = p; };
	    void setHijo(NodoPal* h, int i) {
			hijos[i] = h;
			colaNodo -> desencolar();
		};
	    void aumentarRepetidas(){ repetidas ++;};
	//Getters
	    string getPalabra() { return palabra; };
	    int getRepetidas(){ return repetidas;}
	    NodoPal* getPadre() { return padre; };
	    NodoPal* getHijo(int i){return hijos[i];}
	    bool tieneLugar() { return colaNodo -> colaVacia(); }
};
/*struct nodoPalabra{
       palabra dato;
       int contador; // 
       nodoPalabra *padre;
       nodoPalabra* hijos[TAMANIO];//se define un arreglo de nodos de 1000
       int indice;//para ubicar nodo en la cola 
};*/
//typedef nodoPalabra * pnodo;
/*struct nodo
{
  string nombre;
  int contador;
  struct nodo *izq,*der,*padre; //hay q implementar para n links
};

class arbol{
	/*
    pnodo raiz;
    void Insert(int x, bool &aumento, nodoPalabra* &A);
    void show(pnodo aux, int n);
    void recorerIRD(nodoPalabra* &A);

    
public:
    arbol(){raiz=NULL;};
    ~arbol(){};
    void CreaArbol(palabra x);
    void VerArbol(){ show(raiz,0); }
};*/

void armarHeap(string palabra ){

	cout<< "Armando heap con palabra: "<< palabra << endl;
 /*nodoPalabra *padre;
 nodoPalabra *hijos[n];
 
 
 for(int i=0 ; i<TAMANIO;i++)
 {
 nodoPalabra *nuevaPalabra = new (nodoPalabra);
 nuevaPalabra->dato=palabras[i];
 //if(false)*/
  
  
 
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
