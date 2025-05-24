#include "tdas/extra.h"
#include "tdas/list.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Nodo:
// Un nodo representa un escenario en el laberinto, con conexiones a otros nodos y una lista de items disponibles.
// Cada nodo tiene un identificador único, un nombre, una descripción, y referencias a nodos adyacentes (arriba, abajo, izquierda, derecha).
// Además, puede contener una lista de items que el jugador puede recoger en ese escenario.

typedef struct Nodo {
  int id;
  char *nombre;
  char *descripcion;
  List *items; // Lista de items
  int id_arriba;
  int id_abajo;
  int id_izquierda;
  int id_derecha;
  struct Nodo* arriba;
  struct Nodo* abajo;
  struct Nodo* izquierda;
  struct Nodo* derecha;
  int es_final;
  struct Nodo* siguiente;
} Nodo;

// Grafo:
// Un grafo representa el laberinto completo, compuesto por múltiples nodos (escenarios).
// Cada grafo tiene una lista de nodos y un contador del total de nodos.
typedef struct Grafo{
  Nodo* nodos;
  int total_nodos;
} Grafo;

// Item:
// Un item representa un objeto que el jugador puede recoger en el laberinto.
// Cada item tiene un nombre, un valor (puntaje) y un peso.
typedef struct Item{
  char nombre[100];
  int valor;
  int peso;
} Item;

// Player:
// Un jugador representa al usuario que interactúa con el laberinto.
// Cada jugador tiene un peso total de items, un puntaje total, un tiempo restante para completar el laberinto,
// y una lista de items que ha recogido durante la partida.
typedef struct Player{
  int peso_total;
  int puntaje_total;
  int tiempo;
  List* items;
} Player;


/*## **Menú Principal**

1. **Cargar Laberinto desde Archivo CSV**
    - Leer un archivo CSV que describe los **escenarios**: sus descripciones, decisiones (con direcciones posibles), ítems disponibles (nombre, peso, valor) y conexiones.
    - Construir el **grafo (explícito)** a partir de esa información.
    
    Archivo de ejemplo: [graphquest.csv](https://drive.google.com/file/d/1Xu8du5BrdFG7hd1GW63gB4F5AgKRMbGZ/view?usp=sharing)
    
2. **Iniciar Partida**
    - Comienza el juego desde el escenario inicial. Se muestra el estado del jugador y el menú de opciones correspondientes.
*/



// crear_nodo:
// Crea un nuevo nodo con los parámetros dados y devuelve un puntero al nodo creado.
// Parámetros:
  // - id: Identificador único del nodo.
  // - nombre: Nombre del escenario.
  // - descripcion: Descripción del escenario.
  // - item: Lista de items disponibles en el escenario.
  // - arriba, abajo, izquierda, derecha: IDs de los nodos adyacentes.
  // - es_final: Indica si el nodo es un escenario final (1) o no (0).
Nodo* crear_nodo(int id, const char* nombre, const char* descripcion, List *item, int arriba, int abajo, int izquierda, int derecha, int es_final)
{
  Nodo* nuevo_nodo = malloc(sizeof(Nodo));
  nuevo_nodo->id = id;
  nuevo_nodo->nombre = strdup(nombre);
  nuevo_nodo->descripcion = strdup(descripcion);
  nuevo_nodo->items = item; 
  nuevo_nodo->id_arriba = arriba;
  nuevo_nodo->id_abajo = abajo;
  nuevo_nodo->id_izquierda = izquierda;
  nuevo_nodo->id_derecha = derecha;
  nuevo_nodo->arriba = NULL;
  nuevo_nodo->abajo = NULL;
  nuevo_nodo->izquierda = NULL;
  nuevo_nodo->derecha = NULL;
  nuevo_nodo->es_final = es_final;
  return nuevo_nodo;
}

// agregar_nodo:
// Agrega un nodo al grafo. Si el grafo no tiene nodos, el nuevo nodo se convierte en el primero.
// Si ya hay nodos, se agrega al final de la lista de nodos del grafo.
void agregar_nodo(Grafo *grafo, Nodo *nodo)
{
  if (grafo->nodos == NULL)
  {
    grafo->nodos = nodo;
  }
  else
  {
    Nodo *actual = grafo->nodos;
    while (actual->siguiente != NULL)
    {
      actual = actual->siguiente;
    }
    actual->siguiente = nodo;
  }
  grafo->total_nodos++;
  nodo->siguiente = NULL;
}

