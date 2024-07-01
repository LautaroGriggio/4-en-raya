// BIBLIOTECAS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>

// DECLARAMOS LOS COLORES (FONDO Y LETRA)
#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T         "\x1b[31m"
#define ROJO_F         "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T 	   "\x1b[38;5;227m"
#define AMARILLO_F     "\x1b[48;5;227m"
#define AZUL_T         "\x1b[34m"
#define AZUL_F         "\x1b[44m"
#define MARRON_T       "\x1b[38;5;94m"
#define MARRON_F       "\x1b[48;5;94m"
#define CYAN_T         "\x1b[38;5;117m"
#define CYAN_F         "\x1b[48;5;117m"
#define BLANCO_T       "\x1b[37m"
#define BLANCO_F       "\x1b[47m"

const int FILAS1 = 6;
const int COLUMNAS1 = 7;
int tablero1[FILAS1][COLUMNAS1];

int i, j;
int jug = 1;
int lugar, columna;

// PARA HACER LAS LINEAS DEL TABLERO
int line1()
{
	for (int k = 0; k < 7; ++k) 
	{
        printf(AZUL_F AZUL_T "+---" RESET_COLOR);
    }
    printf(AZUL_F AZUL_T "+" RESET_COLOR);
    printf("\n");
}


int dibujarTablero1() 
{
	line1();
	
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            printf(AZUL_F AZUL_T "|" RESET_COLOR);
            
            if(tablero1[i][j] == 0)
            {
                printf(BLANCO_F BLANCO_T " %d ", tablero1[i][j]);
            }
            else if(tablero1[i][j] == 1)
            {
                printf(AMARILLO_F AMARILLO_T " %d ", tablero1[i][j]);
            }
            else if(tablero1[i][j] == 2)
            {
                printf(ROJO_F ROJO_T " %d ", tablero1[i][j]);
            }
        }
        printf(AZUL_F AZUL_T "|" RESET_COLOR);
        printf("\n");

        // Imprimir líneas separadoras entre filas
        if (i < 5) {
            line1();
        }
    }
    
    line1();
}


// GANADORES
int verificarGanador1() 
{
    for (i = 0; i < FILAS1; i++) // GANADOR POR FILAS1
    {
        for (j = 0; j <= COLUMNAS1 - 4; j++) 
        {
            if (tablero1[i][j] == 1 && tablero1[i][j + 1] == 1 && tablero1[i][j + 2] == 1 && tablero1[i][j + 3] == 1) 
            {
                return tablero1[i][j];
            }
            else if (tablero1[i][j] == 2 && tablero1[i][j + 1] == 2 && tablero1[i][j + 2] == 2 && tablero1[i][j + 3] == 2) 
            {
                return tablero1[i][j];
            }
        }
    }
    
    for (i = 0; i <= FILAS1 - 4; i++) // GANADOR POR COLUMNAS1
    {
        for (j = 0; j < COLUMNAS1; j++)
        {
            if (tablero1[i][j] == 1 && tablero1[i + 1][j] == 1 && tablero1[i + 2][j] == 1 && tablero1[i + 3][j] == 1) 
            {
                return tablero1[i][j];
            }
            else if (tablero1[i][j] == 2 && tablero1[i + 1][j] == 2 && tablero1[i + 2][j] == 2 && tablero1[i + 3][j] == 2) 
            {
                return tablero1[i][j];
            }
        }
    }
    
    for (i = 0; i <= FILAS1 - 4; i++) // GANADOR EN DIAGONAL (IZQUIERDA A DERECHA)
    {
        for (j = 0; j <= COLUMNAS1 - 4; j++) 
		{
            if (tablero1[i][j] == 1 && tablero1[i + 1][j + 1] == 1 && tablero1[i + 2][j + 2] == 1 && tablero1[i + 3][j + 3] == 1) 
            {
                return tablero1[i][j];
            }
            else if (tablero1[i][j] == 2 && tablero1[i + 1][j + 1] == 2 && tablero1[i + 2][j + 2] == 2 && tablero1[i + 3][j + 3] == 2) 
            {
                return tablero1[i][j];
            }
        }
    }
    
    for (i = 0; i <= FILAS1 - 4; i++) // GANADOR EN DIAGONAL (DERECHA A IZQUIERDA)
    {
        for (j = 3; j < COLUMNAS1; j++) 
        {
            if (tablero1[i][j] == 1 && tablero1[i + 1][j - 1] == 1 && tablero1[i + 2][j - 2] == 1 && tablero1[i + 3][j - 3] == 1) 
            {
                return tablero1[i][j];
            }
            else if (tablero1[i][j] == 2 && tablero1[i + 1][j - 1] == 2 && tablero1[i + 2][j - 2] == 2 && tablero1[i + 3][j - 3] == 2) 
            {
                return tablero1[i][j];
            }
        }
    }
    
    return 0; // SIN GANADOR
}


