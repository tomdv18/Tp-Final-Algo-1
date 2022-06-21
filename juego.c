#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <string.h>
#include "defendiendo_torres.h"
#include "utiles.h"
#include "animos.h"
#include "comandos.h"
#define MAX_CAMINOS 100
#define MAX_RUTA 50


const int JUGANDO = 0;
const int PERDIDO = -1;
const int GANADO = 1;
const int ORCOS_TOTAL_ESTE = 100;
const int ORCOS_TOTAL_OESTE = 200;
const int ORCOS_TOTAL_NORTE = 300;
const int ORCOS_TOTAL_SUR = 500;
const int RESIST_MIN_TORRES = 50;
const int DEFENSOR_EXTRA_NIVEL_1 = 25;
const int DEFENSOR_EXTRA_OTROS_NIVELES = 50;
const int REINICIAR_TOPE = 0;
const int ENTRADA_1_FILA = 1;
const int ENTRADA_1_COLUMNA = 14;
const int TORRE_1_FILA = 9;
const int TORRE_1_COLUMNA = 0;
const int ENTRADA_2_FILA = 4;
const int ENTRADA_2_COLUMNA = 0;
const int TORRE_2_FILA = 10;
const int TORRE_2_COLUMNA = 14;
const int ENTRADA_1_NIVEL_3_FILA = 0;
const int ENTRADA_1_NIVEL_3_COLUMNA = 2;
const int TORRE_1_NIVEL_3_FILA = 19;
const int TORRE_1_NIVEL_3_COLUMNA = 10;
const int ENTRADA_2_NIVEL_3_FILA = 0;
const int ENTRADA_2_NIVEL_3_COLUMNA = 18;
const int TORRE_2_NIVEL_3_FILA = 19;
const int TORRE_2_NIVEL_3_COLUMNA = 13;
const int ENTRADA_1_NIVEL_4_FILA = 19;
const int ENTRADA_1_NIVEL_4_COLUMNA = 3;
const int TORRE_1_NIVEL_4_FILA = 0;
const int TORRE_1_NIVEL_4_COLUMNA = 5;
const int ENTRADA_2_NIVEL_4_FILA = 19;
const int ENTRADA_2_NIVEL_4_COLUMNA = 17;
const int TORRE_2_NIVEL_4_FILA = 0;
const int TORRE_2_NIVEL_4_COLUMNA = 12;
static const int NIVELES_PRIMEROS = 15;
static const int NIVELES_ULTIMOS = 20;
static const int LVL_ESTE = 1;
static const int LVL_OESTE = 2;
static const int LVL_NORTE = 3;
static const int LVL_SUR = 4;
static const int COORDENADA_MINIMA = 0;
static const int EXITO = 0;
static const int ERROR = -1;
static const char ELFO = 'L';
static const char ENANO =	'G';
static const char AFIRMATIVO =	'S';
static const int PREDETERMINADO = -1;
static const float PREDETERMINADO_FLOAT = -1;
const char IGUAL = '=';
const char INICIAL_LISTAR = 'l';
const char INICIAL_CONFIGURACION = 'c';
const char INICIAL_GRABACION = 'g';
const char PUNTO = '.';
const int PUNTAJE_VICTORIA_PREDETERMINADA = 885;
const int ORCOS_MUERTOS_TOTALES = 1100;
const int MULTIPLICADOR_ORCOS_MUERTOS_TOTALES = 1000;
/*
 *Recibe un juego cargado
 *Reduce el tope al camino que no se usara en el nivel
 */
void sacar_camino_sin_uso(juego_t *juego){
	if (juego->nivel_actual == LVL_ESTE){
		juego->nivel.tope_camino_2 = REINICIAR_TOPE;
	}
	else if (juego->nivel_actual == LVL_OESTE){
		juego->nivel.tope_camino_1 = REINICIAR_TOPE;
	}
}
/*
 *Recibe un nivel cargado pero sin camino
 *Genera un camino para el nivel 1
 */
void generar_camino_nivel_1(nivel_t * nivel){
	coordenada_t entrada_1;
	entrada_1.fil = ENTRADA_1_FILA;
	entrada_1.col = ENTRADA_1_COLUMNA;
	coordenada_t torre_1;
	torre_1.fil = TORRE_1_FILA;
	torre_1.col = TORRE_1_COLUMNA;
	obtener_camino((nivel->camino_1), &(nivel->tope_camino_1) , entrada_1, torre_1);
}

/*
 *Recibe un nivel cargado pero sin camino
 *Genera un camino para el nivel 2
 */
void generar_camino_nivel_2(nivel_t * nivel){
	coordenada_t entrada_2;
	entrada_2.fil = ENTRADA_2_FILA;
	entrada_2.col = ENTRADA_2_COLUMNA;
	coordenada_t torre_2;
	torre_2.fil = TORRE_2_FILA;
	torre_2.col = TORRE_2_COLUMNA;
	obtener_camino((nivel->camino_2), &(nivel->tope_camino_2) , entrada_2, torre_2);
}
/*
 *Recibe un nivel cargado pero sin caminos
 *Generara dos caminos para el nivel 3
 */ 
void generar_camino_nivel_3(nivel_t * nivel){
	coordenada_t entrada_1_nivel_3;
	entrada_1_nivel_3.fil = ENTRADA_1_NIVEL_3_FILA;
	entrada_1_nivel_3.col = ENTRADA_1_NIVEL_3_COLUMNA;
	coordenada_t torre_1_nivel_3;
	torre_1_nivel_3.fil = TORRE_1_NIVEL_3_FILA;
	torre_1_nivel_3.col = TORRE_1_NIVEL_3_COLUMNA;
	obtener_camino((nivel->camino_1), &(nivel->tope_camino_1) , entrada_1_nivel_3, torre_1_nivel_3);
	coordenada_t entrada_2_nivel_3;
	entrada_2_nivel_3.fil = ENTRADA_2_NIVEL_3_FILA;
	entrada_2_nivel_3.col = ENTRADA_2_NIVEL_3_COLUMNA;
	coordenada_t torre_2_nivel_3;
	torre_2_nivel_3.fil = TORRE_2_NIVEL_3_FILA;
	torre_2_nivel_3.col = TORRE_2_NIVEL_3_COLUMNA;
	obtener_camino((nivel->camino_2), &(nivel->tope_camino_2) , entrada_2_nivel_3, torre_2_nivel_3);
}
/*
 *Recibe un nivel cargado pero sin caminos
 *Generara dos caminos para el nivel 4
 */
