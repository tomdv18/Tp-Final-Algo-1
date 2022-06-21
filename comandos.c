#include <stdio.h>
#include "comandos.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "utiles.h"

#define MAX_LONGITUD_CAMINO 200
#define MAX_TERRENO 20

#define MAX_RANKINGS 100

const char ARRIBA = 'W';
const char ABAJO = 'S';
const char IZQUIERDA = 'A';
const char DERECHA = 'D';
const char FINALIZAR = 'F';
static const char TERRENO = '~';
static const char CAMINO = '#';
const int POSICION_INVALIDA = 0;
static const int ENTRADA_1_FILA = 1;
static const int ENTRADA_1_COLUMNA = 14;
static const int ENTRADA_2_FILA = 4;
static const int ENTRADA_2_COLUMNA = 0;
static const int ENTRADA_1_NIVEL_3_FILA = 0;
static const int ENTRADA_1_NIVEL_3_COLUMNA = 2;
static const int ENTRADA_2_NIVEL_3_FILA = 0;
static const int ENTRADA_2_NIVEL_3_COLUMNA = 18;
static const int ENTRADA_1_NIVEL_4_FILA = 19;
static const int ENTRADA_1_NIVEL_4_COLUMNA = 3;
static const int ENTRADA_2_NIVEL_4_FILA = 19;
static const int ENTRADA_2_NIVEL_4_COLUMNA = 17;
static const int PREDETERMINADO = -1;
static const float PREDETERMINADO_FLOAT = -1;
static const int NO_CRITICO = 0;
const int PROBABILIDAD_CRITICO_MEDIA= 10;
const int MAXIMA_PROBABILIDAD_CRITICO = 25;
const int PROBABILIDAD_FALLO_MINIMA = 12;
const int PROBABILIDAD_FALLO_MEDIA = 25;
const int MAXIMA_PROBABILIDAD_FALLO = 37;
const int MINIMA_VELOCIDAD = 0;
const int MAXIMA_VELOCIDAD = 5;
static int CANTIDAD_TOTAL_NIVELES = 4;

/*
 *
 *Devuelve un valor numerico cualquiera
 */
int pedir_valores(){
    int numero;
    printf("Por favor ingresa tu valor, recuerda que si ingresas -1, sera el valor por defecto\n");
    scanf("%i", &numero);
    printf("\n");
return numero;
}
/*
 *Recibe un valor numerico 
 *Solo devuelve true si recibio un valor que sea igual a -1 o mayor a cero
 */
bool es_valor_correcto(int numero){
    if (numero > 0 || numero == PREDETERMINADO){
        return true;
    }   
    return false;
}

/*
 *Recibe un valor numerico 
 *Solo devuelve un valor que sea igual a -1 o mayor a cero
 */
int pedir_valores_mayores_a_cero(){
    int valor_recibido = pedir_valores();
    while(!es_valor_correcto(valor_recibido)){    
        printf("Ese valor no es valido. Por favor ingresa un numero mayor a cero\n");
        valor_recibido = pedir_valores_mayores_a_cero();
    }
    return valor_recibido;
}

/*
 *Recibe un valor numerico que sea igual a -1 o mayor a cero y ambas torres
 *Devuelve las torres con sus vidas inicializadas
 */
void establecer_valores_vida_torres(resistencia_torres_t * resistencia_torres){
    printf("A continuacion, estableceremos el valor de la vida de la primer torre\n");
    resistencia_torres->resistencia_torre_1 = pedir_valores_mayores_a_cero();
    printf("A continuacion, estableceremos el valor de la vida de la segunda torre\n");
    resistencia_torres->resistencia_torre_2 = pedir_valores_mayores_a_cero();
}

/*
 *Recibe un valor numerico que sea igual a -1 o mayor a cero y a un vector que representa los enanos por nivel
 *Devuelve los enanos inicializados por nivel
 */
void pedir_enanos_iniciales(int enanos_inicio[MAX_NIVELES]){

    for (int i = 0; i <= CANTIDAD_TOTAL_NIVELES -1; i++){
        printf("Con cuantos enanos iniciales quieres contar en el nivel %i? \n", i+1);
        enanos_inicio[i] = pedir_valores_mayores_a_cero();
    }
}

/*
 *Recibe un valor numerico que sea igual a -1 o mayor a cero y a un vector que representa los elfos por nivel
 *Devuelve los elfos inicializados por nivel
 */
