#include <stdio.h>

//CONSTANTES
#define MAX_PROVEEDORES 3
#define MAX_PRODUCTOS 10


// VARIABLES GLOBALES
int contProductos=0;
int posEncontrada=-1;
int auxCodigo;
float auxPrecio;
int auxTamano;
int auxCantidad;
int auxProveedor;
int auxActivo;
int encontrado=0;
int eliminarID;


// ESTRUCTURAS
struct Producto
{
    //Plantilla de datos para cada producto a ingresar
    int id;
    char name[20];
    float tamano;
    int stock;
    float precio;
    //int ubicacion;
    int dia;
    int mes;
    int anio;
    char nombreProveedor[50];
    int activo;
};

struct Proveedor 
{
    int rif;
    char nombre[50];
    char codigo[4];
};

struct Proveedor proveedores[MAX_PROVEEDORES] = { 
    {123456789, "Distribuidora 1", "ABC"},
    {987654321, "Distribuidora 2", "XYZ"},
    {123459876, "Distribuidora 3", "DEF"}
};

struct Producto productos[MAX_PRODUCTOS]; //donde se guarda la info


//FUNCIONES
void almacen();
int menu();
void noHallado();
void registrarProducto();
int buscarCodigo();
int codigo();
void nombre();
int tamano();
int stock();
float precio();
void fechaIngreso();
void nombreProveedor();
int activo();
void eliminar();
void mostrarProducto();
int consultar();
void retirar();

//CODIGO PRINCIPAL
int main()
{
    almacen();
    return 0;
}

//DESARROLLO DE FUNCIONES

int menu()
{
    int option;//guarda la opción ingresada por el usuario

    do
    {
        printf("===========================================================\n");
        printf("\t\t\tALMACEN CAFE\n");
        printf("===========================================================\n");
        printf("[ 1 ] Ingresar\n");
        printf("[ 2 ] Mostrar\n");
        printf("[ 3 ] Eliminar\n");
        printf("[ 4 ] Retirar\n");
        printf("[ 5 ] Consultar\n");
        printf("[ 6 ] Salir\n");
        printf("===========================================================\n");
        scanf("%d", &option);

        if (option < 1 || option > 6)//valida que la opción ingresada esté dentro del rango permitido
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
    }while (option < 1 || option > 6);
    return option;
}

int codigo()
{
    int repetido;
    
    
        printf("===========================================================\n");
        printf("ID: ");
        scanf("%d", &auxCodigo); //<- variable auxiliar para validar
    do
    {
        repetido=0;
        //validación del código
        while(auxCodigo<0)
            {
            printf("Codigo incorrecto, ingrese el codigo: ");
            scanf("%d", &auxCodigo);	
            }
        //fin validación

        buscarCodigo();

        if(posEncontrada!=-1)
        {
            printf("El ID ya existe, ingrese otro ID: ");
            scanf("%d", &auxCodigo);
            repetido=1;
        }
    } while (repetido==1);

    productos[contProductos].id = auxCodigo;
    return auxCodigo;
}

int buscarCodigo()
{
    int c;
    posEncontrada = -1;
    for ( c = 0; c < contProductos; c++)
    {
        if (productos[c].id == auxCodigo)
        {
            posEncontrada = c;
            break;
        }
    }
    return posEncontrada;
}

void nombre()
{
    printf("Producto: ");
    scanf(" %s", productos[contProductos].name); //<- guarda lo ingresado en la variable name dentro de la estructura Producto
}

int tamano()
{
    printf("Tamano: g");
    scanf("%i", &auxTamano);

    //validación del tamaño
    while(auxTamano<0)
        {
        printf("Tamano incorrecto, ingrese el tamano: ");
        scanf("%i", &auxTamano);	
        }
    //fin validación

    productos[contProductos].tamano = auxTamano;
    return auxTamano;
}

int stock()
{
    printf("Stock: ");
    scanf("%d", &auxCantidad);

    //validación del stock
    while(auxCantidad<1)
    {
    printf("Stock incorrecto, ingrese el stock: ");
    scanf("%d", &auxCantidad);	
    }
    //fin validación

    productos[contProductos].stock = auxCantidad;
    return auxCantidad;
}

float precio()
{
    printf("Precio: $");
    scanf("%f", &auxPrecio);

    //validación del precio
    while(auxPrecio<1)
    {
    printf("Precio invalido, ingrese el precio: ");
    scanf("%f", &auxPrecio);	
    }
    //fin validación
    
    productos[contProductos].precio=auxPrecio;
    return auxPrecio;
}

