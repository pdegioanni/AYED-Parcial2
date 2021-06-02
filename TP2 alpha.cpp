#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#define TAMANIO 1000


using namespace std;

//VARIABLES GLOBALES
int comp;//cantidad de comparaciones
int N; //orden del monticulo

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
	//Atributo
	Nodo<T>* czo;
public:
    //Constructores
	Lista() { czo = new Nodo<T>(); };
    Lista(Nodo<T>* n) { czo = n; };
    //Metodos
	void agregar(T d); //Agrega a la cabeza de la lista
    bool listaVacia(){ return czo -> nodoVacio();}; //true si no hay mas elementos en la lista
    T cabeza(); //Devuelve ultimo elemento agregado
	T ultimo(); //Devuelve primer elemento agregado
    Lista* resto(); //Devuelve la misma lista sin la cabeza
    int tamanio(); //Devuelve la cantidad de elementos en la lista
    void borrar(void); //borra la cabeza
    void borrarUltimo();//borra el ultimo
    void imprimirLista(int sentido); //Imprime lista. Si sentido = 0, imprime LIFO. Si sentido = 1, imprime FIFO
    void invertir(Lista* l1); //Invierte los valores de la lista
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


//CLASE NODO PALABRA
//es el tipo de nodo que va formando la heap

class NodoPal { 
	private:
    //Atributos
		string palabra; //Palabra del nodo
    	NodoPal* padre; //link a nodo padre
    	Lista<NodoPal*>* hijos; //links a nodos hijos. Se enlazan a medida que se agregan hijos
    	Cola<int>* colaNodo; //Indica la cantidad de nodos hijos disponibles para enlazar
    	//int repetidas; //Cantidad de repeticiones de la palabra (no se usa por cambio en el enunciado)
    //Metodos	
		NodoPal* buscarHijo(Lista<NodoPal*>* aux, int i); //Devuelve el hijo en la posicion i de la lista
	
	public:
    //Constructor
	    NodoPal(string p) { 
			palabra = p; 
			padre = NULL; 
			hijos = new Lista<NodoPal*>(); //Los hijos se van agregando a la lista a medida que son conocidos
			colaNodo = new Cola<int>();
			for(int i=0; i<N; i++){ colaNodo -> encolar(i);} //Arma una cola con la cantidad de hijos "disponibles" para enlazar
			//repetidas = 0; //(no se usa por cambio en el enunciado)
		};
	//Setters
	    void setPadre(NodoPal* p) { padre = p; }; //Enlaza nodo padre
	    void setHijo(NodoPal* h) { // Enlaza nodo hijo
			hijos -> agregar(h);
			colaNodo -> desencolar();
		};
		void setPalabra(string nuevaPalabra){palabra=nuevaPalabra;} //Cambia la palabra que contiene el nodo
	    //void aumentarRepetidas(){ repetidas ++;}; //Aumenta cantidad de repetidas (no se usa por cambio en el enunciado)
	//Getters
	    string getPalabra() { return palabra; }; //Devuelve la palabra almacenada
	    NodoPal* getPadre() { return padre; }; //Devuelve la direccion del nodo padre
	    NodoPal* getHijo(int i){return buscarHijo(hijos, i);}; //Devuelve la direccion del hijo numero i
	    //int getRepetidas(){ return repetidas;} //(no se usa por cambio en el enunciado)
	//Otros metodos
	    bool tieneLugar() { return !colaNodo -> colaVacia(); } //true si quedan hijos aun no enlazados
	    bool tienePadre(){return !(padre==NULL);}; //true si tiene enlazado un nodo padre
	    NodoPal* getMayorHijo(); //Devuelve la direccion del nodo hijo que contenga la mayor palabra
	    void borrarHijo(); //Elimina el ultimo hijo agregado
};

NodoPal* NodoPal::buscarHijo(Lista<NodoPal*>* aux, int i){
	if(aux != NULL){
		if(i<0 || i>=N )return NULL;
		else if(i== 0){ return aux -> ultimo();} //Devolver hijo mas a la izquierda(primero agregado)
		else if(i == N-1){return aux -> cabeza();}; //Devolver hijo mas a la derecha (ultimo agregado) 
		return buscarHijo(aux -> resto(), i+1);
	}
	else return NULL; 
}

NodoPal* NodoPal:: getMayorHijo(){
	NodoPal* mayor = getHijo(0);
	NodoPal* temp;
	if(mayor != NULL) {
		for(int i = N; i>=1; i--){
			temp = getHijo(i);
			if(temp != NULL && (temp -> getPalabra() > mayor -> getPalabra())) {
				mayor = temp;
			}
		}
		return mayor;
	}
	else return NULL; 
}

