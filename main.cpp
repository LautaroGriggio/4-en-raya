#include "modoFichasEspeciales.h"
#include "modoContrarreloj.h"
#include "modoIA.h"
#include "modoNormal.h"
#include <iostream>
#include <windows.h>

void titulo() {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Texto a centrar
   string texto = "4 EN LINEA";

    // Calcular espacios a agregar a la izquierda para centrar
    int espacios = (consolaAncho - texto.length()) / 2;
    for (int i = 0; i < espacios; ++i) {
        cout << " ";
    }
   cout << texto << endl;
}

void centrarTexto(const string& texto) {
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    int consolaAncho = csbi.srWindow.Right - csbi.srWindow.Left + 1;

    // Calcular espacios a agregar a la izquierda para centrar
    int espacios = (consolaAncho - texto.length()) / 2;
    for (int i = 0; i < espacios; ++i) {
        cout << " ";
    }
   cout << texto << endl;
}

int main() {
    titulo();
    bool salir = false;
    int opcion;

    centrarTexto("|1. Jugador vs Jugador             |");
    centrarTexto("|2.   Jugadores - Fichas Especiales|");
    centrarTexto("|3. 1v1 Contra Reloj               |");
    centrarTexto("|4. Jugador vs Maquina             |");
    centrarTexto("|5. Salir                          |");
    std::cout << std::endl;

    centrarTexto("Elija un modo: ");
    std::cin >> opcion;

    while (!salir) {
        switch (opcion) {
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
                cout << "Saliendo del programa..." << endl;
                salir = true;
                break;
                
            default:
                cout << "Opcion invalida. Por favor, seleccione una opcion valida." << endl;
                break;
        }

        if (!salir) {
            centrarTexto("Elija un modo: ");
            std::cin >> opcion;
        }
    }

    return 0;
}