void generar_camino_nivel_4(nivel_t * nivel){
	coordenada_t entrada_1_nivel_4;
	entrada_1_nivel_4.fil = ENTRADA_1_NIVEL_4_FILA;
	entrada_1_nivel_4.col = ENTRADA_1_NIVEL_4_COLUMNA;
	coordenada_t torre_1_nivel_4;
	torre_1_nivel_4.fil = TORRE_1_NIVEL_4_FILA;
	torre_1_nivel_4.col = TORRE_1_NIVEL_4_COLUMNA;
	obtener_camino((nivel->camino_1), &(nivel->tope_camino_1) , entrada_1_nivel_4, torre_1_nivel_4);
	coordenada_t entrada_2_nivel_4;
	entrada_2_nivel_4.fil = ENTRADA_2_NIVEL_4_FILA;
	entrada_2_nivel_4.col = ENTRADA_2_NIVEL_4_COLUMNA;
	coordenada_t torre_2_nivel_4;
	torre_2_nivel_4.fil = TORRE_2_NIVEL_4_FILA;
	torre_2_nivel_4.col = TORRE_2_NIVEL_4_COLUMNA;
	obtener_camino((nivel->camino_2), &(nivel->tope_camino_2) , entrada_2_nivel_4, torre_2_nivel_4);
}

/*
 *Se mostrara si solo si el jugador gano el juego
 *
 */
void ganador(){
	printf("\n");
	printf("██╗  ██╗ █████╗ ███████╗     ██████╗  █████╗ ███╗   ██╗ █████╗ ██████╗  ██████╗ \n");
	printf("██║  ██║██╔══██╗██╔════╝    ██╔════╝ ██╔══██╗████╗  ██║██╔══██╗██╔══██╗██╔═══██╗\n");
	printf("███████║███████║███████╗    ██║  ███╗███████║██╔██╗ ██║███████║██║  ██║██║   ██║\n");
	printf("██╔══██║██╔══██║╚════██║    ██║   ██║██╔══██║██║╚██╗██║██╔══██║██║  ██║██║   ██║\n");
	printf("██║  ██║██║  ██║███████║    ╚██████╔╝██║  ██║██║ ╚████║██║  ██║██████╔╝╚██████╔╝\n");
	printf("╚═╝  ╚═╝╚═╝  ╚═╝╚══════╝     ╚═════╝ ╚═╝  ╚═╝╚═╝  ╚═══╝╚═╝  ╚═╝╚═════╝  ╚═════╝ \n");
	printf("\n");
}
/*
 *Se mostrara si solo si el jugador perdio el juego
 *
 */
void perdedor(){
	printf("\n");
	printf(" ██████╗  █████╗ ███╗   ███╗███████╗     ██████╗ ██╗   ██╗███████╗██████╗ \n");
	printf("██╔════╝ ██╔══██╗████╗ ████║██╔════╝    ██╔═══██╗██║   ██║██╔════╝██╔══██╗\n");
	printf("██║  ███╗███████║██╔████╔██║█████╗      ██║   ██║██║   ██║█████╗  ██████╔╝\n");
	printf("██║   ██║██╔══██║██║╚██╔╝██║██╔══╝      ██║   ██║╚██╗ ██╔╝██╔══╝  ██╔══██╗\n");
	printf("╚██████╔╝██║  ██║██║ ╚═╝ ██║███████╗    ╚██████╔╝ ╚████╔╝ ███████╗██║  ██║\n");
	printf(" ╚═════╝ ╚═╝  ╚═╝╚═╝     ╚═╝╚══════╝     ╚═════╝   ╚═══╝  ╚══════╝╚═╝  ╚═╝ \n");
	printf("\n");
}
/*
 *
 *Devuelve un entero que corresponde a la columna del defensor a colocar
 */
int pedir_columna_defensor(){	
	int columna = -1;
	printf("\n");
	printf("Inserte la COLUMNA del defensor a colocar, recuerde que debe estar entre 0 y 14 \n");
	printf("si estamos en los primeros niveles y entre 0 y 19 si estamos en el tercero o el cuarto!\n");
	scanf("%i", &columna);
	return columna;
	
}	
/*
 *
 *Devuelve un entero que corresponde a la fila del defensor a colocar 
 */	
int pedir_fila_defensor(){
	int fila = -1;
	printf("\n");
	printf("Inserte la FILA del defensor a colocar, recuerde que debe estar entre 0 y 14 \n");
	printf("si estamos en los primeros niveles y entre 0 y 19 si estamos en el tercero o el cuarto!\n");
	scanf("%i", &fila);
	return fila;
}
/*
 *Recibe la fila y columnas del defensor a colocar
 *Devuelve true si en las coordenadas pasadas es posible agregar un nuevo defensor
 */

