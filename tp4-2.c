#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <string.h>

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
void listar(Nodo *lista);
Nodo *BuscarTareaID(Nodo *lista, int id);
Nodo *BuscarPalabraClave(Nodo *lista, char palabra[]);
///

int main()
{
    // srand(time(NULL));

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
                printf("\n");
                printf("Ingrese una Descripcion de la tarea: \n");
                fgets(buff, 200, stdin);
                buff[strcspn(buff, "\n")] = '\0'; // Eliminar salto de linea
                nuevaTarea.Descripcion = (char *)malloc((strlen(buff) + 1) * sizeof(char));
                strcpy(nuevaTarea.Descripcion, buff);

                printf("\n");
                printf("Ingrese la Duracion de la tarea entre 10 y 100: \n");
                scanf("%d", &nuevaTarea.Duracion);
                getchar();

                nuevaTarea.TareaID = id;
                id = id + 1;

                // Insertar Tarea Nodo a Lista TPendiente
                InsertarNodo(&StartListaTPendiente, CrearNodo(nuevaTarea));

                printf("\n");
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

                if (Aux == NULL)
                {
                    printf("\n");
                    printf("No hay tareas Pendientes \n");
                    break;
                }
                else
                {
                    printf("\n");
                    printf("Escribe ID para marcar como Realizada:\n");
                    printf("0. Volver atras.\n");
                    while (Aux != NULL)
                    {
                        printf("|ID %d Tarea: %s Duracion: %d\n", Aux->T.TareaID, Aux->T.Descripcion, Aux->T.Duracion);
                        Aux = Aux->Siguiente;
                    }

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
                            printf("\n");
                            printf("Id no encontrada, vuelve a intentarlo.\n");
                            break;
                        }
                        else
                        {
                            Nodo *nodoMover = QuitarNodo(&StartListaTPendiente, Aux->T.TareaID);
                            InsertarNodo(&StartListaTRealizada, nodoMover);
                            printf("\n");
                            printf("Tarea movida con exito.\n");
                            Aux = StartListaTPendiente;
                        }
                    }
                    else if (select != 0)
                    {
                        printf("\n");
                        printf("Opcion invalida, vuelve a intentarlo.\n");
                    }
                }
            }
            if (select == 0) // Para que entre al while del menu principal
            {
                select = 1;
            }
        }
        break;

        case 3:
        {
            select = 1;
            printf("\n");
            printf("Tareas Pendientes: \n");
            listar(StartListaTPendiente);
            printf("\n");
            printf("Tareas Realizadas: \n");
            listar(StartListaTRealizada);
        }
        break;

        case 4:
        {
            select = 1;
            while (select != 0)
            {
                printf("\n");
                printf("Ingresar ID:       (0. Volver) \n");
                scanf("%d", &select);
                getchar();
                if (select == 0)
                {
                    break;
                }

                if (select >= 1000)
                {

                    Nodo *tareaID;
                    tareaID = BuscarTareaID(StartListaTPendiente, select);
                    if (tareaID != NULL)
                    {
                        printf("\n");
                        printf("La tarea pertenece a Pendientes\n");
                        printf("|ID %d Tarea: %s Duracion: %d\n", tareaID->T.TareaID, tareaID->T.Descripcion, tareaID->T.Duracion);
                    }
                    else if (tareaID == NULL)
                    {
                        tareaID = BuscarTareaID(StartListaTRealizada, select);

                        if (tareaID != NULL)
                        {
                            printf("\n");
                            printf("La tarea pertenece a Realizadas\n");
                            printf("|ID %d Tarea: %s Duracion: %d\n", tareaID->T.TareaID, tareaID->T.Descripcion, tareaID->T.Duracion);
                        }
                        else
                        {
                            printf("\n");
                            printf("Tarea no encontrada, intentelo de nuevo.\n");
                        }
                    }
                }
                else
                {
                    printf("\n");
                    printf("El ID ingresado es incorrecto, inténtelo de nuevo.\n");
                }
            }
            select = 1;
        }
        break;

        case 5:
        {
            select = 1;
            char palabra[20];
            while (select != 0)
            {
                printf("\n");
                printf("Ingresar Palabra clave:       (0. Volver) \n");
                fgets(palabra, 20, stdin);
                palabra[strcspn(palabra, "\n")] = '\0'; // eliminar salto de linea

                if (strcmp(palabra, "0") == 0)
                {
                    // las cadenas son iguales
                    break;
                }

                Nodo *tareaPalabraClavePend = BuscarPalabraClave(StartListaTPendiente, palabra);
                Nodo *tareaPalabraClaveReal = BuscarPalabraClave(StartListaTRealizada, palabra);

                if (tareaPalabraClavePend != NULL || tareaPalabraClaveReal != NULL)
                {
                    if (tareaPalabraClavePend != NULL)
                    {
                        printf("\n");
                        printf("Tareas Pendientes:\n");
                        printf("|ID %d Tarea: %s Duracion: %d\n", tareaPalabraClavePend->T.TareaID, tareaPalabraClavePend->T.Descripcion, tareaPalabraClavePend->T.Duracion);
                    }
                    if (tareaPalabraClaveReal != NULL)
                    {
                        printf("\n");
                        printf("Tareas Realizadas\n");
                        printf("|ID %d Tarea: %s Duracion: %d\n", tareaPalabraClaveReal->T.TareaID, tareaPalabraClaveReal->T.Descripcion, tareaPalabraClaveReal->T.Duracion);
                    }
                }
                else
                {
                    printf("No se encontro ninguna coincidencia\n");
                }
            }
        }
        break;

        default:
            break;
        }
    }

    Nodo *actual = StartListaTPendiente;
    Nodo *siguiente;
    while (actual != NULL)
    {
        siguiente = actual->Siguiente;
        free(actual->T.Descripcion);
        free(actual);
        actual = siguiente;
    }
    StartListaTPendiente = NULL;

    Nodo *actual = StartListaTRealizada;
    Nodo *siguiente;
    while (actual != NULL)
    {
        siguiente = actual->Siguiente;
        free(actual->T.Descripcion);
        free(actual);
        actual = siguiente;
    }
    StartListaTPendiente = NULL;

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

void listar(Nodo *lista)
{

    while (lista != NULL)
    {
        printf("|ID %d Tarea: %s Duracion: %d\n", lista->T.TareaID, lista->T.Descripcion, lista->T.Duracion);

        lista = lista->Siguiente;
    }
}

Nodo *BuscarTareaID(Nodo *lista, int id)
{
    Nodo *aux = lista;
    while (aux != NULL && aux->T.TareaID != id)
    {
        aux = aux->Siguiente;
    }

    return aux;
}

Nodo *BuscarPalabraClave(Nodo *lista, char palabra[])
{
    while (lista != NULL)
    {
        if (lista->T.Descripcion != NULL &&  palabra != NULL && strstr(lista->T.Descripcion, palabra) != NULL)
        {
            return lista;
        }
        lista = lista->Siguiente;
    }
    return NULL;
}
