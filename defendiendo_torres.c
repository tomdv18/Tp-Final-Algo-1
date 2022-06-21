#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "defendiendo_torres.h"
#include "comandos.h"


static const char ELFO = 'L';
static const char ENANO =	'G';
static const char ORCO =	'0';
static const char TORRE =	'T';
static const char ENTRADA =	'E';
static const char ANIMO_REGULAR =	'R';
static const char ANIMO_BUENO =	'B';
static const char TERRENO = '~';
static const char CAMINO = '#';
const int VALOR_PORCENTAJE_MIN = 1;
const int VALOR_PORCENTAJE_REG = 10;
const int VALOR_PORCENTAJE_MED = 25;
const int PROBABILIDAD_MAXIMA = 100;
const int PROBABILIDAD_AMBIENT_ALTO = 37;
const int PROBABILIDAD_AMBIENT_REG = 25;
const int PROBABILIDAD_AMBIENT_BAJO = 12;
const int CRITICO_ENANO = 100;
const int CRITICO_ELFO = 70;
const int DANIO_NORMAL_ENANO = 60;
const int DANIO_NORMAL_ELFO = 30;
const int VIDA_ORCOS_PREDETER = 200;
const int ATAQUE_FALLIDO = 0;
const int INICIO_DEL_CAMINO = 0;
const int VALOR_ADICIONAL_ORC_MIN = 0;
const int VALOR_ADICIONAL_DEF_MIN = 1;
static const int HUMEDA_ALTA = 75;
static const int HUMEDA_MEDIA = 50;
static const int MUCHO_VIENTO = 75;
static const int MEDIO_VIENTO = 50;
const int RESISTENCIA_TORRE = 600;
const int DEFENSORES_EXTRA = 10;
const int TORRE_SIN_VIDA = 0;
const int ENEMIGO_SIN_VIDA = 0;
const int LVL_ESTE = 1;
const int LVL_OESTE = 2;
const int LVL_NORTE = 3;
const int LVL_SUR = 4;
const int CAMINO_UNO = 1;
const int CAMINO_DOS = 2;
static const int NO_CRITICO = 0;
const int EXITO = 0;
const int ERROR = -1;
const int COORDENADA_MINIMA = 0;
const int POSICION_MUERTO = -5;
const int A_RANGO = 1;
const int  FUERA_RANGO = 0;
static const int MAX_TERRENO = 20;
static const int JUGANDO = 0;
static const int PERDIDO = -1;
static const int GANADO = 1;
static const int NIVELES_PRIMEROS = 15;
static const int NIVELES_ULTIMOS = 20;
static const int PREDETERMINADO = -1;


/*
 *Recibe dos enteros, que representan los limites del numero aleatorio. 
 *Devuelve un numero aleatorio entre los limites enviados
 */
int obtener_numero_random (int valor_minimo, int amplitud_porcentual)  {
  int numero = (rand() % amplitud_porcentual + valor_minimo	);
  return numero;
}
/*
 *Recibe el caracter que corresponde al tipo del defensor 
 *Devuelve un numero segun el tipo recibido.
 */
int ataque_segun_tipo(char tipo){
	if (tipo == ENANO){
	 	return DANIO_NORMAL_ENANO;
	}
	else {
		return DANIO_NORMAL_ELFO;
	}
}
/*
 *Recibe el valor del critico de gimli
 *Devuelve true si el numero aleatorio llamado corresponde al intervalo segun el porcentaje de critico pedido
 */
bool es_critico_enano(juego_t juego){
	int numero = 0;	
	int valor_min = 0;
	int valor_maximo = 0;
	bool es_critico = false;
	numero = obtener_numero_random (VALOR_ADICIONAL_DEF_MIN, PROBABILIDAD_MAXIMA);
	if (juego.critico_gimli == VALOR_PORCENTAJE_REG){
		valor_maximo = VALOR_PORCENTAJE_REG;
			if (numero > valor_min && numero <= valor_maximo){
				es_critico = true;
			}
	}
	else if(juego.critico_gimli == VALOR_PORCENTAJE_MED){
		valor_maximo = VALOR_PORCENTAJE_MED;
			if (numero > valor_min && numero <= valor_maximo){
				es_critico = true;
			}
	}
	return es_critico;
}
/*
 *Recibe el valor del critico de legolas
 *Devuelve true si el numero aleatorio llamado corresponde al intervalo segun el porcentaje de critico pedido
 */
