
#include <stdio.h>
#include <stdbool.h>
#include "animos.h"


const int INICIALIZADOR = 0;
const int INICIALIZADOR_ESPECIFICO = 100;
const char PATA_IZQ = 'I';
const char PATA_DER = 'D';
const char MANIANA = 'M';
const char TARDE = 'T';
const char NOCHE = 'N';
const char ENSALADA = 'E';
const char GUISO = 'G';
const char HAMBURGUESA = 'H';
const char PIZZA = 'P';
const char ANIMO_BUENO = 'B';
const char ANIMO_REGULAR = 'R';
const char ANIMO_MALO = 'M';
const int DIA_MAX = 30;
const int DIA_MIN = 1;
const int SUENIO_MIN = 0;
const int SUENIO_MAX = 12;
const int DIA_MAX_VIENTO_ALTO = 10;
const int DIA_MIN_VIENTO_MEDIO = 11;
const int DIA_MAX_VIENTO_MEDIO = 20;
const int DIA_MIN_VIENTO_LEVE = 21;
const int MUCHO_VIENTO = 75;
const int MEDIO_VIENTO = 50;
const int POCO_VIENTO = 25;
const int HUMEDA_ALTA = 75;
const int HUMEDA_MEDIA = 50;
const int HUMEDA_BAJA = 25;
const int HORAS_DORMIDAS_MEDIA_MAX = 8;
const int HORAS_DORMIDAS_MEDIA_MIN = 5;
const int SUMAR_ANIMO_EXCELENTE = 20;
const int SUMAR_ANIMO_BUENO = 15;
const int SUMAR_ANIMO_REGULAR = 10;
const int SUMAR_ANIMO_MALO =5;
const int ANIMO_MALO_MIN = 5;
const int ANIMO_MALO_MAX = 20;
const int ANIMO_REGU_MIN = 21;
const int ANIMO_REGU_MAX = 35;
const int ANIMO_BUENO_MIN = 36;
const int ANIMO_BUENO_MAX = 50;

//DISCLAIMER: Nunca vi el señor de los anillos, pido disculpas si algo ingresado no corresponde al lore original!


/*
 *
 *Funcion que chequea si el numero ingresado por el usuario es valido
 *Devuelve true si el numero esta dentro de los parametros validos (Entre 1 y 30)
 */
bool es_dia_valido (int dia){
	return (dia <= DIA_MAX && dia >= DIA_MIN);
}

/*
 *
 *Funcion que chequea si el caracter ingresado por el usuario es valido
 *Devuelve true si el caracter es igual a alguno de los tres valores posibles (N, T, ò M)
 */
bool es_hora_valida (char hora){
	return (hora == NOCHE || hora == TARDE || hora == MANIANA);
}

/*
 *
 *Funcion que chequea si el caracter ingresado es valido
 *Devuelve true si el caracter pertenece a alguno de los dos valores posibles (I ò D)
 */
bool es_pie_valido (char pie){
	return (pie == PATA_IZQ || pie == PATA_DER );
}

/*
 *
 *Funcion que chequea si el caracter es correcto
 *Devuelve true si el caracter igual a algun valor posible (G, H, P ò E)
 */
bool es_cena_valido (char cena){
	return (cena == HAMBURGUESA || cena == GUISO || cena == ENSALADA || cena == PIZZA);
}

/*
 *
 *Funcion que chequea si el numero esta entre los numeros validos
 *Devuelve true solo si el entero pertenece a estos parametros validos (0 ò 12)
 */
bool es_suenio_correcto (int horas_suenio){
	return (horas_suenio <= SUENIO_MAX && horas_suenio >= SUENIO_MIN);
}

/*
 *Funcion que recibe un numero entero
 *Chequea que el parametro sea valido, sino lo pide nuevamente
 *Devuelve un numero que pertenece a los valores correctos (Entre 1 y 30. Ambos inclusive)
 */
void en_que_dia (int* dia){
	printf("En que dia del mes nos encontramos? (Del 1 al 30):\n");
	scanf("%i", dia);
	while (!es_dia_valido(*dia)){
		printf("Esa fecha no es correcta. Inserta un numero del 1 al 30\n");
		printf("En que dia del mes nos encontramos? (Del 1 al 30):\n ");
		scanf("%i", dia);
	}
}		

