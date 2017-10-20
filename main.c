#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include"Prototipos.h"
int main()
{
    int cant,auxborrar;
    epelicula* cartelera;
    cant=LeerCantidad();
    cartelera = (epelicula*)malloc((cant +1) * sizeof(epelicula));
    if(cartelera == NULL)
    {
        printf("\nNo se pudo asignar memoria");
        exit(1);
    }
	if(cant ==0)
	{
		printf("\nNo hay Peliculas en el sistema\n\n");
		system("pause");
	}
	else
	{
		LeerBinario(cartelera, cant);
		printf("\nFichero cargado con exito\n\n");
        system("pause");
	}
    int opc;
    do
    {
        switch(menu())
		{
			case 1:
				cartelera = (epelicula*)realloc(cartelera, (cant +1) * sizeof(epelicula));
				if(cartelera == NULL)
				{
					printf("\nNo se pudo asignar memoria");
					exit(1);
				}
                IngresarPelicula(cartelera,cant);
                cant++;
				break;
			case 2:
				auxborrar=BorrarCartelera(cartelera, cant);
				if(!auxborrar)
                {
                    GuardarBinario(cartelera, (cant-1));
                    printf("Pelicula eliminada con exito\n\n");
                    printf("\nFichero guardado con exito\n");
                    system("pause");
                    exit(1);
                }
				break;
			case 3:
				ModificarCartelera(cartelera, cant);
				break;
			case 4:
				GenerarWeb(cartelera, cant);
				break;
            case 5:
                GuardarBinario(cartelera, cant);
                opc=5;
                break;
            default:
                printf("Valor invalido");
                break;
		}
    }while(opc!=5);
 //   mostrarPelicula(cartelera,cant);
    printf("\nFichero guardado con exito\n");
    system("pause");
	return 0;
}