// buscar_nodo_por_id:
// Busca un nodo en el grafo por su ID. Recorre la lista de nodos hasta encontrar el nodo con el ID especificado.
Nodo* buscar_nodo_por_id(Grafo* grafo, int id) {
  Nodo* actual = grafo->nodos;
  while (actual != NULL) {
    if (actual->id == id) return actual;
    actual = actual->siguiente;
  }
  return NULL;
}

// conectar_nodos:
// Conecta los nodos del grafo según sus IDs adyacentes.
// Recorre cada nodo y asigna las referencias a los nodos adyacentes (arriba, abajo, izquierda, derecha) basándose en los IDs.
void conectar_nodos(Grafo* grafo) {
  Nodo* actual = grafo->nodos;
  while (actual != NULL) {
    if (actual->id_arriba != -1)
      actual->arriba = buscar_nodo_por_id(grafo, actual->id_arriba);
    if (actual->id_abajo != -1)
      actual->abajo = buscar_nodo_por_id(grafo, actual->id_abajo);
    if (actual->id_izquierda != -1)
      actual->izquierda = buscar_nodo_por_id(grafo, actual->id_izquierda);
    if (actual->id_derecha != -1)
      actual->derecha = buscar_nodo_por_id(grafo, actual->id_derecha);
    actual = actual->siguiente;
  }
}

// recoger_items:
// Permite al jugador recoger items del nodo actual.
// Muestra una lista de items disponibles y permite al jugador seleccionar cuáles recoger.
void recoger_items(Nodo* nodo_actual, Player* jugador) {
  if (nodo_actual->items == NULL || list_size(nodo_actual->items) == 0) {
    printf("No hay ítems para recoger en este escenario.\n");
    return;
  }
  
  printf("\n=== RECOGER ÍTEMS ===\n");
  printf("Selecciona los ítems que deseas recoger (separados por espacios, 0 para terminar):\n");
  
  int i = 1;
  for (Item *item = list_first(nodo_actual->items); item != NULL; item = list_next(nodo_actual->items)) {
    printf("  %d. %s (Peso: %d kg, Valor: %d pts)\n", i, item->nombre, item->peso, item->valor);
    i++;
  }
  
  printf("Ingresa los números de los ítems: ");
  int seleccion;
  int items_recogidos = 0;
  
  while (scanf("%d", &seleccion) && seleccion != 0) {
    if (seleccion >= 1 && seleccion <= list_size(nodo_actual->items)) {
      Item* item_seleccionado = NULL;
      int pos = 1;
      for (Item *item = list_first(nodo_actual->items); item != NULL; item = list_next(nodo_actual->items)) {
        if (pos == seleccion) {
          item_seleccionado = item;
          break;
        }
        pos++;
      }
      
      if (item_seleccionado != NULL) {
        
        Item* nuevo_item = malloc(sizeof(Item));
        strcpy(nuevo_item->nombre, item_seleccionado->nombre);
        nuevo_item->peso = item_seleccionado->peso;
        nuevo_item->valor = item_seleccionado->valor;
        
        list_pushBack(jugador->items, nuevo_item);
        jugador->peso_total += nuevo_item->peso;
        jugador->puntaje_total += nuevo_item->valor;
        
        printf("Recogiste: %s\n", nuevo_item->nombre);
        items_recogidos++;
      }
    } else {
      printf("Selección inválida: %d\n", seleccion);
    }
  }
  
  if (items_recogidos > 0) {
    jugador->tiempo -= items_recogidos;; 
    printf("Se recogieron %d ítem(s). Tiempo restante: %d\n", items_recogidos, jugador->tiempo);
  }
}

