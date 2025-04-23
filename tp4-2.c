#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct Tarea
{
    int TareaID;       // Numérico autoincremental comenzando en 1000
    char *Descripcion; //
    int Duracion;      // entre 10 – 100
} Tarea;

typedef struct Nodo Nodo;
typedef struct Nodo
{
    Tarea T;
    Nodo *Siguiente;
}Nodo;



Nodo *IniciarListaVacia();
Nodo *CrearNodo(Tarea nuevaTarea);
void InsertarNodo(Nodo **inicio, Nodo *NNodo);
void MostrarTarea(Nodo *TNodo);
///
int main()
{
    srand(time(NULL));

    Nodo *start = IniciarListaVacia();
    int id = 999;
    Tarea nuevaTarea;
    char buff[200];
    
    //Crear Nueva Tarea
    printf("Crear una nueva tarea \n");
    printf("Ingrese una descripción de la tarea: \n");
    fgets(buff, 200, stdin);
    buff[strcspn(buff, "\n")] = '\0'; // Eliminar salto de linea
    getchar();
    nuevaTarea.TareaID = id + 1;
    nuevaTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
    strcpy(nuevaTarea.Descripcion, buff);
    nuevaTarea.Duracion = rand() % 91 + 10;

    //Insertar Tarea Nodo a Lista
    InsertarNodo(&start, CrearNodo(nuevaTarea));

    //Mostrar Tarea
    MostrarTarea(start);

    free(nuevaTarea.Descripcion);
    return 0;
}

Nodo *IniciarListaVacia()
{
    return NULL;
}

Nodo *CrearNodo(Tarea nuevaTarea)
{
    Nodo *Tnodo = (Nodo *)malloc(sizeof(Nodo));
    Tnodo->T = nuevaTarea;
    Tnodo->Siguiente = NULL;
    return Tnodo;
}

void InsertarNodo(Nodo **Start, Nodo *NuevoNodo)
{
    NuevoNodo->Siguiente = *Start;
    *Start = NuevoNodo;
    
}

void MostrarTarea(Nodo *TNodo){
    printf("La tarea es: %s \n",TNodo->T.Descripcion);
    free(TNodo);
}