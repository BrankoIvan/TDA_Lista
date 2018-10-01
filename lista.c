#include "lista.h"
#include <stdbool.h>
#include <stdlib.h>

/******************************************************************************/

typedef struct nodo {
    void* data;
    struct nodo* next;
}nodo_t;

typedef struct lista {
    nodo_t* first;
    nodo_t* last;
    size_t length;
}lista_t;

typedef struct lista_iter {
    lista_t* lista;
    nodo_t* actual;
    nodo_t* anterior;
} lista_iter_t;

/******************************************************************************/

nodo_t* nodo_crear(void* dato){
    nodo_t* nodo = malloc(sizeof(nodo_t));
    if (nodo == NULL) return NULL;

    nodo->data = dato;
    nodo->next = NULL;

    return nodo;
}

void* nodo_destruir(nodo_t* nodo){
    void* dato = nodo->data;
    free(nodo);

    return dato;
}

/******************************************************************************/

lista_t* lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista == NULL) return NULL;

    lista->first = NULL;
    lista->last = NULL;
    lista->length = 0;

    return lista;
}

bool lista_esta_vacia(const lista_t* lista){
    return lista->length == 0;
}

bool lista_insertar_primero(lista_t *lista, void* dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if (nuevo_nodo == NULL) return false;

    if (lista_esta_vacia(lista))
        lista->last = nuevo_nodo;
    else
        nuevo_nodo->next = lista->first;

    lista->first = nuevo_nodo;
    lista->length ++;

    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void* dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if (nuevo_nodo == NULL) return false;

    if (lista_esta_vacia(lista))
        lista->first = nuevo_nodo;
    else
        lista->last->next = nuevo_nodo;

    lista->last = nuevo_nodo;
    lista->length ++;

    return true;
}

void* lista_borrar_primero(lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t* primer_nodo = lista->first;
    lista->first = lista->first->next;
    lista->length --;

    return nodo_destruir(primer_nodo);
}

void* lista_ver_primero(const lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->first->data;
}

void* lista_ver_ultimo(const lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->last->data;
}

size_t lista_largo(const lista_t* lista){
    return lista->length;
}

void lista_destruir(lista_t* lista, void destruir_dato(void*)){
    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL) destruir_dato(dato);
    }

    free(lista);
}

/******************************************************************************/

void lista_iterar(lista_t* lista, bool visitar(void* dato, void* extra), void* extra){
    if (lista_esta_vacia(lista)) return;

    nodo_t* actual = lista->first;

    while (actual != NULL){
        if(!visitar(actual->data, extra)) break;
        actual = actual->next;
    }
}

/******************************************************************************/

lista_iter_t* lista_iter_crear(lista_t* lista){
    lista_iter_t* iter = malloc(sizeof(lista_iter_t));
    if (iter == NULL) return NULL;

    iter->lista = lista;
    iter->anterior = NULL;
    iter->actual = lista->first;
    return iter;
}

bool lista_iter_avanzar(lista_iter_t* iter){
    if (lista_iter_al_final(iter)) return false;

    iter->anterior = iter->actual;
    iter->actual = iter->actual->next;
    return true;
}

void* lista_iter_ver_actual(const lista_iter_t* iter){
    if (lista_iter_al_final(iter)) return NULL;
    return iter->actual->data;
}

bool lista_iter_al_final(const lista_iter_t* iter){
    return iter->actual == NULL;
}

void lista_iter_destruir(lista_iter_t* iter){
    free(iter);
}

bool lista_iter_insertar(lista_iter_t* iter, void* dato){
    nodo_t* nuevo_nodo = nodo_crear(dato);
    if (nuevo_nodo == NULL) return false;
    // Creo un nodo con el valor dado

    nuevo_nodo->next = iter->actual;
    // Hago que el nuevo nodo apunte a mi actual
    iter->actual = nuevo_nodo;
    // Hago que actual apunte al nodo
    if (iter->actual->next == NULL) iter->lista->last = nuevo_nodo;
    // Si mi actual es el ultimo, cambio el ultimo de la lista para que apunte al nodo

    if (iter->anterior == NULL) // Si el anterior es NULL
        iter->lista->first = nuevo_nodo; // actualizo el primero de la lista
    else // Sino 
        iter->anterior->next = nuevo_nodo; // actualizo el anterior
    
    iter->lista->length ++; // aumento el largo de la lista

    return true; // Si llegue hasta aca no hubo errores (supongo), devuelvo true 
}

void* lista_iter_borrar(lista_iter_t* iter){
    if (lista_iter_al_final(iter)) return NULL;

    nodo_t* nodo_auxiliar = iter->actual;
    // Guardo mi nodo actual
    if (iter->actual->next == NULL) iter->lista->last = iter->anterior;
    // Si mi actual es el ultimo, cambio el ultimo de la lista para que apunte al anterior
    iter->actual = iter->actual->next;
    // Muevo el actual al siguiente

    if (iter->anterior == NULL) // Si el anterior es NULL 
        iter->lista->first = iter->actual; // actualizo el primero de la lista
    else // Sino 
        iter->anterior->next = iter->actual; // actualizo el anterior

    iter->lista->length --; // reduzco el largo de la lista

    return nodo_destruir(nodo_auxiliar); // Destruyo el nodo guardado
}
