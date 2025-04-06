#include "client.h"


int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/

	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	/* ---------------- LOGGING ---------------- */

	logger = iniciar_logger();
	if (logger == NULL) {
    	fprintf(stderr, "No se pudo crear el logger\n");
    	return EXIT_FAILURE;
	}
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"
	log_info(logger, "hola! Soy un log");


	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	config = iniciar_config();

	// Usando el config creado previamente, leemos los valores del config y los 
	// dejamos en las variables 'ip', 'puerto' y 'valor'
	ip = config_get_string_value(config, "IP");
	puerto = config_get_string_value(config, "PUERTO");
	valor = config_get_string_value(config, "CLAVE");

	// Loggeamos el valor de config
	log_info(logger, "El valor de CLAVE es: %s", valor);
	log_info(logger, "La IP es: %s", ip);
	log_info(logger, "El puerto es: %s", puerto);


	/* ---------------- LEER DE CONSOLA ---------------- */

	log_info(logger, "iniciando lectura por consola...");
	leer_consola(logger);
	log_info(logger, "Fin del programa de lectura");

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
	log_info(logger, "Intentando conectar al servidor.");

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//Validacion de conexion
		if (conexion < 0) {
    	log_error(logger, "No se pudo conectar al servidor");
    	return EXIT_FAILURE;
	}
		log_info(logger, "Conexión establecida con éxito al servidor");

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(valor,conexion);

	// Armamos y enviamos el paquete
	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}