bool es_coordenada_valida (coordenada_t * posicion, juego_t * juego){
	int tope_del_nivel = -1;
	bool esta_dentro_limites = false;
	char tipo;
	int indice_exito = ERROR;
	while (!esta_dentro_limites && indice_exito == ERROR){
		posicion->fil = pedir_fila_defensor();
		posicion->col = pedir_columna_defensor();
		printf("De que tipo sera el nuevo defensor? Enano (G) o Elfo (L)) \n");
		scanf(" %c", &tipo);
		while (tipo != ENANO && tipo != ELFO){
			printf("De que tipo sera el nuevo defensor? Recuerda que es o Enano (G) o Elfo (L)) \n");
			scanf(" %c", &tipo);
		}
		indice_exito = agregar_defensor(&((*juego).nivel), (*posicion), tipo);
		if (juego->nivel_actual == LVL_ESTE || juego->nivel_actual == LVL_OESTE ){
			tope_del_nivel = NIVELES_PRIMEROS;
		}
		else {
			tope_del_nivel = NIVELES_ULTIMOS;
		}		
		if (indice_exito == EXITO && (posicion->fil < tope_del_nivel && posicion->fil >= COORDENADA_MINIMA) && (posicion->col < tope_del_nivel && posicion->col >= COORDENADA_MINIMA)){
			esta_dentro_limites = true;
		}
	}
return esta_dentro_limites;
}
/*
 *Recibe si la coordenada ingresada por el usuario es valida
 *Si es valida le avisa al jugador, caso contrario avisa al jugador y vuelve a intentar colocar al defensor
 */
void ingresar_nuevo_defensor(juego_t * juego){
coordenada_t posicion;
	printf("Colocaremos un nuevo defensor!\n");
	bool validado = es_coordenada_valida(&posicion, &(*juego));
		while(!validado){
		printf("Esta coordenada no es valida o esta ocupada!\n");
		es_coordenada_valida(&posicion, &(*juego));
		}
		if (validado){
			printf("Tu defensor esta listo para luchar \n");
		}
}
/*
 *Recibe un juego cargado y el nivel actual
 *Devuelve la cantidad maxima de enemigos que habra en ese nivel
 */
void enemigos_maximos (juego_t * juego){
	juego->nivel.tope_enemigos = REINICIAR_TOPE;
	if (juego->nivel_actual == LVL_ESTE){
		juego->nivel.max_enemigos_nivel = ORCOS_TOTAL_ESTE;	
	}
	else if (juego->nivel_actual == LVL_OESTE){
		juego->nivel.max_enemigos_nivel = ORCOS_TOTAL_OESTE;
	}
	else if (juego->nivel_actual == LVL_NORTE){
		juego->nivel.max_enemigos_nivel = ORCOS_TOTAL_NORTE;
	}
	else if (juego->nivel_actual == LVL_SUR){
		juego->nivel.max_enemigos_nivel = ORCOS_TOTAL_SUR;
	}
}
/*
 *Recibe el ultimo defensor extra agregado por el usuario
 *Reduce la vida de los torres y sus defensores extras
 */
void reducir_estadisticas_torres(juego_t * juego, configuracion_t configuracion){
	if ((*juego).nivel.defensores[(*juego).nivel.tope_defensores -1].tipo == ELFO){
		if (configuracion.elfos_extra.coste_torre_2_elfos_extra == PREDETERMINADO){
		(*juego).torres.resistencia_torre_2 = ((*juego).torres.resistencia_torre_2 - RESIST_MIN_TORRES);	
		}
		if (configuracion.elfos_extra.coste_torre_2_elfos_extra != PREDETERMINADO){
			(*juego).torres.resistencia_torre_2 = ((*juego).torres.resistencia_torre_2 - configuracion.elfos_extra.coste_torre_2_elfos_extra );
		}
		(*juego).torres.elfos_extra--;
	}
	else if ((*juego).nivel.defensores[(*juego).nivel.tope_defensores -1].tipo == ENANO){
		if (configuracion.enanos_extra.coste_torre_1_enanos_extra == PREDETERMINADO){
		(*juego).torres.resistencia_torre_1 = ((*juego).torres.resistencia_torre_1 - RESIST_MIN_TORRES);
		}
		if (configuracion.enanos_extra.coste_torre_1_enanos_extra != PREDETERMINADO){
			(*juego).torres.resistencia_torre_1 = ((*juego).torres.resistencia_torre_1 - configuracion.enanos_extra.coste_torre_1_enanos_extra);
		}
		(*juego).torres.enanos_extra--;
	}
}
/*
 *Recibe un juego cargado por parametro
 *Devuelve si es que se pudo, un defensor extra y les reduce estadisticas a las torres
 */
void pedir_defensor_extra(juego_t * juego, configuracion_t configuracion){
	if (juego->torres.resistencia_torre_1 > RESIST_MIN_TORRES && juego->torres.enanos_extra > 0 && juego->torres.resistencia_torre_2 > RESIST_MIN_TORRES  && juego->torres.elfos_extra > 0){
		mostrar_juego(*juego);
		ingresar_nuevo_defensor(&(*juego));
		reducir_estadisticas_torres(&(*juego), configuracion);
	}
	else{
		printf("No cumples los requisitos para agregar un nuevo defensor!!\n");
	}
}
/*
 *
 *Recibe un caracter del usuario, si este es el indicado llama a a la funcion para agregar un defensor.
 */
void preguntar_por_defensor(juego_t * juego, configuracion_t configuracion){
	char respuesta;
	printf("Quieres agregar a un defensor? Pulsa S para si, cualquier tecla para no.\n");
	scanf(" %c", &respuesta);
		if (respuesta == AFIRMATIVO){
			pedir_defensor_extra(&(*juego), configuracion);
		}
}
/*
 *Recibe un juego y unas configuraciones previamente cargadas.
 *Devuelve la cantidad de defensores a agregar segun el nivel.
 */