// descartar_items:
// Permite al jugador descartar items de su inventario.
// Muestra una lista de items en el inventario y permite al jugador seleccionar cuáles descartar.
// Actualiza el peso total y el puntaje del jugador al descartar items.
// Si no hay items en el inventario, informa al jugador.
void descartar_items(Player* jugador) {
  if (jugador->items == NULL || list_size(jugador->items) == 0) {
    printf("No tienes ítems para descartar.\n");
    return;
  }
  
  printf("\n=== DESCARTAR ÍTEMS ===\n");
  printf("Tu inventario actual:\n");
  
  int i = 1;
  for (Item *item = list_first(jugador->items); item != NULL; item = list_next(jugador->items)) {
    printf("  %d. %s (Peso: %d kg, Valor: %d pts)\n", i, item->nombre, item->peso, item->valor);
    i++;
  }
  
  printf("Selecciona los ítems que deseas descartar (separados por espacios, 0 para terminar):\n");
  printf("Ingresa los números de los ítems: ");
  
  int seleccion;
  int items_descartados = 0;
  List* items_a_eliminar = list_create();
  
  while (scanf("%d", &seleccion) && seleccion != 0) {
    if (seleccion >= 1 && seleccion <= list_size(jugador->items)) {
      Item* item_seleccionado = NULL;
      int pos = 1;
      for (Item *item = list_first(jugador->items); item != NULL; item = list_next(jugador->items)) {
        if (pos == seleccion) {
          item_seleccionado = item;
          break;
        }
        pos++;
      }
      
      if (item_seleccionado != NULL) {
        list_pushBack(items_a_eliminar, item_seleccionado);
        jugador->peso_total -= item_seleccionado->peso;
        jugador->puntaje_total -= item_seleccionado->valor;
        printf("Descartaste: %s\n", item_seleccionado->nombre);
        items_descartados++;
      }
    } else {
      printf("Selección inválida: %d\n", seleccion);
    }
  }
  
  for (Item *item_eliminar = list_first(items_a_eliminar); item_eliminar != NULL; item_eliminar = list_next(items_a_eliminar)) {
    list_popCurrent(jugador->items);
    free(item_eliminar);
  }
  
  if (items_descartados > 0) {
    jugador->tiempo -= items_descartados;
    printf("Se descartaron %d ítem(s). Tiempo restante: %d\n", items_descartados, jugador->tiempo);
  }
}

// mover_jugador:
// Permite al jugador moverse a un nodo adyacente (arriba, abajo, izquierda, derecha).
// Muestra las direcciones disponibles y permite al jugador seleccionar una.
// Actualiza el tiempo del jugador basado en su peso total al moverse.
Nodo *mover_jugador(Nodo* nodo_actual, Player* jugador)
{
  printf("=== MOVER JUGADOR ===\n");
  printf("Direcciones disponibles:\n");
  int opciones = 0;
  if (nodo_actual->arriba != NULL) {
    printf("1. Arriba\n");
    opciones++;
  }
  if (nodo_actual->abajo != NULL) {
    printf("2. Abajo\n");
    opciones++;
  }
  if (nodo_actual->izquierda != NULL) {
    printf("3. Izquierda\n");
    opciones++;
  }
  if (nodo_actual->derecha != NULL) {
    printf("4. Derecha\n");
    opciones++;
  }
  if (opciones == 0) {
    printf("No hay direcciones disponibles para moverse.\n");
    return nodo_actual;
  }
  printf("Seleccione una dirección (1-4): ");
  int seleccion;
  scanf("%d", &seleccion);
  Nodo* nuevo_nodo = NULL;
  switch (seleccion) {
    case 1:
      nuevo_nodo = nodo_actual->arriba;
      printf("Te moviste hacia Arriba.\n");
      break;
    case 2:
      nuevo_nodo = nodo_actual->abajo;
      printf("Te moviste hacia Abajo.\n");
      break;
    case 3:
      nuevo_nodo = nodo_actual->izquierda;
      printf("Te moviste hacia la Izquierda.\n");
      break;
    case 4:
      nuevo_nodo = nodo_actual->derecha;
      printf("Te moviste hacia la Derecha.\n");
      break;
    default:
      printf("Selección inválida.\n");
      return nodo_actual;
  }
  if (nuevo_nodo != NULL) {
    int tiempo_usado = (jugador->peso_total + 1) / 10;
    if (tiempo_usado < 1) tiempo_usado = 1; // Mínimo 1 unidad de tiempo
    
    jugador->tiempo -= tiempo_usado;
    printf("Tiempo usado para moverse: %d (basado en peso: %d kg)\n", tiempo_usado, jugador->peso_total);
    printf("Tiempo restante: %d\n", jugador->tiempo);
    return nuevo_nodo;
  }
  
  return nodo_actual;
}

// mostrar_victoria:
// Muestra un mensaje de victoria al jugador cuando alcanza el escenario final.
void mostrar_victoria(Player* jugador){
  printf("\n=== VICTORIA ===\n");
  printf("¡Felicidades! Has alcanzado el escenario final.\n");
  printf("Puntaje total: %d puntos\n", jugador->puntaje_total);
  printf("Tiempo restante: %d\n", jugador->tiempo);
}

// mostrar_derrota:
// Muestra un mensaje de derrota al jugador cuando se agota el tiempo.
void mostrar_derrota(Player* jugador){
  printf("\n=== DERROTA ==\n");
  printf("Has perdido. Tiempo agotado.\n");
}

