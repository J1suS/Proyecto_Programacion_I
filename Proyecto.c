//--------LIBRERÍA--------
#include <stdio.h>


//--------CONSTANTES--------
#define MAX_PROVEEDORES 3
#define MAX_PRODUCTOS 10


//--------VARIABLES GLOBALES--------
int contProductos=0;
//Todas las que tengan al inicio aux son auxiliares
int auxCodigo;
float auxPrecio;
int auxTamano;
int auxCantidad;
int auxProveedor;
int auxActivo;

int encontrado=0;
int eliminarID;
int activos=0; //esta es pa saber CUANTOS PRODUCTOS EXISTEN realmente (son mostrables)


//--------ESTRUCTURAS--------
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
    int rifProveedor;
    char codigoProveedor[4];
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


//--------FUNCIONES--------
int encontrarIndice(int BuscarID);
void almacen();
int menu();
void noHallado();
void registrarProducto();
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

//--------CODIGO PRINCIPAL--------
int main()
{
    almacen();
    return 0;
}

//--------DESARROLLO DE FUNCIONES--------


/*[CENTRALIZACIÓN, EL PAPÁ DE LOS POLLITOS]
  esta belleza hace un solo for y con eso 
          se utiliza para todo*/
int encontrarIndice(int BuscarID)
{
    int i;
    for (i = 0; i < contProductos; i++)
    {
        if (productos[i].id == BuscarID && productos[i].activo == 1) // Verifica que el ID coincida y que el producto esté activo
        {
            return i; // retorna la iteración del ciclo si hay producto encontrado
        }
    }
    return -1; // retorna -1 si no encuentra un producto
}


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

    printf("====================REGISTRAR PRODUCTO=====================\n");
    printf("ID: ");
    scanf("%d", &auxCodigo); //<-auxiliar para validar

    do
    {
        repetido=0;

        //validación del código
        while(auxCodigo<0)
        {
        printf("ID invalida, intente otra vez: ");
        scanf("%d", &auxCodigo);	
        }
        //fin validación

        /*utilizamos la función encontrarIndice() para verificar 
        si el ID ingresado ya existe en el arreglo de productos,
        si la función retorna -1 significa que el ID ya 
        existe y se pide al usuario que ingrese otro ID*/
        if(encontrarIndice(auxCodigo) != -1) 
        {
            printf("El ID ya existe, ingrese otro ID: ");
            scanf("%d", &auxCodigo);
            repetido=1;
        }
    } while (repetido==1);

    productos[contProductos].id = auxCodigo ;//si no hay código repetido, se asigna a la posición del arreglo de productos correspondiente
    return auxCodigo;
}

void nombre()
{
    printf("Producto: ");
    scanf(" %s", productos[contProductos].name);
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
    int fechaValida=0;

    while (fechaValida == 0)
    {
        printf("Fecha de Ingreso (DD/MM/AAAA): ");
        scanf("%d/%d/%d", &productos[contProductos].dia, 
                          &productos[contProductos].mes, 
                          &productos[contProductos].anio);

        if (productos[contProductos].dia < 1 || productos[contProductos].dia > 31)
        {
            printf("Dia invalido (1-31)\nIngrese el dia: ");
            continue;
        }

        if (productos[contProductos].mes < 1 || productos[contProductos].mes > 12) //tiene que agregar correctamente la fecha completa, si no no sale de este ciclo
        {
            printf("Mes invalido (1-12)\nIngrese el mes: ");
            continue;
        }

        if (productos[contProductos].anio < 2000)
        {
            printf("Anio invalido (mayor o igual a 2000)\nIngrese el anio: ");
            continue;
        }
        fechaValida=1;
    }
}

void nombreProveedor()
{
    int p;
    int confirmacion;
    encontrado=0; //al ser una variable global, aqui la reseteamos antes que nada

    do
    {
        printf("RIF del proveedor: ");
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

                printf("Desea seleccionar este proveedor?\n");
                printf("1) Si\n");
                printf("0) No\n");
                printf("-->");
                scanf("%d", &confirmacion);

                //validación de la confirmación
                while(confirmacion<0 || confirmacion>1)
                {
                    printf("Opcion invalida, 1 para seleccionar o 0 para no seleccionar: ");
                    scanf("%d", &confirmacion);	
                }
                //fin validación

                if (confirmacion == 1)
                {
                    int n;
                    int c;
                    //NOMBRE DEL PROVEEDOR
                    for ( n = 0; proveedores[p].nombre[n] != '\0'; n++)
                    {
                        productos[contProductos].nombreProveedor[n] = proveedores[p].nombre[n];//aquí se pone feo, esto hace un print LETRA POR LETRA del nombre del proveedor seleccionado y lo guarda en la información del arreglo del producto, sería más facil si usaramos la librería string.h pero como "las computadoras de la universidad no tienen esas librerías" toca así :v
                    }
                    productos[contProductos].nombreProveedor[n] = '\0'; // Agrega el carácter nulo al final de la cadena
                    //FIN NOMBRE

                    //RIF DEL PROVEEDOR
                    productos[contProductos].rifProveedor = proveedores[p].rif;
                    //FIN RIF

                    //CODIGO DEL PROVEEDOR
                    for ( c = 0; proveedores[p].codigo[c] != '\0'; c++)
                    {
                        productos[contProductos].codigoProveedor[c] = proveedores[p].codigo[c];//lo mismo que el nombre pero con el código del proveedor
                    }
                    productos[contProductos].codigoProveedor[c] = '\0'; // Agrega el carácter nulo al final de la cadena
                    //FIN CODIGO

                    encontrado=1;
                }
                break; //para no seguir buscando innecesariamente
            }
        }
        if (p == MAX_PROVEEDORES)
        {
            printf("RIF no encontrado, intente de nuevo.\n");
        }
        
    } while (encontrado == 0);
}