int defensores_a_agregar(juego_t juego, configuracion_t configuracion){
int cantidad = 0;	
	if (juego.nivel_actual == LVL_ESTE){
		if (configuracion.enanos_inicio[0] == PREDETERMINADO && configuracion.elfos_inicio[0] == PREDETERMINADO){
			cantidad = 5;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[0] != PREDETERMINADO && configuracion.elfos_inicio[0] == PREDETERMINADO){
			cantidad = configuracion.enanos_inicio[0];
			return cantidad;
		}
		else if (configuracion.enanos_inicio[0] == PREDETERMINADO && configuracion.elfos_inicio[0] != PREDETERMINADO){
			cantidad = 5;
			cantidad = cantidad + configuracion.elfos_inicio[0];
			return cantidad;
		}
		else {
			cantidad = configuracion.enanos_inicio[0];
			cantidad = cantidad + configuracion.elfos_inicio[0];
			return cantidad;
		}
	}
	else if (juego.nivel_actual == LVL_OESTE){
		if (configuracion.enanos_inicio[1] == PREDETERMINADO && configuracion.elfos_inicio[1] == PREDETERMINADO){
			cantidad = 5;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[1] != PREDETERMINADO && configuracion.elfos_inicio[1] == PREDETERMINADO){
			cantidad = configuracion.enanos_inicio[1];
			cantidad = cantidad + 5;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[1] == PREDETERMINADO && configuracion.elfos_inicio[1] != PREDETERMINADO){
			cantidad = configuracion.elfos_inicio[1];
			return cantidad;
		}
		else{
			cantidad = configuracion.enanos_inicio[1];
			cantidad = cantidad + configuracion.elfos_inicio[1];
			return cantidad;
		}
	}
	else if (juego.nivel_actual == LVL_NORTE){
		if (configuracion.enanos_inicio[2] == PREDETERMINADO && configuracion.elfos_inicio[2] == PREDETERMINADO){
			cantidad = 6;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[2] != PREDETERMINADO && configuracion.elfos_inicio[2] == PREDETERMINADO){
			cantidad = configuracion.enanos_inicio[2];
			cantidad = cantidad + 3;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[2] == PREDETERMINADO && configuracion.elfos_inicio[2] != PREDETERMINADO){
			cantidad = configuracion.elfos_inicio[2];
			cantidad = cantidad + 3;
			return cantidad;
		}
		else{
			cantidad = configuracion.enanos_inicio[2];
			cantidad = cantidad + configuracion.elfos_inicio[2];
			return cantidad;
		}
	}
	else{
		if (configuracion.enanos_inicio[3] == PREDETERMINADO && configuracion.elfos_inicio[3] == PREDETERMINADO){
			cantidad = 8;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[3] != PREDETERMINADO && configuracion.elfos_inicio[3] == PREDETERMINADO){
			cantidad = configuracion.enanos_inicio[3];
			cantidad = cantidad + 4;
			return cantidad;
		}
		else if (configuracion.enanos_inicio[3] == PREDETERMINADO && configuracion.elfos_inicio[3] != PREDETERMINADO){
			cantidad = configuracion.elfos_inicio[3];
			cantidad = cantidad + 4;
			return cantidad;
		}
		else {
			cantidad = configuracion.enanos_inicio[3];
			cantidad = cantidad + configuracion.elfos_inicio[3];
			return cantidad;
		}
	}
}

/*
 *recibe un archivo de texto y un entero
 *devuelve 1 si pudo leer un nivel
 */
int leimos_nivel (FILE * mapa,  int * nivel){
	return fscanf(mapa, "NIVEL=%i \n", &*nivel);
}

/*
 *recibe un archivo de texto y un entero
 *devuelve 1 si pudo leer un camino
 */
int leimos_camino (FILE * mapa,  int  * camino){
	return fscanf(mapa, "CAMINO=%i \n", &*camino);
}

/*
 *Recibe un archivo y un vector de coordenadas
 *Carga las coordenadas de cada elemento del vector
 */
void hacer_camino(FILE* mapa, coordenada_t *camino){
	fscanf(mapa, "%i;%i\n", &camino->fil, &camino->col);
}



/*
 *Recibe la ruta del archivo de caminos, un vector de caminos, su tope, el numero del nivel y del camino
 *Carga un camino entero con su tope.
 */
void generar_camino_leido(char ruta_caminos[MAX_RUTA], coordenada_t camino[MAX_CAMINOS], int * tope_camino, int nivel, int camino_recibido){

int nivel_actual;
int camino_actual;
(*tope_camino) = 1;
FILE* mapa = fopen(ruta_caminos, "r");
if (mapa == NULL){
	printf("Surgio un errror al abrir el archivo de caminos!");
}
else {
	int i = 0;
	int nivel_leido = leimos_nivel(mapa, &nivel_actual);
	if (nivel_leido == 1 && nivel_actual == nivel){
		int camino_leido = leimos_camino(mapa, &camino_actual);
		if (camino_leido == 1 && camino_actual == camino_recibido){
			do {
				hacer_camino(mapa, &camino[i]);
				i++;
				(*tope_camino)++;
			}
			while (leimos_nivel(mapa, &nivel_actual) == 0 || leimos_camino(mapa, &camino_actual) == 0  || feof(mapa));
		}
	}
}
fclose(mapa);
}

/*
 *Recibe un juego cargado y una configuracion
 *Carga el camino, los enemigos y defensores para el correspondiente nivel
 */
void inicializar_nivel_1(juego_t * juego, configuracion_t configuracion, bool hay_mapa){

	juego->nivel.tope_defensores = REINICIAR_TOPE;
	if (!hay_mapa){
		generar_camino_nivel_1(&juego->nivel);
	}
	else{
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_1, &juego->nivel.tope_camino_1, 1, 1);
	}
	sacar_camino_sin_uso(&(*juego));
	enemigos_maximos(&(*juego));
	int i = 1;
	int max_defensores = defensores_a_agregar(*juego, configuracion);
	while (i <= max_defensores){
	mostrar_juego(*juego);
	ingresar_nuevo_defensor(&(*juego));
	system("clear");
	i++;
	}
}
/*
 *Recibe un juego cargado  y una configuracion
 *Carga el camino, los enemigos y defensores para el correspondiente nivel
 */
void inicializar_nivel_2(juego_t * juego, configuracion_t configuracion, bool hay_mapa){
	juego->nivel.tope_defensores = REINICIAR_TOPE;
	if (!hay_mapa){
		generar_camino_nivel_2(&juego->nivel);
	}
	else{
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_2, &juego->nivel.tope_camino_2, 2, 2);
	} 
	sacar_camino_sin_uso(&(*juego));
	enemigos_maximos(&(*juego));
	printf("==================================\n");
	printf("=NIVEL DOS, INVASION POR EL OESTE=\n");
	printf("==================================\n");
	detener_el_tiempo(2);
	int i = 1;
	int max_defensores = defensores_a_agregar(*juego, configuracion);

	while (i <= max_defensores){	
		mostrar_juego(*juego);
		ingresar_nuevo_defensor(&(*juego));
		system("clear");
		i++;
	}
}
/*
 *Recibe un juego cargado y una configuracion
 *Carga los caminos, los enemigos y defensores para el correspondiente nivel
 */
