#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

using namespace std;

void llenar_arreglo(int b[], int largo){
    srand(time(NULL));
    for(int i=0; i<largo; i++){
        b[i]= 1 + rand()% 100;   
    }
    cout<<"arreglo creado."<<endl;
}

void mostrar_arreglo(int b[], int largo){
    for(int i=0;i<largo;i++){
       cout<<b[i]<<" "; 
    }
    cout<<endl;
}

float promedio_arreglo(int b[], int largo){
    float c=0;
    for (int i=0; i<largo; i++){
        c+=b[i]; 
    }
    float promedio=(c/largo);
    return promedio;
}

float varianza_arreglo(int b[], int largo){
    float promedio= promedio_arreglo( b, largo);
    float var=0;
    for (int i=0; i<largo; i++){
        var+=pow(b[i]-promedio,2.0)/(largo-1);
    }
    return var;
}

float desviacion_arreglo(int b[], int largo){
    return sqrt(varianza_arreglo(b, largo));
}

int main() {
    int largo=100000;
    int arreglo[largo];
    
    llenar_arreglo(arreglo, largo);
    mostrar_arreglo(arreglo,largo);
    cout<<"El promedio es: "<<promedio_arreglo(arreglo,largo)<<endl;
    cout<<"La varianza es: "<<varianza_arreglo(arreglo,largo)<<endl;
    cout<<"La desviacion estandar es: "<<desviacion_arreglo(arreglo,largo)<<endl;
    return (EXIT_SUCCESS);
}
