#include <iostream>
#include <cstdlib>  // Para rand() y srand()
#include <ctime>    // Para time()

// DECLARAMOS LOS COLORES (FONDO Y LETRA)
#define RESET_COLOR    "\x1b[0m"
#define NEGRO_T        "\x1b[30m"
#define NEGRO_F        "\x1b[40m"
#define ROJO_T         "\x1b[31m"
#define ROJO_F         "\x1b[41m"
#define VERDE_T        "\x1b[32m"
#define VERDE_F        "\x1b[42m"
#define AMARILLO_T     "\x1b[38;5;227m"
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

const int FILAS3 = 6;
const int COLUMNAS3 = 7;
int tablero3[FILAS3][COLUMNAS3] = {0};  // Inicializar el tablero3 con ceros

void line3() 
{
    for (int k = 0; k < 7; ++k) 
	{
        printf(AZUL_F AZUL_T "+---" RESET_COLOR);
    }
    printf(AZUL_F AZUL_T "+" RESET_COLOR);
    printf("\n");
}

void dibujarTablero3() 
{
    system("cls");  // Limpiar la consola antes de dibujar el tablero3

    line3();

    for (int i = 0; i < 6; i++) 
	{
        for (int j = 0; j < 7; j++) 
		{
            printf(AZUL_F AZUL_T "|" RESET_COLOR);

            if (tablero3[i][j] == 0) 
			{
                printf(BLANCO_F BLANCO_T " %d ", tablero3[i][j]);
            } 
			else if (tablero3[i][j] == 1) 
			{
                printf(AMARILLO_F AMARILLO_T " %d ", tablero3[i][j]);
            } 
			else if (tablero3[i][j] == 2) 
			{
                printf(ROJO_F ROJO_T " %d ", tablero3[i][j]);
            }
        }
        printf(AZUL_F AZUL_T "|" RESET_COLOR);
        printf("\n");

        // Imprimir lÃ­neas separadoras entre filas
        if (i < 5) {
            line3();
        }
    }

    line3();
}

bool verificarGanador3(int fila, int col) 
{
    int jugadorActual = tablero3[fila][col];
    int contador = 1;  // Contador para contar fichas consecutivas del mismo jugador

    // Verificar horizontalmente hacia la derecha
    for (int j = col + 1; j < COLUMNAS3 && tablero3[fila][j] == jugadorActual; ++j) {
        ++contador;
    }

    // Verificar horizontalmente hacia la izquierda
    for (int j = col - 1; j >= 0 && tablero3[fila][j] == jugadorActual; --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado horizontalmente

    contador = 1;

    // Verificar verticalmente hacia arriba
    for (int i = fila - 1; i >= 0 && tablero3[i][col] == jugadorActual; --i) {
        ++contador;
    }

    // Verificar verticalmente hacia abajo
    for (int i = fila + 1; i < FILAS3 && tablero3[i][col] == jugadorActual; ++i) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado verticalmente

    contador = 1;

    // Verificar diagonal hacia abajo (izquierda a derecha)
    for (int i = fila + 1, j = col + 1; i < FILAS3 && j < COLUMNAS3 && tablero3[i][j] == jugadorActual; ++i, ++j) {
        ++contador;
    }

    for (int i = fila - 1, j = col - 1; i >= 0 && j >= 0 && tablero3[i][j] == jugadorActual; --i, --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia abajo

    contador = 1;

    // Verificar diagonal hacia arriba (izquierda a derecha)
    for (int i = fila - 1, j = col + 1; i >= 0 && j < COLUMNAS3 && tablero3[i][j] == jugadorActual; --i, ++j) {
        ++contador;
    }

    for (int i = fila + 1, j = col - 1; i < FILAS3 && j >= 0 && tablero3[i][j] == jugadorActual; ++i, --j) {
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia arriba

    return false;  // No hay ganador en ninguna direcciÃ³n
}

int movimientoia() 
{
    int columna;
    bool columnaValida = false;

    do {
        columna = rand() % COLUMNAS3;

        // Verificar desde la fila más baja hacia arriba si la columna está disponible
        for (int fila = FILAS3 - 1; fila >= 0; --fila) {
            if (tablero3[fila][columna] == 0) {
                columnaValida = true;
                break;
            }
        }

    } while (!columnaValida);

    return columna;
}


int inteligenciaArtifical() 
{
    int jugador = 1;
    bool juegoTerminado = false;

    while (!juegoTerminado) 
    {
        dibujarTablero3();

        // Turno del jugador humano
        if (jugador == 1) 
        {
            int columna;
            cout << "\nJugador " << jugador << ", ingresa el número de columna (1 - 7): ";
            cin >> columna;
            system("cls");
            columna--;  // Ajuste de columna a índice base 0

            if (columna < 0 || columna >= COLUMNAS3 || tablero3[0][columna] != 0) 
            {
                cout << "Columna inválida o llena. Por favor, ingresa un número válido." << endl;
                continue;
            }

            for (int i = FILAS3 - 1; i >= 0; --i) 
            {
                if (tablero3[i][columna] == 0) {
                    tablero3[i][columna] = jugador;
                    if (verificarGanador3(i, columna)) {
                        dibujarTablero3();
                        cout << endl;
                        cout << "¡Jugador " << jugador << " ha ganado!" << endl;
                        juegoTerminado = true;
                    }
                    break;
                }
            }
        }
        // Turno de la IA
        else {
            int columna = movimientoia();
            for (int i = FILAS3 - 1; i >= 0; --i) 
            {
                if (tablero3[i][columna] == 0) 
                {
                    tablero3[i][columna] = jugador;
                    if (verificarGanador3(i, columna)) 
                    {
                        dibujarTablero3();
                        cout << endl;
                        cout << "¡La IA ha ganado!" << endl;
                        juegoTerminado = true;
                        exit(0);
                    }
                    break;
                }
            }
        }

        jugador = (jugador == 1) ? 2 : 1;
    }

    return 0;
}