/*
 *Recibe un caracter  
 *Si el valor no es correcto, lo vuelve a solicitar
 *Sale un caracter alfabetico, mayuscula y valido (M, T ò N)
 */
void en_que_hora (char* hora){
 	printf("Estamos en la mañana (M), la tarde (T) o la noche (N)?:\n");
 	scanf (" %c", hora);
 	while (!es_hora_valida(*hora)){
 		printf("Ingresaste un caracter no valido \n");
 		printf("Estamos en la mañana (M), la tarde (T) o la noche (N)?:\n");
 		scanf (" %c", hora);
 	}
}

/*
 *Recibe un caracter 
 *Si el valor recibido no es correcto, lo vuelve a solicitar
 *Sale un caracter alfabetico, mayuscula y valido (I ò D)
 */
void cual_pie_primero (char *pie){
	printf("Con que pie se levanto? (I o D):\n");
	scanf(" %c", pie);
	while(!es_pie_valido (*pie)){
		printf ("Eso no es un pie, hasta los duendes solo tienen dos pies, ingresa de nuevo\n");
		printf("Con que pie se levanto? (I o D):\n");
		scanf(" %c", pie);
	}
}

/*
 *Recibe un caracter  
 *Si el valor no es correcto, lo vuelve a solicitar
 *Sale un caracter alfabetico, mayuscula y valido (P, E, G ò H)
 */
void que_comio_cena(char* cena){
	printf("Que ceno anoche? H (Hamburguesa), P (Pizza), E (Ensalada) o G (Guiso):\n");
	scanf(" %c", cena);
	while (!es_cena_valido(*cena)){
		printf("Ingresaste una cena que no esta en los parametros, vuelve a intentar\n");
		printf("Que ceno anoche? H (Hamburguesa), P (Pizza), E (Ensalada) o G (Guiso):\n");
		scanf(" %c", cena);
	}	
}

/*
 *Recibe un numero entero ingresado por el usuario
 *Pide el numero hasta que sea valido
 *Devuelve un entero, que este entre los valores validos (0 y 12. Ambos inclusive)
 */
void cuantas_horas_suenio(int* horas_suenio){
	printf("Cuantas horas durmio anoche? De 0 a 12.:\n");
	scanf(" %i", horas_suenio);
	while (!es_suenio_correcto(*horas_suenio)){
		printf("Nadie duerme esa cantidad de horas!\n");
		printf("Cuantas horas durmio anoche? De 0 a 12.:\n");
		scanf(" %i", horas_suenio);
	}
}

/*
 *Recibe un entero entre 1 y 30, perteneciente a la variable dia
 *Segun el valor del entero, le asigna un valor a la variable viento
 *Devuelve uno de estos tres enteros, representando al viento (25,50 ò 75)
 */
void viento_segun_dia(int dia, int* viento){
	if ((dia <= DIA_MAX_VIENTO_ALTO) && (dia >= DIA_MIN)){
		(*viento = MUCHO_VIENTO);
	}
	else if ((dia <= DIA_MAX_VIENTO_MEDIO) && (dia >= DIA_MIN_VIENTO_MEDIO)){	
		(*viento = MEDIO_VIENTO);
	}
	else{
		(*viento = POCO_VIENTO);
	}
}

/*
 *Recibe un caracter que representa al momento del dia (M, T ò N)
 *Dependiendo del caracter ingresado, asigna un valor a la variable humedo
 *Devuelve un valor entero a la humedad, que puede ser (25, 50 ò 75)
 */
void humedad_segun_hora (char hora, int* humedad){
	if (hora == MANIANA){
		(*humedad = HUMEDA_ALTA);
	}
	else if (hora == TARDE){	
		(*humedad = HUMEDA_BAJA);
	}
	else{
		(*humedad = HUMEDA_MEDIA);
	}
}

/*
 *Recibe el valor del caracter correspondiente a la cena (E, G, H ò P)
 *Dependiendo del valor ingresado, le suma un valor a la variable animo
 *Devuelve el valor del animo, sumado con un entero dependiendo del valor ingresado (5, 10, 15 ò 20)
 */
void sumador_animo_segun_cena (char cena_lego, int* animo_parcial_legolas){
	if (cena_lego == ENSALADA){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_EXCELENTE);
	}
	else if (cena_lego == HAMBURGUESA){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_BUENO);
	}
	else if (cena_lego == GUISO){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_MALO);
	}
	else{
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_REGULAR);
	}
}	

