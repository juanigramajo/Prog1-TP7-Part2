// Integrantes:
// Arroyo María Agustina
// Gramajo Juan Ignacio
// Yalux Santiago

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAX 20

struct fecha
{
    int dia;
    int mes;
    int ano;
} typedef fecha;

struct publicacion
{
    char titulo[30];
    char editorial[30];
    int edicion;
    fecha fec_publicacion;
    char tieneisbn;
    long int isbn;
    char categoria;
    int cantidad;
    int stock;
} typedef publi;


void cargar(publi *punt, int cant);
void mostrar(publi *punt, int cant);
void mostrarInventario(publi *punt, int cant);
void librosSinStock(publi *punt, int cant);
char editar(publi *punt, int cant);


int main() {
    
    publi inventario[MAX], *p_libro;
    int cantLibros;

    p_libro = inventario;

    printf("Ingrese la cantidad de libros a guardar: ");
    scanf("%d", &cantLibros);

    cargar(p_libro, cantLibros);

    editar(p_libro, cantLibros);

    mostrarInventario(p_libro, cantLibros);

    librosSinStock(p_libro, cantLibros);

    return 0;
}


void cargar(publi *punt, int cant) {

    puts("\n---------------CARGA DE DATOS---------------\n");
    for (int i = 0; i < cant; i++)
    {
        fflush(stdin);
        printf("---------------Libro Nº [%d]---------------\n", i+1);
        printf("Ingrese el título: ");
        gets(punt->titulo);

        printf("Ingrese la editorial: ");
        gets(punt->editorial);

        printf("Ingrese el número de edición: ");
        scanf("%d", &punt->edicion);

        printf("Ingrese la fecha de publicación (dd / mm / aaaa): ");
        scanf("%d %d %d", &punt->fec_publicacion.dia, &punt->fec_publicacion.mes, &punt->fec_publicacion.ano);
        

        while (punt->fec_publicacion.dia < 1 || punt->fec_publicacion.dia > 31) {
            printf("\nIngrese un día valido (1 - 31)\nIngrese el día correcto: ");
            scanf("%d", &punt->fec_publicacion.dia);
        }

        while (punt->fec_publicacion.mes < 1 || punt->fec_publicacion.mes > 12) {
            printf("\nIngrese un mes valido (1 - 12)\nIngrese el mes correcto: ");
            scanf("%d", &punt->fec_publicacion.mes);
        }

        while (punt->fec_publicacion.ano < 1000 || punt->fec_publicacion.ano > 2022) {
            printf("\nIngrese un año valido (1000 - 2022)\nIngrese el año correcto: ");
            scanf("%d", &punt->fec_publicacion.ano);
        }
        
        printf("\n¿Tiene ISBN?\nPresione S para indicar SI o presione N para indicar NO: ");
        scanf(" %c", &punt->tieneisbn);
        
        while (punt->tieneisbn != 'S' && punt->tieneisbn != 's' && punt->tieneisbn != 'N' && punt->tieneisbn != 'n')
        {
            printf("\n\nError de formato\nPresione S para indicar SI o N para indicar NO: ");
            scanf(" %c", &punt->tieneisbn);
        }

        if (punt->tieneisbn == 'S' || punt->tieneisbn == 's')
        {
            printf("Ingrese el ISBN: ");
            scanf("%ld", &punt->isbn);

            long int aux = punt->isbn;
            int contador = 0;

            while (aux > 0) {
                aux = aux / 10;
                contador ++;
            }

            while (contador < 10 || contador > 13) {
                printf("\nIngrese un número válido (entre 10 y 13 dígitos)\nIngrese el ISBN: ");
                scanf("%ld", &punt->isbn);

                aux = punt->isbn;
                contador = 0;

                while (aux > 0) {
                aux = aux / 10;
                contador ++;
                }
            }
        } else if (punt->tieneisbn == 'N' || punt->tieneisbn == 'n')
        {
            punt->isbn = 0;
        }
        
        printf("\nCATEGORÍAS:\nPresione L para LIBRO\nPresione R para REVISTA\nPresione T para TESIS\n\nIngrese la categoría: ");
        scanf(" %c", &punt->categoria);
        
        while (punt->categoria != 'L' && punt->categoria != 'l' && punt->categoria != 'R' && punt->categoria != 'r' && punt->categoria != 'T' && punt->categoria != 't')
        {
            printf("\nError de formato\n(Presione L para LIBRO)\n(Presione R para REVISTA)\n(Presione T para TESIS): ");
            scanf(" %c", &punt->categoria);
        }

        
        printf("Ingrese la cantidad de ejemplares: ");
        scanf("%d", &punt->cantidad);    

        while (punt->cantidad < 1) {
            printf("\nNo puede haber menos de 1 ejemplar, ingrese la cantidad de ejemplares: ");
            scanf("%d", &punt->cantidad);
        }


        printf("Ingrese la cantidad de ejemplares en stock: ");
        scanf("%d", &punt->stock);

        while (punt->stock > punt->cantidad) {
            printf("\nNo puede haber más ejemplares en stock que la cantidad declarada de ejemplares, ingrese la cantidad de ejemplares en stock: ");
            scanf("%d", &punt->stock);
        }


        punt++;
    }
    
}



void mostrar(publi *punt, int cant){
    
    printf("Título: ");
    puts(punt->titulo);

    printf("Editorial: ");
    puts(punt->editorial);

    printf("Edicion número %d \n", punt->edicion);

    printf("Publicada el %d / %d / %d \n", punt->fec_publicacion.dia, punt->fec_publicacion.mes, punt->fec_publicacion.ano);

    printf("ISBN: %ld \n", punt->isbn);

    switch (punt->categoria)
    {
    case 'l':
        printf("Categoría: Libro\n");
        break;
    case 'r':
        printf("Categoría: Revista\n");
        break;
    case 't':
        printf("Categoría: Tesis\n");
        break;
    }

    printf("Cantidad de ejemplares: %d \n", punt->cantidad);

    printf("Cantidad de ejemplares en Stock: %d \n", punt->stock);
}




void mostrarInventario(publi *punt, int cant){

    puts("\n\n---------------INVENTARIO---------------");

    for (int i = 0; i < cant; i++)
    {
        printf("\n---------------Libro Nº [%d]---------------", i+1);
        mostrar(punt, cant);
        punt++;
    }
    
}



void librosSinStock(publi *punt, int cant){

    int cantLibSinStock = 0;

    for (int i = 0; i < cant; i++)
    {
        if ((punt->categoria == 'l') && (punt->stock == 0))
        {
            cantLibSinStock++;
        }
        punt++;
    }

    printf("\nCantidad de libros sin Stock: %d \n\n", cantLibSinStock);

}



char editar(publi *punt, int cant)
{
    for (int i = 0; i < cant; i++)
    {
        int editorial1 = strcmp(punt->editorial, "FACET");
        int editorial2 = strcmp(punt->editorial, "facet");
        int editorial3 = strcmp(punt->editorial, "Facet");

        if (punt->isbn == 0 && (editorial1 == 0 || editorial2 == 0 || editorial3 == 0))
        {
            punt->categoria = 't';

        } else if (punt->isbn == 0 && (editorial1 != 0 && editorial2 != 0 && editorial3 != 0))
        {
            punt->categoria = 'r';
        }
        
        if (punt->isbn != 0)
        {
            punt->categoria = 'l';
        }

        punt->categoria = tolower(punt->categoria);
        
        punt++;
    }
    
    return(punt->categoria);
}