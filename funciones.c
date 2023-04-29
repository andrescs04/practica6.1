//
// Created by a.calvo.2022 on 28/04/2023.
//

#include "funciones.h"
#include <stdio.h>
#include <string.h>
#define COMANDO_INSERT "INSERT INTO agenda(id,nombre,apes,telefono,edad,tipo_contacto) VALUES (%i,'%s','%s','%s',%i,'%s');"
#define MAX 100
#define MAX_CHAR 200
#define COMANDO_DELETE "DELETE FROM agenda WHERE id = %i;"



void declarar_variables(){
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

}
int abrir_base() {
    sqlite3* db;
    int rc = sqlite3_open("../agenda.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Error al abrir la base de datos: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }
    return db;
}
void cerrar_base(sqlite3* db){
    sqlite3_close(db);
}


static int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}



int muestraDatos(sqlite3 *db) {
    char *zErrMsg = 0;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

    int rc = sqlite3_open("../agenda.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (1);
    }
    // Creacion de consulta SQL
    strcpy(sql,"SELECT * FROM agenda");

    // Ejecucion de comando SQL: se invoca la funcion callback para cada
    // fila del resultado obtenido
    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}


int muestraDatosFila(sqlite3 *db,int x) {
    char *zErrMsg = 0;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

    int rc = sqlite3_open("../agenda.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return (1);
    }
    // Creacion de consulta SQL
    sprintf(sql, "SELECT * FROM agenda WHERE id = %d;",x);

    // Ejecucion de comando SQL: se invoca la funcion callback para cada
    // fila del resultado obtenido
    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
}


void insertar_datos(){

    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";

    int x;
    char nombre[MAX];
    char apes[MAX];
    char telf[MAX];
    int edad;
    char tipoContacto[MAX];

    rc = sqlite3_open("../agenda.db", &db);

    if (rc) {
        fprintf(stderr, "No se pudo abrir: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    printf("Dame los datos de la nueva persona\n");
    printf("\nId: \n");
    scanf("%i",&x);
    printf("\nNombre: \n");
    scanf("%s",nombre);
    printf("\nApellidos: \n");
    fflush(stdin);
    fgets(apes, sizeof(apes), stdin);
    apes[strcspn(apes, "\n")] = '\0';
    printf("\nNumero de telefono: \n");
    scanf("%s",telf);
    printf("\nEdad: \n");
    scanf("%i",&edad);
    printf("\nTipo de contacto (0-FAVORITO, 1-CONOCIDO, 2-TRABAJO): \n");
    scanf("%s", tipoContacto);


    sprintf(sql,COMANDO_INSERT,x,nombre,apes,telf,edad,tipoContacto);

    rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

    if( rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }
    sqlite3_close(db);

}


void borrar_persona(){
    int x;
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[MAX_CHAR];
    const char* data = "Callback function called";


    rc = sqlite3_open("../agenda.db", &db);

    if (rc){
        fprintf(stderr, "No se pudo abrir: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    printf("Dame el numero de la persona a borrar en la lista(0-MAX)\n");
    scanf("%i",&x);

    printf("\nUsted desea borrar a:\n");
    muestraDatosFila(db,x);

    printf("\n¿Seguro? S/N: ");
    char respuesta[2];
    scanf("%s", respuesta);

    if (respuesta[0] == 'S' || respuesta[0] == 's') {
        sprintf(sql,COMANDO_DELETE,x);
        rc = sqlite3_exec(db, sql, callback, (void*)data, &zErrMsg);

        if( rc != SQLITE_OK ) {
            fprintf(stderr, "SQL error: %s\n", zErrMsg);
            sqlite3_free(zErrMsg);
        }
        printf("Persona borrada :)\n");

    }else{
        printf("El numero de persona que has introducido no existe");
    }
}
