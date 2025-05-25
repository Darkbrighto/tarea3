# GRAPH-QUEST

## Descripción

**GRAPH** es un Videojuego de lenguaje C que permite cargar un Nivel de canciones cargadas desde un archivo CSV. A través de una interfaz por consola, Este juego consiste en recorrer un laberinto representado mediante un grafo, en el que cada nodo es un escenario con decisiones posibles y elementos coleccionables.

## Cómo compilar y ejecutar

Este sistema puede ejecutarse fácilmente utilizando **Visual Studio Code** junto con un compilador de C como **GCC**. Para trabajar con la aplicación en tu entorno local, sigue los siguientes pasos:

### Requisitos previos:

* Tener instalado [Visual Studio Code](https://code.visualstudio.com/)
* Instalar la extensión **C/C++** (Microsoft)
* Contar con un compilador de C (como **gcc**). En Windows se recomienda instalar [MinGW](https://www.mingw-w64.org/) o utilizar [WSL](https://learn.microsoft.com/en-us/windows/wsl/)

### Pasos para compilar y ejecutar:

1. **Descarga y descomprime el** proyecto en una carpeta de tu elección.

2. **Abre el proyecto en Visual Studio Code**

   * Abre VS Code.
   * Selecciona `Archivo > Abrir carpeta...` y elige la carpeta del proyecto. (TAREA3...)

3. **Compila el código**

   * Abre el archivo `tarea3_lecturacsv.c`.
   * Abre la terminal integrada (`Terminal > Nueva terminal`).
   * Abre la carpeta TAREA3 en el Terminal
   * Ejecuta el siguiente comando para compilar el programa:

     ```bash
     gcc tarea3_lecturacsv.c tdas/*c
     ```

4. **Ejecuta el programa**

   * Asegúrate de que el archivo `graphquest.csv` esté en la misma carpeta.
   * Ejecuta el programa con:

     ``
     ./a.out
     ```

## Funcionalidades

### Funcionando correctamente:

* 📂 Cargar un nivel desde un archivo CSV (`graphquest.csv`)
* 👩‍🎤 Poder moverte en el Grafo seleccionando opciones.
* 🕒 Límite de tiempo, cada acción costando 1 al tiempo.
* 📦 Mostrar información del estado actual del jugador (Inventario, habitación actual)
* 📜 Mostrar solo lo posible y necesario (Si no puede moverse arriba, no lo mostrará como opción. )

### Problemas conocidos:

* Si intentas cargar el juego sin leer el CSV, no hay problemas, pero, sin activar el modo debug, no podrás ver el
mensaje de error correspondiente, por ende (falta de feedback al jugador)
* No hay un estado de victoria como tal, llegar al final no puedes moverte y salir hará que pierdas.
* Si descartas items en el multijugador, pese a no ser una accion en caso de no tener items, cuenta como un turno
* (PELIGRO) Escribir ^]]A hará que el programa se caiga completamente
* No hay limpieza clara de la pantalla al iniciar partida.

### A mejorar:

* Mayor feedback al jugador de lo que realmente ocurre, ya sea colocar más prints y arreglar lo de limpiar pantalla.

### Funcionalidades planeadas:

* ➕ Uso de objetos no solo para la carga

## Formato del archivo CSV

El archivo `graphquest.csv` debe contener, como mínimo, las siguientes columnas:

* `ID` (índice 1)
* `Nombre` (índice 2 `,`)
* `Descripción` (índice 3)
* `Cadena en forma de lista de los items` (índice 4)
* `Posibles movimientos` (índice 5)

**Nota:** Asegúrate de que los índices y nombres de columnas coincidan exactamente con el formato del CSV esperado por el programa.

## Ejemplo de uso

#Instrucciones y demas para abajo
# ¿Puede el jugador tomar múltiples veces el mismo objeto en el mapa?
# ¿Cuando el jugador es reiniciado, también se reinician los objetos en el grafo?,  ¿Si es así, como reinicias y sabes que objetos tomar del grafo?
# ¿Reiniciar el jugador y reiniciar el nivel están funcionando?, ya que si reinicias uno debes reiniciar otro
# Tener una copia del grafo original y reemplazar el grafo, osea tener un grafo como guardado de la partido y otro el estado intacto, ya que al reiniciar, se borraran objetos tomados y al tomarlos se borraran.

**Paso 1: Cargar nivel desde el archivo CSV**

```
Opción seleccionada: 1) Cargar csv
nivel cargado exitosamente desde graphquest.csv
```

**Paso 2: Iniciar Partida, Multijugador y Solitario**

```
Opción seleccionada: 3(Solo) o 4(Multijugador)
Debería mostrarse algo así a continuación, en multijugador también debería
tener los turnos, como 1/2:

=== ESTADO ACTUAL ===
Escenario: Entrada principal
Descripción: Una puerta rechinante abre paso a esta mansion olvidada por los dioses y los conserjes. El aire huele a humedad y a misterios sin resolver.

Ítems disponibles en este escenario:
  No hay ítems disponibles.

Tiempo restante: 10
Inventario del Jugador:
  No hay ítems en el inventario.
Peso total: 0 kg
Puntaje total: 0 pts
Acciones disponibles:
  2. Ir Abajo
=== Opciones ===
1. Recoger Items
2. Descartar Items
3. Avanzar en una direccion
4. Reiniciar Partida
5. Salir
Seleccione una opción: 
```

**Paso 3: Acciones a realizar**

```
Opción seleccionada: 1) Recoger Items
-Si hay items en el mapa, podrás recogerlos al seleccionar su índice
-Ítems disponibles en este escenario:
  1. Cuchillo (Peso: 1 kg, Valor: 3 pts)
  2. Pan (Peso: 1 kg, Valor: 2 pts)
-Escribiendo 1 o 2 Hará que los eligas, solo podrás tomar 1.

Opción seleccionada: 2) Descartar Items
-Si tienes Items en el inventario
-Inventario del Jugador:
  1. Cuchillo (Peso: 1 kg, Valor: 3 pts)
  2. Pan (Peso: 1 kg, Valor: 2 pts)
-Escribiendo 1 o 2 descartará el item que eligas.

Opción seleccionada: 3) Avanzar en una dirección
-Se te mostrarán las posibles acciones.
Acciones disponibles:
  1. Ir Arriba
  2. Ir Abajo
  4. Ir Derecha
-Escribiendo 1,2 o 3 avanzará hacia la siguente dirección, esto solo si es posible(es posible si se muestra).
-Avanzar costará en medida de los items que tengas en el inventario

Opción seleccionada: 4) Reiniciar Partida
-Eliminará tu inventario, tu tiempo y volverás al inicio de la partida

Opción seleccionada: 5) Salir
-Para salir completamente ingresa esta opción luego escribe 5 y enter.

-En multijugador existe la opción de pasar de turno(6) lo que hará que juege el siguente jugador.
```

## Contribuciones (solo para tareas grupales)

### Nombre del integrante BRUNO PERÉZ:

* Implementación de la carga CSV
* Implementación del movimiento en el grafo
* Implementación de la eliminación de items en grafo y jugador
* Correción de errores y añadir modo multijugador
* **Auto-evaluación**: 3 (Aporte excelente)

### Nombre del integrante HUGO GALLARDO:

* Comentarios en la aplicación y explicar el uso de cada función.
* Creación del readme y del repositorio de github.
* Búsqueda de errores
* **Auto-evaluación**: 3 (Aporte excelente)