void pedir_elfos_iniciales(int elfos_inicio[MAX_NIVELES]){
    
     for (int i = 0; i <= CANTIDAD_TOTAL_NIVELES -1; i++){
        printf("Con cuantos elfos iniciales quieres contar en el nivel %i? \n", i+1);
        elfos_inicio[i] = pedir_valores_mayores_a_cero();
    }
}

/*
 *recibe un numero
 *Si el numero es menor que -1; lo vuelve a pedir, de lo contrario, devuelve ese numero
 */ 
int pedir_defensores_extra(){
    int numero = pedir_valores();
    while(numero < PREDETERMINADO){
        printf("Ese valor no es valido!\n");
        numero = pedir_defensores_extra();
    }
    return numero;
}
/*
 *
 *Devuelve un numero que corresponde a lo que le costara a la torre invocar un defensor
 */ 
int pedir_danio_torres_defensor_extra (){
    return pedir_defensores_extra();
}

/*
 * Recibe un struct que representa las estadisticas de los enanos extra
 * Incializa la cantidad de enanos extra y el coste que le hara a la torre invocar uno de estos
 */ 
void definir_enanos_extra(enanos_extra_t * enanos_extra){
    printf("Con cuantos enanos extra quieres iniciar?\n");
    enanos_extra->cantidad_enanos_extra = pedir_defensores_extra();
    printf("Cuanto daño le hara invocar un enano a la torre 1?\n");
    enanos_extra->coste_torre_1_enanos_extra = pedir_danio_torres_defensor_extra();
}

 /*
 * Recibe un struct que representa las estadisticas de los elfos extra
 * Incializa la cantidad de elfos extra y el coste que le hara a la torre invocar uno de est
 */ 
void definir_elfos_extra(elfos_extra_t * elfos_extra){
    printf("Con cuantos elfos extra quieres iniciar?\n");
    elfos_extra->cantidad_elfos_extra = pedir_defensores_extra();
    printf("Cuanto daño le hara invocar un enano a la torre 2?\n");
    elfos_extra->coste_torre_2_elfos_extra = pedir_danio_torres_defensor_extra();
}

 /*
 * Recibe un valor numerico
 * Devuelve true si el numero es 0, 10, 25 o -1
 */ 
bool es_valido_critico(int numero){
    if (numero == PREDETERMINADO || numero == PROBABILIDAD_CRITICO_MEDIA ||  numero == MAXIMA_PROBABILIDAD_CRITICO ||  numero == NO_CRITICO){
        return true;
    }
return false;
}

 /*
 * Recibe un valor numerico
 * Devuelve un valor que sea 0, 10, 25 o -1
 */ 
int validar_porcentaje_critico(){
    int numero = pedir_valores ();
    while(!es_valido_critico(numero)){
        printf("Ese numero no es valido! Recuerda que puede ser 0, 10 o 25!");
        numero = validar_porcentaje_critico();
    }
    return numero;
}
 /*
 * Recibe un valor numerico
 * Devuelve true si el numero es 12, 37, 25 o -1
 */ 
bool es_valido_fallo(int numero){
    if (numero == PREDETERMINADO || numero == PROBABILIDAD_FALLO_MEDIA ||  numero == PROBABILIDAD_FALLO_MINIMA ||  numero == MAXIMA_PROBABILIDAD_FALLO){
        return true;
    }
return false;
}

 /*
 * Recibe un valor numerico
 * Devuelve un valor que sea 12, 37, 25 o -1
 */ 
int validar_porcentaje_fallo(){
    int numero = pedir_valores ();
    while (!es_valido_fallo(numero)){   
        printf("Ese numero no es valido! Recuerda que puede ser 12, 25 o 37!");
        numero = validar_porcentaje_fallo();
    }
    return numero;
}
 
 /*
 * Recibe dos valores numericos 
 * Inicializa el porcentaje de critico y de fallos de los enanos
 */ 
void definir_animos_enanos(animos_enanos_t * animos_enanos){
    printf("Cual sera la probabilidad de critico de los enanos?\n"); 
    printf("Recuerda que solo puede ser 0, 10, 25!\n");
    animos_enanos->critico_enanos = validar_porcentaje_critico();
    printf("Cual quieres que sea la probabilidad de fallo de los enanos?\n");
    printf("Recuerda que puede ser 12, 25 o 37!\n");
    animos_enanos->fallo_enanos = validar_porcentaje_fallo();
}

 /*
 * Recibe dos valores numericos 
 * Inicializa el porcentaje de critico y de fallos de los elfos
 */ 
