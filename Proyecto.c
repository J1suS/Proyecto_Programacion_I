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
float auxTamano;
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
int salir(int valor);
int encontrarIndice(int BuscarID);
void almacen();
int menu();
void productoNoHallado();
void registrarProducto();
int llenarPlantilla();
int leerCodigo();
int leerNombre();
int leerTamano();
int leerStock();
float leerPrecio();
int leerFechaIngreso();
void leerProveedor();
int posibleProveedor(int p);
void encontrarProveedor(int p);
void guardarProveedor(int p);
int leerActivo();
void agregarStock();
void eliminarProducto();
void mostrarProducto();
int consultarProducto();
void retirarProducto();

//--------CODIGO PRINCIPAL--------
int main()
{
    almacen();
    return 0;
}

//--------DESARROLLO DE FUNCIONES--------
int salir(int valor)
{
    if (valor == -1)
    {
        printf("\nAccion cancelada. Volviendo al menu\n");
        return 1;
    }
    return 0;
}

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
        printf("[ 3 ] Agregar\n");
        printf("[ 4 ] Eliminar\n");
        printf("[ 5 ] Retirar\n");
        printf("[ 6 ] Consultar\n");
        printf("[ 7 ] Salir\n");
        printf("===========================================================\n");
        scanf("%d", &option);

        if (option < 1 || option > 7)//valida que la opción ingresada esté dentro del rango permitido
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
    }while (option < 1 || option > 7);
    return option;
}

int leerCodigo()
{
    int repetido;

    printf("====================REGISTRAR PRODUCTO=====================\n");
    printf("ID (-1 Cancelar): ");
    scanf("%d", &auxCodigo); //<-auxiliar para validar

    if (salir(auxCodigo))//se escribe en cada opción seleccionada para que, en cualquier momento el usuario pueda salir
    {
        return -1;
    }

    do
    {
        repetido=0;

        //validación del código
        while(auxCodigo<-1)
        {
            printf("ID invalida, intente otra vez: ");
            scanf("%d", &auxCodigo);

            if (salir(auxCodigo))
            {
                return -1;
            }
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

            if (salir(auxCodigo))
            {
                return -1;
            }
            repetido=1;
        }
    } while (repetido==1);

    productos[contProductos].id = auxCodigo ;//si no hay código repetido, se asigna a la posición del arreglo de productos correspondiente
    return auxCodigo;
}

int leerNombre()
{
    printf("Producto (-1 para salir): ");
    scanf(" %s", productos[contProductos].name);

    if (productos[contProductos].name[0] == '-' && productos[contProductos].name[1] == '1')
    {
        salir(-1);
        return -1;
    }
    return 1;
}

int leerTamano()
{
    printf("Tamano en gramos (-1 para salir): ");
    scanf("%f", &auxTamano);
    
    if (salir((int)auxTamano))
    {
        return -1;
    }

    //validación del tamaño
    while(auxTamano<-1)
    {
        printf("Tamano incorrecto, ingrese el tamano: ");
        scanf("%f", &auxTamano);	

        if (salir((int)auxTamano))
        {
            return -1;
        }
    }
    //fin validación

    productos[contProductos].tamano = auxTamano;
    return 1;
}

int leerStock()
{
    printf("Stock (-1 para salir): ");
    scanf("%d", &auxCantidad);

    if (salir(auxCantidad))
    {
        return -1;
    }

    //validación del stock
    while(auxCantidad < 1 && auxCantidad != -1)
    {
    printf("Stock incorrecto, ingrese el stock (-1 para salir): ");
    scanf("%d", &auxCantidad);	
    }
    //fin validación

    if (salir(auxCantidad))
    {
        return -1;
    }

    productos[contProductos].stock = auxCantidad;
    return 1;
}

float leerPrecio()
{
    printf("Precio (-1 para salir): $");
    scanf("%f", &auxPrecio);

    if (salir((int)auxPrecio))
    {
        return -1;
    }

    //validación del precio
    while(auxPrecio<0.1 && auxPrecio != -1)
    {
        printf("Precio invalido, ingrese el precio (-1 para salir): ");
        scanf("%f", &auxPrecio);
        if (salir((int)auxPrecio))
        {
            return -1;
        }
    }
    //fin validación
    
    productos[contProductos].precio=auxPrecio;
    return 1;
}

