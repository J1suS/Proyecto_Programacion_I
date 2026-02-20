//--------LIBRERÍA--------
#include <stdio.h>


//--------CONSTANTES--------
#define MAX_PROVEEDORES 5
#define MAX_PRODUCTOS 10
#define MINIMO_STOCK 10


//--------VARIABLES GLOBALES--------
int contProductos=0;
//Todas las que tengan al inicio aux son auxiliares
int auxCodigo;
float auxPrecio;
float auxTamano;
int auxCantidad;
int auxProveedor;
int auxRif;
int productosRIF[MAX_PRODUCTOS];
int auxActivo;
int contproveedor = 0;
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
    int dia;
    int mes;
    int anio;
    int activo;
};

struct Proveedor 
{
    int rif;
    char nombre[50];
};

struct Proveedor proveedores[MAX_PROVEEDORES]; //donde se guarda la info del proveedor

struct Producto productos[MAX_PRODUCTOS]; //donde se guarda la info


//--------FUNCIONES--------
int salir(int valor);
int encontrarID(int buscarID);
int encontrarRIF(int buscarRIF);
void almacen();
int menuPrincipal();
int menu();
void gestionConsultar();
void gestionProveedores();
void productoNoHallado();
void registroProveedor();
void registrarProducto();
int cancelarAccion();
int leerCodigo();
int leerNombre();
int leerTamano();
int leerStock();
float leerPrecio();
int leerFechaIngreso();
int gestionFecha();
int dia();
int diaValido(int day, int month, int year);//day = día, month = mes, year = año. Sencillo
int mes();
int anio();
void leerProveedor();
int posibleProveedor(int p);
void encontrarProveedor(int p);
int leerActivo();
void agregarStock();
void eliminarProducto();
void productoEncontrado(int idx);
void mostrarProducto();
void gestionConsultar();
int consultarProducto();
void retirarProducto();
void proveedornohallado();

//--------CODIGO PRINCIPAL--------
int main()
{
    menuPrincipal();
    return 0;
}

//--------DESARROLLO DE FUNCIONES--------
//RESULTADO
void almacen()
{
    int option;
    
    if(contproveedor == 0) {
    proveedornohallado();
    return;
    }
    
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
            gestionConsultar();
            break;
        case 0:
            break;
        }
    } while (option != 0);
}

//OPCIONES DISPONIBLES DEL MENÚ
int menuPrincipal()
{
    int opcionPrincipal;

    for (int b = 0; b < MAX_PROVEEDORES; b++)
    {
        proveedores[b].rif = 0;
        if (b < MAX_PRODUCTOS)
        {
            productosRIF[b] = 0;
        }
    }

    do
    {
        printf("===========================================================\n");
        printf("                SISTEMA GESTION CAFE\n");
        printf("===========================================================\n");
        printf("[ 1 ] Proveedores\n");
        printf("[ 2 ] Almacen\n");
        printf("[ 3 ] Salir\n");
        printf("===========================================================\n");
        scanf("%d", &opcionPrincipal);

        switch (opcionPrincipal)
        {
        case 1:
            gestionProveedores();
            break;
        case 2:
            almacen();
            break;
        case 3:
            printf("Saliendo del Sistema...\n");
            break;
        }

        if (opcionPrincipal < 1 || opcionPrincipal > 3)
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
        
    } while (opcionPrincipal != 3);
    return 0;
}

void gestionProveedores()
{
    int hay=0;
    int subOpcion;
    int g;

    do
    {
        printf("===========================================================\n");
        printf("                GESTION DE PROVEEDORES\n");
        printf("===========================================================\n");
        printf("[ 1 ] Agregar\n");
        printf("[ 2 ] Mostrar\n");
        printf("[ 0 ] Regresar\n");
        printf("===========================================================\n");
        scanf("%d", &subOpcion);

        if (salir(subOpcion))
        {
            return;
        }
        
        switch (subOpcion)
        {
        case 1:
            registroProveedor();
            break;
        case 2:
            
            hay = 0;
            for (g = 0; g < MAX_PROVEEDORES; g++)
            {
                if (proveedores[g].rif != 0)
                {
                    hay = 1;
                    break;
                }
            }

            if (hay == 1)
            {
                printf("-----PROVEEDORES REGISTRADOS-----\n");
                printf("%-16s %-30s\n", "RIF", "NOMBRE");
                printf("---------------------------------\n");
                for (g = 0; g < MAX_PROVEEDORES; g++)
                {
                    if (proveedores[g].rif != 0)
                    {
                        printf("RIF-%-12d %-30s\n", proveedores[g].rif, proveedores[g].nombre);
                    }
                }
                printf("---------------------------------\n");
            }
            else
            {
                proveedornohallado();
            }
                            
            break;
        }

        if (subOpcion < 0 || subOpcion > 2)
        {
            printf("Opcion invalida.\n");
        }
        


    } while (subOpcion != 0);
    
}

