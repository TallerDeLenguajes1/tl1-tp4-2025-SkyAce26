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
void transferirATareasRealizadas(Nodo **TareasPendientes, Nodo** TareasRealizadas);
void mostrarListaDeTareas(Nodo *ListaTareas);
void consultarTarea(Nodo *pendientes, Nodo *realizadas);
void liberarLista(Nodo **lista);

int main(){
    Nodo *TareasPendientes;
    Nodo *TareasRealizadas;
    
    //Inicializo las listas
    
    crearLista(&TareasPendientes);
    crearLista(&TareasRealizadas);

    cargarListaTareasPendientes(&TareasPendientes);
    transferirATareasRealizadas(&TareasPendientes, &TareasRealizadas);

    printf("\nTareas pendientes:\n");
    mostrarListaDeTareas(TareasPendientes);

    printf("\nTareas realizadas:\n");
    mostrarListaDeTareas(TareasRealizadas);

    consultarTarea(TareasPendientes, TareasRealizadas);
    
    liberarLista(&TareasPendientes);
    liberarLista(&TareasRealizadas);

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

void transferirATareasRealizadas(Nodo **TareasPendientes, Nodo** TareasRealizadas){
    int idTarea;
    printf("Ingrese el id de la tarea que quiere pasar a la lista de tareas realizadas:\n");
    scanf("%d", &idTarea);
    Nodo**Aux=TareasPendientes;
    
    
    while(*Aux && (*Aux)->T.TareaID != idTarea){

        Aux = &(*Aux)->Siguiente;
    }

    if (*Aux) {
        Nodo *mover = *Aux;
        *Aux = (*Aux)->Siguiente;
        
        mover->Siguiente = *TareasRealizadas;
        *TareasRealizadas = mover;
        printf("Tarea %d movida a realizadas.\n", idTarea);
    }else{
        printf("Tarea no encontrada.\n");
    }

}

void mostrarListaDeTareas(Nodo *ListaTareas){
    Nodo*Aux=ListaTareas;

    while(Aux!=NULL){
        printf("ID: %d\n", Aux->T.TareaID);
        printf("Descripcion: %s\n", Aux->T.Descripcion);
        printf("Duracion: %d\n", Aux->T.Duracion);
        printf("-------------------\n");

        Aux = Aux->Siguiente;
    }
}

void consultarTarea(Nodo *pendientes, Nodo *realizadas) {
    int opcion;
    printf("¿Cómo desea buscar la tarea?\n");
    printf("1. Por ID\n");
    printf("2. Por palabra clave\n");
    scanf("%d", &opcion);
    getchar();

    if (opcion == 1) {
        int id;
        printf("Ingrese el ID de la tarea:\n");
        scanf("%d", &id);

        Nodo *aux = pendientes;
        while (aux) {
            if (aux->T.TareaID == id) {
                printf("\nTarea encontrada en la lista pendientes:\n");
                printf("ID: %d\nDescripcion: %sDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                return;
            }
            aux = aux->Siguiente;
        }

        aux = realizadas;
        while (aux) {
            if (aux->T.TareaID == id) {
                printf("\nTarea encontrada en la lista realizadas:\n");
                printf("ID: %d\nDescripcion: %sDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                return;
            }
            aux = aux->Siguiente;
        }

        printf("No se encontró ninguna tarea con ese ID.\n");

    } else if (opcion == 2) {
        char palabra[100];
        printf("Ingrese palabra clave para buscar en la descripción:\n");
        gets(palabra);

        int encontrada = 0;

        Nodo *aux = pendientes;
        while (aux) {
            if (strstr(aux->T.Descripcion, palabra)) {
                printf("\nTarea encontrada en pendientes:\n");
                printf("ID: %d\nDescripcion: %sDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
            aux = aux->Siguiente;
        }

        aux = realizadas;
        while (aux) {
            if (strstr(aux->T.Descripcion, palabra)) {
                printf("\nTarea encontrada en realizadas:\n");
                printf("ID: %d\nDescripcion: %sDuración: %d\n", aux->T.TareaID, aux->T.Descripcion, aux->T.Duracion);
                encontrada = 1;
            }
            aux = aux->Siguiente;
        }

        if (!encontrada) {
            printf("No se encontró ninguna tarea con esa palabra clave.\n");
        }

    } else {
        printf("Opción inválida.\n");
    }
}

void liberarLista(Nodo **lista){
    Nodo *actual = *lista;
    Nodo *temp;

    while (actual != NULL) {
        temp = actual;
        actual = actual->Siguiente;

        if (temp->T.Descripcion != NULL) {
            free(temp->T.Descripcion);
        }

        free(temp); // Liberar el nodo
    }

    *lista = NULL;
}