int leerFechaIngreso()
{
    int fechaValida=0;

    while (fechaValida == 0)
    {
        printf("Fecha de Ingreso (DD/MM/AAAA) o (-1 para salir): ");

        if (scanf("%d", &productos[contProductos].dia) != 1)
        {
            return -1;
        }

        if (salir(productos[contProductos].dia))
        {
            return -1;
        }

        if (productos[contProductos].dia < 1 || productos[contProductos].dia > 31)
        {
            printf("Dia invalido (1-31)\nIngrese el dia: ");
            continue;
        }
        

        scanf(" /%d/%d", &productos[contProductos].mes, 
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
    return 1;
}

void leerProveedor()
{
    int p;
    int coincide;

    do
    {
        encontrado = 0; //al ser una variable global, aqui la reseteamos antes que nada
        coincide = 0;

        printf("RIF del proveedor (-1 para salir): ");
        scanf("%d", &auxProveedor);

        if (salir(auxProveedor))
        {
            encontrado = -1;
            return;
        }

        for (p = 0; p < MAX_PROVEEDORES; p++)
        {
            if (proveedores[p].rif == auxProveedor)
            {
                encontrarProveedor(p);//esta función muestra la información del proveedor encontrado y pregunta si desea seleccionarlo, si el usuario selecciona el proveedor, se guarda su información en el arreglo de productos para que aparezca en los reportes
                coincide++;

                if (encontrado != 0)
                {
                    break;
                }
            }
        }

        if (coincide == 0 && encontrado == 0)
        {
            printf("RIF no encontrado, intente de nuevo.\n");
        }
        
    } while (encontrado == 0);
}

void encontrarProveedor(int p)
{
    int confirmacion;
    confirmacion = posibleProveedor(p); //muestra la información del proveedor encontrado y pregunta si desea seleccionarlo

    if (confirmacion == -1)
    {
        encontrado = -1;
        return;
    }
    
    if (confirmacion == 1)
    {
        guardarProveedor(p); //guarda la información del proveedor seleccionado en el arreglo de productos para que aparezca en los reportes
        encontrado=1;
    }
}

int posibleProveedor(int p)
{
    int respuesta;
    printf("\n--- INFORMACION DEL PROVEEDOR ---\n");
    printf("RIF: %d\n", proveedores[p].rif);
    printf("Nombre: %s\n", proveedores[p].nombre);
    printf("Codigo: %s\n", proveedores[p].codigo);
    printf("----------------------------------\n");

    printf("Desea seleccionar este proveedor?\n");
    printf(" 1) Si\n");
    printf(" 0) No\n");
    printf("-1) Cancelar\n");
    printf("-->");
    scanf("%d", &respuesta);

    if (salir(respuesta))
    {
        return -1;
    }

    //validación de la confirmación
    while(respuesta < -1 || respuesta > 1)
    {
        printf("Opcion invalida\n");
        printf(" 1) para seleccionar\n");
        printf(" 0) para no seleccionar\n");
        printf("-1) para cancelar\n");
        printf("-->");
        scanf("%d", &respuesta);	
    
        if (salir(respuesta))
        {
            return -1;
        }
    }
    //fin validación

    return respuesta;
}

void guardarProveedor(int p)
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
}

int leerActivo()
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
        if (llenarPlantilla() == -1)
        {
            return;
        }

        leerActivo();

        printf("\n==========================================\n");
        printf("   PRODUCTO REGISTRADO EXITOSAMENTE\n");
        printf("==========================================\n");

        contProductos++;
        activos++;
    }
    else
    {
        printf("\nEl inventario esta lleno.\n");
    }
}

void agregarStock()
{
    int id;
    int cantidad;
    int idx;
    int s;

    if (contProductos == 0)
    {
        productoNoHallado();
        return;
    }
    
    printf("ID del producto a agregar stock (-1 para salir): ");
    scanf("%d", &id);

    if (salir(id))
    {
        return;
    }

    idx = -1;
    for (s = 0; s < contProductos; s++)
    {
        if (productos[s].id == id)
        {
            idx = s;
            break;
        }
    }

    if (idx != -1)
    {
        printf("Producto %s\n", productos[idx].name);
        printf("Stock actual: %d\n", productos[idx].stock);
        printf("Cantidad a agregar (-1 para salir): ");
        scanf("%d", &cantidad);

        if (salir(cantidad))
        {
            return;
        }

        if (cantidad > 0)
        {
            if (productos[idx].stock == 0)
            {
                productos[idx].activo = 1;
                activos++;
            }

            productos[idx].stock += cantidad;
            printf("El producto ha sido reactivado.\n");
            printf("Stock actualizado. Nuevo stock: %d\n", productos[idx].stock);
        }
        else
        {
            printf("Cantidad invalida.\n");
        }
    }
    else
    {
        printf("Producto no encontrado.\n");
    }
}