int activo()
{
    //si el stock es mayor a 0, automáticamente pasa a estar disponible
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
        printf("\nProducto registrado exitosamente.\n");
        contProductos++;
        activos++;
    }
    else
    {
        printf("\nEl inventario esta lleno.\n");
    }
}

void mostrarProducto()
{
    int p;

    noHallado(); //verificamos si el inventario está vacío antes de intentar mostrar los productos
    if (contProductos != 0)
    {
        printf("==================== INVENTARIO ACTUAL ====================\n");
        printf("%-5s %-15s %-10s %-10s %-8s\n", "ID", "NOMBRE", "PRECIO", "STOCK", "ESTADO");
        printf("-----------------------------------------------------------\n");
        for (p = 0; p < contProductos; p++) //mostrar la información de cada producto registrado en el inventario
        {
            if (productos[p].activo == 1)
            {
                printf("%-5d %-15s $%-10.2f %-10d %-8s\n", productos[p].id, productos[p].name, productos[p].precio, productos[p].stock, (productos[p].activo == 1) ? "Disponible" : "no disponible"); //<- OPERADOR TERNIARIO: (productos[p].activo == 1) ? "Disponible" : "no disponible"
                //utilizando un OPERADOR TERNARIO muestra "Disponible" si el valor de activo es 1 y "no disponible" si el valor de activo es 0
            }
        }
        printf("===========================================================\n");
    }
}

void eliminar()
{
    int eliminarID;
    encontrado=0; //como dije antes, al ser una variable global, aqui la reseteamos antes que nada
    
    if (activos == 0)
    {
        noHallado();
        return;
    }

    printf("ID del producto a eliminar: ");
    scanf("%d", &eliminarID);

    int idx = encontrarIndice(eliminarID); // nuevamente, encontrarIndice() para obtener el índice del producto a eliminar
    // Solo buscamos entre los que estan activos
    if (idx != -1)
    {
        productos[idx].activo = 0; // Marcamos el producto como inactivo
        activos--;
        printf("Producto con ID %d ha sido eliminado.\n", eliminarID);
      
    }
    else
    {
        printf("No se encontro el ID o ya fue eliminado.\n");
    }
}

void retirar() 
{
    int id;
    int cantidad;

    if (activos == 0)
    {
        noHallado();
        return;
    }

    printf("ID de producto a retirar: ");
    scanf("%d", &id);

    int idx = encontrarIndice(id); //emcontrarIndiceDeidad

    if (idx != -1)
    {
        printf("Cantidad a retirar: ");
        scanf("%d", &cantidad);

        if (cantidad <= productos[idx].stock)
        {
            productos[idx].stock -= cantidad;
            printf("Retiro exitoso. Stock restante: %d\n", productos[idx].stock);

            if (productos[idx].stock == 0)
            {
                productos[idx].activo = 0;
                activos--;
                printf("El producto se ha agotado y marcado como inactivo.\n");
            }
        }
        else
        {
            ; // Si el stock es 0, marcamos el producto como inactivo
            printf("Error!\n");
            printf("Stock insuficiente.\n");
        }
    }
    else
    {
        printf("Producto no encontrado.\n");
    }
}

int consultar() 
{
    int id;

    if (activos == 0)
    {
        noHallado();
        return 0;
    }

    printf("ID del producto a consultar: ");
    scanf("%d", &id);

    int idx = encontrarIndice(id); //Padre Indice

    if (idx != -1)//si el producto existe y está activo, se muestra su información detallada
    {
        printf("\n------------------ DETALLES DEL PRODUCTO ------------------\n");
        printf("\t\tID:                     %d\n", productos[idx].id);
        printf("\t\tNombre:                 %s\n", productos[idx].name);
        printf("\t\tTamano:                 %.2f gramos\n", productos[idx].tamano);
        printf("\t\tStock:                  %d unidades\n", productos[idx].stock);
        printf("\t\tPrecio:                 $%.2f\n", productos[idx].precio);
        printf("\t\tFecha de ingreso:       %02d/%02d/%04d\n", productos[idx].dia, productos[idx].mes, productos[idx].anio);
        printf("\t\tProveedor:              %s\n", productos[idx].nombreProveedor);
        printf("\t\tRIF del proveedor:      %d\n", productos[idx].rifProveedor);
        printf("\t\tCodigo del proveedor:   %s\n", productos[idx].codigoProveedor);
        printf("\t\tEstado:                 %s\n", (productos[idx].activo == 1) ? "Disponible" : "No disponible");
        printf("------------------------------------------------------------\n");
    }
    else//sino, tira este print
    {
        printf("Producto no encontrado.\n");
    }
    return id;
}

void noHallado()
{
    if (activos == 0)
    {
        printf("===========================================================\n");
        printf("\nEl inventario esta vacio.\n\n");
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