// reiniciar_jugador:
// Reinicia el estado del jugador, eliminando todos los items recogidos, reseteando el tiempo, peso total y puntaje total.
// Libera la memoria de los items recogidos y reinicia las variables del jugador.
void reiniciar_jugador(Player* jugador){
  if (jugador->items != NULL) {
    for (Item *item = list_first(jugador->items); item != NULL; item = list_next(jugador->items)) {
      free(item);
    }
    while (list_size(jugador->items) > 0) {
      list_popFront(jugador->items);
    }
  }
  jugador->tiempo = 10;
  jugador->peso_total = 0;
  jugador->puntaje_total = 0;
  printf("Partida reiniciada. ¡Buena suerte!\n");
}

// leer_escenarios:
// Lee los escenarios desde un archivo CSV y construye el grafo de nodos.
// Cada línea del CSV representa un escenario con su ID, nombre, descripción, items disponibles y conexiones a otros nodos.
void leer_escenarios(Grafo *grafo)
{
  FILE *archivo = fopen("data/graphquest.csv", "r");
  if (archivo == NULL) {
    perror("Error al abrir el archivo");
    return;
  }
  char **campos;
  campos = leer_linea_csv(archivo, ','); // Lee los encabezados del CSV
  while ((campos = leer_linea_csv(archivo, ',')) != NULL)
  {
    int id = atoi(campos[0]);
    char *nombre = strdup(campos[1]);
    char *descripcion = strdup(campos[2]);
    char *items_str = strdup(campos[3]);
    List *lista_items = list_create();
    List *item_string = split_string(items_str, ";");
    for (char *items_entry = list_first(item_string); items_entry != NULL; items_entry = list_next(item_string))
    {
      List *valores = split_string(items_entry, ",");
      Item *nuevo_item = malloc(sizeof(Item));
      strcpy(nuevo_item->nombre, list_first(valores));
      nuevo_item->valor = atoi(list_next(valores));
      nuevo_item->peso = atoi(list_next(valores));
      list_pushBack(lista_items, nuevo_item);
    }
    int arriba = atoi(campos[4]);
    int abajo = atoi(campos[5]);
    int izquierda = atoi(campos[6]);
    int derecha = atoi(campos[7]);
    int es_final = atoi(campos[8]);
    Nodo *nodo = crear_nodo(id, nombre, descripcion, lista_items, arriba, abajo, izquierda, derecha, es_final);
    agregar_nodo(grafo, nodo);
  }
  conectar_nodos(grafo);
  fclose(archivo);
}

// mostrar_estado_actual:
// Muestra el estado actual del jugador y del escenario en el que se encuentra.
// Imprime el nombre y la descripción del escenario actual, los items disponibles en ese escenario,
// el inventario del jugador, el peso total, el puntaje total y las acciones disponibles.
void mostrar_estado_actual(Nodo* nodo_actual, Player* jugador) {
  printf("\n=== ESTADO ACTUAL ===\n");
  printf("Escenario: %s\n", nodo_actual->nombre);
  printf("Descripción: %s\n", nodo_actual->descripcion);
  printf("\nÍtems disponibles en este escenario:\n");
  if (nodo_actual->items != NULL && list_size(nodo_actual->items) > 0) {
    int i = 1;
    for (Item *item = list_first(nodo_actual->items); item != NULL; item = list_next(nodo_actual->items)) {
      printf("  %d. %s (Peso: %d kg, Valor: %d pts)\n", i, item->nombre, item->peso, item->valor);
      i++;
    }
  } else {
    printf("  No hay ítems disponibles.\n");
  }
  printf("\nTiempo restante: %d\n", jugador->tiempo);


  printf("Inventario del Jugador:\n");
  if (jugador->items != NULL && list_size(jugador->items) > 0) {
    int i = 1;
    for (Item *item = list_first(jugador->items); item != NULL; item = list_next(jugador->items)){
      printf("  %d. %s (Peso: %d kg, Valor: %d pts)\n", i, item->nombre, item->peso, item->valor);
      i++;
    }
  } else {
    printf("  No hay ítems en el inventario.\n");
  }
  printf("Peso total: %d kg\n", jugador->peso_total);
  printf("Puntaje total: %d pts\n", jugador->puntaje_total);
  printf("Acciones disponibles:\n");
  if (nodo_actual->arriba != NULL){
    printf("  1. Ir Arriba\n");
  }
  if (nodo_actual->abajo != NULL){
    printf("  2. Ir Abajo\n");
  }
  if (nodo_actual->izquierda != NULL){
    printf("  3. Ir Izquierda\n");
  }
  if (nodo_actual->derecha != NULL){
    printf("  4. Ir Derecha\n");
  }
}


