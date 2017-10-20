#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct
{
    char titulo[30];
    char genero[20];
    int duracion;
    char descripcion[30];
    float puntaje;
    char imagen[100];
}epelicula;

void GuardarCantidad(int);
void LeerBinario(epelicula*,int);
int LeerCantidad();
void IngresarPelicula(epelicula*,int);
void mostrarPelicula(epelicula*, int);
void GenerarWeb(epelicula*,int);
void ModificarCartelera(epelicula*,int);
int BorrarCartelera(epelicula*,int);
void GuardarBinario(epelicula*, int);
int menu();
