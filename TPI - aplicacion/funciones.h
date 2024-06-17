#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>


//FUNCIONES X
int i;
char optionMain[7][40]={"1: Usuarios.","2: Medidores.","3: MedxUsuarios.","4: Mediciones.","5: Facturas.","6: Costos.","0: Salir."};
char optionUsuarios[5][40]={"1: Cargar datos de usuarios.","2: Imprimir lista de usuarios.","3: Eliminar usuario.","4: Buscar usuario.","0: Volver al inicio."};
char optionMedidores[5][40]={"1: Cargar datos de medidores.","2: Imprimir lista de medidores.","3: Eliminar medidor.","4: Buscar medidor.","0: Volver al inicio."};
char optionFacturas[3][40]={"1: Generar Facturas.","2: Imprimir lista de facturas.","0: Volver al inicio."};               
char optionMedXUsuarios[5][40]={"1: Cargar datos de MedXUsuarios.","2: Imprimir lista de MedXUsuarios.","3: Eliminar MedXUsuarios.","4: Buscar MedXUsuarios.","0: Volver al inicio."};          
char optionMedicion[5][40]={"1: Cargar medicion.","2: Imprimir lista de mediciones.","3: Eliminar medicion.","4: Buscar medicion.","0: Volver al inicio."};  
char optionCostos[3][40]={"1: Agregar costo.","2: Imprimir lista de costos.","0: Volver al inicio."};               
					 		    
//STRUCT DEUDORES
typedef struct deudores{
    char apellidoNombre[60];
    struct deudores *izq;
    struct deudores *der;
}deudores;


//-----LES COSTOS-----
typedef struct Costo {
    int idCosto, mtsDesde, mtsHasta;
    float valorMetro;
    struct Costo *sgte;
}Costo;

typedef struct LESCostos{
    Costo *inicio;
}LESCostos;

//-----LDE MEDICIONES-----

typedef struct NodoLDE {
    int idCuenta, periodo, lectura;
    long int fechaLectura;
    struct NodoLDE *sgte;
    struct NodoLDE *anterior;
}NodoLDE;

typedef struct ListaLDE {
    NodoLDE *primero;
    NodoLDE *ultimo;
    int n;
}ListaLDE;

//-----LES USUARIOS-----
typedef struct usuario{
    int idUsuario;
    char apellidoNombre[60];
    long int fechaAlta;
    struct usuario *sgte;
} usuario;

typedef struct listaUsuarios{
    usuario *inicio;
} listaUsuarios;


//-----LEC MEDIDORES-----
typedef struct medidor {
    int idMedidor, numero;
    char modelo[40];
    struct medidor *sgte;
}medidor;

typedef struct listaCMedidores {
    medidor *cabeza;
}listaCMedidores;

//-----LES FACTURAS-----
typedef struct Factura {
    int idCuenta, periodo, consumo;
    long int fechaEmision;
    float totalPagar;
    long int pagada;
    struct Factura *sgte;
} Factura;

typedef struct ListaEnlazadaFactura {
    Factura *inicio;
} ListaEnlazadaFactura;

//-----LES MedXUsuarios-----
typedef struct NodoMedXUsuarios{
    int idUsuario, idMedidor, idCuenta;
    long int fechaAlta, fechaBaja;
    struct NodoMedXUsuarios *sgte;
}NodoMedXUsuarios;

typedef struct LESMedXUsuarios{
    NodoMedXUsuarios *inicio;
}LESMedXUsuarios;


//-----PROTOTIPOS LES DEUDORES-----
void liberarDeudores(deudores* raiz);
void imprimirDeudores(deudores *raiz);
void buscarNombreUsuario(int idUsuario, char *str);
void insertarOrdDeudores(deudores* raiz, deudores *actual);
long int obtenerFechaActual();

//-----PROTOTIPOS LES COSTOS-----
int encontrarConsumo(ListaLDE *l_mediciones, int idCuenta, int *max1);
float obtenerTotalAPagar(LESCostos *l_costos,int consumo);
int ultimoID_Costo = 0;
int ultimoHasta = 0;
LESCostos *crearListaCostos();
Costo *crearCosto();
void menuCostos(LESCostos *lista);
void liberarListaCostos(LESCostos *lista);
void cargarCosto(LESCostos *lista);
void cargarCostosDesdeCSV(LESCostos *lista);
void insertarCostos(LESCostos *lista, Costo *nuevo);
bool vaciaListaCostos(LESCostos *l);
void leerCostos(LESCostos *lista);
void imprimirCosto(Costo *n);
void guardarCostosEnCSV(LESCostos *lista);

//-----PROTOTIPOS LDE MEDICIONES-----
void mainMediciones();
void iniMediciones(ListaLDE *l);
NodoLDE* crearNodoMediciones();
void insertarMediciones(ListaLDE *l, NodoLDE *nuevoNodo);
void buscarMediciones(ListaLDE *L);
void eliminarMediciones(ListaLDE *L);
void liberarMediciones(ListaLDE *l);
void imprimirMediciones(ListaLDE *l);
void liberarMedicionesLista(ListaLDE* L);
void menuMediciones(ListaLDE *cabeza);
void cargarMedicionesDesdeCSV(ListaLDE *cabeza);
void guardarMedicionesEnCSV(ListaLDE* lista);
bool verifCuenta(int idCuenta);

//-----PROTOTIPOS LES FACTURAS-----
void mainFacturas();
int ultimoID_Factura = 0;
ListaEnlazadaFactura *crearListaEnlazadaFactura();
Factura *crearFactura();
void generarFacturas(ListaEnlazadaFactura* l);
void leerFactura(ListaEnlazadaFactura *l);
void insertarFactura(ListaEnlazadaFactura *l, Factura *n);
void eliminarFactura(ListaEnlazadaFactura* l, int id);
void eliminarListaEnlazadaFactura(ListaEnlazadaFactura* l);
Factura *buscarIDFactura(ListaEnlazadaFactura *l, int id);
bool vaciaListaEnlazadaFactura(ListaEnlazadaFactura *l);
void guardarFacturaEnCSV(ListaEnlazadaFactura* lista);
void menuFactura(ListaEnlazadaFactura* lista);
void imprimirFactura(Factura *n);
void imprimirFecha(long int fecha);

//-----PROTOTIPOS LES USUARIOS-----
void mainUsuarios();
int ultimoID_Usuarios = 0;
listaUsuarios *crearListaUsuarios();
usuario *crearUsuario();
void cargarUsuarios(listaUsuarios *l);
void leerUsuarios(listaUsuarios *l);
void insertarUsuarios(listaUsuarios *l, usuario *n);
void eliminarUsuario(listaUsuarios* l, int id);
void eliminarListaUsuarios(listaUsuarios* l);
usuario *buscarIDUsuarios(listaUsuarios *l, int id);
bool vaciaListaUsuarios(listaUsuarios *l);
void guardarUsuariosEnCSV(listaUsuarios* lista);
void cargarUsuariosDesdeCSV(listaUsuarios* lista);
void menuUsuarios(listaUsuarios* lista);
void imprimirUsuario(usuario *n);


