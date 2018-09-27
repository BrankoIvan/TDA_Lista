#include "lista.h"
#include "testing.h"
#include <stdio.h>
#include <stdlib.h>

#define CANTIDAD_VALORES ((int)10)
#define SUMATORIA ((int) (CANTIDAD_VALORES - 1) * (CANTIDAD_VALORES) / 2)
#define TEST_N_1 ((int)100)

#define NEWLINE printf("\n");

#define FORN(i,n,m) for(int i = n; i != m; i+= (m-n)/abs(m-n)) /*Necesita <stdlib.h>*/

bool visitar_1(void* valor, void* extra){
	printf("%d ", *(int*)valor);
	*(int*)extra += 1;
	return true;
}

bool visitar_2(void* valor, void* extra){
	if(*(int*)extra == 0) return false;
	printf("%d ", *(int*)valor);
	*(int*)extra -= 1;
	return true;
}

bool visitar_3(void* valor, void* extra){
	*(int*)extra += *(int*)valor;
	return true;
}


lista_t* dummy_list(){
	lista_t* lista = lista_crear();
	if (lista == NULL) return NULL;

	FORN(i, 0, CANTIDAD_VALORES){
		int* n = malloc(sizeof(int));
		*n = i;
		lista_insertar_ultimo(lista, n);
	}

	return lista;
}

void test_lista_comportamiento(){
    lista_t* lista = lista_crear();   
    char dummy_a = 'a', dummy_b = 'b', dummy_c = 'c';

    printf("\nPRUEBAS BASICAS\n");

    print_test("  Crear lista", lista != NULL);
    print_test("  La lista esta vacia", lista_esta_vacia(lista));
    print_test("  Borrar primero devuelve NULL", lista_borrar_primero(lista) == NULL);
    print_test("  Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("  Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("  Largo es 0", lista_largo(lista) == 0);
    NEWLINE
    print_test("  Agrego elemento A al principio", lista_insertar_primero(lista, &dummy_a));
    print_test("  La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("  Ver primero devuelve elemento A", *(char*)lista_ver_primero(lista) == dummy_a);
    print_test("  Ver ultimo devuelve elemento A", *(char*)lista_ver_ultimo(lista) == dummy_a);
    print_test("  Largo es 1", lista_largo(lista) == 1);
    NEWLINE
    print_test("  Agrego elemento B al principio", lista_insertar_primero(lista, &dummy_b));
    print_test("  La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("  Ver primero devuelve elemento B", *(char*)lista_ver_primero(lista) == dummy_b);
    print_test("  Ver ultimo devuelve elemento A", *(char*)lista_ver_ultimo(lista) == dummy_a);
    print_test("  Largo es 2", lista_largo(lista) == 2);
    NEWLINE
    print_test("  Agrego elemento C al final", lista_insertar_ultimo(lista, &dummy_c));
    print_test("  La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("  Ver primero devuelve elemento B", *(char*)lista_ver_primero(lista) == dummy_b);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(lista) == dummy_c);
    print_test("  Largo es 3", lista_largo(lista) == 3);
    NEWLINE
    print_test("  Borrar primero devuelve elemento B", *(char*)lista_borrar_primero(lista) == dummy_b);
    print_test("  La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("  Ver primero devuelve elemento A", *(char*)lista_ver_primero(lista) == dummy_a);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(lista) == dummy_c);
    print_test("  Largo es 2", lista_largo(lista) == 2);
    NEWLINE
    print_test("  Borrar primero devuelve elemento A", *(char*)lista_borrar_primero(lista) == dummy_a);
    print_test("  La lista no esta vacia", !lista_esta_vacia(lista));
    print_test("  Ver primero devuelve elemento C", *(char*)lista_ver_primero(lista) == dummy_c);
    print_test("  Ver ultimo devuelve elemento C", *(char*)lista_ver_ultimo(lista) == dummy_c);
    print_test("  Largo es 1", lista_largo(lista) == 1);
    NEWLINE
    print_test("  Borrar primero devuelve elemento C", *(char*)lista_borrar_primero(lista) == dummy_c);
    print_test("  La lista esta vacia", lista_esta_vacia(lista));
    print_test("  Ver primero devuelve NULL", lista_ver_primero(lista) == NULL);
    print_test("  Ver ultimo devuelve NULL", lista_ver_ultimo(lista) == NULL);
    print_test("  Largo es 0", lista_largo(lista) == 0);

    NEWLINE
    lista_destruir(lista,NULL);
    print_test("  Pude destruir la lista", true);
}


void test_iter_i_comportamiento(){
	lista_t* lista = dummy_list();
	int flag;
	
	NEWLINE
	flag = 0;
	printf("  Imprimir todo: ");
	lista_iterar(lista, visitar_1, &flag);
	print_test("\n  Extra es el esperado", flag == CANTIDAD_VALORES);
	
	NEWLINE
	flag = TEST_N_1;
	printf("  Imprimir %d elementos: ", TEST_N_1);
	lista_iterar(lista, visitar_2, &flag);
	print_test("\n  Extra es el esperado", flag == TEST_N_1 - CANTIDAD_VALORES);
	
	NEWLINE
	flag = 0;
	lista_iterar(lista, visitar_3, &flag);
	print_test("  Extra es la sumatoria", flag == SUMATORIA);

	lista_destruir(lista,NULL);
}

void test_iter_e_comportamiento(){

}
//    print_test("  ",);

void pruebas_lista_alumno(void){
	test_lista_comportamiento();
	test_iter_i_comportamiento();
	test_iter_e_comportamiento();
}