void definir_animos_elfos(animos_elfos_t * animos_elfos){
    printf("Cual sera la probabilidad de critico de los elfos?\n"); 
    printf("Recuerda que solo puede ser 0, 10, 25!\n");
    animos_elfos->critico_elfos = validar_porcentaje_critico();
    printf("Cual quieres que sea la probabilidad de fallo de los elfos?\n");
    printf("Recuerda que puede ser 12, 25 o 37!\n");
    animos_elfos->fallo_elfos = validar_porcentaje_fallo();
}


/*
 *
 * Devuelve un float 
 */ 
float pedir_valor_float(){
    float numero;
    printf("Por favor ingresa tu valor, recuerda que si ingresas -1, sera el valor por defecto\n");
    scanf("%f", &numero);
    printf("\n");
return numero;
}
/*
 * Recibe un float
 * Devuelve true si es mayor que cero y menor que cinco o simplemente -1
 */ 
bool es_velocidad_valida(float numero){
    if((numero > MINIMA_VELOCIDAD && numero < MAXIMA_VELOCIDAD) || numero == PREDETERMINADO_FLOAT){
        return true;
    }    
return false;
}

/*
 * Recibe un float
 * Devuelve un valor numerico mayor que cero y menor que cinco o simplemente -1
 */ 
float valida_velocidad (){
    float numero = pedir_valor_float();
    while(!es_velocidad_valida(numero)){
        printf("Numero no valido!\n");
        numero = valida_velocidad();
    }
    return numero;
}

/*
 * Recibe un valor numerico mayor que cero y menor que cinco o simplemente -1
 * Le asigna un float a la velocidad del juego
 */ 
void velocidad_del_juego(float * velocidad_juego){
    printf("A que velocidad quieres que corra el juego?\n");
    *(velocidad_juego) = valida_velocidad();

}

/*
 * Recibe una ruta de donde buscara los caminos sin inicializar
 * Inicializa esa misma ruta, pudiendo ser o bien un string de caracteres o bien un -1
 */ 
void pedir_ruta_caminos(char ruta_caminos[MAX_RUTA]){
    char ruta_ingresada[MAX_RUTA];
    printf("En que ruta buscaremos los caminos? Si quieres que sean predeterminados, usa -1 \n");
    printf("Recuerda agregarle la extencion .txt \n");
    scanf("%s", ruta_ingresada);
    strcpy(ruta_caminos, ruta_ingresada);
}

/*
 * Recibe una ruta de donde creara la configuracion
 * Devuelve un archivo de configuracion totalmente cargado
 */ 
void crear_configuracion (char ruta_configuracion[MAX_RUTA]){
configuracion_t configuracion;
    establecer_valores_vida_torres(&configuracion.resistencia_torres);
    system("clear");
    pedir_enanos_iniciales(configuracion.enanos_inicio);
    system("clear");
    pedir_elfos_iniciales(configuracion.elfos_inicio);
    system("clear");
    definir_enanos_extra(&configuracion.enanos_extra);
    system("clear");
    definir_elfos_extra(&configuracion.elfos_extra);
    system("clear");
    definir_animos_enanos(&configuracion.animos_enanos);
    system("clear");
    definir_animos_elfos(&configuracion.animos_elfos);
    system("clear");
    velocidad_del_juego(&configuracion.velocidad_juego);
    system("clear");
    pedir_ruta_caminos(configuracion.ruta_caminos);
    FILE* configuraciones = fopen (ruta_configuracion, "w");
    fprintf(configuraciones, "RESISTENCIA_TORRES= %i , %i \n", configuracion.resistencia_torres.resistencia_torre_1, configuracion.resistencia_torres.resistencia_torre_1);
    fprintf(configuraciones, "ENANOS_INICIO= %i , %i, %i, %i \n", configuracion.enanos_inicio[0], configuracion.enanos_inicio[1],configuracion.enanos_inicio[2],configuracion.enanos_inicio[3]);
    fprintf(configuraciones, "ELFOS_INICIO= %i , %i, %i, %i \n", configuracion.elfos_inicio[0], configuracion.elfos_inicio[1],configuracion.elfos_inicio[2],configuracion.elfos_inicio[3]);
    fprintf(configuraciones, "ENANOS_EXTRA= %i, %i \n", configuracion.enanos_extra.cantidad_enanos_extra, configuracion.enanos_extra.coste_torre_1_enanos_extra);
    fprintf(configuraciones, "ELFOS_EXTRA= %i, %i \n", configuracion.elfos_extra.cantidad_elfos_extra, configuracion.elfos_extra.coste_torre_2_elfos_extra);
    fprintf(configuraciones, "ENANOS_ANIMO= %i, %i \n", configuracion.animos_enanos.critico_enanos, configuracion.animos_enanos.fallo_enanos);
    fprintf(configuraciones, "ELFOS_ANIMO= %i, %i \n", configuracion.animos_elfos.critico_elfos, configuracion.animos_elfos.fallo_elfos);
    fprintf(configuraciones, "VELOCIDAD= %f \n", configuracion.velocidad_juego);
    fprintf(configuraciones, "%s; \n", configuracion.ruta_caminos);
    printf("Archivo de configuracion creado!! Recuerda que su nombre es %s \n", ruta_configuracion);
    fclose(configuraciones);
}