bool es_critico_elfo(juego_t juego){
	int numero = 0;	
	int valor_min = 0;
	int valor_maximo = 0;
	bool es_critico = false;
	numero = obtener_numero_random (VALOR_ADICIONAL_DEF_MIN, PROBABILIDAD_MAXIMA);
	if (juego.critico_legolas == VALOR_PORCENTAJE_REG){
		valor_maximo = VALOR_PORCENTAJE_REG;
			if (numero > valor_min && numero <= valor_maximo){
				es_critico = true;
			}
	}
	else if(juego.critico_legolas == VALOR_PORCENTAJE_MED){
		valor_maximo = VALOR_PORCENTAJE_MED;
			if (numero > valor_min && numero <= valor_maximo){
				es_critico = true;
			}
	}
	return es_critico;
}
/*
 *Recibe un defensor inicializado
 *Le asigna daño al defensor, pudiendo ser este su daño normal o un golpe critico
 */
void danio_critico (defensor_t* defensor, juego_t juego){
	(*defensor).fuerza_ataque = ataque_segun_tipo(defensor->tipo);
	if (defensor->tipo == ENANO){
		if (juego.critico_gimli != NO_CRITICO){
			if (es_critico_enano(juego)){
				(*defensor).fuerza_ataque = CRITICO_ENANO;
			}
		}
	}
	else {
		if (juego.critico_legolas != NO_CRITICO){
			if (es_critico_elfo(juego)){
				(*defensor).fuerza_ataque = CRITICO_ELFO;
			}
		}
	}
}
/*
 *Recibe el porcentaje del viento
 *Devuelve true si el numero aleatorio llamado corresponde al intervalo segun el porcentaje de fallo existente
 */
bool es_fallido_por_viento(juego_t juego){
	int numero;
	int valor_min = 0;
	int valor_maximo = 0;
	bool es_fallido_por_viento = false;
	numero = obtener_numero_random(VALOR_ADICIONAL_DEF_MIN, PROBABILIDAD_MAXIMA);
	if (juego.fallo_legolas == PROBABILIDAD_AMBIENT_ALTO){
		valor_maximo = PROBABILIDAD_AMBIENT_ALTO;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_viento = true;
			}
	}
	else if (juego.fallo_legolas == PROBABILIDAD_AMBIENT_REG){	
		valor_maximo = PROBABILIDAD_AMBIENT_REG;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_viento = true;
		}
	}
	else{
		valor_maximo = PROBABILIDAD_AMBIENT_BAJO;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_viento = true;
		}	
	}
	return es_fallido_por_viento;
}
/*
 *Recibe el porcentaje de la humedad
 *Devuelve true si el numero aleatorio llamado corresponde al intervalo segun el porcentaje de fallo existente
 */
bool es_fallido_por_humedad(juego_t juego){
	int numero = 0;
	int valor_min = 0;
	int valor_maximo = 0;
	bool es_fallido_por_humedad = false;
	numero = obtener_numero_random(VALOR_ADICIONAL_DEF_MIN, PROBABILIDAD_MAXIMA);
	if (juego.fallo_gimli == PROBABILIDAD_AMBIENT_ALTO){
		valor_maximo = PROBABILIDAD_AMBIENT_ALTO;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_humedad = true;
			}
	}
	else if (juego.fallo_gimli == PROBABILIDAD_AMBIENT_REG){	
		valor_maximo = PROBABILIDAD_AMBIENT_REG;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_humedad = true;
		}
	}
	else{
		valor_maximo = PROBABILIDAD_AMBIENT_BAJO;
		if (numero > valor_min && numero <= valor_maximo){
				es_fallido_por_humedad = true;
		}	
	}
	return es_fallido_por_humedad;
}
/*
 *Recibe un defensor inicializado
 *Le asigna daño al defensor, pudiendo ser este su daño normal o un golpe errado
 */
void fallos_de_ataques(defensor_t* defensor, juego_t juego){
	if ((*defensor).tipo == ENANO){
		if (es_fallido_por_humedad(juego)){
			(*defensor).fuerza_ataque = ATAQUE_FALLIDO;
		}
	}
	else{
		if (es_fallido_por_viento(juego)){
		(*defensor).fuerza_ataque = ATAQUE_FALLIDO;
		}
	}	
}
/*
 *Recibe el valor del viento
 *devuelve un Numero que corresponde a la probabilidad de que un elfo erre su proximo ataque
 */
