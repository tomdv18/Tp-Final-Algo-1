#ifndef __COMANDOS_H__
#define __COMANDOS_H__

#define MAX_NOMBRE 100
#define MAX_NIVELES 4
#define MAX_RUTA 50


typedef struct rankista{
    
    int puntaje_final;
    char nombre[MAX_NOMBRE];
}rankista_t;

typedef struct resistencia_torres{
	int resistencia_torre_1;	
	int resistencia_torre_2;
}resistencia_torres_t;

typedef struct enanos_extra{
	
	int cantidad_enanos_extra;
	int coste_torre_1_enanos_extra;
}enanos_extra_t;

typedef struct elfos_extra{
	
	int cantidad_elfos_extra;
	int coste_torre_2_elfos_extra;
}elfos_extra_t;


typedef struct animos_enanos{
		
	int critico_enanos;
	int fallo_enanos;
}animos_enanos_t;

typedef struct animos_elfos{
		
	int critico_elfos;
	int fallo_elfos;
}animos_elfos_t;

typedef struct configuracion{

	resistencia_torres_t resistencia_torres;
	int enanos_inicio[MAX_NIVELES];
	int elfos_inicio[MAX_NIVELES];
	enanos_extra_t enanos_extra;
	elfos_extra_t elfos_extra;
	animos_enanos_t animos_enanos;
	animos_elfos_t animos_elfos;
	float velocidad_juego;
	char ruta_caminos[MAX_RUTA];

}configuracion_t;


void crear_configuracion(char configuracion[MAX_RUTA]);

void poneme_la_repe(char ruta[MAX_RUTA], float velocidad);

void crear_camino(char archivo_de_grabado[MAX_RUTA]);

void mostrar_ranking (int listar, char configuracion[MAX_RUTA]);















#endif /* __COMANDOS_H__ */
