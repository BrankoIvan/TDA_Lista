#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define CADENA_1 "abcde"
#define CADENA_2 "FGHIJ"
#define N_MUCHOS 10000 // Cantidad de elementos con los que se maneja la prueba de volumen
#define N_VARIOS 5 // La cantidad de lineas impresa por pantalla es linealmente dependiente de este numero, debe ser mayor a 0 y menor a 10

#define CREAR_LISTA() lista_t* lista = lista_crear()
#define CREAR_ITERADOR(iter_name, list_name) lista_iter_t* iter_name = lista_iter_crear(list_name)
#define FORN(x, n, m) for(int x = n; x != m; x += (m-n)/abs(m-n)) /*Necesita <stdlib.h>*/
#define PRINT_END_OF_LINE() printf("\n")
#define PRINT_SEPARATOR() printf("\n**********************************************************************")

/******************************************************************************/
// ESTRUCTURA AUXILIAR PARA PRUEBA DE DESTRUCCION

typedef struct estructura_de_prueba {
    void** datos;
} test_t;

test_t* estructura_crear(){
    test_t* estructura = malloc(sizeof(test_t));
    if (estructura == NULL) return NULL;

    estructura->datos = malloc(sizeof(void*));
    if (estructura->datos == NULL){
        free(estructura);
        return NULL;
    }

    return estructura;
}

void _estructura_destruir(test_t* estructura){
    free(estructura->datos);
    free(estructura);
}

void estructura_destruir(void* elemento){
    _estructura_destruir((test_t*) elemento);
}

/******************************************************************************/
// FUNCIONES AUXILIARES PARA PRUEBAS DEL ITERADOR INTERNO

bool imprimir_todo_d(void* valor, void* extra){
    if (valor == NULL) printf("_ ");
    printf("%d ", *(int*)valor);
    return true;
}

bool imprimir_todo_c(void* valor, void* extra){
    if (valor == NULL) printf("_ ");
    else printf("%c ", *(char*)valor);
    return true;
}

bool contar_elementos(void* valor, void* extra){
    *(int*) extra += 1;
    return true;
}

bool recorrer_todo(void* valor, void* extra){
    printf("      Valor dado [%d] es el esperado", *(int*) valor);
    print_test("", *(int*) valor == *(int*) extra);
    *(int*) extra += 1;
    return true;
}

bool recorrer_hasta(void* valor, void* extra){
    if (*(int*) extra == 0) return false;
    printf("%d ", *(int*) valor);
    *(int*) extra -= 1;
    return true;
}

bool duplicar_valores(void* valor, void* extra){
    printf("      Valor dado [%d]", *(int*) valor);
    *(int*) valor = N_VARIOS*3 - *(int*) valor;
    printf(" se cambio correctamente a [%d]", *(int*) valor);
    print_test("", *(int*) valor == *(int*) extra);
    *(int*) extra -= 1;
    return true;
}

/******************************************************************************/
// FUNCIONES AUXILIARES PARA PRUEBAS DEL ITERADOR EXTERNO

void mostrar_estado(lista_t* lista){
    printf("\n        Estado de la lista: (Elemento NULL se representan con '_')\n");
    printf("        [ ");
    lista_iterar(lista, imprimir_todo_c, NULL);
    printf("]\n");
    printf("        Largo: %d\n", (int)lista_largo(lista));
    if (lista_esta_vacia(lista)){
        printf("        Esta Vacia\n");
    } else {
        printf("        Primero: ");
        if (lista_ver_primero(lista))
            printf("%c\n", *(char*)lista_ver_primero(lista));
        else
            printf("_\n");

        printf("        ULtimo : ");
        if (lista_ver_primero(lista))
            printf("%c\n\n", *(char*)lista_ver_ultimo(lista));
        else
            printf("_\n\n");
    }
}

/******************************************************************************/
// PRUEBAS DE LA LISTA