//-----------------------------------------------------------------------------------------------------------//

/*
 * Recibe una ruta de donde buscara la repeticion del juego y la velocidad a la que la reproducira
 * 
 */ 
void poneme_la_repe(char ruta[MAX_RUTA], float velocidad){

    FILE* repeticion = fopen(ruta, "r");  
    if (repeticion == NULL){
        printf("Esa direccion no existe!");
        fclose(repeticion);
    }
    else {
		juego_t juego_jugado;
    	fread(&juego_jugado, sizeof(juego_t), 1, repeticion);
    	while (!feof(repeticion)){
        	mostrar_juego(juego_jugado);
        	detener_el_tiempo(velocidad);
    	    system("clear");
        	fread(&juego_jugado, sizeof(juego_t), 1, repeticion);
    		}
    fclose(repeticion);
    }

}

//--------------------------------------------------------------------------------------------------//



/*
 * 
 * Devuelve una letra 
 */ 
char pedir_letra(){
    char letra;
    printf("\n");
    printf("Usa W para ir hacia arriba.\n");
    printf("Usa S para ir hacia abajo.\n");
    printf("Usa A para ir hacia izquierda.\n");
    printf("Usa D para ir hacia derecha.\n");
    printf("Usa F para FINALIZAR el camino.\n");
    scanf(" %c", &letra);
return letra;
}

/*
 * Recibe una letra
 * Devuelve una letra valida (W,A,S,D ò F)
 */ 

char verificar_letra(){
    char letra = pedir_letra();
    while(letra != ARRIBA && letra != ABAJO && letra != DERECHA && letra != IZQUIERDA && letra != FINALIZAR){
        printf("Esa letra no es valida!!\n");
        letra = pedir_letra(); 
    }
    return letra;
}

/*
 * Recibe una letra, un camino, su tope y un valor que cambia segun los niveles
 * Dependiendo de la letra, genera una coordenada extra para el camino, lo termina o vuelve a pedir una letra 
 */ 
void construir_camino(char letra, coordenada_t camino_actual[MAX_LONGITUD_CAMINO], int * tope_camino, int valor_segun_nivel){
    
    if (letra == ARRIBA && camino_actual[*tope_camino - 1].fil > POSICION_INVALIDA){
        camino_actual[*tope_camino].col = camino_actual[*tope_camino - 1].col;
        camino_actual[*tope_camino].fil = camino_actual[*tope_camino - 1].fil - 1;
        (*tope_camino)++;
    }
    
    else if (letra == ABAJO && camino_actual[*tope_camino - 1].fil < valor_segun_nivel - 1){
        camino_actual[*tope_camino].col = camino_actual[*tope_camino - 1].col;
        camino_actual[*tope_camino].fil = camino_actual[*tope_camino - 1].fil + 1;
        (*tope_camino)++;
    }
    else if (letra == DERECHA && camino_actual[*tope_camino - 1].col < valor_segun_nivel - 1){
        camino_actual[*tope_camino].col = camino_actual[*tope_camino - 1].col + 1;
        camino_actual[*tope_camino].fil = camino_actual[*tope_camino - 1].fil;
        (*tope_camino)++;
    }
    else if (letra == IZQUIERDA && camino_actual[*tope_camino - 1].col > POSICION_INVALIDA){
        camino_actual[*tope_camino].col = camino_actual[*tope_camino - 1].col - 1;
        camino_actual[*tope_camino].fil = camino_actual[*tope_camino - 1].fil;
        (*tope_camino)++;
    }
    else if (letra == FINALIZAR){
        printf("CAMINO TERMINADO\n");
    }
    else {
        system("clear");
        printf("Movimiento no valido\n");
        detener_el_tiempo(1);
    }
    system("clear");

}