int fallo_segun_viento (int viento){
	if(viento == MUCHO_VIENTO){
		return PROBABILIDAD_AMBIENT_ALTO;
	}
	else if(viento == MEDIO_VIENTO){
		return PROBABILIDAD_AMBIENT_REG;
	}
	else{
		return PROBABILIDAD_AMBIENT_BAJO;
	}
}
/*
 *Recibe el valor de la humedad
 *devuelve un Numero que corresponde a la probabilidad de que un enano erre su proximo ataque
 */
int fallo_segun_humedad (int humedad){
	if(humedad == HUMEDA_ALTA){
		return PROBABILIDAD_AMBIENT_ALTO;
	}
	else if(humedad == HUMEDA_MEDIA){
		return PROBABILIDAD_AMBIENT_REG;
	}
	else{
		return PROBABILIDAD_AMBIENT_BAJO;
	}
}
/*
 *Recibe el valor del animo de legolas
 *devuelve un Numero que corresponde a la probabilidad de que un elfo haga daño critico en su proximo ataque
 */
int critico_legolas_segun_animo(char animo_legolas){
	if (animo_legolas == ANIMO_BUENO){
		return VALOR_PORCENTAJE_MED;
	}
	else if (animo_legolas == ANIMO_REGULAR){
		return VALOR_PORCENTAJE_REG;
	}
	else{
		return NO_CRITICO;
	}
}
/*
 *Recibe el valor del animo de gimli
 *devuelve un Numero que corresponde a la probabilidad de que un enano haga daño critico en su proximo ataque
 */
int critico_gimli_segun_animo(char animo_gimli){
	if (animo_gimli == ANIMO_BUENO){
		return VALOR_PORCENTAJE_MED;
	}
	else if (animo_gimli == ANIMO_REGULAR){
		return VALOR_PORCENTAJE_REG;
	}
	else{
		return NO_CRITICO;
	}
}
/*
 *
 *Carga los defensores extra y la vida de cada torre del juego
 */
void inicializar_torres (juego_t * juego, resistencia_torres_t resistencia_torres, enanos_extra_t enanos_extra, elfos_extra_t elfos_extra){
	if (resistencia_torres.resistencia_torre_1 == PREDETERMINADO){
		juego->torres.resistencia_torre_1 = RESISTENCIA_TORRE;
	}
	else if(resistencia_torres.resistencia_torre_1 != PREDETERMINADO){
		juego->torres.resistencia_torre_1 = resistencia_torres.resistencia_torre_1;
	}
	if (resistencia_torres.resistencia_torre_2 == PREDETERMINADO){
		juego->torres.resistencia_torre_2 = RESISTENCIA_TORRE;
	}
	else if(resistencia_torres.resistencia_torre_2 != PREDETERMINADO){
		juego->torres.resistencia_torre_2 = resistencia_torres.resistencia_torre_2;
	}
	if (enanos_extra.cantidad_enanos_extra == PREDETERMINADO){
		juego->torres.enanos_extra = DEFENSORES_EXTRA;
	}
	else if (enanos_extra.cantidad_enanos_extra != PREDETERMINADO){
		juego->torres.enanos_extra = enanos_extra.cantidad_enanos_extra;
	}
	if (elfos_extra.cantidad_elfos_extra == PREDETERMINADO){
		juego->torres.elfos_extra = DEFENSORES_EXTRA;
	}
	else if (elfos_extra.cantidad_elfos_extra != PREDETERMINADO){
		juego->torres.elfos_extra = elfos_extra.cantidad_elfos_extra;
	}	
}

/*
 * Inicializará el juego, cargando la informacion de las torres y
 * los ataques críticos y fallo de Legolas y Gimli.
 * NO inicializará el primer nivel.
 */
void inicializar_juego(juego_t* juego, int viento, int humedad, char animo_legolas, char animo_gimli, configuracion_t configuracion){
	juego->nivel_actual = LVL_ESTE;
	inicializar_torres(&(*juego), configuracion.resistencia_torres, configuracion.enanos_extra, configuracion.elfos_extra);
	

	if (configuracion.animos_elfos.fallo_elfos == PREDETERMINADO){
		juego->fallo_legolas = fallo_segun_viento(viento);
	}
	if (configuracion.animos_elfos.fallo_elfos != PREDETERMINADO){
		juego->fallo_legolas = configuracion.animos_elfos.fallo_elfos;
	}
	if(configuracion.animos_enanos.fallo_enanos == PREDETERMINADO){
		juego->fallo_gimli = fallo_segun_humedad(humedad);
	}
	if(configuracion.animos_enanos.fallo_enanos != PREDETERMINADO){
		juego->fallo_gimli = configuracion.animos_enanos.fallo_enanos;
	}
	if (configuracion.animos_elfos.critico_elfos == PREDETERMINADO){
	juego->critico_legolas = critico_legolas_segun_animo(animo_legolas);
	}
	if (configuracion.animos_elfos.critico_elfos != PREDETERMINADO){
		juego->critico_legolas = configuracion.animos_elfos.critico_elfos;
	}
	if (configuracion.animos_enanos.critico_enanos == PREDETERMINADO){
	juego->critico_gimli = critico_gimli_segun_animo(animo_gimli);
	}
	if (configuracion.animos_enanos.critico_enanos != PREDETERMINADO){
	juego->critico_gimli = configuracion.animos_enanos.critico_enanos;
	}
}