// iniciar_partida:
// Inicia una partida en el laberinto. Muestra el estado actual del jugador y del escenario,
// permite al jugador recoger o descartar items, moverse a nodos adyacentes, reiniciar la partida o salir del juego.
void iniciar_partida(Grafo *grafo)
{
  if (grafo->nodos == NULL)
  {
    printf("No hay nodos cargados. Cargue un laberinto primero.\n");
    return;
  }
  
  int opcion = 0;
  // Inicializar el jugador
  Player *jugador = malloc(sizeof(Player));
  jugador->peso_total = 0;
  jugador->puntaje_total = 0;
  jugador->items = list_create();
  jugador->tiempo = 10;
  
  Nodo* nodo_inicial = buscar_nodo_por_id(grafo, 1);
  if (nodo_inicial == NULL) {
    nodo_inicial = grafo->nodos; // Si no hay nodo con ID 1, usar el primero
  }

  while (1)
  {
    // imprimir nodo actual
    Nodo* nodo_actual = nodo_inicial;
    while (jugador->tiempo > 0)
    {
      mostrar_estado_actual(nodo_actual, jugador);
      if (nodo_actual->es_final)
      {
        mostrar_victoria(jugador);
        break;
      }
      printf("=== Opciones ===\n");
      printf("1. Recoger Items\n");
      printf("2. Descartar Items\n");
      printf("3. Avanzar en una direccion\n");
      printf("4. Reiniciar Partida\n");
      printf("5. Salir\n");
      printf("Seleccione una opción: ");
      int opcion;
      scanf("%d", &opcion);
      switch (opcion) {
        case 1:
          recoger_items(nodo_actual, jugador);
          break;
        case 2:
          descartar_items(jugador);
          break;
        case 3:
          nodo_actual = mover_jugador(nodo_actual, jugador);
          break;
        case 4:
          printf("Reiniciando partida...\n");
          reiniciar_jugador(jugador);
          break; 
        case 5:
          printf("Saliendo del juego.\n");
          if (jugador->puntaje_total > 0) {
            printf("Puntaje final: %d puntos\n", jugador->puntaje_total);
          }
          free(jugador);
          return;
        default:
          printf("Opción no válida. Intente de nuevo.\n");
          break;
      }
      if (jugador->tiempo <= 0)
      {
        mostrar_derrota(jugador);
        break;
      }
      if (opcion == 4){
        break;
      }
      
    }
    if (jugador->tiempo <= 0 || nodo_actual->es_final) {
      printf("\n¿Qué deseas hacer?\n");
      printf("1. Reiniciar Partida\n");
      printf("2. Salir del Juego\n");
      printf("Selecciona una opción: ");
      
      int opcion_final;
      scanf("%d", &opcion_final);
      
      if (opcion_final == 1) {
        reiniciar_jugador(jugador);
        continue; // Continuar el bucle principal para nueva partida
      } else {
        printf("Gracias por jugar. ¡Hasta la próxima!\n");
        break; // Salir del bucle principal
      }
    }
  }
  free(jugador);
}

// inicio_juego:
// Muestra el menú principal del juego, permite cargar el laberinto, activar el modo debug, iniciar la partida o salir del juego.
void inicio_juego(Grafo *grafo)
{
  short cargado = 0, mostrar = 0, mostrartexto = 1;
  while (1)
  {
    if (mostrartexto)
    {
      if (!mostrar) limpiarPantalla(); // Limpia solo si no está en modo debug
      printf("=== Menú Principal ===\n");
      printf("1. Cargar Laberinto \n");
      printf("2. Activar debug \n");
      printf("3. Iniciar Partida \n");
      printf("4. Salir \n");
      printf("Seleccione una opción: ");
      mostrartexto = 0;
    }

    int opcion;
    scanf("%d", &opcion);

    switch (opcion)
    {
      case 1:
        leer_escenarios(grafo);
        printf("Laberinto cargado.\n");
        cargado = 1;
        mostrartexto = 1;
        break;

      case 2:
        mostrar = !mostrar;
        printf("mostrar debug %s\n", mostrar ? "activado" : "desactivado");
        mostrartexto = 1;
        break;

      case 3:
        if (!cargado)
        {
          if (!mostrar) limpiarPantalla(); // Asegura que el mensaje se vea
          printf("Debe cargar el laberinto primero.\n");
          mostrartexto = 1;
          break;
        }
        iniciar_partida(grafo);
        break;

      case 4:
        printf("saliendo.\n");
        exit(0);

      default:
        printf("Opción no válida. Intente de nuevo.\n");
        mostrartexto = 1;
        break;
    }
  }
}
int main() {
  Grafo *grafo = malloc(sizeof(Grafo));
  grafo->nodos = NULL;
  grafo->total_nodos = 0;
  inicio_juego(grafo);

  return 0;
}
