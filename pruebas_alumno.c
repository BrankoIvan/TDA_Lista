#include "lista.h"
#include "testing.h"
#include <stdio.h>

#define NEWLINE printf("\n");

#define FORN(i,n,m) for(int i = n; i != m; i+= (m-n)/abs(m-n)) /*Necesita <stdlib.h>*/

void test_comportamiento(){
    lista_t* list = lista_crear();   
    char dummy_a = 'a', dummy_b = 'b', dummy_c = 'c';

    printf("\nPRUEBAS BASICAS\n");

    print_test("  Crear lista", list != NULL);
    print_test("  La lista esta vacia", lista_esta_vacia(list));
    print_test("  Borrar primero devuelve NULL", lista_borrar_primero(list) == NULL);
    print_test("  Ver primero devuelve NULL", lista_ver_primero(list) == NULL);
    print_test("  Ver ultimo devuelve NULL", lista_ver_ultimo(list) == NULL);
    print_test("  Largo es 0", lista_largo(list) == 0);
    NEWLINE
    print_test("  Agrego elemento A al principio", lista_insertar_primero(list, &dummy_a));
    print_test("  La lista no esta vacia", !lista_esta_vacia(list));
    print_test("  Ver primero devuelve elemento A", *(char*)lista_ver_primero(list) == dummy_a);
    print_test("  Ver ultimo devuelve elemento A", *(char*)lista_ver_ultimo(list) == dummy_a);
    print_test("  Largo es 1", lista_largo(list) == 1);
    NEWLINE
    print_test("  Agrego elemento B al principio", lista_insertar_primero(list, &dummy_b));
    print_test("  La lista no esta vacia", !lista_esta_vacia(list));
    print_test("  Ver primero devuelve elemento B", *(char*)lista_ver_primero(list) == dummy_b);
    print_test("  Ver ultimo devuelve elemento A", *(char*)lista_ver_ultimo(list) == dummy_a);
    print_test("  Largo es 2", lista_largo(list) == 2);
    NEWLINE
    print_test("  Agrego elemento C al final", lista_insertar_ultimo(list, &dummy_c));
    print_test("  La lista no esta vacia", !lista_esta_vacia(list));
    print_test("  Ver primero devuelve elemento B", *(char*)lista_ver_primero(list) == dummy_b);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(list) == dummy_c);
    print_test("  Largo es 3", lista_largo(list) == 3);
    NEWLINE
    print_test("  Borrar primero devuelve elemento B", *(char*)lista_borrar_primero(list) == dummy_b);
    print_test("  La lista no esta vacia", !lista_esta_vacia(list));
    print_test("  Ver primero devuelve elemento A", *(char*)lista_ver_primero(list) == dummy_a);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(list) == dummy_c);
    print_test("  Largo es 2", lista_largo(list) == 2);
    NEWLINE
    print_test("  Borrar primero devuelve elemento A", *(char*)lista_borrar_primero(list) == dummy_a);
    print_test("  La lista no esta vacia", !lista_esta_vacia(list));
    print_test("  Ver primero devuelve elemento C", *(char*)lista_ver_primero(list) == dummy_c);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(list) == dummy_c);
    print_test("  Largo es 1", lista_largo(list) == 1);
    NEWLINE
    print_test("  Borrar primero devuelve elemento C", *(char*)lista_borrar_primero(list) == dummy_c);
    print_test("  La lista esta vacia", lista_esta_vacia(list));
    print_test("  Ver primero devuelve NULL", lista_ver_primero(list) == NULL);
    print_test("  Ver ultimo devuelve NULL", lista_ver_ultimo(list) == NULL);
    print_test("  Largo es 0", lista_largo(list) == 0);

    NEWLINE
    lista_destruir(list,NULL);
    print_test("  Pude destruir la lista", true);
    //     "Test run exitoso, Valgrind OK, arreglos menores en lista.c"
}

//    print_test("  ",);

void pruebas_lista_alumno(void){
	test_comportamiento();
}
