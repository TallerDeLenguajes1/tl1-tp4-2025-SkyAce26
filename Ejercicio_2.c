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
void cargarListaTareasPendientes(Nodo **TareasPendientes);

int main(){
    Nodo *TareasPendientes;
    Nodo *TareasRealizadas;
    
    //Inicializo las listas
    
    crearLista(&TareasPendientes);
    crearLista(&TareasRealizadas);

    cargarListaTareasPendientes(&TareasPendientes);

    return 0;
}

void crearLista(Nodo **lista){
    *lista = NULL;
}

void cargarListaTareasPendientes(Nodo **TareasPendientes){
    int agregarTarea=0;
    char descripcionTarea[100];
        int i=1;

    while(agregarTarea!=1){ 
        Nodo *aux = (Nodo*)malloc(sizeof(Nodo));
        //Cargo el id de la tarea:
        aux->T.TareaID = 1000+ i;
        i++;
        aux->Siguiente = NULL;
        
        getchar();
        //Cargo la descripcion de la tarea:
        printf("Ingrese la descripcion de la tarea pendiente:\n");
        gets(descripcionTarea);
        
        int longitud = strlen(descripcionTarea);
        aux->T.Descripcion = (char*)malloc(longitud*sizeof(char)+1);
        strcpy(aux->T.Descripcion, descripcionTarea);

        //Cargo la duracion de la tarea:
        printf("Ingrese la duracion de la tarea pendiente (entre 10 y 100):\n");
        scanf("%d", &aux->T.Duracion);
        
        aux->Siguiente = *TareasPendientes;
        *TareasPendientes = aux;

        printf("Quiere ingresar una nueva tarea? \n0-Si.\n1-No.\n");
        scanf("%d", &agregarTarea);

    }
}