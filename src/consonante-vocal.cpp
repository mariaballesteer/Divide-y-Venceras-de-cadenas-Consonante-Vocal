#include <iostream>
#include <stdio.h>
#include <time.h>
#include <cstring>

#include <time.h>
#include <sys/time.h>
#include <fstream>

using namespace std;

//primer ejemplo usado:
//const char A[] = {'a','b','c','c','a','b','e','a','d','d','e','d','a','d','e','b','d','a','e'};

//tamaño estándar de la entrada
const int N = 170000;
//Array
char * A;

ofstream cMejor, cPeor, cTodos;

const int minimo = 10000;
const int maximo = 210000;


bool esVocal (int i){
    switch (A[i]){
        case ('a'):
        case ('e'):
        case ('i'):
        case ('o'):
        case ('u'):
            return true;
            break;
        default :
            return false;
    }
}

pair<int,int> solucionDirecta(int p, int q){
    if(!esVocal(p) && esVocal(q))
        return {p,q};
    else
        return {0,0};
}

int dividir(int p, int q) {
    return int((q+p)/2);
}

pair<int,int> cadMLarga(pair<int,int> s1, pair<int,int> s2){
    if((s1.second-s1.first) >= (s2.second-s2.first))
        return s1;
    else
        return s2;
}

pair<int,int> extenderDer(pair<int,int> s1){
    int x = s1.second;
    while((x+2 <= strlen(A)-1) && solucionDirecta(x+1,x+2) != pair{0,0})
        x += 2;
    return {s1.first,x};
}

pair<int,int> extenderIzq(pair<int,int> s2){
    int x = s2.first;
    while((x-2 >= 0) && solucionDirecta(x-2,x-1) != pair{0,0})
        x -= 2;
    return {x,s2.second};
}

pair<int,int> cadFrontera(int p, int q, int m){
    pair<int,int> s3 = {m,m+1};
    s3 = extenderIzq(s3);
    s3 = extenderDer(s3);
    return s3;
}

pair<int,int> combinar(pair<int,int> s1, pair<int,int> s2, int p, int q, int m) {
    if(solucionDirecta(m,m+1) == pair{0,0})
        return cadMLarga(s1,s2);
    
    else{
        if(s1.second == m){
            if(s2.first == m+1){
                return {s1.first,s2.second};
            }
            else{
                s1 = extenderDer(s1);
                return cadMLarga(s1,s2);
            }
        }
        else{
            if(s2.first == m+1){
                s2 = extenderIzq(s2);
                return cadMLarga(s1,s2);
            }
            else{
                pair<int,int> s3 = cadFrontera(p,q,m);
                pair<int,int> s4 = cadMLarga(s1,s2);
                return cadMLarga(s3,s4);
            }
        }
    }
    return {0,0};
}

pair<int,int> DyV(int p, int q) {
    if (p == q)
        return {0,0};
    else if (q - p == 1)
        return solucionDirecta(p,q);
    else {
        
        int m = dividir(p,q);
        pair<int,int>s1 = DyV(p,m);
        pair<int,int>s2 = DyV(m+1,q);
        return combinar(s1,s2,p,q,m);
    }
}

char * generadorEntrada(int n) {
    char * cadena = new char[n];
    for(int i = 0; i < n; i++) {
        cadena[i] = (char) (97 + rand() % (122 - 97 + 1));
    }                  
    return cadena;
}

// todo consonante-vocal
char * generadorEntradaPeor(int n)
{
    char * cadena = new char[n];
    for(int i = 0; i < n; i++)
    {
        if(i%2 == 0){
            cadena[i] = 'b';
        }
        else{
            cadena[i] = 'a';
        }
    }
   
    return cadena;
}

// que nunca se cumpla el patrón
char * generadorEntradaMejor(int n)
{
    char * cadena = new char[n];
    for(int i = 0; i < n; i++)
    {
        cadena[i] = 'a';
    }
   
    return cadena;
}

