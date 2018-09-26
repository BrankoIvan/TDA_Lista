#include "lista.h"
#include <stdbool.h>

typedef struct nodo {
    void* data;
    struct nodo* next;
}nodo_t;

typedef struct lista {
    nodo_t* first;
    nodo_t* last;
    size_t length;
}lista_t;


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


lista_t *lista_crear(void){
    lista_t* lista = malloc(sizeof(lista_t));
    if(lista == NULL) return NULL;

    lista->first = NULL;
    lista->last = NULL;
    lista->length = 0;

    return lista;
}

bool lista_esta_vacia(const lista_t *lista){
    return lista->length == 0;
}

bool lista_insertar_primero(lista_t *lista, void *dato){
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) return false;

    if (lista_esta_vacia(lista))
        lista->last = nodo;
    else
        nodo->next = lista->first;

    lista->first = nodo;
    lista->length++;

    return true;
}

bool lista_insertar_ultimo(lista_t *lista, void *dato){
    nodo_t* nodo = nodo_crear(dato);
    if (nodo == NULL) return false;

    if (lista_esta_vacia(lista))
        lista->first = nodo;
    else
        lista->last->next = nodo;

    lista->last = nodo;
    lista->length++;

    return true;
}

void* lista_borrar_primero(lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;

    nodo_t* nodo = lista->first;
    lista->first = lista->first->next;
    lista->length--;

    return nodo_destruir(nodo);
}

void* lista_ver_primero(const lista_t *lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->first->data;
}

void* lista_ver_ultimo(const lista_t* lista){
    if (lista_esta_vacia(lista)) return NULL;
    return lista->last->data;
}

size_t lista_largo(const lista_t *lista){
    return lista->length;
}

void lista_destruir(lista_t *lista, void destruir_dato(void *)){
    while(!lista_esta_vacia(lista)){
        void* dato = lista_borrar_primero(lista);
        if (destruir_dato != NULL);
            destruir_dato(dato);
    }
    free(lista);
}