void NodoPal:: borrarHijo(){
	if(!hijos -> listaVacia()){
		hijos -> borrar(); 
	}
}

//DECLARACION DE FUNCIONES 
Cola<string>* leerTxt();
void preguntarN();
void armarHeap(string palabra);
void escribirHeapOrdenada();
void imprimirHeap(NodoPal* raiz, int n);
void escribirArchivo();

//DECLARACION DE ESTRUCTURAS AUXILIARES PARA ORDENAR
Cola<NodoPal*>* heapIncompleto = new Cola<NodoPal*>();//Cola auxiliar para construir la heap
Lista<NodoPal*>* heapCompleto = new Lista<NodoPal*>(); //Lista que contendra la heap una vez creada
Pila<string>* pilaOrdenada = new Pila<string>(); //Pila que contendra los datos ordenados


//CLASE PRINCIPAL
int main(){
	//Primera Parte: procesamiento del archivo de entrada
	preguntarN();
	Cola<string>* colaPalabras = leerTxt(); //Carga el archivo y genera una cola con las palabras a ordenar
	/*cout<<"Palabras del archivo sin ordenar:\n" <<endl;
	colaPalabras -> imprimirCola();
	cout<< "--------------------------------------------"<<endl<<endl;*/
	
	//Segunda parte: armado de la heap
	while(!(colaPalabras -> colaVacia())){
		armarHeap(colaPalabras -> prox());
		colaPalabras -> desencolar();
	}
	
	//Si despues de agregar todas las palabras, quedaron nodos sin hijos asignados, 
	//se los agrega a heapCompleto para que- queden todos los nodos en un solo heap
	while(!heapIncompleto -> colaVacia()){ 
		heapCompleto -> agregar(heapIncompleto -> prox());
		heapIncompleto -> desencolar();
	}
	
	//Imprime heap en consola (solo para heap binario)
	//imprimirHeap(heapCompleto -> ultimo(), 0);
	
	//Tercera parte: Armar pila ordenada de palabras en base al sorting de la heap
	while(!heapCompleto -> listaVacia()){
		escribirHeapOrdenada();
	}
	//heapIncompleto -> imprimirCola(); //Debe quedar vacio
	
	//Cuarta parte: Imprimir resultados y generar archivo de salida
	escribirArchivo();
}

//FUNCION LECTOR DE ARCHIVO
Cola<string>* leerTxt(){
	Cola<string> *c = new Cola<string>();
	
	ifstream archivo;
  	string linea;
	//archivo.open("palabras.txt");
	//archivo.open("abecedario.txt");
	archivo.open("texto.txt");
	
	if(!archivo){
		cout<< "No se puede abrir el archivo"<<endl;
		exit(1);
	}
	
	while (archivo >> linea) {
        c -> encolar(linea); //Se van encolando las palabras del archivo
    }
    return c;
    archivo.close();
}

//FUNCION CARGAR ORDEN DE HEAP
//Solicita ingresar el orden de la heap y comprueba si es un numero natural
void preguntarN(){
  	cout <<"Ingrese el orden del monticulo: ";
	cin >> N;
  	while(N <=0) {
  		cout <<"El valor ingresado no es un numero natural. Ingrese el orden del monticulo: ";
		cin >> N;
	}
}

