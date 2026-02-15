#include <stdio.h>
//CONSTANTES
#define MAX_PROVEEDORES 3
#define MAX_PRODUCTOS 5
// VARIABLES GLOBALES
int contProductos=0;
int posEncontrada=-1;
int auxCodigo;
int auxPrecio;
int auxTamano;
int auxCantidad;
int auxProveedor;

// ESTRUCTURAS
struct Producto
{
    //Plantilla de datos para cada producto a ingresar
    int id;                 //codigo del producto
    char name[20];          //nombre
    float tamano;           //cantidad del producto
    int stock;              //unidades
    float precio;
    //int ubicacion;
    char fechaIngrego[8];   //Fecha de ingreso del producto
    char nombreProveedor[50];
    int activo;
};

struct Proveedor //contigo no sé qué hacer aún, pero lo dejo por si acaso
{
    int rif;
    char nombre[50];
    char codigo[3];
};

struct Proveedor proveedores[MAX_PROVEEDORES] = { 
    {123456789, "Distribuidora 1", "DA"},
    {987654321, "Distribuidora 2", "BP"},
    {123459876, "Distribuidora 3", "PC"}
};

struct Producto productos[MAX_PRODUCTOS]; //donde se guarda la info

//FUNCIONES
int menu();
void noHallado();// no entiendo por qué si te escribo aquí sirves, pero estando allí arranca sim problemas
int codigo();
void nombre();
int tamano();
int stock();
float precio();
void fechaIngreso();
void nombreProveedor();


int menu()// función menú, muestra las opciones disponibles y valida la entrada del usuario
{
    int option;//guarda la opción ingresada por el usuario

    do
    {
        printf("\nALMACEN CAFE\n");
        printf("[ 1 ] Ingresar\n");
        printf("[ 2 ] Mostrar\n");
        printf("[ 3 ] Eliminar\n");
        printf("[ 4 ] Retirar\n");
        printf("[ 5 ] Consultar\n");
        printf("[ 6 ] Salir\n");
        scanf("%d", &option);

        if (option < 1 || option > 6)//valida que la opción ingresada esté dentro del rango permitido
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
    }while (option < 1 || option > 6);//si la opción es inválida, se repetirá el menú hasta que se ingrese una opción válida
    
    return option;//devuelve la opción seleccionada por el usuario para que pueda ser utilizada en el programa principal
}

int codigo()
{
    printf("ID: ");
        scanf("%d", &auxCodigo); //<- guarda el valor ingresado en la variable auxiliar para asignarlo  al campo id de la estructura Producto
    //validación del código
        while(auxCodigo<0)
         {
            printf("Codigo incorrecto, ingrese el codigo: ");
            scanf("%d", &auxCodigo);	
         }
        productos[contProductos].id = auxCodigo;
        return auxCodigo;
}

void nombre()
{
    printf("Nombre: ");
        scanf(" %s", productos[contProductos].name); //<- guarda el valor ingresado en la variable name dentro de la estructura Producto
}

int tamano()
{
    printf("Tamano: g");
        scanf("%f", &auxTamano); //<- guarda el valor ingresado en la variable tamaño dentro de la estructura Producto
    //validación del tamaño
        while(auxTamano<0)
         {
            printf("Tamano incorrecto, ingrese el tamano: ");
            scanf("%f", &auxTamano);	
         }
        productos[contProductos].tamano = auxTamano;
        return auxTamano;
}

int stock()
{
    printf("Stock: ");
    scanf("%d", &auxCantidad); //<- guarda el valor ingresado en la variable stock dentro de la estructura Producto
    //validación del stock
    while(auxCantidad<0)
        {
        printf("Stock incorrecto, ingrese el stock: ");
        scanf("%d", &auxCantidad);	
        }
    productos[contProductos].stock = auxCantidad;
    return auxCantidad;
}