// MODO FICHA VERTICAL
void fichaVertical()
{
	for(i = 0; i < FILAS1; i++)
	{
		tablero1[i][columna] = 0;
	}
	
	lugar = FILAS1 - 1;
}


// MODO FICHA HORIZONTAL
void fichaHorizontal()
{
    if (lugar >= 0 && lugar < FILAS1) 
    {
        // Destruye todas las fichas en la fila especificada
        for (i = 0; i < COLUMNAS1; i++) 
        {
            tablero1[lugar][i] = 0;
        }

        // Hacer que las fichas por encima de la fila eliminada caigan
        for (i = lugar; i > 0; i--)
        {
            for (j = 0; j < COLUMNAS1; j++)
            {
                tablero1[i][j] = tablero1[i-1][j];
            }
        }

        // Vaciar la primera fila
        for (j = 0; j < COLUMNAS1; j++)
        {
            tablero1[0][j] = 0;
        }
    }
}


// MODO FICHA ANTI-GRAVEDAD
int fichaAntigravedad()
{
	bool q;
	
	do
	{	
		q = true;
		printf("Y en que fila? [1 - 6]|[Arriba a Abajo]: ");
		scanf("%d", &lugar);
	
		if(lugar > 6 || lugar < 1)
		{
			printf("Mal ingresado. De nuevo");
			q = false;
		}
		else if(lugar - 1 != 0)
		{
			q = false;
			printf("\nOcupado. De nuevo\n");
		}
	}
	while(!q);
	
	lugar--;
	
	system("cls");
}


// MODO FICHA DOBLE
void fichaDoble()
{
    srand(time(NULL));
    
    int dado = rand() % 6 + 1; // UN NUMERO RANDOM DE 1 A 6 SIMULANDO UN DADO
    
    printf("Arma de doble filo. Tiro el dado!\n");
    sleep(2);
    
    if(dado == (jug % 2 + 1)) // SI EL DADO ES IGUAL AL NUMERO DEL JUGADOR (1 O 2)
    {
        printf("Funciono!");
        tablero1[lugar - 1][columna] = dado;
    }
    else if((dado == 1 && (jug % 2 + 1) == 2) || (dado == 2 && (jug % 2 + 1) == 1)) // SI ES 1 Y LO TIRO EL JUGADOR 2 O VICEVERSA
    {
        printf("JAJAJAJAJAJ");
        tablero1[lugar - 1][columna] = dado;
    }
    else // NT
    {
        printf("Bueno peor es nada,");
    }
    
    printf(" salio %d,", dado);
    
    if(dado == 1)
    {
        printf(" es para el uno\n");
    }
    else if(dado == 2)
    {
        printf(" es para el dos\n");
    }
    else
    {
        printf(" para ninguno >=(\n");
    }
}