/*
 *
 *Devuelve un numero entre 200 y 300
 */
int vida_adicional_orcos(){
int numero = (obtener_numero_random(VALOR_ADICIONAL_ORC_MIN, PROBABILIDAD_MAXIMA) + VIDA_ORCOS_PREDETER); 
	return numero;
}
/*
 *Recibe un juego inicializado
 *Crea un/os enemigo/s dependiendo del nivel en el que estemos
 */
void inicializar_enemigo(juego_t* juego){
	if (juego->nivel.max_enemigos_nivel > juego->nivel.tope_enemigos){
		if (juego->nivel_actual == LVL_ESTE){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_UNO;
			juego->nivel.tope_enemigos++;
		}
		else if (juego->nivel_actual == LVL_OESTE){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_DOS;
			juego->nivel.tope_enemigos++;
		}
		else if (juego->nivel_actual == LVL_NORTE){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_DOS;
			juego->nivel.tope_enemigos++;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_UNO;
			juego->nivel.tope_enemigos++;
		}
		else if (juego->nivel_actual == LVL_SUR){
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_DOS;
			juego->nivel.tope_enemigos++;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].vida = vida_adicional_orcos();
			juego->nivel.enemigos[juego->nivel.tope_enemigos].pos_en_camino = INICIO_DEL_CAMINO;
			juego->nivel.enemigos[juego->nivel.tope_enemigos].camino = CAMINO_UNO;
			juego->nivel.tope_enemigos++;
		}
	}
}
/*
 *Recibe un juego inicializado
 *Mueve a todos los enemigos si estan vivos
 */
void mover_enemigos (juego_t * juego){
	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
		 if(juego->nivel.enemigos[i].vida > ENEMIGO_SIN_VIDA){	
		 		juego->nivel.enemigos[i].pos_en_camino++;
		}		
	}
}
/*
 *Recibe un nivel
 *Si existe al menos un enemigo vivo, devuelve true
 */
bool hay_enemigos_vivos (nivel_t nivel){
bool hay_enemigos_vivos = true;
int contador = 0;

	for (int i = 0; i < nivel.tope_enemigos; i++){
			if (nivel.enemigos[i].vida > ENEMIGO_SIN_VIDA){
				contador++;
			}
	}	
	if (contador == 0){
		hay_enemigos_vivos = false;
	}
	
return hay_enemigos_vivos;
}
/*
 *Recibe un juego previamente cargado
 *Devuelve verdadero si y solo si ambas torres siguen con vida
 */
bool estan_torres_de_pie (juego_t juego){
	if ((juego.torres.resistencia_torre_1) == TORRE_SIN_VIDA || (juego.torres.resistencia_torre_2) == TORRE_SIN_VIDA ){
		return false;
	}
	else{ 
		return true;
	}
}
/*
 *Recibe un juego con sus torres y enemigos.
 *Si algun enemigo hace daño a la torre, le reducera la vida a ambos. 
 */
void daniar_torres (juego_t* juego){
	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
			if (juego->nivel.enemigos[i].pos_en_camino == (juego->nivel.tope_camino_1 - 1)  && juego->nivel.enemigos[i].camino == 1 && juego->nivel.enemigos[i].vida > ENEMIGO_SIN_VIDA) {
				juego->torres.resistencia_torre_1 = (juego->torres.resistencia_torre_1 - juego->nivel.enemigos[i].vida);
				juego->nivel.enemigos[i].vida = ENEMIGO_SIN_VIDA;
			}
		}
	for (int j = 0; j <juego->nivel.tope_enemigos; j++){
			if (juego->nivel.enemigos[j].pos_en_camino == (juego->nivel.tope_camino_2 - 1 ) && juego->nivel.enemigos[j].camino == 2 && juego->nivel.enemigos[j].vida > ENEMIGO_SIN_VIDA) {
				juego->torres.resistencia_torre_2 = (juego->torres.resistencia_torre_2 - juego->nivel.enemigos[j].vida);
				juego->nivel.enemigos[j].vida = ENEMIGO_SIN_VIDA;
			}
	}		
}	 	
/*
 *Recibe un juego previamente cargado
 *Devuelve al juego despues de los movimientos de los orcos.
 */