float precio()
{
    printf("Precio: $");
    scanf("%f", &auxPrecio); //<- guarda el valor ingresado en la variable precio dentro de la estructura Producto
    //validación del precio
    while(auxPrecio<0)
        {
        printf("Precio incorrecto, ingrese el precio: ");
        scanf("%f", &auxPrecio);	
        }
    productos[contProductos].precio = auxPrecio;
    return auxPrecio;
}

void fechaIngreso()
{
    printf("Fecha de Ingreso (DD/MM/AA): ");
    scanf(" %s", productos[contProductos].fechaIngrego); //<- guarda el valor ingresado en la variable fecha de Ingreso dentro de la estructura Producto
}

void nombreProveedor()
{
    int p;
    printf("Nombre del proveedor: ");
    
    for (p = 0; p < MAX_PROVEEDORES; p++)
    {
        printf("%d) %s\n", p+1, proveedores[p].nombre);
    }
        printf("Seleccion: ");

    scanf("%d", &auxProveedor); //<- guarda el valor ingresado en la variable nombreProveedor dentro de la estructura Producto
    
    while(auxProveedor<0 || auxProveedor>=MAX_PROVEEDORES)
    {
        printf("Opcion invalida, ingrese el nombre del proveedor: ");
        scanf("%d", &auxProveedor);	
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

        printf("Disponible (1 si) (0 no): ");
        scanf("%d", &productos[contProductos].activo); //<- guarda el valor ingresado en la variable activo dentro de la estructura Producto
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

    printf("==================== INVENTARIO ACTUAL ====================\n");
    printf("%-5s %-15s %-10s %-10s %-8s\n", "ID", "NOMBRE", "PRECIO", "STOCK", "ESTADO"); //<- encabezado de la tabla que se muestra al usuario, con formato para alinear ID, Nombre, Precio, Stock y Estado
    printf("-----------------------------------------------------------\n");
    for (i = 0; i < MAX_PRODUCTOS; i++) //ciclo for para recorrer el arreglo de productos y mostrar la información de cada producto registrado en el inventario
    {
        printf("%-5d %-15s %-10.2f %-10d %-8s\n", 
                productos[i].id, 
                productos[i].name, productos[i].precio, 
                productos[i].stock, 
                (productos[i].activo == 1) ? "Disponible" : "no disponible" //<- muestra "Disponible" si el valor de activo es 1 y "no disponible" si el valor de activo es 0, utilizando un operador ternario para determinar qué texto mostrar en función del estado del producto
              );
    }
    printf("===========================================================\n");
}

int consultar() //función para consultar los detalles de un producto específico mostrando toda la info
{
    int buscarID;
    int k;

    printf("ID del producto a consultar: ");
    scanf("%d", &buscarID);

    noHallado();
     
    for (k = 0; k < contProductos; k++) //ciclo for para recorrer el arreglo de productos y buscar el producto con el ID ingresado por el usuario
    {
        if (productos[k].id == buscarID)// condición para verificar si el ID del producto en la posición k del arreglo productos coincide con el ID ingresado por el usuario, si se encuentra una coincidencia, se muestra la información detallada del producto
        {
            printf("\n--- DETALLES DEL PRODUCTO ---\n");
            printf("ID:        %d\n", productos[k].id);
            printf("Nombre:    %s\n", productos[k].name);
            printf("Tamano:    %.2f g\n", productos[k].tamano);
            printf("Stock:     %d unidades\n", productos[k].stock);
            printf("Precio:    $%.2f\n", productos[k].precio);
            printf("Fecha Ing: %s\n", productos[k].fechaIngrego);
            printf("Proveedor: %s\n", productos[k].nombreProveedor);
            printf("Estado:    %s\n", (productos[k].activo == 1) ? "Activo" : "Inactivo");
            printf("-----------------------------\n");
            break;
        }
    }
    return buscarID;
}

void noHallado()
{
    if (contProductos == 0)
    {
        printf("\nEl inventario esta vacio.\n");
        return;
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
            consultar();
            break;
        }
    } while (option != 6);
    
    return 0;
}