void registroProveedor()
{
    int r;
    int posEncontrado = -1;

    for (r = 0; r < MAX_PROVEEDORES; r++)
    {
        if (proveedores[r].rif == 0)
        {
            posEncontrado = r;            
            break;
        }
    }
    
    if (posEncontrado != -1)
    {
        do
        {
            printf("\n--- REGISTRO DE PROVEEDOR ---\n");
            printf("Nombre: ");
            scanf(" %s", proveedores[posEncontrado].nombre);

            printf("RIF (0 para cancelar): RIF-");
            scanf("%d", &auxRif);

            if (salir(auxRif))
            {
                return;
            }

            if (auxRif < 0)
            {
                printf("RIF invalido, intente otra vez.\n");
                continue;
            }

            if (encontrarRIF(auxRif) != -1)
            {
                printf("RIF ya registrado.\n");
                auxRif = -1;
            }
        } while (auxRif < 0);

        proveedores[posEncontrado].rif = auxRif;
        printf("Proveedor registrado correctamente.\n");
        contproveedor++;
    }
    else
    {
        printf("\nLimite de proveedores alcanzado.\n");
    }
}

int menu()
{
    int option;//guarda la opción ingresada por el usuario

    proveedornohallado();

    do
    {
        printf("===========================================================\n");
        printf("\t\t\tALMACEN CAFE\n");
        printf("===========================================================\n");
        printf("[ 1 ] Ingresar\n");
        printf("[ 2 ] Mostrar\n");
        printf("[ 3 ] Consultar\n");
        printf("[ 0 ] Regresar\n");
        printf("===========================================================\n");
        scanf("%d", &option);

        if (option < 0 || option > 3)//valida que la opción ingresada esté dentro del rango permitido
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
    }while (option < 0 || option > 3);
    return option;
}

void gestionConsultar()
{
    int subOpcion;

    if (contProductos == 0)
    {
        productoNoHallado();
        return;
    }

    do
    {
        printf("===================CONSULTA DE PRODUCTO====================\n");
        printf("[ 1 ] Buscar\n");
        printf("[ 2 ] Agregar\n");
        printf("[ 3 ] Retirar\n");
        printf("[ 4 ] Eliminar\n");
        printf("[ 0 ] Cancelar\n");
        printf("===========================================================\n");
        scanf("%d", &subOpcion);

        switch (subOpcion)
        {
        case 1:
            consultarProducto();
            break;
        case 2:
            agregarStock();
            break;
        case 3:
            retirarProducto();
            break;
        case 4:
            eliminarProducto();
            break;
        case 0:
            printf("Volviendo al menu principal...\n");
            break;
        }

        if (subOpcion < 0 || subOpcion > 4)//valida que la opción ingresada esté dentro del rango permitido
        {
            printf("\nOpcion invalida, intente de nuevo.\n");
        }
    } while (subOpcion < 0 || subOpcion > 4);
}

