#include <stdio.h>
#include <string.h>
#include "malloc.h"
#include "sqlite3.h"
#define MAX_PERSONAS 100
#define MAX 100
enum contacto{
    Favorito,
    Conocido,
    Trabajo
};

typedef struct Persona {
    char nombre[MAX_PERSONAS];
    char apellidos[MAX_PERSONAS];
    char numero[MAX_PERSONAS];
    short int edad;
    enum contacto c;
} tPersona;

typedef struct Agenda {
    tPersona *personas;
    int num_personas;
} tAgenda;


int menu();


int main(){
    menu();
}

void inicializar_agenda(tAgenda *agenda, int num_personas) {
    agenda->personas = (tPersona*) malloc(num_personas * sizeof(tPersona));
    agenda -> num_personas = 0;
}



void listar_personas(tAgenda *agenda){
    printf("Este es el actual listado de personas\n\n");

    for (int i = 0; i < agenda -> num_personas; ++i) {
        printf("%s,%s,%s,%i,%d",agenda ->personas[i].nombre,agenda ->personas[i].apellidos,agenda ->personas[i].numero,agenda ->personas[i].edad);

        switch (agenda->personas[i].c) {
            case Favorito:
                printf(" FAVORITO\n");
                break;
            case Conocido:
                printf("CONOCIDO\n");
                break;
            case Trabajo:
                printf("TRABAJO\n");
                break;
            default:
                printf("\n");
                break;
        }

    }
}



void nueva_persona(tAgenda *agenda){
    tPersona nuevaper;
    //  agenda -> personas = (tPersona *)realloc(agenda->personas,agenda ->num_personas *sizeof(tPersona));
    printf("Dame los datos de la nueva persona\n");
    printf("\nNombre: \n");
    scanf("%s", nuevaper.nombre);
    printf("\nApellidos: \n");
    fflush(stdin);
    fgets(nuevaper.apellidos, sizeof(nuevaper.apellidos), stdin);
    nuevaper.apellidos[strcspn(nuevaper.apellidos, "\n")] = '\0';
    printf("\nNumero de telefono: \n");
    scanf("%s", nuevaper.numero);
    printf("\nEdad: \n");
    scanf("%i",&nuevaper.edad);
    printf("\nTipo de contacto (0-FAVORITO, 1-CONOCIDO, 2-TRABAJO): \n");
    scanf("%i", &nuevaper.c);

    agenda -> personas[agenda ->num_personas] = nuevaper;
    agenda ->num_personas++;
}


void borrar_persona(tAgenda *agenda){
    int num_persona;

    printf("Dame el numero de la persona a borrar en la lista(0-MAX)\n");
    scanf("%i",&num_persona);

    if (num_persona >= 0 && num_persona <= agenda->num_personas){
        tPersona *persona_borrar = &agenda->personas[num_persona];
        printf("\nUsted desea borrar %d,%s,%s,%s,%d,", num_persona, persona_borrar->nombre,
               persona_borrar->apellidos, persona_borrar->numero, persona_borrar->edad);
        switch (persona_borrar->c) {
            case Favorito:
                printf("FAVORITO\n");
                break;
            case Conocido:
                printf("CONOCIDO\n");
                break;
            case Trabajo:
                printf("TRABAJO\n");
                break;
            default:
                break;
        }


        printf("\n¿Seguro? S/N: ");
        char respuesta[2];
        scanf("%s", respuesta);

        if (respuesta[0] == 'S' || respuesta[0] == 's') {
            for (int i = num_persona; i < agenda->num_personas; ++i) {
                agenda->personas[i] = agenda->personas[i + 1];
            }
            agenda-> num_personas--;
            printf("Persona borrada :)\n");

        }
    }else{
        printf("El nuemero de persona que has introducido no existe");
    }
}


void guardar_agenda(tAgenda *agenda){

    char nombre_fichero[MAX];
    printf("Dame el nombre del fichero donde quieras guardar el listado de personas\n");
    scanf("%s",&nombre_fichero);


    FILE *f = fopen(nombre_fichero,"r");
    if (f == NULL){
        perror("Error de apertura: ");
    }

    fprintf(nombre_fichero, "Listado de personas:\n");
    for (int i = 0; i < agenda->num_personas; i++) {
        tPersona *persona = &(agenda->personas[i]);
        fprintf(nombre_fichero, "%d,%s,%s,%s,%d,", i, persona->nombre, persona->apellidos, persona->numero, persona->edad);
        switch (persona->c) {
            case Favorito:
                fprintf(nombre_fichero, "FAVORITO\n");
                break;
            case Conocido:
                fprintf(nombre_fichero, "CONOCIDO\n");
                break;
            case Trabajo:
                fprintf(nombre_fichero, "TRABAJO\n");
                break;
            default:
                fprintf(nombre_fichero, "\n");
                break;
        }
    }

    fclose(nombre_fichero);
    printf("Agenda guardada correctamente en el fichero %s\n", nombre_fichero);

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
    tAgenda agenda;
    printf("\nElige una opcion: \n");
    scanf("%i",&opcion);

    inicializar_agenda(&agenda,20);
    char nombre_fichero[MAX];
    while (opcion != 0) {
        switch (opcion) {
            case 1:
                printf("Listado de personas.\n");
                listar_personas(&agenda);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;

            case 2:
                printf("Nueva persona.\n");
                nueva_persona(&agenda);
                printf("\nElige una opcion: ");
                scanf("%i",&opcion);
                break;

            case 3:
                printf("Borrar persona.\n");
                borrar_persona(&agenda);
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