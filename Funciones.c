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
/** \brief Funcion que guarda en un archivo binario la cantidad de peliculas ingresadas al sistema
 *
 * \param length int, guarda la cantidad de peliculas
 * \return void
 *
 */
void GuardarCantidad(int length)
{
    FILE *f;
	f = fopen("Datos.bin", "wb");
	if(f == NULL)
	{
		printf("No se pudo abrir el fichero");
		exit(1);
	}
	fwrite(&length, sizeof(int), 1, f);
	fclose(f);
}
/** \brief Funcion que lee el archivo binario de peliculas y las coloca en la memoria dinamica para que la informacion sea utilizada
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return void
 *
 */
void LeerBinario(epelicula *lista, int length)
{
	FILE *f;
	f = fopen("ListaPeliculas.bin", "rb");
	if(f == NULL)
	{
		printf("No se pudo abrir el fichero");
		exit(1);
	}
	fread(lista, sizeof(epelicula), length, f);
	fclose(f);
}
/** \brief Funcion que lee el archivo binario que contiene la cantidad de peliculas
 *
 * \return int, retorna la cantidad de peliculas
 *
 */
int LeerCantidad()
{
	int cant = 0;
    FILE *f;
	f = fopen("Datos.bin", "rb");
	fread(&cant, sizeof(epelicula), 1, f);
	fclose(f);
	return cant;
}
/** \brief Funcion para ingresar pelicula, pide datos al usuario para cargar la pelicula y los guarda en una estructura
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return no retorna variables
 *
 */
void IngresarPelicula(epelicula *pelicula,int length)
{
    int i;
    printf("\nIngrese Titulo: ");
				fflush(stdin);
				gets((pelicula +length)->titulo);
				for(i=0;i<length;i++)
                {
                    while(strcmp((pelicula+length)->titulo,(pelicula+i)->titulo)==0)
                    {
                        printf("Titulo ya utilizado, reingresar: ");
                        fflush(stdin);
                        gets((pelicula +length)->titulo);
                    }
                }

			    printf("\nIngrese Genero: ");
				fflush(stdin);
				gets((pelicula +length)->genero);

				printf("\nIngrese Duracion: ");
				scanf("%d",&(pelicula + length)->duracion);

				printf("\nIngrese Descripcion: ");
				fflush(stdin);
				gets((pelicula +length)->descripcion);

			    printf("\nIngrese Puntaje: ");
				scanf("%f",&(pelicula + length)->puntaje);

				printf("\nIngrese Direccion de la imagen: ");
				fflush(stdin);
				gets((pelicula +length)->imagen);

}
    /** \brief funcion auxiliar que utilice para verificar la correcta carga de peliculas en el archivo binario
     *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
     * \return void
     *
     */
    void mostrarPelicula(epelicula *pelicula, int length)
{
    int i;
    for(i=0;i<length;i++)
    {
    printf("\nTitulo: %s\n", (pelicula+i)->titulo);
	printf("genero: %s\n", (pelicula+i)->genero);
    printf("duracion: %d\n", (pelicula+i)->duracion);
    printf("descripcion: %s\n", (pelicula+i)->descripcion);
    printf("puntaje: %.2f\n", (pelicula+i)->puntaje);
    printf("imagen: %s\n", (pelicula+i)->imagen);
    }
}
/** \brief Funcion que abre o genera un archivo de extension .html (pagina web) y escribe en el las sentencias necesarias para la visualizacion correcta de la pagina web junto con los datos de las peliculas ingresadas
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return void
 *
 */
void GenerarWeb(epelicula *pelicula,int length)
{
    FILE* f;
    int i;
    f=fopen("Peliculas.html","w");
    if(f==NULL)
    {
        printf("no se pudo abrir el fichero");
        system("pause");
        exit(1);
    }
    for(i=0;i<length;i++)
    {
        fprintf(f,"<article class='col-md-4 article-intro'>");
        fprintf(f,"<a href='#'>");
        fprintf(f,"<img class='img-responsive img-rounded' src=");
        fprintf(f,(pelicula+i)->imagen);
        fprintf(f," alt=''>");
        fprintf(f,"</a>");
        fprintf(f,"<h3>");
        fprintf(f,"<a href='http://www.imdb.com'>");
        fprintf(f,(pelicula+i)->titulo);
        fprintf(f,"</a>");
        fprintf(f,"</h3>");
        fprintf(f,"<ul>");
        fprintf(f,"<li>");
        fprintf(f,(pelicula+i)->genero);
        fprintf(f,"</li>");
        fprintf(f,"<li>");
        fprintf(f,"%d",(pelicula+i)->duracion);
        fprintf(f,"</li>");
        fprintf(f,"<li>");
        fprintf(f,"%.2f",(pelicula+i)->puntaje);
        fprintf(f,"</li>");
        fprintf(f,"</ul>");
        fprintf(f,"<p>");
        fprintf(f,(pelicula+i)->descripcion);
        fprintf(f,"</p>");
        fprintf(f,"</article>");
    }
    fclose(f);
}
/** \brief Funcion que recibe el archivo binario, pide al usuario que ingrese el titulo de una pelicula y recorre el archivo buscando dicho titulo, cuando lo encuentra(si es que lo encuentra) muestra al usuario un submenu preguntando que quiere modificar el usuario
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return void
 *
 */