void inicializar_nivel_3(juego_t * juego, configuracion_t configuracion, bool hay_mapa){
	juego->nivel.tope_defensores = REINICIAR_TOPE;
	if (!hay_mapa){
		generar_camino_nivel_3(&juego->nivel);
	}
	else{
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_1, &juego->nivel.tope_camino_1, 3, 1);
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_2, &juego->nivel.tope_camino_2, 3, 2);
	}
	enemigos_maximos(&(*juego));
	printf("==================================\n");
	printf("=NIVEL TRES, INVASION POR EL NORTE=\n");
	printf("==================================\n");
	detener_el_tiempo(2);
	int i = 1;
	int max_defensores = defensores_a_agregar(*juego, configuracion);
	while (i <= max_defensores){
	mostrar_juego(*juego);
	ingresar_nuevo_defensor(&(*juego));
	system("clear");
	i++;
	}
}

/*
 *Recibe un juego cargado y una configuracion
 *Carga los caminos, los enemigos y defensores para el correspondiente nivel
 */
void inicializar_nivel_4(juego_t * juego, configuracion_t configuracion, bool hay_mapa){
	juego->nivel.tope_defensores = REINICIAR_TOPE;
	if (!hay_mapa){
		generar_camino_nivel_4(&juego->nivel);
	}
	else{
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_1, &juego->nivel.tope_camino_1, 4, 1);
		generar_camino_leido(configuracion.ruta_caminos, juego->nivel.camino_2, &juego->nivel.tope_camino_2, 4, 2);
	}
	enemigos_maximos(&(*juego));
	printf("===================================\n");
	printf("=NIVEL ULTIMO, INVASION POR EL SUR=\n");
	printf("===================================\n");
	detener_el_tiempo(2);
	int i = 1;
	int max_defensores = defensores_a_agregar(*juego, configuracion);
	mostrar_juego(*juego);
	while (i <= max_defensores){
	mostrar_juego(*juego);
	ingresar_nuevo_defensor(&(*juego));
	system("clear");
	i++;
	}
}
/*
 *Recibe un valor del tipo float
 *Devuelve el valor de la velocidad que corresponda segun ese float recibido
 */
float determinar_velocidad_juego(float velocidad_juego){
if (velocidad_juego == PREDETERMINADO){		
	return 1;
}
else 
	return velocidad_juego;
}


/*
 *Recibe un juego y un float
 *Juega un turno individual
 */

void jugar_un_turno_nivel (juego_t * juego, float velocidad_juego){
	jugar_turno(&*juego);
	mostrar_juego(*juego);
	detener_el_tiempo(velocidad_juego);
	system("clear");
	
}
/*
 *Recibe dos cadenas, el largo de una y un entero
 *
 */
void copia_cadena(char destino[MAX_RUTA], char origen[MAX_RUTA], size_t largo, int recorredor){
	int j = 0;
	while(recorredor < largo){
		destino[j] = origen[recorredor];
		j++;
		recorredor++;
	}
	destino[j] = '\0';
}

/*
 *Recibe dos cadenas, y una letra que sera la que separe
 *Modifica una cadena, con todo lo que tenia la otra, despues de la letra separadora
 */
void desarmar_cadena(char destino[MAX_RUTA], char origen[MAX_RUTA], char letra_corte){
	int i = 0;
	size_t largo = strlen(origen);
	bool desarmada = false;
	while(i < largo && desarmada == false){
		if (origen[i] == letra_corte){
			copia_cadena(destino, origen, largo, i +1);
			desarmada = true;
		}
		i++;
	}
}
/*
 *Recibe dos cadenas, y una letra que sera la que separe
 *Modifica una cadena, con todo lo que tenia la otra, antes de la letra separadora
 */
void desarmar_cadena_sacando_final(char destino[MAX_RUTA], char origen[MAX_RUTA], char letra_corte){
	int i =0;
	size_t largo = strlen(origen);
	while(i < largo && origen[i] != letra_corte){
		destino[i] = origen[i];
		i++;
	}
	destino[i] = '\0';
}


/*
 *Recibe un archivo y una configuracion
 *Aplica los valores correspondientes en la configuracion
 */
void leer_config(FILE * config, configuracion_t * configuracion){

	fscanf(config, "RESISTENCIA_TORRES= %i , %i \n", &configuracion->resistencia_torres.resistencia_torre_1, &configuracion->resistencia_torres.resistencia_torre_1);
	fscanf(config, "ENANOS_INICIO= %i , %i, %i, %i \n", &configuracion->enanos_inicio[0], &configuracion->enanos_inicio[1],&configuracion->enanos_inicio[2],&configuracion->enanos_inicio[3]);
	fscanf(config, "ELFOS_INICIO= %i , %i, %i, %i \n", &configuracion->elfos_inicio[0], &configuracion->elfos_inicio[1],&configuracion->elfos_inicio[2],&configuracion->elfos_inicio[3]);
	fscanf(config, "ENANOS_EXTRA= %i, %i \n", &configuracion->enanos_extra.cantidad_enanos_extra, &configuracion->enanos_extra.coste_torre_1_enanos_extra);
	fscanf(config, "ELFOS_EXTRA= %i, %i \n", &configuracion->elfos_extra.cantidad_elfos_extra,  &configuracion->elfos_extra.coste_torre_2_elfos_extra);
	fscanf(config, "ENANOS_ANIMO= %i, %i \n", &configuracion->animos_enanos.critico_enanos, &configuracion->animos_enanos.fallo_enanos);
	fscanf(config, "ELFOS_ANIMO= %i, %i \n",&configuracion->animos_elfos.critico_elfos, &configuracion->animos_elfos.fallo_elfos);
	fscanf(config, "VELOCIDAD= %f \n", &configuracion->velocidad_juego);
	fscanf(config, "%[^;]; \n", configuracion->ruta_caminos);
}

