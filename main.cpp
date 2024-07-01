#include "modoFichasEspeciales.h"
#include "modoContrarreloj.h"
#include "modoIA.h"
#include "modoNormal.h"

int main() 
{
    bool salir = false;
    int opcion;

	printf("Cual jugamos?\n");
    printf("1. Jugador vs Jugador\n");
    printf("2. 2 Jugadores - Fichas Especiales\n");
    printf("3. 1v1 Contra Reloj\n");
    printf("4. Jugador vs Maquina");
	printf("Cual jugamos?: ");
	scanf("%d", &opcion);

    while (!salir) 
	{
        switch (opcion) 
		{
            case 1:
                system("cls");
                juegoNormal();
                break;
                
            case 2:
                system("cls");
                modoEspecial();
                break;
                
            case 3:
                system("cls");
                contraReloj();
                break;
                
            case 4:
            	system("cls");
            	inteligenciaArtifical();
            	break;
                
            case 5:
                printf("Saliendo del programa...");
                salir = true;
                break;
                
            default:
                printf("Opcion invalida. Por favor, seleccione una opcion valida.");
                break;
        }
    }

    return 0;
}
