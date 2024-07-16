# Programación III: Proyecto Final (2024-1)

## Integrantes
* Jose Guillermo Galvez Pacori
* Dylan Andres Cabezas Ramirez
* Leonardo Alfredo Montoya Solórzano
* Samuel Aaron Saquiray Delgado

## Plataforma de Streaming
El objetivo del proyecto final es implementar una plataforma de *streaming*. Un programa que administre la búsqueda y visualización de la sinopsis de películas. Para ello se debe implementar las siguientes operaciones:

* El programa debe leer la base de datos en forma **.csv**. La base de datos puede ser descargada desde el siguiente [link](https://drive.google.com/file/d/1iusSIbmXJW_OUBm6X7Ik593rgCGPCPza/view?usp=sharing).
* El programa debe cargar este archivo en una **estructura de datos** que permita una rápida búsqueda de una película.
* Para buscar una película se debe utilizar una palabra o frase. También se debe poder buscar películas por el **Tag**: cult, horror, etc.
* Al buscar películas deben de aparecer la cinco más **importantes** y una opción para visualizar las siguientes cinco coincidencias.
* Al seleccionar una película, se debe visualizar la sinopsis y las opciones **Like** y **Ver más tarde** .
* Al iniciar el programa la plataforma debería mostrar las películas que fueron añadidas en **Ver más tarde**. Además, se debe visualizar las películas similares a las que el usuario les dio **Like** (implemente su propio algoritmo).

## Requisitos
* Grupos de cuatro personas como máximo y de tres como mínimo. No se aceptarán grupos de dos o una persona.
* Subir el programa a un repositorio en Github. Aquí debe de estar toda la documentación sobre el proyecto.
* Grabar su presentación y colocar el link en su repositorio. El video debe tener un máximo de 15 minutos. Aquel grupo que sobrepase el tiempo tendrá una penalización en su nota.
* Cumplir con la rúbrica del proyecto.}

# Funcionamiento Técnico del Proyecto

## Introducción
Este programa está diseñado para gestionar un sistema de streaming que permite autenticar usuarios, administrar y recomendar películas. El sistema incluye funcionalidades para cargar películas, realizar búsquedas, recomendar películas, y gestionar listas de "ver más tarde" y "me gusta". La implementación se divide en varios módulos que incluyen la gestión de credenciales, la estructura de datos de las películas, un algoritmo para búsqueda eficiente, y la lógica principal del sistema de streaming.

## Estructura del proyecto

### credenciales.cpp
Define las clases **AutenticacionReal** que se encarga de la autenticación de usuarios utilizando un mapa de usuarios y contraseñas, mientras que la clase **ProxyAutenticacion** actúa como intermediario para la autenticación, añadiendo una capa de seguridad y control adicional.

### pelicula.cpp
Define la clase **Pelicula** que representa una película con atributos como ID, título, sinopsis y categorías. Proporciona métodos para leer películas desde un archivo CSV y contar las palabras en el título y la sinopsis.

### nodo.cpp
Define la clase **NodoTrie**, que representa un nodo en un trie. Cada nodo puede tener hijos y almacenar IDs de películas.

### inverted.cpp
Define la clase **InvertedTrie**, que es un trie invertido para realizar búsquedas eficientes de películas basadas en subcadenas del título y la sinopsis.

### streaming.cpp
Implementa la clase **Streaming**, que es la clase principal del sistema de streaming. Gestiona la carga de películas, la búsqueda, las recomendaciones, y la interacción del usuario con el sistema.

### functions.cpp
Proporciona funciones auxiliares como normalización de texto, conversión de cadenas a conjuntos de palabras, y limpieza de la terminal.

## Descripción técnica

### Estructura de Datos de Películas
La clase **Pelicula** almacena la información de cada película y proporciona métodos para leer datos desde un archivo CSV y contar palabras en el título y la sinopsis. Utiliza unordered_set para almacenar categorías y unordered_map para contar palabras.

### Trie Invertido
La clase **InvertedTrie** utiliza un trie invertido para indexar palabras del título y la sinopsis de cada película. Esto permite realizar búsquedas eficientes de películas basadas en subcadenas de texto.

### Sistema de Streaming
La clase **Streaming** gestiona la lógica principal del sistema. Incluye métodos para:
* Cargar películas desde un archivo.
* Buscar películas por subcadena en el título o sinopsis.
* Buscar películas por categoría.
* Recomendar películas basadas en los gustos del usuario.
* Gestionar listas de "ver más tarde" y "me gusta".

### Funciones Auxiliares
El archivo **functions.cpp** incluye funciones para normalizar texto (remover caracteres especiales y convertir a minúsculas), convertir texto a conjuntos de palabras, y limpiar la terminal.

## Ejecución del Sistema
Para ejecutar el sistema de streaming:

Compilar todos los archivos **.cpp**.
Ejecutar el programa principal.
Interactuar con el menú del sistema para buscar, ver y gestionar películas.
El sistema carga inicialmente las películas desde un archivo CSV y permite al usuario buscar películas por nombre o categoría, ver recomendaciones, y gestionar sus listas de "ver más tarde" y "me gusta".

## Descripción gráfica(frontend)
se crean dos carpetas ,una para manejar las peticiones que hara el frontend hacia nuestro proyecto principal y otra para ejecutar el frontend(para ejecutar el frontend es necesario tener node instalado).
para la parte de manejar las peticiones en c++ se usa una libreria llamada httplib.h que nos brinda soporte para esto.
esta constaria de crear api's para el registro de un nuevo usuario , el inicio de sesion de un usuario existente,busqueda de pelicula por nombre y por categoria,otra para añadir a la lista de ver mas tarde y la ultima para darle me gusta a las peliculas.
para la interacion con el usuario decidimos usar react ya que al ser una plataforma de streaming es mas factible usarlo ya que este trabaja con modulos(componentes) y asi trabajar de una manera mas ordenada.
una vez iniciado la sesion,este te mostrara un cuadro de busqueda que llamara a la api respectiva pasandole el parametro y esta solicitando un json para recibir los datos de las peliculas encontradas,estas ultimas contaran con dos botones de ver mas tarde y de like,estos ultimos llamaran a sus apis respectivas.

## Conclusión
En conclusión, el desarrollo de esta plataforma de streaming ha sido un ejercicio integral que nos ha permitido aplicar y consolidar múltiples conceptos de estructuras de datos, patrones de diseño, y algoritmos de búsqueda, con el propósito de proporcionar una experiencia eficiente y amigable para el usuario.
