#include<mpi.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>   
#include<math.h>   


int arreglo[100000],tam=10000;

// Se crea un arreglo con numeros random
void Llenar_arreglo(){
    int largo = 100000;
    int hora = time(NULL);
    srand(hora);
    for(int i = 0; i<largo; i++){
        arreglo[i] = rand()%100;
        }
}

// Se crea un subvector que contendra los otros vectores 
int* crear_subVector(int inicio, int fin, int* origen){
    int* sub_vec;
    int size;
    int contador = 0;
    size = fin - inicio;
    sub_vec = (int*)malloc(size * sizeof(int));
    for (int i = inicio; i < fin; ++i) {
        *(sub_vec+contador) = *(origen+i);
        contador += 1;
    }
    return  sub_vec;
}

// Se saca los promedios de los subvectores
float subPromedio(int *sub_vector, int largo){
	int *s = sub_vector;
        float promedio;
        float suma;
        for(int i = 0; i < largo; i++) {
                suma+= *s;
                s++;
        }
        promedio = suma/largo;

        return promedio;
}

// Se calcula la varianza del promedio total
float varianza(int vector[],float promArreglo){
    float var;
    for(int i=0; i<=tam; i++){
        var+=pow(vector[i]-promArreglo,2);
	var = var/promArreglo;
    }    
    return var;
}

// Se muestra los subvectores y los promedios de cada sub vector
void print(int my_rank, int comm_sz, int n_over_p, int* sub_vec){
    printf("Process %d out of %d received subvector: [ ", my_rank, comm_sz);
    for (int i = 0; i < n_over_p; ++i)
    {
        printf("%d, ", *(sub_vec+i));	
    }
    printf("]\n");
    float prom = subPromedio(sub_vec,n_over_p);
    printf("Del procesador %d el promedio es %f\n",my_rank,prom);
    printf("\n");

}

int main(void){

    int comm_sz; // numero de procesos
    int my_rank; // rango del proceso

    int* sub_vec = NULL;
    int* total = NULL;
    int n_over_p; 
    float recv_promedio; // Promedio general de los subvectores recibidos 

    MPI_Init(NULL, NULL); // Inicializamos MPI 
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz); //nunero de procesos que se estan ejecutando
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank); //rango del proceso 

    n_over_p = 20/comm_sz; // cantidad en la que se divide el vector

    if (my_rank != 0) { //procesadores distintos del 0
	sub_vec = (int*)malloc(n_over_p * sizeof(int));//espacio para recibir subvectores
        MPI_Recv(sub_vec, n_over_p, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);//recibe subvector

        print(my_rank, comm_sz, n_over_p, sub_vec);

	float recv_promedio = subPromedio(sub_vec,n_over_p); //Se calcula el subpromedio de los subvectores
        MPI_Send(&recv_promedio,1,MPI_FLOAT,0,0,MPI_COMM_WORLD);//Se envía el arreglo con los subpromedio al Proceso 0
        	

    } else {  //Procesador 0 

  	Llenar_arreglo(); // Se llena el arreglo	

        for (int i = 1; i < comm_sz; i++) {
            sub_vec = crear_subVector(i*n_over_p, (i*n_over_p)+n_over_p, arreglo);
            MPI_Send(sub_vec, n_over_p, MPI_INT, i, 0, MPI_COMM_WORLD);  //Se envia los subvectores a los  procesos
        }

        sub_vec = crear_subVector(0, n_over_p, arreglo);//Se generan los subvectores a enviar
	float subProm=subPromedio(sub_vec,n_over_p);

        for(int i=1; i<comm_sz; i++) {
        	float recibeProm = recv_promedio;
        	MPI_Recv(&recibeProm,1,MPI_FLOAT,i,0,MPI_COMM_WORLD,MPI_STATUS_IGNORE); //Se reciben los promedios de subvectores
        	subProm += recibeProm; //Se suman los subpromedios
	} 
	
	print(my_rank, comm_sz, n_over_p, sub_vec);

	float promTotal=(subProm/comm_sz); //Se calcula el promedio total de los subpromedios recibidos 
	printf("El Promedio total es: %f\n", promTotal); 
	printf("La Varianza es: %f\n", varianza(arreglo,promTotal));
	float desvEstandar = sqrt(varianza(arreglo,promTotal));
	printf("La desviacion estandar es: %f\n", desvEstandar); 
    }

    MPI_Finalize();
    return 0;

}

