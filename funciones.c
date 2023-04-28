//
// Created by a.calvo.2022 on 28/04/2023.
//

#include "funciones.h"
#include <stdio.h>
#include <string.h>
#define COMANDO_INSERT "INSERT INTO agenda(id,nombre,apes,telefono,edad,tipo_contacto) VALUES (%i,'%s','%s','%s',%i,'%s');"
#define MAX 1000

void insertar_datos(){

    char sql[MAX];
    int x;
    char nombre[MAX];
    char apes[MAX];
    char telf[MAX];
    int edad;
    char tipoContacto[MAX];


    printf("Dame los datos de la nueva persona\n");
    printf("\nId: \n");
    scanf("%i",x);
    printf("\nNombre: \n");
    scanf("%s",nombre);
    printf("\nApellidos: \n");
    fflush(stdin);
    fgets(apes, sizeof(apes), stdin);
    apes[strcspn(apes, "\n")] = '\0';
    printf("\nNumero de telefono: \n");
    scanf("%s",telf);
    printf("\nEdad: \n");
    scanf("%i",edad);
    printf("\nTipo de contacto (0-FAVORITO, 1-CONOCIDO, 2-TRABAJO): \n");
    scanf("%i", &tipoContacto);


    sprintf(sql,COMANDO_INSERT,x,nombre,apes,telf,edad,tipoContacto);
}