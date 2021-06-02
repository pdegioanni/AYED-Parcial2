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
    int tamanio();
    void borrar(void); //borra la cabeza
    void borrarUltimo();//borra el ultimo
    void imprimirLista(int sentido);
    void invertir(Lista* l1);
    void setDatoCabeza(T a){czo -> setDato(a);};
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
    if(czo->getNext() != NULL){
		Lista* l = new Lista (czo->getNext()); //El czo de la lista actual tiene la dirección del segundo elemento
    	return (l);
	}
    else return NULL;
}

template <class T> int Lista<T>::tamanio(){
	int i = 0;
  	Lista* l = this;
  	while(!l->listaVacia()){
    	i++;
    	l= l -> resto();
    }
  	return i;  
  }

template <class T> void Lista<T>::borrar(){
	if(!listaVacia()){
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
	while(!aux -> resto()->listaVacia()){
		cout << aux -> cabeza()<<endl;
		aux = aux -> resto();
	}
	cout<< aux->cabeza() << "\n";
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
	    Cola() { Lista<T>(); };
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

//CLASE NODO PALABRA
//es el tipo de nodo que va formando la heap

class NodoPal { 
	private:
    	string palabra;
    	NodoPal* padre;
    	//NodoPal* hijos[];
    	int repetidas;
    	Lista<NodoPal*>* hijos;
    	Cola<int>* colaNodo;
		NodoPal* buscarHijo(Lista<NodoPal*>* aux, int i); 
	public:
    //Constructores
	    NodoPal(string p) { 
			palabra = p; 
			padre = NULL; 
			repetidas = 0;
			hijos = new Lista<NodoPal*>(); //Los hijos se van agregando a la lista a medida que son conocidos
			colaNodo = new Cola<int>();
			for(int i=0; i<N; i++){
				//hijos[i] = NULL;
				//hijos ->agregar(NULL); 
				//cout<<i<<endl;
				colaNodo -> encolar(i); //Arma una cola con la cantidad de hijos "disponibles" para enlazar
			}
		};
	//Setters
	    //void set_dato(T a) { dato = a; };
	    void setPadre(NodoPal* p) { padre = p; };
	    void setHijo(NodoPal* h) {
			hijos -> agregar(h);
			colaNodo -> desencolar();
		};
		void setPalabra(string nuevaPalabra){palabra=nuevaPalabra;}
	    void aumentarRepetidas(){ repetidas ++;};
	//Getters
	    string getPalabra() { return palabra; };
	    int getRepetidas(){ return repetidas;}
	    NodoPal* getPadre() { return padre; };
	    NodoPal* getHijo(int i){return buscarHijo(hijos, i);}; 
	    //NodoPal* getHijo(int i){return hijos[i];}
	//Otras funciones
	    bool tieneLugar() { return !colaNodo -> colaVacia(); }
	    bool tienePadre(){return !(padre==NULL);};
	    NodoPal* getMayorHijo();
	    void borrarHijo();
};

NodoPal* NodoPal::buscarHijo(Lista<NodoPal*>* aux, int i){
	if(aux != NULL){
		//cout<<"F"<< aux -> tamanio() <<endl;
			if(i<0 || i>=N || i>= aux -> tamanio()){
		//cout<< "No existe el hijo "<< i<<endl;
		return NULL;	
	} 
	else if(i== 0){ return aux -> ultimo();} //Devolver hijo mas a la izquierda(primero agregado)
	else if(i == N-1){
		return aux -> cabeza(); //Devolver hijo mas a la derecha (ultimo agregado)
	} 
	else return buscarHijo(aux -> resto(), i+1);
	}
}

NodoPal* NodoPal:: getMayorHijo(){
	NodoPal* mayor = getHijo(0);
	/*if(hijos -> tamanio()==1){
		mayor = hijos -> cabeza();
	}
	else{*/
	if(mayor != NULL) {
		for(int i = N; i>=1; i--){
			if(getHijo(i) != NULL && (getHijo(i) -> getPalabra()> mayor -> getPalabra())) mayor = getHijo(i);
			//else{cout<<"Hijo "<<i<<" null";}
		}
	//}
	//buscarHijo(hijos, 0);	
		//cout<<"mayor "<<mayor<<endl;
		//cout<<"MAYOR "<<mayor<<endl;
		return mayor;
	}
	else return NULL; 
}

void NodoPal:: borrarHijo(){
	if(!hijos -> listaVacia()){
		hijos -> borrar(); //Elimina el ultimo hijo agregado
	}
}

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
};*/

//DECLARACION DE FUNCIONES 
Cola<string>* leerTxt();
void preguntarN();
void testImprimirPalabras();
void armarHeap(string palabra);
void escribirHeapOrdenada();
void imprimirHeap(NodoPal* raiz, int n);

//void crearCola(nodoPalabra *&padre *&hijos[]);



//CLASE PRINCIPAL

Cola<NodoPal*>* heapIncompleto = new Cola<NodoPal*>();//Cola auxiliar para construir la heap
//Cola<NodoPal*>* heapCompleto = new Cola<NodoPal*>();
Lista<NodoPal*>* heapCompleto = new Lista<NodoPal*>(); //Lista que contendra la heap una vez creada
//Pila<NodoPal*>* pilaOrdenada = new Pila<NodoPal*>(); //Pila que contendra los datos ordenados
Pila<string>* pilaOrdenada = new Pila<string>(); //Pila que contendra los datos ordenados


int main(){
	preguntarN();
	Cola<string>* colaPalabras = leerTxt(); //Carga el archivo y genera una cola con las palabras a ordenar
	/*cout<<"Palabras del archivo sin ordenar:\n" <<endl;
	colaPalabras -> imprimirCola();
	cout<< "--------------------------------------------"<<endl<<endl;*/
	while(!(colaPalabras -> colaVacia())){
		armarHeap(colaPalabras -> prox());
		colaPalabras -> desencolar();
	}
	//Si despues de agregar todas las palabras, quedaron nodos sin hijos asignados, 
	//se los agrega a heapCompleto para que- queden todos los nodos en un solo heap
	
	heapIncompleto -> desencolar();
	while(!heapIncompleto -> colaVacia()){ 
		//cout<< "Se agrega palabra sin hijos a heap completo: "<< heapIncompleto -> prox() -> getPalabra() <<endl;//dps borrar, solo para chequear
		//heapCompleto -> encolar(heapIncompleto -> prox());
		heapCompleto -> agregar(heapIncompleto -> prox());
		heapIncompleto -> desencolar();
	}
	
	//imprimirHeap(heapCompleto -> ultimo(), 0);
	
	//cout<<"a ver \n"<<endl;
	//heapCompleto -> imprimirLista(0);
	
	//Ordenar heap
	while(!heapCompleto -> listaVacia()){
		escribirHeapOrdenada();
	}
	/*string f = heapCompleto -> cabeza()-> getPalabra();
	cout<<"Volvi al main"<<endl;
	pilaOrdenada -> apilar(f);*/
	
	cout<<"Palabras del archivo ordenadas alfabeticamente: "<< endl;
	
	pilaOrdenada -> imprimirPila();
	/*Pila<string>* p = new Pila<string>();
	p -> apilar("w");
	//p -> apilar("c");
	cout << p -> tamanio();*/
	
	cout<<"Cantidad de comparaciones: "<<comp;
	//heapIncompleto -> imprimirCola(); //Debe quedar vacio
	//heapCompleto -> imprimirCola();
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

void armarHeap(string palabra){
	NodoPal* nuevoNodo = new NodoPal(palabra);
	NodoPal* nodoPadre;
	string palabraPadre;
	
	//Se agrega el nodo a la estructura, vinculandolo al nodo padre que corresponda en orden
	if(heapIncompleto -> colaVacia()){ //Si es el primer nodo ingresado se deja como padre NULL, indicando que es raiz	
		nuevoNodo -> setPadre(NULL); 
		heapIncompleto -> encolar(nuevoNodo);
	} 
	else{ //Si no es el primer nodo agregado
		heapIncompleto -> encolar(nuevoNodo);
		nodoPadre = heapIncompleto -> prox(); //Se toma el siguiente nodo que todavia no tiene sus hijos seteados
		
		if(!(nodoPadre -> tieneLugar())){ // Si siguiente no tiene mas lugar para agregar un hijo,
			//heapCompleto -> encolar(nodoPadre); // se agrega a la cola de nodos con todos sus hijos completos
			heapCompleto -> agregar(nodoPadre); // se agrega a la cola de nodos con todos sus hijos completos
			heapIncompleto -> desencolar();  //Se elimina de la cola de nodos con hijos disponibles 
			nodoPadre = heapIncompleto -> prox(); // Se toma el siguiente en la cola	
		}
		
		//Se agrega nuevo nodo como hijo del primer nodo en la cola que "tenga lugar"
		nuevoNodo -> setPadre(nodoPadre);
		nodoPadre -> setHijo(nuevoNodo);
		palabraPadre = nodoPadre -> getPalabra();
		
		comp ++;
		while(palabra >= palabraPadre && nuevoNodo -> tienePadre()){
			comp ++;
			nuevoNodo -> setPalabra(palabraPadre);
			nodoPadre -> setPalabra(palabra);	
			//Recalcula el nodo padre
			nuevoNodo = nodoPadre;
			if(nuevoNodo -> getPadre() == NULL) break;
			else {
				nodoPadre = nuevoNodo -> getPadre();
				palabraPadre = nodoPadre -> getPalabra();
			}
		}
	} 
	
	//cout<< "A la palabra hija "<< palabra << " se la vincula con palabra padre "<< palabraPadre <<endl;
		
	
	
					
	/*if(nuevoNodo ->getPalabra() > siguiente ->getPalabra()){
		cout<<"se esta intentando ordenar";
		buscaPadre= nodoPadre;
		while(buscaPadre -> tienePadre()){
			string temp = nuevoNodo ->getPalabra();
			nuevoNodo ->getPalabra()= buscaPadre ->getPalabra();
			buscaPadre ->setPalabra(temp);	
		}
							
	}*/
	//Cola<int>* c = new Cola<>();
	//cout<< "Armando heap con palabra: "<< palabra << endl;
	
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

//void ordenarHeap(){}


void escribirHeapOrdenada(){
	if(heapCompleto -> tamanio() == 2) {
		//cout<<"ultimo con "<< heapCompleto -> ultimo() -> getPalabra() <<endl;
		pilaOrdenada -> apilar(heapCompleto -> ultimo() -> getPalabra());
		pilaOrdenada -> apilar(heapCompleto -> cabeza() -> getPalabra());
		heapCompleto -> borrar();
		heapCompleto -> borrar();
	}
	else{
		//cout<<"valor de raiz "<<heapCompleto -> ultimo() -> getPalabra()<<endl;
		NodoPal* nodoRaiz = heapCompleto -> ultimo();
		pilaOrdenada -> apilar(nodoRaiz-> getPalabra());//Agrega a la pila el valor de la raiz
		
		string ultimaPalabra = heapCompleto -> cabeza() -> getPalabra();
		nodoRaiz -> setPalabra(ultimaPalabra); //Carga en la primera posicion el valor del ultimo nodo
		
		//Elimiina el ultimo dato de la heap (cabeza de la lista)
		
		//else pilaOrdenada -> apilar(heapCompleto -> ultimo() -> getPalabra());
		heapCompleto -> borrar();
		
		NodoPal * mayorHijo = nodoRaiz -> getMayorHijo();
		//cout<<"Hijo mayor "<< mayorHijo <<endl; 
		string palabraHijo = mayorHijo -> getPalabra();
		
		comp ++;
		while(palabraHijo > ultimaPalabra && nodoRaiz -> getMayorHijo()!= NULL){
			comp ++;
			nodoRaiz -> setPalabra(palabraHijo);
			mayorHijo -> setPalabra(ultimaPalabra);	
			//Recalcula el hijo mayor
			nodoRaiz = mayorHijo;
			if(nodoRaiz -> getMayorHijo() == NULL) break;
			else {
				mayorHijo = nodoRaiz -> getMayorHijo();
				palabraHijo = mayorHijo -> getPalabra();
			}
		}
		//cout<<"vuelta ----------------------------"<<endl;
		//imprimirHeap(heapCompleto -> ultimo(), 0);
		if(heapCompleto -> cabeza() -> tienePadre()){
			heapCompleto -> cabeza() -> getPadre() -> borrarHijo();//Se elimina el link con el nodo padre
		}
		//if(heapCompleto -> tamanio()==1) cout<<"ultimo";
	}
	
}

void imprimirHeap(NodoPal* raiz, int n){ //Por ahora solo sirve para heap binario
	if(raiz != NULL){
		imprimirHeap(raiz -> getHijo(N-1), n+1);
		for(int i=1; i<=n; i++) cout<<"       ";
		cout<< raiz -> getPalabra()<<endl;
		imprimirHeap(raiz -> getHijo(0), n+1);
	}
};