//-----PROTOTIPOS LEC MEDIDORES-----
void mainMedidores ();
int ultimoID_Medidores = 0;
void insertarOrdMedidores(listaCMedidores *p, medidor *n);
void buscarMedidores(listaCMedidores *p);
void inicializarMedidores(listaCMedidores *p);
void eliminarMedidores(listaCMedidores* cabeza, int id);
void imprimirMedidores(listaCMedidores *p);
void imprimirMedidor(medidor *n);
void menuMedidores(listaCMedidores *cabeza);
void eliminarListaMedidores(listaCMedidores *p);
medidor* buscarIDMedidores(listaCMedidores *l, int id);
void leerMedidores(listaCMedidores *l);
listaCMedidores *crearListaC_Medidores();
medidor* crearMedidor();
void cargarMedidor(listaCMedidores* l);
void guardarMedidoresEnCSV(listaCMedidores* lista);
void cargarMedidoresDesdeCSV(listaCMedidores* lista);

//-----PROTOTIPOS LES MEDXUSUARIOS-----
void mainMedXUsuarios();
NodoMedXUsuarios *crearNodoMedXUsuarios();
LESMedXUsuarios *crearLESMedXUsuarios();
void menuMedXUsuarios(LESMedXUsuarios* lista);
int ultimoID_MedXUsuarios = 0;
bool vaciaLESMedXUsuarios(LESMedXUsuarios *l);
void cargarMedXUsuarios(LESMedXUsuarios* l);
void insertarMedXUsuarios(LESMedXUsuarios *l, NodoMedXUsuarios *n);
void leerMedXUsuarios(LESMedXUsuarios *l);
void eliminarNodoMedXUsuarios(LESMedXUsuarios* l, int id);
void eliminarLESMedXUsuarios(LESMedXUsuarios* l);
NodoMedXUsuarios *buscarIDMedXUsuarios(LESMedXUsuarios *l, int id);
void guardarMedXUsuariosEnCSV(LESMedXUsuarios* lista);
void cargarMedXUsuariosDesdeCSV(LESMedXUsuarios* lista);
void imprimirMedXUsuarios(NodoMedXUsuarios *n);
long int verifUsuario(int idUsuario);
bool verifMedidor(int idMedidor);

//-----FUNCIONES LES USUARIOS-----
void mainUsuarios() {
    listaUsuarios* lista = crearListaUsuarios();
    menuUsuarios(lista);
    eliminarListaUsuarios(lista);
    free(lista);
}

