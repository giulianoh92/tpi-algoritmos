#include "funciones.h"
void menuMain();
int main(){
    menuMain();
    return 0;
}

void menuMain(){
    int opcion, i;
    do{
    	puts("\n\t-----MENU DE INICIO-----\n");
    	for(i=0;i<8;i++)
    		printf("%s\n",optionMain[i]);
    	printf("Ingrese la opcion que desea: ");
    	scanf("%d",&opcion);
    	puts("");
    switch (opcion){
	    case 1:		mainUsuarios();		break;
	    case 2:		mainMedidores();	break;
	    case 3:		mainMedXUsuarios();	break;
	    case 4:		mainMediciones();	break;
	    case 5:		mainFacturas();		break;
	    case 6:		mainCostos();		break;
	    case 0:		break;
	    
		default:
	        printf("Opcion invalida. Por favor, intente nuevamente.\n");
	        break;
    }
    }while(opcion!=0);
    printf("Saliendo...\n");
    return;
}