//FUNCIONES DEL MENÚ
void registrarProducto()
{
    if (contProductos < MAX_PRODUCTOS)//no se podrán ingresar más datos si no se cumple esta condición
    {
        //PLANTILLA DEL PRODUCTO
        if (cancelarAccion() == 0)
        {
            return;
        }

        leerActivo();

        printf("\n===========================================================\n");
        printf("             PRODUCTO REGISTRADO EXITOSAMENTE\n");
        printf("===========================================================\n\n");

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
    int estado;
    int seleccion;
    int encontradoLocal=0; //esta es local, nada que ver con la global

    if (contProductos == 0)
    {
        productoNoHallado();//verificamos si el inventario está vacío antes de intentar mostrar los productos
        return;
    }

    do
    {
        printf("===================REPORTE DE INVENTARIO===================\n");
        printf(" [ 1 ] Productos Activos (Disponibles)\n");
        printf(" [ 2 ] Productos Inactivos (No disponibles)\n");
        printf(" [ 3 ] Productos bajos de stock (Para reponer)\n");
        printf(" [ 0 ] Cancelar\n");
        printf("-->");
        scanf("%d", &seleccion);

        if (salir(seleccion))
        {
            return;
        }

        if (seleccion < 1 || seleccion > 3)
        {
            printf("Opcion invalida. Intente nuevamente.\n");
        }
    }while (seleccion < 1 || seleccion > 3);

    estado = (seleccion == 1) ? 1 : 0; //si la selección es 1, estado será 1 (productos activos), si la selección es 2, estado será 0 (productos inactivos)

    for (p = 0; p < contProductos; p++) //mostrar la información de cada producto registrado en el inventario
    {
    	int mostrarEsteProducto = 0;

        if (seleccion == 1 || seleccion == 2) {
            if (productos[p].activo == estado) mostrarEsteProducto = 1;
        } 
        else if (seleccion == 3) {
            if (productos[p].stock <= MINIMO_STOCK) mostrarEsteProducto = 1;
        }
        if (mostrarEsteProducto)
        {
            if (encontradoLocal == 0)
            {
                printf("=========================INVENTARIO========================\n");
                printf("%-5s %-15s %-10s %-10s %-8s\n", "ID", "NOMBRE", "PRECIO", "STOCK", "ESTADO");
                printf("-----------------------------------------------------------\n");
            }
            
            printf("%-5d %-15s $%-10.2f %-10d %-8s\n", productos[p].id, productos[p].name, productos[p].precio, productos[p].stock, (productos[p].activo == 1) ? "Disponible" : "no disponible"); //<- OPERADOR TERNIARIO: (productos[p].activo == 1) ? "Disponible" : "no disponible"
            //utilizando un OPERADOR TERNARIO muestra "Disponible" si el valor de activo es 1 y "no disponible" si el valor de activo es 0
            encontradoLocal++;
        }
    }
    printf("-----------------------------------------------------------\n\n");

    if (encontradoLocal == 0)
    {
        printf("===========================================================\n");
        printf("No se encontraron productos en esta categoria.\n");
        printf("===========================================================\n");
    }
}

int consultarProducto() 
{
    int id;
    
    int terminado=0;

    if (activos == 0)
    {
        productoNoHallado();
        return 0;
    }

    while (terminado == 0)
    {
    	printf("===================BUSQUEDA DE PRODUCTO====================\n");
        printf("ID del producto a consultar (0 para cancelar): ");
        scanf("%d", &id);

        if (salir(id))
        {
            return 0;
        }

        int idx = encontrarID(id); //Padre Indice

        if (idx != -1)//si el producto existe y está activo, se muestra su información detallada
        {
            printf("\n-------------------DETALLES DEL PRODUCTO-------------------\n");
            printf("\t\tID:                     %d\n", productos[idx].id);
            printf("\t\tNombre:                 %s\n", productos[idx].name);
            printf("\t\tTamano:                 %.2f gramos\n", productos[idx].tamano);
            printf("\t\tStock:                  %d unidades\n", productos[idx].stock);
            printf("\t\tPrecio:                 $%.2f\n", productos[idx].precio);
            printf("\t\tFecha de ingreso:       %02d/%02d/%04d\n", productos[idx].dia, productos[idx].mes, productos[idx].anio);
            int RIFguardado = productosRIF[idx];
            int idxRealProv = encontrarRIF(RIFguardado);
            if (idxRealProv != -1)
            {
                printf("\t\tProveedor:              %s\n", proveedores[idxRealProv].nombre);
                printf("\t\tRIF del proveedor:      %d\n", proveedores[idxRealProv].rif);
            }
            else
            {
                printf("\t\tProveedor:              [No asignado]\n");
                printf("\t\tRIF del proveedor:      [N/A]\n");
            }
            printf("\t\tEstado:                 %s\n", (productos[idx].activo == 1) ? "Disponible" : "No disponible");
            printf("-----------------------------------------------------------\n");
            terminado = 1;
        }
        else//sino, tira este print
        {
            printf("Producto no encontrado.\n");
        }
    }
    return id;
}

//FUNCIONES DE CONSULTAR
void agregarStock()
{
    int id;
    int cantidad;
    int idx;

    if (contProductos == 0)
    {
        productoNoHallado();
        return;
    }
    
    printf("===================AGREGAR UNIDADES========================\n");
    printf("ID del producto a agregar stock (0 para cancelar): ");
    scanf("%d", &id);

    if (salir(id))
    {
        return;
    }

    idx = encontrarID(id);

    if (idx != -1)
    {
        printf("===========================================================\n");
        printf("Producto %s\n", productos[idx].name);
        printf("Stock actual: %d\n", productos[idx].stock);
        printf("Cantidad a agregar (0 para cancelar): ");
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

void eliminarProducto()
{
    int eliminarID;
    int confirmacion;
    encontrado=0; //como dije antes, al ser una variable global, aqui la reseteamos antes que nada
    int terminado=0;

    if (activos == 0)
    {
        productoNoHallado();
        return;
    }

    while (terminado == 0)
    {
        printf("===================ELIMINAR PRODUCTO=======================\n");
        printf("ID del producto a eliminar (0 para cancelar): ");
        scanf("%d", &eliminarID);

        if (salir(eliminarID))
        {
            terminado = 1;
            break;
        }

        int idx = encontrarID(eliminarID); // nuevamente, encontrarIndice() para obtener el índice del producto a eliminar
        // Solo buscamos entre los que estan activos
        if (idx != -1)
        {
            if (productos[idx].activo == 0)
            {
                printf("El producto ya fue eliminado.\n");
            }
            else
            {
                productoEncontrado(idx);
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
                    terminado = 1; // Salimos después de eliminar el producto
                }
                else
                {
                    printf("Eliminacion cancelada.\n");
                }
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
        printf("====================RETIRAR PRODUCTO=======================\n");
        printf("ID de producto a retirar (0 para cancelar): ");
        scanf("%d", &id);

        if (salir(id))
        {
            return;
        }

        int idx = encontrarID(id); //emcontrarIndiceDeidad

        if (idx != -1)
        {
            printf("Producto %s\n", productos[idx].name);
            printf("Stock actual: %d\n", productos[idx].stock);
            printf("Cantidad a retirar: ");
            scanf("%d", &cantidad);

            if (salir(cantidad))
            {
                return;
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

int salir(int valor)
{
    if (valor == 0)
    {
        printf("===========================================================\n");
        printf("\nAccion cancelada. Volviendo al menu\n\n");
        return 1;
    }
    return 0;
}

//CUALQUIER OPCIÓN DISTINTA DE INGRESAR, SIN HABER INGRESADO UN PRODUCTO
void productoNoHallado()
{
    if (activos == 0)
    {
        printf("===========================================================\n");
        printf("\nEl inventario esta vacio.\n\n");
    }
}

//FOR CENTRALIZADO PARA TODO
int encontrarID(int buscarID)
{
    int i;
    for (i = 0; i < contProductos; i++)
    {
        if (productos[i].id == buscarID) // Verifica que el ID coincida y que el producto esté activo
        {
            return i; // retorna la iteración del ciclo si hay producto encontrado
        }
    }
    return -1; // retorna -1 si no encuentra un producto
}

int encontrarRIF(int buscarRIF)
{
    int i;
    for (i = 0; i < MAX_PROVEEDORES; i++)
    {
        if (proveedores[i].rif != 0 && proveedores[i].rif == buscarRIF)
        {
            return i;
        }
    }
    return -1;
}

//INGRESAR PRODUCTO
int leerCodigo()
{
    int repetido;

    printf("====================REGISTRAR PRODUCTO=====================\n");
    printf("ID (0 para cancelar): ");
    scanf("%d", &auxCodigo); //<-auxiliar para validar

    if (salir(auxCodigo))//se escribe en cada opción seleccionada para que, en cualquier momento el usuario pueda salir
    {
        return 0;
    }

    do
    {
        repetido=0;

        //validación del código
        while(auxCodigo<0)
        {
            printf("ID invalida, intente otra vez: ");
            scanf("%d", &auxCodigo);

            if (salir(auxCodigo))
            {
                return 0;
            }
        }
        //fin validación

        /*utilizamos la función buscarCualquierID para verificar 
        si el ID ingresado ya existe en el arreglo de productos,
        si la función retorna -1 significa que el ID ya 
        existe y se pide al usuario que ingrese otro ID*/
        if(encontrarID(auxCodigo) != -1) 
        {
            printf("El ID ya existe, ingrese otro ID: ");
            scanf("%d", &auxCodigo);

            if (salir(auxCodigo))
            {
                return 0;
            }
            repetido=1;
        }
    } while (repetido==1);

    productos[contProductos].id = auxCodigo ;//si no hay código repetido, se asigna a la posición del arreglo de productos correspondiente
    return auxCodigo;
}

int leerNombre()
{
    printf("Producto (0 para cancelar): ");
    scanf(" %19s", productos[contProductos].name);

    if (productos[contProductos].name[0] == '0')
    {
        salir(0);
        return 0;
    }
    return 1;
}

int leerTamano()
{
    printf("Tamano en gramos (0 para cancelar): ");
    scanf("%f", &auxTamano);
    
    if (salir((int)auxTamano))
    {
        return 0;
    }

    //validación del tamaño
    while(auxTamano<0)
    {
        printf("Tamano incorrecto, ingrese el tamano: ");
        scanf("%f", &auxTamano);	

        if (salir((int)auxTamano))
        {
            return 0;
        }
    }
    //fin validación

    productos[contProductos].tamano = auxTamano;
    return 1;
}

int leerStock()
{
    printf("Stock (0 para cancelar): ");
    scanf("%d", &auxCantidad);

    if (salir(auxCantidad))
    {
        return 0;
    }

    //validación del stock
    while(auxCantidad < 1 && auxCantidad != 0)
    {
    printf("Stock incorrecto, ingrese el stock (0 para cancelar): ");
    scanf("%d", &auxCantidad);	
    }
    //fin validación

    if (salir(auxCantidad))
    {
        return 0;
    }

    productos[contProductos].stock = auxCantidad;
    return 1;
}

float leerPrecio()
{
    printf("Precio (0 para cancelar): $");
    scanf("%f", &auxPrecio);

    if (salir((int)auxPrecio))
    {
        return 0;
    }

    //validación del precio
    while(auxPrecio<0.1 && auxPrecio != 0)
    {
        printf("Precio invalido, ingrese el precio (0 para cancelar): ");
        scanf("%f", &auxPrecio);
        if (salir((int)auxPrecio))
        {
            return 0;
        }
    }
    //fin validación
    
    productos[contProductos].precio=auxPrecio;
    return 1;
}

int leerFechaIngreso()
{
    if (gestionFecha() == 0)
    {
        return 0;
    }

    return 1;//si to' salió bien
}

void leerProveedor()
{
    int idxProv;

    do
    {
        encontrado = 0; //al ser una variable global, aqui la reseteamos antes que nada
        //a ti tengo que ajustarte
        

        printf("RIF del proveedor (0 para cancelar)\n");
        printf("RIF-");
        scanf("%d", &auxProveedor);

        if (salir(auxProveedor))
        {
            encontrado = 0;
            return;
        }

        idxProv = encontrarRIF(auxProveedor);

        if (idxProv != -1)
        {
            if (posibleProveedor(idxProv) == 1)
            {
                productosRIF[contProductos] = proveedores[idxProv].rif;
                encontrado = 1;
            }
            else
            {
                printf("RIF no encontrado, intente de nuevo.\n");
            }
        }
    } while (encontrado == 0);
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

//SI EN CUALQUIER MOMENTO DESEA CANCELAR LA ACCIÓN
int cancelarAccion()
{
    if (leerCodigo() == 0)
    {
        return 0;
    }
    if (leerNombre() == 0)
    {
        return 0;
    }
    if (leerTamano() == 0)
    {
        return 0;
    }
    if (leerStock() == 0)
    {
        return 0;
    }
    if (leerPrecio() == 0)
    {
        return 0;
    }
    if (leerFechaIngreso() == 0)
    {
        return 0;
    }

    leerProveedor();

    if (encontrado == 0)
    {
        return 0;
    }

    return 1;
}

//FUNCIONES AUXILIARES PARA leerFechaIngreso()
int gestionFecha()
{
    int paso = 1; //1=dia, 2=mes, 3=año
    int result;
    int valido;

    while (paso < 4)
    {
        switch (paso)
        {
        case 1:
            result = dia();
            break;
        case 2:
            result = mes();
            break;
        case 3:
            result = anio();
            break;
        }

        if (result == -1)
        {
            return -1;
        }

        if (result == 1)
        {
            if (paso == 3)
            {
                valido = diaValido(productos[contProductos].dia, productos[contProductos].mes, productos[contProductos].anio);
                
                if (valido == 0)
                {
                    printf("Fecha Inexistente.\n");
                    paso = 1; // Volver al paso del día
                    continue;
                }
            }
            paso++;
        }
        else
        {
            printf("Dato invalido.\n");
        }
    }
    return 1;
}

int diaValido(int day, int month, int year) 
{
    int bisiesto = 0;
    //meses de 31 días
    if (month == 1 || month == 3)
    {
        return (day <= 31);
    }
    if (month == 5 || month == 7)
    {
        return (day <= 31);
    }
    if (month == 8 || month == 10)
    {
        return (day <= 31);
    }
    if (month == 12)
    {
        return (day <= 31);
    }
    
    //meses de 30 días
    if (month == 4 || month == 6)
    {
        return (day <= 30);
    }
    if (month == 9 || month == 11)
    {
        return (day <= 30);
    }
    
    //Febrero
    if (month == 2)
    {
        bisiesto = 0;

        if (year % 4 == 0)
        {
            if (year % 100 != 0)
            {
                bisiesto = 1;
            }
            else if (year % 400 == 0)
            {
                bisiesto = 1;
            }
        }
    }
    
    if (bisiesto == 1)
    {
        return (day <= 29);
    }
    return (day <= 28);

    return 0;
}

int dia()
{
    printf("Dia: (DD) (0 para cancelar): ");
    scanf("%d", &productos[contProductos].dia);

    if (salir(productos[contProductos].dia))
    {
        return 0;
    }

    //validación del día
    if (productos[contProductos].dia < 1 || productos[contProductos].dia > 31)
    {
        printf("Dia invalido (1-31)\nIngrese el dia: ");
        return 0;
    }
    //fin validación
    return 1;
}

int mes()
{
    printf("Mes: (MM) (0 para cancelar): ");
    scanf("%d", &productos[contProductos].mes);

    if (salir(productos[contProductos].mes))
    {
        return 0;
    }

    //validación del mes
    if (productos[contProductos].mes < 1 || productos[contProductos].mes > 12) //tiene que agregar correctamente la fecha completa, si no no sale de este ciclo
    {
        printf("Mes invalido (1-12)\nIngrese el mes: ");
        return 0;
    }
    //fin validación
    return 1;
}

int anio()
{
    printf("Anio: (AAAA) (0 para cancelar): ");
    scanf("%d", &productos[contProductos].anio);

    if (salir(productos[contProductos].anio))
    {
        return 0;
    }

    //validación del año
    if (productos[contProductos].anio < 2000)
    {
        printf("Anio invalido (mayor o igual a 2000)\nIngrese el anio: ");
        return 0;
    }
    //fin validación
    return 1;
}

//FUNCIONES AUXILIARES PARA leerProveedor()

void encontrarProveedor(int p)
{
    int confirmacion;
    confirmacion = posibleProveedor(p); //muestra la información del proveedor encontrado y pregunta si desea seleccionarlo

    if (confirmacion == 0)
    {
        encontrado = 0;
        return;
    }
    
    if (confirmacion == 1)
    {
        encontrado=1;
    }
}

int posibleProveedor(int p)
{
    int respuesta;

    printf("\n----INFORMACION DEL PROVEEDOR----\n");
    printf("RIF: %d\n", proveedores[p].rif);
    printf("Nombre: %s\n", proveedores[p].nombre);
    printf("---------------------------------\n");

    printf("Desea seleccionar este proveedor?\n");

    do
    {
        printf("[ 1 ] Si\n");
        printf("[ 2 ] No\n");
        printf("[ 0 ] Cancelar\n");
        printf("-->");
        scanf("%d", &respuesta);

        if (salir(respuesta))
        {
            return 0;
        }

        //validación de la confirmación
        if (respuesta < 0 || respuesta > 2)
        {
            printf("Opcion invalida\n");
        }
        //fin validación

    } while (respuesta < 1 || respuesta > 2);

    return respuesta;
}

void productoEncontrado(int idx)
{
    printf("\n-------PRODUCTO ENCONTRADO-------\n");
    printf("Producto:   %s\n", productos[idx].name);
    printf("Stock:      %d\n", productos[idx].stock);
    printf("Precio:     $%.2f\n", productos[idx].precio);
    printf("---------------------------------\n");
    printf("Desea eliminar este producto? \n");
    printf("[ 1 ] Si\n");
    printf("[ 2 ] No\n");
    printf("[ 0 ] Cancelar\n");
}

void proveedornohallado() {

	if (contproveedor == 0)
    {
        printf("===========================================================\n");
        printf("\nNo hay proveedores registrados.\n\n");
    }
}