//menu
void menuUsuarios(listaUsuarios* lista) {
    int opcion, id;
    cargarUsuariosDesdeCSV(lista);
    do {
        puts("\n\n\t-----MENU USUARIOS-----\n");
        for(i=0;i<6;i++)
    		printf("%s\n",optionUsuarios[i]);
        printf("Ingrese la opcion que desea: ");
        scanf("%d", &opcion);
		puts("");
        switch (opcion) {
            case 1:		cargarUsuarios(lista);		break;
            case 2:		leerUsuarios(lista);		break;
            case 3: 
                printf("Ingrese ID de Usuario a eliminar: ");
                scanf("%d", &id);
                eliminarUsuario(lista, id);
                break;
            case 4:
                printf("Ingrese ID de Usuario a buscar: ");
                scanf("%d", &id);
                usuario *n = buscarIDUsuarios(lista,id);
                if (n != NULL) {
                    printf("Usuario encontrado: \n");
                    imprimirUsuario(n);
                } else 
                    printf("No se encontro el usuario\n");
                break;
            case 0:
                printf("Saliendo del programa...\n");
                guardarUsuariosEnCSV(lista);
                break;
            default:
                printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);
}

//inicializa la lista
listaUsuarios *crearListaUsuarios(){
    listaUsuarios *l = malloc(sizeof(listaUsuarios));
    l->inicio = NULL;
    return l;
}
//reserva espacio apra nuevo nodo/usuario
usuario *crearUsuario(){
    usuario *n = malloc(sizeof(usuario));
    n->sgte = NULL;
    return n;
}

//vacia
bool vaciaListaUsuarios(listaUsuarios *l){
    return l->inicio == NULL;
}

//carga de datos
void cargarUsuarios(listaUsuarios* l) {
    char salir[60] = "0", apellidoNombre[60];
    getchar();
    printf("Ingrese Apellido y Nombre (0 para terminar): ");
    fgets(apellidoNombre, sizeof(apellidoNombre), stdin);
    apellidoNombre[strcspn(apellidoNombre, "\n")] = '\0';
    while (strcmp(apellidoNombre, salir) != 0){
        ultimoID_Usuarios++; // Incrementar el ultimo ID
        usuario* nuevoUsuario = crearUsuario();
        nuevoUsuario->idUsuario = ultimoID_Usuarios;
        strcpy(nuevoUsuario->apellidoNombre, apellidoNombre);
        printf("Ingrese Fecha de Alta //aaaammdd//: ");
        scanf("%ld", &nuevoUsuario->fechaAlta);
        insertarUsuarios(l, nuevoUsuario);
        getchar();
        printf("Ingrese Apellido y Nombre (0 para terminar): ");
        fgets(apellidoNombre, sizeof(apellidoNombre), stdin);
        apellidoNombre[strcspn(apellidoNombre, "\n")] = '\0';
    }
}

//insertar nodo en lista
void insertarUsuarios(listaUsuarios *l, usuario *n) {
    if (vaciaListaUsuarios(l)) {
        l->inicio = n;
    } else if (n->idUsuario < l->inicio->idUsuario) {
        n->sgte = l->inicio;
        l->inicio = n;
    } else {
        usuario* aux = l->inicio;
        while (aux->sgte != NULL && aux->sgte->idUsuario < n->idUsuario) {
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
}

//imprimir lista
void leerUsuarios(listaUsuarios *l){
    usuario *aux = l->inicio;
    while (aux != NULL){
    	imprimirUsuario(aux);
        aux = aux->sgte;
    }
}

//imprime datos de un nodo
void imprimirUsuario(usuario *n){
    printf("\n");
    printf("ID Usuario: %d\n", n->idUsuario);
    printf("Apellido y Nombre: %s\n", n->apellidoNombre);
    printf("Fecha de Alta: ");
    imprimirFecha(n->fechaAlta);
}


//eliminar usuario/nodo
void eliminarUsuario(listaUsuarios* l, int id) {
    usuario* eliminar = buscarIDUsuarios(l, id);
    if (eliminar == NULL) {
        printf("El ID solicitado no se encuentra en la lista.\n");
        printf("El usuario no se elimino.\n");
        return;
    }

    usuario* aux = l->inicio;
    if (aux == eliminar) {
        l->inicio = aux->sgte;
        free(eliminar);
        printf("Usuario eliminado.\n");
        return;
    }

    while (aux != NULL && aux->sgte != eliminar) {
        aux = aux->sgte;
    }

    if (aux != NULL) {
        aux->sgte = eliminar->sgte;
        printf("Usuario eliminado.\n");
        free(eliminar);
        return;
    }

    printf("No se pudo eliminar el usuario.\n");
}
//busca id a eliminar
usuario *buscarIDUsuarios(listaUsuarios *l, int id){
    usuario *aux = l->inicio;
    while (aux != NULL){
        if (aux->idUsuario == id){
            return aux;
        }
        aux = aux->sgte;
    }
    return NULL;
}

//liberar 
void eliminarListaUsuarios(listaUsuarios* l) {
    usuario* aux = l->inicio;
    usuario* aux2;
    while (aux != NULL) {
        aux2 = aux->sgte;
        free(aux);
        aux = aux2;
    }
    l->inicio = NULL;
    printf("Lista eliminada.\n");
}

//guardar en archivo csv desde memoria
void guardarUsuariosEnCSV(listaUsuarios* lista) {
    FILE* archivo = fopen("usuarios.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    usuario* actual = lista->inicio;

    // Escribir los datos de los usuarios en el archivo CSV
    while (actual != NULL) {
        fprintf(archivo, "%d,%s,%ld\n", actual->idUsuario, actual->apellidoNombre, actual->fechaAlta);
        actual = actual->sgte;
    }

    fclose(archivo);
    printf("Datos guardados en usuarios.csv\n");
}

//cargar memoria desde archivo csv
void cargarUsuariosDesdeCSV(listaUsuarios* lista) {
    FILE* archivo = fopen("usuarios.csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }


    // Leer los datos de los usuarios desde el archivo CSV
    while (!feof(archivo)) {
        usuario* nuevoUsuario = crearUsuario();

        fscanf(archivo, "%d,%[^,],%ld\n", &nuevoUsuario->idUsuario, nuevoUsuario->apellidoNombre, &nuevoUsuario->fechaAlta);
        if(ultimoID_Usuarios < nuevoUsuario->idUsuario) ultimoID_Usuarios = nuevoUsuario->idUsuario;
        insertarUsuarios(lista, nuevoUsuario);
    }

    fclose(archivo);
    printf("Datos cargados desde usuarios.csv\n");
}



//-----FUNCIONES LEC MEDIDORES-----
void mainMedidores (){
    listaCMedidores *lista = crearListaC_Medidores();
    menuMedidores(lista);
    eliminarListaMedidores(lista);
    free(lista);
}

//menu
void menuMedidores(listaCMedidores* lista) {
    int opcion, id;
    cargarMedidoresDesdeCSV(lista);
    do {
    	puts("\n\n\t-----MENU MEDIDORES-----\n");
        for(i=0;i<6;i++)
    		printf("%s\n",optionMedidores[i]);
        scanf("%d", &opcion);
		puts("");
        switch (opcion) {
            case 1:		cargarMedidor(lista);	break; 
            case 2:		leerMedidores(lista);	break;    
            case 3: 
                printf("Ingrese ID de Medidor a eliminar: ");
                scanf("%d", &id);
                eliminarMedidores(lista, id);
                break;
            case 4:
                printf("Ingrese ID de Medidor a buscar: ");
                scanf("%d", &id);
                medidor *n = buscarIDMedidores(lista,id);
                if (n != NULL) {
                    printf("Medidor encontrado: \n");
                    imprimirMedidor(n);
                } else 
                    printf("No se encontro el medidor\n"); 
                break;
            case 0:
                printf("Saliendo del programa...\n");
                guardarMedidoresEnCSV(lista);
                break;
                
            default:
                printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);
}

//carga de datos
void cargarMedidor(listaCMedidores* l) {
    int numero;
    printf("Ingrese Numero de Medidor (0 para terminar): ");
    scanf("%d", &numero);
    while (numero != 0) {
        ultimoID_Medidores++; // Incrementar el ultimo ID
        medidor* nuevoMedidor = crearMedidor();
        nuevoMedidor->idMedidor = ultimoID_Medidores;
        nuevoMedidor->numero = numero;
        getchar();
        printf("Ingrese Modelo: ");
        fgets(nuevoMedidor->modelo, sizeof(nuevoMedidor->modelo), stdin);
        nuevoMedidor->modelo[strcspn(nuevoMedidor->modelo, "\n")] = '\0';
        insertarOrdMedidores(l, nuevoMedidor);
        printf("Ingrese Numero de Medidor (0 para terminar): ");
        scanf("%d", &numero);
    }
}

//insertar nodo en lista
void insertarOrdMedidores(listaCMedidores *p, medidor *n) {
    if (n != NULL) {
        if (p->cabeza == NULL) {
            p->cabeza = n;
            n->sgte = p->cabeza;
        } else if (n->idMedidor < p->cabeza->idMedidor) {
            medidor *ultimo = p->cabeza;
            while (ultimo->sgte != p->cabeza) {
                ultimo = ultimo->sgte;
            }
            n->sgte = p->cabeza;
            p->cabeza = n;
            ultimo->sgte = n;
        } else {
            medidor *aux = p->cabeza;
            while (aux->sgte != p->cabeza && aux->sgte->idMedidor < n->idMedidor) {
                aux = aux->sgte;
            }
            n->sgte = aux->sgte;
            aux->sgte = n;
        }
    }
}

//eliminar medidor/nodo de lista
void eliminarMedidores(listaCMedidores* l, int id) {
    
    medidor* eliminar = buscarIDMedidores(l, id);
    if (eliminar == NULL) {
        printf("El ID solicitado no se encuentra en la lista.\n");
        printf("El medidor no se elimino.\n");
        return;
    }

    medidor* aux = l->cabeza;
    if (aux == eliminar) {
        l->cabeza = aux->sgte;
        free(eliminar);
        printf("Medidor eliminado.\n");
        return;
    }

    while (aux != NULL && aux->sgte != eliminar) {
        aux = aux->sgte;
    }

    if (aux != NULL) {
        aux->sgte = eliminar->sgte;
        printf("Medidor eliminado.\n");
        free(eliminar);
        return;
    }

    printf("No se pudo eliminar el medidor.\n");
}
//buscar id de medidor a eliminar
medidor* buscarIDMedidores(listaCMedidores *l, int id) {
    medidor *aux = l->cabeza;
    if (aux == NULL) {
        printf("Lista vacia..\n");
        return NULL; // La lista esta vacia
    }
    do {
        if (aux->idMedidor == id) {
            return aux; // Se encontro el nodo con el ID buscado
        }
        aux = aux->sgte;
    } while (aux != l->cabeza);
    return NULL; // No se encontro el nodo con el ID buscado
}


//imprime informacion de medidor
void imprimirMedidor(medidor *n){
    printf("ID del Medidor: %d\nNumero: %d\nModelo: %s\n", n->idMedidor, n->numero, n->modelo);
}

//liberar lista
void eliminarListaMedidores(listaCMedidores *p){
    medidor* aux = p->cabeza;
    medidor* aux2;
    while (aux != NULL && aux2 != p->cabeza) {
        aux2 = aux->sgte;
        free(aux);
        aux = aux2;
    }
    p->cabeza = NULL;
    printf("Lista eliminada.\n");
}

//guardar en archivo csv desde memoria
void guardarMedidoresEnCSV(listaCMedidores* lista) {
    FILE* archivo = fopen("medidores.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    medidor* actual = lista->cabeza;

    // Escribir los datos de los medidores en el archivo CSV
    do {
        fprintf(archivo, "%d,%d,%s\n", actual->idMedidor, actual->numero, actual->modelo);
        actual = actual->sgte;
    } while (actual != lista->cabeza);

    fclose(archivo);
    printf("Datos guardados en medidores.csv\n");
}

//cargar memoria/lista desde archivo csv
void cargarMedidoresDesdeCSV(listaCMedidores* lista) {
    FILE* archivo = fopen("medidores.csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    // Leer los datos de los usuarios desde el archivo CSV
    while (!feof(archivo)) {
        medidor* nuevoMedidor = crearMedidor();

        fscanf(archivo, "%d,%d,%s\n", &nuevoMedidor->idMedidor, &nuevoMedidor->numero, nuevoMedidor->modelo);
        if(ultimoID_Medidores < nuevoMedidor->idMedidor) ultimoID_Medidores = nuevoMedidor->idMedidor;
        insertarOrdMedidores(lista, nuevoMedidor);
    }

    fclose(archivo);
    printf("Datos cargados desde medidores.csv\n");
}

//inicializa lista medidor
listaCMedidores* crearListaC_Medidores(){
    listaCMedidores *l = malloc(sizeof(listaCMedidores));
    l->cabeza = NULL;
    return l;
}
//reserva espacio para nuevo medidor
medidor* crearMedidor(){
    medidor* nuevoMedidor = (medidor*) malloc(sizeof(medidor));
    nuevoMedidor->sgte = NULL;
    return nuevoMedidor;
}

//imprimir lista de medidores
void leerMedidores(listaCMedidores *l){
    medidor *aux = l->cabeza;
    if (aux == NULL){
        printf("La lista esta vacia.\n");
        return;
    }
    do{
        imprimirMedidor(aux);
        aux = aux->sgte;
    }while (aux != NULL && aux != l->cabeza);
}

//imprimir fecha dd/mm/yyyy
void imprimirFecha(long int fecha) {
    if (fecha != 0)
    {
        int dia = fecha % 100;
        int mes = (fecha / 100) % 100;
        int anio = fecha / 10000;
        printf("%02d/%02d/%04d\n", dia, mes, anio);
    }else printf("-\n");
}
    

//-----FUNCIONES LES FACTURA-----
void mainFacturas() {
    ListaEnlazadaFactura* lista = crearListaEnlazadaFactura();
    menuFactura(lista);
    eliminarListaEnlazadaFactura(lista);
    free(lista);
}

//menu
void menuFactura(ListaEnlazadaFactura* lista) {
    int opcion;
    do {
    	puts("\n\n\t-----MENU FACTURAS-----\n");
        for(i=0;i<4;i++)
    		printf("%s\n",optionFacturas[i]);
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);
        puts("");

        switch (opcion) {
            case 1:		generarFacturas(lista);		break;
            case 2:		leerFactura(lista);			break;
            case 0:		printf("Saliendo...\n");	break;
            default:
                printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);
    guardarFacturaEnCSV(lista);
}

//inicializa lista de factura
ListaEnlazadaFactura *crearListaEnlazadaFactura(){
    ListaEnlazadaFactura *l = malloc(sizeof(ListaEnlazadaFactura));
    l->inicio = NULL;
    return l;
}
//reserva espacio para nueva factura
Factura *crearFactura(){
    Factura *n = malloc(sizeof(Factura));
    n->sgte = NULL;
    return n;
}

//vacia
bool vaciaListaEnlazadaFactura(ListaEnlazadaFactura *l){
    return l->inicio == NULL;
}

//carga de datos en factura
void generarFacturas(ListaEnlazadaFactura* l_facturas) {
    int periodo = 0;
    ListaLDE *l_mediciones = malloc(sizeof(ListaLDE));
    l_mediciones->primero = NULL;
    l_mediciones->ultimo = NULL;
    LESCostos *l_costos = crearListaCostos();
    LESMedXUsuarios *l_medxusuarios = crearLESMedXUsuarios();
    cargarMedicionesDesdeCSV(l_mediciones);
    cargarCostosDesdeCSV(l_costos);
    cargarMedXUsuariosDesdeCSV(l_medxusuarios);
    NodoMedXUsuarios *n_medxusuarios = l_medxusuarios->inicio;
    deudores *raiz = malloc(sizeof(deudores));
    raiz->der = NULL;
    raiz->izq = NULL;
    
    while (n_medxusuarios != NULL){
        periodo = 0;
        Factura *n_factura = crearFactura();
        n_factura->idCuenta = n_medxusuarios->idCuenta;
        n_factura->consumo = encontrarConsumo(l_mediciones, n_medxusuarios->idCuenta, &periodo);
        
		if (n_factura->consumo != 0){
            n_factura->fechaEmision = obtenerFechaActual();
            n_factura->periodo = periodo;
            n_factura->totalPagar = obtenerTotalAPagar(l_costos,n_factura->consumo);
            printf("Cuenta %d: ", n_factura->idCuenta);
            printf("Ingrese la fecha de pago (0 si adeuda, 1 para marcar como pagado): ");
            scanf("%ld",&n_factura->pagada);
            if(n_factura->pagada != 0) n_factura->pagada = obtenerFechaActual();
            
            if (n_factura->pagada == 0){
                deudores *nuevo = malloc(sizeof(deudores));
                nuevo->der = NULL;
                nuevo->izq = NULL;
                char apellidoNombreUsuario[60];
                buscarNombreUsuario(n_medxusuarios->idUsuario, apellidoNombreUsuario);
                strcpy(nuevo->apellidoNombre, apellidoNombreUsuario);
                insertarOrdDeudores(raiz, nuevo);
            }
            insertarFactura(l_facturas, n_factura);
        }else 
			free(n_factura);
			
        n_medxusuarios = n_medxusuarios->sgte;
    }
    printf("Lista de deudores: \n");
    imprimirDeudores(raiz);
    liberarDeudores(raiz);
    
}

void buscarNombreUsuario(int idUsuario, char *str){
    listaUsuarios *lista = crearListaUsuarios();
    cargarUsuariosDesdeCSV(lista);
    usuario *nodo = lista->inicio;
    while (nodo != NULL){
        if (nodo->idUsuario == idUsuario){   
            strcpy(str, nodo->apellidoNombre);
            eliminarListaUsuarios(lista);
            return;
        }
        nodo = nodo->sgte;
    }
    eliminarListaUsuarios(lista);
    return;
}

//total a pagar, para cargar factura
float obtenerTotalAPagar(LESCostos *l_costos,int consumo) {
    Costo *n_costos = l_costos->inicio;
    float ultimoCosto = 0, total = 0;
    if (consumo < 0){
        printf("ERROR!!\n");
        return 0;
    }
    while (n_costos != NULL){
        ultimoCosto = n_costos->valorMetro;
        if (n_costos->mtsDesde <= consumo && n_costos->mtsHasta > consumo){
            total = (float)consumo*n_costos->valorMetro;
            return total;
        }
        n_costos = n_costos->sgte;
    }
    
    total = (float)consumo*ultimoCosto;
    return total;
}
//fecha actual, para cargar factura
long int obtenerFechaActual() {
    time_t t = time(NULL);
    struct tm *current_time = localtime(&t);

    int year = current_time->tm_year + 1900;
    int month = current_time->tm_mon + 1;
    int day = current_time->tm_mday;

    long int fecha = year * 10000 + month * 100 + day;
    return fecha;
}
//consumo realizado, para cargar factura
int encontrarConsumo(ListaLDE *l_mediciones, int idCuenta, int *max1) {
    int max2, consumomax1, consumomax2;
    NodoLDE* current = l_mediciones->primero;
    
	if (current == NULL) 
        return 0;
    else {
        *max1 = 0;
        max2 = 0;
        consumomax1 = 0;
        consumomax2 = 0;
        int x = 0;
        do {
            if (x == 1)
                current = current->sgte;
            
            if (current->idCuenta == idCuenta) {
                if (current->periodo > *max1) {
                    max2 = *max1;
                    consumomax2 = consumomax1;
                    *max1 = current->periodo;
                    consumomax1 = current->lectura;
                }
                else if (current->periodo > max2 && current->periodo != *max1) {
                    max2 = current->periodo;
                    consumomax2 = current->lectura;
                }
            }
            x = 1;
        }while (current != l_mediciones->ultimo);
    }
    
    if (*max1 == 0 || max2 == 0) 
        return 0;
    
    return consumomax1 - consumomax2;  
}

//insertar factura/nodo en lista
void insertarFactura(ListaEnlazadaFactura *l, Factura *n) {
    if (vaciaListaEnlazadaFactura(l)) {
        l->inicio = n;
    } else if (n->idCuenta < l->inicio->idCuenta) {
        n->sgte = l->inicio;
        l->inicio = n;
    } else {
        Factura* aux = l->inicio;
        while (aux->sgte != NULL && aux->sgte->idCuenta < n->idCuenta) {
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
}

//imprimir lista
void leerFactura(ListaEnlazadaFactura *l){
    Factura *aux = l->inicio;
    while (aux != NULL){
        imprimirFactura(aux);
        aux = aux->sgte;
    }
}
//imprimir datos de factura/nodo
void imprimirFactura(Factura *n){
    printf("\n");
    printf("ID Factura: %d\n", n->idCuenta);
    printf("Periodo: %d\n",n->periodo);
    printf("Fecha de emision: ");
    imprimirFecha(n->fechaEmision);
    printf("Fecha de pago: ");
    imprimirFecha(n->pagada);
    printf("Consumo: %d m^3\n", n->consumo);
    printf("Total a Pagar: $%.2f\n\n", n->totalPagar);
}

//eliminar factura/nodo
void eliminarFactura(ListaEnlazadaFactura* l, int id) {
    Factura* eliminar = buscarIDFactura(l, id);
    if (eliminar == NULL) {
        printf("El ID solicitado no se encuentra en la lista.\n");
        printf("La Factura no se elimino.\n");
        return;
    }

    Factura* aux = l->inicio;
    if (aux == eliminar) {
        l->inicio = aux->sgte;
        free(eliminar);
        printf("Factura eliminada.\n");
        return;
    }

    while (aux != NULL && aux->sgte != eliminar) {
        aux = aux->sgte;
    }

    if (aux != NULL) {
        aux->sgte = eliminar->sgte;
        printf("Factura eliminada.\n");
        free(eliminar);
        return;
    }

    printf("No se pudo eliminar la Factura.\n");
}
//buscar id a eliminar
Factura *buscarIDFactura(ListaEnlazadaFactura *l, int id){
    Factura *aux = l->inicio;
    while (aux != NULL){
        if (aux->idCuenta == id){
            return aux;
        }
        aux = aux->sgte;
    }
    return NULL;
}

//liberar memeoria 
void eliminarListaEnlazadaFactura(ListaEnlazadaFactura* l) {
    Factura* aux = l->inicio;
    Factura* aux2;
    while (aux != NULL) {
        aux2 = aux->sgte;
        free(aux);
        aux = aux2;
    }
    l->inicio = NULL;
    printf("Lista eliminada.\n");
}

//guardar en archivo csv desde memoria
void guardarFacturaEnCSV(ListaEnlazadaFactura* lista) {
    FILE* archivo = fopen("Factura.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    Factura* actual = lista->inicio;

    // Escribir los datos de los Factura en el archivo CSV
    while (actual != NULL) {
        fprintf(archivo, "%d,%d,%ld,%d,%f,%ld\n", actual->idCuenta, actual->periodo, actual->fechaEmision, actual->consumo, actual->totalPagar, actual->pagada);
        actual = actual->sgte;
    }

    fclose(archivo);
    printf("Datos guardados en Factura.csv\n");
}


//---FUNCIONES PARA ARBOL DE DEUDORES---

//imprime lista/arbol de deudores
void imprimirDeudores(deudores *raiz){
    if (raiz != NULL){
        imprimirDeudores(raiz->der);
        printf("%s\n", raiz->apellidoNombre);
        imprimirDeudores(raiz->izq);
    }
}
//libera lista/arbol de deudores
void liberarDeudores(deudores* raiz){
    if(raiz != NULL){
        liberarDeudores(raiz->der);
        liberarDeudores(raiz->izq);
        free(raiz);
    }
}
//insertar en lista/arbol de deudores
void insertarOrdDeudores(deudores* raiz, deudores *actual){
    if (raiz == NULL){
        raiz = actual;
        return;
    }
    if (strcmp(actual->apellidoNombre,raiz->apellidoNombre) > 0) {
        if (raiz->izq == NULL) 
            raiz->izq = actual;
        else 
            insertarOrdDeudores(raiz->izq, actual);
    } else {
        if (raiz->der == NULL) 
            raiz->der = actual;
        else 
            insertarOrdDeudores(raiz->der, actual);
    }
}



//-----FUNCIONES LES MEDXUSUARIOS-----
void mainMedXUsuarios(){
    LESMedXUsuarios *lista = crearLESMedXUsuarios();
    menuMedXUsuarios(lista);
    eliminarLESMedXUsuarios(lista);
    free(lista);
}

//menu
void menuMedXUsuarios(LESMedXUsuarios* lista) {
    int opcion, id;
    cargarMedXUsuariosDesdeCSV(lista);
    do {
    	puts("\n\n\t-----MENU MEDxUSUARIOS-----\n");
        for(i=0;i<6;i++)
    		printf("%s\n",optionMedXUsuarios[i]);
        printf("Ingrese la opcion deseada: ");
        scanf("%d", &opcion);
		puts("");
        switch (opcion) {
            case 1:		cargarMedXUsuarios(lista);	break;
            case 2:		leerMedXUsuarios(lista);	break;
            case 3: {
                printf("Ingrese ID de Cuenta a eliminar: ");
                scanf("%d", &id);
                eliminarNodoMedXUsuarios(lista, id);
                break;
            }
            case 4:
                printf("Ingrese ID de Cuenta a buscar: ");
                scanf("%d", &id);
                NodoMedXUsuarios *n = buscarIDMedXUsuarios(lista,id);
                if (n != NULL) {
                    printf("Cuenta encontrada: \n");
                    imprimirMedXUsuarios(n);
                } else 
                    printf("No se encontro el usuario\n");
                break;
            case 0:
                printf("Saliendo del programa...\n");
                guardarMedXUsuariosEnCSV(lista);
                break;
            default:
                printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    } while (opcion != 0);
}

//inicializar lista
LESMedXUsuarios *crearLESMedXUsuarios(){
    LESMedXUsuarios *l = malloc(sizeof(LESMedXUsuarios));
    l->inicio = NULL;
    return l;
}
//reserva espacio para nuevo nodo
NodoMedXUsuarios *crearNodoMedXUsuarios(){
    NodoMedXUsuarios *n = malloc(sizeof(NodoMedXUsuarios));
    n->sgte = NULL;
    return n;
}

//vacia
bool vaciaLESMedXUsuarios(LESMedXUsuarios *l){
    return l->inicio == NULL;
}

//carga de datos
void cargarMedXUsuarios(LESMedXUsuarios* l) {
    int idUsuario, idMedidor;
    long int fechaAlta;
    printf("Ingrese ID de Usuario (0 para terminar): ");
    scanf("%d",&idUsuario);
    while (idUsuario != 0){
        if((fechaAlta = verifUsuario(idUsuario)) != 0){
            ultimoID_MedXUsuarios++; // Incrementar el ultimo ID
            NodoMedXUsuarios* nuevoMedXUsuarios = crearNodoMedXUsuarios();
            nuevoMedXUsuarios->idCuenta = ultimoID_MedXUsuarios;
            nuevoMedXUsuarios->fechaAlta = fechaAlta;
            printf("Ingrese ID de Medidor (0 para terminar): ");
            scanf("%d",&idMedidor);
            while (idMedidor != 0){
                if(verifMedidor(idMedidor)){
                    
                    printf("Ingrese Fecha de Baja (de existir, sino 0)//aaaammdd//: ");
                    scanf("%ld", &nuevoMedXUsuarios->fechaBaja);
                    nuevoMedXUsuarios->idMedidor = idMedidor;
                    nuevoMedXUsuarios->idUsuario = idUsuario;
                    insertarMedXUsuarios(l, nuevoMedXUsuarios);
                }
                printf("Ingrese ID de Medidor (0 para terminar): ");
                scanf("%d",&idMedidor);
            }
        }
        printf("Ingrese ID de Usuario (0 para terminar): ");
        scanf("%d",&idUsuario);
    }
}
//verificar si medidor existe
bool verifMedidor(int idMedidor){
    listaCMedidores *lista = crearListaC_Medidores();
    cargarMedidoresDesdeCSV(lista);
    medidor *m = buscarIDMedidores(lista, idMedidor);
    if (m != NULL){
        printf("Numero: %d\nModelo: %s\n",m->numero,m->modelo);
        return true;
    }else{
        printf("Medidor no existe.\n");
        printf("Seleccione entre los siguientes: \n");
        leerMedidores(lista);
        return false;
    }
    
    eliminarListaMedidores(lista);
    free(m);
    free(lista);
}
//verificar si usuario existe
long int verifUsuario(int idUsuario){
    listaUsuarios *lista = crearListaUsuarios();
    cargarUsuariosDesdeCSV(lista);
    usuario *u = buscarIDUsuarios(lista, idUsuario);
    if (u != NULL)
    {
        printf("Nombre: %s\n",u->apellidoNombre);
        return u->fechaAlta;
    }else{
        printf("Usuario no existe.\n");
        printf("Seleccione entre los siguientes: \n");
        leerUsuarios(lista);
        return 0;
    }
    
    eliminarListaUsuarios(lista);
    free(u);
    free(lista);
}

//insertar nodo en lista
void insertarMedXUsuarios(LESMedXUsuarios *l, NodoMedXUsuarios *n) {
    if (vaciaLESMedXUsuarios(l)) {
        l->inicio = n;
    } else if (n->idCuenta < l->inicio->idCuenta) {
        n->sgte = l->inicio;
        l->inicio = n;
    } else {
        NodoMedXUsuarios* aux = l->inicio;
        while (aux->sgte != NULL && aux->sgte->idCuenta < n->idCuenta) {
            aux = aux->sgte;
        }
        n->sgte = aux->sgte;
        aux->sgte = n;
    }
}

//imprimir lista
void leerMedXUsuarios(LESMedXUsuarios *l){
    NodoMedXUsuarios *aux = l->inicio;
    while (aux != NULL){
        imprimirMedXUsuarios(aux);
        aux = aux->sgte;
    }
}

//eliminar nodo
void eliminarNodoMedXUsuarios(LESMedXUsuarios* l, int id) {
    NodoMedXUsuarios* eliminar = buscarIDMedXUsuarios(l, id);
    if (eliminar == NULL) {
        printf("El ID solicitado no se encuentra en la lista.\n");
        printf("La Cuenta no se elimino.\n");
        return;
    }

    NodoMedXUsuarios* aux = l->inicio;
    if (aux == eliminar) {
        l->inicio = aux->sgte;
        free(eliminar);
        printf("Cuenta eliminada.\n");
        return;
    }

    while (aux != NULL && aux->sgte != eliminar) {
        aux = aux->sgte;
    }

    if (aux != NULL) {
        aux->sgte = eliminar->sgte;
        printf("Cuenta eliminada.\n");
        free(eliminar);
        return;
    }

    printf("No se pudo eliminar la cuenta.\n");
}
//buscar nodo a eliminar
NodoMedXUsuarios *buscarIDMedXUsuarios(LESMedXUsuarios *l, int id){
    NodoMedXUsuarios *aux = l->inicio;
    while (aux != NULL){
        if (aux->idCuenta == id){
            return aux;
        }
        aux = aux->sgte;
    }
    return NULL;
}

//liberar lista
void eliminarLESMedXUsuarios(LESMedXUsuarios* l) {
    NodoMedXUsuarios* aux = l->inicio;
    NodoMedXUsuarios* aux2;
    while (aux != NULL) {
        aux2 = aux->sgte;
        free(aux);
        aux = aux2;
    }
    l->inicio = NULL;
    printf("Lista eliminada.\n");
}


//guardar en archivo csv desde memoria/lista
void guardarMedXUsuariosEnCSV(LESMedXUsuarios* lista) {
    FILE* archivo = fopen("MedXUsuarios.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    NodoMedXUsuarios* actual = lista->inicio;

    // Escribir los datos de los MedXUsuarios en el archivo CSV
    while (actual != NULL) {
        fprintf(archivo, "%d,%d,%d,%ld,%ld\n",actual->idCuenta,actual->idMedidor,actual->idUsuario,actual->fechaAlta,actual->fechaBaja);
        actual = actual->sgte;
    }

    fclose(archivo);
    printf("Datos guardados en MedXUsuarios.csv\n");
}

//cargar lista/memoria desde archivo csv
void cargarMedXUsuariosDesdeCSV(LESMedXUsuarios* lista) {
    FILE* archivo = fopen("MedXUsuarios.csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }


    // Leer los datos de los MedXUsuarios desde el archivo CSV
    while (!feof(archivo)) {
        NodoMedXUsuarios* nuevoMedXUsuarios = crearNodoMedXUsuarios();

        fscanf(archivo, "%d,%d,%d,%ld,%ld\n",&nuevoMedXUsuarios->idCuenta,&nuevoMedXUsuarios->idMedidor,&nuevoMedXUsuarios->idUsuario,&nuevoMedXUsuarios->fechaAlta,&nuevoMedXUsuarios->fechaBaja);
        if(ultimoID_MedXUsuarios < nuevoMedXUsuarios->idCuenta) ultimoID_MedXUsuarios = nuevoMedXUsuarios->idCuenta;
        insertarMedXUsuarios(lista, nuevoMedXUsuarios);
    }

    fclose(archivo);
    printf("Datos cargados desde MedXUsuarios.csv\n");
}

//imprimir datos del nodo
void imprimirMedXUsuarios(NodoMedXUsuarios *n){
    printf("\n");
    printf("ID Usuario: %d\n", n->idUsuario);
    printf("ID Medidor: %d\n", n->idMedidor);
    printf("ID Cuenta: %d\n", n->idCuenta);
    printf("Fecha de Alta: ");
    imprimirFecha(n->fechaAlta);
    printf("Fecha de Baja: ");
    imprimirFecha(n->fechaBaja);
}



//-----FUNCIONES LDE MEDICIONES-----
void mainMediciones(){
    ListaLDE *cabeza = malloc(sizeof(ListaLDE));
    menuMediciones(cabeza);
}

//menu
void menuMediciones(ListaLDE *cabeza){
    iniMediciones(cabeza);
    cargarMedicionesDesdeCSV(cabeza);
    int opcion;NodoLDE *nuevoNodo;
    do{
        puts("\n\n\t-----MENU MEDICIONES-----\n");
        for(i=0;i<6;i++)
    		printf("%s\n",optionMedicion[i]);
    	printf("Ingrese la opcion deseada: ");
        scanf("%d",&opcion);
        puts("");
        switch(opcion){
            case 1:
	            nuevoNodo = crearNodoMediciones();
	            insertarMediciones(cabeza,nuevoNodo);
	            break;
        	case 2:		imprimirMediciones(cabeza);	break;
        	case 3:		buscarMediciones(cabeza);	break;
        	case 4:		eliminarMediciones(cabeza);	break;
        	case 0:		
				printf("Saliendo del programa...\n");
                break;
            default: 
            	printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    }while(opcion!=0);
    guardarMedicionesEnCSV(cabeza);
    liberarMedicionesLista(cabeza);
    free(nuevoNodo);
}

//cargar lista/memoria desde archivo csv
void cargarMedicionesDesdeCSV(ListaLDE *cabeza) {
    FILE* archivo = fopen("mediciones.csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    // Leer los datos de los usuarios desde el archivo CSV
    while (!feof(archivo)) {
        NodoLDE* nuevaMedicion = malloc(sizeof(NodoLDE));

        fscanf(archivo, "%d,%d,%ld,%d\n", &nuevaMedicion->idCuenta,&nuevaMedicion->periodo,&nuevaMedicion->fechaLectura,&nuevaMedicion->lectura);
        insertarMediciones(cabeza, nuevaMedicion);
    }

    fclose(archivo);
    printf("Datos cargados desde usuarios.csv\n");
}

//inicializar lista
void iniMediciones(struct ListaLDE *l){
    l->primero = NULL;
    l->ultimo = NULL;
    l->n = 0;
}
//reserva espacio y carga un nuevo nodo/medicion
NodoLDE* crearNodoMediciones(){
    NodoLDE *p = (NodoLDE*)malloc(sizeof(NodoLDE));
    do{
        printf("Ingrese el id de Cuenta (0 para terminar): ");
        scanf("%d", &p->idCuenta);
        if (p->idCuenta == 0) 
			return NULL;
    } while (!verifCuenta(p->idCuenta));
    printf("Ingrese el periodo actual: ");
    scanf("%d", &p->periodo);
    p->fechaLectura = ((long int)(p->periodo * 100) + 101);
    printf("Fecha de lectura: %ld\n",p->fechaLectura);
    printf("Ingrese la lectura (m^3): ");
    scanf("%d", &p->lectura);
    p->sgte = NULL;
    p->anterior = NULL;
    return p;
}

//verifica si el id de cuenta existe en MedXUsuarios
bool verifCuenta(int idCuenta){
    LESMedXUsuarios *lista = crearLESMedXUsuarios();
    cargarMedXUsuariosDesdeCSV(lista);
    NodoMedXUsuarios *n = buscarIDMedXUsuarios(lista, idCuenta);
    if (n != NULL){
        if (n->fechaBaja != 0){
            printf("Cuenta dada de baja el dia ");
            imprimirFecha(n->fechaBaja);
            return false;
        }
        printf("Cuenta numero %d: \n",idCuenta);
        printf("ID Usuario: %d, ID Medidor: %d\n",n->idUsuario, n->idMedidor);
        return true;
    }else{
        printf("Medidor no existe.\n");
        printf("Seleccione entre los siguientes: \n");
        leerMedXUsuarios(lista);
        return false;
    }
    
    eliminarLESMedXUsuarios(lista);
    free(n);
    free(lista);
}

//insertar nuevo nodo/medicion en lista
void insertarMediciones(ListaLDE *l, NodoLDE *nuevoNodo){
    if (nuevoNodo == NULL) 
		return;
    if (l->primero == NULL){
        l->primero = nuevoNodo;
        l->ultimo = nuevoNodo;
    } else if (nuevoNodo->fechaLectura <l->primero->fechaLectura){
        nuevoNodo->sgte = l->primero;
        l->primero->anterior = nuevoNodo;
        l->primero = nuevoNodo;
    } else if (nuevoNodo->fechaLectura >= l->ultimo->fechaLectura){
        nuevoNodo->anterior = l->ultimo;
        l->ultimo->sgte = nuevoNodo;
        l->ultimo = nuevoNodo;
    } else {
        NodoLDE* actual = l->primero->sgte;
        while (actual != NULL){
            if (nuevoNodo->fechaLectura < actual->fechaLectura){
                nuevoNodo->anterior = actual->anterior;
                nuevoNodo->sgte = actual;
                actual->anterior->sgte = nuevoNodo;
                actual->anterior = nuevoNodo;
                break;
            }
            actual = actual->sgte;
        }
    }
    l->n++;
}

//busca una medicion y la imprime
void buscarMediciones(ListaLDE* L) {
    int id;
    printf("Ingrese el ID buscado: "); scanf("%d",&id);
    if (L->primero == NULL)
    {
        printf("La lista esta vacia.\n");
        return;
    }
    int band = 0;
    NodoLDE* actual = L->primero;
    int x = 0;
    do{
        if(x) 
            actual = actual->sgte;
        
        if (actual->idCuenta == id){
            printf("Nodo encontrado: ID Cuenta: %d, Periodo: %d, Lectura: %d, Fecha Lectura: ",
            actual->idCuenta, actual->periodo, actual->lectura);
            imprimirFecha(actual->fechaLectura);
            band = 1;
        }
        x = 1;
    } while (actual != L->ultimo);
    if(band == 0) printf("La Cuenta con ID %d no se encontró en la lista\n", id);
}

//imprimir lista de mediciones
void imprimirMediciones(ListaLDE* L) {
    NodoLDE* actual = L->primero;
    if (actual == NULL){
        printf("La lista esta vacia.\n");
        return;
    }
    while (actual != L->ultimo) {
        printf("ID Cuenta: %d, Periodo: %d, Lectura: %d, Fecha Lectura: ", actual->idCuenta, actual->periodo, actual->lectura);
        imprimirFecha(actual->fechaLectura);
        actual = actual->sgte;
    }
    printf("ID Cuenta: %d, Periodo: %d, Lectura: %d, Fecha Lectura: ", actual->idCuenta, actual->periodo, actual->lectura);
    imprimirFecha(actual->fechaLectura);
}

//busca una medicion y la elimina
void eliminarMediciones(ListaLDE* L) {
    NodoLDE* actual = L->primero;
    int id;
    puts("Ingrese el ID a eliminar: ");
    scanf("%d", &id);
    while (actual != NULL) {
        if (actual->idCuenta == id) {
            if (actual == L->primero) {
                L->primero = actual->sgte;
                if (L->primero != NULL) {
                    L->primero->anterior = NULL;
                }
            } else if (actual == L->ultimo) {
                L->ultimo = actual->anterior;
                if (L->ultimo != NULL) 
                    L->ultimo->sgte = NULL;
                
            } else {
                actual->anterior->sgte = actual->sgte;
                actual->sgte->anterior = actual->anterior;
            }
            
            free(actual);
            L->n--;
            printf("Cuenta %d eliminada.\n", id);
            return;
        }
        
        actual = actual->sgte;
    }
    
    printf("Cuenta %d no encontrada.\n", id);
}

//guardar en archivo csv desde lista/memoria
void guardarMedicionesEnCSV(ListaLDE* lista) {
    FILE* archivo = fopen("mediciones.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return;
    }

    NodoLDE* actual = lista->primero;

    // Escribir los datos de los usuarios en el archivo CSV
    while (actual != NULL) {
        fprintf(archivo, "%d,%d,%ld,%d\n", actual->idCuenta,actual->periodo,actual->fechaLectura,actual->lectura);
        actual = actual->sgte;
    }

    fclose(archivo);
    printf("Datos guardados en usuarios.csv\n");
}

//liberar lista
void liberarMedicionesLista(ListaLDE* L) {
    NodoLDE* actual = L->primero;
    
    while (actual != NULL) {
        NodoLDE* siguiente = actual->sgte;
        free(actual);
        actual = siguiente;
    }
    
    L->primero = NULL;
    L->ultimo = NULL;
    L->n = 0;
    
    printf("Todos los nodos han sido liberados.\n");
}


//-----FUNCIONES COSTOS-----
void mainCostos(){
    LESCostos *lista = crearListaCostos();
    menuCostos(lista);
    liberarListaCostos(lista);
    free(lista);
}

//menu
void menuCostos(LESCostos *lista){
    int opcion;
    cargarCostosDesdeCSV(lista);
    do{
    	puts("\n\n\t-----MENU COSTOS-----\n");
        for(i=0;i<4;i++)
    		printf("%s\n",optionCostos[i]);
    	printf("Ingrese la opcion deseada: "); 
        scanf("%d", &opcion);
        puts("");
        switch(opcion){
            case 1:		cargarCosto(lista);			break;
            case 2:		leerCostos(lista);			break;
            case 0:		printf("Saliendo...\n");	break;
            default: 
            	printf("Opcion invalida. Por favor, intente nuevamente.\n");
                break;
        }
    }while(opcion != 0);
    guardarCostosEnCSV(lista);
}

//inicializar lista
LESCostos *crearListaCostos(){
    LESCostos *lista = (LESCostos *)malloc(sizeof(LESCostos));
    lista->inicio = NULL;
    return lista;
}
//reserva espacio para nuevo nodo
Costo *crearCosto(){
    Costo *costo = (Costo *)malloc(sizeof(Costo));
    costo->sgte = NULL;
    return costo;
}

//cargar lista
void cargarCosto(LESCostos *lista){
    int mtsHasta;
    float valorMetro;
    printf("Ingrese hasta cuantos metros (0 para salir, -1 para limite).\n");
    scanf("%d",&mtsHasta);
    while (mtsHasta != 0){
        printf("Ingrese el valor del m^3: ");
        scanf("%f",&valorMetro);
        ultimoID_Costo++; // Incrementar el ultimo ID
        Costo* nuevoCosto = crearCosto();
        nuevoCosto->idCosto = ultimoID_Costo;
        nuevoCosto->mtsDesde = ultimoHasta;
        if (mtsHasta == -1){
            mtsHasta = 0;
            nuevoCosto->mtsHasta = mtsHasta;
            nuevoCosto->valorMetro = valorMetro;
            insertarCostos(lista, nuevoCosto);
            break;
        } else {
            ultimoHasta = mtsHasta;
            nuevoCosto->mtsHasta = mtsHasta;
            nuevoCosto->valorMetro = valorMetro;
            insertarCostos(lista, nuevoCosto);
            printf("Ingrese hasta cuantos metros (0 para salir).\n");
            scanf("%d",&mtsHasta);
        }
    }
}

//insertar nodo en lista
void insertarCostos(LESCostos *lista, Costo *nuevo){
    if (vaciaListaCostos(lista)) {
        lista->inicio = nuevo;
    } else if (nuevo->idCosto < lista->inicio->idCosto) {
        nuevo->sgte = lista->inicio;
        lista->inicio = nuevo;
    } else {
        Costo* aux = lista->inicio;
        while (aux->sgte != NULL && aux->sgte->idCosto < nuevo->idCosto) {
            aux = aux->sgte;
        }
        nuevo->sgte = aux->sgte;
        aux->sgte = nuevo;
    }
}

//vacia
bool vaciaListaCostos(LESCostos *l){
    return l->inicio == NULL;
}

//imprime toda la lista
void leerCostos(LESCostos *lista){
    Costo *aux = lista->inicio;
    while (aux != NULL){
        imprimirCosto(aux);
        aux = aux->sgte;
    }
}
//imprime datos un nodo
void imprimirCosto(Costo *n){
    printf("\n");
    printf("ID Costo: %d\n", n->idCosto);
    printf("Desde %d m^3\n", n->mtsDesde);
    if (n->mtsHasta != 0)
        printf("Hasta %d m^3\n", n->mtsHasta);
    printf("Costo por m^3: $%.2f\n",n->valorMetro);
}

//cargar lista/memoria desde archivo csv
void cargarCostosDesdeCSV(LESCostos *lista){
    FILE* archivo = fopen("costos.csv", "r");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }


    // Leer los datos de los usuarios desde el archivo CSV
    while (!feof(archivo)) {
        Costo* nuevoCosto = crearCosto();

        fscanf(archivo, "%d,%d,%d,%f\n", &nuevoCosto->idCosto, &nuevoCosto->mtsDesde, &nuevoCosto->mtsHasta, &nuevoCosto->valorMetro);
        if(ultimoID_Costo < nuevoCosto->idCosto) ultimoID_Costo = nuevoCosto->idCosto; 
        if(ultimoHasta < nuevoCosto->mtsHasta) ultimoHasta = nuevoCosto->mtsHasta;
        insertarCostos(lista, nuevoCosto);
    }

    fclose(archivo);
    printf("Datos cargados desde costos.csv\n");
}

//guardar en archivo csv desde lista/memoria
void guardarCostosEnCSV(LESCostos *lista){
    FILE* archivo = fopen("costos.csv", "w");
    if (archivo == NULL) {
        printf("No se pudo abrir el archivo.");
        return;
    }

    Costo* actual = lista->inicio;

    // Escribir los datos de los usuarios en el archivo CSV
    while (actual != NULL) {
        fprintf(archivo, "%d,%d,%d,%f\n", actual->idCosto, actual->mtsDesde, actual->mtsHasta, actual->valorMetro);
        actual = actual->sgte;
    }

    fclose(archivo);
    printf("Datos guardados en costos.csv\n");
}

//liberar lista
void liberarListaCostos(LESCostos *lista){
    Costo* aux = lista->inicio;
    Costo* aux2;
    while (aux != NULL) {
        aux2 = aux->sgte;
        free(aux);
        aux = aux2;
    }
    lista->inicio = NULL;
    printf("Lista eliminada.\n");
}

                
