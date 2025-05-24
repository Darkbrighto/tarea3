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
* Bajo ciertas condiciónes desconocidas, puede el programa quedarse estancado en el inicio.

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
Opción seleccionada: 1) Cargar nivel
nivel cargado exitosamente desde graphquest.csv
```

**Paso 2: Buscar por artista**

```
Opción seleccionada: 2) Buscar canciones por artista
Ingrese el nombre del artista: Queen
- Bohemian Rhapsody
- Don't Stop Me Now
- Another One Bites The Dust
```

**Paso 3: Buscar por tempo**

```
Opción seleccionada: 3) Buscar canciones por tempo
Seleccione el rango de tempo (Lento, Moderado, Rápido): Rápido
- Song A (135 BPM)
- Song B (142 BPM)
```

**Paso 4: Ver detalles de una canción**

```
Opción seleccionada: 4) Mostrar información detallada
Ingrese el nombre de la canción: Bohemian Rhapsody
Artista: Queen
Álbum: A Night at the Opera
Género: Rock
Tempo: 144 BPM
```

## Contribuciones (solo para tareas grupales)

### Nombre del integrante BRUNO PERÉZ:

* Implementación de la carga y búsqueda de canciones por artista, género y tempo
* Implementación de la eliminación de canciónes y creación de listas de reproducción
* Correción de errores y reducir tiempos de carga
* **Auto-evaluación**: 3 (Aporte excelente)

### Nombre del integrante HUGO GALLARDO:

* Comentarios en la aplicación y explicar el uso de cada función.
* Creación del readme y del repositorio de github.
* Implementación en función de leer (elegir cuanto)
* Get tempo range y incluir treemap
* **Auto-evaluación**: 3 (Aporte excelente)