// JUEGO
void modoEspecial() 
{
    // DECLARAMOS
    int especial;
    int k, h, y;
    char modo[5][255]; // CHAR NOMBRE[CANTIDAD][CARACTERES]
    strcpy(modo[1], "\n[|1|] FICHA VERTICAL\n- Cae y destruye todas las fichas (excepto ella) de su columna\n");
    strcpy(modo[2], "\n[|2|] FICHA HORIZONTAL\n- Cae y destruye todas las ficha (excepto ella) de su fila\n- Todas las de encima caen\n- Afecta a la Anti-Gravedad\n");
    strcpy(modo[3], "\n[|3|] FICHA ANTI-GRAVEDAD\n- Se coloca en cualquier punto del tablero1\n");
    strcpy(modo[4], "\n[|4|] FICHA DOBLE\n- Se tira una ficha normal\n- Se tira una segunda ficha encima y se lanza un dado\n- Si sale 1 es del 'jugador 1'\n- Si sale 2 es del 'jugador 2'\n- Si sale otro numero, no habra ficha extra\n");
    int uso[5][2] = {0};
   
    dibujarTablero1(); // HACEMOS EL TABLERO
    
    do // BUCLE PARA TODOS LOS TURNOS
    {   
        jug++; // CONTADOR PARA DETERMINAR EL TURNO
        
        printf(AMARILLO_F AMARILLO_T "'O'" RESET_COLOR);
        printf(AMARILLO_T " JUGADOR UNO" RESET_COLOR);
        printf(" - ");
        printf(ROJO_F ROJO_T"'X'" RESET_COLOR);
        printf(ROJO_T " JUGADOR 2" RESET_COLOR);
        printf(CYAN_T "\nTURNO JUGADOR %d\n\n" RESET_COLOR, jug % 2 + 1);
		
        	printf("FICHAS ESPECIALES:\n");        
        	for(i = 1; i < 5; i++)
        	{
            	if(uso[i - 1][jug % 2 + 1] == 2)
            	{
                	// NADA
            	}
                else
                {
                    printf("%s", modo[i]);
                }
        	}
        	
        	printf("\nQueres usar una? (0 para no usar ninguna): ");
        	scanf("%d", &especial);
        
        	if(especial > 0 && especial < 5)
        	{
            	if (uso[especial - 1][jug % 2 + 1] == 2)
            	{
                	system("cls");
                	printf("Ya usaste esta ficha.\n\n");
                	dibujarTablero1();
                	continue;
            	}
            	else
            	{
                	uso[especial - 1][jug % 2 + 1] = 1;
            	}
        	}
        	else if(especial == 0)
        	{
            	// No se usa ninguna ficha especial
        	}
        	else
        	{
            	system("cls");
            	printf("Numero mal ingresado.\n\n");
            	dibujarTablero1();
            	continue;
        	}
        
        printf("\nColumna para tirar la ficha (1 - 7): ");
        scanf("%d", &columna);
        
        if(uso[2][jug % 2 + 1] != 1) // PARA QUE NO OCURRA EN LA FICHA ANTI-GRAVITACIONAL
        {
            system("cls");
        }
        
        if (columna < 1 || columna > 7) // INGRESA ALGO MAL Y NO INICIA
        {
            printf("Columna fuera de rango. Por favor ingrese una columna valida (1 - 7). Vamos de nuevo.\n\n");
            jug++;
            dibujarTablero1();
            continue;
        }
        
        columna--; // PARA QUE CONCUERDE CON EL FOR
        
        k = 0;
        
        for (i = 0; i < FILAS1; i++) // DETERMINAMOS DONDE VA LA FICHA
        {
            if (tablero1[i][columna] != 0) // SI POR LA COLUMNA ENCUENTRA UNA FICHA, CONTEA A 'K'
            {
                k++;
            } 
            else // SINO 'LUGAR' SERA IGUAL A LA ITERACION, CUANDO ENCUENTRE UNA FICHA, 'LUGAR' TENDRA ASIGNADO EL ULTIMO LUGAR LIBRE
            {   
                lugar = i;
            }
        }
        
        if (k == FILAS1) // LLENO
        {
            printf("Columna llena. Elija otra columna.\n");
            continue;
        }
        
        if(uso[2][jug % 2 + 1] == 1) // PARA QUE 'LUGAR' TOME EL VALOR QUE LE DAMOS EN LA FUNCION
        {
            fichaAntigravedad();
        }
        else if(uso[1][jug % 2 + 1] == 1)
        {
            fichaHorizontal();
        }
		else if(uso[0][jug % 2 + 1] == 1)
        {
             fichaVertical();
        }
        
        tablero1[lugar][columna] = jug % 2 + 1; // SE COLOCA LA FICHA EN EL LUGAR LIBRE Y AL JUGADOR QUE SEGUN CORRESPONDA
        
        if(uso[3][jug % 2 + 1] == 1)
        {
            fichaDoble();
        }
        
        uso[especial - 1][jug % 2 + 1] = 2;
        
        dibujarTablero1(); // VOLVEMOS A DIBUJAR TABLERO
        
        if (verificarGanador1() != 0) // SI LA FUNCION RETORNA 1 (HAY GANADOR) SE TERMINA EL JUEGO
        {
            int ganador = verificarGanador1();
            printf("GANO EL GOAT! GANO EL %d", jug % 2 + 1);
            exit(0);
        }
    } 
    while (1); // CICLO INFINITO
}