void test_lista_comportamiento(){
    CREAR_LISTA();      
    char dummy_a = 'a', dummy_b = 'b';

    PRINT_SEPARATOR();
    printf("\nPRUEBA - LISTA: COMPORTAMIENTO BASICO\n");

    PRINT_END_OF_LINE();
    print_test("  Crear lista", lista != NULL);
    print_test("  La lista esta vacia", lista_esta_vacia(lista));
    print_test("  Borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("  Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("  Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("  Largo es 0", lista_largo(lista) == 0);
    PRINT_END_OF_LINE();
    print_test("  Agrego elemento A al principio", lista_insertar_primero(lista, &dummy_a));
    print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Ver primero devuelve elemento A", *(char*)lista_ver_primero(lista) == dummy_a);
    print_test("      Ver ultimo devuelve elemento A", *(char*)lista_ver_ultimo(lista) == dummy_a);
    print_test("      Largo es 1", lista_largo(lista) == 1);
    PRINT_END_OF_LINE();
    print_test("  Agrego elemento B al final", lista_insertar_ultimo(lista, &dummy_b));
    print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Ver primero devuelve elemento A", *(char*)lista_ver_primero(lista) == dummy_a);
    print_test("      Ver ultimo devuelve elemento B", *(char*)lista_ver_ultimo(lista) == dummy_b);
    print_test("      Largo es 2", lista_largo(lista) == 2);
    PRINT_END_OF_LINE();
    print_test("  Borrar primero devuelve elemento A", *(char*)lista_borrar_primero(lista) == dummy_a);
    print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Ver primero devuelve elemento B", *(char*)lista_ver_primero(lista) == dummy_b);
    print_test("      Ver ultimo devuelve elemento B", *(char*)lista_ver_ultimo(lista) == dummy_b);
    print_test("      Largo es 1", lista_largo(lista) == 1);
    PRINT_END_OF_LINE();
    print_test("  Borrar primero devuelve elemento B", *(char*)lista_borrar_primero(lista) == dummy_b);
    print_test("      La lista esta vacia", lista_esta_vacia(lista));
    print_test("      Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("      Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("      Largo es 0", lista_largo(lista) == 0);

    PRINT_END_OF_LINE();
    lista_destruir(lista,NULL);
    print_test("  Pude destruir la lista", true);
}

void test_lista_comportamiento_extendido(){
    CREAR_LISTA();
    int vector_1[N_VARIOS], vector_2[N_VARIOS], medio = 0;
    FORN(i, 0, N_VARIOS){
        vector_1[i] = i+1;
        vector_2[i] = -(i+1);
    }

    PRINT_SEPARATOR();;
    printf("\nPRUEBA - LISTA: COMPORTAMIENTO EXTENDIDO\n");

    PRINT_END_OF_LINE();
    print_test("  Agrego elemento 0 al principio", lista_insertar_primero(lista, &medio));

    PRINT_END_OF_LINE();
    FORN(i, 0, N_VARIOS){
        printf("  Agrego %d al principio", i+1);
        print_test("",lista_insertar_primero(lista, &vector_1[i]));
        printf("  Agrego %d al final", -(i+1));
        print_test("",lista_insertar_ultimo(lista, &vector_2[i]));
        printf("  Ver primero devuelve %d", i+1);
        print_test("", *(int*)lista_ver_primero(lista) == vector_1[i]);
        printf("  Ver ultimo devuelve %d", -(i+1));
        print_test("", *(int*)lista_ver_ultimo(lista) == vector_2[i]);
        print_test("  Largo es el esperado", lista_largo(lista) == 1+(i+1)*2);
        PRINT_END_OF_LINE();
    }

    size_t indice = 1+N_VARIOS*2;

    FORN(i, N_VARIOS, -N_VARIOS){
        print_test("  Borrar primero devuelve lo esperado", *(int*)lista_borrar_primero(lista) == i);
        print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
        print_test("      Ver primero devuelve lo esperado", *(int*)lista_ver_primero(lista) == i-1);
        print_test("      Ver ultimo devuelve lo esperado", *(int*)lista_ver_ultimo(lista) == -N_VARIOS);
        print_test("      Largo es el esperado", lista_largo(lista) == indice-1); indice--;
        PRINT_END_OF_LINE();
    }

    print_test("  Borrar primero devuelve lo esperado", *(int*)lista_borrar_primero(lista) == -N_VARIOS);
    print_test("  La lista esta vacia", lista_esta_vacia(lista));

    lista_destruir(lista,NULL);
}

void test_lista_algunos_elementos(){
    CREAR_LISTA();
    char dummy[] = CADENA_1;

    PRINT_SEPARATOR();;
    printf("\nPRUEBA - LISTA: VARIOS ELEMENTOS\n");

    PRINT_END_OF_LINE();
    FORN(i, 0, N_VARIOS){
        print_test("  Agrego un elemento al principio", lista_insertar_primero(lista, &dummy[i]));
        print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
        print_test("      Ver primero devuelve lo esperado", *(char*)lista_ver_primero(lista) == dummy[i]);
        print_test("      Ver ultimo devuelve lo esperado", *(char*)lista_ver_ultimo(lista) == dummy[0]);
        print_test("      Largo es el esperado", lista_largo(lista) == i+1);
        PRINT_END_OF_LINE();
    }

    PRINT_END_OF_LINE();
    FORN(i, N_VARIOS-1, 0){
        print_test("  Borrar primero devuelve lo esperado", *(char*)lista_borrar_primero(lista) == dummy[i]);
        print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
        print_test("      Ver primero devuelve lo esperado", *(char*)lista_ver_primero(lista) == dummy[i-1]);
        print_test("      Ver ultimo devuelve lo esperado", *(char*)lista_ver_ultimo(lista) == dummy[0]);
        print_test("      Largo es el esperado", lista_largo(lista) == i);
        PRINT_END_OF_LINE();
    }

    PRINT_END_OF_LINE();
    FORN(i, 1, N_VARIOS){ // 1 porque todavia tengo el primer elemento en la lista y no quiero repetirlo
        print_test("  Agrego un elemento al final", lista_insertar_ultimo(lista, &dummy[i]));
        print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
        print_test("      Ver primero devuelve lo esperado", *(char*)lista_ver_primero(lista) == dummy[0]);
        print_test("      Ver ultimo devuelve lo esperado", *(char*)lista_ver_ultimo(lista) == dummy[i]);
        print_test("      Largo es el esperado", lista_largo(lista) == i+1);
        PRINT_END_OF_LINE();
    }

    PRINT_END_OF_LINE();
    FORN(i, 0, N_VARIOS-1){
        print_test("  Borrar primero devuelve lo esperado", *(char*)lista_borrar_primero(lista) == dummy[i]);
        print_test("      La lista no esta vacia", !lista_esta_vacia(lista));
        print_test("      Ver primero devuelve lo esperado", *(char*)lista_ver_primero(lista) == dummy[i+1]);
        print_test("      Ver ultimo devuelve lo esperado", *(char*)lista_ver_ultimo(lista) == dummy[N_VARIOS-1]);
        print_test("      Largo es el esperado", lista_largo(lista) == N_VARIOS-i-1);
        PRINT_END_OF_LINE();
    }

    lista_destruir(lista,NULL);
}

void test_lista_volumen(){
    CREAR_LISTA();
    int vector[N_MUCHOS]; FORN(i, 0, N_MUCHOS) vector[i] = i;
    size_t fallos;

    PRINT_SEPARATOR();;
    printf("\nPRUEBA - LISTA: VOLUMEN\n");

    fallos = 0;
    FORN(i,0,N_MUCHOS){
        if (!lista_insertar_primero(lista, &vector[i])) fallos ++; 
        if (!lista_insertar_ultimo(lista, &vector[i])) fallos ++;
        if (*(int*)lista_ver_primero(lista) != vector[i]) fallos ++; 
        if (*(int*)lista_ver_ultimo(lista) != vector[i]) fallos ++; 
        if (lista_esta_vacia(lista)) fallos ++; 
        if (lista_largo(lista) != (i+1)*2) fallos ++;
    }
    PRINT_END_OF_LINE();
    printf("  Agrego elementos verificando invariantes:\n");
    printf("      Invariantes no mantenidas: %d", (int)fallos);
    print_test("", fallos == 0);

    // Termine con una lista que tiene 2 veces el vector de prueba
    fallos = 0;
    size_t indice = N_MUCHOS*2;
    FORN(i, N_MUCHOS-1, -1){
        if (*(int*)lista_borrar_primero(lista) != i) fallos ++;
        if (*(int*)lista_ver_primero(lista) != vector[i-1]) fallos ++;
        if (*(int*)lista_ver_ultimo(lista) != vector[N_MUCHOS-1]) fallos ++;
        if (lista_esta_vacia(lista)) fallos ++;
        if (lista_largo(lista) != indice-1) fallos ++; indice--;
    }
    FORN(i, 0, N_MUCHOS-1){
        if (*(int*)lista_borrar_primero(lista) != i) fallos ++;
        if (*(int*)lista_ver_primero(lista) != vector[i+1]) fallos ++;
        if (*(int*)lista_ver_ultimo(lista) != vector[N_MUCHOS-1]) fallos ++;
        if (lista_esta_vacia(lista)) fallos ++;
        if (lista_largo(lista) != indice-1) fallos ++; indice--;
    }

    if (*(int*)lista_borrar_primero(lista) != N_MUCHOS-1) fallos ++;
    if (lista_ver_primero(lista) != NULL) fallos ++;
    if (lista_ver_ultimo(lista) != NULL) fallos ++;
    if (!lista_esta_vacia(lista)) fallos ++;
    if (lista_largo(lista) != 0) fallos ++;    

    printf("  Borro elementos verificando invariantes:\n");
    printf("      Invariantes no mantenidas: %d", (int)fallos);
    print_test("", fallos == 0);

    lista_destruir(lista, NULL);
}

void test_lista_NULL(){
    CREAR_LISTA();

    PRINT_SEPARATOR();;
    printf("\nPRUEBA - LISTA: MANEJO DE ELEMENTOS NULL\n");

    PRINT_END_OF_LINE();
    print_test("  Agrego NULL al principio", lista_insertar_primero(lista, NULL));
    print_test("      Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Pero ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("      Ver ultimo tambien devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("      Largo es 1", lista_largo(lista) == 1);
    PRINT_END_OF_LINE();
    print_test("  Agrego NULL al final", lista_insertar_ultimo(lista, NULL));
    print_test("      Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Pero ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("      Ver ultimo tambien devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("      Largo es 2", lista_largo(lista) == 2);
    PRINT_END_OF_LINE();
    print_test("  Agrego NULL al principio", lista_insertar_primero(lista, NULL));
    print_test("      Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Pero ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("      Ver ultimo tambien devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("      Largo es 1", lista_largo(lista) == 3);
    PRINT_END_OF_LINE();
    print_test("  Agrego NULL al final", lista_insertar_ultimo(lista, NULL));
    print_test("      Lista no esta vacia", !lista_esta_vacia(lista));
    print_test("      Pero ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("      Ver ultimo tambien devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("      Largo es 2", lista_largo(lista) == 4);
    size_t fallos = 0;
    FORN(_, 0, 4)if (lista_borrar_primero(lista) != NULL) fallos++;
    PRINT_END_OF_LINE();
    print_test("  Borrar el primero 4 veces", fallos == 0);
    print_test("      La lista esta vacia", lista_esta_vacia(lista));
    print_test("      Largo es 0", lista_largo(lista) == 0);

    lista_destruir(lista,NULL);
}

void test_lista_destruccion(){
    lista_t* lista = lista_crear();

    PRINT_SEPARATOR();
    printf("\nPRUEBA - LISTA: DISTINTOS TIPOS DE DESTRUCCION\n");

    int vector[N_VARIOS*2]; 
    FORN(i, 0, N_VARIOS*2){
        vector[i] = i;
        lista_insertar_ultimo(lista, &vector[i]);
    }
    lista_destruir(lista,NULL);
    print_test("  Pude destruir una lista con elementos estaticos", true);

    lista = lista_crear();
    FORN(i, 0, N_VARIOS*2) lista_insertar_ultimo(lista, malloc(sizeof(void*)));
    lista_destruir(lista, free);
    print_test("  Pude destruir una lista con elementos dinamicos", true);

    lista = lista_crear();
    FORN(i, 0, N_VARIOS*2) lista_insertar_ultimo(lista, estructura_crear());
    lista_destruir(lista, estructura_destruir);
    print_test("  Pude destruir una lista con estructuras", true);

}

/******************************************************************************/
// PRUEBAS DEL ITERADOR EXTERNO

void test_iter_e_comportamiento(){
    CREAR_LISTA();
    CREAR_ITERADOR(iter, lista);
    char dummy_a = 'a', dummy_b = 'b';

    PRINT_SEPARATOR();
    printf("\nPRUEBA - ITERADOR EXTERNO: COMPORTAMIENTO BASICO\n");

    PRINT_END_OF_LINE();
    print_test("  Creo iterador con lista vacia", iter != NULL);
    print_test("      Estoy al final", lista_iter_al_final(iter));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter));
    print_test("      Borrar es invalido", lista_iter_borrar(iter) == NULL);

    PRINT_END_OF_LINE();
    print_test("  Agrego elemento A con el iterador", lista_iter_insertar(iter, &dummy_a));
    print_test("      No estoy al final", !lista_iter_al_final(iter));
    print_test("      Ver actual devuelve el elemento A", *(char*)lista_iter_ver_actual(iter) == dummy_a);
    print_test("  Borrar es valido y devuelve el elemento A", *(char*)lista_iter_borrar(iter) == dummy_a);
    print_test("      Estoy al final", lista_iter_al_final(iter));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter));
    print_test("      Borrar es invalido", lista_iter_borrar(iter) == NULL);

    PRINT_END_OF_LINE();
    print_test("  Agrego elemento A con el iterador", lista_iter_insertar(iter, &dummy_a));
    print_test("      No estoy al final", !lista_iter_al_final(iter));
    print_test("      Ver actual devuelve el elemento A", *(char*)lista_iter_ver_actual(iter) == dummy_a); 
    print_test("  Agrego elemento B con el iterador", lista_iter_insertar(iter, &dummy_b));
    print_test("      No estoy al final", !lista_iter_al_final(iter));
    print_test("      Ver actual devuelve el elemento B", *(char*)lista_iter_ver_actual(iter) == dummy_b);
    print_test("  Borrar es valido y devuelve el elemento B", *(char*)lista_iter_borrar(iter) == dummy_b);
    print_test("      No estoy al final", !lista_iter_al_final(iter));
    print_test("      Ver actual devuelve el elemento A", *(char*)lista_iter_ver_actual(iter) == dummy_a);
    print_test("  Borrar es valido y devuelve el elemento A", *(char*)lista_iter_borrar(iter) == dummy_a);
    print_test("      Estoy al final", lista_iter_al_final(iter));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter));
    print_test("      Borrar es invalido", lista_iter_borrar(iter) == NULL);

    lista_iter_destruir(iter);
    print_test("\n  Destruyo el iterador", true);
    lista_destruir(lista,NULL);    
}

void test_iter_e_comportamiento_monitoreado(){  //No se me ocurrio un mejor nombre
    CREAR_LISTA();
    CREAR_ITERADOR(iter, lista);
    char dummy_1[N_VARIOS] = CADENA_1;
    char dummy_2[N_VARIOS] = CADENA_2;

    PRINT_SEPARATOR();
    printf("\nPRUEBA - ITERADOR EXTERNO: MANEJO DE VARIOS ITERADORES, MONITOREADO CON PRIMITIVAS DE LA LISTA\n");

    PRINT_END_OF_LINE();
    print_test("  Creo iterador con lista vacia", iter != NULL);
    print_test("      Estoy al final", lista_iter_al_final(iter));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter));
    print_test("      Borrar es invalido", lista_iter_borrar(iter) == NULL);
    //mostrar_estado(lista);

    PRINT_END_OF_LINE();
    FORN(i, 0, N_VARIOS){
        print_test("  Agrego elemento con el iterador", lista_iter_insertar(iter, &dummy_1[i]));
        print_test("      No estoy al final", !lista_iter_al_final(iter));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter) == dummy_1[i]);
        printf("      Actual: %c\n", *(char*)lista_iter_ver_actual(iter));
        //mostrar_estado(lista);
    }

    PRINT_END_OF_LINE();
    FORN(i, N_VARIOS-1, 0){
        print_test("  Avanzar es valido", lista_iter_avanzar(iter));
        print_test("      No estoy al final", !lista_iter_al_final(iter));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter) == dummy_1[i-1]);
        printf("      Actual: %c\n", *(char*)lista_iter_ver_actual(iter));
    }

    print_test("  Avanzar es valido", lista_iter_avanzar(iter));
    print_test("      Estoy al final", lista_iter_al_final(iter));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter));
    print_test("      Borrar es invalido", lista_iter_borrar(iter) == NULL);

    lista_iter_destruir(iter);
    print_test("\n  Destruyo el iterador", true);

    /*-----------------------------------------------------------------------------*/

    CREAR_ITERADOR(iter_2, lista);
    PRINT_END_OF_LINE();
    print_test("  Creo otro iterador para la lista", iter_2 != NULL);
    print_test("      No estoy al final", !lista_iter_al_final(iter_2));
    print_test("      Ver actual devuelve el elemento esperado", *(char*)lista_iter_ver_actual(iter_2) == dummy_1[N_VARIOS-1]);

    PRINT_END_OF_LINE();
    FORN(i, 0, N_VARIOS){
        print_test("  Agrego elemento con el nuevo iterador", lista_iter_insertar(iter_2, &dummy_2[i]));
        print_test("      No estoy al final", !lista_iter_al_final(iter_2));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_2) == dummy_2[i]);
        printf("      Actual: %c\n", *(char*)lista_iter_ver_actual(iter_2));
        //mostrar_estado(lista);
    }

    PRINT_END_OF_LINE();
    FORN(i, N_VARIOS-1, 0){
        print_test("  Avanzar es valido", lista_iter_avanzar(iter_2));
        print_test("      No estoy al final", !lista_iter_al_final(iter_2));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_2) == dummy_2[i-1]);
        printf("      Actual: %c\n", *(char*)lista_iter_ver_actual(iter_2));
    }

    FORN(i, N_VARIOS-1, -1){
        print_test("  Avanzar es valido", lista_iter_avanzar(iter_2));
        print_test("      No estoy al final", !lista_iter_al_final(iter_2));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_2) == dummy_1[i]);
        printf("      Actual: %c\n", *(char*)lista_iter_ver_actual(iter_2));
    }

    print_test("  Avanzar es valido", lista_iter_avanzar(iter_2));
    print_test("      Estoy al final", lista_iter_al_final(iter_2));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter_2) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter_2));
    print_test("      Borrar es invalido", lista_iter_borrar(iter_2) == NULL);
    lista_iter_destruir(iter_2);
    print_test("\n  Destruyo el segundo iterador", true);

    /*-----------------------------------------------------------------------------*/

    CREAR_ITERADOR(iter_3, lista);
    PRINT_END_OF_LINE();
    print_test("  Creo otro iterador para la lista", iter_3 != NULL);
    print_test("      No estoy al final", !lista_iter_al_final(iter_3));
    print_test("      Ver actual devuelve el elemento esperado", *(char*)lista_iter_ver_actual(iter_3) == dummy_2[N_VARIOS-1]);

    PRINT_END_OF_LINE();
    FORN(i, N_VARIOS-1, 0){
        print_test("  Borrar devuelve el esperado", *(char*)lista_iter_borrar(iter_3) == dummy_2[i]);
        print_test("      No estoy al final", !lista_iter_al_final(iter_3));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_3) == dummy_2[i-1]);
        printf("      Actual: %c\n\n", *(char*)lista_iter_ver_actual(iter_3));
    }

    print_test("  Borrar devuelve el esperado", *(char*)lista_iter_borrar(iter_3) == dummy_2[0]);
    print_test("      No estoy al final", !lista_iter_al_final(iter_3));
    print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_3) == dummy_1[N_VARIOS-1]);

    FORN(i, N_VARIOS-1, 0){
        print_test("  Borrar devuelve el esperado", *(char*)lista_iter_borrar(iter_3) == dummy_1[i]);
        print_test("      No estoy al final", !lista_iter_al_final(iter_3));
        print_test("      Ver actual devuelve el elemento", *(char*)lista_iter_ver_actual(iter_3) == dummy_1[i-1]);
        printf("      Actual: %c\n\n", *(char*)lista_iter_ver_actual(iter_3));
    }

    print_test("  Borrar devuelve el esperado", *(char*)lista_iter_borrar(iter_3) == dummy_1[0]);
    print_test("      Estoy al final", lista_iter_al_final(iter_3));
    print_test("      Ver actual es NULL", lista_iter_ver_actual(iter_3) == NULL);
    print_test("      Avanzar es invalido", !lista_iter_avanzar(iter_3));
    print_test("      Borrar es invalido", lista_iter_borrar(iter_3) == NULL);

    /*-----------------------------------------------------------------------------*/

    mostrar_estado(lista);
    lista_iter_destruir(iter_3);
    print_test("\n  Destruyo el tercer iterador", true);

    lista_destruir(lista, NULL);
}