void fechaIngreso()
{
    printf("Fecha de Ingreso (DD/MM/AA): ");
    scanf("%d/%d/%d", &productos[contProductos].dia, &productos[contProductos].mes, &productos[contProductos].anio);
    while (productos[contProductos].dia < 1 || productos[contProductos].dia>31)
    {
        printf("Dia invalido, ingrese el dia: ");
        scanf("%d", &productos[contProductos].dia);
    }
    while (productos[contProductos].mes < 1 || productos[contProductos].mes>12)
    {
        printf("Mes invalido, ingrese el mes: ");
        scanf("%d", &productos[contProductos].mes);
    }
    while (productos[contProductos].anio < 1)
    {
        printf("Anio invalido, ingrese el anio: ");
        scanf("%d", &productos[contProductos].anio);
    }
}

void nombreProveedor()
{
    int p;
    int confirmacion;
    encontrado=0; //al ser una variable global, aqui la reseteamos antes que nada

    do
    {
        printf("RIF del proveedor: \n");
        scanf("%d", &auxProveedor);

        for (p = 0; p < MAX_PROVEEDORES; p++)
        {
            if (proveedores[p].rif == auxProveedor)
            {
                printf("\n--- INFORMACION DEL PROVEEDOR ---\n");
                printf("RIF: %d\n", proveedores[p].rif);
                printf("Nombre: %s\n", proveedores[p].nombre);
                printf("Codigo: %s\n", proveedores[p].codigo);
                printf("----------------------------------\n");

                printf("¿Desea seleccionar este proveedor? (1: Si, 0: No): ");
                scanf("%d", &confirmacion);

                while(confirmacion<0 || confirmacion>1)
                {
                    printf("Opcion invalida, ingrese 1 para seleccionar o 0 para no seleccionar: ");
                    scanf("%d", &confirmacion);	
                }

                if (confirmacion == 1)
                {
                    int n;
                    for ( n = 0; proveedores[p].nombre[n] != '\0'; n++)
                    {
                        productos[contProductos].nombreProveedor[n] = proveedores[p].nombre[n];//aquí se pone feo, esto hace un print LETRA POR LETRA del nombre del proveedor seleccionado y lo guarda en la información del arreglo del producto, sería más facil si usaramos la librería string.h pero como "las computadoras de la universidad no tienen esas librerías" toca así :v
                    }

                    productos[contProductos].nombreProveedor[n] = '\0'; // Agrega el carácter nulo al final de la cadena

                    encontrado=1;
                    break; // Sale del ciclo for si el usuario confirma la selección del proveedor
                }
                else
                {
                    printf("RIF no encontrado, intente de nuevo.\n");
                    encontrado=0; // Si el usuario no confirma, se reinicia la búsqueda
                }
            }
        }
        
    } while (encontrado == 0);
}

int activo()
{
    if (productos[contProductos].stock > 0)
    {
        productos[contProductos].activo = 1;
        return 1;
    }
    else
    {
        productos[contProductos].activo = 0;
        return 0;
    }
}

void registrarProducto()
{
    if (contProductos < MAX_PRODUCTOS)//no se podrán ingresar más datos si no se cumple esta condición
    {
        //PLANTILLA DEL PRODUCTO
        codigo();
        nombre();
        tamano();
        stock();
        precio();
        fechaIngreso();
        nombreProveedor();
        activo();
        contProductos++;
    }
    else
    {
        printf("\nEl inventario esta lleno.\n");
    }
}

void mostrarProducto()
{
    int i;

    noHallado(); //verificamos si el inventario está vacío antes de intentar mostrar los productos
    if (contProductos != 0)
    {
        printf("==================== INVENTARIO ACTUAL ====================\n");
        printf("%-5s %-15s %-10s %-10s %-8s\n", "ID", "NOMBRE", "PRECIO", "STOCK", "ESTADO"); //<- encabezado de la tabla que se muestra al usuario, con formato para alinear ID, Nombre, Precio, Stock y Estado
        printf("-----------------------------------------------------------\n");
        for (i = 0; i < contProductos; i++) //ciclo for para recorrer el arreglo de productos y mostrar la información de cada producto registrado en el inventario
        {
            if (productos[i].activo == 1)
            {
                printf("%-5d %-15s $%-10.2f %-10d %-8s\n", productos[i].id, productos[i].name, productos[i].precio, productos[i].stock, (productos[i].activo == 1) ? "Disponible" : "no disponible"); //<- muestra "Disponible" si el valor de activo es 1 y "no disponible" si el valor de activo es 0, utilizando un operador ternario para determinar qué texto mostrar en función del estado del producto
            }
        }
        printf("===========================================================\n");
    }
}