/*
 * Recibe un terreno 
 * Rellena el terreno con los caracteres correspondientes a la nada
 */ 
void inicializar_nuevo_terreno(char terreno[MAX_TERRENO][MAX_TERRENO], int tope_nivel){
    for (int i = 0; i < tope_nivel; i++){
        for (int j = 0; j < tope_nivel; j++){
            terreno[i][j] = TERRENO;
        }
    }
}

/*
 * Recibe un terreno inicializado
 * Rellena el terreno con los caracteres correspondientes al camino, donde corresponda
 */ 
void rellenar_camino(char terreno[MAX_TERRENO][MAX_TERRENO], coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
    for (int i = 0; i < tope_camino; i++){
        terreno[camino[i].fil][camino[i].col] = CAMINO;
    }
}

/*
 * Recibe un valor, un camino a mostrar y su tope
 * Imprime por pantalla ese camino en el mapa
 */ 
void mostrar_tablero(int valor_segun_nivel, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
char terreno[MAX_TERRENO][MAX_TERRENO];         
    printf("=======================GENERANDO CAMINOS=======================\n");
    printf("                                  1  1  1  1  1  1  1  1  1  1 \n");
    printf("    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9\n");
    printf(" ······························································ \n");
    inicializar_nuevo_terreno(terreno, valor_segun_nivel);
    rellenar_camino(terreno, camino, tope_camino);
    for (int i = 0; i < valor_segun_nivel; i++){
        printf("%2i ", i);
    for (int j = 0; j < valor_segun_nivel; j++){
            printf(" %c ", terreno[i][j]);
        }
        printf("\n");
    }       
    printf("\n");
}
/*
 *Recibe un archivo, una vector de caminos y enteros que representan nivel, camino y el tope del camino
 *Escribe el camino en el archivo recibido
 */
void finalizar_camino (FILE * archivo, int nivel_actual, int camino_actual, coordenada_t camino[MAX_LONGITUD_CAMINO], int tope_camino){
    fprintf(archivo, "NIVEL=%i\n", nivel_actual);
    fprintf(archivo, "CAMINO=%i\n", camino_actual);
    for (int i = 0; i < tope_camino; i++){  
        fprintf(archivo, "%i;%i\n", camino[i].fil, camino[i].col);
    }
}
/*
 * Recibe un archivo en modo escritura
 * Crea un camino en ese archivo, correspondiendo al camino del nivel 1
 */ 
void camino_nivel_1(FILE* archivo){
    int nivel = 1;
    int camino = 1;
    int valor_maximo_nivel = 15;
    coordenada_t camino_nivel_uno[MAX_LONGITUD_CAMINO];
    camino_nivel_uno[0].fil = ENTRADA_1_FILA;
    camino_nivel_uno[0].col = ENTRADA_1_COLUMNA;
    int tope_camino = 1;
    printf("Estableceremos el camino.\n");
    printf("Comenzamos desde el Este! Arrancaremos en la fila %i, columna %i \n", camino_nivel_uno[0].fil, camino_nivel_uno[0].col);
    char letra = verificar_letra();
    construir_camino(letra, camino_nivel_uno, &tope_camino, valor_maximo_nivel);
    mostrar_tablero(valor_maximo_nivel, camino_nivel_uno, tope_camino);
    while (letra != FINALIZAR){
        letra = verificar_letra();
        construir_camino(letra, camino_nivel_uno, &tope_camino, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_nivel_uno, tope_camino);
    }
    if (letra == FINALIZAR){
        finalizar_camino(archivo, nivel, camino, camino_nivel_uno, tope_camino);        
    }
}

/*
 * Recibe un archivo en modo escritura
 * Crea un camino en ese archivo, correspondiendo al camino del nivel 2
 */ 
