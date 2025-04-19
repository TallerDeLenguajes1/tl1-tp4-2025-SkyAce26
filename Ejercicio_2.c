#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tarea{
    int TareaID;//Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion; // entre 10 – 100
}Tarea;

typedef struct Nodo{
    Tarea T;
    struct Nodo *Siguiente;
}Nodo;

void crearLista(Nodo **lista);


int main(){
    Nodo *TareasPendientes;
    Nodo *TareasRealizadas;
    
    //Inicializo las listas
    
    crearLista(&TareasPendientes);
    crearLista(&TareasRealizadas);


    return 0;
}

void crearLista(Nodo **lista){
    *lista = NULL;
}