/*
 *
 *Devuelve una configuracion inicializada con todos sus valores en -1
 */
void inicializar_configuracion(configuracion_t * configuracion){
	configuracion->resistencia_torres.resistencia_torre_1 = PREDETERMINADO;
	configuracion->resistencia_torres.resistencia_torre_2 = PREDETERMINADO;
	configuracion->enanos_inicio[0] = PREDETERMINADO;
	configuracion->enanos_inicio[1] = PREDETERMINADO;
	configuracion->enanos_inicio[2] = PREDETERMINADO;
	configuracion->enanos_inicio[3] = PREDETERMINADO;
	configuracion->elfos_inicio[0] = PREDETERMINADO;
	configuracion->elfos_inicio[1] = PREDETERMINADO;
	configuracion->elfos_inicio[2] = PREDETERMINADO;
	configuracion->elfos_inicio[3] = PREDETERMINADO;
	configuracion->enanos_extra.cantidad_enanos_extra = PREDETERMINADO;
	configuracion->enanos_extra.coste_torre_1_enanos_extra = PREDETERMINADO;
	configuracion->elfos_extra.cantidad_elfos_extra = PREDETERMINADO;
	configuracion->elfos_extra.coste_torre_2_elfos_extra = PREDETERMINADO;
	configuracion->animos_enanos.critico_enanos = PREDETERMINADO;
	configuracion->animos_enanos.fallo_enanos = PREDETERMINADO;
	configuracion->animos_elfos.critico_elfos = PREDETERMINADO;
	configuracion->animos_elfos.fallo_elfos = PREDETERMINADO;
	configuracion->velocidad_juego = PREDETERMINADO_FLOAT;
	strcpy(configuracion->ruta_caminos, "-1");
}

/*
 * Recibe una configuracion inicializada
 * Devuelve un entero segun los valores de la configuracion
 */
int calcular_puntaje(configuracion_t configuracion){
	int numero = configuracion.resistencia_torres.resistencia_torre_1;
	numero = numero + configuracion.resistencia_torres.resistencia_torre_2;
	numero = numero + configuracion.enanos_inicio[0];
	numero = numero + configuracion.enanos_inicio[1];
	numero = numero + configuracion.enanos_inicio[2];
	numero = numero + configuracion.enanos_inicio[3];	
	numero = numero + configuracion.elfos_inicio[0];
	numero = numero + configuracion.elfos_inicio[1];
	numero = numero + configuracion.elfos_inicio[2];
	numero = numero + configuracion.elfos_inicio[3];
	numero = numero + configuracion.enanos_extra.cantidad_enanos_extra;
	numero = numero + configuracion.elfos_extra.cantidad_elfos_extra;
	numero = (MULTIPLICADOR_ORCOS_MUERTOS_TOTALES * ORCOS_MUERTOS_TOTALES) / numero;
return numero;	
}

/*
 * Recibe un string de caracteres
 * Devuelve a ese string rodeado de  palabras (ranking_string.csv)
 */
void fusion_de_nombres(char configuracion[MAX_RUTA]){
char nuevo_nombre[MAX_NOMBRE];
	
	if (strcmp (configuracion, "predeterminado") == 0){
		strcpy(configuracion, "ranking.csv");
	}
	else{
		strcpy(nuevo_nombre, "ranking_");
		strcat(nuevo_nombre, configuracion);
		strcat(nuevo_nombre, ".csv");
		strcpy(configuracion, nuevo_nombre);
	}
}

/*
 * Recibe un vector de individuos del ranking y su tope
 * Ordena a los personajes segun su puntaje
 */
void ordenar(rankista_t rankista[MAX_NOMBRE], int tope){
		rankista_t rankista_aux;
		int j;
		for (int i = 1; i < tope; i++){
			j=i;
			rankista_aux = rankista[i];
			while(j > 0 && rankista_aux.puntaje_final < rankista[j-1].puntaje_final){
				rankista[j] = rankista[j-1];
				j--;
			}
			rankista[j] = rankista_aux;
		}
}
/*
 * Recibe a un individuo del ranking y la ruta del archivo de ranking
 * Lo inserta en este archivo, de forma ordenada
 */
void insertar_en_ranking(rankista_t rankista, char ruta_ranking[MAX_RUTA]){
	FILE* ranking = fopen(ruta_ranking,"r");
	if (ranking == NULL){
		FILE* ranking_iniciado = fopen(ruta_ranking,"w");
		fprintf(ranking_iniciado, "%s;%i \n",rankista.nombre, rankista.puntaje_final);
		fclose(ranking_iniciado);
		fclose(ranking);
	}
	else{
		rankista_t todos_los_rankistas[MAX_NOMBRE];
		int i = 0;
		int tope_rankistas = 1;
		while(!feof(ranking)){
			fscanf(ranking, "%[^;];%i \n", todos_los_rankistas[i].nombre, &todos_los_rankistas[i].puntaje_final);
			i++;
			tope_rankistas++;
		}
		ordenar(todos_los_rankistas, tope_rankistas);
		FILE* nuevo_ranking = fopen("nuevo_ranking.csv", "w");
		int j = 0;
		while (j < tope_rankistas){
			fprintf(nuevo_ranking, "%s;%i \n",todos_los_rankistas[j].nombre, todos_los_rankistas[j].puntaje_final);
			j++;
		}
		fclose(ranking);
		fclose(nuevo_ranking);
		remove(ruta_ranking);
		rename("nuevo_ranking.csv", ruta_ranking);
	}
}

/*
 * Recibe un puntaje numerico y la configuracion
 * Inserta en el ranking segun su configuracion
 */