void test_iter_e_NULL(){
    CREAR_LISTA();
    FORN(i, 0, N_VARIOS) lista_insertar_ultimo(lista, NULL);

    PRINT_SEPARATOR();
    printf("\nPRUEBA - ITERADOR EXTERNO: LISTA CON ELEMENTOS NULL\n");

    mostrar_estado(lista);

    /*--------------------------------------------------------------------------*/

    CREAR_ITERADOR(iter, lista);
    FORN(i, 0, N_VARIOS){
        if (lista_iter_al_final(iter)) printf("    Estoy al final\n");
        if (lista_iter_ver_actual(iter) != NULL) printf("    Actual no es NULL\n");
        if (!lista_iter_avanzar(iter)) printf("   No puedo avanzar\n");
    }
    printf("  Recorri lista con elementos NULL\n");

    FORN(i, 0, N_VARIOS){
        PRINT_END_OF_LINE();
        print_test("  Agrego elemento NULL con el iterador", lista_iter_insertar(iter, NULL));
        print_test("      Ver actual es NULL", lista_iter_ver_actual(iter) == NULL);
        print_test("      Pero no estoy al final", !lista_iter_al_final(iter));
        print_test("  Avanzar es valido", lista_iter_avanzar(iter));
        print_test("      Ver actual devuelve NULL", lista_iter_ver_actual(iter) == NULL);
        print_test("      Estoy al final", lista_iter_al_final(iter));
        print_test("      Borrar es invalido", !lista_iter_borrar(iter));
        //mostrar_estado(lista);
    }

    mostrar_estado(lista);
    lista_iter_destruir(iter);
    printf("  Destruyo el iterador\n");

    /*--------------------------------------------------------------------------*/

    CREAR_ITERADOR(iter_2, lista);
    printf("  Creo otro iterador\n");

    FORN(i, 0, N_VARIOS*2){
        PRINT_END_OF_LINE();
        print_test("  No estoy al final", !lista_iter_al_final(iter_2));
        print_test("  Pero borrar devuelve NULL", lista_iter_borrar(iter_2) == NULL);
        //mostrar_estado(lista);
    }

    mostrar_estado(lista);
    lista_iter_destruir(iter_2);

    /*--------------------------------------------------------------------------*/

    lista_destruir(lista, NULL);
}