int llenarPlantilla()
{
    if (leerCodigo() == -1)
    {
        return -1;
    }
    if (leerNombre() == -1)
    {
        return -1;
    }
    if (leerTamano() == -1)
    {
        return -1;
    }
    if (leerStock() == -1)
    {
        return -1;
    }
    if (leerPrecio() == -1)
    {
        return -1;
    }
    if (leerFechaIngreso() == -1)
    {
        return -1;
    }

    leerProveedor();

    if (encontrado == -1)
    {
        return -1;
    }

    return 1;
}

void mostrarProducto()
{
    int p;
    if (activos == 0)
    {
        productoNoHallado();//verificamos si el inventario está vacío antes de intentar mostrar los productos
        return;
    }

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


void eliminarProducto()
{
    int eliminarID;
    int confirmacion;
    encontrado=0; //como dije antes, al ser una variable global, aqui la reseteamos antes que nada
    int termiando=0;

    if (activos == 0)
    {
        productoNoHallado();
        return;
    }

    while (termiando == 0)
    {
        printf("ID del producto a eliminar (-1 para salir): ");
        scanf("%d", &eliminarID);

        if (salir(eliminarID) == -1)
        {
            break;
        }

        int idx = encontrarIndice(eliminarID); // nuevamente, encontrarIndice() para obtener el índice del producto a eliminar
        // Solo buscamos entre los que estan activos
        if (idx != -1)
        {
            printf("\n>>> PRODUCTO ENCONTRADO <<<\n");
            printf("\n>>> Producto: %s <<<\n", productos[idx].name);
            printf("\n>>> Stock: %d <<<\n", productos[idx].stock);
            printf("\n>>> Precio: $%.2f <<<\n", productos[idx].precio);
            printf("\n>>> PRODUCTO ENCONTRADO <<<\n");
            printf("Desea eliminar este producto? \n");
            printf(" 1) Si\n");
            printf(" 0) No\n");
            printf("-1) Cancelar\n");
            scanf("%d", &confirmacion);

            if (salir(confirmacion))
            {
                break;
            }
            
            if (confirmacion == 1)
            {
                productos[idx].activo = 0; // Marcamos el producto como inactivo
                activos--;
                printf("Producto con ID %d ha sido eliminado.\n", eliminarID);
                termiando = 1; // Salimos después de eliminar el producto
            }
            else
            {
                printf("Eliminacion cancelada.\n");
            }
        }
        else
        {
            printf("No se encontro el ID o ya fue eliminado.\n");
        }
    }
}

void retirarProducto() 
{
    int id;
    int cantidad;
    int terminado=0;

    if (activos == 0)
    {
        productoNoHallado();
        return;
    }
    while (terminado == 0)
    {
        printf("ID de producto a retirar (-1 para salir): ");
        scanf("%d", &id);

        if (salir(id))
        {
            break;
        }

        int idx = encontrarIndice(id); //emcontrarIndiceDeidad

        if (idx != -1)
        {
            printf("Producto %s\n", productos[idx].name);
            printf("Stock actual: %d\n", productos[idx].stock);
            printf("Cantidad a retirar: ");
            scanf("%d", &cantidad);

            if (salir(cantidad))
            {
                break;
            }

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
                terminado = 1; // Salimos después de realizar el retiro
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
}

int consultarProducto() 
{
    int id;
    int terminado=0;

    if (activos == 0)
    {
        productoNoHallado();
        return -1;
    }

    while (terminado == 0)
    {
        printf("ID del producto a consultar (-1 para salir): ");
        scanf("%d", &id);

        if (salir(id))
        {
            return 0;
        }

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
            terminado = 1;
        }
        else//sino, tira este print
        {
            printf("Producto no encontrado.\n");
        }
    }
    return id;
}

void productoNoHallado()
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
            agregarStock();
            break;
        case 4:
            eliminarProducto();
            break;
        case 5:
            retirarProducto();
            break;
        case 6:
            consultarProducto();
            break;
        }
    } while (option != 7);
}