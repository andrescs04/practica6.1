#include <stdio.h>
#include <string.h>
#include "sqlite3.h"
#include "funciones.h"
#define MAX_CHAR 200
#define MAX 100
#define COMANDO_INSERT "INSERT INTO agenda(id,nombre,apes,telefono,edad,tipo_contacto) VALUES (%i,'%s','%s','%s',%i,'%s');"
#define COMANDO_DELETE "DELETE FROM agenda WHERE id = %i;"


int menu();

int main() {
    menu();

    /*sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

    // Apertura de la BD
    rc = sqlite3_open("../agenda.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (1);
    }

    // Muestra contenido de la BD:
    printf("\n\n--- Antes de INSERTAR ---\n");
    muestraDatos(db);

    // Inserta datos a partir de variables:
    // Datos a insertar:
    int x = 10;
    char nombre[MAX_CHAR] = "Chema";
    char apes[MAX_CHAR] = "Colmenar Verdugo";
    char telf[MAX_CHAR] = "699999999";
    int edad = 25;
    char tipoContacto[MAX_CHAR] = "FAVORITO";

    // Creacion de comando de insercion
    sprintf(sql,COMANDO_INSERT,x,nombre,apes,telf,edad,tipoContacto);

    // Insercion:
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    // Muestra datos de nuevo
    printf("\n\n--- Despues de INSERTAR ---\n");
    muestraDatos(db);

    // Borrado del nuevo elemento
    sprintf(sql,COMANDO_DELETE,x);
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }


    // Muestra datos de nuevo
    printf("\n\n--- Despues de BORRAR ---\n");
    muestraDatos(db);


    // Clausura de conexion
    sqlite3_close(db);
*/
    return 0;
}


int menu() {
    printf("----- Practica -----\n");
    printf("Bienvenido a la Agenda: \n");
    printf("1 - Listado de personas."
           "\n2 - Nueva persona."
           "\n3 - Borrar persona."
           "\n4 - Guardar agenda en fichero de texto"
           "\n5 - Leer agenda de fichero de texto"
           "\n0 - Salir.\n");
    int opcion;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

    printf("\nElige una opcion: \n");
    scanf("%i",&opcion);

    //inicializar_agenda(&agenda,20);
    char nombre_fichero[MAX];
    while (opcion != 0) {
        switch (opcion) {
            case 1:
                printf("Listado de personas.\n");
                muestraDatos(db);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;

            case 2:
                printf("Nueva persona.\n");
                insertar_datos(db);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;

            case 3:
                printf("Borrar persona.\n");
                borrar_persona();
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;
            case 4:
                scanf("%s",nombre_fichero);
                printf("Guardar agenda en fichero de texto.\n");
                //guardar_fichero(&agenda);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;
            case 5:
                printf("Leer agenda de fichero de texto.\n");
                //borrar_persona(&agenda);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;
            default:
                printf("No introduciste ningun valor correcto.\n");
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
        }
    }
    printf("\nHas terminado la practica.");
}