void poner_en_ranking(int puntaje_final, char configruta[MAX_RUTA]){
	char nuevo_nombre[MAX_NOMBRE];
	char configuracion[MAX_NOMBRE];
    printf("Tu puntaje es de %i puntos! \n", puntaje_final);
    printf("Por favor, ingresa el nombre que quieras asociar a este puntaje \n");
    scanf("%s", nuevo_nombre);
	rankista_t rankista;
	rankista.puntaje_final = puntaje_final;
	strcpy(rankista.nombre, nuevo_nombre);
	desarmar_cadena_sacando_final(configuracion, configruta, PUNTO);
	fusion_de_nombres(configuracion);
	insertar_en_ranking(rankista, configuracion);
}
/*
 *Recibe la ruta de la configuracion y la ruta del archivo de grabacion
 *Ejecuta todo el juego
 */
void the_game(char ruta_archivo_configuracion[MAX_RUTA], char archivo_grabacion[MAX_RUTA]){

int viento;
int humedad;
char animo_legolas;
char animo_gimli; 
juego_t juego;
int contador = 0;
bool se_quiere_grabar = true;
bool hay_configuracion_personalizada = false;
bool hay_mapa = false;
configuracion_t configuracion;

inicializar_configuracion (&configuracion);

if (strcmp(ruta_archivo_configuracion, "NO") != 0){
	FILE* config = fopen (ruta_archivo_configuracion, "r");
	if (config == NULL){
		printf("ERROR AL ABRIR EL ARCHIVO, USANDO CONFIG PREDETERMINADA!\n");
	}
	else{
	leer_config(config, &configuracion);
	hay_configuracion_personalizada = true;
	}
	fclose(config);	
}
if (strcmp (archivo_grabacion, "NO") == 0){
	se_quiere_grabar = false;
}
FILE* guardar = fopen(archivo_grabacion, "w");

if (hay_configuracion_personalizada){
	if (strcmp (configuracion.ruta_caminos, "-1") != 0){
		FILE* caminos = fopen (configuracion.ruta_caminos, "r");
		if (caminos == NULL){
			printf("Caminos no encontrados. Usando los predeterminados...\n");
		}
		else {
			hay_mapa = true;
		}			
			fclose(caminos);
	}	
}
	
//--------------------------------Ejecucion del juego ----------------------------------------------//
	srand((unsigned)time(NULL));
	animos(&viento, &humedad, &animo_legolas, &animo_gimli);
	inicializar_juego(&juego, viento, humedad, animo_legolas, animo_gimli, configuracion);
	inicializar_nivel_1(&juego, configuracion, hay_mapa);
	mostrar_juego(juego);
	jugar_turno(&juego);
	contador = 1;
	float velocidad = determinar_velocidad_juego(configuracion.velocidad_juego);
	while(estado_juego(juego) == JUGANDO){
		while(estado_nivel(juego.nivel) == JUGANDO && estado_juego(juego) == JUGANDO){
			jugar_un_turno_nivel(&juego, velocidad);
			contador++;
		if (se_quiere_grabar == true){
			fwrite(&juego, sizeof(juego_t), 1, guardar);
		}
		if ((contador % DEFENSOR_EXTRA_NIVEL_1 == 0) && (juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)){
			preguntar_por_defensor(&juego, configuracion);
			detener_el_tiempo(1);
			system("clear");
			}
		}
		if (estado_nivel(juego.nivel) == GANADO && estado_juego(juego) == JUGANDO){
			printf("Has superado este nivel!!\n");
			juego.nivel_actual++;
			inicializar_nivel_2 (&juego, configuracion, hay_mapa);
			mostrar_juego(juego);
			jugar_turno(&juego);
			contador = 1;
			while(estado_nivel(juego.nivel) == JUGANDO && estado_juego(juego) == JUGANDO){	
				jugar_un_turno_nivel(&juego, velocidad);
				contador++;
				if (se_quiere_grabar == true){
					fwrite(&juego, sizeof(juego_t),1, guardar);
				}
				if ((contador % DEFENSOR_EXTRA_OTROS_NIVELES == 0) && (juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)){
					preguntar_por_defensor(&juego, configuracion);
					detener_el_tiempo(1);
					system("clear");
				}
			}
		}	
		if (estado_nivel(juego.nivel) == GANADO && estado_juego(juego) == JUGANDO){
			printf("Has superado el segundo nivel!!\n");
			detener_el_tiempo(2);
			juego.nivel_actual++;
			inicializar_nivel_3(&juego, configuracion, hay_mapa);
			mostrar_juego(juego);
			contador = 1;
			jugar_turno(&juego);
			while(estado_nivel(juego.nivel) == JUGANDO && estado_juego(juego) == JUGANDO){	
				jugar_un_turno_nivel(&juego, velocidad);
				contador ++;
				if (se_quiere_grabar == true){
					fwrite(&juego, sizeof(juego_t), 1, guardar);
				}
				if ((contador % DEFENSOR_EXTRA_OTROS_NIVELES == 0) && (juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)){
					preguntar_por_defensor(&juego, configuracion);
					detener_el_tiempo(1);
					system("clear");
				}
			}		
		}	
		if (estado_nivel(juego.nivel) == 1 && estado_juego(juego) == JUGANDO){
			printf("Has superado el tercer nivel!!\n");
			detener_el_tiempo(2);
			juego.nivel_actual++;
			inicializar_nivel_4(&juego, configuracion, hay_mapa);
			mostrar_juego(juego);
			contador = 1;
			jugar_turno(&juego);
			while(estado_nivel(juego.nivel) == JUGANDO && estado_juego(juego) == JUGANDO){	
				jugar_un_turno_nivel(&juego, velocidad);
				contador ++;
				if (se_quiere_grabar == true){
					fwrite(&juego, sizeof(juego_t), 1, guardar);
				}
				if ((contador % DEFENSOR_EXTRA_OTROS_NIVELES == 0) && (juego.nivel.tope_enemigos < juego.nivel.max_enemigos_nivel)){
					preguntar_por_defensor(&juego, configuracion);
					detener_el_tiempo(1);
					system("clear");
				}
			}
		}
	}
	if (estado_juego(juego) == GANADO){
		ganador();
		printf("\n");
		if (hay_configuracion_personalizada){
			int puntaje = calcular_puntaje(configuracion);
			poner_en_ranking(puntaje,ruta_archivo_configuracion);
		}
		else{
			poner_en_ranking(PUNTAJE_VICTORIA_PREDETERMINADA,"predeterminado");
		}
	}
	if (estado_juego(juego) == PERDIDO){
		perdedor();
	}

	fclose(guardar);
		
}