void turno_orcos (juego_t *juego){
	mover_enemigos(&(*juego));
	daniar_torres (&(*juego));
	inicializar_enemigo(&(*juego));
}
/*
 *Recibe un juego previamente cargado
 *Devuelve verdadero si  ambas torres siguen con vida, el nivel es el ultimo y no hay mas enemigos vivos
 */
bool juego_ganado (juego_t juego){
	bool juego_ganado = false;
	if (juego.nivel_actual == LVL_SUR && estan_torres_de_pie(juego) && !hay_enemigos_vivos(juego.nivel)){
		juego_ganado = true;
	}
return juego_ganado;
}
/*
 * Recibe un juego con todas sus estructuras válidas. 
 * El juego se dará por ganado si el juego está en el ultimo nivel y éste ha sido terminado.
 * El juego se dará por perdido, si alguna de las torres llega a 0 en su resistencia.
 * Devolverá:
 * >  0 si el estado es jugando.
 * > -1 si el estado es perdido.
 * >  1 si el estado es ganado.
 */
int estado_juego(juego_t juego){
	if (juego_ganado(juego)){
		return GANADO;
	}
	else if (!estan_torres_de_pie(juego)){
		return PERDIDO;
	}
	else{
		return JUGANDO;
	}	
}
/*
 * Recibe un nivel con todas sus estructuras válidas. 
 * El nivel se dará por ganado cuando estén TODOS los orcos de ese 
 * nivel muertos (esto es, con vida menor o igual a 0).
 * Devolverá:
 * >  0 si el estado es jugando.
 * >  1 si el estado es ganado.
 */
int estado_nivel(nivel_t nivel){
	int contador = 0;
	for (int i = 0; i < nivel.max_enemigos_nivel; i++){
		if (nivel.enemigos[i].vida <= ENEMIGO_SIN_VIDA){
			contador++;
		}
	}
	if (contador == nivel.max_enemigos_nivel)	{
		return GANADO;
	}
	else {
		return JUGANDO;
	}
}
/*
 * Recibe el nivel y unas coordenadas
 * Devuelve verdadero si y solo si esas cordenadas no corresponden a nada mas en el nivel
 */
bool es_valida_posicion (nivel_t nivel, coordenada_t posicion){	
	for(int i = 0; i < nivel.tope_defensores; i++){
		if( nivel.defensores[i].posicion.fil == posicion.fil &&	
			nivel.defensores[i].posicion.col == posicion.col){
		return false;
		}
	}
	for (int j = 0; j < nivel.tope_camino_1; j++){
		if (nivel.camino_1[j].col == posicion.col &&	
			nivel.camino_1[j].fil == posicion.fil){
		return false;
		}
	}	
	for (int k = 0; k < nivel.tope_camino_2; k++){
		if (nivel.camino_2[k].col == posicion.col &&	
			nivel.camino_2[k].fil == posicion.fil){
		return false;
		}	
	}	
	return true;
}
/* 
 * Agregará un defensor en el nivel recibido como parametro.
 * Devolverá:
 * >  0 si pudo agregar el defensor correctamente.
 * > -1 si no pudo (la coordenada es parte del camino de ese nivel, 
 * existe otro defensor, etc.)
 */
int agregar_defensor(nivel_t* nivel, coordenada_t posicion, char tipo){
	int se_pudo = EXITO;
	if (es_valida_posicion(*nivel, posicion)){
			nivel->defensores[nivel->tope_defensores].posicion = posicion;
			nivel->defensores[nivel->tope_defensores].tipo = tipo;
			nivel->defensores[nivel->tope_defensores].fuerza_ataque = ataque_segun_tipo(tipo);
			nivel->tope_defensores++;
			return se_pudo;
		}
	else{
		return ERROR;
	}	
}
/*
 *Recibe un defensor y un enemigo
 *devuelve la vida del enemigo menos el daño realizado por el defensor
 */
