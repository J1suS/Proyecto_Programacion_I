#include <stdio.h>
//CONSTANTES
#define MAX_PROVEEDORES 3
#define MAX_PRODUCTOS 5

// VARIABLES GLOBALES
int contProductos=0;
int posEncontrada=-1;
int auxCodigo;
float auxPrecio;
int auxTamano;
int auxCantidad;
int auxProveedor;
int auxActivo;

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

struct Proveedor //contigo no sé qué hacer aún, pero lo dejo por si acaso
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
    printf("Nombre: ");
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
    printf("Nombre del proveedor: \n");
    
    for (p = 0; p < MAX_PROVEEDORES; p++)
    {
        printf("%d) %s\n", p+1, proveedores[p].nombre);
    }
        printf("Seleccion: ");

    scanf("%d", &auxProveedor); //<- guarda el valor ingresado en la variable nombreProveedor dentro de la estructura Producto
    
    while(auxProveedor<1 || auxProveedor>MAX_PROVEEDORES)
    {
        printf("Opcion invalida, ingrese el nombre del proveedor: ");
        scanf("%d", &auxProveedor);	
    }

    auxProveedor--;

    printf("Seleccionaste: %s\n", proveedores[auxProveedor].nombre);
    printf("RIF: %d\n", proveedores[auxProveedor].rif);
    printf("Nombre: %s\n", proveedores[auxProveedor].nombre);
    printf("Codigo: %s\n", proveedores[auxProveedor].codigo);

    productos[contProductos].nombreProveedor[15] = proveedores[auxProveedor].nombre[15]; //<- guarda el nombre del proveedor seleccionado en el campo nombreProveedor de la estructura Producto
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

void registrarProducto()//función para registrar un nuevo producto en el inventario
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
        contProductos++; //<- incrementa el contador de productos para que el siguiente producto se guarde en la siguiente posición del arreglo productos
    }
    else
    {
        printf("\nEl inventario esta lleno.\n"); //<- mensaje que se muestra si el contador de productos ha alcanzado el máximo permitido, indicando que no se pueden ingresar más productos al inventario
    }
}

void mostrarProducto()//función para mostrar info general de todos los productos registrados en el inventario
{
    int i; //variable de control para el ciclo for

    noHallado(); //<- llamada a la función noHallado para verificar si el inventario está vacío antes de intentar mostrar los productos
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

    noHallado();

    printf("ID del producto a eliminar: ");
    scanf("%d", &eliminarID);

    for (l=0; l < contProductos; l++)
    {
        // Solo buscamos entre los que estan activos
        if (productos[l].id == eliminarID && productos[l].activo == 1)
        {
            productos[l].activo = 0; // "Borrado" lógico
            printf(">> Producto '%s' marcado como inactivo (eliminado).\n", productos[l].name);
            break;
        }
        else
        {
            printf("No se encontro el ID o ya fue eliminado");
        }
    }


}

int consultar() //función para consultar los detalles de un producto específico mostrando toda la info
{
    int buscarID;
    int k;

    printf("ID del producto a consultar: ");
    scanf("%d", &buscarID);

    if (contProductos != 0)
    {
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
    }
}

//CODIGO PRINCIPAL
int main()
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
            //retirar(); //<- función para retirar productos del inventario, aún no implementada
            break;
        case 5:
            consultar();
            break;
        }
    } while (option != 6);

    return 0;
}