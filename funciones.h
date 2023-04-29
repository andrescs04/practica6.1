//
// Created by a.calvo.2022 on 28/04/2023.
//

#ifndef EJEMPLO_SQLITE_C_FUNCIONES_H
#define EJEMPLO_SQLITE_C_FUNCIONES_H
#include "sqlite3.h"
void insertar_datos();
int muestraDatos(sqlite3 *db);
int muestraDatosFila(sqlite3 *db,int x);
static int callback(void *NotUsed, int argc, char **argv, char **azColName);
int abrir_base();
void cerrar_base();
void borrar_persona();


#endif //EJEMPLO_SQLITE_C_FUNCIONES_H