void ModificarCartelera(epelicula *pelicula,int length)
{
    int i,opcion;
    int flag=0;
    pelicula=pelicula;
    char tituloaux[20];
    fflush(stdin);
    printf("Ingresar el titulo de la pelicula a modificar: ");
    gets(tituloaux);
    length=LeerCantidad();
    LeerBinario(pelicula,length);
    for(i=0;i<length;i++)
    {
        if((strcmp((pelicula+i)->titulo,tituloaux))==0)
        {
            do
            {
                system("cls");
                printf("\n¿Que desea modificar?");
                printf("\n\n1-Titulo\n");
                printf("2-Genero\n");
                printf("3-Duracion\n");
                printf("4-Descripcion\n");
                printf("5-Puntaje\n");
                printf("6-Imagen\n");
                printf("7-Salir\n");

                printf("\nIngrese opcion: ");
                scanf("%d", &opcion);
                switch (opcion)
                {
                case 1:
                    {
                    printf("\nIngrese nuevo Titulo: ");
                    fflush(stdin);
                    gets((pelicula+i)->titulo);
                    break;
                    }
                case 2:
                    {
                    printf("\nIngrese nuevo Genero: ");
                    fflush(stdin);
                    gets((pelicula+i)->genero);
                    break;
                    }
                case 3:
                    {
                    printf("\nIngrese nueva Duracion: ");
                    scanf("%d",&(pelicula+i)->duracion);
                    break;
                    }
                case 4:
                    {
                    printf("\nIngrese nueva Descripcion: ");
                    fflush(stdin);
                    gets((pelicula+i)->descripcion);
                    break;
                    }
                case 5:
                    {
                    printf("\nIngrese nuevo Puntaje: ");
                    scanf("%f",&(pelicula+i)->puntaje);
                    break;
                    }
                case 6:
                    {
                    printf("\nIngrese nueva Direccion de la imagen: ");
                    fflush(stdin);
                    gets((pelicula+i)->imagen);
                    break;
                    }
                default:
                    {
                        break;
                    }
                }
            }while(opcion!=7);
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("No hay peliculas con el titulo ingresado\n");
        system("pause");
    }
}
/** \brief Funcion que abre el archivo de peliculas, pide al usuario el titulo de la pelicula que se quiere eliminar, recorre el archivo de peliculas y de encontrar el titulo ingresado, elimina la pelicula.
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return int
 *
 */
int BorrarCartelera(epelicula *pelicula,int length)
{
    int i,j;
    int flag=0;
 //   pelicula=(int)pelicula;
    char tituloaux[20];
    fflush(stdin);
    printf("Ingresar el titulo de la pelicula a eliminar: ");
    gets(tituloaux);
    length=LeerCantidad();
    LeerBinario(pelicula,length);
    for(i=0;i<length;i++)
    {
        if((strcmp((pelicula+i)->titulo,tituloaux))==0)
        {
            for(j=i;j<length;j++)
            {
                *(pelicula+j)=*(pelicula+j+1);
            }
            flag=1;
            break;
        }
    }
    if(flag==0)
    {
        printf("No hay peliculas con el titulo ingresado\n");
        system("pause");
    }
    return flag;
}


/** \brief Funcion que guarda la estructura tipo epelicula en un archivo binario
 *
 * \param *pelicula, es un puntero a una estructura de tipo epelicula.
 * \param length, variable tipo entero que tiene cargado el numero de peliculas.
 * \return void
 *
 */
void GuardarBinario(epelicula *lista, int length)
{
	FILE *f;
	f = fopen("ListaPeliculas.bin", "wb");
	if(f == NULL)
	{
		printf("No se pudo abrir el fichero");
		exit(1);
	}
	fwrite(lista, sizeof(epelicula), length, f);
	GuardarCantidad(length);
	fclose(f);
}

/** \brief Funcion que muestra un menu de opciones al usuario
 *
 * \return int, retorna un valor entero con la opcion elegida por el usuario
 *
 */
int menu()
{
	int opcion;
	system("cls");
	printf("\nMenu de opciones");
	printf("\n\n1-Alta Pelicula\n");
	printf("2-Borrar Peliculas\n");
	printf("3-Modificar Peliculas\n");
	printf("4-Generar pagina web\n");
	printf("5-Salir\n");

	printf("\nIngrese opcion: ");
	scanf("%d", &opcion);
	return opcion;
}
