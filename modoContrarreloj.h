#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>  // Para la función exit()
#include <chrono>   // Para el temporizador
#include <thread>   // Para el temporizador
#include <atomic>   // Para el temporizador

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

int TIEMPO_TOTAL_JUGADOR = 40; // Tiempo total en segundos para cada jugador

const int FILAS2 = 6;
const int COLUMNAS2 = 7;
int tablero2[6][7] = {0};

// Variables para el tiempo restante de cada jugador
atomic<int> tiempoRestanteJugador1(TIEMPO_TOTAL_JUGADOR);
atomic<int> tiempoRestanteJugador2(TIEMPO_TOTAL_JUGADOR);

// Bandera para indicar turno activo/inactivo
atomic<bool> turnoActivoJugador1(false);
atomic<bool> turnoActivoJugador2(false);


void line2() 
{
    for (int k = 0; k < 7; ++k) 
	{
        printf(AZUL_F AZUL_T "+---" RESET_COLOR);
    }
    printf(AZUL_F AZUL_T "+" RESET_COLOR);
    printf("\n");
}

void dibujarTablero2() 
{
    system("cls");  // Limpiar la consola antes de dibujar el tablero2

    line2();

    for (int i = 0; i < 6; i++) 
	{
        for (int j = 0; j < 7; j++) 
		{
            printf(AZUL_F AZUL_T "|" RESET_COLOR);

            if (tablero2[i][j] == 0) 
			{
                printf(BLANCO_F BLANCO_T " %d ", tablero2[i][j]);
            } 
			else if (tablero2[i][j] == 1) 
			{
                printf(AMARILLO_F AMARILLO_T " %d ", tablero2[i][j]);
            } 
			else if (tablero2[i][j] == 2) 
			{
                printf(ROJO_F ROJO_T " %d ", tablero2[i][j]);
            }
        }
        printf(AZUL_F AZUL_T "|" RESET_COLOR);
        printf("\n");

        // Imprimir líneas separadoras entre filas
        if (i < 5) 
		{
            line2();
        }
    }

    line2();
}

bool verificarGanador2(int fila, int col) 
{
    int jugadorActual = tablero2[fila][col];
    int contador = 1;  // Contador para contar fichas consecutivas del mismo jugador

    // Verificar horizontalmente hacia la derecha
    for (int j = col + 1; j < COLUMNAS2 && tablero2[fila][j] == jugadorActual; ++j) 
	{
        ++contador;
    }

    // Verificar horizontalmente hacia la izquierda
    for (int j = col - 1; j >= 0 && tablero2[fila][j] == jugadorActual; --j) 
	{
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado horizontalmente

    contador = 1;

    // Verificar verticalmente hacia arriba
    for (int i = fila - 1; i >= 0 && tablero2[i][col] == jugadorActual; --i) 
	{
        ++contador;
    }

    // Verificar verticalmente hacia abajo
    for (int i = fila + 1; i < FILAS2 && tablero2[i][col] == jugadorActual; ++i) 
	{
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado verticalmente

    contador = 1;

    // Verificar diagonal hacia abajo (izquierda a derecha)
    for (int i = fila + 1, j = col + 1; i < FILAS2 && j < COLUMNAS2 && tablero2[i][j] == jugadorActual; ++i, ++j) 
	{
        ++contador;
    }

    for (int i = fila - 1, j = col - 1; i >= 0 && j >= 0 && tablero2[i][j] == jugadorActual; --i, --j) 
	{
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia abajo

    contador = 1;

    // Verificar diagonal hacia arriba (izquierda a derecha)
    for (int i = fila - 1, j = col + 1; i >= 0 && j < COLUMNAS2 && tablero2[i][j] == jugadorActual; --i, ++j) 
	{
        ++contador;
    }

    for (int i = fila + 1, j = col - 1; i < FILAS2 && j >= 0 && tablero2[i][j] == jugadorActual; ++i, --j) 
	{
        ++contador;
    }

    if (contador >= 4) return true;  // Ganador encontrado diagonal hacia arriba

    return false;  // No hay ganador en ninguna dirección
}

void mostrarTiempoRestante(int jugador, atomic<int>& tiempoRestante, atomic<bool>& turnoActivo) 
{
    while (tiempoRestante > 0) 
    {
        if (turnoActivo) 
        {
            cout << "\rJugador " << jugador << " - Tiempo restante: " << tiempoRestante << " segundos " << flush;
            this_thread::sleep_for(chrono::seconds(1));
            --tiempoRestante;
        } 
        else 
        {
            this_thread::sleep_for(chrono::milliseconds(100));
        }
    }

    // Cuando el tiempo del jugador llega a cero
    if (tiempoRestante <= 0) 
    {
        cout << "\n¡Tiempo agotado para Jugador " << jugador << "!\n";
        // Detener el juego y marcar al otro jugador como ganador
        if (jugador == 1) 
        {
            cout << "¡Jugador 2 gana por tiempo!\n";
        } 
        else 
        {
            cout << "¡Jugador 1 gana por tiempo!\n";
        }
        exit(0); // Opción para salir del juego, puedes manejar esto según la lógica de tu programa
    }
}

// Función principal del juego
int contraReloj() 
{
    int jugador = 1;
    bool juegoTerminado = false;

    tiempoRestanteJugador1 = TIEMPO_TOTAL_JUGADOR;
    tiempoRestanteJugador2 = TIEMPO_TOTAL_JUGADOR;

    // Lanzar los hilos para mostrar el tiempo restante de cada jugador
    thread tMostrarTiempo1(mostrarTiempoRestante, 1, ref(tiempoRestanteJugador1), ref(turnoActivoJugador1));
    thread tMostrarTiempo2(mostrarTiempoRestante, 2, ref(tiempoRestanteJugador2), ref(turnoActivoJugador2));

    while (!juegoTerminado) 
    {
        dibujarTablero2();

        int colum;
        int columna;

        atomic<int>& tiempoRestante = (jugador == 1) ? tiempoRestanteJugador1 : tiempoRestanteJugador2;
        atomic<bool>& turnoActivo = (jugador == 1) ? turnoActivoJugador1 : turnoActivoJugador2;
        atomic<bool>& turnoInactivo = (jugador == 1) ? turnoActivoJugador2 : turnoActivoJugador1;

        turnoActivo = true;
        turnoInactivo = false;

        cout << "\nJugador " << jugador << ", ingresa el numero de columna (1 - 7): ";
        cin >> colum;

        columna = colum - 1;

        if (columna < 0 || columna >= COLUMNAS2) 
        {
            system("cls");
            cout << "Columna inválida. Por favor, ingresa un número entre 1 y 7." << endl;
            turnoActivo = false;
            continue;
        }

        system("cls");

        for (int i = FILAS2 - 1; i >= 0; --i) 
        {
            if (tablero2[i][columna] == 0) 
            {
                tablero2[i][columna] = jugador;
                if (verificarGanador2(i, columna)) 
                {
                    dibujarTablero2();
                    cout << endl;
                    cout << "¡Jugador " << jugador << " ha ganado!" << endl;
                    juegoTerminado = true;
                }
                break;
            }
        }

        turnoActivo = false;
        jugador = (jugador == 1) ? 2 : 1;
    }

    // Esperar a que terminen los hilos de tiempo
    tMostrarTiempo1.join();
    tMostrarTiempo2.join();

    return 0;
}