/*
 *Recibe un vector de caracteres
 *Luego de desarmar el vector recibido, ejecuta la repeticion de una partida en velocidad predeterminada
 */
void repeticion_sin_velocidad(char argv[]){
	char archivo_grabacion[MAX_RUTA];
	desarmar_cadena(archivo_grabacion, argv, IGUAL);
	poneme_la_repe(archivo_grabacion, 1);	
}
/*
 *Recibe dos vectores de caractereres
 *Reproduce una repeticion con velocidad personalizada
 */
void poner_repeticion(char argv[], char argv2[]){
	char archivo_grabacion[MAX_RUTA];
	char velocidad_de_repe[MAX_RUTA];
	desarmar_cadena(archivo_grabacion, argv, IGUAL);
	desarmar_cadena(velocidad_de_repe, argv2, IGUAL);
	float velocidad = (float) atof(velocidad_de_repe);
	poneme_la_repe(archivo_grabacion, velocidad);
}
/*
 *Recibe dos vectores de caracteres
 *Muestra un ranking segun la cantidad y el tipo de configuracion que ingresa el usuario
 */
void mostrar_ranking_personalizado(char argv[], char argv2[]){
	char cantidad[MAX_RUTA];
	char configuracion[MAX_RUTA];
	char configuracion2[MAX_RUTA];
	desarmar_cadena(cantidad, argv, IGUAL);
	int cantida = (int) atoi(cantidad);
	desarmar_cadena(configuracion, argv2, IGUAL);
	desarmar_cadena_sacando_final(configuracion2, configuracion, PUNTO);
	mostrar_ranking(cantida, configuracion2);
}

/*
 *Recibe un vector de caracteres
 *Muestra todo un ranking que el usuario elija
 */
void mostrar_ranking_sin_limite(char argv[]){
	char configuracion[MAX_RUTA];
	char configuracion2[MAX_RUTA];
	desarmar_cadena(configuracion, argv, IGUAL);
	desarmar_cadena_sacando_final(configuracion2, configuracion, PUNTO);
	mostrar_ranking(-1, configuracion2);
}

/*
 *Recibe un vector de caracteres
 *Muestra el ranking predeterminado, la cantidad de posiciones que el usuario elija
 */
void mostrar_ranking_default(char argv[]){
	char cantidad[MAX_RUTA];
	desarmar_cadena(cantidad, argv, IGUAL);
	int cantida = (int) atoi(cantidad);
	mostrar_ranking(cantida, "predeterminado");
}
/*
 *Recibe dos vectores de caracteres
 *Juega con un archivo de configuracion y de grabacion elegidos por el usuario
 */
void jugar(char argv[], char argv2[]){
	char archivo_grabacion[MAX_RUTA];
	char archivo_configuracion[MAX_RUTA];
	desarmar_cadena(archivo_configuracion, argv, IGUAL);
	desarmar_cadena(archivo_grabacion, argv2, IGUAL);
	the_game(archivo_configuracion, archivo_grabacion);
}
/*
 *Recibe un vector de caracteres
 *Juega con una configuracion determinada
 */
void jugar_sin_grabar(char argv[]){
	char archivo_grabacion[MAX_RUTA];
	char archivo_configuracion[MAX_RUTA];
	desarmar_cadena(archivo_configuracion, argv, IGUAL);
	strcpy(archivo_grabacion, "NO");
	the_game(archivo_configuracion, archivo_grabacion);
}
/*
 *Recibe un vector de caracteres
 *Juega con la configuracion default, pero grabando la partida
 */
void jugar_sin_configuracion(char argv[]){
	char archivo_grabacion[MAX_RUTA];
	char archivo_configuracion[MAX_RUTA];
	desarmar_cadena(archivo_grabacion, argv, IGUAL);
	strcpy(archivo_configuracion, "NO");
	the_game(archivo_configuracion, archivo_grabacion);
}

int main(int argc, char *argv[]){


if (strcmp (argv[1], "crear_configuracion") == 0  ){
	if (argc == 3){
		crear_configuracion(argv[2]);
	}
}
if (strcmp (argv[1], "crear_camino") == 0 ){
	if (argc == 3){
		crear_camino(argv[2]);
	}
}
if (strcmp (argv[1], "poneme_la_repe") == 0  ){
	if (argc == 3){
		repeticion_sin_velocidad(argv[2]);
	}
	else if (argc == 4){
		poner_repeticion(argv[2], argv[3]);
	}
}
if (strcmp (argv[1], "ranking") == 0 ){
	if (argc == 4){
		mostrar_ranking_personalizado(argv[2], argv[3]);
	}
	if (argc == 3){
		if (argv[2][0] == INICIAL_LISTAR){
			mostrar_ranking_default(argv[2]);
		}
		if (argv[2][0] == INICIAL_CONFIGURACION){
			mostrar_ranking_sin_limite(argv[2]);
		}
	}
}
if (strcmp (argv[1], "jugar") == 0 ){
	if (argc == 4){
		jugar(argv[2], argv[3]);
	}
	if (argc == 3){
		if (argv[2][0] == INICIAL_CONFIGURACION){
			jugar_sin_grabar(argv[2]);
		}
		if (argv[2][0] == INICIAL_GRABACION){
			jugar_sin_configuracion(argv[2]);
		}
	}
}
else 
	printf("Error en la cantidad o el tipo de los argumentos!\n");

return 0;
}