/*
 *Recibe el valor alfabetico correspondiente a con que pie se levanto
 *Dependiendo del valor ingresado, le suma un valor a la variable animo
 *Devuelve el valor del animo, sumado con un entero que representa el animo (0 ò 10)
 */
void sumador_animo_segun_pie (char pie_lego, int* animo_parcial_legolas){
	if (pie_lego == PATA_DER){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_REGULAR);
	}
}

/*
 *Recibe el valor numerico de las horas de sueño (Entre 0 y 12)
 *Dependiendo del valor ingresado, le suma un valor a la variable animo
 *Devuelve el valor del animo, sumado con un entero que representa el animo (0, 10 ò 20)
 */
void sumador_animo_segun_suenio (int horas_suenio_lego, int* animo_parcial_legolas){
	if ((horas_suenio_lego <= SUENIO_MAX) && (horas_suenio_lego > HORAS_DORMIDAS_MEDIA_MAX)){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_EXCELENTE);
	}
	else if ((horas_suenio_lego <= HORAS_DORMIDAS_MEDIA_MAX) && (horas_suenio_lego >= HORAS_DORMIDAS_MEDIA_MIN)){
		(*animo_parcial_legolas = *animo_parcial_legolas + SUMAR_ANIMO_REGULAR);
	}
}

/*
 *Recibe el valor numerico del animo total
 *Dependiendo del valor ingresado, le asigna un valor a la variable animo final
 *Devuelve el valor del animo final, representado con una letra Mayuscula (M, B ò R)
 */
void animo_final (int animo_parcial_gimli, char* animo_gimli){ 
	if ((animo_parcial_gimli <= ANIMO_MALO_MAX) &&  (animo_parcial_gimli >= ANIMO_MALO_MIN)){ 
 		(*animo_gimli = ANIMO_MALO);
	}
	else if ((animo_parcial_gimli <= ANIMO_REGU_MAX) &&  (animo_parcial_gimli >= ANIMO_REGU_MIN)){ 
		(*animo_gimli = ANIMO_REGULAR);
	}
	else if ((animo_parcial_gimli <= ANIMO_BUENO_MAX) &&  (animo_parcial_gimli >= ANIMO_BUENO_MIN)){ 
		(*animo_gimli = ANIMO_BUENO);
	}	
}


void animos(int* viento, int* humedad, char* animo_legolas,
			 char* animo_gimli){

	int dia = INICIALIZADOR;
 	char hora;
 	char pie_lego;
 	char pie_gim;
 	char cena_lego;
 	char cena_gim;
 	int horas_suenio_gim = INICIALIZADOR_ESPECIFICO;
 	int horas_suenio_lego = INICIALIZADOR_ESPECIFICO;
 	int animo_parcial_gimli = INICIALIZADOR;
 	int animo_parcial_legolas = INICIALIZADOR;
 	/*viento = INICIALIZADOR;
 	*humedad = INICIALIZADOR;
 	*animo_gimli;
 	*animo_legolas;
*/
	en_que_dia(&dia);
	en_que_hora(&hora);
 	printf("Dime que es lo que sabes de Legolas\n" );
 	cual_pie_primero(&pie_lego);
 	que_comio_cena(&cena_lego);
 	cuantas_horas_suenio(&horas_suenio_lego);
	printf("Cuentame los secretos de Gimli\n" );	
	cual_pie_primero(&pie_gim);
 	que_comio_cena(&cena_gim);
 	cuantas_horas_suenio(&horas_suenio_gim);
	viento_segun_dia(dia, viento);
	humedad_segun_hora(hora, humedad);	
	sumador_animo_segun_cena(cena_lego, &animo_parcial_legolas);
	sumador_animo_segun_cena(cena_gim, &animo_parcial_gimli);
	sumador_animo_segun_pie(pie_lego, &animo_parcial_legolas);
	sumador_animo_segun_pie(pie_gim, &animo_parcial_gimli);
	sumador_animo_segun_suenio(horas_suenio_lego, &animo_parcial_legolas);
	sumador_animo_segun_suenio(horas_suenio_gim, &animo_parcial_gimli);
	animo_final(animo_parcial_gimli, &(*animo_gimli));
	animo_final(animo_parcial_legolas, &(*animo_legolas));
	printf("Resumen: %i %i %c %c. \n", *viento, *humedad, *animo_legolas, *animo_gimli);
}
