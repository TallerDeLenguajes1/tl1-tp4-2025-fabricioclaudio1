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
} Nodo;

Nodo *IniciarListaVacia();
Nodo *CrearNodo(Tarea nuevaTarea);
Nodo *QuitarNodo(Nodo **Start, int id);
void InsertarNodo(Nodo **inicio, Nodo *NNodo);
void MostrarTarea(Nodo *TNodo);
///

int main()
{
    srand(time(NULL));

    Nodo *StartListaTPendiente = IniciarListaVacia();
    Nodo *StartListaTRealizada = IniciarListaVacia();

    int id = 1000;
    Tarea nuevaTarea;
    char buff[200];

    int select = 1;

    while (select != 0)
    {
        printf("\n");
        printf("Eliga una opcion: \n");
        printf("1. Agregar una Tarea Pendiente.\n");
        printf("2. Mover Tareas Pendientes a Realizadas.\n");
        printf("3. Listar Tareas Pendientes y Realizadas.\n");
        printf("4. Buscar Tareas por ID.\n");
        printf("5. Buscar Tareas por palabra clave.\n");
        printf("0. Salir.\n");

        scanf("%d", &select);
        getchar();

        switch (select)
        {
        case 1:
            select = 1;
            while (select != 2)
            {
                // Agregar Nueva Tarea
                printf("Ingrese una Descripcion de la tarea: \n");
                fgets(buff, 200, stdin);
                buff[strcspn(buff, "\n")] = '\0'; // Eliminar salto de linea
                nuevaTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
                strcpy(nuevaTarea.Descripcion, buff);

                printf("Ingrese la Duracion de la tarea entre 10 y 100: \n");
                scanf("%d", &nuevaTarea.Duracion);
                getchar();

                nuevaTarea.TareaID = id;
                id = id + 1;

                // Insertar Tarea Nodo a Lista TPendiente
                InsertarNodo(&StartListaTPendiente, CrearNodo(nuevaTarea));

                printf("Desea agregar otra tarea? \n");
                printf("1. SI\n");
                printf("2. NO\n");
                scanf("%d", &select);
                getchar();
            }
            break;

        case 2:
        {
            select = 1;
            Nodo *Aux = StartListaTPendiente;
            while (select != 0)
            {
                printf("Escribe ID para marcar como Realizada.\n");
                printf("0. Volver atras.\n");
                do
                {
                    printf("|ID %d Tarea: %s Duracion: %d\n", Aux->T.TareaID, Aux->T.Descripcion, Aux->T.Duracion);
                    Aux = Aux->Siguiente;
                } while (Aux->Siguiente);

                Aux = StartListaTPendiente;
                scanf("%d", &select);
                getchar();
                if (select >= 1000)
                {
                    while (Aux != NULL && Aux->T.TareaID != select)
                    {
                        Aux = Aux->Siguiente;
                    }
                    if (Aux == NULL)
                    {
                        printf("Id no encontrada, vuelve a intentarlo.\n");
                        break;
                    }
                    Nodo *nodoMover = QuitarNodo(&StartListaTPendiente, Aux->T.TareaID);
                    InsertarNodo(&StartListaTRealizada, nodoMover);
                }
                else if (select != 0)
                {
                    printf("Opcion invalida, vuelve a intentarlo.\n");
                }
            }
        }
        break;

        case 3:

            break;

        case 4:

            break;

        case 5:

            break;

        default:
            break;
        }
    }

    free(nuevaTarea.Descripcion);

    Nodo *borrarPendiente = StartListaTPendiente;
    Nodo *borrarRealizada = StartListaTRealizada;
    while (borrarPendiente)
    {
        if (borrarPendiente->Siguiente == NULL)
        {
            free(borrarPendiente);
            borrarPendiente = StartListaTPendiente;
        }
        borrarPendiente->Siguiente;
    }

    /*Para Pend y Realz
    while (borrarPendiente || borrarRealizada)
    {
        if (borrarPendiente->Siguiente == NULL)
        {
            free(borrarPendiente);
            borrarPendiente = StartListaTPendiente;
        }
        borrarPendiente->Siguiente;

        if (borrarRealizada->Siguiente == NULL)
        {
            free(borrarRealizada);
            borrarRealizada = StartListaTRealizada;
        }
        borrarRealizada->Siguiente;

    }*/


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

Nodo *QuitarNodo(Nodo **Start, int id)
{
    Nodo *Aux = *Start;
    Nodo *Anterior = NULL;

    while (Aux != NULL && Aux->T.TareaID != id)
    {
        Anterior = Aux;
        Aux = Aux->Siguiente;
    }

    if (Aux != NULL)
    {
        if (Aux == *Start)
        {
            *Start = Aux->Siguiente;
        }
        else
        {
            Anterior->Siguiente = Aux->Siguiente;
        }
        Aux->Siguiente = NULL;
    }

    return Aux;
}

void InsertarNodo(Nodo **Start, Nodo *NuevoNodo)
{
    NuevoNodo->Siguiente = *Start;
    *Start = NuevoNodo;
}

void MostrarTarea(Nodo *Lista)
{
    printf("La tarea es: %s \n", Lista->T.Descripcion);
    printf("Id: %d Duracion: %d \n", Lista->T.TareaID, Lista->T.Duracion);
    free(Lista);
}