void imprimirSol (pair<int,int> solucion){
    if(solucion == pair{0,0})
        cout << "No hay cadenas consonante-vocal de ninguna longitud" << endl;
    else{
        cout << "La solución es ";
        for(int i = solucion.first; i <= solucion.second; i++){
            cout << A[i];
        }
        cout << " en la posición " << solucion.first + 1 << endl;
    }
}

void imprimirArray (){
    for(int i = 0; i < strlen(A); i++){
        cout << A[i];
    }
    cout << endl;
}

string obtenerTiempo(int p, int q) {
    struct timeval t1, t2;
    double tiempo;
    gettimeofday(&t1, NULL);
    pair<int, int> solucion = DyV(p,q);
    gettimeofday(&t2, NULL);
    tiempo = (t2.tv_sec - t1.tv_sec)*1000 + (t2.tv_usec -t1.tv_usec)/1000.0;
    string t = "";
    string cadenaTiempo = to_string(tiempo);
    for(int h = 0; h < cadenaTiempo.length(); h++)
    {
        if(cadenaTiempo[h] != '.')    
            t = t + cadenaTiempo[h];
        else t = t + ',';
    }
    return t;
}



void archivosCSV()
{
    cTodos.open("data/todos.csv");
    cPeor.open("data/peor.csv");
    cMejor.open("data/mejor.csv");


    int p,q,m;
    cMejor << "n;tm(n)" << endl;
    cPeor << "n;tM(n)" << endl;
    cTodos << "n;tM(n);tm(n)" << endl;
	for(int n = minimo; n <= maximo; n+=10000)
    {
        // generacion de la entrada aletoria para una n dada
        p = 0; 
        q = n - 1;
        A = generadorEntradaPeor(n);
        string tM = obtenerTiempo(p,q);
        A = generadorEntradaMejor(n);
        string tm = obtenerTiempo(p,q);

        m = n/1000;
        
        
        // añade al fichero csv la n usada y los milisegundos que ha tardado el algoritmo (direfencia entre t1 y t2)
        cTodos << n << ";" << tM << ";" << tm << endl;
        cMejor << n << ";" << tm << endl;
        cPeor << n << ";" << tM << endl;

    }

}

int main(){

    srand(time(NULL));

    // llama al generador de casos
    // lee el fichero y lo va metiendo en un array de caracteres a la vez que cuenta 
    cout << "¿Qué desea hacer? (introduzca el número de la opción)" << endl;
    cout << "1 - Analizar un número a indicar de arrays" << endl;
    cout << "2 - Producir datos sobre el tiempo que se guardarán en un archivo .csv" << endl;
    cout << "3 - Ayuda" << endl;

    int opcion;
    cin >> opcion;
    if (opcion == 1){
        int c;
        cout << "Introduzca el número de cadenas que quiere analizar" << endl;
        cin >> c;
        int array;
        cout << "¿Quiere saber cuáles son los arrays? (1 = SI; 0 = NO)" << endl;
        cin >> array;
        for (int i = 0; i < c; i++){
            cout << i+1 << "-";
            A = generadorEntrada(N);
            if (array == 1){
                imprimirArray();
            } 
            int p = 0;
            int q = strlen(A)-1;
            pair<int,int> solucion = DyV(p,q);
            imprimirSol(solucion);
        }
    }
    else if(opcion == 2) {
        archivosCSV();
    }
    else {
        cout << "1 - Se generará de manera aleatoria un array de caracteres (alfabeto únicamente) que se analizará a través de un algoritmo basado en \"Divide y Vencerás\" para comprobar cuál es la subcadena más larga que cumpla con el patrón consonante-vocal. Usted determinará el número de cadenas a analizar." << endl;
        cout << "2 - Se hará un estudio del tiempo sobre dos tipos de entradas: el peor caso y el mejor. Insertará los datos en archivos .csv, es decir, en hojas de cálculo." << endl;
    }
    
    return 0;

}