void eliminar()
{
    int eliminarID;
    int l;
    int activos=0; //esta es pa saber CUANTOS PRODUCTOS EXISTEN
    encontrado=0; //como dije antes, al ser una variable global, aqui la reseteamos antes que nada
    
    if (contProductos == 0)
    {
        noHallado();
        return;
    }

    printf("ID del producto a eliminar: ");
    scanf("%d", &eliminarID);

    for (l=0; l < contProductos; l++)
    {
        // Solo buscamos entre los que estan activos
        if (productos[l].activo == 1)
        {
            activos++;

            if (productos[l].id == eliminarID)
            {
                productos[l].activo = 0; //marcamos el producto como inactivo en lugar de eliminarlo físicamente del arreglo, esto permite mantener la integridad del arreglo y evitar problemas con los índices de los productos restantes
                printf("Producto con ID %d ha sido eliminado (marcado como inactivo).\n", eliminarID);
                encontrado=1;
                break; // Salimos del ciclo una vez que encontramos y marcamos el producto como inactivo
            }
        }
    }

    if (activos == 0)
    {
        noHallado();
    }
    else if (encontrado == 0)
    {
        printf("No se encontro el ID o ya fue eliminado.\n");
    }
}

void retirar() 
{
    printf("Codigo de producto a retirar: ");
    scanf("%d", &auxCodigo);
    //reutilizamos la función para encontrar el producto por su código
    buscarCodigo();
    if (posEncontrada == -1)
    {
        printf("Producto no encontrado o ya eliminado.\n");
    }
    else
    {
        printf("Cantidad a retirar: ");
        scanf("%d", &auxCantidad);
        if (auxCantidad > productos[posEncontrada].stock)
        {
            printf("No hay suficiente stock para retirar esa cantidad.\n");
        }
        else
        {
            productos[posEncontrada].stock -= auxCantidad;
            printf(">> Retiraste %d unidades del producto '%s'. Stock restante: %d\n", auxCantidad, productos[posEncontrada].name, productos[posEncontrada].stock);
            if (productos[posEncontrada].stock == 0)
            {
                productos[posEncontrada].activo = 0; // Si el stock llega a 0, marcamos el producto como inactivo
                printf(">> El producto '%s' ahora esta agotado y marcado como inactivo.\n", productos[posEncontrada].name);
            }
        }
    }
}

int consultar() 
{
    int buscarID;
    int k;


    if (contProductos != 0)
    {
        printf("ID del producto a consultar: ");
        scanf("%d", &buscarID);

        for (k = 0; k < contProductos; k++) //ciclo for para recorrer el arreglo de productos y buscar el producto con el ID ingresado por el usuario
        {
            if (productos[k].id == buscarID)// condición para verificar si el ID del producto en la posición k del arreglo productos coincide con el ID ingresado por el usuario, si se encuentra una coincidencia, se muestra la información detallada del producto
            {
                printf("\n------------------ DETALLES DEL PRODUCTO ------------------\n");
                printf("\t\tID:                 %d\n", productos[k].id);
                printf("\t\tNombre:             %s\n", productos[k].name);
                printf("\t\tTamano:             %.2f gramos\n", productos[k].tamano);
                printf("\t\tStock:              %d unidades\n", productos[k].stock);
                printf("\t\tPrecio:             $%.2f\n", productos[k].precio);
                printf("\t\tFecha de ingreso:   %02d/%02d/%04d\n", productos[k].dia, productos[k].mes, productos[k].anio);
                printf("\t\tProveedor:          %s\n", productos[k].nombreProveedor);
                printf("\t\tEstado:             %s\n", (productos[k].activo == 1) ? "Activo" : "Inactivo");
                printf("--------------------------------------------------------------\n");
                break;
            }
        }
    }
    else
    {
        noHallado();
    }
    return buscarID;
}

void noHallado()
{
    if (contProductos == 0)
    {
        printf("===========================================================\n");
        printf("\nEl inventario esta vacio.\n\n");
        return;
    }
}

void almacen()
{
    int option;
    do
    {
        option = menu();
        switch (option)
        {
        case 1:
            registrarProducto();
            break;
        case 2:
            mostrarProducto();
            break;
        case 3:
            eliminar();
            break;
        case 4:
            retirar();
            break;
        case 5:
            consultar();
            break;
        }
    } while (option != 6);
}