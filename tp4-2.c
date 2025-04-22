#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct
{
    Tarea T;
    Nodo *Siguiente;
} Nodo;

Nodo *IniciarListaVacia();
Nodo *CrearNodo(Tarea *nuevaTarea, int *id);
void InsertarNodo(Nodo **inicio, Nodo *NNodo);
///
int main()
{
    srand(time(NULL));

    Nodo *start = IniciarListaVacia();

    Tarea *nuevaTarea;
    int id = 999;
    InsertarNodo(&start, CrearNodo(nuevaTarea, &id));

    free(nuevaTarea->Descripcion);

    return 0;
}

Nodo *IniciarListaVacia()
{
    return NULL;
}

Nodo *CrearNodo(Tarea *nuevaTarea, int *id)
{
    char buff[200];
    printf("Crear una nueva tarea \n");
    printf("Ingrese una descripción de la tarea: \n");
    fgets(buff, 200, stdin);
    buff[strcspn(buff, "\n")] = '\0'; // Eliminar salto de linea

    nuevaTarea->TareaID = *id + 1;
    nuevaTarea->Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    nuevaTarea->Duracion = rand() % 91 + 10;

    Nodo *Tnodo = (Nodo *)malloc(sizeof(Nodo));
    Tnodo->T = *nuevaTarea;
    Tnodo->Siguiente = NULL;

    return Tnodo;
}

void InsertarNodo(Nodo **inicio, Nodo *NNodo)
{
    NNodo->Siguiente = *inicio;
    *inicio = NNodo;
    
}