//FUNCION ARMAR HEAP CON PALABRAS
//Recibe las palabras de la cola de palabras y las va agregando a la heap
void armarHeap(string palabra){
	//Se crea nuevo nodo con la palabra recibida
	NodoPal* nuevoNodo = new NodoPal(palabra);
	NodoPal* nodoPadre;
	string palabraPadre;
	
	//Se agrega el nuevo nodo a la estructura, vinculandolo al nodo padre que corresponda en orden
	if(heapIncompleto -> colaVacia()){ //Si es el primer nodo ingresado se deja como padre NULL, indicando que es raiz	
		nuevoNodo -> setPadre(NULL); 
		heapIncompleto -> encolar(nuevoNodo);
	} 
	else{ //Si no es el primer nodo agregado
		heapIncompleto -> encolar(nuevoNodo);
		nodoPadre = heapIncompleto -> prox(); //Se toma el siguiente nodo que todavia no tiene sus hijos seteados
		
		if(!(nodoPadre -> tieneLugar())){ // Si siguiente no tiene mas lugar para agregar un hijo,
			heapCompleto -> agregar(nodoPadre); // se agrega a la lista de nodos con todos sus hijos completos
			heapIncompleto -> desencolar();  //Se elimina de la cola de nodos con hijos disponibles 
			nodoPadre = heapIncompleto -> prox(); // Se toma el siguiente en la cola	
		}
		
		//Se agrega nuevo nodo como hijo del primer nodo en la cola que "tenga lugar"
		nuevoNodo -> setPadre(nodoPadre);
		nodoPadre -> setHijo(nuevoNodo);
		palabraPadre = nodoPadre -> getPalabra();
		
	//Se intercambian valores con el nodo recien agregado hasta que valga la condicion de heap	
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
}

//FUNCION ARMAR PILA ORDENADA DE PALABRAS
//Arma una pila de palabras ordenadas con las palabras de la heap
void escribirHeapOrdenada(){
	if(heapCompleto -> tamanio() == 2) { //Si solo quedan dos elementos, los apila directamente
		pilaOrdenada -> apilar(heapCompleto -> ultimo() -> getPalabra());
		pilaOrdenada -> apilar(heapCompleto -> cabeza() -> getPalabra());
		heapCompleto -> borrar();
		heapCompleto -> borrar();
	}
	else{
		//Agrega a la pila el valor de la raiz actual de la heap
		NodoPal* nodoRaiz = heapCompleto -> ultimo();
		pilaOrdenada -> apilar(nodoRaiz-> getPalabra());
		
		//Carga en la posicion raiz el valor del ultimo nodo
		string ultimaPalabra = heapCompleto -> cabeza() -> getPalabra();
		nodoRaiz -> setPalabra(ultimaPalabra); 
		
		//Elimiina el ultimo dato de la heap (cabeza de la lista)
		if(heapCompleto -> cabeza() -> tienePadre()){
			heapCompleto -> cabeza() -> getPadre() -> borrarHijo();//Se elimina el link con el nodo padre
		}
		heapCompleto -> borrar();
		
		//El valor recien insertado en la raiz se "empuja" hacia abajo hasta que se cumpla la condicion de heap
		//Se lo va intercambiando sucesivamente con el hijo que tenga la palabra mas grande
		NodoPal * mayorHijo = nodoRaiz -> getMayorHijo();
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
		//Paso a paso en consola (para heap binario)
		/*	cout<<endl<<"----------------------------------"<<endl;
			imprimirHeap(heapCompleto -> ultimo(), 0);*/
	}
	
}

//FUNCION IMPRIMIR HEAP BINARIO
//Imprime el heap en consola en forma de arbol (solo para heap binario)
void imprimirHeap(NodoPal* raiz, int n){ 
	NodoPal* hijoDer;
	NodoPal* hijoIzq;
	
	if(raiz != NULL){
		hijoDer = raiz -> getHijo(N-1);
		hijoIzq = raiz -> getHijo(0);
		if(hijoDer  != hijoIzq) imprimirHeap(hijoDer, n+1);
		for(int i=1; i<=n; i++) cout<<"       ";
		cout<< raiz -> getPalabra()<<endl;
		imprimirHeap(hijoIzq, n+1);
	}
};

//FUNCION ESCRIBIR ARCHIVO DE TEXTO
//Imprime los datos de la cola en un archivo de texto
void escribirArchivo(){
	cout<<"\n\n-------------------- Resultados ---------------------------- "<< endl;
	cout<<"Palabras del archivo ordenadas alfabeticamente: "<< endl;
	pilaOrdenada -> imprimirPila(); //Imprime salida en consola para pruebas
	ofstream archivoOrdenado;//se declara el archivo
	archivoOrdenado.open("SalidaOrdenada.txt",ios::out); //crea archivo de texto y le asigna la funcion de escribir
	
	if(archivoOrdenado.fail()){
		cout<<"No se pudo abrir el archivo para escribir.";
		exit(1);
	}
	//Se "imprimen" los datos recibidos de pilaOrdenada en el archivo creado
	string palabra = pilaOrdenada -> tope();
	pilaOrdenada ->desapilar();
	
	string siguiente;
	int repeticiones = 0;
	
	while(!pilaOrdenada->pilaVacia()){
		siguiente = pilaOrdenada -> tope();
		while(siguiente == palabra){
			repeticiones ++;
			pilaOrdenada ->desapilar();
			if(!pilaOrdenada -> pilaVacia()) siguiente = pilaOrdenada -> tope();
			else break;
		}
		archivoOrdenado<< palabra << " - "<< repeticiones << " repeticiones"<<endl;
		palabra = siguiente;
		repeticiones = 0;
		pilaOrdenada ->desapilar();
	}
	
	cout<<"Cantidad de comparaciones: "<<comp<<endl;
	archivoOrdenado<<endl<< "Cantidad de comparaciones: "<<comp<<endl;
		archivoOrdenado.close();
}
