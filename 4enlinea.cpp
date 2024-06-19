#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>  // Para la funci�n exit()

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


using namespace std;

const int FILAS = 6;
const int COLUMNAS = 7;

vector<vector<int> > tablero(FILAS, vector<int>(COLUMNAS, 0));

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);


int line()
{
	for (int k = 0; k < 7; ++k) 
	{
        printf(AZUL_F AZUL_T "+---" RESET_COLOR);
    }
    printf(AZUL_F AZUL_T "+" RESET_COLOR);
    printf("\n");
}


int dibujarTablero() 
{
	line();
	
    for(int i = 0; i < 6; i++)
    {
        for(int j = 0; j < 7; j++)
        {
            printf(AZUL_F AZUL_T "|" RESET_COLOR);
            
            if(tablero[i][j] == 0)
            {
                printf(BLANCO_F BLANCO_T " %d ", tablero[i][j]);
            }
            else if(tablero[i][j] == 1)
            {
                printf(AMARILLO_F AMARILLO_T " %d ", tablero[i][j]);
            }
            else if(tablero[i][j] == 2)
            {
                printf(ROJO_F ROJO_T " %d ", tablero[i][j]);
            }
        }
        printf(AZUL_F AZUL_T "|" RESET_COLOR);
        printf("\n");

        // Imprimir l�neas separadoras entre filas
        if (i < 5) {
            line();
        }
    }
    
    line();
}


bool verificarGanador(int fila, int col) 
{
    int jugadorActual = tablero[fila][col];
    int contador = 1;  // Contador para contar fichas consecutivas del mismo jugador

    // Verificar horizontalmente hacia la derecha
    for (int j = col + 1; j < COLUMNAS && tablero[fila][j] == jugadorActual; ++j) {
        ++contador;
    }

    // Verificar horizontalmente hacia la izquierda
    for (int j = col - 1; j >= 0 && tablero[fila][j] == jugadorActual; --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado horizontalmente

    contador = 1;

    // Verificar verticalmente hacia arriba
    for (int i = fila - 1; i >= 0 && tablero[i][col] == jugadorActual; --i) {
        ++contador;
    }

    // Verificar verticalmente hacia abajo
    for (int i = fila + 1; i < FILAS && tablero[i][col] == jugadorActual; ++i) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado verticalmente

    contador = 1;

    // Verificar diagonal hacia abajo (izquierda a derecha)
    for (int i = fila + 1, j = col + 1; i < FILAS && j < COLUMNAS && tablero[i][j] == jugadorActual; ++i, ++j) {
        ++contador;
    }

    for (int i = fila - 1, j = col - 1; i >= 0 && j >= 0 && tablero[i][j] == jugadorActual; --i, --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia abajo

    contador = 1;

    // Verificar diagonal hacia arriba (izquierda a derecha)
    for (int i = fila - 1, j = col + 1; i >= 0 && j < COLUMNAS && tablero[i][j] == jugadorActual; --i, ++j) {
        ++contador;
    }

    for (int i = fila + 1, j = col - 1; i < FILAS && j >= 0 && tablero[i][j] == jugadorActual; ++i, --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia arriba

    return false;  // No hay ganador en ninguna direcci�n
}


void mostrarMenu() 
{	
    cout << "Menu:" << endl;
    cout << "1. Jugador vs Jugador" << endl;
    cout << "2. 2 Jugadores - Fichas Especiales!" << endl;
    cout << "3. Salir" << endl;
    cout << "Ingrese el numero de la opcion deseada: ";
}


int juegoUno() 
{
    int jugador = 1;
    bool juegoTerminado = false;

    while (!juegoTerminado) 
	{
        dibujarTablero();
		
		int colum;
        int columna;
        cout << "\nJugador " << jugador << ", ingresa el numero de columna (1 - 7): ";
        cin >> colum;
        
        columna = colum - 1;

        if (columna < 0 || columna >= COLUMNAS) 
		{	
			system("cls");
            cout << "Columna inv�lida. Por favor, ingresa un n�mero entre 0 y 6." << endl;
            
            continue;
        }
        
        system("cls");

        for (int i = FILAS - 1; i >= 0; --i) 
		{
            if (tablero[i][columna] == 0) 
			{
                tablero[i][columna] = jugador;
                if (verificarGanador(i, columna)) 
				{
                    dibujarTablero();
                    cout << endl;
                    cout << "�Jugador " << jugador << " ha ganado!" << endl;
                    juegoTerminado = true;
                }
                break;
            }
        }

        jugador = (jugador == 1) ? 2 : 1;
    }

    // Aqu� puedes agregar cualquier limpieza adicional o salida
    return 0;
}


int main() 
{
    bool salir = false;

    while (!salir) 
	{
        mostrarMenu();

        int opcion;
        cin >> opcion;

        switch (opcion) 
		{
            case 1:
            	system("cls");
                juegoUno();
                
                exit(0);
            case 2:
            	system("cls");
//                juegoDos();
                // Aqu� va el c�digo correspondiente a la opci�n 2
                break;
            case 3:
                cout << "Saliendo del programa..." << endl;
                salir = true;
                break;
            default:
                cout << "Opci�n inv�lida. Por favor, seleccione una opci�n v�lida." << endl;
                break;
        }
    }

    return 0;
}

