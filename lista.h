#include <stdlib.h>
#include <stdbool.h>

/******************************************************************************/
/*                             Tipos de datos                                 */
/******************************************************************************/

typedef struct lista lista_t;
typedef struct lista_iter lista_iter_t;


/******************************************************************************/
/*                         Primitivas de la Lista                             */
/******************************************************************************/

// Crea una lista.
// Post: devuelve una lista vacia.
lista_t* lista_crear(void);

// Verifica si la lista tiene elementos o no.
// Pre: la lista fue creada.
bool lista_esta_vacia(const lista_t *lista);

// Agrega un nuevo elemento al principio de la lista. Devuelve falso en caso de error.
// Pre: La lista fue creada.
// Post: se agrego un nuevo elemento a la lista, dato se encuentra al principio 
// de la lista.
bool lista_insertar_primero(lista_t *lista, void *dato);

// Agrega un nuevo elemento al final de la lista. Devuelve falso en caso de error.
// Pre: La lista fue creada.
// Post: se agrego un nuevo elemento a la lista, dato se encuentra al final de la lista.
bool lista_insertar_ultimo(lista_t *lista, void *dato);

// Borra el primer elemento de la lista. Si la lista tiene elementos, borra el
// primero de la lista y devuelve su dato, si esta vacia, devuelve NULL.
// Pre: La lista fue creada.
// Post: Se devolvio el dato del primer elemento. La lista tiene un elemento menos 
// si la lista no esta vacia
void* lista_borrar_primero(lista_t *lista);

// Obtiene el dato del primer elemento de la lista. Si la lista tiene
// elementos, se devuelve el dato del primero, si está vacía devuelve NULL.
// Pre: La lista fue creada
// Post: Devuelve el primer elemento de la lista o NULL si no tiene elementos
void* lista_ver_primero(const lista_t *lista);

// Obtiene el dato del ultimo elemento de la lista. Si la lista tiene
// elementos, se devuelve el dato del ultimo, si está vacía devuelve NULL.
// Pre: La lista fue creada
// Post: Devuelve el ultimo elemento elemento de la lista o NULL si no tiene elementos
void* lista_ver_ultimo(const lista_t* lista);

// Obtiene la cantidad de elementos en la lista
// Pre: La lista fue creada
// Post: Devuelve la cantidad de elementos en la lista
size_t lista_largo(const lista_t *lista);

// Destruye la lista. Si se recibe la función destruir_dato por parámetro,
// llama a la misma para todos los elementos de la lista.
// Pre: la lista fue creada. destruir_dato es una función capaz de destruir
// los datos de la cola, o NULL en caso de que no se la utilice.
// Post: se eliminaron todos los elementos de la lista.
void lista_destruir(lista_t *lista, void destruir_dato(void *));


/******************************************************************************/
/*                   Primitivas del Iterador Interno                          */
/******************************************************************************/

// 
//
void lista_iterar(lista_t *lista, bool visitar(void *dato, void *extra), void *extra);


/******************************************************************************/
/*                   Primitivas del Iterador Externo                          */
/******************************************************************************/

// Crea un un iterador externo para una lista.
// Post: devuelve un iterador iniciado en el primer elemento de la lista.
lista_iter_t *lista_iter_crear(lista_t *lista);

// 
// Pre: El iterador fue creado
// Post: 
bool lista_iter_avanzar(lista_iter_t *iter);

// 
// Pre: El iterador fue creado
// Post: 
void *lista_iter_ver_actual(const lista_iter_t *iter);

// 
// Pre: El iterador fue creado
// Post: 
bool lista_iter_al_final(const lista_iter_t *iter);

// 
// Pre: El iterador fue creado
// Post: 
void lista_iter_destruir(lista_iter_t *iter);

// 
// Pre: El iterador fue creado
// Post: 
bool lista_iter_insertar(lista_iter_t *iter, void *dato);

// 
// Pre: El iterador fue creado
// Post: 
void *lista_iter_borrar(lista_iter_t *iter);


/* ------------Pruebas Unitarias------------- */

// Realiza pruebas sobre la implementación del alumno.
//
void pruebas_lista_alumno(void);