void atacar_enemigo(defensor_t defensor, enemigo_t* enemigo){
	enemigo->vida = (enemigo->vida - defensor.fuerza_ataque);
}
/*
 *Recibe un defensor, las posibilidades de que su ataque se modifique y a un enemigo
 *Devuelve los cambios en la vida del enemigo (si los hubo)
 */
void definir_ataque(defensor_t * defensor, juego_t juego, enemigo_t *enemigo){
	danio_critico (&(*defensor), juego);
	fallos_de_ataques(&(*defensor), juego);
	atacar_enemigo (*defensor, &(*enemigo));	
}
/* 
 * Recibe un enano y su posicion
 * Devuelve, si es que existe, el ultimo personaje enemigo en su rango de ataque
 */
int posicion_enemigo_cuerpo_cuerpo(defensor_t defensor, coordenada_t camino_1[MAX_LONGITUD_CAMINO], coordenada_t camino_2[MAX_LONGITUD_CAMINO], enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos){
  int pos_enemigo = -1;
    for(int i = 0; i < tope_enemigos;  i++){
        if(camino_1[enemigos[i].pos_en_camino].col == (defensor.posicion.col - 1) || camino_1[enemigos[i].pos_en_camino].col == defensor.posicion.col || camino_1[enemigos[i].pos_en_camino].col == (defensor.posicion.col + 1)){
      		if((camino_1[enemigos[i].pos_en_camino].fil == (defensor.posicion.fil - 1) || camino_1[enemigos[i].pos_en_camino].fil == defensor.posicion.fil || camino_1[enemigos[i].pos_en_camino].fil == defensor.posicion.fil + 1) && enemigos[i].vida > ENEMIGO_SIN_VIDA){
          	pos_enemigo = i;
        	}
      	}
      	if(camino_2[enemigos[i].pos_en_camino].col == (defensor.posicion.col - 1) || camino_2[enemigos[i].pos_en_camino].col == defensor.posicion.col || camino_2[enemigos[i].pos_en_camino].col == (defensor.posicion.col + 1)){
      		if((camino_2[enemigos[i].pos_en_camino].fil == (defensor.posicion.fil - 1) || camino_2[enemigos[i].pos_en_camino].fil == defensor.posicion.fil || camino_2[enemigos[i].pos_en_camino].fil == defensor.posicion.fil + 1) && enemigos[i].vida > ENEMIGO_SIN_VIDA){
          	pos_enemigo = i;
   			}
   		}
   	}	
  return pos_enemigo;
}
/*
 *Recibe un defensor y a los enemigos 
 *Si un enemigo esta a rango, llama a la funcion para atacarlo
 */
void turno_enano_individual(defensor_t defensor, juego_t* juego){
	int enemigo_a_atacar = posicion_enemigo_cuerpo_cuerpo(defensor, juego->nivel.camino_1, juego->nivel.camino_2, juego->nivel.enemigos, juego->nivel.tope_enemigos);
		if (enemigo_a_atacar != -1){
			definir_ataque(&defensor, (*juego), &(juego->nivel.enemigos[enemigo_a_atacar]));
		}
}
/*
 *Recibe al juego, los defensores y su tope
 *Devuelve al juego despues del turno de los enanos
 */
void turno_enanos (defensor_t defensores[MAX_DEFENSORES], int tope_defensores, juego_t * juego){
	for (int i = 0; i < tope_defensores; i++){
		if (defensores[i].tipo == ENANO){
			turno_enano_individual(defensores[i], &(*juego));
		}	
	}
}
/*
 *Recibe un numero 
 *Devuelve ese numero pero siempre de valor positivo
 */
int conseguir_modulo(int numero) {
 	if (numero < 0) {
    	numero = numero * (-1);
 	}
	return numero;
}
/*
 *Recibe un defensor y un camino con enemigos y sus posiciones
 *Devuelve 1 si el enemigo esta a rango del defensor, 0 si no esta a rango
 */
int distancia_taxi(defensor_t defensor, coordenada_t camino[MAX_LONGITUD_CAMINO], enemigo_t enemigo){
  	int distancia = -1;
	distancia = conseguir_modulo(defensor.posicion.fil - camino[enemigo.pos_en_camino].fil) + 
  				conseguir_modulo(defensor.posicion.col - camino[enemigo.pos_en_camino].col);
 	if (distancia > 0 && distancia <= 3){
		return A_RANGO;
 	}
 	else{ 
 		return FUERA_RANGO;
 	}
}	
/*
 *Recibe un defensor y a los enemigos 
 *Si un enemigo esta a rango, llama a la funcion para atacarlo
 */