void camino_nivel_2(FILE* archivo){
    int nivel = 2;
    int camino = 2;
    int valor_maximo_nivel = 15;
    coordenada_t camino_nivel_dos[MAX_LONGITUD_CAMINO];
    camino_nivel_dos[0].fil = ENTRADA_2_FILA;
    camino_nivel_dos[0].col = ENTRADA_2_COLUMNA;
    int tope_camino = 1;
    printf("NIVEL DOS\n");
    printf("Estableceremos el camino.\n");
    printf("Comenzamos desde el Oeste! Arrancaremos en la fila %i, columna %i \n", camino_nivel_dos[0].fil, camino_nivel_dos[0].col);
    char letra = verificar_letra();
    construir_camino(letra, camino_nivel_dos, &tope_camino, valor_maximo_nivel);
    while (letra != FINALIZAR){
        letra = verificar_letra();
        construir_camino(letra, camino_nivel_dos, &tope_camino, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_nivel_dos, tope_camino);
    }
    if (letra == FINALIZAR){
         finalizar_camino(archivo, nivel, camino, camino_nivel_dos, tope_camino);
    }
}

/*
 * Recibe un archivo en modo escritura
 * Crea dos caminos en ese archivo, correspondiendo a los caminos del nivel 3
 */ 
void caminos_nivel_3(FILE* archivo){
    int valor_maximo_nivel = 20;
    int nivel = 3;
    int camino = 1;
    coordenada_t camino_uno_nivel_tres[MAX_LONGITUD_CAMINO];
    camino_uno_nivel_tres[0].fil = ENTRADA_1_NIVEL_3_FILA;
    camino_uno_nivel_tres[0].col = ENTRADA_1_NIVEL_3_COLUMNA;
    int tope_camino_uno = 1;
    printf("==============================\n");
    printf("          NIVEL TRES\n");
    printf("==============================\n");
    printf("Primer camino \n");
    printf("Comenzamos desde el Norte! Arrancaremos en la fila %i, columna %i \n", camino_uno_nivel_tres[0].fil,  camino_uno_nivel_tres[0].col);
    char letra = verificar_letra();
    construir_camino(letra, camino_uno_nivel_tres, &tope_camino_uno, valor_maximo_nivel);
    while (letra != FINALIZAR){
        letra = verificar_letra();
        construir_camino(letra, camino_uno_nivel_tres, &tope_camino_uno, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_uno_nivel_tres, tope_camino_uno);
    }
    if (letra == FINALIZAR){
        finalizar_camino(archivo, nivel, camino, camino_uno_nivel_tres, tope_camino_uno);
    }
    printf("Ahora haremos el segundo camino del nivel 3!\n");
    camino = 2;
    coordenada_t camino_dos_nivel_tres[MAX_LONGITUD_CAMINO];
    camino_dos_nivel_tres[0].fil = ENTRADA_2_NIVEL_3_FILA;
    camino_dos_nivel_tres[0].col = ENTRADA_2_NIVEL_3_COLUMNA;
    int tope_camino_dos = 1;
    printf("Recuerda que vamos desde el Norte! Arrancaremos en la fila %i, columna %i \n", camino_dos_nivel_tres[0].fil,  camino_dos_nivel_tres[0].col);
    char letra2 = verificar_letra();
    construir_camino(letra2, camino_dos_nivel_tres, &tope_camino_dos, valor_maximo_nivel);
    while (letra2 != FINALIZAR){
        letra2 = verificar_letra();
        construir_camino(letra2, camino_dos_nivel_tres, &tope_camino_dos, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_dos_nivel_tres, tope_camino_dos);
    }
    if (letra2 == FINALIZAR){
       finalizar_camino(archivo, nivel, camino, camino_dos_nivel_tres, tope_camino_dos);
    }
}


/*
 * Recibe un archivo en modo escritura
 * Crea dos caminos en ese archivo, correspondiendo a los caminos del nivel 4
 */ 