/******************************************************************************/
// PRUEBAS DEL ITERADOR INTERNO

void test_iter_i_comportamiento(){
    CREAR_LISTA();
    int extra = 0;

    PRINT_SEPARATOR();
    printf("\nPRUEBA - ITERADOR INTERNO: COMPORTAMIENTO\n");

    printf("\n  Recorro lista vacia");
    lista_iterar(lista, contar_elementos, &extra);
    print_test("", extra == 0);

    int vector[N_VARIOS*3]; 
    FORN(i, 0, N_VARIOS*3){
        vector[i] = i;
        lista_insertar_ultimo(lista, &vector[i]);
    }

    printf("\n  Agrego %d elementos con primitivas de la lista", N_VARIOS*3);
    printf("\n  Recorro la lista completa\n");
    lista_iterar(lista, recorrer_todo, &extra);

    printf("\n  Altero los valores de la lista\n");
    extra = N_VARIOS*3;
    lista_iterar(lista, duplicar_valores, &extra);

    printf("\n  Recorro hasta la mitad [ ");
    extra = N_VARIOS*3/2;
    lista_iterar(lista, recorrer_hasta, &extra);
    print_test("] ", extra == 0);

    printf("\n  Trato de recorrer mas elementos de los que hay [ ");
    extra = 1 + N_VARIOS*3;
    lista_iterar(lista, recorrer_hasta, &extra);
    print_test("] ", extra == 1);

    lista_destruir(lista, NULL);
}

/******************************************************************************/

void pruebas_lista_alumno(void){
    test_lista_comportamiento();
    test_lista_comportamiento_extendido();
    test_lista_algunos_elementos();
    test_lista_volumen();
    test_lista_NULL();
    test_lista_destruccion();

    test_iter_e_comportamiento();
    test_iter_e_comportamiento_monitoreado();
    test_iter_e_NULL();

    test_iter_i_comportamiento();
}