void turno_elfo_individual (defensor_t defensor, juego_t * juego){
int contador = 0 ;
	for (int i = 0; i < juego->nivel.tope_enemigos; i++){
		contador = distancia_taxi(defensor, juego->nivel.camino_1,  juego->nivel.enemigos[i]);
			if (contador == 1 && juego->nivel.enemigos[i].vida > ENEMIGO_SIN_VIDA  ){
				definir_ataque (&defensor, *juego, &(*juego).nivel.enemigos[i]);
			}
	}			
	for (int j = 0; j < juego->nivel.tope_enemigos; j++){
		contador = distancia_taxi(defensor, juego->nivel.camino_2,  juego->nivel.enemigos[j]);
			if (contador == 1 && juego->nivel.enemigos[j].vida > ENEMIGO_SIN_VIDA){
				definir_ataque (&defensor, *juego, &(*juego).nivel.enemigos[j]);
			}
	}	
}
/*
 *Recibe a los defensores y su tope
 *Si el defensor es un elfo, llama a la funcion para atacar enemigos.
 */
void turno_elfos(defensor_t defensores[MAX_DEFENSORES], int tope_defensores, juego_t* juego){
	for (int i = 0; i < tope_defensores; i++){
		if (defensores[i].tipo == ELFO){
			turno_elfo_individual(defensores[i], &(*juego));
		}
	}
}
/*
 * Jugará un turno y dejará el juego en el estado correspondiente.
 * Harán su jugada enanos, elfos y orcos en ese orden.
 */
void jugar_turno(juego_t* juego){
	turno_enanos((juego->nivel.defensores), juego->nivel.tope_defensores, &(*juego));
	turno_elfos((juego->nivel.defensores), juego->nivel.tope_defensores, &(*juego));
	turno_orcos(&(*juego));

}
/*
 *Recibe la matriz del terreno sin inicializar
 *Rellena la matriz del terreno
 */
void inicializar_terreno(juego_t juego, char terreno[MAX_TERRENO][MAX_TERRENO], int tope_del_nivel){
	for (int i = 0; i < tope_del_nivel; i++){
		for (int j = 0; j < tope_del_nivel; j++){
			terreno[i][j] = TERRENO;
		}
	}		
}
/*
 *Recibe la matriz del terreno sin inicializar
 *Rellena la matriz del terreno
 */
void mostrar_defensores (defensor_t defensores[MAX_DEFENSORES], int tope_defensores, char terreno[MAX_TERRENO][MAX_TERRENO]){
	for (int i = 0; i < tope_defensores; i++){
		terreno[defensores[i].posicion.fil][defensores[i].posicion.col] = defensores[i].tipo;
	}	
}	
/*
 *Recibe la matriz del terreno ya inicializada 
 *Rellena la matriz con los caminos
 */
void mostrar_caminos (char terreno[MAX_TERRENO][MAX_TERRENO], coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2){
	for (int i = 0; i < tope_camino_1; i++){
		terreno[camino_1[i].fil][camino_1[i].col] = CAMINO;
	}
	for (int j = 0; j < tope_camino_2; j++){
		terreno[camino_2[j].fil][camino_2[j].col] = CAMINO;
	}
}
/*
 *Recibe los caminos y el vector de enemigos con sus topes. Tambien recibe la matriz del terreno
 *Le asigna a la matriz terreno una O si en ese lugar del camino hay un orco
 */
void mostrar_orcos (coordenada_t camino_1[MAX_LONGITUD_CAMINO], int tope_camino_1, coordenada_t camino_2[MAX_LONGITUD_CAMINO], int tope_camino_2, enemigo_t enemigos[MAX_ENEMIGOS], int tope_enemigos, char terreno[MAX_TERRENO][MAX_TERRENO]){
	for (int i = 0; i < tope_camino_1; i++){
      		if (enemigos[i].camino == 1 && enemigos[i].vida > ENEMIGO_SIN_VIDA){
      			terreno[camino_1[enemigos[i].pos_en_camino].fil][camino_1[enemigos[i].pos_en_camino].col] = ORCO;
    		}
 	}
	for (int j = 0; j < tope_camino_2; j++){
      		if (enemigos[j].camino == 2 && enemigos[j].vida > ENEMIGO_SIN_VIDA){
      			terreno[camino_2[enemigos[j].pos_en_camino].fil][camino_2[enemigos[j].pos_en_camino].col] = ORCO;
    		}
 	}
}		
/*
 *Recibe la matriz del terreno ya inicializada
 *Rellena la matriz con las torres
 */
