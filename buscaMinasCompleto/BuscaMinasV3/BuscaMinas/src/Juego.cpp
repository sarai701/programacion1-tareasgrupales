//Jonathan Samuel Gonzalez Ixpata
#include "Juego.h"
#include <fstream>
#include <unistd.h>
#include <chrono>   // Para el cronómetro
#include <iomanip>  // Para formato de tiempo

int Juego::aleatorio_en_rango(int minimo, int maximo)
	{
		return minimo + rand() / (RAND_MAX / (maximo - minimo + 1) + 1);
	}

	int Juego::filaAleatoria()
	{
		return this->aleatorio_en_rango(0, this->tablero.getAlturaTablero() - 1);
	}

	int Juego::columnaAleatoria()
	{
		return this->aleatorio_en_rango(0, this->tablero.getAnchoTablero() - 1);
	}

	Juego::Juego(Tablero tablero, int cantidadMinas)
    : tablero(tablero), cantidadMinas(cantidadMinas), score(0)
    {
        this->tablero = tablero;
		this->cantidadMinas = cantidadMinas;
		this->colocarMinasAleatoriamente();
		this->score = 0; //inicializar el score en 0
	}
	string Juego::getNombreJugador(){
	    return nombreJugador;
	}
	void Juego::aumentarScore(){
	this->score +=5;//se suman 5pts por celda buena
	}
	int Juego::getScore(){
	    return this->score;
	}

	void Juego::colocarMinasAleatoriamente()
	{
		int x, y, minasColocadas = 0;

		while (minasColocadas < this->cantidadMinas)
		{
			x = this->columnaAleatoria();
			y = this->filaAleatoria();
			if (this->tablero.colocarMina(x, y))
			{
				minasColocadas++;
			}
		}
	}

	int Juego::tiempoTranscurrido() {
    auto ahora = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::seconds>(ahora - inicio).count();
}

	int Juego::solicitarFilaUsuario() {
    int fila;
    do {
        std::cout << "Ingresa la FILA (1-" << tablero.getAlturaTablero() << "): ";
        std::cin >> fila;
        if (fila < 1 || fila > tablero.getAlturaTablero()) {
            std::cout << "Error: Fila inválida. Intente nuevamente.\n";
        }
    } while (fila < 1 || fila > tablero.getAlturaTablero());
    return fila - 1;
}

	int Juego::solicitarColumnaUsuario() {
    int columna;
    do {
        std::cout << "Ingresa la COLUMNA (1-" << tablero.getAnchoTablero() << "): ";
        std::cin >> columna;
        if (columna < 1 || columna > tablero.getAnchoTablero()) {
            std::cout << "Error: Columna inválida. Intente nuevamente.\n";
        }
    } while (columna < 1 || columna > tablero.getAnchoTablero());
    return columna - 1;
}

	bool Juego::jugadorGana()
	{
		int conteo = this->tablero.contarCeldasSinMinasYSinDescubrir();
		if (conteo == 0)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	void Juego::iniciar(int &vidas) {
    inicio = chrono::system_clock::now(); // Inicia el cronómetro

    cout << "Ingrese su nombre: ";
    cin.ignore();
    getline(cin, nombreJugador);

    int fila, columna;
    bool juegoTerminado = false;

    while (vidas > 0 && !juegoTerminado) {
        system("cls"); // Limpia la consola (Windows)

        // Muestra tiempo, nombre y puntuación
        int segundos = tiempoTranscurrido();
        cout << "Jugador: " << nombreJugador << " | "
             << "Vidas: " << vidas << " | "
             << "Tiempo: "
             << setw(2) << setfill('0') << segundos / 60 << ":"
             << setw(2) << setfill('0') << segundos % 60 << "\n\n";

        tablero.imprimir(); // Muestra el tablero

        // Solicita coordenadas con validación
        fila = solicitarFilaUsuario();
        columna = solicitarColumnaUsuario();

        // Procesa el movimiento
        bool movimientoSeguro = tablero.descubrirMina(columna, fila);

        if (!movimientoSeguro) {
            vidas--;
            if (vidas > 0) {
                cout << "\n¡MINA! Vidas restantes: " << vidas << endl;
                cout << "Presione Enter para continuar...";
                cin.ignore(); cin.get();
            } else {
                cout << "\n¡PERDISTE " << nombreJugador << "!\n";
                tablero.setModoDesarrollador(true);
                tablero.imprimir();
                juegoTerminado = true;
            }
        } else {
            aumentarScore();
            cout << "\nPuntuación actual: " << getScore() << endl;
            cout << "Presione Enter para continuar...";
            cin.ignore(); cin.get();
        }

        // Verifica victoria
        if (jugadorGana()) {
            cout << "\n¡FELICIDADES " << nombreJugador << "! HAS GANADO\n";
            cout << "Puntuación final: " << getScore() << endl;
            tablero.setModoDesarrollador(true);
            tablero.imprimir();
            juegoTerminado = true;
        }
    }

    // Muestra tiempo total al finalizar
    int tiempoTotal = tiempoTranscurrido();
    cout << "\nTiempo total de juego: "
         << tiempoTotal / 60 << "m " << tiempoTotal % 60 << "s\n";
}
