#include "tdas/extra.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Nodo {
  int id;
  char *nombre;
  char *descripcion;
  List *items; // Lista de items
  int arriba;
  int abajo;
  int izquierda;
  int derecha;
  int es_final;
  struct Nodo* siguiente;
} Nodo;

typedef struct Grafo{
  Nodo* nodos;
  int total_nodos;
} Grafo;

typedef struct Item{
  char nombre[100];
  int valor;
  int peso;
} Item;
/* ptropptied

typedef struct Jugador{
  char nombre[100];
  int vida;
  int oro;
  List* items; // Lista de items
} Jugador;

*/

/*## **Menú Principal**

1. **Cargar Laberinto desde Archivo CSV**
    - Leer un archivo CSV que describe los **escenarios**: sus descripciones, decisiones (con direcciones posibles), ítems disponibles (nombre, peso, valor) y conexiones.
    - Construir el **grafo (explícito)** a partir de esa información.
    
    Archivo de ejemplo: [graphquest.csv](https://drive.google.com/file/d/1Xu8du5BrdFG7hd1GW63gB4F5AgKRMbGZ/view?usp=sharing)
    
2. **Iniciar Partida**
    - Comienza el juego desde el escenario inicial. Se muestra el estado del jugador y el menú de opciones correspondientes.
*/




/**
 * Carga canciones desde un archivo CSV
 */
/*
void leer_escenarios() {
  // Intenta abrir el archivo CSV que contiene datos de películas
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror(
        "Error al abrir el archivo"); // Informa si el archivo no puede abrirse
    return;
  }

  char **campos;
  // Leer y parsear una línea del archivo CSV. La función devuelve un array de
  // strings, donde cada elemento representa un campo de la línea CSV procesada.

  // comentario hugistico : parsear en este contexto significa dividir una cadena en partes
  // separadas por un delimitador específico (en este caso, la coma).
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV


  // Lee cada línea del archivo CSV hasta el final
  while ((campos = leer_linea_csv(archivo, ',')) != NULL) {
    printf("ID: %d\n", atoi(campos[0]));
    printf("Nombre: %s\n", campos[1]);
    printf("Descripción: %s\n", campos[2]);

    List* items = split_string(campos[3], ";");

    printf("Items: \n");
    for(char *item = list_first(items); item != NULL; 
          item = list_next(items)){

        List* values = split_string(item, ",");
        char* item_name = list_first(values);
        int item_value = atoi(list_next(values));
        int item_weight = atoi(list_next(values));
        printf("  - %s (%d pts, %d kg)\n", item_name, item_value, item_weight);
        list_clean(values);
        free(values);
    }

    int arriba = atoi(campos[4]);
    int abajo = atoi(campos[5]);
    int izquierda = atoi(campos[6]);
    int derecha = atoi(campos[7]);

    if (arriba != -1) printf("Arriba: %d\n", arriba);
    if (abajo != -1) printf("Abajo: %d\n", abajo);
    if (izquierda != -1) printf("Izquierda: %d\n", izquierda);
    if (derecha != -1) printf("Derecha: %d\n", derecha);

    
    int is_final = atoi(campos[8]);
    if (is_final) printf("Es final\n");

    list_clean(items);
    free(items);
    
  }
  fclose(archivo); // Cierra el archivo después de leer todas las líneas

}
*/

void inicio_juego()
{
  short cargado = 0;
  while(1)
  {
    printf("1. Cargar Laberinto \n");
    printf("2. Iniciar Partida \n");
    printf("3. Salir \n");
    printf("Seleccione una opción: ");
    int opcion;
    scanf("%d", &opcion);
    switch(opcion)
    {
      case 1:
        // leer_escenarios();
        printf("Laberinto cargado.\n");
        cargado = 1;
        break;
      case 2:
        if(cargado == 0)
        {
          printf("Debe cargar el laberinto primero.\n");
          break;
        }
        // iniciar_partida();
        break;
      case 3:
        printf("saliendo.\n");
        exit(0);
      default:
        printf("Opción no válida. Intente de nuevo.\n");
    }
    limpiarPantalla();
  }
}

int main() {
  inicio_juego();

  return 0;
}