void mostrar_torre(juego_t juego, char terreno[MAX_TERRENO][MAX_TERRENO]){
	if (juego.nivel_actual == LVL_ESTE){
		terreno[juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1 -1 ].col] = TORRE;
	}
	if (juego.nivel_actual == LVL_OESTE ){
	terreno[juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2 -1 ].col] = TORRE;
	}
	if (juego.nivel_actual == LVL_NORTE){
	terreno[juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1 -1 ].col] = TORRE;
	terreno[juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2 -1 ].col] = TORRE;
	}
	if (juego.nivel_actual == LVL_SUR){
	terreno[juego.nivel.camino_1[juego.nivel.tope_camino_1 - 1].fil][juego.nivel.camino_1[juego.nivel.tope_camino_1 -1 ].col] = TORRE;
	terreno[juego.nivel.camino_2[juego.nivel.tope_camino_2 - 1].fil][juego.nivel.camino_2[juego.nivel.tope_camino_2 -1 ].col] = TORRE;
	}
}
/*
 *Recibe la matriz del terreno ya inicializada
 *Rellena la matriz con las torres
 */
void mostrar_entrada(juego_t juego, char terreno[MAX_TERRENO][MAX_TERRENO]){
	if ((juego.nivel_actual == LVL_NORTE || juego.nivel_actual == LVL_ESTE || juego.nivel_actual == LVL_SUR) && ( 0 < juego.nivel.tope_camino_1)){
		terreno[juego.nivel.camino_1[0].fil][juego.nivel.camino_1[0].col] = ENTRADA;
	}
	if ((juego.nivel_actual == LVL_NORTE || juego.nivel_actual == LVL_OESTE || juego.nivel_actual == LVL_SUR) && ( 0 < juego.nivel.tope_camino_2)){
		terreno[juego.nivel.camino_2[0].fil][juego.nivel.camino_2[0].col] = ENTRADA;
	}
}
/* 
 * Mostrará el mapa dependiendo del nivel en que se encuentra el jugador.
 */
void mostrar_juego(juego_t juego){
 	char terreno[MAX_TERRENO][MAX_TERRENO];	
	int tope_del_nivel = 0;	
	if (juego.nivel_actual == LVL_ESTE || juego.nivel_actual == LVL_OESTE){
		tope_del_nivel = NIVELES_PRIMEROS;
	}
	else{
		tope_del_nivel = NIVELES_ULTIMOS;
	}	
	printf("=======================DEFENDIENDO TORRES=======================\n");
	printf("                                  1  1  1  1  1  1  1  1  1  1 \n");
	printf("    0  1  2  3  4  5  6  7  8  9  0  1  2  3  4  5  6  7  8  9\n");
	printf(" ······························································ \n");
	inicializar_terreno(juego, terreno, tope_del_nivel);
	mostrar_caminos(terreno, juego.nivel.camino_1, juego.nivel.tope_camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_2);
	mostrar_torre(juego, terreno);
	mostrar_entrada(juego, terreno);
	mostrar_defensores ( juego.nivel.defensores, juego.nivel.tope_defensores, terreno);
	mostrar_orcos (juego.nivel.camino_1, juego.nivel.tope_camino_1, juego.nivel.camino_2, juego.nivel.tope_camino_2, juego.nivel.enemigos, juego.nivel.tope_enemigos, terreno);
	
	for (int i = 0; i < tope_del_nivel; i++){
		printf("%2i ", i);
		for (int j = 0; j < tope_del_nivel; j++){
			printf(" %c ", terreno[i][j]);
		}
		printf("\n");
	}		
	printf("\n");
	printf("La probabilidad de fallo elfico es de un %i  \n", juego.fallo_legolas );
	printf("La probabilidad de fallo enanistico es de un %i  \n", juego.fallo_gimli );
	printf("La probabilidad de critico elfico es de un %i  \n", juego.critico_legolas);
	printf("La probabilidad de critico enanistico es de un %i   \n", juego.critico_gimli);
	printf("VIDA TORRE 1  %i   \n", juego.torres.resistencia_torre_1);
	printf("VIDA TORRE 2  %i   \n", juego.torres.resistencia_torre_2);
	printf("Enanos extra: %i   \n", juego.torres.enanos_extra);
	printf("Elfos extra:  %i   \n", juego.torres.elfos_extra);
	printf("\n");
}