void caminos_nivel_4(FILE* archivo){
    int nivel = 4;
    int camino = 1;
    int valor_maximo_nivel = 20;
    coordenada_t camino_uno_nivel_cuatro[MAX_LONGITUD_CAMINO];
    camino_uno_nivel_cuatro[0].fil = ENTRADA_1_NIVEL_4_FILA;
    camino_uno_nivel_cuatro[0].col = ENTRADA_1_NIVEL_4_COLUMNA;

    int tope_camino_uno = 1;
    printf("==============================\n");
    printf("          NIVEL FINAL\n");
    printf("==============================\n");
    printf("Primer camino \n");
    printf("Recuerda que vamos desde el Sur! Arrancaremos en la fila %i, columna %i \n", camino_uno_nivel_cuatro[0].fil,  camino_uno_nivel_cuatro[0].col);
    char letra = verificar_letra();
    construir_camino(letra, camino_uno_nivel_cuatro, &tope_camino_uno, valor_maximo_nivel);
    while (letra != FINALIZAR){
        letra = verificar_letra();
        construir_camino(letra, camino_uno_nivel_cuatro, &tope_camino_uno, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_uno_nivel_cuatro, tope_camino_uno);
    }
    if (letra == FINALIZAR){
        finalizar_camino(archivo, nivel, camino, camino_uno_nivel_cuatro, tope_camino_uno);
        
    }
    camino = 2;
    coordenada_t camino_dos_nivel_cuatro[MAX_LONGITUD_CAMINO];
    camino_dos_nivel_cuatro[0].fil = ENTRADA_2_NIVEL_4_FILA;
    camino_dos_nivel_cuatro[0].col = ENTRADA_2_NIVEL_4_COLUMNA;
    printf("Ahora haremos el segundo camino del nivel 4!\n");
    int tope_camino_dos = 1;
    printf("Recuerda que vamos desde el Sur! Arrancaremos en la fila %i, columna %i \n", camino_dos_nivel_cuatro[0].fil,  camino_dos_nivel_cuatro[0].col);
    char letra2 = verificar_letra();
    construir_camino(letra2, camino_dos_nivel_cuatro, &tope_camino_dos, valor_maximo_nivel);
    while (letra2 != FINALIZAR){
        letra2 = verificar_letra();
        construir_camino(letra2, camino_dos_nivel_cuatro, &tope_camino_dos, valor_maximo_nivel);
        mostrar_tablero(valor_maximo_nivel, camino_dos_nivel_cuatro, tope_camino_dos);
    }
    if (letra2 == FINALIZAR){
        finalizar_camino(archivo, nivel, camino, camino_dos_nivel_cuatro, tope_camino_dos);
    }
}

/*
 * Recibe la ruta de donde abrira el archivo de caminos
 * Crea todos los caminos correspondientes a esta ruta.
 */ 
void crear_camino(char archivo_de_grabado[MAX_RUTA]){
    FILE* archivo = fopen(archivo_de_grabado , "w");
    camino_nivel_1(archivo);
    camino_nivel_2(archivo);
    caminos_nivel_3(archivo);
    caminos_nivel_4(archivo);
fclose(archivo);
}

//--------------------------------------------------------------------------------------------------------------------//

/*
 * Recibe un string de caracteres
 * Modifica a ese string rodeado de  palabras (ranking_string.csv)
 */
void fusiones_de_nombres(char configuracion[MAX_RUTA]){
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
 * Recibe un string de caracteres y un entero que representa a la cantidad de personas a mostrar
 * Muestra por pantalla la cantidad de miembros del ranking que corresponda.
 */
void mostrar_ranking(int cantidad, char configuracion[MAX_RUTA]){
    int i = 0;
    char nombre[MAX_NOMBRE];
    int puntaje;
    if(strcmp(configuracion, "predeterminada") != 0){
        fusiones_de_nombres(configuracion);
        FILE* ranking = fopen(configuracion, "r");
        if (cantidad == PREDETERMINADO){
            do {
             fscanf(ranking, "%[^;];%i\n", nombre, &puntaje);
             printf("%s;%i\n", nombre, puntaje);
            }while (!feof(ranking));
        }
        else {
            do {
             fscanf(ranking, "%[^;];%i\n", nombre, &puntaje);
             printf("%s;%i\n", nombre, puntaje);
            i++;
             } while (i < cantidad || !feof(ranking));
       }
     fclose(ranking);
    }
    else{
        FILE* ranking = fopen("ranking.csv", "r");
        if (cantidad == PREDETERMINADO){ 
            do {
                fscanf(ranking, "%[^;];%i\n", nombre, &puntaje);
                printf("%s;%i\n", nombre, puntaje);
            } while (!feof(ranking));
        }
        else{
            do {
                fscanf(ranking, "%[^;];%i\n", nombre, &puntaje);
                printf("%s;%i\n", nombre, puntaje);
                i++;
            } while (i < cantidad || !feof(ranking));   
        }
     fclose(ranking);
    }
}
